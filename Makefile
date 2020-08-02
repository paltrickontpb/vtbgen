.PHONY: all
all: checkbuild
	g++ *.cpp -o ./build/main.o
	@echo "Build complete"

checkbuild:
	@if [ -d "build" ]; then \
		echo "Build directory already exists"; \
	else \
		echo "Making Build directory"; \
		mkdir build; \
	fi

test:
	@if [ -d "test" ]; then \
		echo "Test directory already exists"; \
	else \
		echo "Making test directory"; \
		mkdir test; \
	fi 
	cp dff.v ./test/dff.v
	cp ./build/main.o ./test/main.o
	./test/main.o ./test/dff.v

clean:
	rm -rf ./build
	rm -rf ./test
	@echo "Cleaning complete"