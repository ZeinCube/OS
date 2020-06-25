#include <stdio.h>
#include <stdint.h>

#define mask64  0b0010000000100000001000000010000000100000001000000010000000100000
#define mask32  0b00100000001000000010000000100000
#define mask16  0b0010000000100000
#define mask8  0b00100000

short isLetter(const char *str) {
    if (((int) str >= 65 && (int) str <= 90) || ((int) str >= 97 && (int) str <= 122)) {
        return 1;
    }
    return 0;
}

void changeCase(char *str, size_t n) {
    size_t length = n;
    str += n;
    while (length >= 8) {
        *((uint64_t *) (str - length)) ^= mask64;
        length -= 8;
    }
    while (length >= 4) {
        *((uint32_t *) (str - length)) ^= mask32;
        length -= 4;
    }
    while (length >= 2) {
        *((uint32_t *) (str - length)) ^= mask16;
        length -= 2;
    }
    while (length != 0) {
        *(str - length) ^= mask8;
        --length;
    }

    for (int i = n; i > 0; --i){
        if (!isLetter((const char *) *(str - i))){
            *(str - i) ^= 1 << 5;
        }
    }
}

int main() {
    char string[] = "23456789chvg8BJHJGFGDcvb^%njkNBVHGFfcVBNKjhCG$%^&^%$#$^%$#@$%^%$%^bjYFVbnkl   iH5GvbjkgIUYFvug\0";
    printf("test:   %s\n", string);
    changeCase(string, sizeof(string)-1);
    printf("answer: %s\n", string);
}
