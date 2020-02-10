#include "DefinitiveIdentification.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
DefinitiveIdentification::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // DefinitiveIdentification ::=
  //   DefinitiveOID
  // | DefinitiveOIDandIRI
  // | empty

  LOG_START("DefinitiveOID", asnData);
  DefinitiveOID definitive_oid;
  if (definitive_oid.Parse(asnData, endStop))
  {
    mDefinitiveOID = definitive_oid;
    LOG_PASS("DefinitiveOID", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("DefinitiveOID", asnData);
  }

  /*
  DefinitiveOIDandIRI definitive_oid_and_iri;
  if (definitive_oid_and_iri.Parse(asnData, endStop))
  {
    nDefinitiveOIDandIRI = definitive_oid_and_iri;
  }
  */

  return true;
}
