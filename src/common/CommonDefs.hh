#pragma once

namespace OpenASN
{
  // X.680 08/2015
  enum class Production
  {
    ADDITIONAL_ELEMENT_SET_SPEC,
    ALTERNATIVE_TYPE_LIST,
    ALTERNATIVE_TYPE_LISTS,
    APPLICATION,
    ASSIGNMENT,
    ASSIGNMENT_LIST,
    BIT_STRING_TYPE,
    BMP_STRING,
    BOOLEAN_TYPE,
    BOOLEAN_VALUE,
    BUILTIN_TYPE,
    BUILTIN_VALUE,
    CHARACTER_STRING_TYPE,
    CHOICE_TYPE,
    CLASS,
    CLASS_NUMBER,
    COMPONENT_TYPE,
    COMPONENT_TYPE_LIST,
    COMPONENT_TYPE_LISTS,
    CONSTRAINT,
    CONSTRAINT_LIST,
    CONSTRAINT_SPEC,
    CONTAINED_SUBTYPE,
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
    GENERALIZED_TIME,
    GENERAL_STRING,
    GRAPHIC_STRING,
    IA5_STRING,
    IDENTIFIER,
    IMPLICIT,
    INCLUDES,
    INTEGER_TYPE,
    INTERSECTION_ELEMENTS,
    INTERSECTIONS,
    IRI_TYPE,
    ISO646_STRING,
    MODULE_BODY,
    MODULE_DEFINITION,
    MODULE_IDENTIFIER,
    MODULE_REFERENCE,
    NAME_FORM,
    NAMED_BIT,
    NAMED_BIT_LIST,
    NAMED_NUMBER,
    NAMED_NUMBER_LIST,
    NAMED_TYPE,
    NEGATIVE_NUMBER,
    NULL_TYPE,
    NUMBER,
    NUMERIC_STRING,
    OBJECT_DESCRIPTOR,
    OBJECT_IDENTIFIER_TYPE,
    OCTET_STRING_TYPE,
    PREFIXED_TYPE,
    PRINTABLE_STRING,
    PRIVATE,
    REAL_TYPE,
    REFERENCED_TYPE,
    RELATIVE_IRI_TYPE,
    RELATIVE_OID_TYPE,
    ROOT_ALTERNATIVE_TYPE_LIST,
    ROOT_COMPONENT_TYPE_LIST,
    ROOT_ELEMENT_SET_SPEC,
    ROOT_ENUMERATION,
    RESTRICTED_CHARACTER_STRING_TYPE,
    SELECTION_TYPE,
    SEQUENCE_TYPE,
    SEQUENCE_OF_TYPE,
    SET_TYPE,
    SET_OF_TYPE,
    SIGNED_NUMBER,
    SINGLE_VALUE,
    SUBTYPE_CONSTRAINT,
    SUBTYPE_ELEMENTS,
    TAG,
    TAGGED_TYPE,
    T61_STRING,
    TELETEX_STRING,
    TIME_OF_DAY_TYPE,
    TIME_TYPE,
    TYPE,
    TYPE_ASSIGNMENT,
    TYPE_REFERENCE,
    UNIONS,
    UNIVERSAL,
    UNIVERSAL_STRING,
    UNRESTRICTED_CHARACTER_STRING_TYPE,
    USEFUL_TYPE,
    UTC_TIME,
    UTF8_STRING,
    VALUE_REFERENCE,
    VALUE,
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
