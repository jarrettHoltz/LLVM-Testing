#include <stdio.h>
int main(int argc, const char** argv) {
    int num = 0;
    int num2 = 0;
    num = 1;
    num2 = 2; 
    num = num2;
    num = num2 + num;
    scanf("%i", &num);
    printf("%i\n", num - 2);
    return 0;
}