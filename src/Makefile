CC=gcc -std=c11 -D_GNU_SOURCE
TST_LIBS=-lcheck -lm -lpthread 
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=s21_math.c
H=s21_math.h
LIBO=s21_math.o
LIBA=s21_math.a
EXE=test.out

all: s21_math.a test gcov_report

clean:
	rm -rf *.a && rm -rf *.o
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov
	rm -rf report/ && rm -rf *.out

test: s21_math.a
	$(CC) test.c -L. $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)

rebuild: clean all

s21_math.a: clean
	$(CC) -c $(SOURCES) -o $(BUILD_PATH)$(LIBO)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: s21_math.a
	$(CC) $(GCOV_LIBS) test.c $(SOURCES) $(LIBA) -L. $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)
	lcov -t "test" -c -d $(BUILD_PATH) --output-file $(BUILD_PATH)coverage.info
	genhtml $(BUILD_PATH)coverage.info --output-directory $(BUILD_PATH)report/

check:
	@echo
	@echo ===CPPCHECK===
	@echo
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@echo
	@echo ===STYLE TEST===
	@echo
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	@echo
	@echo ===LEAKS TEST===
	@echo
	CK_FORK=no leaks -atExit -- $(BUILD_PATH)$(EXE)
