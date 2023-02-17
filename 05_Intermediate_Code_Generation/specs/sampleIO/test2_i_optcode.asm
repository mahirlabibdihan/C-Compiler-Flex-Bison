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
L1:
	MOV AX, 3
	MOV [BP-2], AX
L2:
	MOV AX, 8
	MOV [BP-4], AX
L3:
	MOV AX, 6
	MOV [BP-6], AX
L4:
	MOV AX, 3
	MOV DX, AX
	MOV AX, [BP-2]
	CMP AX, DX
	JE L5
	JMP L6
L5:
	MOV AX, [BP-4]
	CALL print_output
	CALL new_line
L6:
	MOV AX, 8
	MOV DX, AX
	MOV AX, [BP-4]
	CMP AX, DX
	JL L7
	JMP L8
L7:
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
	JMP L9
L8:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L9:
	MOV AX, 6
	MOV DX, AX
	MOV AX, [BP-6]
	CMP AX, DX
	JNE L10
	JMP L11
L10:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
	JMP L17
L11:
	MOV AX, 8
	MOV DX, AX
	MOV AX, [BP-4]
	CMP AX, DX
	JG L12
	JMP L13
L12:
	MOV AX, [BP-4]
	CALL print_output
	CALL new_line
	JMP L17
L13:
	MOV AX, 5
	MOV DX, AX
	MOV AX, [BP-2]
	CMP AX, DX
	JL L14
	JMP L15
L14:
	MOV AX, [BP-2]
	CALL print_output
	CALL new_line
	JMP L17
L15:
	MOV AX, 0
	MOV [BP-6], AX
L16:
	MOV AX, [BP-6]
	CALL print_output
	CALL new_line
L17:
	MOV AX, 0
	JMP L18
L18:
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
