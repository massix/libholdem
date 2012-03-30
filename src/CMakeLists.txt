# src folder

include_directories(.)
set(LIBHOLDEM_MAJOR 1)
set(LIBHOLDEM_REVIEW 0)
set(LIBHOLDEM_MINOR 0)

file(GLOB SOURCES *.c)

#configure_file(
#	"${PROJECT_SOURCE_DIR}/src/holdem_version.h.in"
#	"${PROJECT_SOURCE_DIR}/src/holdem_version.h"
#)

add_definitions(--std=c99 -Wall -dynamiclib)
add_library(holdem SHARED ${SOURCES})
add_library(sholdem STATIC ${SOURCES})

