#pragma once

#include "Module.hh"

#include <string>

namespace OpenASN
{
  // X.680 08/2015 sec 13.1
  class Parser
  {
    private:
      enum ModuleParserState
      {
        START,
        READ_MODULE_IDENTIFIER,
        READ_DEFINITIONS,
        READ_ENCODING_REFERENCE_DEFAULT,
        READ_TAG_DEFAULT,
        READ_EXTENSION_DEFAULT,
        READ_DOUBLE_COLON_EQUAL,
        READ_BEGIN,
        READ_MODULE_BODY,
        READ_ENCODING_CONTROL_SECTIONS,
        READ_END,
        END
      };

    public:
      bool Parse(const std::string& asnWord);

    private:
      ModuleParserState mState;
      Module mModule;
  };
}
