#include "akinator.h"

#define LINE_LEN 100

AKIN_MES akin_rd_recurs(akin_t* akn, FILE* filename);

// ctor акинатора
AKIN_MES akin_ctor(akin_t* akn) {
    // ctor дерева
    tree_ctor(&akn->tr);

    return AKIN_MES_OK;
}

// dtor акинатора
AKIN_MES akin_dtor(akin_t* akn) {
    // dtor дерева
    tree_dtor(&akn->tr);

    return AKIN_MES_OK;
}

// считывание из файла
AKIN_MES akin_rd(akin_t* akn, char* filename) {
    FILE* file_rd;
    file_rd = fopen(filename, "r");

    akin_rd_recurs(akn, file_rd);

    fclose(file_rd);
    return AKIN_MES_OK;
    
}

// заполнение akin дерева
AKIN_MES akin_rd_recurs(akin_t* akn, FILE* filename) {
    char c;
    char node_name[LINE_LEN];
    char branch0_name[LINE_LEN];
    char branch1_name[LINE_LEN];
    c = fgetc(filename);
    int i;
    for (i = 0; (c = fgetc(filename)) != ' '; i++) node_name[i] = c;
    node_name[i] = '\0';
    for (i = 0; (c = fgetc(filename)) != ' '; i++) branch0_name[i] = c;
    branch0_name[i] = '\0';
    for (i = 0; (c = fgetc(filename)) != ')'; i++) branch1_name[i] = c;
    branch1_name[i] = '\0';
    if (strcmp(branch1_name, "nil") != 0) akin_rd_recurs();
    



    return AKIN_MES_OK;
}