#ifndef MARSHALER__H
#define MARSHALER__H

// TODO: errors expand is required

#include "constants.h"
#include "helpers.h"

#include <string.h>

#define __JSON_CALL_MARSHALER(obj_name, field_declarator) \
	err = __JSON_MARSHAL_CB_NAME(obj_name, field_declarator)(obj, dest); \
	if (err != NULL) \
		return err;

#define __JSON_CALL_UNMARSHALER(obj_name, field_declarator) \
	err = __JSON_UNMARSHAL_CB_NAME(obj_name, field_declarator)(data, dest); \
	if (err != NULL) \
		return err;

#define __JSON_DECLARE_MARSHALER(name, ...) \
	const struct json_error *JSON_CONCAT(json_marshal_, name)( \
			const struct __JSON_OBJ_NAME(name) *obj, \
			char **dest) { \
		*dest = NULL; \
		const struct json_error *err = NULL; \
		JSON_FOREACH(__JSON_CALL_MARSHALER, name, __VA_ARGS__) \
		return NULL; \
	}

#define __JSON_DECLARE_UNMARSHALER(name, ...) \
	const struct json_error *JSON_CONCAT(json_marshal_, name)( \
			const char **data, \
			struct __JSON_OBJ_NAME(name) *dest) { \
		memset(dest, 0, sizeof(*dest)); \
		const struct json_error *err = NULL; \
		JSON_FOREACH(__JSON_CALL_UNMARSHALER, name, __VA_ARGS__) \
		return NULL; \
	}

#endif
