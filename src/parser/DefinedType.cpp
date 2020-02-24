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
      std::vector<std::string>& endStop)
{
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
  if (external_type_reference->Parse(asnData, asnDataIndex, endStop))
  {
    mExternalTypeReference = external_type_reference;
    LOG_PASS();
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
  if (type_reference->Parse(asnData, asnDataIndex, endStop))
  {
    mTypeReference = type_reference;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  // ParameterizedType
  // ParameterizedValueSetType
}
