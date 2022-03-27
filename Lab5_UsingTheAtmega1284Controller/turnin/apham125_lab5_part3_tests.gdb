# Test file for "lab_chip"


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

test "PINA: 0x01 => PORTB: 0x00, state = init"
set state = start
setPINA 0x01
continue 5
expectPORTB 0
expect state init
checkResult

test "PINA: 0x01, 0x00 => PORTB: 0x00, state = light"
set state = start
setPINA 0x01
continue 5
setPINA 0x00
continue 5
expectPORTB 0x01
expect state light
checkResult

test "PINA: 0x01, 0x00, 0x01 => PORTB: 0x01, state = init"
set state = start
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x01
expect state init
checkResult

test "11 button presses"
set state = start
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2

expectPORTB 0x2A
expect state init
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n