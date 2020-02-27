#include "Exclusions.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Exclusions::
GetType() const
{
  return Production::EXCLUSIONS;
}

bool
Exclusions::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // Exclusions ::= EXCEPT Elements

  size_t starting_index = asnDataIndex;

  auto obj = "EXCEPT";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "Elements";
  LOG_START();
  auto elements =
    ProductionFactory::Get(Production::ELEMENTS);
  if (elements->Parse(asnData, asnDataIndex, endStop))
  {
    mElements = elements;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
