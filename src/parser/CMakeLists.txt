set(LIB_NAME parser)

set(SOURCES AsnData.cpp
            AsnParser.cpp
            Assignment.cpp
            AssignmentList.cpp
            BooleanType.cpp
            BuiltinType.cpp
            ComponentType.cpp
            ComponentTypeList.cpp
            ComponentTypeLists.cpp
            DefinitiveIdentification.cpp
            DefinitiveObjIdComponent.cpp
            DefinitiveObjIdComponentList.cpp
            DefinitiveOID.cpp
            Identifier.cpp
            IntegerType.cpp
            ModuleBody.cpp
            ModuleDefinition.cpp
            ModuleIdentifier.cpp
            NamedType.cpp
            NameForm.cpp
            ParseHelper.cpp
            ProductionFactory.cpp
            RootComponentTypeList.cpp
            SequenceType.cpp
            TypeAssignment.cpp
            Type.cpp
            TypeReference.cpp
)

add_library(${LIB_NAME} ${SOURCES})

#target_compile_options

#target_include_directories

target_link_libraries(${LIB_NAME} spdlog
)
