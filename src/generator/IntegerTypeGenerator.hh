#pragma once

#include "IGenerator.hh"

namespace OpenASN
{
  class IntegerTypeGenerator : public IGenerator
  {
    public:
      IntegerTypeGenerator(const std::string& identifier,
                           bool isConstructed);

    public:
      std::string GetIdentifier() const override;

      void Generate() const override;

    private:
      std::string mIdentifier;
      bool mIsConstructed;
  };
}
