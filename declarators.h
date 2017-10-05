#ifndef DECLARATORS__H
#define DECLARATORS__H

#include "clib.h"

// JSON_STRING declarator
#define __FIELD_TYPE_JSON_STRING(name) char *
#define __FIELD_NAME_JSON_STRING(name) name
#define __MARSHALER_JSON_STRING(name) marshal_string
#define __UNMARSHALER_JSON_STRING(name) unmarshal_string

#endif
