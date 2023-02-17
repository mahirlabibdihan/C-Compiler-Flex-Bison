.MODEL SMALL
.STACK 1000H
.DATA
	CR EQU 0DH
	LF EQU 0AH
	number DB "00000$"
	; Line no: 5 => int cnt;
	cnt0 DW (0000H)
.CODE
show1 PROC
	PUSH BP
	MOV BP, SP
	; Line no: 3 => println(n);
	MOV AX, [BP+4]
	CALL print_output
	CALL new_line
L1:
	MOV SP, BP
	POP BP
	RET 2
show1 ENDP
check2 PROC
	PUSH BP
	MOV BP, SP
	; Line no: 8 => cnt++;
	PUSH cnt0
	INC cnt0
	POP AX
L3:
	; Line no: 9 => return cnt;
	MOV AX, cnt0
	MOV [BP+4], AX
	JMP L2
L2:
	MOV SP, BP
	POP BP
	RET 0
check2 ENDP
factorial3 PROC
	PUSH BP
	MOV BP, SP
	; Line no: 14 => If-Else Statement
	; n==0
	MOV DX, 0
	MOV AX, [BP+4]
	CMP AX, DX
	JE L5
	JMP L6
L5:
	; Line no: 16 => return 1;
	MOV AX, 1
	MOV [BP+6], AX
	JMP L4
	JMP L4
L6:
	; Line no: 20 => return n*factorial(n-1);
	SUB SP, 2
	; factorial(n-1)
	MOV DX, 1
	MOV AX, [BP+4]
	SUB AX, DX
	PUSH AX
	CALL factorial3
	POP CX
	MOV AX, [BP+4]
	CWD
	IMUL CX
	PUSH AX
	POP AX
	MOV [BP+6], AX
	JMP L4
L4:
	MOV SP, BP
	POP BP
	RET 2
factorial3 ENDP
grade4 PROC
	PUSH BP
	MOV BP, SP
	; Line no: 26 => If-Else Statement
	; n<0||n>100
	MOV DX, 0
	MOV AX, [BP+4]
	CMP AX, DX
	JL L10
	PUSH 0
	JMP L11
L10:
	PUSH 1
L11:
	POP AX
	CMP AX, 0
	JNE L8
	MOV DX, 100
	MOV AX, [BP+4]
	CMP AX, DX
	JG L12
	PUSH 0
	JMP L13
L12:
	PUSH 1
L13:
	POP AX
	CMP AX, 0
	JNE L8
	JMP L9
L8:
	; Line no: 28 => show(-1);
	; show(-1)
	MOV AX, 1
	NEG AX
	PUSH AX
	CALL show1
	JMP L7
L9:
	; Line no: 30 => If-Else Statement
	; n>=80
	MOV DX, 80
	MOV AX, [BP+4]
	CMP AX, DX
	JGE L14
	JMP L15
L14:
	; Line no: 32 => show(80);
	; show(80)
	MOV AX, 80
	PUSH AX
	CALL show1
	JMP L7
L15:
	; Line no: 34 => If-Else Statement
	; n>=70&&n<80
	MOV DX, 70
	MOV AX, [BP+4]
	CMP AX, DX
	JGE L18
	PUSH 0
	JMP L19
L18:
	PUSH 1
L19:
	POP AX
	CMP AX, 0
	JE L17
	MOV DX, 80
	MOV AX, [BP+4]
	CMP AX, DX
	JL L20
	PUSH 0
	JMP L21
L20:
	PUSH 1
L21:
	POP AX
	CMP AX, 0
	JNE L16
	JMP L17
L16:
	; Line no: 36 => show(70);
	; show(70)
	MOV AX, 70
	PUSH AX
	CALL show1
	JMP L7
L17:
	; Line no: 38 => If-Else Statement
	; n>=60&&n<70
	MOV DX, 60
	MOV AX, [BP+4]
	CMP AX, DX
	JGE L24
	PUSH 0
	JMP L25
L24:
	PUSH 1
L25:
	POP AX
	CMP AX, 0
	JE L23
	MOV DX, 70
	MOV AX, [BP+4]
	CMP AX, DX
	JL L26
	PUSH 0
	JMP L27
L26:
	PUSH 1
L27:
	POP AX
	CMP AX, 0
	JNE L22
	JMP L23
L22:
	; Line no: 40 => show(60);
	; show(60)
	MOV AX, 60
	PUSH AX
	CALL show1
	JMP L7
L23:
	; Line no: 42 => If-Else Statement
	; n>=50&&n<60
	MOV DX, 50
	MOV AX, [BP+4]
	CMP AX, DX
	JGE L30
	PUSH 0
	JMP L31
L30:
	PUSH 1
L31:
	POP AX
	CMP AX, 0
	JE L29
	MOV DX, 60
	MOV AX, [BP+4]
	CMP AX, DX
	JL L32
	PUSH 0
	JMP L33
L32:
	PUSH 1
L33:
	POP AX
	CMP AX, 0
	JNE L28
	JMP L29
L28:
	; Line no: 44 => show(50);
	; show(50)
	MOV AX, 50
	PUSH AX
	CALL show1
	JMP L7
L29:
	; Line no: 46 => If Statement
	; n<50
	MOV DX, 50
	MOV AX, [BP+4]
	CMP AX, DX
	JL L34
	JMP L7
L34:
	; Line no: 48 => show(-100);
	; show(-100)
	MOV AX, 100
	NEG AX
	PUSH AX
	CALL show1
L7:
	MOV SP, BP
	POP BP
	RET 2
grade4 ENDP
main PROC
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	; Line no: 53 => grade(85);
	; grade(85)
	MOV AX, 85
	PUSH AX
	CALL grade4
L36:
	; Line no: 54 => grade(75);
	; grade(75)
	MOV AX, 75
	PUSH AX
	CALL grade4
L37:
	; Line no: 55 => grade(80);
	; grade(80)
	MOV AX, 80
	PUSH AX
	CALL grade4
L38:
	; Line no: 56 => grade(69);
	; grade(69)
	MOV AX, 69
	PUSH AX
	CALL grade4
L39:
	; Line no: 57 => grade(32);
	; grade(32)
	MOV AX, 32
	PUSH AX
	CALL grade4
L40:
	; Line no: 58 => grade(49);
	; grade(49)
	MOV AX, 49
	PUSH AX
	CALL grade4
L41:
	; Line no: 59 => grade(50);
	; grade(50)
	MOV AX, 50
	PUSH AX
	CALL grade4
L42:
	; Line no: 60 => grade(71);
	; grade(71)
	MOV AX, 71
	PUSH AX
	CALL grade4
L43:
	; Line no: 61 => grade(51);
	; grade(51)
	MOV AX, 51
	PUSH AX
	CALL grade4
L44:
	; Line no: 62 => grade(-95);
	; grade(-95)
	MOV AX, 95
	NEG AX
	PUSH AX
	CALL grade4
L45:
	; Line no: 63 => grade(200);
	; grade(200)
	MOV AX, 200
	PUSH AX
	CALL grade4
L46:
	; Line no: 64 => show(factorial(5));
	; show(factorial(5))
	SUB SP, 2
	; factorial(5)
	MOV AX, 5
	PUSH AX
	CALL factorial3
	CALL show1
L47:
	; Line no: 65 => show(factorial(6));
	; show(factorial(6))
	SUB SP, 2
	; factorial(6)
	MOV AX, 6
	PUSH AX
	CALL factorial3
	CALL show1
L48:
	; Line no: 66 => return 0;
	MOV AX, 0
	JMP L35
L35:
	MOV SP, BP
	POP BP
	MOV AX, 4CH
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
