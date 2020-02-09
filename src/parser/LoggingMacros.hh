#pragma once

#define LOG_START(OBJ, ASN_DATA)                                               \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" started at \"{}\"",                                \
              (OBJ),                                                           \
              (ASN_DATA).PeekCurrent() ?                                       \
                std::get<1>((ASN_DATA).PeekCurrent().value()) : "-");          \
}

#define LOG_PASS(OBJ, ASN_DATA)                                                \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" passed at \"{}\"",                                 \
              (OBJ),                                                           \
              (ASN_DATA).PeekCurrent() ?                                       \
                std::get<1>((ASN_DATA).PeekCurrent().value()) : "-");          \
}

#define LOG_FAIL(OBJ, ASN_DATA)                                                \
{                                                                              \
  SPDLOG_ERROR("Parse \"{}\" failed at \"{}\"",                                \
               (OBJ),                                                          \
               (ASN_DATA).PeekCurrent() ?                                      \
                 std::get<1>((ASN_DATA).PeekCurrent().value()) : "-");         \
}
