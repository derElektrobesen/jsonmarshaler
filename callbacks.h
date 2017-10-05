#ifndef CALLBACKS__H
#define CALLBACKS__H

#include "helpers.h"
#include "constants.h"
#include "lib.h"
#include "declarators.h"

#define __JSON_FIELD_GETTER_CB_TYPE_NAME(name) \
	JSON_CONCAT(__JSON_OBJ_NAME(name), __field_getter)

#define __JSON_FIELD_SETTER_CB_TYPE_NAME(name) \
	JSON_CONCAT(__JSON_OBJ_NAME(name), __field_setter)

#define __JSON_FIELD_MARSHALER(field_declarator) \
	JSON_CONCAT(__MARSHALER_, field_declarator)

#define __JSON_FIELD_UNMARSHALER(field_declarator) \
	JSON_CONCAT(__UNMARSHALER_, field_declarator)

#define __JSON_DECLARE_CALLBACKS_TYPES(name) \
	typedef const struct json_error *(*__JSON_FIELD_GETTER_CB_TYPE_NAME(name)) \
		(const struct __JSON_OBJ_NAME(name) *obj, char **dest); \
	typedef const struct json_error *(*__JSON_FIELD_SETTER_CB_TYPE_NAME(name)) \
		(const char *data, struct __JSON_OBJ_NAME(name) *dest);

#define __JSON_GEN_MARSHAL_CALLBACK(obj_name, field_declarator) \
	static const struct json_error *__JSON_MARSHAL_CB_NAME(obj_name, field_declarator) \
		(const struct __JSON_OBJ_NAME(obj_name) *obj, char **dest) { \
		return __JSON_FIELD_MARSHALER(field_declarator)( \
			__JSON_FIELD_STR_NAME(field_declarator), \
			obj->__JSON_FIELD_NAME(field_declarator), dest); \
	}

#define __JSON_GEN_UNMARSHAL_CALLBACK(obj_name, field_declarator) \
	static const struct json_error *__JSON_UNMARSHAL_CB_NAME(obj_name, field_declarator) \
		(const char *data, struct __JSON_OBJ_NAME(obj_name) *dest) { \
		return __JSON_FIELD_UNMARSHALER(field_declarator)( \
			__JSON_FIELD_STR_NAME(field_declarator), \
			data, &dest->__JSON_FIELD_NAME(field_declarator)); \
	}

#define __JSON_DECLARE_CALLBACKS_IMPL(name, ...) \
	JSON_FOREACH(__JSON_GEN_MARSHAL_CALLBACK, name, __VA_ARGS__) \
	JSON_FOREACH(__JSON_GEN_UNMARSHAL_CALLBACK, name, __VA_ARGS__)

#define __JSON_DECLARE_CALLBACKS(name, ...) \
	__JSON_DECLARE_CALLBACKS_TYPES(name) \
	__JSON_DECLARE_CALLBACKS_IMPL(name, __VA_ARGS__) \

#endif
