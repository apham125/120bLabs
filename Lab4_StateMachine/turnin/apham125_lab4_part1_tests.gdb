# Test file for "Lab4_StateMachines"


echo ======================================================\n
echo Running all tests..."\n\n

Test 1: "PINA: 0x00 =>PORTB:0x01"
setPINA 0x00
continue 5
expectPORTB 0x01
checkResult

Test 2: "PINA: 0x01 => PORTB: 0x02 "
setPINA 0x01
continue 5
expectPORTB 0x02
checkResult

Test 3: "PINA: 0x00 => PORTB: 0x02 "
setPINA 0x00
continue 5
expectPORTB 0x02
checkResult

Test 4: "PINA: 0x01 => PORTB: 0x01 "
setPINA 0x01
continue 5
expectPORTB 0x01
checkResult

Test 5: "PINA: 0x00 => PORTB: 0x01 "
setPINA 0x00
continue 5
expectPORTB 0x01
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
