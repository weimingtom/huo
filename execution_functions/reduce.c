#include "../structures.h"
#include "../execute.h"
#include "../base_util.h"
#include "let_binding.h"
#include "../core_functions.h"

struct Value reduce_array(struct Tree * ast, struct Tree_map * defined, struct Scopes * scopes){
    if (ast->size < 4) {
        ERROR("Not enough arguments for reduce_array: %i < 4\n", ast->size);
    }
    int start = 0;
    struct Value result;
    struct Value array = execute(ast->children[0], defined, scopes);
    if(ast->size == 5){
        result = execute(ast->children[4], defined, scopes);
    } else {
        result = *array.data.array->values[0];
        start = 1;
    }
    for(int i = start; i < array.data.array->size; i++){
        struct Value * item = array.data.array->values[i];
        struct Tree * function = duplicate_tree(ast->children[3]);

        store_let_value(&ast->children[1]->content, &result, scopes);
        store_let_value(&ast->children[2]->content, item, scopes);
        result = execute(function, defined, scopes);
    }
    return result;
}
