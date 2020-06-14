#pragma once

#include "IProduction.hh"

namespace OpenASN
{
  class AsnParser
  {
    public:
      std::shared_ptr<IProduction> Parse(const std::string& asnFilePath);
  };
}
