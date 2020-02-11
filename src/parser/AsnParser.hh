#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  class AsnParser
  {
    public:
      std::shared_ptr<IProduction> Parse(const std::string& asnFilePath);
  };
}
