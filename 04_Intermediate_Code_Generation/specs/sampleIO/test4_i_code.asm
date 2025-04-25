;-------
;
;-------
.MODEL SMALL
.STACK 1000H
.Data
	CR EQU 0DH
	LF EQU 0AH
	number DB "00000$"
	a DW 1 DUP (0000H)
	b DW 1 DUP (0000H)
	c DW 1 DUP (0000H)
.CODE
func_a PROC
	PUSH BP
	MOV BP, SP
	MOV AX, 7
	MOV a, AX
	PUSH AX
	POP AX
L1:
	POP BP
	RET 
func_a ENDP
foo PROC
	PUSH BP
	MOV BP, SP
	
	MOV AX, 3
	MOV DX, AX
	MOV AX, [BP+4]
	ADD AX, DX
	PUSH AX
	POP AX
	MOV [BP+4], AX
	PUSH AX
	POP AX
L2:
	MOV AX, [BP+4]
	JMP L3
L3:
	POP BP
	RET 2
foo ENDP
bar PROC
	PUSH BP
	MOV BP, SP
	MOV AX, [BP+6]
	MOV CX, AX
	MOV AX, 4
	CWD
	MUL CX
	PUSH AX
	MOV AX, [BP+4]
	MOV CX, AX
	MOV AX, 2
	CWD
	MUL CX
	PUSH AX
	POP AX
	MOV DX, AX
	POP AX
	ADD AX, DX
	PUSH AX
	POP AX
	MOV c, AX
	PUSH AX
	POP AX
L4:
	MOV AX, c
	JMP L5
L5:
	POP BP
	RET 4
bar ENDP
main PROC
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
L6:
	MOV AX, 5
	MOV [BP-2], AX
	PUSH AX
	POP AX
L7:
	MOV AX, 6
	MOV [BP-4], AX
	PUSH AX
	POP AX
L8:
	CALL func_a
	PUSH AX
	POP AX
L9:
	MOV AX, a
	CALL print_output
	CALL new_line
L10:
	MOV AX, [BP-2]
	PUSH AX
	CALL foo
	PUSH AX
	POP AX
	MOV [BP-6], AX
	PUSH AX
	POP AX
L11:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L12:
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, [BP-4]
	PUSH AX
	CALL bar
	PUSH AX

	POP AX
	MOV [BP-8], AX
	PUSH AX
	POP AX
L13:
	MOV AX, [BP-8]
	CALL print_output
	CALL new_line
L14:
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, [BP-4]
	PUSH AX
	CALL bar
	PUSH AX

	POP AX
	MOV CX, AX
	MOV AX, 6
	CWD
	MUL CX
	PUSH AX

	MOV AX, 2
	MOV DX, AX
	POP AX
	ADD AX, DX
	PUSH AX

	MOV AX, [BP-2]
	PUSH AX
	CALL foo
	PUSH AX

	POP AX
	MOV CX, AX
	MOV AX, 3
	CWD
	MUL CX
	PUSH AX
	
	POP AX
	MOV DX, AX
	POP AX
	SUB AX, DX
	PUSH AX
	POP AX
	MOV [BP-4], AX
	PUSH AX
	POP AX
L15:
	MOV AX, [BP-4]
	CALL print_output
	CALL new_line
L16:
	MOV AX, 0
	JMP L17
L17:
	ADD SP, 8
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