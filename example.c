#include <stdio.h>

void add(int a, int b, int* c) {
  int d = a + b;
  c = &d;
}
//
int simple_add(int a, int b) {
 return a + b;
}

int main(int argc, const char** argv) {
//     int num = 0;
//     int num2 = 0;
//     int eleven = 11;
//     num = 1;
//     num2 = num + 1;
//     eleven = num2 + 1;
    int twelve = 1;
    
    twelve = simple_add(twelve, 3);
    
    twelve = simple_add(twelve, twelve);
    
    int output = twelve;
    
    twelve = 5;
    
//     output = eleven;
//     add(0, 1, &output);
    
    output = simple_add(0, 1);
    
//     scanf("%i", &num);
//     printf("%i\n", num - 2);

    return output;
}