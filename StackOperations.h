//
// Created by walterineils on 5/4/23.
//

#ifndef LC3_LANGUAGE_EXTENDER_STACKOPERATIONS_H
#define LC3_LANGUAGE_EXTENDER_STACKOPERATIONS_H

#include "PseudoOpCode.h"
#include <regex>

class StackOperations : public PseudoOpCode
{
private:
    std::vector<std::string> stackNames;

    std::tuple<std::string, std::string, std::string> getStackComponents(const std::string& stackName)
    {
        // If stackNames does not contain stackName, add it.
        if (std::find(stackNames.begin(), stackNames.end(), stackName) == stackNames.end()) {
            stackNames.push_back(stackName);
        }
        return {"__stack_impl_" + stackName + "_stack_ptr", "__stack_impl_" + stackName + "_temp_save_location",
                "__stack_impl_" + stackName + "_storage"};
    }

    std::vector<std::string> handlePushOperation(const std::string& stackName, int targetRegister)
    {
        auto [stackPointer, temporarySaveLocation, _] = getStackComponents(stackName);
        int  tempRegister                             = (targetRegister + 1) % 7;
        // ST ${tempRegister}, ${temporarySaveLocation}
        // LD ${tempRegister}, ${stackPointer}
        // ADD ${tempRegister}, ${tempRegister}, #1
        // ST ${tempRegister}, ${stackPointer}
        // STI ${targetRegister}, ${stackPointer}
        // LD ${tempRegister}, ${temporarySaveLocation}

        std::vector<std::string> result;
        result.push_back("STI R" + std::to_string(targetRegister) + ", " + stackPointer);
        result.push_back("ST R" + std::to_string(tempRegister) + ", " + temporarySaveLocation);
        result.push_back("LD R" + std::to_string(tempRegister) + ", " + stackPointer);
        result.push_back("ADD R" + std::to_string(tempRegister) + ", R" + std::to_string(tempRegister) + ", #1");
        result.push_back("ST R" + std::to_string(tempRegister) + ", " + stackPointer);
        result.push_back("LD R" + std::to_string(tempRegister) + ", " + temporarySaveLocation);
        return result;
    }

    std::vector<std::string> handlePopOperation(const std::string& stackName, int targetRegister)
    {
        auto [stackPointer, temporarySaveLocation, _] = getStackComponents(stackName);
        int  tempRegister                             = (targetRegister + 1) % 7;
        // ST ${tempRegister}, ${temporarySaveLocation}
        // LD ${tempRegister}, ${stackPointer}
        // ADD ${tempRegister}, ${tempRegister}, #-1
        // ST ${tempRegister}, ${stackPointer}
        // LDI ${targetRegister}, ${stackPointer}
        // LD ${tempRegister}, ${temporarySaveLocation}

        std::vector<std::string> result;
        result.push_back("ST R" + std::to_string(tempRegister) + ", " + temporarySaveLocation);
        result.push_back("LD R" + std::to_string(tempRegister) + ", " + stackPointer);
        result.push_back("ADD R" + std::to_string(tempRegister) + ", R" + std::to_string(tempRegister) + ", #-1");
        result.push_back("ST R" + std::to_string(tempRegister) + ", " + stackPointer);
        result.push_back("LDI R" + std::to_string(targetRegister) + ", " + stackPointer);
        result.push_back("LD R" + std::to_string(tempRegister) + ", " + temporarySaveLocation);
        return result;
    }

    std::vector<std::string> handlePeekOperation(const std::string& stackName, int targetRegister)
    {
        auto [stackPointer, temporarySaveLocation, _] = getStackComponents(stackName);
        int  tempRegister                             = (targetRegister + 1) % 7;
        // ST ${tempRegister}, ${temporarySaveLocation}
        // LD ${tempRegister}, ${stackPointer}
        // LDI ${targetRegister}, ${stackPointer}
        // LD ${tempRegister}, ${temporarySaveLocation}

        std::vector<std::string> result;
        result.push_back("ST R" + std::to_string(tempRegister) + ", " + temporarySaveLocation);
        result.push_back("LD R" + std::to_string(tempRegister) + ", " + stackPointer);
        result.push_back("LDI R" + std::to_string(targetRegister) + ", " + stackPointer);
        result.push_back("LD R" + std::to_string(tempRegister) + ", " + temporarySaveLocation);
        return result;
    }

public:
    /// @brief Produces initialization logic to be inserted at the beginning of the program.
    [[nodiscard]] std::vector<std::string> getInitializationLogic() override
    {
        std::vector<std::string> result;
        for (auto& stackName: stackNames) {
            auto [stackPointer, temporarySaveLocation, stackBlockName] = getStackComponents(stackName);
            // LEA R0, ${stackBlockName}
            // ST R0, ${stackPointer}

            result.push_back("LEA R0, " + stackBlockName);
            result.push_back("ST R0, " + stackPointer);
        }
        return result;
    }

    [[nodiscard]] std::vector<std::string> getFileEndStatements() override
    {
        std::vector<std::string> result;
        for (auto& stackName: stackNames) {
            auto [stackPointer, temporarySaveLocation, stackBlockName] = getStackComponents(stackName);
            // __stack_storage_block_${stackName} .BLKW 256
            // ${stackPointer} .FILL x0
            // ${temporarySaveLocation} .FILL x0

            result.push_back(stackBlockName + " .BLKW #32");
            result.push_back(stackPointer + " .FILL x0");
            result.push_back(temporarySaveLocation + " .FILL x0");
        }
        return result;
    }

    /// @brief Determines what order the PseudoOpCode replacements should be performed in.
    [[nodiscard]] int getPriority() override
    {
        return 0;
    }

    /// @brief Determines if the PseudoOpCode can handle the given token.
    [[nodiscard]] bool canHandle(const std::string& token) override
    {
        // Possible forms:
        // PUSH_${STACK_NAME} ${REGISTER}
        // POP_${STACK_NAME} ${REGISTER}
        // PEEK_${STACK_NAME} ${REGISTER}

        std::regex pushRegex("PUSH_([A-Za-z0-9]+) R([0-7])");
        std::regex popRegex("POP_([A-Za-z0-9]+) R([0-7])");
        std::regex peekRegex("PEEK_([A-Za-z0-9]+) R([0-7])");

        std::smatch pushMatch;
        std::smatch popMatch;
        std::smatch peekMatch;

        if (std::regex_match(token, pushMatch, pushRegex)) {
            return true;
        }
        else if (std::regex_match(token, popMatch, popRegex)) {
            return true;
        }
        else if (std::regex_match(token, peekMatch, peekRegex)) {
            return true;
        }

        return false;
    }

    /// @brief Handles the given token.
    [[nodiscard]] std::vector<std::string> handleToken(const std::string& token) override
    {

        // Possible forms:
        // PUSH_${STACK_NAME} ${REGISTER}
        // POP_${STACK_NAME} ${REGISTER}
        // PEEK_${STACK_NAME} ${REGISTER}

        std::regex pushRegex("PUSH_([A-Za-z0-9]+) R([0-7])");
        std::regex popRegex("POP_([A-Za-z0-9]+) R([0-7])");
        std::regex peekRegex("PEEK_([A-Za-z0-9]+) R([0-7])");

        std::smatch pushMatch;
        std::smatch popMatch;
        std::smatch peekMatch;

        if (std::regex_match(token, pushMatch, pushRegex)) {
            return handlePushOperation(pushMatch[1], std::stoi(pushMatch[2]));
        }
        else if (std::regex_match(token, popMatch, popRegex)) {
            return handlePopOperation(popMatch[1], std::stoi(popMatch[2]));
        }
        else if (std::regex_match(token, peekMatch, peekRegex)) {
            return handlePeekOperation(peekMatch[1], std::stoi(peekMatch[2]));
        }
        else {
            throw std::runtime_error("Invalid token passed to StackOperations PseudoOpCode: " + token);
        }
    }
};


#endif //LC3_LANGUAGE_EXTENDER_STACKOPERATIONS_H
