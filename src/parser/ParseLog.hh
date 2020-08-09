#pragma once

#include "ParseDefs.hh"

#include <map>
#include <ostream>
#include <vector>

namespace OpenASN
{
  // This class optimizes the amount of logs that is printed when a production
  // succeeds or fails in parsing. The aim is to reduce irrelevant logs. When a
  // production completes parsing, whether its success or failure logs get
  // printed will depend on whether its parent production succeeded or failed.
  // If a production's parent production succeeds, its failure logs are marked
  // as suppressed.
  //
  // Possible scenarios -
  //
  // ---------------------------------------------------------------------------
  // Child Production  | Parent Production | Action
  // Parse Status      | Parse Status      |
  // ---------------------------------------------------------------------------
  // Pass              | Fail              | Print child log
  // Fail              | Fail              | Print child log
  // Pass              | Pass              | Print child log
  // Fail              | Pass              | Supress child log
  //
  // When a production's logs is marked as suppressed, all of its child's logs
  // are marked as suppressed too.
  //
  // Example -
  //
  // ModuleBody - Passed
  //   AssignmentList - Passed
  //     Assignment - Passed
  //       TypeAssignment - Passed
  //         Type - Passed
  //           BuiltinType - Passed
  //             BitStringType - Failed
  //             BooleanType - Passed
  //           ConstraintList - Failed
  //             Constraint - Failed
  //           BuiltinType - Passed
  //     Assignment - Passed
  //       TypeAssignment - Passed
  //         Type - Passed
  //           BuiltinType - Passed
  //             BitStringType - Failed
  //             BooleanType - Failed
  //             CharacterStringType - Failed
  //               RestrictedCharacterStringType - Failed
  //                 BMPString - Failed
  //                 GeneralString - Failed
  //                 ...
  //               UnrestrictedCharacterStringType - Failed
  //             ChoiceType - Failed
  //             ...
  //             IntegerType - Passed
  //               INTEGER - Passed
  //           ConstraintList  - Failed
  //             Constraint  - Failed
  //           BuiltinType - Passed
  //     Assignment - Failed
  //       TypeAssignment - Failed
  //       ValueAssignment - Failed
  //       ValueSetTypeAssignment - Failed
  //
  // In the above case, only all success logs will be printed

  #define LOG_START()                                                          \
  {                                                                            \
    ParseLog::GetInstance(asnData).Log(                                        \
      LogEntry{LogAction::STARTED, asnDataIndex, obj, parsePath, false});      \
  }

  #define LOG_PASS()                                                           \
  {                                                                            \
    ParseLog::GetInstance(asnData).Log(                                        \
      LogEntry{LogAction::PASSED, asnDataIndex, obj, parsePath, false});       \
  }

  #define LOG_FAIL()                                                           \
  {                                                                            \
    ParseLog::GetInstance(asnData).Log(                                        \
      LogEntry{LogAction::FAILED, asnDataIndex, obj, parsePath, false});       \
  }

  enum class LogAction
  {
    STARTED,
    PASSED,
    FAILED
  };

  struct LogEntry
  {
    bool operator<(const LogEntry& rhs) const;

    LogAction mAction;
    // Index of current ASN word
    size_t mAsnDataIndex;
    // Production this log applies to
    std::string mCurrentProduction;
    // Path leading to the current production
    std::vector<std::string> mProductionPath;

    // True if this log is suppressed
    bool mIsSuppressed;
  };

  class ParseLog
  {
  public:
    static ParseLog& GetInstance(const std::vector<Word>& asnData);

  public:
    void Log(const LogEntry& logEntry);
    void Dump();

  private:
    ParseLog(const std::vector<Word>& asnData);

    bool isParentLogEntryPassed(const LogEntry& logEntry);
    void markAsSuppressed(const LogEntry& logEntry);
    void printLogStr(const LogEntry& logEntry);

  private:
    const std::vector<Word>& mAsnData;

    std::vector<LogEntry> mLogEntryList;

    // Look up to find all child and sub child log entries falling under a
    // given parent production path. The log entry is denoted by its index
    // as per mLogEntryList.
    //
    // Eg - ModuleDefinition>ModuleIdentifier>DefinitiveIdentification log
    // will be filed under -
    //   { ModuleDefinition }
    //   { ModuleDefinition, ModuleIdentifier }
    //   { ModuleDefinition, ModuleIdentifier, DefinitiveIdentification }
    std::map<std::vector<std::string>, std::vector<size_t>> mLogEntryTree;

    // Lookup to find logs filed under a specific production path (and not
    // its child path as above)
    std::map<std::vector<std::string>, std::vector<size_t>> mLogEntryMap;
  };

  std::ostream& operator<<(std::ostream& out, const LogAction& val);
}
