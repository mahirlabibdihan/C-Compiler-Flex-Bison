;-------
;
;-------
.MODEL SMALL
.STACK 1000H
.Data
	CR EQU 0DH
	LF EQU 0AH
	number DB "00000$"
.CODE
foo PROC
	PUSH BP
	MOV BP, SP
	MOV AX, [BP+4]
	MOV DX, AX
	MOV AX, [BP+6]
	ADD AX, DX
	PUSH AX
	MOV AX, 5
	MOV DX, AX
	POP AX
	CMP AX, DX
	JLE L1
	JMP L2
L1:
	MOV AX, 7
	JMP L3
L2:
	MOV AX, 2
	MOV DX, AX
	MOV AX, [BP+6]
	SUB AX, DX
	PUSH AX
	MOV AX, 1
	MOV DX, AX
	MOV AX, [BP+4]
	SUB AX, DX
	PUSH AX
	CALL foo
	PUSH AX
	MOV AX, 1
	MOV DX, AX
	MOV AX, [BP+6]
	SUB AX, DX
	PUSH AX
	MOV AX, 2
	MOV DX, AX
	MOV AX, [BP+4]
	SUB AX, DX
	PUSH AX
	CALL foo
	MOV CX, AX
	MOV AX, 2
	CWD
	MUL CX
	MOV DX, AX
	POP AX
	ADD AX, DX
	JMP L3
L3:
	POP BP
	RET 4
foo ENDP
main PROC
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
L4:
	MOV AX, 7
	MOV [BP-2], AX
L5:
	MOV AX, 3
	MOV [BP-4], AX
L6:
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, [BP-4]
	PUSH AX
	CALL foo
	MOV [BP-6], AX
L7:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L8:
	MOV AX, 0
	JMP L9
L9:
	ADD SP, 6
	POP BP
	MOV AX,4CH
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
END main
