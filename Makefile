build:
	[ -d ./bin ] || mkdir ./bin
	gcc ./src/*.c -Wall -o ./bin/toy

test1:

clean:
	rm ./bin/*
