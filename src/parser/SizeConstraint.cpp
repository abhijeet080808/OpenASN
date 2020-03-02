#include "SizeConstraint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SizeConstraint::
GetType() const
{
  return Production::SIZE_CONSTRAINT;
}

bool
SizeConstraint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("SizeConstraint");

  // SizeConstraint ::= SIZE Constraint
  //
  // TODO - Apply below logic here or in generator
  //
  // The "Constraint" specifies the permitted integer values for the length of
  // the specified values, and takes the form of any constraint which can be
  // applied to the following parent type: INTEGER (0 .. MAX)
  //
  // The "Constraint" shall use the "SubtypeConstraint" alternative of
  // "ConstraintSpec".
  //
  // Applicable constraints for INTEGER -
  // - SingleValue
  // - ContainedSubtype
  // - ValueRange

  size_t starting_index = asnDataIndex;

  auto obj = "SIZE";
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
