#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <stdint.h>

#define MAX_STACK_SIZE  1024
#define MAX_TASKS       4

typedef struct {
    uint32_t* sp;
    uint8_t task_id;
    void (*entry)(void);
} task_t;

void create_task(void (*task_entry)());
void schedule_next(void);
void PendSV_Handler(void);
void scheduler_launch(void);

// I didn't know this was possible
extern task_t tasks[MAX_TASKS];
extern uint8_t num_tasks;
extern uint8_t curr_task;
extern task_t *current_tcb;
extern task_t *next_tcb;

#endif // ROUND_ROBIN_H