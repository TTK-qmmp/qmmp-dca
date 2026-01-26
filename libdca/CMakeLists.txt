cmake_minimum_required(VERSION 3.0)

project(dca)

set(HEADERS
    dca.h
    gettimeofday.h
)

set(SOURCES
    parse.c
    gettimeofday.c
    extract_dca.c
    downmix.c
    bitstream.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${STATIC_LIB_SUFFIX})

install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/lib${PROJECT_NAME})
