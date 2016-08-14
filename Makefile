
CC=gcc
PROD_CFLAGS=-I. -Wall
TEST_LIBS=-lcheck -lm -lpthread -lrt
SRC=src
TEST=tests
TEST_CFLAGS=-I$(SRC) -g -Wall
TARGET=target
PROD_TARGET=$(TARGET)
TEST_TARGET=$(TARGET)/$(TEST)
HEADERS=$(SRC)/binary_parser.h $(SRC)/roman_arithmetic.h
PROD_OBJECTS=$(PROD_TARGET)/binary_parser.o $(PROD_TARGET)/roman_arithmetic.o $(PROD_TARGET)/converters.o
PROD_MAIN_OBJECT=$(PROD_TARGET)/main.o
TEST_EXECS=$(TEST_TARGET)/story_tests $(TEST_TARGET)/binary_parser_test $(TEST_TARGET)/roman_arithmetic_test $(TEST_TARGET)/converters_test
	
.PHONY: prod test all

$(TEST_TARGET):
	mkdir -p $(TEST_TARGET)
	
$(PROD_TARGET):
	mkdir -p $(PROD_TARGET)

$(PROD_TARGET)/%.o: $(SRC)/%.c $(PROD_TARGET) $(HEADERS)
	$(CC) -c -o $@ $< $(PROD_CFLAGS)

$(TEST_TARGET)/%.o: $(TEST_TARGET)/%.c $(PROD_TARGET) $(TEST_TARGET) $(HEADERS)
	$(CC) -c -o $@ $< $(TEST_CFLAGS)

$(TEST_TARGET)/%.c: $(TEST)/%.check $(TEST_TARGET) $(HEADERS)
	checkmk $< > $@
	cp $@ /tmp

prod: $(PROD_OBJECTS) $(PROD_MAIN_OBJECT)
	$(CC) -o $(PROD_TARGET)/falconkata $^

$(TEST_TARGET)/%: $(TEST_TARGET)/%.o prod
	$(CC) -o $@ $< $(PROD_OBJECTS) $(TEST_LIBS)

test: $(PROD_OBJECTS) $(TEST_EXECS)

all: prod test

