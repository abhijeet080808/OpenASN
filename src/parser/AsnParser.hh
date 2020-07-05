#pragma once

#include "IProduction.hh"

#include <vector>

namespace OpenASN
{
  class AsnParser
  {
    public:
      std::vector<std::shared_ptr<IProduction>>
        Parse(const std::string& asnFilePath);
  };
}
