.MODEL MEDIUM
.STACK 200H
.CODE

START:
	MOV AX, 0003H
	INT 10H

	MOV BX, 0B800H
	MOV ES, BX
	MOV BX, 0
	MOV AH, 1

	MOV CX, 100

	STARTLOOP:
		MOV ES:[BX], AH
		ADD BX, 2
		ADD AH, 1
	LOOP STARTLOOP

	MOV AX, 0100H
	INT 21H

	MOV AX, 4C00H
	INT 21H
END START
