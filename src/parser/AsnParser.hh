#pragma once

#include <string>

namespace OpenASN
{
  class AsnParser
  {
    public:
      void Parse(const std::string& asnFilePath);
  };
}
