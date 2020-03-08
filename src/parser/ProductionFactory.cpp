#include "ProductionFactory.hh"

#include "Absent.hh"
#include "AdditionalElementSetSpec.hh"
#include "AlternativeTypeList.hh"
#include "AlternativeTypeLists.hh"
#include "Application.hh"
#include "Assignment.hh"
#include "AssignmentList.hh"
#include "BitStringType.hh"
#include "BMPString.hh"
#include "BooleanType.hh"
#include "BooleanValue.hh"
#include "BuiltinType.hh"
#include "BuiltinValue.hh"
#include "CharacterStringType.hh"
#include "ChoiceType.hh"
#include "Class.hh"
#include "ClassNumber.hh"
#include "ComponentConstraint.hh"
#include "ComponentType.hh"
#include "ComponentTypeList.hh"
#include "ComponentTypeLists.hh"
#include "Constraint.hh"
#include "ConstraintList.hh"
#include "ConstraintSpec.hh"
#include "ContainedSubtype.hh"
#include "DateType.hh"
#include "DateTimeType.hh"
#include "DefinedType.hh"
#include "DefinedValue.hh"
#include "DefinitiveIdentification.hh"
#include "DefinitiveOID.hh"
#include "DefinitiveObjIdComponent.hh"
#include "DefinitiveObjIdComponentList.hh"
#include "DurationType.hh"
#include "Elements.hh"
#include "ElementSetSpec.hh"
#include "ElementSetSpecs.hh"
#include "Ellipsis.hh"
#include "EmbeddedPDVType.hh"
#include "EncodingPrefix.hh"
#include "EncodingPrefixedType.hh"
#include "EncodingReference.hh"
#include "EncodingReferencePrime.hh"
#include "EnumeratedType.hh"
#include "Enumeration.hh"
#include "EnumerationItem.hh"
#include "Enumerations.hh"
#include "ExceptionIdentification.hh"
#include "ExceptionSpec.hh"
#include "Exclusions.hh"
#include "Explicit.hh"
#include "ExternalType.hh"
#include "ExternalTypeReference.hh"
#include "ExternalValueReference.hh"
#include "FullSpecification.hh"
#include "GeneralizedTime.hh"
#include "GeneralString.hh"
#include "GraphicString.hh"
#include "IA5String.hh"
#include "Identifier.hh"
#include "Implicit.hh"
#include "Includes.hh"
#include "InnerTypeConstraints.hh"
#include "IntegerType.hh"
#include "IntegerValue.hh"
#include "IntersectionElements.hh"
#include "Intersections.hh"
#include "IRIType.hh"
#include "ISO646String.hh"
#include "LessThan.hh"
#include "LowerEndpoint.hh"
#include "LowerEndValue.hh"
#include "Max.hh"
#include "Min.hh"
#include "ModuleBody.hh"
#include "ModuleDefinition.hh"
#include "ModuleIdentifier.hh"
#include "MultipleTypeConstraints.hh"
#include "NameForm.hh"
#include "NamedBit.hh"
#include "NamedBitList.hh"
#include "NamedConstraint.hh"
#include "NamedNumber.hh"
#include "NamedNumberList.hh"
#include "NamedType.hh"
#include "NegativeNumber.hh"
#include "NullType.hh"
#include "Number.hh"
#include "NumericString.hh"
#include "ObjectDescriptor.hh"
#include "ObjectIdentifierType.hh"
#include "OctetStringType.hh"
#include "Optional.hh"
#include "PartialSpecification.hh"
#include "PatternConstraint.hh"
#include "PermittedAlphabet.hh"
#include "PrefixedType.hh"
#include "PresenceConstraint.hh"
#include "Present.hh"
#include "PrintableString.hh"
#include "Private.hh"
#include "RealType.hh"
#include "ReferencedType.hh"
#include "RelativeIRIType.hh"
#include "RelativeOIDType.hh"
#include "RestrictedCharacterStringType.hh"
#include "RootAlternativeTypeList.hh"
#include "RootComponentTypeList.hh"
#include "RootElementSetSpec.hh"
#include "RootEnumeration.hh"
#include "SelectionType.hh"
#include "SequenceType.hh"
#include "SequenceOfType.hh"
#include "SetType.hh"
#include "SetOfType.hh"
#include "SignedNumber.hh"
#include "SingleTypeConstraint.hh"
#include "SingleValue.hh"
#include "SizeConstraint.hh"
#include "SubtypeConstraint.hh"
#include "SubtypeElements.hh"
#include "Tag.hh"
#include "TaggedType.hh"
#include "T61String.hh"
#include "TeletexString.hh"
#include "TimeOfDayType.hh"
#include "TimeType.hh"
#include "Type.hh"
#include "TypeAssignment.hh"
#include "TypeConstraint.hh"
#include "TypeConstraints.hh"
#include "TypeReference.hh"
#include "Unions.hh"
#include "Universal.hh"
#include "UniversalString.hh"
#include "UnrestrictedCharacterStringType.hh"
#include "UpperEndpoint.hh"
#include "UpperEndValue.hh"
#include "UsefulType.hh"
#include "UTCTime.hh"
#include "UTF8String.hh"
#include "Value.hh"
#include "ValueConstraint.hh"
#include "ValueRange.hh"
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
    case Production::ABSENT:
      return std::make_shared<Absent>();

    case Production::ADDITIONAL_ELEMENT_SET_SPEC:
      return std::make_shared<AdditionalElementSetSpec>();

    case Production::ALTERNATIVE_TYPE_LIST:
      return std::make_shared<AlternativeTypeList>();

    case Production::ALTERNATIVE_TYPE_LISTS:
      return std::make_shared<AlternativeTypeLists>();

    case Production::APPLICATION:
      return std::make_shared<Application>();

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

    case Production::BOOLEAN_VALUE:
      return std::make_shared<BooleanValue>();

    case Production::BUILTIN_TYPE:
      return std::make_shared<BuiltinType>();

    case Production::BUILTIN_VALUE:
      return std::make_shared<BuiltinValue>();

    case Production::CHARACTER_STRING_TYPE:
      return std::make_shared<CharacterStringType>();

    case Production::CHOICE_TYPE:
      return std::make_shared<ChoiceType>();

    case Production::CLASS:
      return std::make_shared<Class>();

    case Production::CLASS_NUMBER:
      return std::make_shared<ClassNumber>();

    case Production::COMPONENT_CONSTRAINT:
      return std::make_shared<ComponentConstraint>();

    case Production::COMPONENT_TYPE:
      return std::make_shared<ComponentType>();

    case Production::COMPONENT_TYPE_LIST:
      return std::make_shared<ComponentTypeList>();

    case Production::COMPONENT_TYPE_LISTS:
      return std::make_shared<ComponentTypeLists>();

    case Production::CONSTRAINT:
      return std::make_shared<Constraint>();

    case Production::CONSTRAINT_LIST:
      return std::make_shared<ConstraintList>();

    case Production::CONSTRAINT_SPEC:
      return std::make_shared<ConstraintSpec>();

    case Production::CONTAINED_SUBTYPE:
      return std::make_shared<ContainedSubtype>();

    case Production::DATE_TYPE:
      return std::make_shared<DateType>();

    case Production::DATE_TIME_TYPE:
      return std::make_shared<DateTimeType>();

    case Production::DEFINED_TYPE:
      return std::make_shared<DefinedType>();

    case Production::DEFINED_VALUE:
      return std::make_shared<DefinedValue>();

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

    case Production::ELEMENTS:
      return std::make_shared<Elements>();

    case Production::ELEMENT_SET_SPEC:
      return std::make_shared<ElementSetSpec>();

    case Production::ELEMENT_SET_SPECS:
      return std::make_shared<ElementSetSpecs>();

    case Production::ELLIPSIS:
      return std::make_shared<Ellipsis>();

    case Production::EMBEDDED_PDV_TYPE:
      return std::make_shared<EmbeddedPDVType>();

    case Production::ENCODING_PREFIX:
      return std::make_shared<EncodingPrefix>();

    case Production::ENCODING_PREFIXED_TYPE:
      return std::make_shared<EncodingPrefixedType>();

    case Production::ENCODING_REFERENCE:
      return std::make_shared<EncodingReference>();

    case Production::ENCODING_REFERENCE_PRIME:
      return std::make_shared<EncodingReferencePrime>();

    case Production::ENUMERATED_TYPE:
      return std::make_shared<EnumeratedType>();

    case Production::ENUMERATION:
      return std::make_shared<Enumeration>();

    case Production::ENUMERATION_ITEM:
      return std::make_shared<EnumerationItem>();

    case Production::ENUMERATIONS:
      return std::make_shared<Enumerations>();

    case Production::EXCEPTION_IDENTIFICATION:
      return std::make_shared<ExceptionIdentification>();

    case Production::EXCEPTION_SPEC:
      return std::make_shared<ExceptionSpec>();

    case Production::EXCLUSIONS:
      return std::make_shared<Exclusions>();

    case Production::EXPLICIT:
      return std::make_shared<Explicit>();

    case Production::EXTERNAL_TYPE:
      return std::make_shared<ExternalType>();

    case Production::EXTERNAL_TYPE_REFERENCE:
      return std::make_shared<ExternalTypeReference>();

    case Production::EXTERNAL_VALUE_REFERENCE:
      return std::make_shared<ExternalValueReference>();

    case Production::FULL_SPECIFICATION:
      return std::make_shared<FullSpecification>();

    case Production::GENERALIZED_TIME:
      return std::make_shared<GeneralizedTime>();

    case Production::GENERAL_STRING:
      return std::make_shared<GeneralString>();

    case Production::GRAPHIC_STRING:
      return std::make_shared<GraphicString>();

    case Production::IA5_STRING:
      return std::make_shared<IA5String>();

    case Production::IDENTIFIER:
      return std::make_shared<Identifier>();

    case Production::IMPLICIT:
      return std::make_shared<Implicit>();

    case Production::INCLUDES:
      return std::make_shared<Includes>();

    case Production::INNER_TYPE_CONSTRAINTS:
      return std::make_shared<InnerTypeConstraints>();

    case Production::INTEGER_TYPE:
      return std::make_shared<IntegerType>();

    case Production::INTEGER_VALUE:
      return std::make_shared<IntegerValue>();

    case Production::INTERSECTION_ELEMENTS:
      return std::make_shared<IntersectionElements>();

    case Production::INTERSECTIONS:
      return std::make_shared<Intersections>();

    case Production::IRI_TYPE:
      return std::make_shared<IRIType>();

    case Production::ISO646_STRING:
      return std::make_shared<ISO646String>();

    case Production::LESS_THAN:
      return std::make_shared<LessThan>();

    case Production::LOWER_ENDPOINT:
      return std::make_shared<LowerEndpoint>();

    case Production::LOWER_END_VALUE:
      return std::make_shared<LowerEndValue>();

    case Production::MAX:
      return std::make_shared<Max>();

    case Production::MIN:
      return std::make_shared<Min>();

    case Production::MODULE_BODY:
      return std::make_shared<ModuleBody>();

    case Production::MODULE_DEFINITION:
      return std::make_shared<ModuleDefinition>();

    case Production::MODULE_IDENTIFIER:
      return std::make_shared<ModuleIdentifier>();

    case Production::MULTIPLE_TYPE_CONSTRAINTS:
      return std::make_shared<MultipleTypeConstraints>();

    case Production::MODULE_REFERENCE:
      return std::make_shared<ModuleReference>();

    case Production::NAME_FORM:
      return std::make_shared<NameForm>();

    case Production::NAMED_BIT:
      return std::make_shared<NamedBit>();

    case Production::NAMED_BIT_LIST:
      return std::make_shared<NamedBitList>();

    case Production::NAMED_CONSTRAINT:
      return std::make_shared<NamedConstraint>();

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

    case Production::OBJECT_DESCRIPTOR:
      return std::make_shared<ObjectDescriptor>();

    case Production::OBJECT_IDENTIFIER_TYPE:
      return std::make_shared<ObjectIdentifierType>();

    case Production::OCTET_STRING_TYPE:
      return std::make_shared<OctetStringType>();

    case Production::OPTIONAL:
      return std::make_shared<Optional>();

    case Production::PARTIAL_SPECIFICATION:
      return std::make_shared<PartialSpecification>();

    case Production::PATTERN_CONSTRAINT:
      return std::make_shared<PatternConstraint>();

    case Production::PERMITTED_ALPHABET:
      return std::make_shared<PermittedAlphabet>();

    case Production::PREFIXED_TYPE:
      return std::make_shared<PrefixedType>();

    case Production::PRESENCE_CONSTRAINT:
      return std::make_shared<PresenceConstraint>();

    case Production::PRESENT:
      return std::make_shared<Present>();

    case Production::PRINTABLE_STRING:
      return std::make_shared<PrintableString>();

    case Production::PRIVATE:
      return std::make_shared<Private>();

    case Production::REAL_TYPE:
      return std::make_shared<RealType>();

    case Production::REFERENCED_TYPE:
      return std::make_shared<ReferencedType>();

    case Production::RELATIVE_IRI_TYPE:
      return std::make_shared<RelativeIRIType>();

    case Production::RELATIVE_OID_TYPE:
      return std::make_shared<RelativeOIDType>();

    case Production::ROOT_ALTERNATIVE_TYPE_LIST:
      return std::make_shared<RootAlternativeTypeList>();

    case Production::ROOT_COMPONENT_TYPE_LIST:
      return std::make_shared<RootComponentTypeList>();

    case Production::ROOT_ELEMENT_SET_SPEC:
      return std::make_shared<RootElementSetSpec>();

    case Production::ROOT_ENUMERATION:
      return std::make_shared<RootEnumeration>();

    case Production::RESTRICTED_CHARACTER_STRING_TYPE:
      return std::make_shared<RestrictedCharacterStringType>();

    case Production::SELECTION_TYPE:
      return std::make_shared<SelectionType>();

    case Production::SEQUENCE_TYPE:
      return std::make_shared<SequenceType>();

    case Production::SEQUENCE_OF_TYPE:
      return std::make_shared<SequenceOfType>();

    case Production::SET_TYPE:
      return std::make_shared<SetType>();

    case Production::SET_OF_TYPE:
      return std::make_shared<SetOfType>();

    case Production::SIGNED_NUMBER:
      return std::make_shared<SignedNumber>();

    case Production::SINGLE_TYPE_CONSTRAINT:
      return std::make_shared<SingleTypeConstraint>();

    case Production::SINGLE_VALUE:
      return std::make_shared<SingleValue>();

    case Production::SIZE_CONSTRAINT:
      return std::make_shared<SizeConstraint>();

    case Production::SUBTYPE_CONSTRAINT:
      return std::make_shared<SubtypeConstraint>();

    case Production::SUBTYPE_ELEMENTS:
      return std::make_shared<SubtypeElements>();

    case Production::TAG:
      return std::make_shared<Tag>();

    case Production::TAGGED_TYPE:
      return std::make_shared<TaggedType>();

    case Production::T61_STRING:
      return std::make_shared<T61String>();

    case Production::TELETEX_STRING:
      return std::make_shared<TeletexString>();

    case Production::TIME_OF_DAY_TYPE:
      return std::make_shared<TimeOfDayType>();

    case Production::TIME_TYPE:
      return std::make_shared<TimeType>();

    case Production::TYPE:
      return std::make_shared<Type>();

    case Production::TYPE_ASSIGNMENT:
      return std::make_shared<TypeAssignment>();

    case Production::TYPE_CONSTRAINT:
      return std::make_shared<TypeConstraint>();

    case Production::TYPE_CONSTRAINTS:
      return std::make_shared<TypeConstraints>();

    case Production::TYPE_REFERENCE:
      return std::make_shared<TypeReference>();

    case Production::UNIONS:
      return std::make_shared<Unions>();

    case Production::UNIVERSAL:
      return std::make_shared<Universal>();

    case Production::UNIVERSAL_STRING:
      return std::make_shared<UniversalString>();

    case Production::UNRESTRICTED_CHARACTER_STRING_TYPE:
      return std::make_shared<UnrestrictedCharacterStringType>();

    case Production::UPPER_ENDPOINT:
      return std::make_shared<UpperEndpoint>();

    case Production::UPPER_END_VALUE:
      return std::make_shared<UpperEndValue>();

    case Production::USEFUL_TYPE:
      return std::make_shared<UsefulType>();

    case Production::UTC_TIME:
      return std::make_shared<UTCTime>();

    case Production::UTF8_STRING:
      return std::make_shared<UTF8String>();

    case Production::VALUE:
      return std::make_shared<Value>();

    case Production::VALUE_CONSTRAINT:
      return std::make_shared<ValueConstraint>();

    case Production::VALUE_RANGE:
      return std::make_shared<ValueRange>();

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
