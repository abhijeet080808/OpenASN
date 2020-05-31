set(LIB_NAME parser)

set(GEN_SOURCES Absent.cpp
                AdditionalElementSetSpec.cpp
                AlternativeTypeList.cpp
                AlternativeTypeLists.cpp
                Application.cpp
                ArcIdentifier.cpp
                AsnFalse.cpp
                AsnTrue.cpp
                Assignment.cpp
                AssignmentList.cpp
                BitStringType.cpp
                BitStringValue.cpp
                BMPString.cpp
                BooleanType.cpp
                BooleanValue.cpp
                BuiltinType.cpp
                BuiltinValue.cpp
                Cell.cpp
                CharsDefn.cpp
                CharSyms.cpp
                CharacterStringList.cpp
                CharacterStringType.cpp
                CharacterStringValue.cpp
                ChoiceType.cpp
                ChoiceValue.cpp
                Class.cpp
                ClassNumber.cpp
                ComponentConstraint.cpp
                ComponentType.cpp
                ComponentTypeList.cpp
                ComponentTypeLists.cpp
                ComponentValueList.cpp
                Constraint.cpp
                ConstraintList.cpp
                ConstraintSpec.cpp
                ContainedSubtype.cpp
                DateTimeType.cpp
                DateType.cpp
                DefinedType.cpp
                DefinedValue.cpp
                DefinitiveIdentification.cpp
                DefinitiveObjIdComponent.cpp
                DefinitiveObjIdComponentList.cpp
                DefinitiveOID.cpp
                DurationType.cpp
                Elements.cpp
                ElementSetSpec.cpp
                ElementSetSpecs.cpp
                Elems.cpp
                Ellipsis.cpp
                EmbeddedPDVType.cpp
                EncodingPrefix.cpp
                EncodingPrefixedType.cpp
                EncodingReference.cpp
                EnumeratedType.cpp
                EnumeratedValue.cpp
                Enumeration.cpp
                EnumerationItem.cpp
                Enumerations.cpp
                ExceptionIdentification.cpp
                ExceptionSpec.cpp
                Exclusions.cpp
                Explicit.cpp
                ExternalType.cpp
                ExternalTypeReference.cpp
                ExternalValueReference.cpp
                FirstArcIdentifier.cpp
                FullSpecification.cpp
                GeneralizedTime.cpp
                GeneralString.cpp
                GraphicString.cpp
                Group.cpp
                IA5String.cpp
                IdentifierList.cpp
                IElems.cpp
                Implicit.cpp
                Includes.cpp
                InnerTypeConstraints.cpp
                IntegerType.cpp
                IntegerValue.cpp
                IntersectionElements.cpp
                IntersectionMark.cpp
                IRIType.cpp
                IRIValue.cpp
                ISO646String.cpp
                ModuleBody.cpp
                ValueRange.cpp
)

set(SOURCES AsnParser.cpp
            Bstring.cpp
            Cstring.cpp
            EncodingReferencePrime.cpp
            Hstring.cpp
            Identifier.cpp
            Intersections.cpp # TODO
            LessThan.cpp
            LowerEndpoint.cpp
            LowerEndValue.cpp
            Max.cpp
            Min.cpp
            ModuleDefinition.cpp
            ModuleIdentifier.cpp
            MultipleTypeConstraints.cpp
            NamedBit.cpp
            NamedBitList.cpp
            NamedConstraint.cpp
            NamedNumber.cpp
            NamedNumberList.cpp
            NamedType.cpp
            NamedValue.cpp
            NameForm.cpp
            NegativeNumber.cpp
            NullType.cpp
            NullValue.cpp
            Number.cpp
            NumericString.cpp
            ObjectDescriptor.cpp
            ObjectIdentifierType.cpp
            OctetStringType.cpp
            Optional.cpp
            ParseHelper.cpp
            PartialSpecification.cpp
            PatternConstraint.cpp
            PermittedAlphabet.cpp
            Plane.cpp
            PrefixedType.cpp
            PresenceConstraint.cpp
            Present.cpp
            Private.cpp
            PrintableString.cpp
            ProductionFactory.cpp
            PropertyAndSettingPair.cpp
            PropertyName.cpp
            PropertySettings.cpp
            PropertySettingsList.cpp
            Quadruple.cpp
            RealType.cpp
            ReferencedType.cpp
            RelativeIRIType.cpp
            RelativeOIDType.cpp
            RestrictedCharacterStringType.cpp
            RestrictedCharacterStringValue.cpp
            RootAlternativeTypeList.cpp
            RootComponentTypeList.cpp
            RootElementSetSpec.cpp
            RootEnumeration.cpp
            Row.cpp
            SelectionType.cpp
            SequenceOfType.cpp
            SequenceType.cpp
            SequenceValue.cpp
            SettingName.cpp
            SetType.cpp
            SetOfType.cpp
            SignedNumber.cpp
            SingleTypeConstraint.cpp
            SingleValue.cpp
            SizeConstraint.cpp
            SubsequentArcIdentifier.cpp
            SubtypeConstraint.cpp
            SubtypeElements.cpp
            TableColumn.cpp
            TableRow.cpp
            Tag.cpp
            TaggedType.cpp
            T61String.cpp
            TeletexString.cpp
            TimeOfDayType.cpp
            TimeType.cpp
            Tuple.cpp
            Type.cpp
            TypeAssignment.cpp
            TypeConstraint.cpp
            TypeConstraints.cpp
            TypeReference.cpp
            Unions.cpp
            Universal.cpp
            UniversalString.cpp
            UnrestrictedCharacterStringType.cpp
            UnrestrictedCharacterStringValue.cpp
            UpperEndpoint.cpp
            UpperEndValue.cpp
            UsefulType.cpp
            UTCTime.cpp
            UTF8String.cpp
            Value.cpp
            ValueConstraint.cpp
            VideotexString.cpp
            VisibleString.cpp
)

foreach(GEN_SOURCE ${GEN_SOURCES})
  string(REPLACE ".cpp" "" CLASS_NAME ${GEN_SOURCE})
  list(APPEND GEN_HEADERS ${CLASS_NAME}.hh)
endforeach()

add_custom_command(
  OUTPUT  ${GEN_HEADERS} ${GEN_SOURCES}
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/parser_generator.py
          -a ${CMAKE_CURRENT_SOURCE_DIR}/x_680_productions.asn1
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser_generator.py
          ${CMAKE_CURRENT_SOURCE_DIR}/x_680_productions.asn1
  COMMENT "Generating parser code"
  #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(parsergen DEPENDS ${GEN_HEADERS} ${GEN_SOURCES})

add_library(${LIB_NAME} ${SOURCES} ${GEN_SOURCES})
add_dependencies(${LIB_NAME} parsergen)

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
