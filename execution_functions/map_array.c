#include "../structures.h"
#include "../execute.h"
#include "../base_util.h"
#include "let_binding.h"

struct Value map_array(struct Tree * ast, struct Tree_map * defined, struct Scopes * scopes){
    if (ast->size < 4) {
        ERROR("Not enough arguments for map_array: %i < 4\n", ast->size);
    }
    struct Value array = execute(ast->children[0], defined, scopes);
    for(int i = 0; i < array.data.array->size; i++){
        struct Value *item = array.data.array->values[i];
        struct Value index = {
            .type = 'l',
            .data = {
                .ln=(long)i
            }
        };
        struct Tree * function = duplicate_tree(ast->children[3]);
        store_let_value(&ast->children[1]->content, item, scopes);
        store_let_value(&ast->children[2]->content, &index, scopes);
        struct Value result = execute(function, defined, scopes);
        array.data.array->values[i] = copy_value_heap(&result);
    }
    return array;
}
