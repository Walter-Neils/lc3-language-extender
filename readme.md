# LC3 Language Extender
## Introduction
The LC3 has an extremely small set of instructions, which makes complex logic difficult to write as the programmer
has an extremely limited set of tools to work with. Simple tasks such as printing a string to the console require many
instructions to be executed, and the programmer must keep track of the state of the machine at all times. 
That's where this program comes in; it allows the programmer to create 'pseudo-instructions' which are then translated
into the appropriate LC3 instructions. This allows the programmer to focus on the logic of the program, rather than 
the implementation details of the LC3. 

## Setup
The program allows creation of pseudo-instructions through the implementation of a PseudoOpCode class. 
```c++
class PseudoOpCode
{
public:
    [[nodiscard]] virtual std::string getName()
    {
        return "UNKNOWN";
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
```
## Internal Operation Details
### PseudoOpCode function calls
- The program will iterate through all PseudoOpCodes, and call canHandle() on each one.
  - Execution will only stop when all PseudoOpCodes fail to handle any tokens in the file
- getInitializationLogic() is called on each PseudoOpCode after all tokens have been handled.
  - The results of each call are concatenated together, and inserted at the beginning of the file.
- getFileEndStatements() is called on each PseudoOpCode after all tokens have been handled.
  - The results of each call are concatenated together, and inserted at the end of the file.
- Initialization logic and file end statements are inserted ordered by priority.
  - PseudoOpCodes with a higher priority are inserted first.
  - This allows PseudoOpCodes to ensure that a required initialization statement is executed before they begin their own initialization logic.

Calling getInitializationLogic() and getFileEndStatements() after all tokens have been handled allows the PseudoOpCodes
to determine what logic needs to be inserted at the beginning and end of the file. Take, for example, the stack.
In order to generate the initialization logic and file end statements, the stack must know what stack names
have been used in the program. This information is only available after all tokens have been handled.

## Usage
The program is run from the command line. The input file is read from stdin, and the output is written to stdout.
Diagnostic information is written to stderr.
Simply pipe the input file into the program, and redirect stdout to the desired output file. 
```shell
cat input.asm | ./lc3_language_extender > output.asm
```

## Examples
### Printing a string
```asm
; Input File
.ORIG x3000
PRINT "Hello, world!"
PRINT "Hello, world!"
PRINT "Testing!"
.END
```

```asm
; Output File
.ORIG x3000
LEA R0, __stack_impl_TEMP_storage
ST R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
STI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
STI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
STI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_1
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
__string_impl_0 .STRINGZ "Hello, world!"
__string_impl_1 .STRINGZ "Testing!"
__stack_impl_TEMP_storage .BLKW 32
__stack_impl_TEMP_stack_ptr .FILL x0
__stack_impl_TEMP_temp_save_location .FILL x0
.END
```
You can see that the resulting file is much larger than the input file. This increase in size is due to the interplay
between the pseudo-instruction 'PRINT' and the stack pseudo-instructions. The PRINT pseudo-instruction is expanded into
a series of stack operations, which are then expanded into a series of LC3 instructions.
Because the stack pseudo-instructions have been expanded, the stack must be initialized. 
Thus, the program must generate logic for initializing the stack, which is then inserted at the beginning of the program.
The program must also allocate space for the stack, which is done by inserting a .BLKW directive at the end of the program.
You'll also notice that the program has only created two strings, even though there are three PRINT statements. This is
because the program is smart enough to recognize that the first two strings are identical, and thus only creates one string
in memory.

Please note that this is not the most efficient string print implementation possible. 
It is written this way to demonstrate interplay between separate pseudo-instructions.
The most efficient string print implementation would not use the stack at all, and would instead store R0
in a temporary location, print the string, and then restore R0 from the temporary location. This is much simpler than the stack
operation logic, but it does not demonstrate the interplay between pseudo-instructions.

### Multiple Stacks
```asm
; Input File
.ORIG x3000
PUSH_STACK1 R0
PUSH_STACK2 R1
POP_STACK1 R2
POP_STACK2 R3
.END
```

```asm
; Output File
.ORIG x3000
LEA R0, __stack_impl_STACK1_storage
ST R0, __stack_impl_STACK1_stack_ptr
LEA R0, __stack_impl_STACK2_storage
ST R0, __stack_impl_STACK2_stack_ptr
ST R1, __stack_impl_STACK1_temp_save_location
LD R1, __stack_impl_STACK1_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_STACK1_stack_ptr
STI R0, __stack_impl_STACK1_stack_ptr
LD R1, __stack_impl_STACK1_temp_save_location
ST R2, __stack_impl_STACK2_temp_save_location
LD R2, __stack_impl_STACK2_stack_ptr
ADD R2, R2, #1
ST R2, __stack_impl_STACK2_stack_ptr
STI R1, __stack_impl_STACK2_stack_ptr
LD R2, __stack_impl_STACK2_temp_save_location
ST R3, __stack_impl_STACK1_temp_save_location
LD R3, __stack_impl_STACK1_stack_ptr
ADD R3, R3, #-1
ST R3, __stack_impl_STACK1_stack_ptr
LDI R2, __stack_impl_STACK1_stack_ptr
LD R3, __stack_impl_STACK1_temp_save_location
ST R4, __stack_impl_STACK2_temp_save_location
LD R4, __stack_impl_STACK2_stack_ptr
ADD R4, R4, #-1
ST R4, __stack_impl_STACK2_stack_ptr
LDI R3, __stack_impl_STACK2_stack_ptr
LD R4, __stack_impl_STACK2_temp_save_location
__stack_impl_STACK1_storage .BLKW 32
__stack_impl_STACK1_stack_ptr .FILL x0
__stack_impl_STACK1_temp_save_location .FILL x0
__stack_impl_STACK2_storage .BLKW 32
__stack_impl_STACK2_stack_ptr .FILL x0
__stack_impl_STACK2_temp_save_location .FILL x0
.END
```
You can see that the program has created two stacks based on the used names, and has correctly pushed and popped values from each stack.

## Future Features
* Support for more pseudo-instructions 
  * Comparison: (LT, GT, LE, GE, etc.)
  * Register label as trap vector (REGISTER_TRAP x0)
* Support for sequential operation optimization
  * Don't restore temp registers if they are immediately overwritten
* Better diagnostics
* Sub-step output
  * Show the output of each step of the translation process
* Detect invalid pseudo-instructions
* Detect invalid pseudo-instruction arguments
* Support multi-line pseudo-instructions (complex branching, etc.)