#include "BooleanTypeGenerator.hh"

#include "common/StringManip.hh"
#include "spdlog/spdlog.h"

#include <fstream>
#include <sstream>

using namespace OpenASN;

BooleanTypeGenerator::
BooleanTypeGenerator(const std::string& identifier,
                     bool isConstructed)
  : mIdentifier(identifier),
    mIsConstructed(isConstructed)
{
  StringManip::Capitalize(mIdentifier);
}

void
BooleanTypeGenerator::
Generate()
{
  std::stringstream ss_hdr;

  ss_hdr << "#pragma once\n"
         << "\n"
         << "#include <cstdint>\n"
         << "#include <vector>\n"
         << "\n"
         << "namespace OpenASN\n"
         << "{\n"
         << "  class " << mIdentifier << "\n"
         << "  {\n"
         << "    public:\n"
         << "      " << mIdentifier << "();\n"
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

  std::stringstream ss_src;

  ss_src << "#include \"" << mIdentifier << ".hh\"\n"
         << "\n"
         << "using namespace OpenASN;\n"
         << "\n"
         << mIdentifier << "::\n"
         << mIdentifier << "()\n"
         << "  : mValue(false)\n"
         << "{\n"
         << "}\n"
         << "\n"
         << "void\n"
         << mIdentifier << "::\n"
         << "SetValue(bool value)\n"
         << "{\n"
         << "  mValue = value;\n"
         << "}\n"
         << "\n"
         << "bool\n"
         << mIdentifier << "::\n"
         << "GetValue() const\n"
         << "{\n"
         << "  return mValue;\n"
         << "}\n"
         << "\n"
         << "bool\n"
         << mIdentifier << "::\n"
         << "EncodeBER(std::vector<uint8_t>& buffer)\n"
         << "{\n"
         << "  // Tag\n"
         << "  buffer.push_back(" << ((mIsConstructed << 5) | 1) << ");\n"
         << "\n"
         << "  // Length\n"
         << "  buffer.push_back(1);\n"
         << "\n"
         << "  // Value\n"
         << "  buffer.push_back(mValue ? 0xff : 0x00);\n"
         << "\n"
         << "  return true;\n"
         << "}\n"
         << "bool\n"
         << mIdentifier << "::\n"
         << "DecodeBER(std::vector<uint8_t>& buffer)\n"
         << "{\n"
         << "  // Tag\n"
         << "  if (buffer.size() < 1 || buffer.at(0) != " << ((mIsConstructed << 5) | 1) << ")\n"
         << "  {\n"
         << "    return false;\n"
         << "  }\n"
         << "\n"
         << "  // Length\n"
         << "  if (buffer.size() < 2 || buffer.at(1) != 1)\n"
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
         << "  mValue = (buffer.at(2) == 0 ? false : true);\n"
         << "\n"
         << "  for (size_t i = 0; i < 2 + len; i++)\n"
         << "  {\n"
         << "    buffer.erase(buffer.begin());\n"
         << "  }\n"
         << "\n"
         << "  return true;"
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
