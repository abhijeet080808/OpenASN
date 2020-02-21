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

  LOG_START("CharacterStringType", asnData);
  auto character_string_type =
    ProductionFactory::Get(Production::CHARACTER_STRING_TYPE);
  if (character_string_type->Parse(asnData, endStop))
  {
    mBooleanType = boolean_type;
    LOG_PASS("CharacterStringType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("CharacterStringType", asnData);
  }

  LOG_START("ChoiceType", asnData);
  auto choice_type =
    ProductionFactory::Get(Production::CHOICE_TYPE);
  if (choice_type->Parse(asnData, endStop))
  {
    mChoiceType = choice_type;
    LOG_PASS("ChoiceType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("ChoiceType", asnData);
  }

  LOG_START("DateType", asnData);
  auto date_type =
    ProductionFactory::Get(Production::DATE_TYPE);
  if (date_type->Parse(asnData, endStop))
  {
    mDateType = date_type;
    LOG_PASS("DateType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("DateType", asnData);
  }

  LOG_START("DateTimeType", asnData);
  auto date_time_type =
    ProductionFactory::Get(Production::DATE_TIME_TYPE);
  if (date_time_type->Parse(asnData, endStop))
  {
    mDateTimeType = date_time_type;
    LOG_PASS("DateTimeType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("DateTimeType", asnData);
  }

  LOG_START("DurationType", asnData);
  auto duration_type =
    ProductionFactory::Get(Production::DURATION_TYPE);
  if (duration_type->Parse(asnData, endStop))
  {
    mDurationType = duration_type;
    LOG_PASS("DurationType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("DurationType", asnData);
  }

  LOG_START("EmbeddedPDVType", asnData);
  auto embedded_pdv_type =
    ProductionFactory::Get(Production::EMBEDDED_PDV_TYPE);
  if (embedded_pdv_type->Parse(asnData, endStop))
  {
    mEmbeddedPDVType = embedded_pdv_type;
    LOG_PASS("EmbeddedPDVType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("EmbeddedPDVType", asnData);
  }

  LOG_START("EnumeratedType", asnData);
  auto enumerated_type =
    ProductionFactory::Get(Production::ENUMERATED_TYPE);
  if (enumerated_type->Parse(asnData, endStop))
  {
    mEnumeratedType = enumerated_type;
    LOG_PASS("EnumeratedType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("EnumeratedType", asnData);
  }

  LOG_START("ExternalType", asnData);
  auto external_type =
    ProductionFactory::Get(Production::EXTERNAL_TYPE);
  if (external_type->Parse(asnData, endStop))
  {
    mExternalType = external_type;
    LOG_PASS("ExternalType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("ExternalType", asnData);
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

  LOG_START("IRIType", asnData);
  auto iri_type =
    ProductionFactory::Get(Production::IRI_TYPE);
  if (iri_type->Parse(asnData, endStop))
  {
    mIRIType = iri_type;
    LOG_PASS("IRIType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("IRIType", asnData);
  }

  LOG_START("NullType", asnData);
  auto null_type =
    ProductionFactory::Get(Production::NULL_TYPE);
  if (null_type->Parse(asnData, endStop))
  {
    mNullType = null_type;
    LOG_PASS("NullType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("NullType", asnData);
  }

  LOG_START("ObjectIdentifierType", asnData);
  auto object_identifier_type =
    ProductionFactory::Get(Production::OBJECT_IDENTIFIER_TYPE);
  if (object_identifier_type->Parse(asnData, endStop))
  {
    mObjectIdentifierType = object_identifier_type;
    LOG_PASS("ObjectIdentifierType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("ObjectIdentifierType", asnData);
  }

  LOG_START("OctetStringType", asnData);
  auto octet_string_type =
    ProductionFactory::Get(Production::OCTET_STRING_TYPE);
  if (octet_string_type->Parse(asnData, endStop))
  {
    mOctetStringType = octet_string_type;
    LOG_PASS("OctetStringType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("OctetStringType", asnData);
  }

  LOG_START("RealType", asnData);
  auto real_type =
    ProductionFactory::Get(Production::REAL_TYPE);
  if (real_type->Parse(asnData, endStop))
  {
    mRealType = real_type;
    LOG_PASS("RealType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("RealType", asnData);
  }

  LOG_START("RelativeIRIType", asnData);
  auto relative_iri_type =
    ProductionFactory::Get(Production::RELATIVE_IRI_TYPE);
  if (relative_iri_type->Parse(asnData, endStop))
  {
    mRelativeIRIType = relative_iri_type;
    LOG_PASS("RelativeIRIType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("RelativeIRIType", asnData);
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
