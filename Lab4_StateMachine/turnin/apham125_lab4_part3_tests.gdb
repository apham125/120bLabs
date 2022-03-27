# Test file for "Lab4_StateMachines"


echo ======================================================\n
echo Running all tests..."\n\n

Test 1: "PINA: 0x00 =>PORTB:0x00, PORTC: 0x01"
setPINA 0x00
continue 5
expectPORTB 0x00
expectPORTC 0x01
checkResult

Test 2: "PINA: 0x04 => PORTB:0x00 PORTC: 0x08 "
setPINA 0x04
continue 5
expectPORTB 0x00
expectPORTC 0x02
checkResult

Test 3: "PINA: 0x00 => PORTB:0x00 PORTC: 0x03 "
setPINA 0x04
continue 5
expectPORTB 0x00
expectPORTC 0x03
checkResult

Test 4: "PINA: 0x02 => PORTB:0x00 PORTC: 0x04 "
setPINA 0x02
continue 5
expectPORTB 0x00
expectPORTC 0x04
checkResult

Test 5: "PINA: 0x00 => PORTB:0x01 PORTC: 0x05 "
setPINA 0x04
continue 5
expectPORTB 0x01
expectPORTC 0x05
checkResult

Test 6: "PINA: 0x80 => PORTB:0x00 PORTC: 0x01 "
setPINA 0x00
continue 5
expectPORTB 0x00
expectPORTC 0x01
checkResult

Test 7: "PINA: 0x02 => PORTB:0x00 PORTC: 0x06 "
setPINA 0x04
continue 5
expectPORTB 0x00
expectPORTC 0x06
checkResult

Test 8: "PINA: 0x80 => PORTB:0x00 PORTC: 0x01 "
setPINA 0x00
continue 5
expectPORTB 0x00
expectPORTC 0x01
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
