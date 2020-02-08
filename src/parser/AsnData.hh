#pragma once

#include <string>
#include <vector>

namespace OpenASN
{
  // Data pertaining to a single ASN.1 file
  class AsnData
  {
    public:
      enum class PrecedingInfo
      {
        PRECEDED_BY_WHITESPACE,
        PRECEDED_BY_NEWLINE,
      };

      enum class SucceedingInfo
      {
        SUCCEEDED_BY_WHITESPACE,
        SUCCEEDED_BY_NEWLINE
      };

    public:
      AsnData();

      void Insert(PrecedingInfo precedingInfo,
                  const std::string& asnword,
                  SucceedingInfo succeedingInfo);

      size_t GetSize();

      std::tuple<PrecedingInfo, std::string, SucceedingInfo> PeekPrev();
      std::tuple<PrecedingInfo, std::string, SucceedingInfo> PeekCurrent();
      std::tuple<PrecedingInfo, std::string, SucceedingInfo> PeekNext();

      std::tuple<PrecedingInfo, std::string, SucceedingInfo> Get();

      void ResetCurrentIndex();

    private:
      std::vector<std::tuple<PrecedingInfo,
                             std::string,
                             SucceedingInfo>> mAsnData;
      size_t mCurrentAsnDataIndex;
  };
}
