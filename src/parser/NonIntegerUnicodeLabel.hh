#pragma once

#include "Identifier.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  // TODO - This is only a subset of the actual non-integerUnicodeLabel
  // Need to add support for exact non-integerUnicodeLabel
  using NonIntegerUnicodeLabel = Identifier;
}
