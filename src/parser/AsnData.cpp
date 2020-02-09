#include "AsnData.hh"

using namespace OpenASN;

AsnData::
AsnData()
  : mAsnWords(),
    mCurrentAsnWordIndex(0)
{
}

void
AsnData::
Insert(PrecedingInfo precedingInfo,
       const std::string& asnWord,
       SucceedingInfo succeedingInfo)
{
  mAsnWords.push_back(std::make_tuple(precedingInfo, asnWord, succeedingInfo));
}

size_t
AsnData::
GetSize()
{
  return mAsnWords.size();
}

std::optional<AsnData::Word>
AsnData::
PeekPrev()
{
  if (mAsnWords.size() > mCurrentAsnWordIndex - 1)
  {
    return mAsnWords.at(mCurrentAsnWordIndex - 1);
  }

  return std::nullopt;
}

std::optional<AsnData::Word>
AsnData::
PeekCurrent()
{
  if (mAsnWords.size() > mCurrentAsnWordIndex)
  {
    return mAsnWords.at(mCurrentAsnWordIndex);
  }

  return std::nullopt;
}

std::optional<AsnData::Word>
AsnData::
PeekNext()
{
  if (mAsnWords.size() > mCurrentAsnWordIndex + 1)
  {
    return mAsnWords.at(mCurrentAsnWordIndex + 1);
  }

  return std::nullopt;
}

void
AsnData::
IncrementCurrentIndex()
{
  ++mCurrentAsnWordIndex;
}

void
AsnData::
ResetCurrentIndex()
{
  mCurrentAsnWordIndex = 0;
}
