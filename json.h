#ifndef JSON__H
#define JSON__H

#include "helpers.h"
#include "constants.h"
#include "lib.h"
#include "declarators.h"

#include "object.h"
#include "callbacks.h"
#include "marshaler.h"

struct json_error;

#define JSON_DEFINE_OBJECT(name, ...) \
	__JSON_DECLARE_OBJECT(name, __VA_ARGS__) \
	__JSON_DECLARE_CALLBACKS(name, __VA_ARGS__) \
	__JSON_DECLARE_MARSHALER(name, __VA_ARGS__) \
	__JSON_DECLARE_UNMARSHALER(name, __VA_ARGS__)

#endif
