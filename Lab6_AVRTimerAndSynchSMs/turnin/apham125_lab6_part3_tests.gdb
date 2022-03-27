# Test file for "Lab6"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

define timeContinue
    if $argc > 0
        set $i = $arg0
    else
        set $i =1
    end
    while $i > 0
        set TimerFlag = 1
        continue
        set $i = $i - 1
    end
end

test "Init"
timeContinue
expect PORTB 0x07
checkResult

test "Increment 2"
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
expect PORTB 0x09
expect state init
checkResult

test "Decrement 2"
setPINA ~0x02
timeContinue
setPINA ~0x00
timeContinue
expectPORTB 0x08
setPINA ~0x02
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x02
timeContinue
setPINA ~0x00
timeContinue
expect PORTB 0x06
checkResult

test "Reset"
setPINA ~0x03
timeContinue
expect PORTB 0x00
checkResult

test"Dec at 0"
setPINA ~0x02
timeContinue
setPINA ~0x00
timeContinue
expect PORTB 0x00
checkResult

test"inc at 9"
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
setPINA ~0x01
timeContinue
setPINA ~0x00
timeContinue
expect PORTB 0x09
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
