CC=gcc
FLAGS=-Wall -Werror -Wextra

all: 	cpp s21_cat test

clean:
	rm s21_cat

s21_cat: s21_cat.c
	$(CC) $(FLAGS) -std=c11 s21_cat.c -o s21_cat

test: test_cat.sh
	chmod 771 ./test_cat.sh
	./test_cat.sh
	rm *.txt

git: s21_cat.c
	git add s21_cat.c
	git commit -m new
	git push origin nahasape

cpp: s21_cat.c s21_cat.h
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm CPPLINT.cfg
	cppcheck *.c *.h

