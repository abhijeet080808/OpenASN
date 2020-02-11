#pragma once

#include "parser/IProduction.hh"

#include <memory>

namespace OpenASN
{
  class AsnGenerator
  {
    public:
      bool Generate(const std::shared_ptr<IProduction> production);
  };
}
