#pragma once

namespace OpenASN
{
  // X.690 08/2015 sec 8.1.2
  enum class TagClass
  {
    UNIVERSAL = 0,
    APPLICATION = 1,
    CONTEXT_SPECIFIC = 2,
    PRIVATE = 3
  };
}
