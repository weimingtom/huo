#ifndef _MAP_ARRAY_H
#define _MAP_ARRAY_H

#include "../structures/structures.h"

struct Value map_array(struct Tree * ast, hash_table *defined, struct Scopes * scopes, int max_depth);

#endif