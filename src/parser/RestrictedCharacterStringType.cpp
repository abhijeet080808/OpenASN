#include "RestrictedCharacterStringType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RestrictedCharacterStringType::
GetType() const
{
  return Production::RESTRICTED_CHARACTER_STRING_TYPE;
}

bool
RestrictedCharacterStringType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // RestrictedCharacterStringType ::=
  //   BMPString
  // | GeneralString
  // | GraphicString
  // | IA5String
  // | ISO646String
  // | NumericString
  // | PrintableString
  // | TeletexString
  // | T61String
  // | UniversalString
  // | UTF8String
  // | VideotexString
  // | VisibleString

  size_t starting_index = asnDataIndex;

  auto obj = "BMPString";
  LOG_START();
  auto bmp_string =
    ProductionFactory::Get(Production::BMP_STRING);
  if (bmp_string->Parse(asnData, asnDataIndex, endStop))
  {
    mBMPString = bmp_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "GeneralString";
  LOG_START();
  auto general_string =
    ProductionFactory::Get(Production::GENERAL_STRING);
  if (general_string->Parse(asnData, asnDataIndex, endStop))
  {
    mGeneralString = general_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "GraphicString";
  LOG_START();
  auto graphic_string =
    ProductionFactory::Get(Production::GRAPHIC_STRING);
  if (graphic_string->Parse(asnData, asnDataIndex, endStop))
  {
    mGraphicString = graphic_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "IA5String";
  LOG_START();
  auto ia5_string =
    ProductionFactory::Get(Production::IA5_STRING);
  if (ia5_string->Parse(asnData, asnDataIndex, endStop))
  {
    mIA5String = ia5_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "ISO646String";
  LOG_START();
  auto iso646_string =
    ProductionFactory::Get(Production::ISO646_STRING);
  if (iso646_string->Parse(asnData, asnDataIndex, endStop))
  {
    mISO646String = iso646_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "NumericString";
  LOG_START();
  auto numeric_string =
    ProductionFactory::Get(Production::NUMERIC_STRING);
  if (numeric_string->Parse(asnData, asnDataIndex, endStop))
  {
    mNumericString = numeric_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "PrintableString";
  LOG_START();
  auto printable_string =
    ProductionFactory::Get(Production::PRINTABLE_STRING);
  if (printable_string->Parse(asnData, asnDataIndex, endStop))
  {
    mPrintableString = printable_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "T61String";
  LOG_START();
  auto t61_string =
    ProductionFactory::Get(Production::T61_STRING);
  if (t61_string->Parse(asnData, asnDataIndex, endStop))
  {
    mT61String = t61_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "TeletexString";
  LOG_START();
  auto teletex_string =
    ProductionFactory::Get(Production::TELETEX_STRING);
  if (teletex_string->Parse(asnData, asnDataIndex, endStop))
  {
    mTeletexString = teletex_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "UniversalString";
  LOG_START();
  auto universal_string =
    ProductionFactory::Get(Production::UNIVERSAL_STRING);
  if (universal_string->Parse(asnData, asnDataIndex, endStop))
  {
    mUniversalString = universal_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "UTF8String";
  LOG_START();
  auto utf8_string =
    ProductionFactory::Get(Production::UTF8_STRING);
  if (utf8_string->Parse(asnData, asnDataIndex, endStop))
  {
    mUTF8String = utf8_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "VideotexString";
  LOG_START();
  auto videotex_string =
    ProductionFactory::Get(Production::VIDEOTEX_STRING);
  if (videotex_string->Parse(asnData, asnDataIndex, endStop))
  {
    mVideotexString = videotex_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "VisibleString";
  LOG_START();
  auto visible_string =
    ProductionFactory::Get(Production::VISIBLE_STRING);
  if (visible_string->Parse(asnData, asnDataIndex, endStop))
  {
    mVisibleString = visible_string;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  asnDataIndex = starting_index;
  return false;
}
