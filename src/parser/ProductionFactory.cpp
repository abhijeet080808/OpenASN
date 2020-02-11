#include "ProductionFactory.hh"

#include "Assignment.hh"
#include "AssignmentList.hh"
#include "BooleanType.hh"
#include "BuiltinType.hh"
#include "ComponentType.hh"
#include "ComponentTypeList.hh"
#include "ComponentTypeLists.hh"
#include "DefinitiveIdentification.hh"
#include "DefinitiveOID.hh"
#include "DefinitiveObjIdComponent.hh"
#include "DefinitiveObjIdComponentList.hh"
#include "Identifier.hh"
#include "IntegerType.hh"
#include "ModuleBody.hh"
#include "ModuleDefinition.hh"
#include "ModuleIdentifier.hh"
#include "NameForm.hh"
#include "NamedType.hh"
#include "RootComponentTypeList.hh"
#include "SequenceType.hh"
#include "Type.hh"
#include "TypeAssignment.hh"
#include "TypeReference.hh"

#include <cassert>

using namespace OpenASN;

std::shared_ptr<IProduction>
ProductionFactory::
Get(Production production)
{
  switch (production)
  {
    case Production::ASSIGNMENT:
      return std::make_shared<Assignment>();

    case Production::ASSIGNMENT_LIST:
      return std::make_shared<AssignmentList>();

    case Production::BOOLEAN_TYPE:
      return std::make_shared<BooleanType>();

    case Production::BUILTIN_TYPE:
      return std::make_shared<BuiltinType>();

    case Production::COMPONENT_TYPE:
      return std::make_shared<ComponentType>();

    case Production::COMPONENT_TYPE_LIST:
      return std::make_shared<ComponentTypeList>();

    case Production::COMPONENT_TYPE_LISTS:
      return std::make_shared<ComponentTypeLists>();

    case Production::DEFINITIVE_IDENTIFICATION:
      return std::make_shared<DefinitiveIdentification>();

    case Production::DEFINITIVE_OID:
      return std::make_shared<DefinitiveOID>();

    case Production::DEFINITIVE_OBJ_ID_COMPONENT:
      return std::make_shared<DefinitiveObjIdComponent>();

    case Production::DEFINITIVE_OBJ_ID_COMPONENT_LIST:
      return std::make_shared<DefinitiveObjIdComponentList>();

    case Production::IDENTIFIER:
      return std::make_shared<Identifier>();

    case Production::INTEGER_TYPE:
      return std::make_shared<IntegerType>();

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

    case Production::NAMED_TYPE:
      return std::make_shared<NamedType>();

    case Production::ROOT_COMPONENT_TYPE_LIST:
      return std::make_shared<RootComponentTypeList>();

    case Production::SEQUENCE_TYPE:
      return std::make_shared<SequenceType>();

    case Production::TYPE:
      return std::make_shared<Type>();

    case Production::TYPE_ASSIGNMENT:
      return std::make_shared<TypeAssignment>();

    case Production::TYPE_REFERENCE:
      return std::make_shared<TypeReference>();

    case Production::VALUE_REFERENCE:
      return std::make_shared<ValueReference>();

    default:
      assert(false);
      return nullptr;
  }
}
