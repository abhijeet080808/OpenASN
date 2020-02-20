#pragma once

namespace OpenASN
{
  // X.680 08/2015
  enum class Production
  {
    ALTERNATIVE_TYPE_LIST,
    ALTERNATIVE_TYPE_LISTS,
    ASSIGNMENT,
    ASSIGNMENT_LIST,
    BIT_STRING_TYPE,
    BMP_STRING,
    BOOLEAN_TYPE,
    BUILTIN_TYPE,
    CHARACTER_STRING_TYPE,
    CHOICE_TYPE,
    COMPONENT_TYPE,
    COMPONENT_TYPE_LIST,
    COMPONENT_TYPE_LISTS,
    DATE_TYPE,
    DATE_TIME_TYPE,
    DEFINITIVE_IDENTIFICATION,
    DEFINITIVE_OID,
    DEFINITIVE_OBJ_ID_COMPONENT,
    DEFINITIVE_OBJ_ID_COMPONENT_LIST,
    DURATION_TYPE,
    GENERAL_STRING,
    GRAPHIC_STRING,
    IA5_STRING,
    IDENTIFIER,
    INTEGER_TYPE,
    ISO646_STRING,
    MODULE_BODY,
    MODULE_DEFINITION,
    MODULE_IDENTIFIER,
    MODULE_REFERENCE,
    NAME_FORM,
    NAMED_BIT,
    NAMED_BIT_LIST,
    NAMED_TYPE,
    NUMBER,
    NUMERIC_STRING,
    PRINTABLE_STRING,
    ROOT_ALTERNATIVE_TYPE_LIST,
    ROOT_COMPONENT_TYPE_LIST,
    RESTRICTED_CHARACTER_STRING_TYPE,
    SEQUENCE_TYPE,
    T61_STRING,
    TELETEX_STRING,
    TYPE,
    TYPE_ASSIGNMENT,
    TYPE_REFERENCE,
    UNIVERSAL_STRING,
    UNRESTRICTED_CHARACTER_STRING_TYPE,
    UTF8_STRING,
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
