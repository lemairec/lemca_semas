#ifndef APPARCHIVE_H
#define APPARCHIVE_H

#ifndef __cplusplus
#error 
#endif /* __cplusplus */

#define CCI_USE_ARCHIVE

#include <stdint.h>
#include <vector>

std::vector<uint8_t> AppArchive_compress(const std::vector<uint8_t>& poolData);
std::vector<uint8_t> expand(uint8_t channel, const uint8_t *comp, size_t compressed_size, size_t decomp_sz);
uint8_t AppArchive_open(std::vector<uint8_t>& archive);
uint32_t AppArchive_read(uint8_t channel, uint8_t* dst, uint32_t u32BlockSizeReq);
void AppArchive_seekToBegin(uint8_t channel);
void close(uint8_t channel);

#endif /* APPARCHIVE_H */
