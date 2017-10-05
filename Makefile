MAX_ARGS = 100

GENERATED_FILES = \
	args_counter.h \
	foreach.h

all: generate
	cc main.c -o main.out.c -E

generate: $(GENERATED_FILES)

args_counter.h:
	echo '#define __JSON_ARGS_RSEQ_N() \\' > $@
	seq $(MAX_ARGS) 1 | awk '{print "\t" $$1 ", \\"}' >> $@
	echo "\t0\n" >> $@
	echo '#define __JSON_ARGS_N(\\' >> $@
	seq 1 $(MAX_ARGS) | awk '{print "\t_" $$1 ", \\"}' >> $@
	echo "\tN, ...) N" >> $@

foreach.h:
	seq 2 $(MAX_ARGS) | xargs -I{} bash -c '\
		echo "#define __JSON_FOREACH_ITER_{}(ACTION, ARG, X, ...) \\" >> $@;\
		echo -e "\tACTION(ARG, X) \\" >> $@;\
		echo -e "\t__JSON_FOREACH_ITER_$$(({}-1))(ACTION, ARG, __VA_ARGS__)" >> $@;\
		echo >> $@'

clean:
	rm -f $(GENERATED_FILES)

.PHONY: all generate generate_args_counter
