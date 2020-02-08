#pragma once

#include <optional>
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

      using Word = std::optional<std::tuple<
        PrecedingInfo, std::string, SucceedingInfo>>;

    public:
      AsnData();

      void Insert(PrecedingInfo precedingInfo,
                  const std::string& asnword,
                  SucceedingInfo succeedingInfo);

      size_t GetSize();

      Word PeekPrev();
      Word PeekCurrent();
      Word PeekNext();

      // also increments index by 1 so that next Get will return
      // the next element
      Word Get();

      void ResetCurrentIndex();

    private:
      std::vector<std::tuple<PrecedingInfo,
                             std::string,
                             SucceedingInfo>> mAsnData;
      size_t mCurrentAsnDataIndex;
  };
}
