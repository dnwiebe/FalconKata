
CC=gcc
CFLAGS=-I. -Wall
TEST_LIBS=-lcheck -lm -lpthread -lrt
SRC=src
TEST=tests
TARGET=target
PROD_TARGET=$(TARGET)
TEST_TARGET=$(TARGET)/$(TEST)
HEADERS=src/binary_parser.h
PROD_OBJECTS=$(PROD_TARGET)/binary_parser.o $(PROD_TARGET)/main.o
TEST_EXECS=$(TEST_TARGET)/story_tests
	
.PHONY: pre-build prod test all

$(TEST_TARGET):
	mkdir -p $(TEST_TARGET)
	
$(PROD_TARGET):
	mkdir -p $(PROD_TARGET)

$(PROD_TARGET)/%.o: $(SRC)/%.c $(PROD_TARGET) $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TEST_TARGET)/%.o: $(TEST_TARGET)/%.c $(PROD_TARGET) $(TEST_TARGET) $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TEST_TARGET)/%.c: $(TEST)/%.check $(TEST_TARGET) $(HEADERS)
	checkmk $< > $@
	cp $@ /tmp

prod: $(PROD_OBJECTS)
	$(CC) -o $(PROD_TARGET)/falconkata $^

$(TEST_TARGET)/%: $(TEST_TARGET)/%.o prod
	$(CC) -o $@ $< $(TEST_LIBS)

test: $(PROD_OBJECTS) $(TEST_EXECS)
	$(CC) -o $(TEST_TARGET)/falconkata_test $(PROD_OBJECTS) $(TEST_OBJECTS) $(TEST_LIBS)

all: prod test
