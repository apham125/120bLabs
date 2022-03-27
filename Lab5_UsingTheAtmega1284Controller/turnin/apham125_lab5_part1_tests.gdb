# Test file for "Lab5"


echo ======================================================\n
echo Running all tests..."\n\n

Test 1: "PINA: 0x00 => PORTC: 0x40"
setPINA 0x00
continue 5
expectPORTC 0x40
checkResult

Test 2: "PINA: 0x07 => PORTC: 0x3C"
setPINA 0x07
continue 5
expectPORTC 0x3C
checkResult

Test 3: "PINA: 0x0C => PORTC: 0x3E"
setPINA 0x0C
continue 5
expectPORTC 0x3E
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n