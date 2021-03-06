#include "structures/structures.h"
#include "constants.h"
#include "base_util.h"
#include "config.h"

const huo_depth_t RECURSE_MAX = 250;
const huo_int_t LOOP_MAX = -1;

struct String functions = STR_NEW("*+-/!=<>|&");

struct String numbers = STR_NEW("-0123456789");

struct String letters = STR_NEW("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

struct String print_const = STR_NEW("print");

struct String concat_const = STR_NEW("cat");

struct String if_const = STR_NEW("if");

struct String def_const = STR_NEW("def");

struct String let_const = STR_NEW("let");

struct String length_const = STR_NEW("length");

struct String index_const = STR_NEW("index");

struct String push_const = STR_NEW("push");

struct String each_const = STR_NEW("each");

struct String map_const = STR_NEW("map");

struct String reduce_const = STR_NEW("reduce");

struct String set_const = STR_NEW("set");

struct String for_const = STR_NEW("for");

struct String do_const = STR_NEW("do");

struct String read_file_const = STR_NEW("read");

struct String import_const = STR_NEW("import");

struct String substring_const = STR_NEW("substring");

struct String split_const = STR_NEW("split");

struct String return_const = STR_NEW("return");

struct String parallel_const = STR_NEW("parallel");

struct String switch_const = STR_NEW("switch");

struct String default_const = STR_NEW("default");

struct String while_const = STR_NEW("while");

struct String eval_const = STR_NEW("eval");

struct String read_line_const = STR_NEW("readline");

struct String false_const = STR_NEW("false");

struct String true_const = STR_NEW("true");

struct String typeof_const = STR_NEW("typeof");

struct String function_names = STR_NEW("[if, read, let, set, each, for, do, switch, parallel, import, map, reduce, substring, while]");

struct String keyword_const = STR_NEW("keyword");
struct String number_const = STR_NEW("number");
struct String string_const = STR_NEW("string");
struct String boolean_const = STR_NEW("boolean");
struct String array_const = STR_NEW("array");
struct String undefined_const = STR_NEW("undefined");

const char open_parens_const = '(';
const char close_parens_const = ')';
const char root_type_const = 'r';
const char quote_const = '"';
const char bracket_const = '[';
const char end_bracket_const = ']';
const char dot_const = '.';

bool is_a_open_parens(char ch){ return ch == open_parens_const; }
bool is_a_close_parens(char ch){ return ch == close_parens_const; }
bool is_a_root_type(char ch){ return ch == root_type_const; }
bool is_a_quote(char ch){ return ch == quote_const; }
bool is_a_bracket(char ch){ return ch == bracket_const; }
bool is_a_end_bracket(char ch){ return ch == end_bracket_const; }

bool is_a_function(char ch){
  return string_contains(ch, &functions);
}
