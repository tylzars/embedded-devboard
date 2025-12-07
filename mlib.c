#include <stdint.h>
#include <stdarg.h>

int32_t m_strlen(char* in_str) {
    int32_t i = 0;
    while (in_str[i] != '\0'){
        i++;
    }
    return i;
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

int m_sprintf(char* out, char* fmt, ...) {
    int32_t fmt_len = m_strlen(fmt);
    int chars_written = 0;

    va_list args;
    va_start(args, fmt);

    for (int i = 0; i < fmt_len; i++) {
        if (fmt[i] == '%') {
            switch (fmt[++i]) {
                case 's': {
                    char *tmp_str = va_arg(args, char*);
                    int tmp_str_len = m_strlen(tmp_str);
                    m_strcat(out, tmp_str);
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
                    char tmp_int_str[20];
                    itoa(va_arg(args, int), tmp_int_str);
                    int tmp_int_str_len = m_strlen(tmp_int_str);
                    m_strcat(out, tmp_int_str);
                    chars_written = chars_written + tmp_int_str_len;
                    break;
                }
                case 'f': {
                    // implement ftoa
                    out[chars_written++] = fmt[i];
                    chars_written++;
                    break;
                }
                case 'x': { // this should also handle X
                    char tmp_hex_str[20];
                    itohs(va_arg(args, int), tmp_hex_str);
                    int tmp_hex_str_len = m_strlen(tmp_hex_str);
                    m_strcat(out, "0x");
                    m_strcat(out, tmp_hex_str);
                    chars_written = chars_written + tmp_hex_str_len + 2;
                    break;
                }
            }
            out[chars_written++] = fmt[i];
            //chars_written++;
        } else {
            out[chars_written++] = fmt[i];
        }
    }

    out[chars_written] = '\0';

    return chars_written;
}