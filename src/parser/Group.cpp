#include "Group.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Group::
GetType() const
{
  return Production::GROUP;
}

bool
Group::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Group");

  // Group ::= number

  size_t starting_index = asnDataIndex;

  auto obj = "Number";
  LOG_START();
  auto number =
    ProductionFactory::Get(Production::NUMBER);
  if (number->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mNumber = number;
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
