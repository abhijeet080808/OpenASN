#include "BuiltinType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
BuiltinType::
GetType() const
{
  return Production::BUILTIN_TYPE;
}

bool
BuiltinType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
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

  size_t starting_index = asnDataIndex;

  auto obj = "BitStringType";
  LOG_START();
  auto bit_string_type =
    ProductionFactory::Get(Production::BIT_STRING_TYPE);
  if (bit_string_type->Parse(asnData, asnDataIndex, endStop))
  {
    mBitStringType = bit_string_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "BooleanType";
  LOG_START();
  auto boolean_type =
    ProductionFactory::Get(Production::BOOLEAN_TYPE);
  if (boolean_type->Parse(asnData, asnDataIndex, endStop))
  {
    mBooleanType = boolean_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "CharacterStringType";
  LOG_START();
  auto character_string_type =
    ProductionFactory::Get(Production::CHARACTER_STRING_TYPE);
  if (character_string_type->Parse(asnData, asnDataIndex, endStop))
  {
    mBooleanType = boolean_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "ChoiceType";
  LOG_START();
  auto choice_type =
    ProductionFactory::Get(Production::CHOICE_TYPE);
  if (choice_type->Parse(asnData, asnDataIndex, endStop))
  {
    mChoiceType = choice_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "DateType";
  LOG_START();
  auto date_type =
    ProductionFactory::Get(Production::DATE_TYPE);
  if (date_type->Parse(asnData, asnDataIndex, endStop))
  {
    mDateType = date_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "DateTimeType";
  LOG_START();
  auto date_time_type =
    ProductionFactory::Get(Production::DATE_TIME_TYPE);
  if (date_time_type->Parse(asnData, asnDataIndex, endStop))
  {
    mDateTimeType = date_time_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "DurationType";
  LOG_START();
  auto duration_type =
    ProductionFactory::Get(Production::DURATION_TYPE);
  if (duration_type->Parse(asnData, asnDataIndex, endStop))
  {
    mDurationType = duration_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "EmbeddedPDVType";
  LOG_START();
  auto embedded_pdv_type =
    ProductionFactory::Get(Production::EMBEDDED_PDV_TYPE);
  if (embedded_pdv_type->Parse(asnData, asnDataIndex, endStop))
  {
    mEmbeddedPDVType = embedded_pdv_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "EnumeratedType";
  LOG_START();
  auto enumerated_type =
    ProductionFactory::Get(Production::ENUMERATED_TYPE);
  if (enumerated_type->Parse(asnData, asnDataIndex, endStop))
  {
    mEnumeratedType = enumerated_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "ExternalType";
  LOG_START();
  auto external_type =
    ProductionFactory::Get(Production::EXTERNAL_TYPE);
  if (external_type->Parse(asnData, asnDataIndex, endStop))
  {
    mExternalType = external_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "IntegerType";
  LOG_START();
  auto integer_type =
    ProductionFactory::Get(Production::INTEGER_TYPE);
  if (integer_type->Parse(asnData, asnDataIndex, endStop))
  {
    mIntegerType = integer_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "IRIType";
  LOG_START();
  auto iri_type =
    ProductionFactory::Get(Production::IRI_TYPE);
  if (iri_type->Parse(asnData, asnDataIndex, endStop))
  {
    mIRIType = iri_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "NullType";
  LOG_START();
  auto null_type =
    ProductionFactory::Get(Production::NULL_TYPE);
  if (null_type->Parse(asnData, asnDataIndex, endStop))
  {
    mNullType = null_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "ObjectIdentifierType";
  LOG_START();
  auto object_identifier_type =
    ProductionFactory::Get(Production::OBJECT_IDENTIFIER_TYPE);
  if (object_identifier_type->Parse(asnData, asnDataIndex, endStop))
  {
    mObjectIdentifierType = object_identifier_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "OctetStringType";
  LOG_START();
  auto octet_string_type =
    ProductionFactory::Get(Production::OCTET_STRING_TYPE);
  if (octet_string_type->Parse(asnData, asnDataIndex, endStop))
  {
    mOctetStringType = octet_string_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "PrefixedType";
  LOG_START();
  auto prefixed_type =
    ProductionFactory::Get(Production::PREFIXED_TYPE);
  if (prefixed_type->Parse(asnData, asnDataIndex, endStop))
  {
    mPrefixedType = prefixed_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "RealType";
  LOG_START();
  auto real_type =
    ProductionFactory::Get(Production::REAL_TYPE);
  if (real_type->Parse(asnData, asnDataIndex, endStop))
  {
    mRealType = real_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "RelativeIRIType";
  LOG_START();
  auto relative_iri_type =
    ProductionFactory::Get(Production::RELATIVE_IRI_TYPE);
  if (relative_iri_type->Parse(asnData, asnDataIndex, endStop))
  {
    mRelativeIRIType = relative_iri_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "RelativeOIDType";
  LOG_START();
  auto relative_oid_type =
    ProductionFactory::Get(Production::RELATIVE_OID_TYPE);
  if (relative_oid_type->Parse(asnData, asnDataIndex, endStop))
  {
    mRelativeOIDType = relative_oid_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "SequenceType";
  LOG_START();
  auto sequence_type =
    ProductionFactory::Get(Production::SEQUENCE_TYPE);
  if (sequence_type->Parse(asnData, asnDataIndex, endStop))
  {
    mSequenceType = sequence_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "SequenceOfType";
  LOG_START();
  auto sequence_of_type =
    ProductionFactory::Get(Production::SEQUENCE_OF_TYPE);
  if (sequence_of_type->Parse(asnData, asnDataIndex, endStop))
  {
    mSequenceOfType = sequence_of_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "SetType";
  LOG_START();
  auto set_type =
    ProductionFactory::Get(Production::SET_TYPE);
  if (set_type->Parse(asnData, asnDataIndex, endStop))
  {
    mSetType = set_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "SetOfType";
  LOG_START();
  auto set_of_type =
    ProductionFactory::Get(Production::SET_OF_TYPE);
  if (set_of_type->Parse(asnData, asnDataIndex, endStop))
  {
    mSetOfType = set_of_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "TimeType";
  LOG_START();
  auto time_type =
    ProductionFactory::Get(Production::TIME_TYPE);
  if (time_type->Parse(asnData, asnDataIndex, endStop))
  {
    mTimeType = time_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  asnDataIndex = starting_index;
  return false;
}
