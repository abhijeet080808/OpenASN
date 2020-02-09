set(LIB_NAME parser)

set(SOURCES AsnData.cpp
            AsnParser.cpp
            DefinitiveIdentification.cpp
            DefinitiveObjIdComponent.cpp
            DefinitiveObjIdComponentList.cpp
            DefinitiveOID.cpp
            Identifier.cpp
            ModuleDefinition.cpp
            ModuleIdentifier.cpp
            NamedType.cpp
            NameForm.cpp
            ParseHelper.cpp
            TypeReference.cpp
)

add_library(${LIB_NAME} ${SOURCES})

#target_compile_options

#target_include_directories

target_link_libraries(${LIB_NAME} spdlog
)