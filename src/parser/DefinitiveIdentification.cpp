#include "DefinitiveIdentification.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // DefinitiveIdentification ::=
  //   DefinitiveOID
  // | DefinitiveOIDandIRI
  // | empty

  LOG_START("DefinitiveOID", asnData);
  auto definitive_oid =
    ProductionFactory::Get(Production::DEFINITIVE_OID);
  if (definitive_oid->Parse(asnData, endStop))
  {
    mDefinitiveOID = definitive_oid;
    LOG_PASS("DefinitiveOID", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("DefinitiveOID", asnData);
  }

  // DefinitiveOIDandIRI

  return true;
}
