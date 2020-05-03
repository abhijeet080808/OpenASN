#!/usr/bin/env python3

import re

def camel_case_to_snake_case(string):
    # HTTPResponseCode" -> "HTTP_ResponseCode"
    string = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', string)
    # "HTTP_ResponseCode" -> "HTTP_Response_Code"
    string = re.sub('([a-z0-9])([A-Z])', r'\1_\2', string)
    # "HTTP_Response_Code" -> "HTTP_RESPONSE_CODE"
    return string.upper()


def append_may_parse(fd, production, indentation):
    uc_production = camel_case_to_snake_case(production)
    lc_production = uc_production.lower()
    ind = " " * indentation

    fd.write(ind + "{ // MAY PARSE %s\n" % production)
    fd.write(ind + "  auto obj = \"%s\";\n" % production)
    fd.write(ind + "  LOG_START();\n")
    fd.write(ind + "  auto %s = \n" % lc_production)
    fd.write(ind + "    ProductionFactory::Get(Production::%s);\n" % uc_production)
    fd.write(ind + "  if (%s->Parse(asnData, asnDataIndex, endStop, parsePath))\n" %
             lc_production)
    fd.write(ind + "  {\n")
    fd.write(ind + "    m%s = %s;\n" % (production, lc_production))
    fd.write(ind + "    LOG_PASS();\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "  else\n")
    fd.write(ind + "  {\n")
    fd.write(ind + "    asnDataIndex = starting_index;\n")
    fd.write(ind + "    LOG_FAIL();\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "}\n")


def append_must_parse(fd, production, indentation):
    uc_production = camel_case_to_snake_case(production)
    lc_production = uc_production.lower()
    ind = " " * indentation

    fd.write(ind + "{ // MUST PARSE %s\n" % production)
    fd.write(ind + "  auto obj = \"%s\";\n" % production)
    fd.write(ind + "  LOG_START();\n")
    fd.write(ind + "  auto %s = \n" % lc_production)
    fd.write(ind + "    ProductionFactory::Get(Production::%s);\n" % uc_production)
    fd.write(ind + "  if (%s->Parse(asnData, asnDataIndex, endStop, parsePath))\n" %
             lc_production)
    fd.write(ind + "  {\n")
    fd.write(ind + "    m%s = %s;\n" % (production, lc_production))
    fd.write(ind + "    LOG_PASS();\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "  else\n")
    fd.write(ind + "  {\n")
    fd.write(ind + "    LOG_FAIL();\n")
    fd.write(ind + "    return false;\n")
    fd.write(ind + "  }\n")
    fd.write(ind + "}\n")


def append_parse_production_group_decl(fd, production_group, indentation):
    ind = " " * indentation

    prod_grp = ''.join(production_group)
    if prod_grp != "empty":
        fd.write(ind + "bool Parse%s(\n" % prod_grp)
        fd.write(ind + "  const std::vector<Word>& asnData,\n")
        fd.write(ind + "  size_t& asnDataIndex,\n")
        fd.write(ind + "  std::vector<std::string>& endStop,\n")
        fd.write(ind + "  std::vector<std::string>& parsePath);\n")


def append_parse_production_group_defn(fd,
                                       production_name,
                                       production_group,
                                       indentation):
    ind = " " * indentation

    prod_grp = ''.join(production_group)
    if prod_grp != "empty":
        fd.write(ind + "bool\n")
        fd.write(ind + "%s::\n" % production_name)
        fd.write(ind + "Parse%s(\n" % prod_grp)
        fd.write(ind + "  const std::vector<Word>& asnData,\n")
        fd.write(ind + "  size_t& asnDataIndex,\n")
        fd.write(ind + "  std::vector<std::string>& endStop,\n")
        fd.write(ind + "  std::vector<std::string>& parsePath)\n")
        fd.write(ind + "{\n")

        for production in production_group:
            append_must_parse(fd, production, indentation + 2)

        fd.write(ind + "  return true;\n")
        fd.write(ind + "}\n")


def read_file():
    with open("x_680_productions.asn1", "r") as fd:
        words = fd.read().split()
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


def generate_cpp_header(production, production_or_groups):
    production_name = production[0]

    excluded_words = ["|", "\"..\"", "empty"]

    member_variables = []
    for word in production[2:]:
        if word not in excluded_words:
            member_variables.append(word)

    fd = open(production_name + ".hh", "w")

    fd.write("#pragma once\n")
    fd.write("\n")
    fd.write("#include \"IProduction.hh\"\n")
    fd.write("\n")
    fd.write("#include <memory>\n")
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
    fd.write("        std::vector<std::string>& parsePath) override;\n")
    fd.write("\n")
    fd.write("    private:\n")

    for production_group in production_or_groups:
        append_parse_production_group_decl(fd, production_group, 6)

    fd.write("\n")
    fd.write("    public:\n")
    for var in member_variables:
        fd.write("      std::shared_ptr<IProduction> m%s;\n" % var)
    fd.write("  };\n")
    fd.write("}\n")

    fd.close()
    print("Generated %s.hh" % production_name)


def generate_cpp_source(production, production_or_groups):
    production_name = production[0]

    fd = open(production_name + ".cpp", "w")

    fd.write("#include \"%s.hh\"\n" % production_name)
    fd.write("\n")
    fd.write("#include \"LoggingMacros.hh\"\n")
    fd.write("#include \"ParseHelper.hh\"\n")
    fd.write("#include \"ProductionFactory.hh\"\n")
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
    fd.write("  std::vector<std::string>& parsePath)\n")
    fd.write("{\n")

    fd.write("  //")
    for word in production:
        fd.write(" %s" % word)
    fd.write("\n")

    fd.write("\n")
    fd.write("  parsePath.push_back(\"%s\");\n" % production_name)
    fd.write("\n")
    fd.write("  size_t starting_index = asnDataIndex;\n")

    empty_present = False
    for production_group in production_or_groups:
        prod_grp = ''.join(production_group)
        if prod_grp != "empty":
            fd.write("\n")
            fd.write("  if (Parse%s(\n" % prod_grp)
            fd.write("        asnData, asnDataIndex, endStop, parsePath))\n")
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

    if not empty_present:
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


def main():
    productions = read_file()
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

        generate_cpp_header(production,
                            production_or_groups)

        generate_cpp_source(production,
                            production_or_groups)


if __name__ == "__main__":
    # execute only if run as a script
    main()

