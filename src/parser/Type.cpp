#include "Type.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Type::
GetType() const
{
  return Production::TYPE;
}

bool
Type::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Type");

  // Type ::= BuiltinType | ReferencedType | ConstrainedType

  // ConstrainedType ::=
  //   Type Constraint
  // | TypeWithConstraint

  // If Type first parses for ConstrainedType, it leads to a
  // circular dependency -
  // TypeAssignment>Type>ConstrainedType>Type>ContrainedType>Type...
  //
  // Val ::= BOOLEAN (FALSE) can lead to error if Type is not parsed as
  // ConstrainedType first but as BuiltinType. The Constraint remains
  // unparsed.

  // To avoid circular dependencies and let ConstrainedType work, redefined as -
  //
  // Type ::=
  //   BuiltinType ConstraintList
  // | BuiltinType
  // | ReferencedType ConstraintList
  // | ReferencedType
  // | TypeWithConstraint
  //
  // ConstraintList ::=
  //   Constraint
  // | ConstraintList Constraint

  size_t starting_index = asnDataIndex;

  auto obj = "BuiltinType";
  LOG_START();
  auto builtin_type =
    ProductionFactory::Get(Production::BUILTIN_TYPE);
  if (builtin_type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mBuiltinType = builtin_type;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
  }

  if (mBuiltinType)
  {
    obj = "ConstraintList";
    LOG_START();
    auto constraint_list =
      ProductionFactory::Get(Production::CONSTRAINT_LIST);
    if (constraint_list->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mConstraintList = constraint_list;
      LOG_PASS();
      parsePath.pop_back();
      return true;
    }
    else
    {
      LOG_FAIL();
      parsePath.pop_back();
      return true;
    }
  }

  obj = "ReferencedType";
  LOG_START();
  auto referenced_type =
    ProductionFactory::Get(Production::REFERENCED_TYPE);
  if (referenced_type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mReferencedType = referenced_type;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
  }

  if (mReferencedType)
  {
    obj = "ConstraintList";
    LOG_START();
    auto constraint_list =
      ProductionFactory::Get(Production::CONSTRAINT_LIST);
    if (constraint_list->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mConstraintList = constraint_list;
      LOG_PASS();
      parsePath.pop_back();
      return true;
    }
    else
    {
      LOG_FAIL();
      parsePath.pop_back();
      return true;
    }
  }

  // TypeWithConstraint

  asnDataIndex = starting_index;
  parsePath.pop_back();
  return false;
}
