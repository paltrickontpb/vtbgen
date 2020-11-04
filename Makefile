.PHONY: all test
all: checkbuild
	g++ *.cpp -o ./build/vtbgen
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
	@cp ./verilogtest/dff.v ./test/dff.v
	@cp ./verilogtest/spi_slave.v ./test/spi_slave.v
	@cp ./build/vtbgen ./test/vtbgen
	./test/vtbgen ./test/dff.v
	@mv dff_tb.v test/dff_tb.v
	
clean:
	rm -rf ./build
	rm -rf ./test
	@echo "Cleaning complete"