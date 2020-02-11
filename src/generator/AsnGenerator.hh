#pragma once

#include "parser/Assignment.hh"
#include "parser/ModuleDefinition.hh"

#include <memory>

namespace OpenASN
{
  class AsnGenerator
  {
    public:
      bool Generate(const ModuleDefinition* pModuleDefinition);

    private:
      bool generateClass(const Assignment* pAssignment);
  };
}
