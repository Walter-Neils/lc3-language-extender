//
// Created by walterineils on 5/4/23.
//

#ifndef LC3_LANGUAGE_EXTENDER_PSEUDOOPCODE_H
#define LC3_LANGUAGE_EXTENDER_PSEUDOOPCODE_H

#include <iostream>
#include <vector>

class PseudoOpCode
{
public:
    [[nodiscard]] virtual std::string getName()
    {
        return typeid(*this).name();
    }

    /// @brief Produces initialization logic to be inserted at the beginning of the program.
    [[nodiscard]] virtual std::vector<std::string> getInitializationLogic() = 0;

    [[nodiscard]] virtual std::vector<std::string> getFileEndStatements() = 0;

    /// @brief Determines what order the PseudoOpCode replacements should be performed in.
    [[nodiscard]] virtual int getPriority() = 0;

    /// @brief Determines if the PseudoOpCode can handle the given token.
    [[nodiscard]] virtual bool canHandle(const std::string& token) = 0;

    /// @brief Handles the given token. Source token line is replaced for the result tokens.
    [[nodiscard]] virtual std::vector<std::string> handleToken(const std::string& token) = 0;
};


#endif //LC3_LANGUAGE_EXTENDER_PSEUDOOPCODE_H
