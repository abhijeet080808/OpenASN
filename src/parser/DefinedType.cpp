#include "DefinedType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DefinedType::
GetType() const
{
  return Production::DEFINED_TYPE;
}

bool
DefinedType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("DefinedType");

  // DefinedType ::=
  //   ExternalTypeReference
  // | typereference
  // | ParameterizedType
  // | ParameterizedValueSetType

  size_t starting_index = asnDataIndex;

  auto obj = "ExternalTypeReference";
  LOG_START();
  auto external_type_reference =
    ProductionFactory::Get(Production::EXTERNAL_TYPE_REFERENCE);
  if (external_type_reference->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mExternalTypeReference = external_type_reference;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "TypeReference";
  LOG_START();
  auto type_reference =
    ProductionFactory::Get(Production::TYPE_REFERENCE);
  if (type_reference->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mTypeReference = type_reference;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  // ParameterizedType
  // ParameterizedValueSetType
}
