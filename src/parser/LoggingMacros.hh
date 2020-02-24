#pragma once

#define LOG_START_GEN(OBJ, ASN_DATA, ASN_DATA_INDEX)                           \
{                                                                              \
  SPDLOG_DEBUG("Parse \"{}\" STARTED, now at \"{}\"",                          \
               (OBJ),                                                          \
               (ASN_DATA).size() > (ASN_DATA_INDEX) ?                          \
                 std::get<1>((ASN_DATA).at((ASN_DATA_INDEX))) : "<EOF>");      \
}

#define LOG_PASS_GEN(OBJ, ASN_DATA, ASN_DATA_INDEX)                            \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" PASSED, now at \"{}\"",                            \
              (OBJ),                                                           \
              (ASN_DATA).size() > (ASN_DATA_INDEX) ?                           \
                std::get<1>((ASN_DATA).at((ASN_DATA_INDEX))) : "<EOF>");       \
}

#define LOG_FAIL_GEN(OBJ, ASN_DATA, ASN_DATA_INDEX)                            \
{                                                                              \
  SPDLOG_DEBUG("Parse \"{}\" FAILED, now at \"{}\"",                           \
               (OBJ),                                                          \
               (ASN_DATA).size() > (ASN_DATA_INDEX) ?                          \
                 std::get<1>((ASN_DATA).at((ASN_DATA_INDEX))) : "<EOF>");      \
}

#define LOG_START() LOG_START_GEN(obj, asnData, asnDataIndex)
#define LOG_PASS()  LOG_PASS_GEN(obj, asnData, asnDataIndex)
#define LOG_FAIL()  LOG_FAIL_GEN(obj, asnData, asnDataIndex)

