/* ************************************************************************ */


/* ************************************************************************ */
#include <stdint.h> // malloc
#include <string.h>
#include <map>
#include <IsoCommonDef.h>
#include <IsoVtcApi.h>
#include "AppPool.h"
#include "AppCommon/AppUtil.h"
#include "AppCommon/AppHW.h"
#if defined(CCI_USE_ARCHIVE)
#include "AppArchive.h"
#endif /* defined(CCI_USE_ARCHIVE) */



/* ************************************************************************ */
#if defined(_MSC_VER )
#pragma warning(disable : 4996)
#endif // defined(_MSC_VER )

/* ************************************************************************ */

/* static function declarations */

/* ************************************************************************ */
static uint8_t s_appPoolIdx = 1U;
static std::map<uint8_t, AppPool*>s_appPool;

/* ************************************************************************ */
static uint8_t getNextPoolIdx()
{
    if (s_appPool.size() >= 16U) /* We only allow up to 16 open archives. */
    {
       return 0U;
    }

    std::map<uint8_t, AppPool*>::iterator it = s_appPool.find(s_appPoolIdx);
    while (it != s_appPool.end())
    {
       s_appPoolIdx++; /* start index at 1; '0' is invalid channel */
       if (s_appPoolIdx == 0U)
       {
          s_appPoolIdx = 1U;
       }

       it = s_appPool.find(s_appPoolIdx);
    }

   return s_appPoolIdx;
}

uint8_t poolLoadByFilename(const char * pcFilename)
{
   if (pcFilename == nullptr)
   {
      return 0U;
   }

   uint8_t poolIdx = getNextPoolIdx();
   if (poolIdx == 0)
   {
       return 0U;
   }

   AppPool* appPool = new AppPool(pcFilename);
   s_appPool[poolIdx] = appPool;
   return poolIdx;
}

uint8_t poolLoadByByteArray(const uint8_t* data, uint32_t size)
{
    if ((data == nullptr) || (size == 0))
    {
       return 0U;
    }

    uint8_t poolIdx = getNextPoolIdx();
    if (poolIdx == 0)
    {
        return 0U;
    }

    AppPool* appPool = new AppPool(data, size);
    s_appPool[poolIdx] = appPool;
    return poolIdx;
}

void poolFree(uint8_t channel)
{
   std::map<uint8_t, AppPool*>::iterator it = s_appPool.find(channel);
   if (it != s_appPool.end())
   {
      delete it->second;
      s_appPool.erase(it);
   }
}

static AppPool* getPoolByChannel(uint8_t channel)
{
   std::map<uint8_t, AppPool*>::iterator it = s_appPool.find(channel);
   return (it == s_appPool.end()) ? nullptr : it->second;
}

extern "C" iso_bool poolIsOpen(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return ((appPool != nullptr) && (appPool->isOpen())) ? ISO_TRUE : ISO_FALSE;
}

extern "C" iso_bool poolOpen(uint8_t channel, uint32_t mode)
{
   AppPool* appPool = getPoolByChannel(channel);
   return ((appPool != nullptr) && (appPool->open(mode))) ? ISO_TRUE : ISO_FALSE;
}

extern "C" void poolClose(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   if (appPool != nullptr)
   {
      appPool->close();
   }
}

extern "C" uint32_t poolReadPos(uint8_t channel, uint8_t* dst, uint32_t u32BlockSizeReq)
{
   AppPool* appPool = getPoolByChannel(channel);
   if (appPool == nullptr)
   {
      return 0U;
   }

   // Continue reading until EOF or as required data is read.
   uint32_t pos = 0;
   uint32_t count = 0U;
   while ((pos < u32BlockSizeReq) && (count != UINT32_MAX))
   {
      uint32_t req = u32BlockSizeReq - pos;
      count = appPool->read(&dst[pos], req);
      if (count <= req)
      {
         pos += count;
      }
      else
      {
         count = UINT32_MAX;
      }
   }

   return pos;
}

extern "C" uint32_t poolReadEOF(uint8_t channel, uint8_t* dst, uint32_t u32BlockSizeReq)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->read(dst, u32BlockSizeReq) : UINT32_MAX;
}

extern "C" uint32_t poolGetPos(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getPos() : 0U;
}

extern "C" uint32_t poolGetSize(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getSize() : 0U;
}

const uint8_t* poolGetData(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getOpenPool().data() : 0U;
}

extern "C" void poolSeekToBegin(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   if (appPool != nullptr)
   {
      appPool->seekToBegin();
   }
}

extern "C" uint16_t poolGetNumObj(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getNumObj() : 0U;
}

uint32_t poolGetMaxObjectSize(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getMaxObjectSize() : 0U;
}

static std::vector<uint8_t> getDataFromFile(const char* fileName)
{
   std::vector<uint8_t> data;

   if (fileName != nullptr)
   {
      FILE *pFile = fopen(fileName, "rb");
      if (pFile)
      {
         fseek(pFile, 0L, SEEK_END);
         iso_u32 poolSize = static_cast<iso_u32>(ftell(pFile));
         data.resize(poolSize);
         fseek(pFile, 0L, SEEK_SET);
         (void)fread(data.data(), sizeof(iso_u8), poolSize, pFile);
         fclose(pFile);
         pFile = nullptr;
      }
   }

   return data;
}

static std::vector<uint8_t> getDataFromMemory(const uint8_t* poolData, uint32_t poolSize)
{
   std::vector<uint8_t> data;

   if ((poolData != nullptr) && (poolSize > 0))
   {
      data.resize(poolSize);
      memcpy(data.data(), poolData, poolSize);
   }

   return data;
}

AppPool::AppPool(const uint8_t* data, uint32_t dataSize)
   : AppPool(getDataFromMemory(data, dataSize))
{
}

AppPool::AppPool(const char* fileName)
   : AppPool(getDataFromFile(fileName))
{
}

AppPool::AppPool(const std::vector<uint8_t>& data) 
   : m_pool()
   // TODO m_mode(0U),
{
   if (data.empty())
   {
      return;
   }

   PoolData &pool = m_pool[POOL::ALL];
   pool.numObj = IsoVtcGetNumofPoolObjs(data.data(), (iso_s32)data.size());

   if (pool.numObj == 0U)
   {
      return;
   }
   
   pool.data = data;

#if defined(CCI_USE_ARCHIVE)
   for (uint8_t idx = POOL::ALL; idx < POOL::SIZE; idx++)
   {
      PoolData &pool = m_pool[idx];
      if (pool.numObj > 0)
      {
         pool.archive = AppArchive::compress(pool.data);
      }
   }
#endif /* defined(CCI_USE_ARCHIVE) */
}


AppPool::~AppPool()
{
}

bool AppPool::open(uint32_t mode)
{
   printf(" open \n");

    m_pos = 0U;

#if defined(CCI_USE_ARCHIVE)
   m_pool[POOL::ALL  ].channel = AppArchive::open(m_pool[POOL::ALL  ].archive);
#endif /* defined(CCI_USE_ARCHIVE) */


   return m_pool[POOL::ALL].data.size() > 0;

}

uint32_t AppPool::read(uint8_t* dst, uint32_t u32BlockSizeReq)
{
#if !defined(CCI_USE_ARCHIVE)
   if ((m_pool[POOL::ALL].data.empty()) || (dst==nullptr))
   {
      return UINT32_MAX;
   }

   if (m_pos >= m_pool[POOL::ALL].data.size())
   {
      return UINT32_MAX;
   }

   if ((m_pos + u32BlockSizeReq) > m_pool[POOL::ALL].data.size())
   {
      u32BlockSizeReq = static_cast<uint32_t>(m_pool[POOL::ALL].data.size() - m_pos);
   }

   memcpy(dst, &m_pool[POOL::ALL].data[m_pos], u32BlockSizeReq);
   m_pos += u32BlockSizeReq;
   return u32BlockSizeReq;

#else // !defined(CCI_USE_ARCHIVE)
   uint32_t ret = 0U;
   uint8_t idx = 1U;
   for (idx = POOL::ROOT; idx < POOL::SIZE; idx++)
   {
      PoolData &poolData = m_pool[idx];
      if (poolData.channel == 0)
      {
         continue;
      }

      ret = AppArchive::read(poolData.channel, dst, u32BlockSizeReq);
      if (ret <= u32BlockSizeReq)
      {
         m_pos += ret;
         iso_DebugPrint("%d/%d: %d %d\n", idx, poolData.channel, ret, m_pos);
         break;
      }
   }

   if (idx == POOL::SIZE)
   {
      ret = UINT32_MAX;
   }

   return ret;
#endif /* !defined(CCI_USE_ARCHIVE) */
}

const std::vector<uint8_t>& AppPool::getOriginalPool() const
{
   return m_pool[POOL::ALL].data;
}

const std::vector<uint8_t>& AppPool::getOpenPool() const
{
   return m_pool[POOL::ALL].data;
}

void AppPool::close()
{
   m_pool[POOL::ALL].data.clear();
}

bool AppPool::isOpen()const
{
   return m_pool[POOL::ALL].data.size() > 0;
}

uint32_t AppPool::getPos()const
{
   return (m_pool[POOL::ALL].data.size() > 0) ? m_pos : UINT32_MAX;
}

uint32_t AppPool::getSize()const
{
   return (m_pool[POOL::ALL].data.size() > 0) ? static_cast<uint32_t>(m_pool[POOL::ALL].data.size()) : 0U;
}

void AppPool::seekToBegin()
{
#if defined(CCI_USE_ARCHIVE)
   for (uint8_t idx = POOL::ALL; idx < POOL::SIZE; idx++)
   {
      PoolData &poolData = m_pool[idx];
      AppArchive::seekToBegin(poolData.channel);
   }
#endif /* defined(CCI_USE_ARCHIVE) */

   m_pos = 0;
}

uint16_t AppPool::getNumObj()const
{
   return m_numObj;
}

uint32_t AppPool::getMaxObjectSize()const
{
   return (uint32_t)m_pool[POOL::ALL].data.size();
}
