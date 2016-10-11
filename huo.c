#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <malloc.h>
#include "tokenizer.h"
#include "parser.h"
#include "structures.h"
#include "execute.h"
#include "store_defs.h"
#include "base_util.h"

int main(int argc, char const *argv[]) {
#ifdef __MINGW32__
	extern void ptw32_processInitialize(void);
	ptw32_processInitialize();
	//ptw32_processTerminate();
#endif
	if(argc < 2){
        printf("Error: you have run Huo without pointing it to a file.\n");
        return 0;
    }
     
    FILE *fp;
    fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("Error: %d (%s)\n", errno, strerror(errno));
        return 0;
    }

    struct Tokens *pt;
    pt = (struct Tokens *)malloc(sizeof(struct Tokens));
    pt->length = 0;
    pt->counter = 0;
    struct String *pfile;
    pfile = (struct String*)malloc(sizeof(struct String));
    pfile->length = 0;

    char c;
    while ((c = fgetc(fp)) != EOF){
        pfile->body[pfile->length] = c;
        pfile->length++;
    }
    fclose(fp);
    struct Tokens * tokens = tokenize(pfile, pt);
    // for(int i = 0; i < tokens->length; i++){
    //     printf("%c", tokens->tokens[i].type);
    // }
    struct Tree root;
    root.type = 'r';
    root.size = 0;
    parse(&root, tokens);
    // this prints the AST for reference
    // printTree(&root);
    // printf("\n");
    struct Tree_map * defined = malloc(sizeof(struct Tree_map));
    struct Map * let_map = malloc(sizeof(struct Map));
    int num_defs = store_defs(&root, defined);
    for(int i = num_defs; i < root.size; i++){
        execute(root.children[i], defined, let_map);
    }
    return 0;
}
