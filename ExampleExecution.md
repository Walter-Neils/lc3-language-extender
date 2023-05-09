```asm
; Input File
.ORIG x3000
PRINT "Hello, world!"
PRINT "Hello, world!"
PRINT "Testing!"
.END
; Processing iteration 0
.ORIG x3000
PUSH_TEMP R0
LEA R0, __string_impl_0
TRAP x22
POP_TEMP R0
PRINT "Hello, world!"
PRINT "Testing!"
.END
; End processing iteration 0
; Processing iteration 1
.ORIG x3000
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
POP_TEMP R0
PUSH_TEMP R0
LEA R0, __string_impl_0
TRAP x22
POP_TEMP R0
PRINT "Testing!"
.END
; End processing iteration 1
; Processing iteration 2
.ORIG x3000
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
PUSH_TEMP R0
LEA R0, __string_impl_0
TRAP x22
POP_TEMP R0
PUSH_TEMP R0
LEA R0, __string_impl_1
TRAP x22
POP_TEMP R0
.END
; End processing iteration 2
; Processing iteration 3
.ORIG x3000
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
POP_TEMP R0
PUSH_TEMP R0
LEA R0, __string_impl_1
TRAP x22
POP_TEMP R0
.END
; End processing iteration 3
; Processing iteration 4
.ORIG x3000
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
PUSH_TEMP R0
LEA R0, __string_impl_1
TRAP x22
POP_TEMP R0
.END
; End processing iteration 4
; Processing iteration 5
.ORIG x3000
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_1
TRAP x22
POP_TEMP R0
.END
; End processing iteration 5
; Processing iteration 6
.ORIG x3000
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_1
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
.END
; End processing iteration 6
.ORIG x3000
LEA R0, __stack_impl_TEMP_storage
ST R0, __stack_impl_TEMP_stack_ptr
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
LEA R0, __string_impl_0
TRAP x22
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #-1
ST R1, __stack_impl_TEMP_stack_ptr
LDI R0, __stack_impl_TEMP_stack_ptr
LD R1, __stack_impl_TEMP_temp_save_location
STI R0, __stack_impl_TEMP_stack_ptr
ST R1, __stack_impl_TEMP_temp_save_location
LD R1, __stack_impl_TEMP_stack_ptr
ADD R1, R1, #1
ST R1, __stack_impl_TEMP_stack_ptr
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