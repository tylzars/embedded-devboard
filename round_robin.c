#include <stdint.h>
#include "round_robin.h"
#include "seven_seg.h"

uint8_t task_stacks[MAX_TASKS][MAX_STACK_SIZE];
task_t tasks[MAX_TASKS];
uint8_t num_tasks = 0;
uint8_t curr_task = 0;
task_t* current_tcb = 0x0;
task_t* next_tcb = 0x0;

void create_task(void (*task_entry)()) {
    // Prevent task creation overrun
    if (num_tasks == MAX_TASKS) {
        return;
    }

    // Get the bottom of the stack
    uint32_t *sp = (uint32_t*)&task_stacks[num_tasks][MAX_STACK_SIZE];

    // Figure 2-7. Exception Stack Frame
    *(--sp) = 0x01000000;           // xPSR (Thumb bit)
    *(--sp) = (uint32_t)task_entry; // PC
    *(--sp) = 0xFFFFFFFD;           // LR (return to thread, PSP)
    *(--sp) = 0; // R12
    *(--sp) = 0; // R3
    *(--sp) = 0; // R2
    *(--sp) = 0; // R1
    *(--sp) = 0; // R0

    // Initialize R4-R11 to 0
    for (int i = 0; i < 8; i++) {
        *(--sp) = 0;
    }

    tasks[num_tasks].sp = sp;
    tasks[num_tasks].task_id = num_tasks;
    tasks[num_tasks].entry = task_entry; // TODO: implement restart

    num_tasks++;
    return;
}

// Launch first task
__attribute__((naked)) void scheduler_launch(void) {
    asm volatile(
        // Point current_tcb at task 0
        "LDR     R0, =current_tcb\n\t"
        "LDR     R2, [R0]\n\t"       // R2 = current_tcb (already set to &tasks[0])

        // Load its saved SP
        "LDR     SP, [R2]\n\t"        // SP = tasks[0].sp
        "POP     {R4-R11}\n\t"        // Restore R4-R11 from fake frame
        "POP     {R0-R3}\n\t"         // Restore R0-R3
        "POP     {R12}\n\t"           // Restore R12
        "ADD     SP, SP, #4\n\t"      // Skip saved LR
        "POP     {LR}\n\t"            // LR = PC (task entry point) -> branch point
        "ADD     SP, SP, #4\n\t"      // Skip xPSR

        // Switch to PSP
        "MOV     R0, SP\n\t"
        "MSR     PSP, R0\n\t"        // Set PSP to wherever SP is now
        "MRS     R0, CONTROL\n\t"
        "ORR     R0, R0, #2\n\t"      // SPSEL = 1 → use PSP in thread mode
        "MSR     CONTROL, R0\n\t"
        "ISB\n\t"                      // Required after CONTROL write

        "BX      LR\n\t"              // Jump to task entry
    );
}

// Move to next task and load it's task control block
void schedule_next(void) {
    curr_task = (curr_task + 1) % num_tasks;
    next_tcb = &tasks[curr_task];
    return;
}

__attribute__((naked)) void PendSV_Handler(void) {
    asm volatile(
        // Disable interrupts during context switch
        "CPSID   I\n\t"

        // Save current task context
        // R4-R11 are callee-saved, hardware only pushes R0-R3, R12, LR, PC, xPSR
        "MRS     R0, PSP\n\t"
        "STMDB   R0!, {R4-R11}\n\t"

        // current_tcb->sp = PSP (save stack pointer into TCB)
        "LDR     R1, =current_tcb\n\t"
        "LDR     R2, [R1]\n\t"
        "STR     R0, [R2]\n\t"

        // 2.5.7.2 - Exception Return
        // Save EXC_RETURN before calling C function
        // EXC_RETURN = Return to thread mode, use PSP
        "PUSH    {LR}\n\t"
        "BL      schedule_next\n\t"

        // current_tcb = next_tcb
        "LDR     R1, =next_tcb\n\t"
        "LDR     R2, [R1]\n\t"
        "LDR     R1, =current_tcb\n\t"
        "STR     R2, [R1]\n\t"

        // Restore next task context
        // R2 still points to next_tcb, first member is sp
        "LDR     R0, [R2]\n\t"
        "LDMIA   R0!, {R4-R11}\n\t"
        "MSR     PSP, R0\n\t"

        // Restore EXC_RETURN and re-enable interrupts
        // Hardware restores R0-R3, R12, LR, PC, xPSR from PSP on BX LR
        "POP     {LR}\n\t"
        "CPSIE   I\n\t"
        "BX      LR\n\t"
    );
}