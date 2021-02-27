#!/bin/bash
g++-10 -o main -W -Wall -Wextra -pedantic -Iextern/cpp11_range/include -Iextern/eigen -Iinclude -g -std=gnu++20 test.cpp
