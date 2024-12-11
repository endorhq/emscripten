all: a.out.js a.out.debug.js

# Phony because we are working with the compiler generated code
.PHONY: a.out.js
a.out.js: main.c
	../../emcc -O3 -sASYNCIFY $< -o $@

# Phony because we are working with the compiler generated code
.PHONY: a.out.debug.js
a.out.debug.js: main.c
	../../emcc -g -sASYNCIFY -sSOCKET_DEBUG -sSYSCALL_DEBUG -sASYNCIFY_DEBUG=1 $< -o $@

.PHONY: clean
clean:
	rm -f a.out.{,debug}.js a.out.{,debug}wasm
