#ifndef MACRO__H
#define MACRO__H

#include "args_counter.h"
#include "foreach.h"

#define JSON_CONCAT(arg1, arg2) __JSON_CONCAT_1(arg1, arg2)
#define __JSON_CONCAT_1(arg1, arg2) __JSON_CONCAT_2(arg1, arg2)
#define __JSON_CONCAT_2(arg1, arg2) arg1 ## arg2

#define __JSON_FOREACH_ITER_1(ACTION, X) ACTION(X)

#define __JSON_ARGS_N_HELPER(...) __JSON_ARGS_N(__VA_ARGS__)
#define JSON_ARGS_N(...) __JSON_ARGS_N_HELPER(__VA_ARGS__, __JSON_ARGS_RSEQ_N())

#define __JSON_FOREACH_N(N, ACTION, ...) JSON_CONCAT(__JSON_FOREACH_ITER_, N)(ACTION, __VA_ARGS__)
#define JSON_FOREACH(ACTION, ...) __JSON_FOREACH_N(JSON_ARGS_N(__VA_ARGS__), ACTION, __VA_ARGS__)

#endif
