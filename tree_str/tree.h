#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <dir.h>

#include "../error.h"

#define TREE_BRANCH_COUNT 2


enum TREE_MES {
    TREE_MES_OK = 0,
    TREE_MES_MEM_ALLOCATE,
    TREE_MES_GET_TIME,
    TREE_MES_INVAL_IND,
    TREE_MES_INVAL_PTR,
};


typedef char node_elem_t;

struct tree_err_t
{
    const char* file;   // имя файла
    const char* func;   // имя функции
    int line;           // номер линии
};

// один элемент
struct node_t {
    node_t* root_ptr;                         // корень
    node_t* branch_ptr[TREE_BRANCH_COUNT];    // левая и правая ветка
    node_elem_t value;                        // значение текущего элемента
};

struct tree_t {
    size_t num_elems;        // количество элементов в списке 
    node_t* head;            // указатель на голову дерева
    tree_err_t error;        // структура ошибки
};

TREE_MES tree_ctor(tree_t* tr);
TREE_MES tree_dtor(tree_t* tr);
TREE_MES tree_insert(tree_t* const tr, const node_elem_t* const val, node_t* const nd, size_t br_ind, size_t to_br_ind, node_t** const new_node);
//TREE_MES tree_sort_ins(tree_t* tr, node_elem_t val, node_t* now_node);
TREE_MES tree_delete(tree_t* tr, node_t* node);
TREE_MES tree_get_graph(tree_t* tr, char* filename_png);

#endif // TREE_H