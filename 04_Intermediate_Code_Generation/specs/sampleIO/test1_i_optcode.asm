;-------
;
;-------
.MODEL SMALL
.STACK 1000H
.Data
	CR EQU 0DH
	LF EQU 0AH
	number DB "00000$"
	i DW 1 DUP (0000H)
	j DW 1 DUP (0000H)
.CODE
main PROC
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
L1:
	MOV AX, 1
	MOV i, AX
L2:
	MOV AX, i
	CALL print_output
	CALL new_line
L3:
	MOV AX, 8
	MOV DX, AX
	MOV AX, 5
	ADD AX, DX
	MOV j, AX
L4:
	MOV AX, j
	CALL print_output
	CALL new_line
L5:
	MOV AX, j
	MOV CX, AX
	MOV AX, 2
	CWD
	MUL CX
	MOV DX, AX
	MOV AX, i
	ADD AX, DX
	MOV [BP-2], AX
L6:
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
L7:
	MOV AX, 9
	MOV CX, AX
	MOV AX, [BP-2]
	CWD
	DIV CX
	PUSH DX
	POP AX
	MOV [BP-6], AX
L8:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L9:
	MOV AX, [BP-4]
	MOV DX, AX
	MOV AX, [BP-6]
	CMP AX, DX
	JLE L10
	JMP L12
L10:
	MOV AX, 1
	JMP L11
L12:
	MOV AX, 0
L11:
	MOV [BP-8], AX
L13:
	MOV AX, [BP-8]
	CALL print_output
	CALL new_line
L14:
	MOV AX, j
	MOV DX, AX
	MOV AX, i
	CMP AX, DX
	JNE L15
	JMP L17
L15:
	MOV AX, 1
	JMP L16
L17:
	MOV AX, 0
L16:
	MOV [BP-10], AX
L18:
	MOV AX, [BP-10]
	CALL print_output
	CALL new_line
L19:
	MOV AX, [BP-8]
	CMP AX, 0
	JNE L21
	JMP L20
L20:
	MOV AX, [BP-10]
	CMP AX, 0
	JNE L21
	JMP L23
L21:
	MOV AX, 1
	JMP L22
L23:
	MOV AX, 0
L22:
	MOV [BP-12], AX
L24:
	MOV AX, [BP-12]
	CALL print_output
	CALL new_line
L25:
	MOV AX, [BP-8]
	CMP AX, 0
	JNE L26
	JMP L29
L26:
	MOV AX, [BP-10]
	CMP AX, 0
	JNE L27
	JMP L29
L27:
	MOV AX, 1
	JMP L28
L29:
	MOV AX, 0
L28:
	MOV [BP-12], AX
L30:
	MOV AX, [BP-12]
	CALL print_output
	CALL new_line
L31:
	MOV AX, [BP-12]
	PUSH AX
	INC AX
	MOV [BP-12], AX
	POP AX
L32:
	MOV AX, [BP-12]
	CALL print_output
	CALL new_line
L33:
	MOV AX, [BP-12]
	NEG AX
	MOV [BP-2], AX
L34:
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
L35:
	MOV AX, 0
	JMP L36
L36:
	ADD SP, 12
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
