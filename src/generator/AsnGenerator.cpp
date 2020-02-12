#include "AsnGenerator.hh"

#include "parser/AssignmentList.hh"
#include "parser/BooleanType.hh"
#include "parser/BuiltinType.hh"
#include "parser/ModuleBody.hh"
#include "parser/ModuleIdentifier.hh"
#include "parser/Type.hh"
#include "parser/TypeAssignment.hh"
#include "parser/TypeReference.hh"

#include "spdlog/spdlog.h"

#include <cassert>
#include <fstream>
#include <sstream>

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

    generateClass(p_module_reference->mValue, p_assignment);
  }

  return true;
}

bool
AsnGenerator::
generateClass(const std::string& moduleReference, const Assignment* pAssignment)
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
        generateBooleanTypeClass(moduleReference, p_type_reference->mValue);
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

bool
AsnGenerator::
generateBooleanTypeClass(const std::string& moduleReference,
                         const std::string& typeReference)
{
  std::stringstream ss_hdr;

  ss_hdr << "#pragma once\n"
         << "\n"
         << "#include <vector>\n"
         << "\n"
         << "namespace " << moduleReference << "\n"
         << "{\n"
         << "  class " << typeReference << "\n"
         << "  {\n"
         << "    public:\n"
         << "      " << typeReference << "();\n"
         << "\n"
         << "      void SetValue(bool value);\n"
         << "      bool GetValue() const;\n"
         << "\n"
         << "      // Encodes and enqueues bytes to vector\n"
         << "      bool EncodeBER(std::vector<uint8_t>& buffer);\n"
         << "      // Dequeues and decodes bytes from vector\n"
         << "      bool DecodeBER(std::vector<uint8_t>& buffer);\n"
         << "\n"
         << "    private:\n"
         << "      bool mValue;\n"
         << "  };\n"
         << "}";

  SPDLOG_DEBUG("{}", ss_hdr.str());

  std::stringstream ss_cpp;

  ss_cpp << "#include \"" << typeReference << ".hh\"\n"
         << "\n"
         << "using namespace " << moduleReference << ";\n"
         << "\n"
         << typeReference << "::\n"
         << typeReference << "()\n"
         << "  : mValue(false)\n"
         << "{\n"
         << "}\n"
         << "\n"
         << "void\n"
         << typeReference << "::\n"
         << "SetValue(bool value)\n"
         << "{\n"
         << "  mValue = value;\n"
         << "}\n"
         << "\n"
         << "bool\n"
         << typeReference << "::\n"
         << "GetValue() const\n"
         << "{\n"
         << "  return mValue;\n"
         << "}\n"
         << "\n"
         << "bool\n"
         << typeReference << "::\n"
         << "EncodeBER(std::vector<uint8_t>& buffer)\n"
         << "{\n"
         << "  // Tag for BOOLEAN is 1\n"
         << "  buffer.push_back(0x01);\n"
         << "\n"
         << "  // Length is 1\n"
         << "  buffer.push_back(0x01);\n"
         << "\n"
         << "  // Write value\n"
         << "  buffer.push_back(mValue ? 0xFF : 0x00);\n"
         << "\n"
         << "  return true;\n"
         << "}\n"
         << "\n"
         << "bool\n"
         << typeReference << "::\n"
         << "DecodeBER(std::vector<uint8_t>& buffer)\n"
         << "{\n"
         << "  if (buffer.size() < 3)\n"
         << "  {\n"
         << "    return false;\n"
         << "  }\n"
         << "\n"
         << "  // Tag for BOOLEAN is 1\n"
         << "  if (buffer.at(0) != 0x01)\n"
         << "  {\n"
         << "    return false;\n"
         << "  }\n"
         << "\n"
         << "  // Length is 1\n"
         << "  if (buffer.at(1) != 0x01)\n"
         << "  {\n"
         << "    return false;\n"
         << "  }\n"
         << "\n"
         << "  // Read value\n"
         << "  mValue = (buffer.at(2) == 0x00 ? false : true);\n"
         << "\n"
         << "  buffer.erase(buffer.begin());\n"
         << "  buffer.erase(buffer.begin());\n"
         << "  buffer.erase(buffer.begin());\n"
         << "\n"
         << "  return true;\n"
         << "}\n";

  SPDLOG_DEBUG("{}", ss_cpp.str());

  std::ofstream hh_file(typeReference + ".hh");
  hh_file << ss_hdr.rdbuf();
  hh_file.close();
  SPDLOG_INFO("Wrote {}.hh", typeReference);

  std::ofstream cc_file(typeReference + ".cpp");
  cc_file << ss_cpp.rdbuf();
  cc_file.close();
  SPDLOG_INFO("Wrote {}.cpp", typeReference);

  return true;
}
