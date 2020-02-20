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
Peek(int indexOffset)
{
  int index = mCurrentAsnWordIndex + indexOffset;

  if (index >= 0 && mAsnWords.size() > (size_t)index)
  {
    return mAsnWords.at(index);
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
DecrementCurrentIndex()
{
  --mCurrentAsnWordIndex;
}

void
AsnData::
ResetCurrentIndex()
{
  mCurrentAsnWordIndex = 0;
}
