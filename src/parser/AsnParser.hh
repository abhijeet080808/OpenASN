#pragma once

#include "Production.hh"

#include <string>

namespace OpenASN
{
  class AsnParser
  {
    private:
      enum ParserState
      {
        START,
        READ_PRODUCTION_NAME,
        END
      };

    public:
      void Parse(const std::string& asnFilePath);

    private:
      void consume(const std::string& asnWord,
                   ParserState& state,
                   Production& production);
  };
}
