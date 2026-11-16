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
    if ((node_name[0] = fgetc(filename)) != '\"') RETURN_ERROR(AKIN_MES_FILE_ERROR);
    int i;
    for (i = 0; (c = fgetc(filename)) != '\"'; i++) {
        node_name[i] = c;
    }
    node_name[i] = '\0';
    tree_insert(&(akn->tr), node_name, node, br_ind, 0, &temp);
    
    if(fgetc(filename) != ' ') RETURN_ERROR(AKIN_MES_FILE_ERROR);
    if ((branch0_name[0] = fgetc(filename)) == '(') {
        akin_rd_recurs(akn, filename, temp, 0);
        if(fgetc(filename) != ' ') RETURN_ERROR(AKIN_MES_FILE_ERROR);
    } else {
        for (i = 1; (c = fgetc(filename)) != ' '; i++) branch0_name[i] = c;
        branch0_name[i] = '\0';
        if (strcmp(branch0_name, "nil") == 0) temp->branch_ptr[0] = NULL;
        else RETURN_ERROR(AKIN_MES_FILE_ERROR);
    }

    if ((branch1_name[0] = fgetc(filename)) == '(') {
        akin_rd_recurs(akn, filename, temp, 1);
        if(fgetc(filename) != ')') RETURN_ERROR(AKIN_MES_FILE_ERROR);
    } else {
        for (i = 1; (c = fgetc(filename)) != ')'; i++) branch1_name[i] = c;
        branch1_name[i] = '\0';
        if (strcmp(branch1_name, "nil") == 0) temp->branch_ptr[1] = NULL;
    }

    return AKIN_MES_OK;
}

// игра
AKIN_MES akin_game(akin_t* akn) {
    printf("Привет! Я акинатор!\n");
    while (1) {
        printf("Поиграем?[Y/N]\n");
        char c;
        c = toupper(getchar());
        while(c != 'Y' && c != 'N') c = toupper(getchar());
        if (c == 'Y') akin_game_recurs(akn, akn->tr.head);
        else if (c == 'N') break;
    }
    printf("Пока!\n");

    return AKIN_MES_OK;
}

// рекурсивная функция игры
AKIN_MES akin_game_recurs(akin_t* akn, node_t* node) {
    char new_value[LINE_LEN];
    char new_diff[LINE_LEN];
    size_t branch_id;
    node_t* temp;

    if (node->branch_ptr[0] == NULL && node->branch_ptr[1] == NULL) {
        printf("Это %s?\n", &(node->value));
        char ans = toupper(getchar());
        while(ans != 'Y' && ans != 'N') ans = toupper(getchar());
        if (ans == 'Y') printf("Ура! Я отгадал!\n");
        else {
            // обучение
            printf("Я хочу узнать, что ты загадал...\n");
            printf("Что ты загадал?\n");
            scanf("%s", new_value);
            printf("Чем %s отличается от %s?\n", new_value, &(node->value));
            printf("Он: ");
            scanf("%s", new_diff);
            for (int i = 0; i < TREE_BRANCH_COUNT; i++) {
                if (node->root_ptr->branch_ptr[i]->value == node->value) {
                    branch_id = i;
                    break;
                }
            }
            tree_insert(&(akn->tr), new_diff, node->root_ptr, branch_id, 0, &temp);
            tree_insert(&(akn->tr), new_value, temp, 1, 0, &temp);            
        }

    } else {
        printf("%s?[Y/N]\n", &(node->value));
        char ans = toupper(getchar());
        while(ans != 'Y' && ans != 'N') ans = toupper(getchar());
        if (ans == 'Y') akin_game_recurs(akn, node->branch_ptr[1]);
        else akin_game_recurs(akn, node->branch_ptr[0]);
    }

    return AKIN_MES_OK;
}