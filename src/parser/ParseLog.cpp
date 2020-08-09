#include "ParseLog.hh"

#include "common/StringManip.hh"
#include "spdlog/spdlog.h"

#include <cassert>
#include <sstream>

using namespace OpenASN;

namespace
{
  const bool DEBUG = 0;
}

bool
LogEntry::
operator<(const LogEntry& rhs) const
{
  if (mAction < rhs.mAction) return true;
  if (mAction > rhs.mAction) return false;

  if (mAsnDataIndex < rhs.mAsnDataIndex) return true;
  if (mAsnDataIndex > rhs.mAsnDataIndex) return false;

  if (mCurrentProduction < rhs.mCurrentProduction) return true;
  if (mCurrentProduction > rhs.mCurrentProduction) return false;

  if (mProductionPath.size() < rhs.mProductionPath.size()) return true;
  if (mProductionPath.size() > rhs.mProductionPath.size()) return false;

  auto prod_path = StringManip::Flatten(mProductionPath, ">");
  auto rhs_prod_path = StringManip::Flatten(rhs.mProductionPath, ">");

  if (prod_path < rhs_prod_path) return true;
  if (prod_path > rhs_prod_path) return false;

  if (mIsSuppressed < rhs.mIsSuppressed) return true;
  if (mIsSuppressed > rhs.mIsSuppressed) return false;

  return false;
}

ParseLog&
ParseLog::
GetInstance(const std::vector<Word>& asnData)
{
  static ParseLog p(asnData);
  return p;
}

ParseLog::
ParseLog(const std::vector<Word>& asnData)
  : mAsnData(asnData),
    mLogEntryList(),
    mLogEntryTree(),
    mLogEntryMap()
{
}

void
ParseLog::
Log(const LogEntry& logEntry)
{
  assert(!logEntry.mProductionPath.empty());
  assert(!logEntry.mIsSuppressed);

  mLogEntryList.push_back(logEntry);
  size_t log_index = mLogEntryList.size() - 1;

  if (DEBUG) printLogStr(mLogEntryList.at(log_index));

  std::vector<std::string> prod_path;
  for (const auto& production : logEntry.mProductionPath)
  {
    // Build up the production path by adding 1 production entry at a time
    prod_path.push_back(production);

    if (DEBUG)
    {
      SPDLOG_INFO("Tagged above log to path {}",
                  StringManip::Flatten(prod_path, ">"));
    }

    if (mLogEntryTree.find(prod_path) == mLogEntryTree.end())
    {
      std::vector<size_t> log_index_list;
      log_index_list.push_back(log_index);
      mLogEntryTree.insert(std::make_pair(prod_path, log_index_list));
    }
    else
    {
      mLogEntryTree.at(prod_path).push_back(log_index);
    }
  }

  if (mLogEntryMap.find(logEntry.mProductionPath) == mLogEntryMap.end())
  {
    std::vector<size_t> log_index_list;
    log_index_list.push_back(log_index);
    mLogEntryMap.insert(std::make_pair(prod_path, log_index_list));
  }
  else
  {
    mLogEntryMap.at(prod_path).push_back(log_index);
  }
}

void
ParseLog::
Dump()
{
  SPDLOG_INFO("Suppressing unneeded logs among {} collected logs",
              mLogEntryList.size());

  // TODO - Parse parent logs before parsing child logs.
  // Eg Parse -
  // #>ModuleDefinition0>ModuleIdentifier
  // before
  // #>ModuleDefinition0>ModuleIdentifier>DefinitiveIdentification
  // to prevent trying to iterate same set of logs to suppress
  // and to add back asserts below

  for (const auto& log_entry : mLogEntryList)
  {
    // This entry is already suppressed, nothing more to do
    if (log_entry.mIsSuppressed)
    {
      continue;
    }

    // If log is FAILED and its parent is PASSED, mark itself and all of its
    // child logs as suppressed
    if (log_entry.mAction == LogAction::FAILED)
    {
      if (isParentLogEntryPassed(log_entry))
      {
        markAsSuppressed(log_entry);
      }
    }
  }

  SPDLOG_INFO("Printing logs");

  size_t log_count = 0;
  // Print all logs
  for (const auto& log_entry : mLogEntryList)
  {
    // Do not print suppressed logs
    if (log_entry.mIsSuppressed)
    {
      continue;
    }

    printLogStr(log_entry);
    ++log_count;
  }

  SPDLOG_INFO("Printed {} logs out of {} logs",
              log_count, mLogEntryList.size());

  mLogEntryList.clear();
  mLogEntryTree.clear();
  mLogEntryMap.clear();
}

bool
ParseLog::
isParentLogEntryPassed(const LogEntry& logEntry)
{
  if (logEntry.mProductionPath.size() <= 1)
  {
    // Ignore the "#" prepended at the beginning of the path
    return true;
  }

  std::vector<std::string> mParentProductionPath(
      logEntry.mProductionPath.begin(), logEntry.mProductionPath.end() - 1);

  for (const auto& log_entry_index : mLogEntryMap.at(mParentProductionPath))
  {
    const auto log_entry = mLogEntryList.at(log_entry_index);

    if (log_entry.mAction == LogAction::PASSED &&
        log_entry.mCurrentProduction == logEntry.mProductionPath.back())
    {
      if (DEBUG) printLogStr(logEntry);
      if (DEBUG) SPDLOG_INFO("Above log has pass parent -");
      if (DEBUG) printLogStr(log_entry);
      return true;
    }
    else if (log_entry.mAction == LogAction::FAILED &&
              log_entry.mCurrentProduction == logEntry.mProductionPath.back())
    {
      if (DEBUG) printLogStr(logEntry);
      if (DEBUG) SPDLOG_INFO("Above log has fail parent -");
      if (DEBUG) printLogStr(log_entry);
      return false;
    }
  }

  printLogStr(logEntry);
  SPDLOG_INFO("Above log has no parent log with status of PASSED or FAILED");

  assert(false);
}

void
ParseLog::
markAsSuppressed(const LogEntry& logEntry)
{
  assert(logEntry.mAction == LogAction::FAILED);
  assert(!logEntry.mIsSuppressed);

  std::vector<std::string> full_prod_path = logEntry.mProductionPath;
  full_prod_path.push_back(logEntry.mCurrentProduction);

  if (DEBUG) printLogStr(logEntry);
  if (DEBUG) SPDLOG_INFO("Suppressing itself and child of above log");
  if (DEBUG) SPDLOG_INFO("Path:{}", StringManip::Flatten(full_prod_path, ">"));

  // TODO - Do not suppress PASS logs that are taken from the parseHistory
  // directly

  // Mark all STATUS/PASSED/FAILED log entries matching production path and
  // beyond as suppressed
  if (mLogEntryTree.find(full_prod_path) != mLogEntryTree.end())
  {
    for (const auto& log_entry_index : mLogEntryTree.at(full_prod_path))
    {
      //if (mLogEntryList.at(log_entry_index).mAction == LogAction::FAILED)
      {
        if (DEBUG) printLogStr(mLogEntryList.at(log_entry_index));
        if (DEBUG) SPDLOG_INFO("Suppressing above nested log");

        //assert(!mLogEntryList.at(log_entry_index).mIsSuppressed);

        mLogEntryList.at(log_entry_index).mIsSuppressed = true;
      }
    }
  }

  // Also mark (STATUS) logs related to this FAILED logEntry as suppressed
  for (const auto& log_entry_index : mLogEntryMap.at(logEntry.mProductionPath))
  {
    if (mLogEntryList.at(log_entry_index).mCurrentProduction ==
          logEntry.mCurrentProduction)
    {
      if (DEBUG) printLogStr(mLogEntryList.at(log_entry_index));
      if (DEBUG) SPDLOG_INFO("Suppressing above log");

      //assert(!mLogEntryList.at(log_entry_index).mIsSuppressed);

      mLogEntryList.at(log_entry_index).mIsSuppressed = true;
    }
  }
}

void
ParseLog::
printLogStr(const LogEntry& logEntry)
{
  std::stringstream action_str;
  action_str << logEntry.mAction;

  SPDLOG_INFO("{}: {} parse \"{}\"\n[{}]",
      mAsnData.size() > logEntry.mAsnDataIndex ?
      "[" +
      std::to_string(std::get<4>(mAsnData.at(logEntry.mAsnDataIndex))) +
      ":" +
      std::to_string(std::get<5>(mAsnData.at(logEntry.mAsnDataIndex))) +
      "] \"" +
      std::get<1>(mAsnData.at(logEntry.mAsnDataIndex)) +
      "\"" :
      "[-:-] \"<EOF>\"",
      action_str.str(),
      logEntry.mCurrentProduction,
      StringManip::Flatten(logEntry.mProductionPath, ">"));
}

namespace OpenASN
{
  std::ostream& operator<<(std::ostream& out, const LogAction& val)
  {
    switch (val)
    {
      case LogAction::STARTED:
        out << "STARTED";
        break;
      case LogAction::PASSED:
        out << "PASSED";
        break;
      case LogAction::FAILED:
        out << "FAILED";
        break;
    }
    return out;
  }
}
