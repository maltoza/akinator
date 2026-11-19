#include <locale.h>
#include <stdio.h>
#include <windows.h>
#include "./akin/akinator.h"

#define LINE_LEN 100

int main() { 
    akin_t akn;
    char filename_r[LINE_LEN] = "eng_ann_r.trq";
    char filename_w[LINE_LEN] = "eng_ann_r.trq";
    char word[LINE_LEN] = {};
    node_t* res;
    //SetConsoleCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);
    //setlocale(LC_ALL, "ru_RU.UTF8");

    printf("Start...\n");

    // ctor акинатора
    akin_ctor(&akn);

    // считывание данных дерева из файла
    akin_rd(&akn, filename_r);
    
    while (1) {
        printf("What do you want to do?\n");
        printf("Play game[G], get defenition of word[D], compare two words[C], exit[E]\n");
        char c;
        c = toupper(getchar());
        while(c != 'G' && c != 'D' && c != 'C' && c != 'E') c = toupper(getchar());
        switch (c) {
            case 'G':
                // игра
                akin_game(&akn);
                break;
            case 'D':
                // определение слова
                akin_get_definition(&akn);
                break;
            case 'C':
                // сравнение двух слов
                akin_compare_words(&akn);
                break;
            case 'E':
                break;
            default:
                break;
        }
        if (c == 'E') break;
    }

    // сохранение дерева
    akin_wr(&akn, filename_w);

    // dtor акинатора
    akin_dtor(&akn);
    printf("...Finish\n");

    return 0;
}