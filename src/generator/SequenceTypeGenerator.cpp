#include "SequenceTypeGenerator.hh"

#include "BooleanTypeGenerator.hh"
#include "IntegerTypeGenerator.hh"

#include "common/StringManip.hh"
#include "parser/BuiltinType.hh"
#include "parser/ComponentType.hh"
#include "parser/ComponentTypeList.hh"
#include "parser/ComponentTypeLists.hh"
#include "parser/Identifier.hh"
#include "parser/NamedType.hh"
#include "parser/RootComponentTypeList.hh"
#include "parser/Type.hh"
#include "spdlog/spdlog.h"

#include <fstream>
#include <sstream>

using namespace OpenASN;

SequenceTypeGenerator::
SequenceTypeGenerator(const std::string& identifier,
                     bool isConstructed,
                     SequenceType* pSequenceType)
  : mIdentifier(identifier),
    mIsConstructed(isConstructed)
{
  StringManip::Capitalize(mIdentifier);

  auto p_component_type_lists = dynamic_cast<ComponentTypeLists*>(
      pSequenceType->mComponentTypeLists.get());

  auto p_root_component_type_list = dynamic_cast<RootComponentTypeList*>(
      p_component_type_lists->mRootComponentTypeList.get());

  auto p_component_type_list = dynamic_cast<ComponentTypeList*>(
      p_root_component_type_list->mComponentTypeList.get());

  while (p_component_type_list)
  {
    auto p_component_type = dynamic_cast<ComponentType*>(
      p_component_type_list->mComponentType.get());

    auto p_named_type = dynamic_cast<NamedType*>(
      p_component_type->mNamedType.get());

    auto p_identifier = dynamic_cast<Identifier*>(
      p_named_type->mIdentifier.get());

    auto p_type = dynamic_cast<Type*>(
      p_named_type->mType.get());

    if (p_type->mBuiltinType.get())
    {
      auto p_builtin_type = dynamic_cast<BuiltinType*>(
          p_type->mBuiltinType.get());

      if (p_builtin_type->mBooleanType.get())
      {
        std::shared_ptr<IGenerator> generator =
          std::make_shared<BooleanTypeGenerator>(
              p_identifier->mValue,
              false);

        generator->Generate();
        mSubTypeGeneratorList.push_back(generator);
      }
      else if (p_builtin_type->mIntegerType.get())
      {
        std::shared_ptr<IGenerator> generator =
          std::make_shared<IntegerTypeGenerator>(
              p_identifier->mValue,
              false);

        generator->Generate();
        mSubTypeGeneratorList.push_back(generator);
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

    p_component_type_list = dynamic_cast<ComponentTypeList*>(
        p_component_type_list->mComponentTypeList.get());
  }
}

std::string
SequenceTypeGenerator::
GetIdentifier() const
{
  return mIdentifier;
}

void
SequenceTypeGenerator::
Generate() const
{
  std::stringstream ss_hdr;

  ss_hdr << "#pragma once\n"
         << "\n";

  for (const auto& type : mSubTypeGeneratorList)
  {
    ss_hdr << "#include \"" << type->GetIdentifier() << ".hh\"\n";
  }

  ss_hdr << "\n"
         << "#include <cstdint>\n"
         << "#include <vector>\n"
         << "\n"
         << "namespace OpenASN\n"
         << "{\n"
         << "  class " << mIdentifier << "\n"
         << "  {\n"
         << "    public:\n"
         << "      " << mIdentifier << "();\n"
         << "      " << mIdentifier << "(";

  int index = 0;
  for (size_t i = 0; i < mSubTypeGeneratorList.size(); i++)
  {
    auto type = mSubTypeGeneratorList.at(i);

    ss_hdr << "const " << type->GetIdentifier() << "& value" << index++;

    if (i < mSubTypeGeneratorList.size() - 1)
    {
      ss_hdr << ", ";
    }
  }

  ss_hdr << ");\n"
         << "\n";

  for (const auto& type : mSubTypeGeneratorList)
  {
    ss_hdr << "      void Set" << type->GetIdentifier()
           << "(const " << type->GetIdentifier() << "& value);\n"
           << "      " << type->GetIdentifier()
           << " Get" << type->GetIdentifier() << "() const;\n"
           << "\n";
  }

  ss_hdr << "      // Encodes and enqueues bytes to vector\n"
         << "      bool EncodeBER(std::vector<uint8_t>& buffer);\n"
         << "      // Dequeues and decodes bytes from vector\n"
         << "      bool DecodeBER(std::vector<uint8_t>& buffer);\n"
         << "\n"
         << "    private:\n";

  for (const auto& type : mSubTypeGeneratorList)
  {
    ss_hdr << "      " << type->GetIdentifier() << " m"
           << type->GetIdentifier() << ";\n";
  }

  ss_hdr << "  };\n"
         << "}";

  std::stringstream ss_src;

  ss_src << "#include \"" << mIdentifier << ".hh\"\n"
         << "\n"
         << "using namespace OpenASN;\n"
         << "\n"
         << mIdentifier << "::\n"
         << mIdentifier << "()\n"
         << "  : ";

  for (size_t i = 0; i < mSubTypeGeneratorList.size(); i++)
  {
    auto type = mSubTypeGeneratorList.at(i);

    if (i == 0)
    {
      ss_src << "m" << type->GetIdentifier() << "()";
    }
    else
    {
      ss_src << "    m" << type->GetIdentifier() << "()";
    }

    if (i == mSubTypeGeneratorList.size() - 1)
    {
      ss_src << "\n";
    }
    else
    {
      ss_src << ",\n";
    }
  }

  ss_src << "{\n"
         << "}\n"
         << "\n";

  ss_src << mIdentifier << "::\n"
         << mIdentifier << "(";

  index = 0;
  for (size_t i = 0; i < mSubTypeGeneratorList.size(); i++)
  {
    auto type = mSubTypeGeneratorList.at(i);

    ss_src << "const " << type->GetIdentifier() << "& value" << index++;

    if (i < mSubTypeGeneratorList.size() - 1)
    {
      ss_src << ", ";
    }
  }

  ss_src << ")\n"
         << "  : ";

  index = 0;
  for (size_t i = 0; i < mSubTypeGeneratorList.size(); i++)
  {
    auto type = mSubTypeGeneratorList.at(i);

    if (i == 0)
    {
      ss_src << "m" << type->GetIdentifier() << "(value" << index++ << ")";
    }
    else
    {
      ss_src << "    m" << type->GetIdentifier() << "(value" << index++ << ")";
    }

    if (i == mSubTypeGeneratorList.size() - 1)
    {
      ss_src << "\n";
    }
    else
    {
      ss_src << ",\n";
    }
  }

  ss_src << "{\n"
         << "}\n"
         << "\n";

  for (const auto& type : mSubTypeGeneratorList)
  {
    ss_src << "void\n"
           << mIdentifier << "::\n"
           << "Set" << type->GetIdentifier()
           << "(const " << type->GetIdentifier() << "& value)\n"
           << "{\n"
           << "  m" << type->GetIdentifier() << " = value;\n"
           << "}\n"
           << "\n"
           << type->GetIdentifier() << "\n"
           << mIdentifier << "::\n"
           << "Get" << type->GetIdentifier() << "() const\n"
           << "{\n"
           << "  return m" << type->GetIdentifier() << ";\n"
           << "}\n"
           << "\n";
  }

  ss_src << "bool\n"
         << mIdentifier << "::\n"
         << "EncodeBER(std::vector<uint8_t>& buffer)\n"
         << "{\n"
         << "  // Tag\n"
         << "  buffer.push_back(" << ((mIsConstructed << 5) | 16) << ");\n"
         << "\n"
         << "  // Length\n"
         << "  buffer.push_back(0);\n"
         << "  size_t length_index = buffer.size() - 1;\n"
         << "\n"
         << "  // Value\n";

  for (const auto& type : mSubTypeGeneratorList)
  {
    ss_src << "  if (!m" << type->GetIdentifier() << ".EncodeBER(buffer))\n"
           << "  {\n"
           << "    return false;\n"
           << "  }\n"
           << "\n";
  }

  ss_src << "\n"
         << "  buffer.at(length_index) = buffer.size() - length_index - 1;\n"
         << "\n"
         << "  return true;\n"
         << "}\n"
         << "\n"
         << "bool\n"
         << mIdentifier << "::\n"
         << "DecodeBER(std::vector<uint8_t>& buffer)\n"
         << "{\n"
         << "  // Tag\n"
         << "  if (buffer.size() < 1 || buffer.at(0) != "
         << ((mIsConstructed << 5) | 16) << ")\n"
         << "  {\n"
         << "    return false;\n"
         << "  }\n"
         << "\n"
         << "  // Length\n"
         << "  if (buffer.size() < 2 || buffer.at(1) < 1)\n"
         << "  {\n"
         << "    return false;\n"
         << "  }\n"
         << "\n"
         << "  const size_t len = buffer.at(1);\n"
         << "\n"
         << "  if (buffer.size() < (2 + len))\n"
         << "  {\n"
         << "    return false;\n"
         << "  }\n"
         << "\n"
         << "  // Value\n"
         << "  buffer.erase(buffer.begin());\n"
         << "  buffer.erase(buffer.begin());\n"
         << "\n";

  for (const auto& type : mSubTypeGeneratorList)
  {
    ss_src << "  if (!m" << type->GetIdentifier() << ".DecodeBER(buffer))\n"
           << "  {\n"
           << "    return false;\n"
           << "  }\n"
           << "\n";
  }

  ss_src << "  return true;\n"
         << "}\n";

  SPDLOG_DEBUG("{}", ss_hdr.str());
  SPDLOG_DEBUG("{}", ss_src.str());

  std::ofstream hdr_file(mIdentifier + ".hh");
  hdr_file << ss_hdr.rdbuf();
  hdr_file.close();
  SPDLOG_INFO("Generated {}.hh", mIdentifier);

  std::ofstream src_file(mIdentifier + ".cpp");
  src_file << ss_src.rdbuf();
  src_file.close();
  SPDLOG_INFO("Generated {}.cpp", mIdentifier);
}
