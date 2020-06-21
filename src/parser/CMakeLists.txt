set(LIB_NAME parser)

set(GEN_PARSER_SOURCES
  ABSENT.cpp
  AdditionalElementSetSpec.cpp
  AdditionalEnumeration.cpp
  ALL.cpp
  AlternativeTypeList.cpp
  AlternativeTypeLists.cpp
  APPLICATION.cpp
  ArcIdentifier.cpp
  ASN_INCLUDES.cpp
  ASN_IDENTIFIER.cpp
  ASN_NULL.cpp
  Assignment.cpp
  AssignmentList.cpp
  AUTOMATIC.cpp
  BEGIN.cpp
  BIT.cpp
  BitStringType.cpp
  BitStringValue.cpp
  BMPString.cpp
  BOOLEAN.cpp
  BooleanType.cpp
  BooleanValue.cpp
  BuiltinType.cpp
  BuiltinValue.cpp
  Cell.cpp
  CHARACTER.cpp
  CharacterStringList.cpp
  CharacterStringType.cpp
  CharacterStringValue.cpp
  CharsDefn.cpp
  CharSyms.cpp
  CHOICE.cpp
  ChoiceType.cpp
  ChoiceValue.cpp
  Class.cpp
  ClassNumber.cpp
  COMPONENT.cpp
  ComponentConstraint.cpp
  ComponentId.cpp
  COMPONENTS.cpp
  ComponentType.cpp
  ComponentTypeList.cpp
  ComponentTypeLists.cpp
  ComponentValueList.cpp
  CONTAINING.cpp
  Constraint.cpp
  ConstraintList.cpp
  ConstraintSpec.cpp
  ContainedSubtype.cpp
  DATE.cpp
  DATE_TIME.cpp
  DateTimeType.cpp
  DateType.cpp
  DEFAULT.cpp
  DefinedType.cpp
  DefinedValue.cpp
  DEFINITIONS.cpp
  DefinitiveIdentification.cpp
  DefinitiveObjIdComponent.cpp
  DefinitiveObjIdComponentList.cpp
  DefinitiveOID.cpp
  DURATION.cpp
  DurationType.cpp
  Elements.cpp
  ElementSetSpec.cpp
  ElementSetSpecs.cpp
  Elems.cpp
  Ellipsis.cpp
  EMBEDDED.cpp
  EmbeddedPDVType.cpp
  EmbeddedPDVValue.cpp
  EncodingPrefix.cpp
  EncodingPrefixedType.cpp
  EncodingReference.cpp
  END.cpp
  ENUMERATED.cpp
  EnumeratedType.cpp
  EnumeratedValue.cpp
  Enumeration.cpp
  EnumerationItem.cpp
  Enumerations.cpp
  EXCEPT.cpp
  ExceptionIdentification.cpp
  ExceptionSpec.cpp
  Exclusions.cpp
  EXPLICIT.cpp
  EXPORTS.cpp
  EXTENSIBILITY.cpp
  ExtensionEndMarker.cpp
  EXTERNAL.cpp
  ExternalType.cpp
  ExternalValue.cpp
  ExternalTypeReference.cpp
  ExternalValueReference.cpp
  FALSE.cpp
  FirstArcIdentifier.cpp
  FirstRelativeArcIdentifier.cpp
  FROM.cpp
  FullSpecification.cpp
  GeneralizedTime.cpp
  GeneralString.cpp
  GraphicString.cpp
  Group.cpp
  IA5String.cpp
  IdentifierList.cpp
  IMPLICIT.cpp
  IMPLIED.cpp
  IMPORTS.cpp
  Includes.cpp
  InnerTypeConstraints.cpp
  INSTRUCTIONS.cpp
  INTEGER.cpp
  IntegerType.cpp
  IntegerValue.cpp
  INTERSECTION.cpp
  IntersectionElements.cpp
  IntersectionMark.cpp
  IRIType.cpp
  IRIValue.cpp
  ISO646String.cpp
  LessThan.cpp
  LowerEndpoint.cpp
  LowerEndValue.cpp
  MAX.cpp
  MIN.cpp
  ModuleBody.cpp
  ModuleDefinition.cpp
  ModuleIdentifier.cpp
  MultipleTypeConstraints.cpp
  NameAndNumberForm.cpp
  NamedBit.cpp
  NamedBitList.cpp
  NamedConstraint.cpp
  NamedNumber.cpp
  NamedNumberList.cpp
  NamedType.cpp
  NamedValue.cpp
  NamedValueList.cpp
  NameForm.cpp
  NullType.cpp
  NullValue.cpp
  NumberForm.cpp
  NumericString.cpp
  OBJECT.cpp
  ObjectDescriptor.cpp
  ObjectIdentifierType.cpp
  ObjectIdentifierValue.cpp
  ObjIdComponents.cpp
  ObjIdComponentsList.cpp
  OCTET.cpp
  OctetStringType.cpp
  OF.cpp
  OID_IRI.cpp
  OPTIONAL.cpp
  PartialSpecification.cpp
  PATTERN.cpp
  PatternConstraint.cpp
  PDV.cpp
  PermittedAlphabet.cpp
  Plane.cpp
  PrefixedType.cpp
  PrefixedValue.cpp
  PresenceConstraint.cpp
  PRESENT.cpp
  PrintableString.cpp
  PRIVATE.cpp
  ProductionFactory.cpp
  PropertyAndSettingPair.cpp
  PropertyName.cpp
  PropertySettings.cpp
  PropertySettingsList.cpp
  Quadruple.cpp
  REAL.cpp
  RealType.cpp
  ReferencedType.cpp
  RELATIVE_OID.cpp
  RELATIVE_OID_IRI.cpp
  RelativeIRIType.cpp
  RelativeIRIValue.cpp
  RelativeOIDComponents.cpp
  RelativeOIDComponentsList.cpp
  RelativeOIDType.cpp
  RelativeOIDValue.cpp
  RestrictedCharacterStringType.cpp
  RestrictedCharacterStringValue.cpp
  RootAlternativeTypeList.cpp
  RootComponentTypeList.cpp
  RootElementSetSpec.cpp
  RootEnumeration.cpp
  Row.cpp
  SelectionType.cpp
  SEQUENCE.cpp
  SequenceOfType.cpp
  SequenceOfValue.cpp
  SequenceType.cpp
  SequenceValue.cpp
  SET.cpp
  SetOfType.cpp
  SetOfValue.cpp
  SettingName.cpp
  SETTINGS.cpp
  SetType.cpp
  SetValue.cpp
  SignedNumber.cpp
  SingleTypeConstraint.cpp
  SingleValue.cpp
  SIZE.cpp
  SizeConstraint.cpp
  STRING.cpp
  SubsequentArcIdentifier.cpp
  SubtypeConstraint.cpp
  SubtypeElements.cpp
  T61String.cpp
  TableColumn.cpp
  TableRow.cpp
  Tag.cpp
  TaggedType.cpp
  TAGS.cpp
  TeletexString.cpp
  TIME.cpp
  TIME_OF_DAY.cpp
  TimeOfDayType.cpp
  TimeType.cpp
  TRUE.cpp
  Tuple.cpp
  Type.cpp
  TypeAssignment.cpp
  TypeConstraint.cpp
  TypeConstraints.cpp
  TypeWithConstraint.cpp
  UNION.cpp
  UnionMark.cpp
  UNIVERSAL.cpp
  UniversalString.cpp
  UnrestrictedCharacterStringType.cpp
  UnrestrictedCharacterStringValue.cpp
  UpperEndpoint.cpp
  UpperEndValue.cpp
  UsefulType.cpp
  UTCTime.cpp
  UTF8String.cpp
  Value.cpp
  ValueAssignment.cpp
  ValueConstraint.cpp
  ValueList.cpp
  ValueRange.cpp
  VideotexString.cpp
  VisibleString.cpp
  WITH.cpp
)

set(PARSER_SOURCES
  Bstring.cpp
  Cstring.cpp
  Encodingreference.cpp
  Hstring.cpp
  Identifier.cpp
  IntegerUnicodeLabel.hh
  Intersections.cpp # TODO
  Modulereference.hh
  NegativeNumber.cpp
  NonIntegerUnicodeLabel.hh
  Number.cpp
  Psname.hh
  Typereference.cpp
  Unions.cpp # TODO
  Valuereference.hh
)

set(GEN_SOURCES
  ProductionDefs.hh
  ProductionFactory.cpp
)

set(SOURCES
  AsnParser.cpp
  ParseHelper.cpp
)

foreach(GEN_PARSER_SOURCE ${GEN_PARSER_SOURCES})
  string(REPLACE ".cpp" "" CLASS_NAME ${GEN_PARSER_SOURCE})
  list(APPEND GEN_PARSER_HEADERS ${CLASS_NAME}.hh)
endforeach()

foreach(GEN_SOURCE ${GEN_SOURCES})
  string(REPLACE ".cpp" "" CLASS_NAME ${GEN_SOURCE})
  # The list also contains a few header only source files
  string(REPLACE ".hh" "" CLASS_NAME ${CLASS_NAME})
  list(APPEND GEN_HEADERS ${CLASS_NAME}.hh)
endforeach()

foreach(PARSER_SOURCE ${PARSER_SOURCES})
  string(REPLACE ".cpp" "" CLASS_NAME ${PARSER_SOURCE})
  # The list also contains a few header only source files
  string(REPLACE ".hh" "" CLASS_NAME ${CLASS_NAME})
  list(APPEND PARSER_NAMES ${CLASS_NAME})
endforeach()

add_custom_command(
  OUTPUT  ${GEN_PARSER_HEADERS}
          ${GEN_PARSER_SOURCES}
          ${GEN_HEADERS}
          ${GEN_SOURCES}
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/parser_generator.py
          -a ${CMAKE_CURRENT_SOURCE_DIR}/x_680_productions.asn1
          -s ${PARSER_NAMES}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser_generator.py
          ${CMAKE_CURRENT_SOURCE_DIR}/x_680_productions.asn1
          ${PARSER_NAMES}
  COMMENT "Generating parser code"
  #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(genparser
  DEPENDS ${GEN_HEADERS}
          ${GEN_SOURCES}
          ${GEN_PARSER_HEADERS}
          ${GEN_PARSER_SOURCES}
)

add_library(${LIB_NAME}
  ${SOURCES}
  ${GEN_SOURCES}
  ${PARSER_SOURCES}
  ${GEN_PARSER_SOURCES})
add_dependencies(${LIB_NAME} genparser)

#target_compile_options

target_include_directories(${LIB_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/src # for autogenerated messages
)

target_link_libraries(${LIB_NAME}
  PRIVATE
    spdlog
    common
)

set_target_properties(${LIB_NAME} PROPERTIES UNITY_BUILD ON)
