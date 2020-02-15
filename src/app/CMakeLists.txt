set(EXE_NAME asn1c)

set(SOURCES asn1c.cpp)

add_executable(${EXE_NAME} ${SOURCES})

#target_compile_options

target_include_directories(${EXE_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${EXE_NAME}
  PRIVATE
    cxxopts
    spdlog
    common
    generator
    parser
)
