#pragma once

#include <string>

namespace OpenASN
{
  class IGenerator
  {
    public:
      virtual ~IGenerator() = default;

    public:
      virtual std::string GetIdentifier() const = 0;

      virtual void Generate() const = 0;
  };
}
