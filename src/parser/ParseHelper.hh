#pragma once

#include "ParseDefs.hh"

#include <string>
#include <vector>

namespace OpenASN
{
  class ParseHelper
  {
    public:
      static bool IsObjectPresent(const std::string& object,
                                  const std::vector<Word>& asnData,
                                  size_t& asnDataIndex);

    public:
      static bool HitEndStop(const std::string& asnWord,
                             const std::vector<std::string>& endStop);

      static bool IsReserved(const std::string& asnWord);
      static bool IsLexicalItem(char c);
      static bool IsWhitespace(char c);
      static bool IsNewline(char c);
  };
}
