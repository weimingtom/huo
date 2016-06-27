#ifndef _FOR_EACH_H
#define _FOR_EACH_H

#include "../structures.h"

struct Value for_each(struct Tree * ast, struct Tree_map * defined, struct Scopes * scopes);
struct Value for_each_string(struct Value string, struct Tree * ast, struct Tree_map * defined, struct Scopes * scopes);

#endif
