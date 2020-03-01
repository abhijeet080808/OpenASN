#include "Assignment.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Assignment::
GetType() const
{
  return Production::ASSIGNMENT;
}

bool
Assignment::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Assignment");

  // Assignment ::=
  //   TypeAssignment
  // | ValueAssignment
  // | XMLValueAssignment
  // | ValueSetTypeAssignment
  // | ObjectClassAssignment
  // | ObjectAssignment
  // | ObjectSetAssignment
  // | ParameterizedAssignment

  size_t starting_index = asnDataIndex;

  auto obj = "TypeAssignment";
  LOG_START();
  auto type_assignment =
    ProductionFactory::Get(Production::TYPE_ASSIGNMENT);
  if (type_assignment->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mTypeAssignment = type_assignment;
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
