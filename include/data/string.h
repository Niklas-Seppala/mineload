#if !defined(STRING_H)
#define STRING_H
#include <string.h>
#include "core.h"
#include "data/contants.h"

struct string
{
    char *chars;
    size_t length;
};
typedef struct string string_t;
#define string string_t

string string_create(const char *src);
void string_free(string *str);

#endif // STRING_H
