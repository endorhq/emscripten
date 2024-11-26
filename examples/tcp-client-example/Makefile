# Phony because we are working with the compiler generated code
.PHONY: a.out.js
a.out.js: main.c
	../../emcc -g $< -o $@

.PHONY: clean
clean:
	rm -f a.out.js a.out.wasm
