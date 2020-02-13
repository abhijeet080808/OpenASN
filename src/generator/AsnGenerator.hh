#pragma once

#include "parser/Assignment.hh"
#include "parser/ComponentType.hh"
#include "parser/ModuleDefinition.hh"
#include "parser/SequenceType.hh"

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
      bool generateSequenceTypeClass(const std::string& moduleReference,
                                     const std::string& typeReference,
                                     const SequenceType* pSequenceType);
      bool generateComponentHeaderFunction(const ComponentType* pComponentType,
                                           std::stringstream& ss);
      bool generateComponentHeaderVariable(const ComponentType* pComponentType,
                                           std::stringstream& ss);
  };
}
