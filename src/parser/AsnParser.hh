#pragma once

#include "Production.hh"

#include <string>

namespace OpenASN
{
  class AsnParser
  {
    public:
      void Parse(const std::string& asnFilePath);
  };
}
