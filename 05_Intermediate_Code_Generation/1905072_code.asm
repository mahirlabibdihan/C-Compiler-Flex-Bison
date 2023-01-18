.MODEL SMALL

.STACK 100H


.DATA


.CODE

	foo PROC
		; Function with name foo started
		PUSH BP
		MOV BP, SP	; All the offsets of a function depends on the value of BP

		PUSH [BP + 6]	; a pushed for expression evaluation

		PUSH [BP + 4]	; b pushed for expression evaluation

		; At line no 2: ADD a and b
		POP BX	; b popped from stack
		POP AX	; a popped from stack
		ADD AX, BX
		PUSH AX	; Pushed evaluated value of a+b in the stack

		PUSH 5	; Pushing constant value in stack
		; At line no  2: Checking if a+b<=5
		POP BX	; Popped out 5 from stack
		POP AX	; Popped out a+b from stack
		CMP AX, BX	; Comparing a+b with 5
		JLE L0
		PUSH 0	; Saving expression value to be false
		JMP L1
		L0:
		PUSH 1	; Saving expression value to be true
		L1:


		; At line no 2: Evaluationg if statement
		POP AX	; Popped expression value from stack
		CMP AX, 0	; Checking whether expression is true or false
		JNE L2
		; If expression is false then jump to the end of if block
		JMP L3
		L2:

		PUSH 7	; Pushing constant value in stack
		POP AX	; Popped return value and saved it in AX


		MOV SP, BP	; Restoring SP at the end of function
		POP BP	; Restoring BP at the end of function
		RET 4

		; End label for if statement
		L3:

		PUSH [BP + 6]	; a pushed for expression evaluation

		PUSH 2	; Pushing constant value in stack
		; At line no 5: SUB a and 2
		POP BX	; 2 popped from stack
		POP AX	; a popped from stack
		SUB AX, BX
		PUSH AX	; Pushed evaluated value of a-2 in the stack

		PUSH [BP + 4]	; b pushed for expression evaluation

		PUSH 1	; Pushing constant value in stack
		; At line no 5: SUB b and 1
		POP BX	; 1 popped from stack
		POP AX	; b popped from stack
		SUB AX, BX
		PUSH AX	; Pushed evaluated value of b-1 in the stack

		CALL foo	; Function with name foo called
		PUSH AX	; Return value of function named foo pushed in stack

		PUSH 2	; Pushing constant value in stack
		PUSH [BP + 6]	; a pushed for expression evaluation

		PUSH 1	; Pushing constant value in stack
		; At line no 5: SUB a and 1
		POP BX	; 1 popped from stack
		POP AX	; a popped from stack
		SUB AX, BX
		PUSH AX	; Pushed evaluated value of a-1 in the stack

		PUSH [BP + 4]	; b pushed for expression evaluation

		PUSH 2	; Pushing constant value in stack
		; At line no 5: SUB b and 2
		POP BX	; 2 popped from stack
		POP AX	; b popped from stack
		SUB AX, BX
		PUSH AX	; Pushed evaluated value of b-2 in the stack

		CALL foo	; Function with name foo called
		PUSH AX	; Return value of function named foo pushed in stack

		; MULTIPLICATION operation between 2 and foo(a-1,b-2)
		POP BX	; foo(a-1,b-2) popped from stack
		POP AX	; 2 popped from stack
		IMUL BX	; Multiplying 2 and foo(a-1,b-2)
		PUSH AX	; Saving result of 2*foo(a-1,b-2) in stack

		; At line no 5: ADD foo(a-2,b-1) and 2*foo(a-1,b-2)
		POP BX	; 2*foo(a-1,b-2) popped from stack
		POP AX	; foo(a-2,b-1) popped from stack
		ADD AX, BX
		PUSH AX	; Pushed evaluated value of foo(a-2,b-1)+2*foo(a-1,b-2) in the stack

		POP AX	; Popped return value and saved it in AX


		MOV SP, BP	; Restoring SP at the end of function
		POP BP	; Restoring BP at the end of function
		RET 4

	foo ENDP

	main PROC
		; Function with name main started

		; DATA SEGMENT INITIALIZATION
		MOV AX, @DATA
		MOV DS, AX
		MOV BP, SP
		PUSH BX 	; In line no 10: i declared
		PUSH BX 	; In line no 10: j declared
		PUSH BX 	; In line no 10: k declared
		PUSH [BP + -2]	; i pushed for expression evaluation

		PUSH 7	; Pushing constant value in stack
		; At line no 11: Assigning 7 into i
		POP AX	;7 popped from stack
		MOV [BP + -2], AX	; Value of 7 assigned into i

		POP AX	; Popped out i=7

		PUSH [BP + -4]	; j pushed for expression evaluation

		PUSH 3	; Pushing constant value in stack
		; At line no 12: Assigning 3 into j
		POP AX	;3 popped from stack
		MOV [BP + -4], AX	; Value of 3 assigned into j

		POP AX	; Popped out j=3

		PUSH [BP + -6]	; k pushed for expression evaluation

		PUSH [BP + -2]	; i pushed for expression evaluation

		PUSH [BP + -4]	; j pushed for expression evaluation

		CALL foo	; Function with name foo called
		PUSH AX	; Return value of function named foo pushed in stack

		; At line no 14: Assigning foo(i,j) into k
		POP AX	;foo(i,j) popped from stack
		MOV [BP + -6], AX	; Value of foo(i,j) assigned into k

		POP AX	; Popped out k=foo(i,j)


		PUSH [BP + -6]	; Passing k to PRINT_NUM for printing it
		CALL PRINT_NUM

		PUSH 0	; Pushing constant value in stack
		POP AX	; Popped return value and saved it in AX


		MOV SP, BP	; Restoring SP at the end of function
		POP BP	; Restoring BP at the end of function

		; Setting interrupt for function end
		MOV AH, 4CH
		INT 21H
	main ENDP

	;printf(n)
	PRINT_NUM PROC NEAR
        PUSH BP             ;Saving BP
        MOV BP, SP          ;BP points to the top of the stack
        MOV BX, [BP + 4]    ;The number to be printed
        ;if(BX < -1) then the number is positive
        CMP BX, 0
        JGE POSITIVE
        ;else, the number is negative
        MOV AH, 2           
        MOV DL, '-'         ;Print a '-' sign
        INT 21H
        NEG BX              ;make BX positive
        POSITIVE:
        MOV AX, BX
        MOV CX, 0        ;Initialize character count
        PUSH_WHILE:
            XOR DX, DX  ;clear DX
            MOV BX, 10  ;BX has the divisor //// AX has the dividend
            DIV BX
            ;quotient is in AX and remainder is in DX
            PUSH DX     ;Division by 10 will have a remainder less than 8 bits
            INC CX       ;CX++
            ;if(AX == 0) then break the loop
            CMP AX, 0
            JE END_PUSH_WHILE
            ;else continue
            JMP PUSH_WHILE
        END_PUSH_WHILE:
        MOV AH, 2
        POP_WHILE:
            POP DX      ;Division by 10 will have a remaainder less than 8 bits
            ADD DL, '0'
            INT 21H     ;So DL will have the desired character
            DEC CX       ;CX--
            ;if(CX <= 0) then end loop
            CMP CX, 0
            JLE END_POP_WHILE
            ;else continue
            JMP POP_WHILE
        END_POP_WHILE:
        ;Print 
        MOV DL, 0DH
        INT 21H
        MOV DL, 0AH
        INT 21H
        POP BP          ; Restore BP
        RET 2
    PRINT_NUM ENDP
END MAIN

