.MODEL SMALL
.STACK 1000H
.DATA
	CR EQU 0DH
	LF EQU 0AH
	number DB "00000$"
.CODE
main PROC
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	; Line no: 4 => int i,j,k,ll;
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
L2:
	; Line no: 6 => For Loop
	; i=0
	MOV AX, 0
	MOV [BP-2], AX
	PUSH AX
L4:
	; i<6
	MOV DX, 6
	MOV AX, [BP-2]
	CMP AX, DX
	JL L5
	JMP L3
L5:
	; Line no: 8 => int k;
	SUB SP, 2
L7:
	; Line no: 9 => println(i);
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
	; Deallocating Variables
	ADD SP, 2
L6:
	; i++
	PUSH [BP-2]
	INC WORD PTR [BP-2]
	JMP L4
L3:
	; Line no: 12 => k=4;
	MOV AX, 4
	MOV [BP-6], AX
	PUSH AX
	POP AX
L8:
	; Line no: 13 => ll=6;
	MOV AX, 6
	MOV [BP-8], AX
	PUSH AX
	POP AX
L9:
	; Line no: 14 => While Loop
L11:
	; k>0
	MOV DX, 0
	MOV AX, [BP-6]
	CMP AX, DX
	JG L12
	JMP L10
L12:
	; Line no: 16 => ll=ll+3;
	MOV DX, 3
	MOV AX, [BP-8]
	ADD AX, DX
	PUSH AX
	POP AX
	MOV [BP-8], AX
	PUSH AX
	POP AX
L13:
	; Line no: 17 => k--;
	PUSH [BP-6]
	DEC WORD PTR [BP-6]
	POP AX
	JMP L11
L10:
	; Line no: 20 => println(ll);
	MOV AX, [BP-8]
	CALL print_output
	CALL new_line
L14:
	; Line no: 21 => println(k);
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L15:
	; Line no: 23 => k=4;
	MOV AX, 4
	MOV [BP-6], AX
	PUSH AX
	POP AX
L16:
	; Line no: 24 => ll=6;
	MOV AX, 6
	MOV [BP-8], AX
	PUSH AX
	POP AX
L17:
	; Line no: 26 => While Loop
L19:
	; k--!=0
	PUSH [BP-6]
	DEC WORD PTR [BP-6]
	MOV DX, 0
	POP AX
	CMP AX, DX
	JNE L20
	JMP L18
L20:
	; Line no: 28 => ll=ll+3;
	MOV DX, 3
	MOV AX, [BP-8]
	ADD AX, DX
	PUSH AX
	POP AX
	MOV [BP-8], AX
	PUSH AX
	POP AX
	JMP L19
L18:
	; Line no: 31 => println(ll);
	MOV AX, [BP-8]
	CALL print_output
	CALL new_line
L21:
	; Line no: 32 => println(k);
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L22:
	; Line no: 34 => return 0;
	JMP L1
	; Deallocating Variables
	ADD SP, 8
L1:
	MOV SP, BP
	POP BP
	MOV AH, 4CH
	INT 21H
main ENDP
new_line proc
    push ax
    push dx
    mov ah,2
    mov dl,cr
    int 21h
    mov ah,2
    mov dl,lf
    int 21h
    pop dx
    pop ax
    ret
new_line endp
print_output proc  ;print what is in ax
    push ax
    push bx
    push cx
    push dx
    push si
    lea si,number
    mov bx,10
    add si,4
    cmp ax,0
    jnge negate
    print:
    xor dx,dx
    div bx
    mov [si],dl
    add [si],'0'
    dec si
    cmp ax,0
    jne print
    inc si
    lea dx,si
    mov ah,9
    int 21h
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
    negate:
    push ax
    mov ah,2
    mov dl,'-'
    int 21h
    pop ax
    neg ax
    jmp print
print_output endp
END MAIN
