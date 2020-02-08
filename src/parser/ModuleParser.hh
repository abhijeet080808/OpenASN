#pragma once

#include "Module.hh"

#include <string>

namespace OpenASN
{
  class ModuleParser
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
        READ_ASSIGNMENT_CHAR_SEQUENCE, // "::="
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
