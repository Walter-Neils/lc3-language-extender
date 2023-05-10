#include <iostream>
#include <algorithm>

#include "PseudoOpCode.h"
#include "StackOperations.h"
#include "StringPrintOpCode.h"
#include "SubtractOpCode.h"

#define NON_RESULT_OUT std::cerr
#define RESULT_OUT std::cout

const int MAXIMUM_ITERATIONS = 5000;

int main()
{
    std::vector<PseudoOpCode*> pseudoOpCodes;
    pseudoOpCodes.push_back(new StackOperations());
    pseudoOpCodes.push_back(new StringPrintOpCode());
    pseudoOpCodes.push_back(new SubtractOpCode());


    // Sort by priority.
    std::sort(pseudoOpCodes.begin(), pseudoOpCodes.end(), [](PseudoOpCode* a, PseudoOpCode* b) {
        return a->getPriority() > b->getPriority();
    });

    std::vector<std::string> content;

    // File Structure:
    // .ORIG x${SOME_NUMBER}
    // ...
    // .END

    {
        bool        foundOrig = false;
        bool        foundEnd  = false;
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line.find(".ORIG") != std::string::npos) {
                foundOrig = true;
            }
            if (line.find(".END") != std::string::npos) {
                foundEnd = true;
            }
            content.push_back(line);
            if (foundEnd) break;
        }

        if (!foundOrig) {
            throw std::runtime_error("No .ORIG directive found.");
        }
        if (!foundEnd) {
            throw std::runtime_error("No .END directive found.");
        }
    }

    {
        // Remove comments
        for (int i = 0; i < content.size(); i++) {
            auto& line = content[i];
            auto pos = line.find(';');
            if (pos != std::string::npos) {
                line = line.substr(0, pos);
            }
        }

        // Remove lines that are empty or only contain whitespace
        for (int i = 0; i < content.size(); i++) {
            auto& line = content[i];
            if (line.find_first_not_of(' ') == std::string::npos) {
                content.erase(content.begin() + i);
                i--;
            }
        }

        // Remove leading and trailing whitespace
        for (int i = 0; i < content.size(); i++) {
            auto& line = content[i];
            line = line.substr(line.find_first_not_of(' '));
            line = line.substr(0, line.find_last_not_of(' ') + 1);
        }
    }


    for (int i = 0;; i++) {
        bool modified = false;
        for (auto pseudoOpCode: pseudoOpCodes) {
            for (int j = 0; j < content.size(); j++) {
                if (pseudoOpCode->canHandle(content[j])) {
                    NON_RESULT_OUT << "PseudoOpCode " << pseudoOpCode->getName() << " handling token " << content[j] << "\n";
                    auto result = pseudoOpCode->handleToken(content[j]);
                    content.erase(content.begin() + j);
                    content.insert(content.begin() + j, result.begin(), result.end());
                    modified = true;
                }
            }
        }
        if (!modified) {
            break;
        }

        if (i > MAXIMUM_ITERATIONS) {
            throw std::runtime_error("Maximum iterations exceeded.");
        }
    }

    // Sort by priority, lowest first
    std::sort(pseudoOpCodes.begin(), pseudoOpCodes.end(), [](PseudoOpCode* a, PseudoOpCode* b) {
        return a->getPriority() < b->getPriority();
    });

    // Get line with '.ORIG x3000'
    size_t   origLine = 0;
    for (int i        = 0; i < content.size(); i++) {
        if (content[i].find(".ORIG") != std::string::npos) {
            origLine = i;
            break;
        }
    }

    // Insert all initialization logic immediately after .ORIG
    for (auto pseudoOpCode: pseudoOpCodes) {
        auto result = pseudoOpCode->getInitializationLogic();
        content.insert(content.begin() + origLine + 1, result.begin(), result.end());
    }

    // Get line with '.END'
    size_t   endLine = 0;
    for (int i       = 0; i < content.size(); i++) {
        if (content[i].find(".END") != std::string::npos) {
            endLine = i;
            break;
        }
    }

    // Insert all file end statements immediately before .END
    for (auto pseudoOpCode: pseudoOpCodes) {
        auto result = pseudoOpCode->getFileEndStatements();
        content.insert(content.begin() + endLine, result.begin(), result.end());
    }

    for (auto line: content) {
        RESULT_OUT << line << std::endl;
    }


    return 0;
}
