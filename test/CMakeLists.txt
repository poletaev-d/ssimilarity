cmake_minimum_required(VERSION 2.8)
project(ssimilarity_test)
set(SOURCES main.cpp similarity_functions.cpp)

add_executable(ssimilarity_test ${SOURCES})


target_include_directories(ssimilarity_test PRIVATE "../third_party/googletest/googletest/include")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(../third_party/googletest/googletest gtest_build)
target_link_libraries(ssimilarity_test gtest)

target_include_directories(ssimilarity_test PRIVATE "../src")


add_test(NAME SSimilarityTest COMMAND ssimilarity_test)