		.MODEL SMALL
		.STACK 100H
		.DATA
		.CODE
		f PROC
		PUSH BP
		MOV BP, SP
		POP BP
		POP BX
		PUSH 10
		PUSH BX
		RET
		f ENDP
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
