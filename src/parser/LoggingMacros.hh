#pragma once

#include "common/StringManip.hh"

namespace OpenASN
{
  #define LOG_START_GEN(OBJ, ASN_DATA, ASN_DATA_INDEX, PARSE_PATH)             \
  {                                                                            \
    SPDLOG_INFO("At \"{}\"({}) - STARTED parse \"{}\" [{}]",                   \
                (ASN_DATA).size() > (ASN_DATA_INDEX) ?                         \
                  std::get<1>((ASN_DATA).at((ASN_DATA_INDEX))) : "<EOF>",      \
                ASN_DATA_INDEX,                                                \
                (OBJ),                                                         \
                StringManip::Flatten((PARSE_PATH), ">"));                      \
  }

  #define LOG_PASS_GEN(OBJ, ASN_DATA, ASN_DATA_INDEX, PARSE_PATH)              \
  {                                                                            \
    SPDLOG_INFO("At \"{}\"({}) - PASSED parse \"{}\" [{}]",                    \
                (ASN_DATA).size() > (ASN_DATA_INDEX) ?                         \
                  std::get<1>((ASN_DATA).at((ASN_DATA_INDEX))) : "<EOF>",      \
                ASN_DATA_INDEX,                                                \
                (OBJ),                                                         \
                StringManip::Flatten((PARSE_PATH), ">"));                      \
  }

  #define LOG_FAIL_GEN(OBJ, ASN_DATA, ASN_DATA_INDEX, PARSE_PATH)              \
  {                                                                            \
    SPDLOG_INFO("At \"{}\"({}) - FAILED parse \"{}\" [{}]",                    \
                (ASN_DATA).size() > (ASN_DATA_INDEX) ?                         \
                  std::get<1>((ASN_DATA).at((ASN_DATA_INDEX))) : "<EOF>",      \
                ASN_DATA_INDEX,                                                \
                (OBJ),                                                         \
                StringManip::Flatten((PARSE_PATH), ">"));                      \
  }

  #define LOG_START() LOG_START_GEN(obj, asnData, asnDataIndex, parsePath)
  #define LOG_PASS()  LOG_PASS_GEN(obj, asnData, asnDataIndex, parsePath)
  #define LOG_FAIL()  LOG_FAIL_GEN(obj, asnData, asnDataIndex, parsePath)
}
