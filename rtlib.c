#include <stdio.h>
#include <stdarg.h>
void logop(int* i) {
    printf("Assigned: %i\n",  *i);
}

void LogAssigned(int size, ...) {
  va_list arguements;
  va_start(arguements, size);
  for(int l = size; l > 0; --l) {
    char* test = va_arg(arguements, char *);
    printf("%s current: %i\n", test, *va_arg(arguements, int*));
  }
  if(size > 0) {
    printf("\n");
  }
  va_end(arguements);
}

void LogInitial(int size, ...) {
  va_list arguements;
  va_start(arguements, size);
  for(int l = size; l > 0; --l) {
    char* test = va_arg(arguements, char *);
    printf("%s initial: %i\n", test, *va_arg(arguements, int*));
  }
  va_end(arguements);
}