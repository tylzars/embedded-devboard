#include <stdint.h>
#include "round_robin.h"

uint8_t task_stacks[MAX_TASKS][MAX_STACK_SIZE];
task_t tasks[MAX_TASKS];
uint8_t num_tasks = 0;

void create_task(void* task_entry) {
    tasks[num_tasks].entry = task_entry;
    tasks[num_tasks].sp = (uint32_t*)(&task_stacks[num_tasks][MAX_STACK_SIZE]);

    tasks[num_tasks].ctx.SP = (uint32_t)(&task_stacks[num_tasks][MAX_STACK_SIZE]);
    tasks[num_tasks].ctx.LR = (uint32_t)(&create_task);
    num_tasks++;
    return;
}

__attribute__((naked)) void PendSV_Handler(void) {
    return;
}