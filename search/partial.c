/*
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
  0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#define FUNCTION_MARKER 0xaaaaaaaaaaaaaaaa
#define ARG_MARKER      0xbbbbbbbbbbbbbbbb

typedef int(*partial_ptr)(int);
typedef int(*func_ptr)(void *, int);

int
partial_template(int arg) {
	return ((func_ptr) FUNCTION_MARKER)((void *) ARG_MARKER, arg);
} int partial_template_next(int stub) { return stub; }

int
patch_template(partial_ptr func, void *search, void *new) {
	void **dst;

	dst = memmem((void *) func, partial_template_next - partial_template,
		(void *) &search, 8);

	if (!dst) {
		return -1;
	}

	*dst = new;

	return 0;
}

#define patch_function_pointer(func, new) patch_template(func, \
	(void *) FUNCTION_MARKER, (void *) new)
#define patch_arg_pointer(func, new) patch_template(func, \
	(void *) ARG_MARKER, new)

partial_ptr
make_partial(func_ptr f, void *data) {
	size_t len = partial_template_next - partial_template;

	partial_ptr func = (partial_ptr) mmap(0, len, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (!func) {
		return NULL;
	}

	memcpy((void *) func, (void *) partial_template, len);

	if (patch_function_pointer(func, f) == -1 ||
		patch_arg_pointer(func, data) == -1) {

		return NULL;
	}

	mprotect((void *) func, len, PROT_EXEC | PROT_READ);

	return func;
}

int
lal(void *data, int n) {
	printf("%p %d\n", data, n);
	return 0;
}

int
main() {
	make_partial(lal, (void *) 0xc4f3c4f3c4f3c4f3)(42);

	return 0;
}
