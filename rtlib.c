#include <stdio.h>
// #include <string>
void logop(int* i) {
    printf("Assigned: %i\n",  *i);
}

void LogAssigned(char* i, int* j, int* size) {
    for(int l = 0; l < *size; --l) {
      printf("Name: %s Current Value %i\n", i, j[l]);
    }
}

void LogInitial(char* i, int* j) {
    printf("Name: %s Previous Value %i\n", i, *j);
}