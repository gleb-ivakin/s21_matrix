CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    CHECK=-lcheck
else
    CHECK=-lcheck -lm -lsubunit -lrt -lpthread
endif

all: gcov_report

clean:
	rm -rf *.g* report.* *.out* *.o ./report s21_matrix.a *.txt *.cfg

s21_matrix.a:
	$(CC) -c s21_matrix.c -o s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

test: clean s21_matrix.a
	$(CC) $(CFLAGS) -g test.c s21_matrix.a -o test.out $(CHECK)
	./test.out

gcov_report: clean
	$(CC) $(CFLAGS) --coverage -c s21_matrix.c -o s21_matrix.o
	$(CC) $(CFLAGS) --coverage test.c s21_matrix.o $(CHECK)
	./a.out
	gcov -b -l -p -c s21_matrix.gcno; gcovr -g -k -r . --html --html-details -o report.html

git: clean
	git status
	git add .
	git commit -m "$m"
	git push origin develop

go:
	git stash
	git pull origin develop

check:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c test.c s21_matrix.c s21_matrix.h

valgrind: test
	valgrind -q -s --leak-check=full --trace-children=yes --track-origins=yes --log-file=RESULT_VALGRIND.txt ./test.out
	cat RESULT_VALGRIND.txt
