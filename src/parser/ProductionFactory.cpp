#include "ProductionFactory.hh"

#include "AlternativeTypeList.hh"
#include "AlternativeTypeLists.hh"
#include "Assignment.hh"
#include "AssignmentList.hh"
#include "BitStringType.hh"
#include "BMPString.hh"
#include "BooleanType.hh"
#include "BuiltinType.hh"
#include "CharacterStringType.hh"
#include "ChoiceType.hh"
#include "ComponentType.hh"
#include "ComponentTypeList.hh"
#include "ComponentTypeLists.hh"
#include "DateType.hh"
#include "DateTimeType.hh"
#include "DefinitiveIdentification.hh"
#include "DefinitiveOID.hh"
#include "DefinitiveObjIdComponent.hh"
#include "DefinitiveObjIdComponentList.hh"
#include "DurationType.hh"
#include "EmbeddedPDVType.hh"
#include "EnumeratedType.hh"
#include "Enumeration.hh"
#include "EnumerationItem.hh"
#include "Enumerations.hh"
#include "ExternalType.hh"
#include "GeneralString.hh"
#include "GraphicString.hh"
#include "IA5String.hh"
#include "Identifier.hh"
#include "IntegerType.hh"
#include "IRIType.hh"
#include "ISO646String.hh"
#include "ModuleBody.hh"
#include "ModuleDefinition.hh"
#include "ModuleIdentifier.hh"
#include "NameForm.hh"
#include "NamedBit.hh"
#include "NamedBitList.hh"
#include "NamedNumber.hh"
#include "NamedNumberList.hh"
#include "NamedType.hh"
#include "NegativeNumber.hh"
#include "NullType.hh"
#include "Number.hh"
#include "NumericString.hh"
#include "PrintableString.hh"
#include "RestrictedCharacterStringType.hh"
#include "RootAlternativeTypeList.hh"
#include "RootComponentTypeList.hh"
#include "RootEnumeration.hh"
#include "SequenceType.hh"
#include "SignedNumber.hh"
#include "T61String.hh"
#include "TeletexString.hh"
#include "Type.hh"
#include "TypeAssignment.hh"
#include "TypeReference.hh"
#include "UniversalString.hh"
#include "UnrestrictedCharacterStringType.hh"
#include "UTF8String.hh"
#include "VideotexString.hh"
#include "VisibleString.hh"

#include <cassert>

using namespace OpenASN;

std::shared_ptr<IProduction>
ProductionFactory::
Get(Production production)
{
  switch (production)
  {
    case Production::ALTERNATIVE_TYPE_LIST:
      return std::make_shared<AlternativeTypeList>();

    case Production::ALTERNATIVE_TYPE_LISTS:
      return std::make_shared<AlternativeTypeLists>();

    case Production::ASSIGNMENT:
      return std::make_shared<Assignment>();

    case Production::ASSIGNMENT_LIST:
      return std::make_shared<AssignmentList>();

    case Production::BIT_STRING_TYPE:
      return std::make_shared<BitStringType>();

    case Production::BMP_STRING:
      return std::make_shared<BMPString>();

    case Production::BOOLEAN_TYPE:
      return std::make_shared<BooleanType>();

    case Production::BUILTIN_TYPE:
      return std::make_shared<BuiltinType>();

    case Production::CHARACTER_STRING_TYPE:
      return std::make_shared<CharacterStringType>();

    case Production::CHOICE_TYPE:
      return std::make_shared<ChoiceType>();

    case Production::COMPONENT_TYPE:
      return std::make_shared<ComponentType>();

    case Production::COMPONENT_TYPE_LIST:
      return std::make_shared<ComponentTypeList>();

    case Production::COMPONENT_TYPE_LISTS:
      return std::make_shared<ComponentTypeLists>();

    case Production::DATE_TYPE:
      return std::make_shared<DateType>();

    case Production::DATE_TIME_TYPE:
      return std::make_shared<DateTimeType>();

    case Production::DEFINITIVE_IDENTIFICATION:
      return std::make_shared<DefinitiveIdentification>();

    case Production::DEFINITIVE_OID:
      return std::make_shared<DefinitiveOID>();

    case Production::DEFINITIVE_OBJ_ID_COMPONENT:
      return std::make_shared<DefinitiveObjIdComponent>();

    case Production::DEFINITIVE_OBJ_ID_COMPONENT_LIST:
      return std::make_shared<DefinitiveObjIdComponentList>();

    case Production::DURATION_TYPE:
      return std::make_shared<DurationType>();

    case Production::EMBEDDED_PDV_TYPE:
      return std::make_shared<EmbeddedPDVType>();

    case Production::ENUMERATED_TYPE:
      return std::make_shared<EnumeratedType>();

    case Production::ENUMERATION:
      return std::make_shared<Enumeration>();

    case Production::ENUMERATION_ITEM:
      return std::make_shared<EnumerationItem>();

    case Production::ENUMERATIONS:
      return std::make_shared<Enumerations>();

    case Production::EXTERNAL_TYPE:
      return std::make_shared<ExternalType>();

    case Production::GENERAL_STRING:
      return std::make_shared<GeneralString>();

    case Production::GRAPHIC_STRING:
      return std::make_shared<GraphicString>();

    case Production::IA5_STRING:
      return std::make_shared<IA5String>();

    case Production::IDENTIFIER:
      return std::make_shared<Identifier>();

    case Production::INTEGER_TYPE:
      return std::make_shared<IntegerType>();

    case Production::IRI_TYPE:
      return std::make_shared<IRIType>();

    case Production::ISO646_STRING:
      return std::make_shared<ISO646String>();

    case Production::MODULE_BODY:
      return std::make_shared<ModuleBody>();

    case Production::MODULE_DEFINITION:
      return std::make_shared<ModuleDefinition>();

    case Production::MODULE_IDENTIFIER:
      return std::make_shared<ModuleIdentifier>();

    case Production::MODULE_REFERENCE:
      return std::make_shared<ModuleReference>();

    case Production::NAME_FORM:
      return std::make_shared<NameForm>();

    case Production::NAMED_BIT:
      return std::make_shared<NamedBit>();

    case Production::NAMED_BIT_LIST:
      return std::make_shared<NamedBitList>();

    case Production::NAMED_NUMBER:
      return std::make_shared<NamedNumber>();

    case Production::NAMED_NUMBER_LIST:
      return std::make_shared<NamedNumberList>();

    case Production::NAMED_TYPE:
      return std::make_shared<NamedType>();

    case Production::NEGATIVE_NUMBER:
      return std::make_shared<NegativeNumber>();

    case Production::NULL_TYPE:
      return std::make_shared<NullType>();

    case Production::NUMBER:
      return std::make_shared<Number>();

    case Production::NUMERIC_STRING:
      return std::make_shared<NumericString>();

    case Production::PRINTABLE_STRING:
      return std::make_shared<PrintableString>();

    case Production::ROOT_ALTERNATIVE_TYPE_LIST:
      return std::make_shared<RootAlternativeTypeList>();

    case Production::ROOT_COMPONENT_TYPE_LIST:
      return std::make_shared<RootComponentTypeList>();

    case Production::ROOT_ENUMERATION:
      return std::make_shared<RootEnumeration>();

    case Production::RESTRICTED_CHARACTER_STRING_TYPE:
      return std::make_shared<RestrictedCharacterStringType>();

    case Production::SEQUENCE_TYPE:
      return std::make_shared<SequenceType>();

    case Production::SIGNED_NUMBER:
      return std::make_shared<SignedNumber>();

    case Production::T61_STRING:
      return std::make_shared<T61String>();

    case Production::TELETEX_STRING:
      return std::make_shared<TeletexString>();

    case Production::TYPE:
      return std::make_shared<Type>();

    case Production::TYPE_ASSIGNMENT:
      return std::make_shared<TypeAssignment>();

    case Production::TYPE_REFERENCE:
      return std::make_shared<TypeReference>();

    case Production::UNIVERSAL_STRING:
      return std::make_shared<UniversalString>();

    case Production::UNRESTRICTED_CHARACTER_STRING_TYPE:
      return std::make_shared<UnrestrictedCharacterStringType>();

    case Production::UTF8_STRING:
      return std::make_shared<UTF8String>();

    case Production::VALUE_REFERENCE:
      return std::make_shared<ValueReference>();

    case Production::VIDEOTEX_STRING:
      return std::make_shared<VideotexString>();

    case Production::VISIBLE_STRING:
      return std::make_shared<VisibleString>();

    default:
      assert(false);
      return nullptr;
  }
}
