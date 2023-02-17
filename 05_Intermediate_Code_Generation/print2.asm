; Will sent parameter in stack    
OUTPUT PROC
    ; Saving all registers
    PUSH BP
    MOV BP, SP
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    
    ; Reseting
    XOR AX, AX
    XOR BX, BX
    XOR CX, CX
    XOR DX, DX
    
    MOV BX, [BP+4]
    CMP BX, 0 
    JGE POS_OUT ; Check sign bit
    
    NEG_OUT:
        NEG BX 
        
        MOV AH, 2
        MOV DL, '-'
        INT 21H
    POS_OUT: 
        MOV AX, BX
        XOR CX, CX
        STACK_LOOP:
            ; DX = AX % 10       
            ; AX = AX / 10
            XOR DX, DX
            MOV BX, 10
            DIV BX
            
            PUSH DX
            INC CX
            CMP AX, 0
            JNE STACK_LOOP
        END_STACK_LOOP:
        
        PRINT_LOOP:
            POP DX
            ADD DL, '0'
            
            MOV AH, 2
            INT 21H
            
            DEC CX
            CMP CX, 0
            JNE PRINT_LOOP    
        END_PRINT_LOOP:
    
    MOV DL, 0DH
    INT 21H
    MOV DL, 0AH
    INT 21H
    ; Restoring all registers         
    POP DX
    POP CX
    POP BX
    POP AX
    POP BP
    RET 2
OUTPUT ENDP