#include "TypeConstraints.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
TypeConstraints::
GetType() const
{
  return Production::TYPE_CONSTRAINTS;
}

bool
TypeConstraints::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("TypeConstraints");

  // TypeConstraints ::=
  //   NamedConstraint
  // | NamedConstraint "," TypeConstraints

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "NamedConstraint";
    LOG_START();
    auto named_constraint =
      ProductionFactory::Get(Production::NAMED_CONSTRAINT);
    if (named_constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mNamedConstraint.push_back(named_constraint);
      LOG_PASS();
    }
    else
    {
      asnDataIndex = starting_index;
      LOG_FAIL();
      parsePath.pop_back();
      return false;
    }

    obj = ",";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      ++asnDataIndex;
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mNamedConstraint.empty())
  {
    asnDataIndex = starting_index;
    parsePath.pop_back();
    return false;
  }
  else
  {
    parsePath.pop_back();
    return true;
  }
}
