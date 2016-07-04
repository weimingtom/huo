#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures/structures.h"
#include "constants.h"
#include "core_functions.h"
#include "build_array.h"
#include "config.h"

void parse(struct Tree * root, struct Tokens *tokens){
    int p_nest = 0;
    while(tokens->counter < tokens->length){
        struct Token token = tokens->tokens[tokens->counter];
        if(token.type == 'o'){
            p_nest += 1;
            struct Tree * tree = malloc_or_die(sizeof(struct Tree));
            tree->type = 'f';
            tree->size = 0;
            tree->children = NULL;

            tokens->counter++;
            parse(tree, tokens);
            RESIZE(root->children, root->size+1);
            root->children[root->size] = tree;
            root->size++;
        }
        else if(is_a_function(token.type)){
            root->type = token.type;
            struct String content =  string_copy_stack(&token.data);
            struct Value val = {
                .type=KEYWORD,
                .data={
                    .str=content
                }
            };
            root->content = val;
        }
        else if(token.type == 'b'){ //open bracket
            struct Tree * value = malloc_or_die(sizeof(struct Tree));
            value->type = 'a'; // a for array
            value->size = 0;
            value->children = NULL;
            struct Value content = {
                .type=ARRAY,
            };
            content.data.array = build_array(tokens);

            value->content = content;
            RESIZE(root->children, root->size+1);
            root->children[root->size] = value;
            root->size++;
        }
        else if(token.type == 'k'){
            // if we are inside a def call this could be name or args
            if(root->type != 'f'){
                // != 'f' means we already set this root node as some kind of function
                struct Tree * value = malloc_or_die(sizeof(struct Tree));
                value->type = token.type;
                value->size = 0;
                value->children = NULL;
                struct String content = string_copy_stack(&token.data);
                struct Value val = {
                    .type=KEYWORD,
                    .data={
                        .str=content
                    }
                };
                value->content = val;

                RESIZE(root->children, root->size+1);
                root->children[root->size] = value;
                root->size++;
            } else {
                root->type = token.type;
                struct String content =  string_copy_stack(&token.data);
                struct Value val = {
                    .type=KEYWORD,
                    .data={
                        .str=content
                    }
                };
                root->content = val;
            }
        }
        else if(token.type == 's'){
            struct Tree * value = malloc_or_die(sizeof(struct Tree));
            value->type = token.type;
            value->size = 0;
            value->children = NULL;
            struct String content =  string_copy_stack(&token.data);
            struct Value val = {
                .type=STRING,
                .data={
                    .str=content
                }
            };
            value->content = val;

            RESIZE(root->children, root->size+1);
            root->children[root->size] = value;
            root->size++;
        }
        else if(token.type == 'n'){
            struct Tree * value = malloc_or_die(sizeof(struct Tree));
            value->type = token.type;
            value->size = 0;
            value->children = NULL;
            struct Value val;
            if(string_contains(dot_const, &token.data)){
                float content = atof(token.data.body);
                val.type=FLOAT;
                val.data.fl=content;
            } else {
                long content = atol(token.data.body);
                val.type=LONG;
                val.data.ln=content;
            }
            value->content = val;

            RESIZE(root->children, root->size+1);
            root->children[root->size] = value;
            root->size++;
        }
        else if(token.type == 'c'){
            //if (p_nest == 0)
            //    return;
            //p_nest -= 1;
           // if (p_nest < 0) {
            //    ERROR("Invalid nesting");
            //}
            return;
        } else if(token.type == 'e'){
            ERROR("Invalid nesting");
        }
        tokens->counter++;
    }
    return;
}