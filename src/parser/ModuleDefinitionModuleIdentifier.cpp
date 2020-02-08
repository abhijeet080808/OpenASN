#include "ModuleDefinitionModuleIdentifier.hh"

using namespace OpenASN;

bool
ModuleDefinitionModuleIdentifier::
Parse(AsnData& asnData)
{
  const auto& asn_word = asnData.Get();
  if (asn_word)
  {
    mModuleReference = std::get<1>(asn_word.value());
  }
  else
  {
    return false;
  }

  return true;
}
