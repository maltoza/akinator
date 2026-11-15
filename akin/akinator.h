#ifndef AKINATOR_H
#define AKINATOR_H

#include "ctype.h"
#include "../error.h"
#include "tree.h"


// сообщения акинатора
enum AKIN_MES {
    AKIN_MES_OK,
};

// структура акинатора
struct akin_t {
    tree_t tr;      // дерево

};

AKIN_MES akin_ctor(akin_t* akn);
AKIN_MES akin_dtor(akin_t* akn);
AKIN_MES akin_rd(akin_t* akn, char* filename);
AKIN_MES akin_game(akin_t* akn);

#endif // AKINATOR_H