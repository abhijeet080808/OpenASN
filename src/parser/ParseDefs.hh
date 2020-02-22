#pragma once

#include <tuple>
#include <string>

namespace OpenASN
{
  enum class PrecedingInfo
  {
    PRECEDED_BY_WHITESPACE,
    PRECEDED_BY_NEWLINE,
  };

  enum class SucceedingInfo
  {
    SUCCEEDED_BY_WHITESPACE,
    SUCCEEDED_BY_NEWLINE
  };

  using Word = std::tuple<PrecedingInfo, std::string, SucceedingInfo>;
}
