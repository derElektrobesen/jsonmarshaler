#ifndef CONSTANTS__H
#define CONSTANTS__H

#define __JSON_OBJ_NAME(name) name

#define __JSON_UNMARSHAL_CB_NAME(obj_name, field_declarator) \
	__JSON_CB_NAME(JSON_CONCAT(__json_unmarshal_, obj_name), field_declarator)

#define __JSON_MARSHAL_CB_NAME(obj_name, field_declarator) \
	__JSON_CB_NAME(JSON_CONCAT(__json_marshal_, obj_name), field_declarator)

#define __JSON_CB_NAME(prefix, field_declarator) \
	__JSON_CB_NAME_IMPL(JSON_CONCAT(prefix, __), field_declarator)

#define __JSON_CB_NAME_IMPL(prefix, field_declarator) \
	JSON_CONCAT(prefix, __JSON_FIELD_NAME(field_declarator))


#endif
