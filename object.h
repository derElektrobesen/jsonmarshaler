#ifndef OBJECT__H
#define OBJECT__H

#include "helpers.h"
#include "constants.h"
#include "lib.h"
#include "declarators.h"

#define __JSON_GEN_STRUCT_FIELD(object_name, field_declarator) \
	__JSON_FIELD_TYPE(field_declarator) __JSON_FIELD_NAME(field_declarator);

#define __JSON_DECLARE_OBJECT(name, ...) \
	struct __JSON_OBJ_NAME(name) { \
		JSON_FOREACH(__JSON_GEN_STRUCT_FIELD, name, __VA_ARGS__) \
	};

#endif
