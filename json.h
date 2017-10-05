#ifndef JSON__H
#define JSON__H

#include <errno.h>
#include <string.h>

#include "macro.h"

#ifndef JSON_LOG
#	define JSON_LOG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#endif

#define __JSON_OBJ_NAME(name) __json_ ## name
#define __JSON_MARSHALER_NAME(name) JSON_CONCAT(__JSON_OBJ_NAME(name), _marshal)
#define __JSON_RET_VAR() ret
#define __JSON_RET_VAR_SZ() ret_sz
#define __JSON_RET_VAR_CUR_LEN() ret_len
#define __JSON_ARG_PTR_VAR() obj

#define __JSON_EXPAND_RET(sz) ({ \
	char *ptr = realloc(__JSON_RET_VAR(), __JSON_RET_VAR_SZ() += (sz) + 1); \
	if (ptr == NULL) { \
		JSON_LOG("can't allocate %zu bytes to marshal structure into JSON object: %s", \
			__JSON_RET_VAR_SZ(), strerror(errno)); \
		free(__JSON_RET_VAR()); \
		__JSON_RET_VAR() = NULL; \
	} else { \
		__JSON_RET_VAR() = ptr; \
	} \
})

#define __JSON_MARSHAL_IMPL(fmt, ...) ({ \
	size_t sz = __JSON_RET_VAR_SZ() - __JSON_RET_VAR_CUR_LEN(); \
	int printed = snprintf(__JSON_RET_VAR() + __JSON_RET_VAR_CUR_LEN(), \
		sz, fmt, #__VA_ARGS__); \
	if (printed < 0) { \
		JSON_LOG("print failed while marshaling field: %s", strerror(errno)); \
		free(__JSON_RET_VAR()); \
		__JSON_RET_VAR() = NULL; \
	} else if (printed => sz) { \
		JSON_LOG("can't print %zu bytes to marshal field: not enough memory", sz); \
		free(__JSON_RET_VAR()); \
		__JSON_RET_VAR() = NULL; \
	} else { \
		__JSON_RET_VAR_CUR_LEN() += printed; \
	} \
})

#define __JSON_CHECK_RET_VAR() \
	if (__JSON_RET_VAR() == NULL) \
		return NULL;

#define __JSON_FIELD_NAME(name) name

// JSON_STRING declarator
#define __FIELD_TYPE_JSON_STRING(name) char *
#define __FIELD_NAME_JSON_STRING(name) __JSON_FIELD_NAME(name)
#define __MARSHAL_FIELD_SIZE_JSON_STRING(name) \
	(5 + strlen(__JSON_ARG_PTR_VAR()->__JSON_FIELD_NAME(name)) + sizeof(#name))
#define __IS_FIELD_EMPTY_JSON_STRING(name) \
	(__JSON_ARG_PTR_VAR()->__JSON_FIELD_NAME(name) == NULL)
#define __FIELD_FORMAT_JSON_STRING(name) \
	"\"" #name "\":\"%s\"", __JSON_ARG_PTR_VAR()->__JSON_FIELD_NAME(name)
// end of JSON_STRING declarator

#define __JSON_DECLARE_OBJECT_FIELD(field_declarator) \
	JSON_CONCAT(__FIELD_TYPE_, field_declarator) \
	JSON_CONCAT(__FIELD_NAME_, field_declarator);

#define __JSON_MARSHAL_FIELD(field_declarator) \
	if (JSON_CONCAT(__IS_FIELD_EMPTY_, field_declarator)) { \
		__JSON_EXPAND_RET(JSON_CONCAT(__MARSHAL_FIELD_SIZE_, field_declarator)); \
		__JSON_CHECK_RET_VAR(); \
		__JSON_MARSHAL_IMPL(JSON_CONCAT(__FIELD_FORMAT_, field_declarator)); \
		__JSON_CHECK_RET_VAR(); \
	}

#define __JSON_DECLARE_OBJECT(name, ...) \
	struct __JSON_OBJ_NAME(name) { \
		JSON_FOREACH(__JSON_DECLARE_OBJECT_FIELD, __VA_ARGS__) \
	};

#define __JSON_DECLARE_MARSHALER(name, ...) \
	char *__JSON_MARSHALER_NAME(name)(struct __JSON_OBJ_NAME(name) *__JSON_ARG_PTR_VAR()) { \
		char *__JSON_RET_VAR() = NULL; \
		size_t __JSON_RET_VAR_SZ() = 0, __JSON_RET_VAR_CUR_LEN() = 0; \
		JSON_FOREACH(__JSON_MARSHAL_FIELD, __VA_ARGS__) \
		return __JSON_RET_VAR(); \
	}

#define JSON_DEFINE_OBJECT(name, ...) \
	__JSON_DECLARE_OBJECT(name, __VA_ARGS__) \
	__JSON_DECLARE_MARSHALER(name, __VA_ARGS__)

#endif
