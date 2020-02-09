#pragma once

#include "AsnData.hh"

#include "NameForm.hh"
//#include "DefinitiveNumberForm.hh"
//#include "DefinitiveNameAndNumberForm.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class DefinitiveObjIdComponent
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::optional<NameForm> mNameForm;
      //std::optional<DefinitiveNumberForm> mDefinitiveNumberForm;
      //std::optional<DefinitiveNameAndNumberForm> mDefinitiveNameAndNumberForm;
  };
}
