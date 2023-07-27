#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"
#include "tx_api.h"
#include "game_core_config.h"

UINT game_core_thread_create(TX_BYTE_POOL *byte_pool);

#ifdef __cplusplus
}
#endif
