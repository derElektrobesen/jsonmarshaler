#ifndef CLIB__H
#define CLIB__H

const struct json_error *marshal_string(const char *field_name, const char *data, char **dest) {}
const struct json_error *unmarshal_string(const char *field_name, const char *data, char **dest) {}

#endif
