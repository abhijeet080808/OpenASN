#pragma once

#define LOG_START(OBJ, ASN_DATA)                                               \
{                                                                              \
  SPDLOG_INFO("Parse \"{}\" at \"{}\": STARTED",                               \
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

#define LOG_RESULT(PARSED_RESULT, OBJ, ASN_DATA)                               \
{                                                                              \
  switch ((PARSED_RESULT))                                                     \
  {                                                                            \
    case ParseResult::PASSED:                                                  \
      SPDLOG_INFO("Parse \"{}\" at \"{}\": PASSED",                            \
                  (OBJ),                                                       \
                  (ASN_DATA).PeekCurrent() ?                                   \
                    std::get<1>((ASN_DATA).PeekCurrent().value()) : "-");      \
      break;                                                                   \
    case ParseResult::FAILED:                                                  \
      SPDLOG_ERROR("Parse \"{}\" at \"{}\": FAILED",                           \
                   (OBJ),                                                      \
                   (ASN_DATA).PeekCurrent() ?                                  \
                     std::get<1>((ASN_DATA).PeekCurrent().value()) : "-");     \
      break;                                                                   \
    case ParseResult::NOT_PRESENT:                                             \
      SPDLOG_INFO("Parse \"{}\" at \"{}\": NOT_PRESENT",                       \
                  (OBJ),                                                       \
                  (ASN_DATA).PeekCurrent() ?                                   \
                    std::get<1>((ASN_DATA).PeekCurrent().value()) : "-");      \
      break;                                                                   \
    default:                                                                   \
      SPDLOG_WARN("Parse \"{}\" at \"{}\": NA",                                \
                  (OBJ),                                                       \
                  (ASN_DATA).PeekCurrent() ?                                   \
                    std::get<1>((ASN_DATA).PeekCurrent().value()) : "-");      \
  }                                                                            \
}
