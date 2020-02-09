#include "ModuleDefinition.hh"

using namespace OpenASN;

bool
ModuleDefinition::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  std::vector<std::string> end_stop{ "DEFINITIONS" };
  end_stop.insert(std::end(end_stop), std::begin(endStop), std::end(endStop));

  if (mModuleIdentifier.Parse(asnData, end_stop))
  {
    // ok
  }
  else
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

