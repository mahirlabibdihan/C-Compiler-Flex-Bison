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
f PROC
	PUSH BP
	MOV BP, SP
	SUB SP, 2
L1:
	MOV AX, 5
	MOV [BP-2], AX
L2:
L3:
	MOV AX, 0
	MOV DX, AX
	MOV AX, [BP-2]
	CMP AX, DX
	JG L4
	JMP L6
L4:
	MOV AX, [BP+4]
	PUSH AX
	INC AX
	MOV [BP+4], AX
	POP AX
L5:
	MOV AX, [BP-2]
	PUSH AX
	DEC AX
	MOV [BP-2], AX
	POP AX
	JMP L3
L6:
	MOV AX, [BP+4]
	MOV CX, AX
	MOV AX, 3
	CWD
	MUL CX
	PUSH AX
	MOV AX, 7
	MOV DX, AX
	POP AX
	SUB AX, DX
	JMP L8
L7:
	MOV AX, 9
	MOV [BP+4], AX
L8:
	ADD SP, 2
	POP BP
	RET 2
f ENDP
g PROC
	PUSH BP
	MOV BP, SP
	SUB SP, 2
	SUB SP, 2
L9:
	MOV AX, [BP+6]
	PUSH AX
	CALL f
	PUSH AX
	MOV AX, [BP+6]
	MOV DX, AX
	POP AX
	ADD AX, DX
	PUSH AX
	MOV AX, [BP+4]
	MOV DX, AX
	POP AX
	ADD AX, DX
	MOV [BP-2], AX
L10:
	MOV AX, 0
	MOV [BP-4], AX
L11:
	MOV AX, 7
	MOV DX, AX
	MOV AX, [BP-4]
	CMP AX, DX
	JL L13
	JMP L16
	POP AX
L12:
	MOV AX, [BP-4]
	PUSH AX
	INC AX
	MOV [BP-4], AX
	POP AX
	JMP L11
L13:
	MOV AX, 3
	MOV CX, AX
	MOV AX, [BP-4]
	CWD
	DIV CX
	PUSH DX
	MOV AX, 0
	MOV DX, AX
	POP AX
	CMP AX, DX
	JE L14
	JMP L15
L14:
	MOV AX, 5
	MOV DX, AX
	MOV AX, [BP-2]
	ADD AX, DX
	MOV [BP-2], AX
	JMP L12
L15:
	MOV AX, 1
	MOV DX, AX
	MOV AX, [BP-2]
	SUB AX, DX
	MOV [BP-2], AX
	JMP L12
L16:
	MOV AX, [BP-2]
	JMP L17
L17:
	ADD SP, 4
	POP BP
	RET 4
g ENDP
main PROC
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
L18:
	MOV AX, 1
	MOV [BP-2], AX
L19:
	MOV AX, 2
	MOV [BP-4], AX
L20:
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, [BP-4]
	PUSH AX
	CALL g
	MOV [BP-2], AX
L21:
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
L22:
	MOV AX, 0
	MOV [BP-6], AX
L23:
	MOV AX, 4
	MOV DX, AX
	MOV AX, [BP-6]
	CMP AX, DX
	JL L25
	JMP L30
	POP AX
L24:
	MOV AX, [BP-6]
	PUSH AX
	INC AX
	MOV [BP-6], AX
	POP AX
	JMP L23
L25:
	MOV AX, 3
	MOV [BP-2], AX
L26:
L27:
	MOV AX, 0
	MOV DX, AX
	MOV AX, [BP-2]
	CMP AX, DX
	JG L28
	JMP L24
L28:
	MOV AX, [BP-4]
	PUSH AX
	INC AX
	MOV [BP-4], AX
	POP AX
L29:
	MOV AX, [BP-2]
	PUSH AX
	DEC AX
	MOV [BP-2], AX
	POP AX
	JMP L27
	JMP L24
L30:
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
L31:
	MOV AX, [BP-4]
	CALL print_output
	CALL new_line
L32:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L33:
	MOV AX, 0
	JMP L34
L34:
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
