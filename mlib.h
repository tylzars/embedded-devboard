#ifndef MLIB_H
#define MLIB_H

#include <stdint.h>
#include <stdarg.h>

int32_t m_strlen(char* in_str);
void str_reverse(char* in_str);
void m_strcpy(char* src, char* dest);
void m_strcat(char* final, char* to_append);
void itoa(int to_conv, char* post_conv);
void itohs(int32_t in, char* out);
int m_sprintf(char* out, char* fmt, ...);
void to_lower(char *in);
#endif // MLIB_H