#ifndef _IF_BLOCK_H
#define _IF_BLOCK_H

#include "../structures/structures.h"

struct Value if_block(struct Tree * ast, hash_table *defined, struct Scopes * scopes, int max_depth);

#endif