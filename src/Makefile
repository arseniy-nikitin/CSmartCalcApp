CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm

CHECK_SRC=./tests/test_*.check
TEST_SRC=./tests/test_*.c
BD_SRC = ../build/

DIR=./std_calc/  \
		./bank_calc/ \
		./common/
SRC=$(foreach dir,$(DIR),$(wildcard $(dir)*.c))
OBJ=$(patsubst %.c,%.o,$(SRC))

MSG=Minor bug fixes
BRANCH=$(shell git branch --show-current)

OS:=$(shell uname -s)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

.PHONY: test_smart_calc.c smart_calc.a

all:
	make install
	make test
	make run

rebuild:
	make clean
	make uninstall
	make all

install: clean
	mkdir -p $(BD_SRC)
	cd $(BD_SRC) && qmake ../src/smart_calc/smart_calc.pro && make && make clean && rm -rf .qmake.stash Makefile

uninstall:
	rm -rf ../build

dist:
	tar -czvf ../smart_calc.tar ../src

dvi:
	open ./readme.md

run:
ifeq ($(OS), Linux)
	$(OPEN_CMD) $(BD_SRC)smart_calc
else
	$(OPEN_CMD) $(BD_SRC)smart_calc.app
endif

test_smart_calc.c: $(CHECK_SRC)
	checkmk clean_mode=1 $(CHECK_SRC) > ./tests//$@

smart_calc.a: $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	make clean_obj

clean_obj:
	rm -rf $(OBJ)

test: test_smart_calc.c smart_calc.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) ${TEST_SRC} smart_calc.a -o unit_test -lcheck -lm
else
	$(CC) $(CFLAGS) ${TEST_SRC} smart_calc.a -o unit_test -lcheck $(LINUX_FLAGS)
endif
	./unit_test

clean_test:
	rm -rf unit_test

# If lcov cause errors add "--filter range" after --no-external flag, works only in MAC
gcov_report: test
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o gcov_test -lcheck -lm
else
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o gcov_test -lcheck $(LINUX_FLAGS)
endif
	./gcov_test
	lcov -t "stest" -o s21_test.info --no-external -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

clean_gcov:
	rm -rf *.gcda *.gcno *.info report gcov_test

#cppcheck --enable=all --suppress=missingIncludeSystem ${SRC}
style:
	clang-format --style=Google -n */*.c */*.cpp */*.h *.h

clean:
	make clean_obj
	make clean_test
	make clean_gcov
	rm -rf *.a *.dSYM ./tests/test_*.c
	rm -rf ./build-smart_calc*

push:
ifeq ($(BRANCH), develop)
	git add $(DIR) 
else
	git add $(BRANCH)
endif
	git add Makefile tests smart_calc.h readme.md
	git commit -m "$(BRANCH): $(MSG)"
	git push origin $(BRANCH)