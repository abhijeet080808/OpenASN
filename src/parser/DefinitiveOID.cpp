#include "DefinitiveOID.hh"

using namespace OpenASN;

bool
DefinitiveOID::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  auto asn_word = asnData.Get();
  if (asn_word && std::get<1>(asn_word.value()) == "{")
  {
    // ok
  }
  else
  {
    return false;
  }

  std::vector<std::string> end_stop{ "}" };
  end_stop.insert(std::end(end_stop), std::begin(endStop), std::end(endStop));

  if (mDefinitiveObjIdComponentList.Parse(asnData, end_stop))
  {
    // ok
  }
  else
  {
    return false;
  }

  asn_word = asnData.Get();
  if (asn_word && std::get<1>(asn_word.value()) == "}")
  {
    // ok
  }
  else
  {
    return false;
  }

  return true;
}
