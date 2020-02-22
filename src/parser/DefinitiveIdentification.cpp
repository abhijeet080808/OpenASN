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
      std::vector<std::string>& endStop)
{
  // DefinitiveIdentification ::=
  //   DefinitiveOID
  // | DefinitiveOIDandIRI
  // | empty

  auto obj = "DefinitiveOID";
  LOG_START();
  auto definitive_oid =
    ProductionFactory::Get(Production::DEFINITIVE_OID);
  if (definitive_oid->Parse(asnData, asnDataIndex, endStop))
  {
    mDefinitiveOID = definitive_oid;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  // DefinitiveOIDandIRI

  return true;
}
