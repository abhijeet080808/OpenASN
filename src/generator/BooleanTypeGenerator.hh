#pragma once

#include "IGenerator.hh"

#include <string>

namespace OpenASN
{
  class BooleanTypeGenerator : public IGenerator
  {
    public:
      BooleanTypeGenerator(const std::string& identifier,
                           bool isConstructed);

    public:
      void Generate() override;

    private:
      std::string mIdentifier;
      bool mIsConstructed;
  };
}
