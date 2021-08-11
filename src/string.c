#include "data/string.h"
#include "core.h"

#define MAX_STRING_SIZE 255
string string_create(const char *src)
{
    string result;
    size_t len = strnlen(src, MAX_STRING_SIZE) + 1;
    result.chars = OOM_GUARD(calloc(len, sizeof(char)));
    strncpy(result.chars, src, len-1);
    result.chars[len-1] = 0;
    result.length = len -1;
    return result;
}

void string_free(string *str)
{
    free(str->chars);
    str->chars = NULL;
    str->length = 0;
}