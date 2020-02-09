#include "DefinitiveOID.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
DefinitiveOID::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  LOG_START("{", asnData);
  auto asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "{")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("{", asnData);
  }
  else
  {
    LOG_FAIL("{", asnData);
    return false;
  }

  std::vector<std::string> end_stop{ "}" };
  end_stop.insert(std::end(end_stop), std::begin(endStop), std::end(endStop));

  LOG_START("DefinitiveObjIdComponentList", asnData);
  if (mDefinitiveObjIdComponentList.Parse(asnData, end_stop))
  {
    LOG_PASS("DefinitiveObjIdComponentList", asnData);
  }
  else
  {
    LOG_FAIL("DefinitiveObjIdComponentList", asnData);
    return false;
  }

  LOG_START("}", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "}")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("}", asnData);
  }
  else
  {
    LOG_FAIL("}", asnData);
    return false;
  }

  return true;
}
