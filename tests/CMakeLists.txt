# Both test case and its corresponding ASN1 file must have the same name,
# only differing by extension (.cpp vs .asn1)
#
# The list of test cases below must be specified in the below format -
#   <test_case_name>_<generated_test_file_1>_<generated_test_file_2>_<...>
#
#  Both test_name does and generated_test_file_* shall not specify the file
#  extension
set(TEST_CASES SimpleTypeTest_SimpleTypeTestBool_SimpleTypeTestInt
               SequenceTypeTest_SequenceTypeTestSeq_SequenceTypeTestInt1_SequenceTypeTestInt2_SequenceTypeTestBool1
)

foreach(TEST_CASE ${TEST_CASES})

  # split all test case tokens
  string(REPLACE "_" ";" TEST_TOKENS ${TEST_CASE})
  # first token is the test case name (name common to both cpp and asn1 file)
  list(GET TEST_TOKENS 0 TEST_NAME)
  # remove first token (rest tokens are names of files generated from asn1 file)
  list(REMOVE_AT TEST_TOKENS 0)
  # append cpp to all generated file names
  list(TRANSFORM TEST_TOKENS APPEND ".cpp" OUTPUT_VARIABLE TEST_TOKENS_CPP)
  # append hh to all generated file names
  list(TRANSFORM TEST_TOKENS APPEND ".hh" OUTPUT_VARIABLE TEST_TOKENS_HH)

  # use asn1c to parse asn1 file and generate hh/cpp files
  add_custom_command(
    OUTPUT  ${TEST_TOKENS_HH} ${TEST_TOKENS_CPP}
    COMMAND asn1c -a ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.asn1
    DEPENDS asn1c ${TEST_NAME}.asn1
  )

  add_executable(${TEST_NAME} ${TEST_NAME}.cpp ${TEST_TOKENS_CPP})

  target_include_directories(${TEST_NAME}
    PRIVATE
      ${PROJECT_BINARY_DIR}/tests
  )

  target_link_libraries(${TEST_NAME}
    PRIVATE
      gtest
      gmock
  )

  add_test(${TEST_NAME} ${TEST_NAME})

endforeach()
