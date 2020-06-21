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

  using Word = std::tuple<
    PrecedingInfo,
    std::string,    // the actual ASN word
    SucceedingInfo,
    size_t,         // number of whitespaces preceding this word
    size_t,         // line index of this word in ASN1 defination
    size_t>;        // char index of this word in ASN1 defination
}
