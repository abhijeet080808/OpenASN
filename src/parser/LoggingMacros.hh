#pragma once

#include "common/StringManip.hh"

namespace OpenASN
{
  #define LOG_GEN(ACTION, OBJ, ASN_DATA, ASN_DATA_IDX, PARSE_PATH)             \
  {                                                                            \
    SPDLOG_INFO("{}: {} parse \"{}\" [{}]",                                    \
                (ASN_DATA).size() > (ASN_DATA_IDX) ?                           \
                  "["                                                        + \
                  std::to_string(std::get<4>((ASN_DATA).at((ASN_DATA_IDX)))) + \
                  ":"                                                        + \
                  std::to_string(std::get<5>((ASN_DATA).at((ASN_DATA_IDX)))) + \
                  "] \""                                                     + \
                  std::get<1>((ASN_DATA).at((ASN_DATA_IDX)))                 + \
                  "\"" :                                                       \
                  "[-:-] \"<EOF>\"",                                           \
                (ACTION),                                                      \
                (OBJ),                                                         \
                StringManip::Flatten((PARSE_PATH), ">"));                      \
  }

  #define LOG_START() LOG_GEN("STARTED", obj, asnData, asnDataIndex, parsePath)
  #define LOG_PASS() LOG_GEN("PASSED", obj, asnData, asnDataIndex, parsePath)
  #define LOG_FAIL() LOG_GEN("FAILED", obj, asnData, asnDataIndex, parsePath)
}
