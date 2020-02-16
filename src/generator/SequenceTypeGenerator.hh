#pragma once

#include "IGenerator.hh"

#include "parser/SequenceType.hh"

#include <memory>

namespace OpenASN
{
  class SequenceTypeGenerator : public IGenerator
  {
    public:
      SequenceTypeGenerator(const std::string& identifier,
                            bool isConstructed,
                            SequenceType* pSequenceType);

    public:
      std::string GetIdentifier() const override;

      void Generate() const override;

    private:
      std::string mIdentifier;
      bool mIsConstructed;
      std::vector<std::shared_ptr<IGenerator>> mSubTypeGeneratorList;
  };
}
