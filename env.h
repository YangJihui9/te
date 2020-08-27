#ifndef ENV_H
#define ENV_H

#ifndef BUFSIZE
#define BUFSIZE    80
#endif

#ifndef TERMINAL_TASK_STACK_SIZE
#define TERMINAL_TASK_STACK_SIZE      256
#endif

#ifndef RXTX_TASK_STACK_SIZE
#define RXTX_TASK_STACK_SIZE      256
#endif


#ifndef TERMINAL_TASK_PRIO
#define TERMINAL_TASK_PRIO            20
#endif

#ifndef RXTX_TASK_PRIO
#define RXTX_TASK_PRIO            21
#endif

#endif  // ENV_H
