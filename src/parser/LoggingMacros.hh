#pragma once

#define LOG_START(OBJ, ASN_DATA)                                               \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" STARTED, now at \"{}\"",                           \
              (OBJ),                                                           \
              (ASN_DATA).Peek() ?                                              \
                std::get<1>((ASN_DATA).Peek().value()) : "<EOF>");             \
}

#define LOG_PASS(OBJ, ASN_DATA)                                                \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" PASSED, now at \"{}\"",                            \
              (OBJ),                                                           \
              (ASN_DATA).Peek() ?                                              \
                std::get<1>((ASN_DATA).Peek().value()) : "<EOF>");             \
}

#define LOG_FAIL(OBJ, ASN_DATA)                                                \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" FAILED, now at \"{}\"",                            \
              (OBJ),                                                           \
              (ASN_DATA).Peek() ?                                              \
                std::get<1>((ASN_DATA).Peek().value()) : "<EOF>");             \
}
