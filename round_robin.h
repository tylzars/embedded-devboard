#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <stdint.h>

#define MAX_STACK_SIZE  1024
#define MAX_TASKS       2

typedef struct {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r12;
    uint32_t SP; // r13
    uint32_t LR; // r14
    uint32_t PC; // r15
} context_t;

typedef struct {
    void (*entry)(void);
    uint32_t* sp;
    context_t ctx;
} task_t;

void create_task(void* task_entry);

#endif // ROUND_ROBIN_H