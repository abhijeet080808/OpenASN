#pragma once

#define LOG_START_GEN(OBJ, ASN_DATA, ASN_DATA_INDEX)                           \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" STARTED, now at \"{}\"",                           \
              (OBJ),                                                           \
              (ASN_DATA).size() > (ASN_DATA_INDEX) ?                           \
                std::get<1>((ASN_DATA).at((ASN_DATA_INDEX))) : "<EOF>");       \
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
  SPDLOG_INFO("Parse \"{}\" FAILED, now at \"{}\"",                            \
              (OBJ),                                                           \
              (ASN_DATA).size() > (ASN_DATA_INDEX) ?                           \
                std::get<1>((ASN_DATA).at((ASN_DATA_INDEX))) : "<EOF>");       \
}

#define LOG_START()                                                            \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" STARTED, now at \"{}\"",                           \
              obj,                                                             \
              asnData.size() > asnDataIndex ?                                  \
                std::get<1>(asnData.at(asnDataIndex)) : "<EOF>");              \
}

#define LOG_PASS()                                                             \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" PASSED, now at \"{}\"",                            \
              obj,                                                             \
              asnData.size() > asnDataIndex ?                                  \
                std::get<1>(asnData.at(asnDataIndex)) : "<EOF>");              \
}

#define LOG_FAIL()                                                             \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" FAILED, now at \"{}\"",                            \
              obj,                                                             \
              asnData.size() > asnDataIndex ?                                  \
                std::get<1>(asnData.at(asnDataIndex)) : "<EOF>");              \
}
