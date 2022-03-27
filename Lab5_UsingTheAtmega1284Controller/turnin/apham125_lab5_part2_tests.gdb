# Test file for "Lab5"


echo ======================================================\n
echo Running all tests..."\n\n

Test 1: "PINA: 0x00 =>PORTC:0x07"
setPINA 0x00
continue 5
expectPORTC 0x07
checkResult

Test 2: "PINA: 0x01 => PORTC: 0x08 "
setPINA 0x01
continue 5
expectPORTC 0x8
checkResult

Test 3: "PINA: 0x02 => PORTC: 0x07 "
setPINA 0x02
continue 5
expectPORTB 0x07
checkResult

Test 4: "PINA: 0x00 => PORTB: 0x00 "
setPINA 0x00
continue 5
expectPORTB 0x00
checkResult



# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
