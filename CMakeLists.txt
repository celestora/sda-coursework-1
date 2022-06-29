cmake_minimum_required(VERSION 2.8)
project(coursework C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-std=gnu99 -O0)

add_executable(coursework main.c getch.c getch.h Table.c LinkedList.c Table.h LinkedList.h Menu.h Menu.c Algos.c Algos.h TestArray.c TestArray.h Generators.c Generators.h BenchMark.c BenchMark.h)
