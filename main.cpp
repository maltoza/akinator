#include "akinator.h"

#define LINE_LEN 100

int main() { 
    akin_t akn;
    char filename[LINE_LEN] = "temp.trq";
    printf("Start...\n");

    // ctor акинатора
    akin_ctor(&akn);

    // считывание данных дерева из файла
    akin_rd(&akn, filename);

    // dtor акинатора
    akin_dtor(&akn);
    printf("...End\n");

    return 0;
}