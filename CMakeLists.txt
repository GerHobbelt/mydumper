cmake_minimum_required(VERSION 2.6)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(mydumper)
set(VERSION 0.10.0)
set(ARCHIVE_NAME "${CMAKE_PROJECT_NAME}-${VERSION}")

find_path(MYSQL_INCLUDE_DIR mysql/mysql.h)
find_library(MYSQL_LIBRARIES libmariadb.lib)

find_path(ZLIB_INCLUDE_DIRS NAMES zlib.h)
find_library(ZLIB_LIBRARIES zlib.lib)

find_path(PCRE_INCLUDE_DIR NAMES pcre.h)
find_library(PCRE_PCRE_LIBRARY pcre.lib)

find_path(PCRE_INCLUDE_DIR NAMES pcre.h)
find_library(PCRE_PCRE_LIBRARY pcre.lib)

find_path(GLIB2_INCLUDE_DIR NAMES glib.h)
find_library(GLIB2_LIBRARIES glib-2.0.lib)
find_library(GTHREAD2_LIBRARIES gthread-2.0.lib)

option(WITH_BINLOG "Build binlog dump options" OFF)
option(WITH_SSL "Build SSL support" ON)

set(CMAKE_C_FLAGS "-O2 ${MYSQL_CFLAGS}")

include_directories(${MYDUMPER_SOURCE_DIR} ${MYSQL_INCLUDE_DIR}/mysql ${GLIB2_INCLUDE_DIR} ${PCRE_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS})
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_executable(mydumper mydumper.c server_detect.c g_unix_signal.c connection.c getPassword.c)
target_link_libraries(mydumper ${MYSQL_LIBRARIES} ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} ${PCRE_PCRE_LIBRARY} ${ZLIB_LIBRARIES})

add_executable(myloader myloader.c connection.c getPassword.c)
target_link_libraries(myloader ${MYSQL_LIBRARIES} ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} ${PCRE_PCRE_LIBRARY} ${ZLIB_LIBRARIES})

INSTALL(TARGETS mydumper myloader
  RUNTIME DESTINATION bin
)
