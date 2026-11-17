#ifndef AKINATOR_H
#define AKINATOR_H

#include "ctype.h"
#include "../error.h"
#include "../tree_str/tree.h"


// сообщения акинатора
enum AKIN_MES {
    AKIN_MES_OK,
    AKIN_MES_FILE_ERROR,
};

// структура акинатора
struct akin_t {
    tree_t tr;      // дерево

};

AKIN_MES akin_ctor(akin_t* akn);
AKIN_MES akin_dtor(akin_t* akn);
AKIN_MES akin_rd(akin_t* akn, char* filename);
AKIN_MES akin_game(akin_t* akn);
AKIN_MES akin_wr(akin_t* akn, char* filename);

#endif // AKINATOR_H