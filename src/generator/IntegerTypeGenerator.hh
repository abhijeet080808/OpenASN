#pragma once

#include "IGenerator.hh"

#include <string>

namespace OpenASN
{
  class IntegerTypeGenerator : public IGenerator
  {
    public:
      IntegerTypeGenerator(const std::string& identifier,
                           bool isConstructed);

    public:
      void Generate() override;

    private:
      std::string mIdentifier;
      bool mIsConstructed;
  };
}
