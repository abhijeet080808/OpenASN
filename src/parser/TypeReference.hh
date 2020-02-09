#pragma once

#include <string>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class TypeReference
  {
    public:
      bool Parse(const std::string& asnWord);

    public:
      std::string mValue;
  };

  using ModuleReference = TypeReference;
}
