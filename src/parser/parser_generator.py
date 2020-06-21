#!/usr/bin/env python3

import argparse
import re

def camel_case_to_snake_case(string):
    # HTTPResponseCode" -> "HTTP_ResponseCode"
    string = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', string)
    # "HTTP_ResponseCode" -> "HTTP_Response_Code"
    string = re.sub('([a-z0-9])([A-Z])', r'\1_\2', string)
    # "HTTP_Response_Code" -> "HTTP_RESPONSE_CODE"
    return string.upper()


def append_must_parse(fd,
                      production,
                      indentation,
                      end_stop_production):
    ind = " " * indentation

    # Escape double quote for C++ code
    if end_stop_production == "\"":
        end_stop_production = "\\\""

    cpp_production = get_cpp_production_name(production)
    uc_production = camel_case_to_snake_case(cpp_production)

    if (end_stop_production):
        fd.write(ind + "endStop.push_back(\"%s\");\n" % end_stop_production)
        fd.write("\n")
    fd.write(ind + "{ // Parsing %s\n" % cpp_production)
    fd.write(ind + "  auto obj = \"%s\";\n" % cpp_production)
    fd.write(ind + "  LOG_START();\n")
    fd.write("\n")
    fd.write(ind + "  auto prod_index = std::make_pair(\n")
    fd.write(ind + "    asnDataIndex,\n")
    fd.write(ind + "    Production::%s);\n" % uc_production)
    fd.write(ind + "  auto existing_prod_iter = " +
        "parseHistory.find(prod_index);\n")
    fd.write("\n")
    fd.write(ind + "  auto prod = ProductionFactory::Get(\n")
    fd.write(ind + "    Production::%s);\n" % uc_production)
    fd.write("\n")
    fd.write(ind + "  // If this production has already been parsed " +
        "at this same asnDataIndex,\n")
    fd.write(ind + "  // do not parse it again but re-use old production\n")
    fd.write(ind + "  if (existing_prod_iter != parseHistory.end())\n")
    fd.write(ind + "  {\n")
    fd.write(ind + "    if (existing_prod_iter->second.first.get() " +
        "!= nullptr)\n")
    fd.write(ind + "    {\n")
    if (end_stop_production):
        fd.write(ind + "      endStop.pop_back();\n")
    fd.write(ind + "      m%s = existing_prod_iter->second.first;\n"
        % cpp_production)
    fd.write(ind + "      asnDataIndex = existing_prod_iter->second.second;\n")
    fd.write(ind + "      LOG_PASS();\n")
    fd.write(ind + "    }\n")
    fd.write(ind + "    else\n")
    fd.write(ind + "    {\n")
    if (end_stop_production):
        fd.write(ind + "      endStop.pop_back();\n")
    fd.write(ind + "      LOG_FAIL();\n")
    fd.write(ind + "      return false;\n")
    fd.write(ind + "    }\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "  else if (prod->Parse(\n")
    fd.write(ind + "    " +
        "asnData, asnDataIndex, endStop, parsePath, parseHistory))\n")
    fd.write(ind + "  {\n")
    if (end_stop_production):
        fd.write(ind + "    endStop.pop_back();\n")
    fd.write(ind + "    m%s = prod;\n" % (cpp_production))
    fd.write(ind + "    // Store the production and asnDataIndex after " +
        "parse consumes one or more\n")
    fd.write(ind + "    // words, for later use if necessary\n")
    fd.write(ind + "    parseHistory[prod_index] = " +
        "std::make_pair(prod, asnDataIndex);\n")
    fd.write(ind + "    LOG_PASS();\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "  else\n")
    fd.write(ind + "  {\n")
    if (end_stop_production):
        fd.write(ind + "    endStop.pop_back();\n")
    fd.write(ind + "    parseHistory[prod_index] = " +
        "std::make_pair(nullptr, 0);\n")
    fd.write(ind + "    LOG_FAIL();\n")
    fd.write(ind + "    return false;\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "}\n")
    fd.write("\n")


def is_non_char_production(production):
    # true for non quoted production like ModuleBody etc
    return production[0] != "\"" and \
           production[-1] != "\"" and \
           len(production) > 0


def is_char_production(production):
    # true for quoted productions like "::=", "DATE-TIME" etc
    return production[0] == "\"" and \
           production[-1] == "\"" and \
           len(production) > 2


def is_reserved_production(production):
    # following from ParseHelper::IsReserved
    # true for quoted productions like "ABSENT", "DATE-TIME" etc
    # false for quoted productions like "::=" "," etc

    if is_char_production(production) is False:
        return False

    if production[1:-1] == "-":
        return False

    for char in production[1:-1]:
        if char.isalpha() is False and \
           char.isdigit() is False and \
           char != "-":
            return False

    return True


def get_cpp_production_name(production):
    # remove quotes if needed
    if is_non_char_production(production) is False:
        production = production[1:-1]

    # remove hyphen if present and capitalise first word after hyphen
    production = re.sub('(-)(.)', lambda m: m.group(2).upper(), production)

    # capitalize first character
    return production[0].upper() + production[1:]


def append_char_must_parse(fd, production, indentation):
    ind = " " * indentation

    # Escape double quote for C++ code
    if production == "\"":
        production = "\\\""

    fd.write(ind + "{ // Parsing \"%s\"\n" % production)
    fd.write(ind + "  auto obj = \"%s\";\n" % production)
    fd.write(ind + "  LOG_START();\n")
    fd.write(ind + "  if (ParseHelper::IsObjectPresent(" \
             "obj, asnData, asnDataIndex))\n")
    fd.write(ind + "  {\n")
    fd.write(ind + "    ++asnDataIndex;\n")
    fd.write(ind + "    LOG_PASS();\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "  else\n")
    fd.write(ind + "  {\n")
    fd.write(ind + "    LOG_FAIL();\n")
    fd.write(ind + "    return false;\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "}\n")
    fd.write("\n")


def get_parse_production_group_fn_name(production_group):
    # remove all literals like "..", "," from the function name
    fn_name = ""
    for production in production_group:
        if is_non_char_production(production) == True:
            fn_name += get_cpp_production_name(production)
        elif is_char_production(production) == True:
            if is_reserved_production(production) == True:
                fn_name += get_cpp_production_name(production)
            elif production[1:-1] == "(":
                fn_name += "RoundOpenBracket"
            elif production[1:-1] == ")":
                fn_name += "RoundCloseBracket"
            elif production[1:-1] == "{":
                fn_name += "CurlyOpenBracket"
            elif production[1:-1] == "}":
                fn_name += "CurlyCloseBracket"
            elif production[1:-1] == "[":
                fn_name += "SquareOpenBracket"
            elif production[1:-1] == "]":
                fn_name += "SquareCloseBracket"
            elif production[1:-1] == ",":
                fn_name += "Comma"
            elif production[1:-1] == ".":
                fn_name += "SingleDot"
            elif production[1:-1] == "..":
                fn_name += "DoubleDot"
            elif production[1:-1] == "...":
                fn_name += "TripleDot"
            elif production[1:-1] == ":":
                fn_name += "Colon"
            elif production[1:-1] == "!":
                fn_name += "Not"
            elif production[1:-1] == "^":
                fn_name += "Caret"
            elif production[1:-1] == "\"":
                fn_name += "DoubleQuote"
            elif production[1:-1] == "/":
                fn_name += "ForwardSlash"
            elif production[1:-1] == "|":
                fn_name += "VerticalSlash"
            elif production[1:-1] == "<":
                fn_name += "LessThan"
            elif production[1:-1] == "::=":
                fn_name += "ColonColonEqual"
            elif production[1:-1] == "=":
                fn_name += "Equal"
            elif production[1:-1] == "-":
                fn_name += "Hyphen"
            elif production[1:-1] == "*":
                fn_name += "Asterisk"
            else:
                raise ValueError("Unknown char production %s", production)

    return fn_name


def append_parse_production_group_decl(fd, production_group, indentation):
    ind = " " * indentation

    prod_grp_fn = get_parse_production_group_fn_name(production_group)
    if prod_grp_fn.lower() != "empty":
        fd.write(ind + "bool Parse%s(\n" % prod_grp_fn)
        fd.write(ind + "  const std::vector<Word>& asnData,\n")
        fd.write(ind + "  size_t& asnDataIndex,\n")
        fd.write(ind + "  std::vector<std::string>& endStop,\n")
        fd.write(ind + "  std::vector<std::string>& parsePath,\n")
        fd.write(ind + "  ProductionParseHistory& parseHistory);\n")
        fd.write("\n")


def append_parse_production_group_defn(fd,
                                       production_name,
                                       production_group,
                                       indentation):
    ind = " " * indentation

    prod_grp_fn = get_parse_production_group_fn_name(production_group)
    if prod_grp_fn.lower() != "empty":
        fd.write(ind + "bool\n")
        fd.write(ind + "%s::\n" % production_name)
        fd.write(ind + "Parse%s(\n" % prod_grp_fn)
        fd.write(ind + "  const std::vector<Word>& asnData,\n")
        fd.write(ind + "  size_t& asnDataIndex,\n")
        fd.write(ind + "  std::vector<std::string>& endStop,\n")
        fd.write(ind + "  std::vector<std::string>& parsePath,\n")
        fd.write(ind + "  ProductionParseHistory& parseHistory)\n")
        fd.write(ind + "{\n")

        is_non_char_prod_present = False

        for prod_index, production in enumerate(production_group):
            # Fetch the next suitable production that is to be used as
            # end stop for current production if it is a non char production
            end_stop_production = None
            for next_production in production_group[prod_index + 1:]:
                if is_char_production(next_production) is True:
                    if is_reserved_production(next_production) is True:
                        end_stop_production = next_production[1:-1]
                        break
                    else:
                        end_stop_production = next_production[1:2]
                        break

            # Add code for current production
            if is_char_production(production) is True:
                if is_reserved_production(production) is True:
                    append_char_must_parse(fd,
                                           production[1:-1],
                                           indentation + 2)
                else:
                    for char in production[1:-1]:
                        append_char_must_parse(fd,
                                               char,
                                               indentation + 2)
            else:
                append_must_parse(fd,
                                  production,
                                  indentation + 2,
                                  end_stop_production)
                is_non_char_prod_present = True

        if is_non_char_prod_present is False:
            fd.write(ind + "  (void)(parseHistory);\n")
            fd.write(ind + "  (void)(endStop);\n")

        fd.write(ind + "  return true;\n")
        fd.write(ind + "}\n")


def read_file(asn_file):
    words = []

    with open(asn_file, "r") as fd:
        for line in fd:
            line = line.partition('--')[0]
            line = line.rstrip()
            words.extend(line.split())

    productions = []
    production = []
    for word in words:
        if word == "::=" and "::=" in production:
            production.append(word)
            # there is only one word that prepends ::=
            productions.append(production[:-2])
            del(production[:-2])
        else:
            production.append(word)

    if production:
        productions.append(production[:])

    #print(productions)
    return productions


def generate_production_cpp_header(production, production_or_groups):
    production_name = production[0]

    excluded_words = ["|", "empty"]

    member_variables = []
    for word in production[2:]:
        if word not in excluded_words and is_non_char_production(word) == True:
            member_variables.append(get_cpp_production_name(word))
    # remove duplicate productions that are part of more than 1 production group
    member_variables = list(dict.fromkeys(member_variables))

    fd = open(production_name + ".hh", "w")

    fd.write("///////////////////////////////////////\n")
    fd.write("// THIS HEADER FILE IS AUTOGENERATED //\n")
    fd.write("///////////////////////////////////////\n")
    fd.write("\n")
    fd.write("#pragma once\n")
    fd.write("\n")
    fd.write("#include \"parser/IProduction.hh\"\n")
    fd.write("\n")
    fd.write("namespace OpenASN\n")
    fd.write("{\n")
    fd.write("  // X.680 08/2015 Annex L\n")
    fd.write("  class %s : public IProduction\n" % production_name)
    fd.write("  {\n")
    fd.write("    public:\n")
    fd.write("      Production GetType() const override;\n")
    fd.write("\n")
    fd.write("      bool Parse(\n")
    fd.write("        const std::vector<Word>& asnData,\n")
    fd.write("        size_t& asnDataIndex,\n")
    fd.write("        std::vector<std::string>& endStop,\n")
    fd.write("        std::vector<std::string>& parsePath,\n")
    fd.write("        ProductionParseHistory& parseHistory) override;\n")
    fd.write("\n")
    fd.write("    private:\n")

    for production_group in production_or_groups:
        append_parse_production_group_decl(fd, production_group, 6)

    if member_variables:
        fd.write("    public:\n")
        for var in member_variables:
            fd.write("      std::shared_ptr<IProduction> m%s;\n" % var)

    fd.write("  };\n")
    fd.write("}\n")

    fd.close()
    print("Generated %s.hh" % production_name)


def generate_production_cpp_source(production, production_or_groups):
    production_name = production[0]

    fd = open(production_name + ".cpp", "w")

    fd.write("///////////////////////////////////////\n")
    fd.write("// THIS SOURCE FILE IS AUTOGENERATED //\n")
    fd.write("///////////////////////////////////////\n")
    fd.write("\n")
    fd.write("#include \"%s.hh\"\n" % production_name)
    fd.write("\n")
    fd.write("#include \"parser/LoggingMacros.hh\"\n")
    fd.write("#include \"parser/ParseHelper.hh\"\n")
    fd.write("#include \"parser/ProductionFactory.hh\"\n")
    fd.write("\n")
    fd.write("#include \"spdlog/spdlog.h\"\n")
    fd.write("\n")
    fd.write("using namespace OpenASN;\n")
    fd.write("\n")
    fd.write("Production\n")
    fd.write("%s::\n" % production_name)
    fd.write("GetType() const\n")
    fd.write("{\n")
    fd.write("  return Production::%s;\n" %
               camel_case_to_snake_case(production_name))
    fd.write("}\n")
    fd.write("\n")
    fd.write("bool\n")
    fd.write("%s::\n" % production_name)
    fd.write("Parse(\n")
    fd.write("  const std::vector<Word>& asnData,\n")
    fd.write("  size_t& asnDataIndex,\n")
    fd.write("  std::vector<std::string>& endStop,\n")
    fd.write("  std::vector<std::string>& parsePath,\n")
    fd.write("  ProductionParseHistory& parseHistory)\n")
    fd.write("{\n")

    fd.write("  //")
    for word in production:
        fd.write(" %s" % word)
        if word == "::=" or word == "|":
            fd.write("\n  //  ")
    fd.write("\n")

    fd.write("\n")
    fd.write("  parsePath.push_back(\"%s\");\n" % production_name)
    fd.write("  size_t starting_index = asnDataIndex;\n")

    empty_present = False
    for production_group in production_or_groups:
        prod_grp_fn = get_parse_production_group_fn_name(production_group)
        if prod_grp_fn.lower() != "empty":
            fd.write("\n")
            fd.write("  if (Parse%s(\n" % prod_grp_fn)
            fd.write("        " +
                "asnData, asnDataIndex, endStop, " +
                "parsePath, parseHistory))\n")
            fd.write("  {\n")
            fd.write("    parsePath.pop_back();\n");
            fd.write("    return true;\n")
            fd.write("  }\n")
            fd.write("  else\n")
            fd.write("  {\n")
            fd.write("    asnDataIndex = starting_index;\n")
            fd.write("  }\n")
        else:
            empty_present = True
            fd.write("\n")
            fd.write("  // empty production\n")
            fd.write("  parsePath.pop_back();\n");
            fd.write("  return true;\n")

    if empty_present is False:
        fd.write("\n")
        fd.write("  parsePath.pop_back();\n");
        fd.write("  return false;\n")

    fd.write("}\n")

    for production_group in production_or_groups:
        fd.write("\n")
        append_parse_production_group_defn(fd,
                                           production_name,
                                           production_group,
                                           0)

    fd.close()
    print("Generated %s.cpp" % production_name)


def generate_production_factory_cpp_header():
    fd = open("ProductionFactory.hh", "w")

    fd.write("///////////////////////////////////////\n")
    fd.write("// THIS HEADER FILE IS AUTOGENERATED //\n")
    fd.write("///////////////////////////////////////\n")
    fd.write("\n")
    fd.write("#pragma once\n")
    fd.write("\n")
    fd.write("#include \"parser/IProduction.hh\"\n")
    fd.write("\n")
    fd.write("namespace OpenASN\n")
    fd.write("{\n")
    fd.write("  class ProductionFactory\n")
    fd.write("  {\n")
    fd.write("      public:\n")
    fd.write("        static std::shared_ptr<IProduction> " +
             "Get(Production production);\n")
    fd.write("  };\n")
    fd.write("}\n")

    fd.close()
    print("Generated ProductionFactory.hh")


def generate_production_factory_cpp_source(production_names):
    fd = open("ProductionFactory.cpp", "w")

    fd.write("///////////////////////////////////////\n")
    fd.write("// THIS SOURCE FILE IS AUTOGENERATED //\n")
    fd.write("///////////////////////////////////////\n")
    fd.write("\n")
    fd.write("#include \"parser/ProductionFactory.hh\"\n")
    fd.write("\n")

    for production_name in production_names:
        fd.write("#include \"parser/%s.hh\"\n" % production_name)

    fd.write("\n")
    fd.write("#include <cassert>\n")
    fd.write("\n")
    fd.write("using namespace OpenASN;\n")
    fd.write("\n")
    fd.write("std::shared_ptr<IProduction>\n")
    fd.write("ProductionFactory::\n")
    fd.write("Get(Production production)\n")
    fd.write("{\n")
    fd.write("  switch (production)\n")
    fd.write("  {\n")

    for production_name in production_names:
        uc_production = camel_case_to_snake_case(production_name)

        fd.write("    case Production::%s:\n" % uc_production)
        fd.write("      return std::make_shared<%s>();\n" % production_name)
        fd.write("\n")

    fd.write("    default:\n")
    fd.write("      assert(false);\n")
    fd.write("      return nullptr;\n")

    fd.write("  }\n")
    fd.write("}\n")

    fd.close()
    print("Generated ProductionFactory.cpp")


def generate_production_defs_cpp_header(production_names):
    fd = open("ProductionDefs.hh", "w")

    fd.write("///////////////////////////////////////\n")
    fd.write("// THIS HEADER FILE IS AUTOGENERATED //\n")
    fd.write("///////////////////////////////////////\n")
    fd.write("\n")
    fd.write("#pragma once\n")
    fd.write("\n")
    fd.write("namespace OpenASN\n")
    fd.write("{\n")
    fd.write("  // X.680 08/2015\n")
    fd.write("  enum class Production\n")
    fd.write("  {\n")

    for production_name in production_names:
        uc_production = camel_case_to_snake_case(production_name)
        fd.write("    %s,\n" % uc_production)

    fd.write("\n")
    fd.write("    ENUM_END\n")
    fd.write("  };\n")
    fd.write("}\n")

    fd.close()
    print("Generated ProductionDefs.hh")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-a", "--asn-file",
                        type=str, required=True, nargs=None,
                        help="/path/to/asn_file")
    parser.add_argument("-s", "--static-productions",
                        type=str, required=True, nargs='+',
                        help="List of names of all static productions")
    args = parser.parse_args()

    # productions:
    # [['ModuleBody', '::=', 'AssignmentList', '|', 'empty'],
    #  ['ValueRange', '::=', 'LowerEndpoint', '".."', 'UpperEndpoint']]
    productions = read_file(args.asn_file)
    for production in productions:
        production_or_groups = []
        production_group = []
        for word in production[2:]:
            if word == "|":
                production_or_groups.append(production_group[:])
                production_group.clear()
            else:
                production_group.append(word)

        if production_group:
            production_or_groups.append(production_group[:])

        # production_or_groups:
        # [['AssignmentList'], ['empty']]
        # [['LowerEndpoint', '".."', 'UpperEndpoint']]

        generate_production_cpp_header(production,
                                       production_or_groups)

        generate_production_cpp_source(production,
                                       production_or_groups)

    all_production_names = args.static_productions + \
                           [production[0] for production in productions]
    all_production_names.sort()
    print("List of all productions: %s" % all_production_names)

    generate_production_factory_cpp_header()
    generate_production_factory_cpp_source(all_production_names)

    generate_production_defs_cpp_header(all_production_names)


if __name__ == "__main__":
    # execute only if run as a script
    main()

