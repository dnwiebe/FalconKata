#!/bin/bash

target/tests/binary_parser_test
target/tests/converters_test
target/tests/roman_arithmetic_test
target/tests/story_tests

target/falconkata <tests/input.txt >/tmp/actual.txt
diff tests/expected.txt /tmp/actual.txt
