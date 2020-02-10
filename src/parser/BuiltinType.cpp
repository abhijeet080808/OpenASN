#include "BuiltinType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

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

  LOG_START("BooleanType", asnData);
  BooleanType boolean_type;
  if (boolean_type.Parse(asnData, endStop))
  {
    mBooleanType = boolean_type;
    LOG_PASS("BooleanType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("BooleanType", asnData);
  }

  LOG_START("SequenceType", asnData);
  SequenceType sequence_type;
  if (sequence_type.Parse(asnData, endStop))
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
