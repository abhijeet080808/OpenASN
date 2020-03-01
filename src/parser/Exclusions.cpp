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
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Exclusions");

  // Exclusions ::= EXCEPT Elements

  size_t starting_index = asnDataIndex;

  auto obj = "EXCEPT";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "Elements";
  LOG_START();
  auto elements =
    ProductionFactory::Get(Production::ELEMENTS);
  if (elements->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mElements = elements;
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
}
