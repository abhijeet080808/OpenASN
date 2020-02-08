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

std::tuple<AsnData::PrecedingInfo, std::string, AsnData::SucceedingInfo>
AsnData::
PeekPrev()
{
  return mAsnData.at(mCurrentAsnDataIndex - 1);
}

std::tuple<AsnData::PrecedingInfo, std::string, AsnData::SucceedingInfo>
AsnData::
PeekCurrent()
{
  return mAsnData.at(mCurrentAsnDataIndex);
}

std::tuple<AsnData::PrecedingInfo, std::string, AsnData::SucceedingInfo>
AsnData::
PeekNext()
{
  return mAsnData.at(mCurrentAsnDataIndex + 1);
}

std::tuple<AsnData::PrecedingInfo, std::string, AsnData::SucceedingInfo>
AsnData::
Get()
{
  return mAsnData.at(mCurrentAsnDataIndex++);
}

void
AsnData::
ResetCurrentIndex()
{
  mCurrentAsnDataIndex = 0;
}
