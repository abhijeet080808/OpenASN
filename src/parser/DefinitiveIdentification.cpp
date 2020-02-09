#include "DefinitiveIdentification.hh"

using namespace OpenASN;

bool
DefinitiveIdentification::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  DefinitiveOID definitive_oid;
  if (definitive_oid.Parse(asnData, endStop))
  {
    mDefinitiveOID = definitive_oid;
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
