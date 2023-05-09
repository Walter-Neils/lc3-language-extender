//
// Created by walterineils on 5/7/23.
//

#ifndef LC3_LANGUAGE_EXTENDER_STRINGPRINTOPCODE_H
#define LC3_LANGUAGE_EXTENDER_STRINGPRINTOPCODE_H

#include <iostream>
#include <algorithm>
#include <regex>
#include <vector>
#include "PseudoOpCode.h"

class StringPrintOpCode : public PseudoOpCode
{
private:
    std::vector<std::string> stringInstances;

    std::string getStringLabel(const std::string& value)
    {
        // If stringInstances does not contain value, add it.
        if (std::find(stringInstances.begin(), stringInstances.end(), value) == stringInstances.end()) {
            stringInstances.push_back(value);
        }
        size_t index = std::find(stringInstances.begin(), stringInstances.end(), value) - stringInstances.begin();
        return "__string_impl_" + std::to_string(index);
    }

public:
    [[nodiscard]] std::string getName() override
    {
        return "STRING PRINT";
    }

    [[nodiscard]] std::vector<std::string> getInitializationLogic() override
    {
        return {};
    }

    [[nodiscard]] std::vector<std::string> getFileEndStatements() override
    {
        std::vector<std::string> result;
        for (size_t              i = 0; i < stringInstances.size(); i++) {
            result.push_back("__string_impl_" + std::to_string(i) + " .STRINGZ \"" + stringInstances[i] + "\"");
        }
        return result;
    }

    [[nodiscard]] int getPriority() override
    {
        return 0;
    }

    [[nodiscard]] bool canHandle(const std::string& token) override
    {
        // Form: PRINT "${content}"
        return std::regex_match(token, std::regex(R"(PRINT\s+\".*\")"));
    }

    [[nodiscard]] std::vector<std::string> handleToken(const std::string& token) override
    {
        // Form: PRINT "${content}"
        std::regex  regex(R"(PRINT\s+\"(.*)\")");
        std::smatch match;
        std::regex_match(token, match, regex);
        if (match.size() != 2) {
            throw std::runtime_error("Invalid token: " + token);
        }
        std::string content = match[1].str();
        std::string label   = getStringLabel(content);
        return {"PUSH_TEMP R0", "LEA R0, " + label, "TRAP x22", "POP_TEMP R0"};
    }
};


#endif //LC3_LANGUAGE_EXTENDER_STRINGPRINTOPCODE_H
