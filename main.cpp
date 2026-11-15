#include <locale.h>
#include <stdio.h>
#include <windows.h>
#include "akinator.h"

#define LINE_LEN 100

int main() { 
    akin_t akn;
    char filename[LINE_LEN] = "base_mod.trq";

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "Rus");

    printf("Start...\n");

    // ctor акинатора
    akin_ctor(&akn);

    // считывание данных дерева из файла
    akin_rd(&akn, filename);
    
    // игра
    akin_game(&akn);

    // dtor акинатора
    akin_dtor(&akn);
    printf("...End\n");

    return 0;
}