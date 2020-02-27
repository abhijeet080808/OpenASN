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
      std::vector<std::string>& endStop)
{
  // ExceptionSpec ::= "!" ExceptionIdentification | empty

  size_t starting_index = asnDataIndex;

  auto obj = "!";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    return true;
  }

  obj = "ExceptionIdentification";
  LOG_START();
  auto exception_identification =
    ProductionFactory::Get(Production::EXCEPTION_IDENTIFICATION);
  if (exception_identification->Parse(asnData, asnDataIndex, endStop))
  {
    mExceptionIdentification = exception_identification;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
