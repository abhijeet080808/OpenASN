#include "AsnGenerator.hh"

#include "BooleanTypeGenerator.hh"
#include "IntegerTypeGenerator.hh"
#include "SequenceTypeGenerator.hh"

#include "parser/AssignmentList.hh"
#include "parser/BuiltinType.hh"
#include "parser/ModuleBody.hh"
#include "parser/ModuleIdentifier.hh"
#include "parser/Type.hh"
#include "parser/TypeAssignment.hh"
#include "parser/TypeReference.hh"
#include "spdlog/spdlog.h"

#include <cassert>

using namespace OpenASN;

bool
AsnGenerator::
Generate(const ModuleDefinition* pModuleDefinition)
{
  auto p_module_identifier = dynamic_cast<ModuleIdentifier*>(
      pModuleDefinition->mModuleIdentifier.get());
  auto p_module_reference = dynamic_cast<ModuleReference*>(
      p_module_identifier->mModuleReference.get());

  auto p_module_body = dynamic_cast<ModuleBody*>(
      pModuleDefinition->mModuleBody.get());
  auto p_assignment_list = dynamic_cast<AssignmentList*>(
      p_module_body->mAssignmentList.get());

  SPDLOG_INFO("Module: {}", p_module_reference->mValue);
  SPDLOG_INFO("Assignments: {}", p_assignment_list->mAssignment.size());

  for (const auto& assignment : p_assignment_list->mAssignment)
  {
    auto p_assignment = dynamic_cast<Assignment*>(
        assignment.get());

    generateClass(p_assignment);
  }

  return true;
}

bool
AsnGenerator::
generateClass(const Assignment* pAssignment)
{
  if (pAssignment->mTypeAssignment.get())
  {
    auto p_type_assignment = dynamic_cast<TypeAssignment*>(
      pAssignment->mTypeAssignment.get());

    auto p_type_reference = dynamic_cast<TypeReference*>(
      p_type_assignment->mTypeReference.get());

    auto p_type = dynamic_cast<Type*>(
      p_type_assignment->mType.get());

    if (p_type->mBuiltinType.get())
    {
      auto p_builtin_type = dynamic_cast<BuiltinType*>(
          p_type->mBuiltinType.get());

      if (p_builtin_type->mBooleanType.get())
      {
        std::shared_ptr<IGenerator> generator =
          std::make_shared<BooleanTypeGenerator>(
              p_type_reference->mValue,
              false);

        generator->Generate();
      }
      else if (p_builtin_type->mIntegerType.get())
      {
        std::shared_ptr<IGenerator> generator =
          std::make_shared<IntegerTypeGenerator>(
              p_type_reference->mValue,
              false);

        generator->Generate();
      }
      else if (p_builtin_type->mSequenceType.get())
      {
        std::shared_ptr<IGenerator> generator =
          std::make_shared<SequenceTypeGenerator>(
              p_type_reference->mValue,
              false,
              dynamic_cast<SequenceType*>(
                p_builtin_type->mSequenceType.get()));

        generator->Generate();
      }
      else
      {
        assert(false);
      }
    }
    else
    {
      assert(false);
    }
  }
  else
  {
    assert(false);
  }

  return true;
}

