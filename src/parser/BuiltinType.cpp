#include "BuiltinType.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

Production
BuiltinType::
GetType() const
{
  return Production::BUILTIN_TYPE;
}

bool
BuiltinType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // BuiltinType ::=
  //   BitStringType
  // | BooleanType
  // | CharacterStringType
  // | ChoiceType
  // | DateType
  // | DateTimeType
  // | DurationType
  // | EmbeddedPDVType
  // | EnumeratedType
  // | ExternalType
  // | InstanceOfType
  // | IntegerType
  // | IRIType
  // | NullType
  // | ObjectClassFieldType
  // | ObjectIdentifierType
  // | OctetStringType
  // | RealType
  // | RelativeIRIType
  // | RelativeOIDType
  // | SequenceType
  // | SequenceOfType
  // | SetType
  // | SetOfType
  // | PrefixedType
  // | TimeType
  // | TimeOfDayType

  LOG_START("BitStringType", asnData);
  auto bit_string_type =
    ProductionFactory::Get(Production::BIT_STRING_TYPE);
  if (bit_string_type->Parse(asnData, endStop))
  {
    mBitStringType = bit_string_type;
    LOG_PASS("BitStringType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("BitStringType", asnData);
  }

  LOG_START("BooleanType", asnData);
  auto boolean_type =
    ProductionFactory::Get(Production::BOOLEAN_TYPE);
  if (boolean_type->Parse(asnData, endStop))
  {
    mBooleanType = boolean_type;
    LOG_PASS("BooleanType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("BooleanType", asnData);
  }

  LOG_START("IntegerType", asnData);
  auto integer_type =
    ProductionFactory::Get(Production::INTEGER_TYPE);
  if (integer_type->Parse(asnData, endStop))
  {
    mIntegerType = integer_type;
    LOG_PASS("IntegerType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("IntegerType", asnData);
  }

  LOG_START("SequenceType", asnData);
  auto sequence_type =
    ProductionFactory::Get(Production::SEQUENCE_TYPE);
  if (sequence_type->Parse(asnData, endStop))
  {
    mSequenceType = sequence_type;
    LOG_PASS("SequenceType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("SequenceType", asnData);
  }

  return false;
}
