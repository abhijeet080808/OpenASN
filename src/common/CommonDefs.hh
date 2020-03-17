#pragma once

namespace OpenASN
{
  // X.680 08/2015
  enum class Production
  {
    ABSENT,
    ADDITIONAL_ELEMENT_SET_SPEC,
    ALTERNATIVE_TYPE_LIST,
    ALTERNATIVE_TYPE_LISTS,
    APPLICATION,
    ASSIGNMENT,
    ASSIGNMENT_LIST,
    BIT_STRING_TYPE,
    BIT_STRING_VALUE,
    BMP_STRING,
    BOOLEAN_TYPE,
    BOOLEAN_VALUE,
    BSTRING,
    BUILTIN_TYPE,
    BUILTIN_VALUE,
    CELL,
    CHARS_DEFN,
    CHAR_SYMS,
    CHARACTER_STRING_LIST,
    CHARACTER_STRING_TYPE,
    CHARACTER_STRING_VALUE,
    CHOICE_TYPE,
    CLASS,
    CLASS_NUMBER,
    COMPONENT_CONSTRAINT,
    COMPONENT_TYPE,
    COMPONENT_TYPE_LIST,
    COMPONENT_TYPE_LISTS,
    COMPONENT_VALUE_LIST,
    CONSTRAINT,
    CONSTRAINT_LIST,
    CONSTRAINT_SPEC,
    CONTAINED_SUBTYPE,
    CSTRING,
    DATE_TYPE,
    DATE_TIME_TYPE,
    DEFINED_TYPE,
    DEFINED_VALUE,
    DEFINITIVE_IDENTIFICATION,
    DEFINITIVE_OID,
    DEFINITIVE_OBJ_ID_COMPONENT,
    DEFINITIVE_OBJ_ID_COMPONENT_LIST,
    DURATION_TYPE,
    ELEMENTS,
    ELEMENT_SET_SPEC,
    ELEMENT_SET_SPECS,
    ELLIPSIS,
    EMBEDDED_PDV_TYPE,
    ENCODING_PREFIX,
    ENCODING_PREFIXED_TYPE,
    ENCODING_REFERENCE,
    ENCODING_REFERENCE_PRIME,
    ENUMERATED_TYPE,
    ENUMERATION,
    ENUMERATION_ITEM,
    ENUMERATIONS,
    EXCEPTION_IDENTIFICATION,
    EXCEPTION_SPEC,
    EXCLUSIONS,
    EXPLICIT,
    EXTERNAL_TYPE,
    EXTERNAL_TYPE_REFERENCE,
    EXTERNAL_VALUE_REFERENCE,
    FULL_SPECIFICATION,
    GENERALIZED_TIME,
    GENERAL_STRING,
    GRAPHIC_STRING,
    GROUP,
    HSTRING,
    IA5_STRING,
    IDENTIFIER,
    IDENTIFIER_LIST,
    IMPLICIT,
    INCLUDES,
    INNER_TYPE_CONSTRAINTS,
    INTEGER_TYPE,
    INTEGER_VALUE,
    INTERSECTION_ELEMENTS,
    INTERSECTIONS,
    IRI_TYPE,
    ISO646_STRING,
    LESS_THAN,
    LOWER_END_VALUE,
    LOWER_ENDPOINT,
    MAX,
    MIN,
    MODULE_BODY,
    MODULE_DEFINITION,
    MODULE_IDENTIFIER,
    MODULE_REFERENCE,
    MULTIPLE_TYPE_CONSTRAINTS,
    NAME_FORM,
    NAMED_BIT,
    NAMED_BIT_LIST,
    NAMED_CONSTRAINT,
    NAMED_NUMBER,
    NAMED_NUMBER_LIST,
    NAMED_TYPE,
    NAMED_VALUE,
    NEGATIVE_NUMBER,
    NULL_TYPE,
    NUMBER,
    NUMERIC_STRING,
    OBJECT_DESCRIPTOR,
    OBJECT_IDENTIFIER_TYPE,
    OCTET_STRING_TYPE,
    OPTIONAL,
    PARTIAL_SPECIFICATION,
    PATTERN_CONSTRAINT,
    PERMITTED_ALPHABET,
    PLANE,
    PREFIXED_TYPE,
    PRESENCE_CONSTRAINT,
    PRESENT,
    PRINTABLE_STRING,
    PRIVATE,
    PROPERTY_AND_SETTING_PAIR,
    PROPERTY_NAME,
    PROPERTY_SETTINGS,
    PROPERTY_SETTINGS_LIST,
    PS_NAME,
    QUADRUPLE,
    REAL_TYPE,
    REFERENCED_TYPE,
    RELATIVE_IRI_TYPE,
    RELATIVE_OID_TYPE,
    RESTRICTED_CHARACTER_STRING_TYPE,
    RESTRICTED_CHARACTER_STRING_VALUE,
    ROOT_ALTERNATIVE_TYPE_LIST,
    ROOT_COMPONENT_TYPE_LIST,
    ROOT_ELEMENT_SET_SPEC,
    ROOT_ENUMERATION,
    ROW,
    SELECTION_TYPE,
    SEQUENCE_OF_TYPE,
    SEQUENCE_TYPE,
    SEQUENCE_VALUE,
    SETTING_NAME,
    SET_TYPE,
    SET_OF_TYPE,
    SIGNED_NUMBER,
    SINGLE_TYPE_CONSTRAINT,
    SINGLE_VALUE,
    SIZE_CONSTRAINT,
    SUBTYPE_CONSTRAINT,
    SUBTYPE_ELEMENTS,
    TABLE_COLUMN,
    TABLE_ROW,
    TAG,
    TAGGED_TYPE,
    T61_STRING,
    TELETEX_STRING,
    TIME_OF_DAY_TYPE,
    TIME_TYPE,
    TUPLE,
    TYPE,
    TYPE_ASSIGNMENT,
    TYPE_CONSTRAINT,
    TYPE_CONSTRAINTS,
    TYPE_REFERENCE,
    UNIONS,
    UNIVERSAL,
    UNIVERSAL_STRING,
    UNRESTRICTED_CHARACTER_STRING_TYPE,
    UNRESTRICTED_CHARACTER_STRING_VALUE,
    UPPER_END_VALUE,
    UPPER_ENDPOINT,
    USEFUL_TYPE,
    UTC_TIME,
    UTF8_STRING,
    VALUE,
    VALUE_CONSTRAINT,
    VALUE_RANGE,
    VALUE_REFERENCE,
    VIDEOTEX_STRING,
    VISIBLE_STRING
  };

  // X.690 08/2015 sec 8.1.2
  enum class TagClass
  {
    UNIVERSAL = 0,
    APPLICATION = 1,
    CONTEXT_SPECIFIC = 2,
    PRIVATE = 3
  };
}
