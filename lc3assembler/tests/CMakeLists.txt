cmake_minimum_required(VERSION 3.12)

project(lc3asm)

include_directories(googletest/include)
list(APPEND testDependencies "../reader.cpp" "../instructions.cpp" "../assembler.cpp")
add_executable(assemblerTest assemblerTest.cpp ${testDependencies})

target_link_libraries(assemblerTest PRIVATE gtest fmt)