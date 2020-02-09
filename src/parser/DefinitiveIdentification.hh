#pragma once

#include "AsnData.hh"

#include "DefinitiveOID.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class DefinitiveIdentification
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
			std::optional<DefinitiveOID> mDefinitiveOID;
			//std::optional<DefinitiveOIDandIRI> mDefinitiveOIDandIRI;
  };
}
