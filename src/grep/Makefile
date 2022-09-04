CC=gcc
FLAGS=-Wall -Werror -Wextra

all: cpp s21_grep test

clean:
	rm s21_grep

test:
	chmod 771 ./test_grep.sh
	./test_grep.sh

s21_grep: s21_grep.c
	$(CC) $(FLAGS) -std=c11 s21_grep.c -o s21_grep

git: s21_grep.c
	git add s21_grep.c
	git commit -m new
	git push origin nahasape

cpp: s21_grep.c s21_grep.h
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm CPPLINT.cfg
	cppcheck *.c *.h

