#include "PermittedAlphabet.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
PermittedAlphabet::
GetType() const
{
  return Production::PERMITTED_ALPHABET;
}

bool
PermittedAlphabet::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("PermittedAlphabet");

  // PermittedAlphabet ::= FROM Constraint

  size_t starting_index = asnDataIndex;

  auto obj = "FROM";
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

  // 51.7.3 TODO - Only allow Constraints - SingleValue, ContainedSubtype,
  // ValueRange, and SizeConstraint
  obj = "Constraint";
  LOG_START();
  auto constraint =
    ProductionFactory::Get(Production::CONSTRAINT);
  if (constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mConstraint = constraint;
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
