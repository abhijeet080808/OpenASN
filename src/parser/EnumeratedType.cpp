#include "EnumeratedType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ProductionFactory.hh"

using namespace OpenASN;

Production
EnumeratedType::
GetType() const
{
  return Production::ENUMERATED_TYPE;
}

bool
EnumeratedType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // EnumeratedType ::=
  // ENUMERATED "{" Enumerations "}"

  LOG_START("ENUMERATED", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "ENUMERATED")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("ENUMERATED", asnData);
  }
  else
  {
    LOG_FAIL("ENUMERATED", asnData);
    return false;
  }

  LOG_START("{", asnData);
  asn_word = asnData.Peek();
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

  LOG_START("Enumerations", asnData);
  auto enumerations =
    ProductionFactory::Get(Production::ENUMERATIONS);
  if (enumerations->Parse(asnData, end_stop))
  {
    mEnumerations = enumerations;
    LOG_PASS("Enumerations", asnData);
  }
  else
  {
    LOG_FAIL("Enumerations", asnData);
    return false;
  }

  LOG_START("}", asnData);
  asn_word = asnData.Peek();
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
