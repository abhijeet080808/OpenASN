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
      bool generateClass(const std::string& moduleReference,
                         const Assignment* pAssignment);
      bool generateBooleanTypeClass(const std::string& moduleReference,
                                    const std::string& typeReference);
  };
}
