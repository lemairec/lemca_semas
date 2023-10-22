#ifndef ISOBUS_MESSAGE_H_
#define ISOBUS_MESSAGE_H_

#include "driver/twai.h"
#include "AppCommon/AppHW.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void onIsobusMessage(uint8_t canNode_u8, twai_message_t* twai_msg_ps, uint8_t isRX);

#ifdef __cplusplus
}
#endif

#endif