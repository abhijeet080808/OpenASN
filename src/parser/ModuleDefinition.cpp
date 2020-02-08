#include "ModuleDefinition.hh"

using namespace OpenASN;

bool
ModuleDefinition::
Parse(AsnData& asnData)
{
  if (!mModuleIdentifier.Parse(asnData))
  {
    return false;
  }

  auto asn_word = asnData.Get();
  if (asn_word && std::get<1>(asn_word.value()) == "DEFINITIONS")
  {
    // ok
  }
  else
  {
    return false;
  }

  asn_word = asnData.Get();
  if (asn_word && std::get<1>(asn_word.value()) == "::=")
  {
    // ok
  }
  else
  {
    return false;
  }

  asn_word = asnData.Get();
  if (asn_word && std::get<1>(asn_word.value()) == "BEGIN")
  {
    // ok
  }
  else
  {
    return false;
  }

  return true;
}

