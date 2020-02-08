#include "AsnData.hh"

using namespace OpenASN;

AsnData::
AsnData()
  : mAsnData(),
    mCurrentAsnDataIndex(0)
{
}

void
AsnData::
Insert(PrecedingInfo precedingInfo,
       const std::string& asnWord,
       SucceedingInfo succeedingInfo)
{
  mAsnData.push_back(std::make_tuple(precedingInfo, asnWord, succeedingInfo));
}

size_t
AsnData::
GetSize()
{
  return mAsnData.size();
}

AsnData::Word
AsnData::
PeekPrev()
{
  if (mAsnData.size() > mCurrentAsnDataIndex - 1)
  {
    return mAsnData.at(mCurrentAsnDataIndex - 1);
  }

  return std::nullopt;
}

AsnData::Word
AsnData::
PeekCurrent()
{
  if (mAsnData.size() > mCurrentAsnDataIndex)
  {
    return mAsnData.at(mCurrentAsnDataIndex);
  }

  return std::nullopt;
}

AsnData::Word
AsnData::
PeekNext()
{
  if (mAsnData.size() > mCurrentAsnDataIndex + 1)
  {
    return mAsnData.at(mCurrentAsnDataIndex + 1);
  }

  return std::nullopt;
}

AsnData::Word
AsnData::
Get()
{
  if (mAsnData.size() > mCurrentAsnDataIndex)
  {
    return mAsnData.at(mCurrentAsnDataIndex++);
  }

  return std::nullopt;
}

void
AsnData::
ResetCurrentIndex()
{
  mCurrentAsnDataIndex = 0;
}
