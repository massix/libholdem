# src folder

include_directories(. ../src)

file(GLOB SOURCES *.c)

#configure_file(
#	"${PROJECT_SOURCE_DIR}/src/holdem_version.h.in"
#	"${PROJECT_SOURCE_DIR}/src/holdem_version.h"
#)

link_directories(${PROJECT_BINARY_DIR})
link_libraries(check holdem)

add_definitions(--std=c99 -Wall -dynamiclib)
add_executable(unittest ${SOURCES})

enable_testing()
add_test(MainUnitTest unittest)
