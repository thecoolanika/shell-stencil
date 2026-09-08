string:
	gcc -Wno-builtin-declaration-mismatch -g -O0 -Iinclude -I. util/string.c -o bin/string.o -c

exec:
	gcc -Wno-builtin-declaration-mismatch -g -O0 -Iinclude -I. src/exec.c -o bin/exec.o -c

input: string
	gcc -Wno-builtin-declaration-mismatch -g -O0 -Iinclude -I. src/input.c -o bin/input.o -c

shell: exec input
	gcc -Wno-builtin-declaration-mismatch -g -O0 -Iinclude -I. bin/string.o bin/exec.o bin/input.o test/shell.c -o bin/shell

readfile: exec input
	gcc -Wno-builtin-declaration-mismatch -g -O0 -Iinclude -I. bin/string.o bin/exec.o bin/input.o test/readfile.c -o bin/readfile

string_test: string
	gcc -Wno-builtin-declaration-mismatch -g -O0 -Iinclude -I. bin/input.o bin/string.o test/test.c -o bin/string_test

clean:
	rm -rf bin/*
