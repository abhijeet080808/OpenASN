#include "ExceptionSpec.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ExceptionSpec::
GetType() const
{
  return Production::EXCEPTION_SPEC;
}

bool
ExceptionSpec::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ExceptionSpec");

  // ExceptionSpec ::= "!" ExceptionIdentification | empty

  size_t starting_index = asnDataIndex;

  auto obj = "!";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    parsePath.pop_back();
    return true;
  }

  obj = "ExceptionIdentification";
  LOG_START();
  auto exception_identification =
    ProductionFactory::Get(Production::EXCEPTION_IDENTIFICATION);
  if (exception_identification->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mExceptionIdentification = exception_identification;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }
}
