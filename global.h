#ifndef global
#define global

// Boolean
#define bool uint8_t
#define false 0
#define true 1

// Bit Manipulation Macros
#define TOGGLE_BIT(reg, bit) ((reg) ^= (bit))
#define UNSET_BIT(reg, bit)  ((reg) &= (~bit))
#define SET_BIT(reg, bit)    ((reg) |= (bit))

#endif