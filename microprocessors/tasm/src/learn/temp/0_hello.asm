.MODEL SMALL
.STACK 100H

.DATA

MSG DB "Hello World$"

.CODE

START:
	MOV AX, SEG MSG
	MOV DS, AX
	MOV DX, OFFSET MSG
	MOV AH, 09H
	INT 21H

	MOV AX, 4C00H
	INT 21H
END START
