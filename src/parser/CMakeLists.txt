set(LIB_NAME parser)

set(SOURCES AlternativeTypeList.cpp
            AlternativeTypeLists.cpp
            AsnData.cpp
            AsnParser.cpp
            Assignment.cpp
            AssignmentList.cpp
            BitStringType.cpp
            BMPString.cpp
            BooleanType.cpp
            BuiltinType.cpp
            CharacterStringType.cpp
            ChoiceType.cpp
            ComponentType.cpp
            ComponentTypeList.cpp
            ComponentTypeLists.cpp
            DefinitiveIdentification.cpp
            DefinitiveObjIdComponent.cpp
            DefinitiveObjIdComponentList.cpp
            DefinitiveOID.cpp
            GeneralString.cpp
            GraphicString.cpp
            IA5String.cpp
            Identifier.cpp
            IntegerType.cpp
            ISO646String.cpp
            ModuleBody.cpp
            ModuleDefinition.cpp
            ModuleIdentifier.cpp
            NamedBit.cpp
            NamedBitList.cpp
            NamedType.cpp
            NameForm.cpp
            Number.cpp
            NumericString.cpp
            ParseHelper.cpp
            PrintableString.cpp
            ProductionFactory.cpp
            RootAlternativeTypeList.cpp
            RootComponentTypeList.cpp
            RestrictedCharacterStringType.cpp
            SequenceType.cpp
            T61String.cpp
            TeletexString.cpp
            TypeAssignment.cpp
            Type.cpp
            TypeReference.cpp
            UniversalString.cpp
            UnrestrictedCharacterStringType.cpp
            UTF8String.cpp
            VideotexString.cpp
            VisibleString.cpp
)

add_library(${LIB_NAME} ${SOURCES})

#target_compile_options

target_include_directories(${LIB_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${LIB_NAME}
  PRIVATE
    spdlog
    common
)
