#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#define GUI_THREAD_STACK_SIZE             (1024*3)
#define GUI_THREAD_PRIORITY               (10)
#define GUI_THREAD_PREEMPTION_THRESHOLD   (GUI_THREAD_PRIORITY)
#define GUI_THREAD_NAME                   "GUI thread"

#ifdef __cplusplus
}
#endif
