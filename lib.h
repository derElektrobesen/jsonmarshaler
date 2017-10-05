#ifndef LIB__H
#define LIB__H

#define __JSON_FIELD_NAME(field_declarator) \
	JSON_CONCAT(__FIELD_NAME_, field_declarator)

#define __JSON_FIELD_TYPE(field_declarator) \
	JSON_CONCAT(__FIELD_TYPE_, field_declarator)

#define __JSON_FIELD_STR_NAME_IMPL_2(name) #name
#define __JSON_FIELD_STR_NAME_IMPL(name) __JSON_FIELD_STR_NAME_IMPL_2(name)

#define __JSON_FIELD_STR_NAME(field_declarator) \
	__JSON_FIELD_STR_NAME_IMPL(__JSON_FIELD_NAME(field_declarator))

#endif
