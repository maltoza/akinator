#include "tree.h"

#ifdef TREE_DEBUG
    #define TREE_ASSERT(tree_ptr) tree_assert((tree_ptr), __FILE__, __FUNCTION__, __LINE__)
#else
    #define TREE_ASSERT(tree_ptr) 
#endif

#define FILENAME_HTML "./tree_log.html"
#define LINE_LEN 100
#define POISON_NODE_ID SIZE_MAX
#define POISON_NODE_VALUE 666

TREE_MES tree_gv_print_node(tree_t* tr, FILE* file_gv, node_t* node);
TREE_MES tree_gv_print_edges(tree_t* tr, FILE* file_gv, node_t* node);
TREE_MES tree_verificate(tree_t* const tr, const char* file_name, const char* func_name, const int line);
void tree_dump(tree_t* tr, TREE_MES res);


TREE_MES tree_assert(tree_t* tr, const char* const file, const char* const func, const int line) {
    TREE_MES result = tree_verificate(tr, file, func, line);
    if (tr->head != NULL) tree_dump(tr, result);
    return TREE_MES_OK;
}

TREE_MES tree_verificate(tree_t* const tr, const char* file_name, const char* func_name, const int line) {
    tr->error.file = file_name;
    tr->error.func = func_name;
    tr->error.line = line;
    
    return TREE_MES_OK;
}


void tree_dump(tree_t* tr, TREE_MES res) {
    char filename_html[LINE_LEN] = FILENAME_HTML;
    char filename_svg[LINE_LEN];
    
    FILE* log_html = fopen(filename_html, "a+");

    fprintf(log_html, "<pre>\n");
    fprintf (log_html, "======================================\n");
    if (res == TREE_MES_OK)
    {
        fprintf (log_html, "            VERIFICATE OK\n");       
    }
    else
    {
        fprintf (log_html, "            VERIFICATE ERROR\n");
    }
    fprintf (log_html, "======================================\n");
    fprintf (log_html, "            INFORMATION:\n");
    fprintf (log_html, "File name:     %s\n", tr->error.file);
    fprintf (log_html, "Function name: %s\n", tr->error.func);
    fprintf (log_html, "Line number:   %d\n", tr->error.line);
    fprintf (log_html, "---------------------------------------\n");
    fprintf (log_html, "    num_elems: %zu\n", tr->num_elems);
    fprintf (log_html, "---------------------------------------\n");

    tree_get_graph(tr, filename_svg);
    if (tr->head == NULL) fprintf (log_html, "Tree is empty\n");
    else fprintf (log_html, "<img src=\"%s\" alt=\"%s\">\n", filename_svg, filename_svg);

    fprintf (log_html, "======================================\n\n\n");
    fprintf(log_html, "</pre>");
    fclose(log_html);
    return;
}



// создание дерева
TREE_MES tree_ctor(tree_t* tr) {
    system("del /Q Graphviz\\*.gv");
    system("del /Q Graphviz\\*.svg");
    remove(FILENAME_HTML);
    mkdir("Graphviz");

    tr->head = NULL;
    tr->num_elems = 0;
    char filename_html[LINE_LEN] = FILENAME_HTML;

    TREE_ASSERT(tr);

    return TREE_MES_OK;
}


// уничтожение дерева
TREE_MES tree_dtor(tree_t* tr) {
    TREE_ASSERT(tr);

    if (tr != NULL && tr->head != NULL) {
        tree_delete(tr, tr->head);
        tr->num_elems = 0;
        tr->head = NULL;
    }

    return TREE_MES_OK;
}

// удаление дерева
TREE_MES tree_delete(tree_t* tr, node_t* node) {
    assert(tr != NULL);
    assert(node != NULL);

    // рекурсивный вызов
    for (size_t i = 0; i < TREE_BRANCH_COUNT; i++) {
        if (node->branch_ptr[i] != NULL) {
            tree_delete(tr, node->branch_ptr[i]);
            node->branch_ptr[i] = NULL;
        }
    }
    // освобождение полей node
    if (node->root_ptr != NULL) {
        for (size_t i = 0; i < TREE_BRANCH_COUNT; i++) {
            if (node->root_ptr->branch_ptr[i] == node) {
                node->root_ptr->branch_ptr[i] = NULL;
            }
        }
    }
    
    node->root_ptr = NULL;
    // освобождение памяти node
    free(node);

    return TREE_MES_OK;
}

/* вставка элемента в дерево
tr - указатель на структуру дерева
val - узел: значение
nd - узел: родитель
br_ind - индекс перемещаемой ветки родителя
to_br_ind - узел: индекс переносимой ветки 
new_node - указатель на адрес нового узла
*/
TREE_MES tree_insert(tree_t* const tr, const node_elem_t* const val, node_t* const nd, size_t br_ind, size_t to_br_ind, node_t** const new_node) {
    TREE_ASSERT(tr);

    node_t* node_temp;
    if (tr->head == NULL) {
        node_temp = (node_t*)calloc(1, sizeof(node_t) + sizeof(char) * strlen(val));
        if (node_temp != NULL) {
            strcpy_s(&(node_temp->value), sizeof(char) * (1 + strlen(val)), val);
            node_temp->root_ptr = NULL;
            for (size_t i = 0; i < TREE_BRANCH_COUNT; i++) node_temp->branch_ptr[i] = NULL;
            tr->head = node_temp;
        } else RETURN_ERROR(TREE_MES_MEM_ALLOCATE);
    } else if (nd == NULL) {
        if (to_br_ind >= TREE_BRANCH_COUNT) RETURN_ERROR(TREE_MES_INVAL_IND);
        node_temp = (node_t*)calloc(1, sizeof(node_t) + sizeof(char) * strlen(val));
        if (node_temp != NULL) {
            strcpy_s(&(node_temp->value), sizeof(char) * (1 + strlen(val)), val);
            node_temp->root_ptr = NULL;
            for (size_t i = 0; i < TREE_BRANCH_COUNT; i++) node_temp->branch_ptr[i] = NULL;
            node_temp->branch_ptr[to_br_ind] = tr->head;
            tr->head->root_ptr = node_temp;
        }
    } else {
        if (br_ind >= TREE_BRANCH_COUNT) RETURN_ERROR(TREE_MES_INVAL_IND);
        if (to_br_ind >= TREE_BRANCH_COUNT) RETURN_ERROR(TREE_MES_INVAL_IND);
        node_temp = (node_t*)calloc(1, sizeof(node_t) + sizeof(char) * strlen(val));
        if (node_temp != NULL) {
            strcpy_s(&(node_temp->value), sizeof(char) * (1 + strlen(val)), val);
            node_temp->root_ptr = nd;
            for (size_t i = 0; i < TREE_BRANCH_COUNT; i++) node_temp->branch_ptr[i] = NULL;
            node_temp->branch_ptr[to_br_ind] = nd->branch_ptr[br_ind];
            nd->branch_ptr[br_ind] = node_temp;
        }
    }

    *new_node = node_temp;
    tr->num_elems += 1;

    TREE_ASSERT(tr);
    return TREE_MES_OK;
}

/*
TREE_MES tree_sort_ins(tree_t* tr, node_elem_t val, node_t* now_node) {

    node_t* test;
    if (tr->head == NULL) {
        tree_insert(tr, val, now_node, NULL, NULL, &test);
    } else if (val >= now_node->value) {
        if (now_node->branch_ptr[1] == NULL) tree_insert(tr, val, now_node, 1, 0, &test);
        else tree_sort_ins(tr, val, now_node->branch_ptr[1]);
    } else { 
        if (now_node->branch_ptr[0] == NULL) tree_insert(tr, val, now_node, 0, 0, &test);
        else tree_sort_ins(tr, val, now_node->branch_ptr[0]);
    }   

    return TREE_MES_OK;
}
*/


TREE_MES tree_get_graph(tree_t* tr, char* filename_img) {
    FILE* file_gv;
    char filename_gv[LINE_LEN] = "./Graphviz/";
    struct timespec time_now;
    struct tm time_info;
    char time_str[LINE_LEN];

    if (tr == NULL) RETURN_ERROR(TREE_MES_INVAL_PTR);
    if (tr->head != NULL) {
        clock_gettime(CLOCK_REALTIME, &time_now);
        localtime_s(&time_info, &time_now.tv_sec);
        size_t res = strftime(time_str, LINE_LEN, "%Y%m%d_%H%M%S", &time_info);
        if (res == 0) RETURN_ERROR(TREE_MES_GET_TIME);

        char sec[LINE_LEN] = {};
        char cmd[LINE_LEN] = {};

        sprintf(sec, "_%05ld", time_now.tv_nsec/10000);
        strcat_s(time_str, sec);


        strcat_s(filename_gv, time_str);
        strcat_s(filename_gv, ".gv");

        strcpy_s(filename_img, LINE_LEN, "./Graphviz/");
        strcat_s(filename_img, LINE_LEN, time_str);
        strcat_s(filename_img, LINE_LEN, ".svg");

        mkdir("Graphviz");
        // построение описание графа для graphviz
        fopen_s(&file_gv, filename_gv, "w");
        fprintf(file_gv, "digraph G {\n");
        fprintf(file_gv, "node [shape=Mrecord, style=filled, fillcolor=lightblue, fontname=\"Arial\", fontsize=10];\n");
        fprintf(file_gv, "edge [color=black];\n");

        // рисование узлов
        tree_gv_print_node(tr, file_gv, tr->head);
        // рисование связей
        tree_gv_print_edges(tr, file_gv, tr->head);

        //fprintf(file_gv, "node%zu -> node%zu;\n", ind_lst_temp - 1, 0);
        fprintf(file_gv, "}\n");

        fclose(file_gv);

        // преобразование описания графа в картинку
        sprintf(cmd, "dot -Tsvg %s -o %s", filename_gv, filename_img);
        system(cmd);
    }

    return TREE_MES_OK;
} 


TREE_MES tree_gv_print_node(tree_t* tr, FILE* file_gv, node_t* node) {
    size_t n = 0;
    for (int i = 0; i < TREE_BRANCH_COUNT; i++) {
        if (node->branch_ptr[i] == NULL) n++;
    }
    if (node == tr->head) {
        fprintf(file_gv, "node%p [label=\"{Node: %p | Value: %s | Root: %p}\", fillcolor=\"%s\"];\n",
            node,
            node,
            &(node->value),
            node->root_ptr,
            "#77E0AE");
    } else if (n == TREE_BRANCH_COUNT) {
        fprintf(file_gv, "node%p [label=\"{Node: %p | Value: %s | Root: %p}\", fillcolor=\"%s\"];\n",
            node,
            node,
            &(node->value),
            node->root_ptr,
            "#FFA688");
    } else {
        fprintf(file_gv, "node%p [label=\"{Node: %p | Value: %s | Root: %p}\", fillcolor=\"%s\"];\n",
            node,
            node,
            &(node->value),
            node->root_ptr,
            "#77C3D9");
    }
    for (size_t i = 0; i < TREE_BRANCH_COUNT; i++) {
        if (node->branch_ptr[i] != NULL) {
            tree_gv_print_node(tr, file_gv, node->branch_ptr[i]);
        }
    }


    return TREE_MES_OK;
}

TREE_MES tree_gv_print_edges(tree_t* tr, FILE* file_gv, node_t* node) {
    for (size_t i = 0; i < TREE_BRANCH_COUNT; i++) {
        if (node->branch_ptr[i] != NULL) {
            fprintf(file_gv, "node%p -> node%p;\n", 
                node, 
                node->branch_ptr[i]);
            tree_gv_print_edges(tr, file_gv, node->branch_ptr[i]);
        }
    }

    return TREE_MES_OK;
}