//
// Created by walterineils on 5/7/23.
//

#ifndef LC3_LANGUAGE_EXTENDER_SUBTRACTOPCODE_H
#define LC3_LANGUAGE_EXTENDER_SUBTRACTOPCODE_H

#include <iostream>
#include <vector>
#include <regex>
#include "PseudoOpCode.h"

class SubtractOpCode : public PseudoOpCode
{
public:
    [[nodiscard]] std::string getName() override
    {
        return "SUBTRACT";
    }

    [[nodiscard]] std::vector<std::string> getInitializationLogic() override
    {
        return {};
    }

    [[nodiscard]] std::vector<std::string> getFileEndStatements() override
    {
        return {};
    }

    [[nodiscard]] int getPriority() override
    {
        return 0;
    }

    [[nodiscard]] bool canHandle(const std::string& token) override
    {
        // Form: SUBTRACT R${DESTINATION_REGISTER}, R${SOURCE_REGISTER}, #${VALUE}
        // Or:  SUBTRACT R${DESTINATION_REGISTER}, R${SOURCE_REGISTER}, R${SOURCE_REGISTER}
        std::regex subtractRegex(R"(SUBTRACT R\d{1,2}, R\d{1,2}, (R\d{1,2}|#\d+))");
        return std::regex_match(token, subtractRegex);
    }

    std::vector<std::string> createImmediateSubtraction(int destinationRegister, int sourceRegister, int value)
    {
        std::vector<std::string> result;
        int                      tempRegister = (destinationRegister + 1) % 7;
        if (tempRegister == sourceRegister) {
            tempRegister = (tempRegister + 1) % 7;
        }
        // PUSH_TEMP R${TEMP_REGISTER}
        // AND R${TEMP_REGISTER}, R${TEMP_REGISTER}, #0
        // ADD R${TEMP_REGISTER}, R${TEMP_REGISTER}, #${VALUE}
        // NOT R${TEMP_REGISTER}, R${TEMP_REGISTER}
        // ADD R${DESTINATION_REGISTER}, R${SOURCE_REGISTER}, R${TEMP_REGISTER}
        // POP_TEMP R${TEMP_REGISTER}
        result.push_back("PUSH_TEMP R" + std::to_string(tempRegister));
        result.push_back("AND R" + std::to_string(tempRegister) + ", R" + std::to_string(tempRegister) + ", #0");
        result.push_back("ADD R" + std::to_string(tempRegister) + ", R" + std::to_string(tempRegister) + ", #" +
                         std::to_string(value));
        result.push_back("NOT R" + std::to_string(tempRegister) + ", R" + std::to_string(tempRegister));
        result.push_back(
                "ADD R" + std::to_string(destinationRegister) + ", R" + std::to_string(sourceRegister) + ", R" +
                std::to_string(tempRegister));
        result.push_back("POP_TEMP R" + std::to_string(tempRegister));
        return result;
    }

    std::vector<std::string>
    createRegisterSubtraction(int destinationRegister, int sourceRegister, int rightSourceRegister)
    {
        std::vector<std::string> result;
        int                      tempRegister = (destinationRegister + 1) % 7;
        if (tempRegister == sourceRegister) {
            tempRegister = (tempRegister + 1) % 7;
        }
        // PUSH_TEMP R${TEMP_REGISTER}
        // AND R${TEMP_REGISTER}, R${TEMP_REGISTER}, #0
        // ADD R${TEMP_REGISTER}, R${TEMP_REGISTER}, R${RIGHT_SOURCE_REGISTER}
        // NOT R${TEMP_REGISTER}, R${TEMP_REGISTER}
        // ADD R${DESTINATION_REGISTER}, R${SOURCE_REGISTER}, R${TEMP_REGISTER}
        // POP_TEMP R${TEMP_REGISTER}
        result.push_back("PUSH_TEMP R" + std::to_string(tempRegister));
        result.push_back("AND R" + std::to_string(tempRegister) + ", R" + std::to_string(tempRegister) + ", #0");
        result.push_back("ADD R" + std::to_string(tempRegister) + ", R" + std::to_string(tempRegister) + ", R" +
                         std::to_string(rightSourceRegister));
        result.push_back("NOT R" + std::to_string(tempRegister) + ", R" + std::to_string(tempRegister));
        result.push_back(
                "ADD R" + std::to_string(destinationRegister) + ", R" + std::to_string(sourceRegister) + ", R" +
                std::to_string(tempRegister));
        result.push_back("POP_TEMP R" + std::to_string(tempRegister));
        return result;
    }

    [[nodiscard]] std::vector<std::string> handleToken(const std::string& token) override
    {
        std::regex  subtractRegex(R"(SUBTRACT R(\d{1,2}), R(\d{1,2}), (R\d{1,2}|#\d+))");
        std::smatch match;
        std::regex_match(token, match, subtractRegex);
        bool isImmediate = match[3].str().find('#') != std::string::npos;
        if (isImmediate) {
            int destinationRegister = std::stoi(match[1].str());
            int sourceRegister      = std::stoi(match[2].str());
            int value               = std::stoi(match[3].str().substr(1));
            return createImmediateSubtraction(destinationRegister, sourceRegister, value);
        }
        else {
            int destinationRegister = std::stoi(match[1].str());
            int sourceRegister      = std::stoi(match[2].str());
            int rightSourceRegister = std::stoi(match[3].str().substr(1));
            return createRegisterSubtraction(destinationRegister, sourceRegister, rightSourceRegister);
        }
    }
};


#endif //LC3_LANGUAGE_EXTENDER_SUBTRACTOPCODE_H
