#include <string.h>

int lengthOfLongestSubstring(char * s){
    int len = strlen(s);
    int start = 0;
    int end = 0;
    int max_len = 0;
    int char_set[128] = {0};
    while (end < len) {
        if (char_set[s[end]] == 0) {
            char_set[s[end]] = 1;
            end++;
            if (end - start > max_len) {
                max_len = end - start;
            }
        } else {
            char_set[s[start]] = 0;
            start++;
        }
    }
    return max_len;
}