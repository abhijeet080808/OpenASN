#include "ReferencedType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ReferencedType::
GetType() const
{
  return Production::REFERENCED_TYPE;
}

bool
ReferencedType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ReferencedType ::=
  //   DefinedType
  // | UsefulType
  // | SelectionType
  // | TypeFromObject
  // | ValueSetFromObjects

  size_t starting_index = asnDataIndex;

  auto obj = "DefinedType";
  LOG_START();
  auto defined_type =
    ProductionFactory::Get(Production::DEFINED_TYPE);
  if (defined_type->Parse(asnData, asnDataIndex, endStop))
  {
    mDefinedType = defined_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "UsefulType";
  LOG_START();
  auto useful_type =
    ProductionFactory::Get(Production::USEFUL_TYPE);
  if (useful_type->Parse(asnData, asnDataIndex, endStop))
  {
    mUsefulType = useful_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  asnDataIndex = starting_index;
  return false;
}
