set(CTEST_CUSTOM_TESTS_IGNORE
  ${CTEST_CUSTOM_TESTS_IGNORE}
  # ignore tests from cxxopts
  options
  find-package-test
  add-subdirectory-test
)
