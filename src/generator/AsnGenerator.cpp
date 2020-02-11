#include "AsnGenerator.hh"

#include "parser/ModuleIdentifier.hh"
#include "parser/TypeReference.hh"
#include "parser/ModuleBody.hh"
#include "parser/AssignmentList.hh"

#include "spdlog/spdlog.h"

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
generateClass(const Assignment* )//assignment)
{
  return true;
}
