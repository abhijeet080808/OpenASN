#include "IntegerTypeGenerator.hh"

#include "common/StringManip.hh"
#include "spdlog/spdlog.h"

#include <fstream>
#include <sstream>

using namespace OpenASN;

IntegerTypeGenerator::
IntegerTypeGenerator(const std::string& identifier,
                     bool isConstructed)
  : mIdentifier(identifier),
    mIsConstructed(isConstructed)
{
  StringManip::Capitalize(mIdentifier);
}

std::string
IntegerTypeGenerator::
GetIdentifier() const
{
  return mIdentifier;
}

void
IntegerTypeGenerator::
Generate() const
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
         << "      " << mIdentifier << "(int64_t value);\n"
         << "\n"
         << "      void SetValue(int64_t value);\n"
         << "      int64_t GetValue() const;\n"
         << "\n"
         << "      // Encodes and enqueues bytes to vector\n"
         << "      bool EncodeBER(std::vector<uint8_t>& buffer);\n"
         << "      // Dequeues and decodes bytes from vector\n"
         << "      bool DecodeBER(std::vector<uint8_t>& buffer);\n"
         << "\n"
         << "    private:\n"
         << "      int64_t mValue;\n"
         << "  };\n"
         << "}";

  std::stringstream ss_src;

  ss_src << "#include \"" << mIdentifier << ".hh\"\n"
         << "\n"
         << "using namespace OpenASN;\n"
         << "\n"
         << mIdentifier << "::\n"
         << mIdentifier << "()\n"
         << "  : mValue(0)\n"
         << "{\n"
         << "}\n"
         << "\n"
         << mIdentifier << "::\n"
         << mIdentifier << "(int64_t value)\n"
         << "  : mValue(value)\n"
         << "{\n"
         << "}\n"
         << "\n"
         << "void\n"
         << mIdentifier << "::\n"
         << "SetValue(int64_t value)\n"
         << "{\n"
         << "  mValue = value;\n"
         << "}\n"
         << "\n"
         << "int64_t\n"
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
         << "  buffer.push_back(" << ((mIsConstructed << 5) | 2) << ");\n"
         << "\n"
         << "  // Length\n"
         << "  buffer.push_back(0);\n"
         << "  size_t length_index = buffer.size() - 1;\n"
         << "\n"
         << "  // Value\n"
         << "  // for +ve values, if MSB of byte N is 0,\n"
         << "  // byte N - 1 with value 0x00 can be removed\n"
         << "  // for -ve values, if MSB of byte N is 1,\n"
         << "  // byte N - 1 with value 0xff can be removed\n"
         << "  bool try_drop = true;\n"
         << "\n"
         << "  for (size_t i = sizeof(mValue) - 1; i > 0; i--)\n"
         << "  {\n"
         << "    const int curr_byte = (mValue >> ((i) * 8)) & 0xff;\n"
         << "    const int next_byte = (mValue >> ((i - 1) * 8)) & 0xff;\n"
         << "    const int next_byte_msb = (next_byte >> 7);\n"
         << "\n"
         << "    if (curr_byte == 0 && next_byte_msb == 0 && try_drop)\n"
         << "    {\n"
         << "      // drop\n"
         << "    }\n"
         << "    else if (curr_byte == 0xff && next_byte_msb == 1 && try_drop)\n"
         << "    {\n"
         << "      // drop\n"
         << "    }\n"
         << "    else\n"
         << "    {\n"
         << "      buffer.push_back(curr_byte);\n"
         << "      try_drop = false;\n"
         << "    }\n"
         << "  }\n"
         << "\n"
         << "  buffer.push_back(mValue & 0xff);\n"
         << "\n"
         << "  buffer.at(length_index) = buffer.size() - length_index - 1;\n"
         << "\n"
         << "  return true;\n"
         << "}\n"
         << "bool\n"
         << mIdentifier << "::\n"
         << "DecodeBER(std::vector<uint8_t>& buffer)\n"
         << "{\n"
         << "  if (buffer.size() < 1 || buffer.at(0) != "
         << ((mIsConstructed << 5) | 2) << ")\n"
         << "  {\n"
         << "    return false;\n"
         << "  }\n"
         << "\n"
         << "  // Length\n"
         << "  if (buffer.size() < 2 || buffer.at(1) > 8)\n"
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
         << "  for (size_t i = 0; i < len; i++)\n"
         << "  {\n"
         << "    mValue |= (buffer.at(i + 2) << ((len - i - 1) * 8));\n"
         << "  }\n"
         << "\n"
         << "  for (size_t i = 0; i < 2 + len; i++)\n"
         << "  {\n"
         << "    buffer.erase(buffer.begin());\n"
         << "  }\n"
         << "\n"
         << "  return true;\n"
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
