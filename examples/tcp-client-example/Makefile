# Phony because we are working with the compiler generated code
.PHONY: a.out.js
a.out.js: main.c
	../../emcc $< -o $@

.PHONY: clean
clean:
	rm a.out.js a.out.wasm
