#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#define GAME_THREAD_STACK_SIZE             (1024*3)
#define GAME_THREAD_PRIORITY               (10)
#define GAME_THREAD_PREEMPTION_THRESHOLD   (GAME_THREAD_PRIORITY)
#define GAME_THREAD_NAME                   "Game thread"

#ifdef __cplusplus
}
#endif
