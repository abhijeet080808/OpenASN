#include "DefinitiveIdentification.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DefinitiveIdentification::
GetType() const
{
  return Production::DEFINITIVE_IDENTIFICATION;
}

bool
DefinitiveIdentification::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("DefinitiveIdentification");

  // DefinitiveIdentification ::=
  //   DefinitiveOID
  // | DefinitiveOIDandIRI
  // | empty

  auto obj = "DefinitiveOID";
  LOG_START();
  auto definitive_oid =
    ProductionFactory::Get(Production::DEFINITIVE_OID);
  if (definitive_oid->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mDefinitiveOID = definitive_oid;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  // DefinitiveOIDandIRI

  parsePath.pop_back();
  return true;
}
