#include "AsnGenerator.hh"

#include "parser/ModuleDefinition.hh"
#include "parser/ModuleIdentifier.hh"
#include "parser/TypeReference.hh"
#include "parser/ModuleBody.hh"
#include "parser/AssignmentList.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
AsnGenerator::
Generate(const std::shared_ptr<IProduction> production)
{
  auto p_module_definition = dynamic_cast<ModuleDefinition*>(
      production.get());

  auto p_module_identifier = dynamic_cast<ModuleIdentifier*>(
      p_module_definition->mModuleIdentifier.get());
  auto p_module_reference = dynamic_cast<ModuleReference*>(
      p_module_identifier->mModuleReference.get());

  auto p_module_body = dynamic_cast<ModuleBody*>(
      p_module_definition->mModuleBody.get());
  auto assignment_list = dynamic_cast<AssignmentList*>(
      p_module_body->mAssignmentList.get());


  auto module_name = p_module_reference->mValue;

  SPDLOG_INFO("Module: {}", module_name);
  SPDLOG_INFO("Assignments: {}", assignment_list->mAssignment.size());
  return production.get() != nullptr;
}

