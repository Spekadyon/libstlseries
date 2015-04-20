project (libstlseries C)

cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(HIDAPI REQUIRED)

include_directories (${HIDAPI_INCLUDE_DIRS})

add_library (stlseries SHARED lib.c stlseries.h)
set_target_properties(stlseries PROPERTIES SOVERSION 0 VERSION 0.0.0)
target_link_libraries (stlseries ${HIDAPI_LIBRARIES})


install (TARGETS stlseries DESTINATION lib)
install (FILES stlseries.h DESTINATION include)
