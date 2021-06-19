set(CMAKE_CXX_FLAGS "-std=c++17 -pedantic -Wall -Wextra -Werror")

project(oop_exercise_08)

add_executable(oop_exercise_08 main.cpp)
target_link_libraries(oop_exercise_08 pthread)