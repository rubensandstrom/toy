.SILENT:
build:
	[ -d ./bin ] || mkdir ./bin
	gcc ./src/*.c -Wall -o ./bin/toy

run:
	[ -d ./bin ] || mkdir ./bin
	gcc ./src/*.c -Wall -o ./bin/toy
	./bin/toy ./example/dynamic_array.toy

test1:
	gcc $(filter-out ./src/main.c, $(wildcard ./src/*.c)) ./test/test1.c -o ./test/test
	./test/test
	rm ./test/test

clean:
	rm ./bin/*
