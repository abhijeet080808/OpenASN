set(LIB_NAME generator)

set(SOURCES AsnGenerator.cpp
)

add_library(${LIB_NAME} ${SOURCES})

#target_compile_options

target_include_directories(${LIB_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${LIB_NAME}
  PRIVATE
    spdlog
    parser
)
