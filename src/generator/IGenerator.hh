#pragma once

namespace OpenASN
{
  class IGenerator
  {
    public:
      virtual ~IGenerator() = default;

    public:
      virtual void Generate() = 0;
  };
}
