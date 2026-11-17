#include <locale.h>
#include <stdio.h>
#include <windows.h>
#include "./akin/akinator.h"

#define LINE_LEN 100

int main() { 
    akin_t akn;
    char filename_r[LINE_LEN] = "eng_ann_r.trq";
    char filename_w[LINE_LEN] = "eng_ann_r.trq";

    //SetConsoleCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);
    //setlocale(LC_ALL, "ru_RU.UTF8");

    printf("Start...\n");

    // ctor акинатора
    akin_ctor(&akn);

    // считывание данных дерева из файла
    akin_rd(&akn, filename_r);
    
    // игра
    akin_game(&akn);

    // сохранение дерева
    akin_wr(&akn, filename_w);

    // dtor акинатора
    akin_dtor(&akn);
    printf("...Finish\n");

    return 0;
}