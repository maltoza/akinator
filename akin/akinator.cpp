#include "akinator.h"

#define LINE_LEN 100

AKIN_MES akin_rd_recurs(akin_t* akn, FILE* filename, node_t* node, size_t br_ind);
AKIN_MES akin_game_recurs(akin_t* akn, node_t* node);


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
    if (fgetc(file_rd) != EOF) akin_rd_recurs(akn, file_rd, NULL, 0);

    fclose(file_rd);
    return AKIN_MES_OK;
    
}

// заполнение akin дерева
AKIN_MES akin_rd_recurs(akin_t* akn, FILE* filename, node_t* node, size_t br_ind) {
    char c;
    char node_name[LINE_LEN];
    char branch0_name[LINE_LEN];
    char branch1_name[LINE_LEN];
    node_t* temp;
    while ((node_name[0] = fgetc(filename)) != '\"');
    int i;
    for (i = 0; (c = fgetc(filename)) != '\"'; i++) {
        node_name[i] = c;
    }
    node_name[i] = '\0';
    tree_insert(&(akn->tr), node_name, node, br_ind, 0, &temp);
    
    while(isspace(branch0_name[0] = fgetc(filename)));
    if ((branch0_name[0]) == '(') akin_rd_recurs(akn, filename, temp, 0);
    for (i = 1; (c = fgetc(filename)) != ' '; i++) branch0_name[i] = c;
    branch0_name[i] = '\0';
    if (strcmp(branch0_name, "nill") == 0) node->branch_ptr[0] = NULL;

    while(isspace(branch1_name[0] = fgetc(filename)));
    if ((branch1_name[0]) == '(') akin_rd_recurs(akn, filename, temp, 1);
    for (i = 1; (c = fgetc(filename)) != ')'; i++) branch1_name[i] = c;
    branch1_name[i] = '\0';
    if (strcmp(branch0_name, "nill") == 0) node->branch_ptr[1] = NULL;

    return AKIN_MES_OK;
}


AKIN_MES akin_game(akin_t* akn) {
    wprintf(L"Привет! Я акинатор!\n");
    wprintf(L"Хочешь сыграть в игру?[Y/N]\n");
    char c;
    c = toupper(getchar());
    while(c != 'Y' && c != 'N') c = toupper(getchar());
    if (c == 'Y') akin_game_recurs(akn, akn->tr.head);

    wprintf(L"Пока!\n");

    return AKIN_MES_OK;
}

AKIN_MES akin_game_recurs(akin_t* akn, node_t* node) {
    if (node->branch_ptr[0] == NULL && node->branch_ptr[1] == NULL) {
        wchar_t temp[LINE_LEN];
        mbstowcs(temp, &(node->value), LINE_LEN);
        wprintf(L"Это %ls?\n", temp);
    } else {
        wchar_t temp[LINE_LEN];
        mbstowcs(temp, &(node->value), LINE_LEN);
        wprintf(L"%ls?[Y/N]\n", temp);
        char ans = toupper(getchar());
        while(ans != 'Y' && ans != 'N') ans = toupper(getchar());
        if (ans == 'Y') akin_game_recurs(akn, node->branch_ptr[1]);
        else akin_game_recurs(akn, node->branch_ptr[0]);
    }

    return AKIN_MES_OK;
}