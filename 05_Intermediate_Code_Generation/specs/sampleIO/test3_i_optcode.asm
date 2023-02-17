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
main PROC
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
L1:
	MOV AX, 0
	MOV [BP-2], AX
L2:
	MOV AX, 6
	MOV DX, AX
	MOV AX, [BP-2]
	CMP AX, DX
	JL L4
	JMP L5
	POP AX
L3:
	MOV AX, [BP-2]
	PUSH AX
	INC AX
	MOV [BP-2], AX
	POP AX
	JMP L2
L4:
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
	JMP L3
L5:
	MOV AX, 4
	MOV [BP-6], AX
L6:
	MOV AX, 6
	MOV [BP-8], AX
L7:
L8:
	MOV AX, 0
	MOV DX, AX
	MOV AX, [BP-6]
	CMP AX, DX
	JG L9
	JMP L11
L9:
	MOV AX, 3
	MOV DX, AX
	MOV AX, [BP-8]
	ADD AX, DX
	MOV [BP-8], AX
L10:
	MOV AX, [BP-6]
	PUSH AX
	DEC AX
	MOV [BP-6], AX
	POP AX
	JMP L8
L11:
	MOV AX, [BP-8]
	CALL print_output
	CALL new_line
L12:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L13:
	MOV AX, 4
	MOV [BP-6], AX
L14:
	MOV AX, 6
	MOV [BP-8], AX
L15:
L16:
	MOV AX, [BP-6]
	PUSH AX
	DEC AX
	MOV [BP-6], AX
	POP AX
	CMP AX, 0
	JNE L17
	JMP L18
L17:
	MOV AX, 3
	MOV DX, AX
	MOV AX, [BP-8]
	ADD AX, DX
	MOV [BP-8], AX
	JMP L16
L18:
	MOV AX, [BP-8]
	CALL print_output
	CALL new_line
L19:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L20:
	MOV AX, 0
	JMP L21
L21:
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
