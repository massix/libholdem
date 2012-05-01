# test folder

include_directories(. ../src)

file(GLOB SOURCES *.c)

link_directories(${PROJECT_BINARY_DIR})
link_libraries(holdem check)

add_definitions(--std=c99 -Wall)
add_executable(unittest ${SOURCES})

enable_testing()
add_test(MainUnitTest unittest)
