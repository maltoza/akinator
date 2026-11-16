#include <locale.h>
#include <stdio.h>
#include <windows.h>
#include "./akin/akinator.h"

#define LINE_LEN 100

int main() { 
    akin_t akn;
    char filename[LINE_LEN] = "ann_temp.trq";

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF8");

    printf("Старт...\n");

    // ctor акинатора
    akin_ctor(&akn);

    // считывание данных дерева из файла
    akin_rd(&akn, filename);
    
    // игра
    akin_game(&akn);

    // dtor акинатора
    akin_dtor(&akn);
    printf("...Финиш\n");

    return 0;
}