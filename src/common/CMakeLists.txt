set(LIB_NAME common)

set(SOURCES
  StringManip.cpp
)

add_library(${LIB_NAME} ${SOURCES})

#target_compile_options

#target_include_directories

#target_link_libraries

set_target_properties(${LIB_NAME} PROPERTIES UNITY_BUILD ON)
