#include <stdint.h>

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

    str_reverse(post_conv);
}