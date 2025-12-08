#include <stdint.h>
#include <stdarg.h>

int32_t m_strlen(char* in_str) {
    int32_t i = 0;
    while (in_str[i] != '\0'){
        i++;
    }
    return i;
}

void m_memset(void *s, int c, int32_t n) {
    for (int i = 0; i < n; i++) {
       ((unsigned char*)s)[i] = (unsigned char) c;
    }
}

void str_reverse(char* in_str) {
    int32_t end = m_strlen(in_str) - 1;
    int32_t start = 0;

    while (start != end && start < end) {
        char tmp = in_str[start];
        in_str[start] = in_str[end];
        in_str[end] = tmp;
        start++;
        end--;
    }
}

void m_strcpy(char* src, char* dest) {
    int32_t i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void m_strcat(char* final, char* to_append) {
    int32_t start = m_strlen(final);
    int32_t i = 0;
    // TODO: Replace with strncpy???
    while (to_append[i] != '\0') {
        final[i+start] = to_append[i];
        i++;
    }
    final[start+i] = '\0';
}

void itoa(int32_t to_conv, char* post_conv) {
    int32_t i = 0;

    if (to_conv == 0) {
        post_conv[i++] = '0';
    } else {
        while (to_conv != 0) {
            post_conv[i++] = (to_conv % 10) + '0';
            to_conv = to_conv / 10;
        }
    }

    post_conv[i] = '\0';

    // Because end is the first character added
    str_reverse(post_conv);
}

void itohs(int32_t in, char* out) {
    for (int i = 0; i < 8; i++) {
        // Get current nibble location
        int32_t curr_bits = 4 * (7 - i); 
         // Shift and and to isolate that nibble
        char nibble = (in >> curr_bits) & 0xF;
        // Do conversion
        if (nibble < 10) {
            nibble = nibble + '0';
        } else {
            nibble = nibble + 'A' - 10;
        }
        out[i] = nibble;
    }
    // Null terminate
    out[8] = '\0';
}

void to_lower(char *in) {
    for (int i = 0; i < m_strlen(in); i++) {
        if ('A' <= in[i] && in[i] <= 'Z') {
            in[i] = in[i] + 0x20;
        }
    }
}

void to_upper(char *in) {
    for (int i = 0; i < m_strlen(in); i++) {
        if ('a' <= in[i] && in[i] <= 'z') {
            in[i] = in[i] - 0x20;
        }
    }
}

int m_sprintf(char* out, char* fmt, ...) {
    int32_t fmt_len = m_strlen(fmt);
    int chars_written = 0;                    
    char tmp_str[20];

    va_list args;
    va_start(args, fmt);

    // split on spaces (0(n))
    // find a percent and take until the next space (O(n^2))

    for (int i = 0; i < fmt_len; i++) {
        if (fmt[i] == '%') {
            switch (fmt[++i]) {
                case 's': {
                    char *tmp_str_var = va_arg(args, char*);
                    int tmp_str_len = m_strlen(tmp_str_var);
                    m_strcat(out, tmp_str_var);
                    chars_written = chars_written + tmp_str_len;
                    break;
                }
                case 'c': {
                    char tmp = va_arg(args, int); // no such thing as a char const
                    out[chars_written++] = tmp;
                    chars_written++;
                    break;
                }
                case 'd': {
                    itoa(va_arg(args, int), tmp_str);
                    m_strcat(out, tmp_str);
                    chars_written = chars_written + m_strlen(tmp_str);
                    break;
                }
                case 'f': {
                    out[chars_written++] = fmt[i];
                    chars_written++;
                    break;
                }
                case 'X': {
                    itohs(va_arg(args, int), tmp_str);
                    m_strcat(out, "0x");
                    m_strcat(out, tmp_str);
                    chars_written = chars_written + m_strlen(tmp_str) + 2;
                    break;
                }
                case 'x' :{
                    itohs(va_arg(args, int), tmp_str);
                    to_lower(tmp_str);
                    m_strcat(out, "0x");
                    m_strcat(out, tmp_str);
                    chars_written = chars_written + m_strlen(tmp_str) + 2;
                    break;
                }
            }
        } else {
            out[chars_written++] = fmt[i];
        }
    }

    out[chars_written] = '\0';

    return chars_written;
}