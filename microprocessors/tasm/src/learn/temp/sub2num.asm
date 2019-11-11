.model small
.stack 100h

include io.inc	; printstr, stoi, itos

.data
	num1 dw ?
	num2 dw ?
	msg1 db 13, 10, 'Enter first number (num1): $'
	msg2 db 13, 10, 'Enter second number (num2): $'
	crlf	db 13, 10, '$'
	submsg db 13, 10, 'Difference (num1 - num2): $'
.code

main proc
	mov ax, @data
	mov ds, ax

	;------------------------take first number as input----------------------------
	mov dx, offset msg1
	call printstr
	
	mov ah, 0ah
	mov dx, offset bufferin
	int 21h

	call stoi	; convert input to integer (stored in bx)
	mov num1, bx	; save in num1
	; -----------------------------------------------------------------------------

	call clearbuffer	; clear buffer to discard any previous values in buffer

	;------------------------take second number as input---------------------------
	mov dx, offset msg2
	call printstr

	mov ah, 0ah
	mov dx, offset bufferin
	int 21h

	; make sure to uncomment the next two lines if you aren't displaying a string with already present CRLF at beginning, otherwise expect problems with output
	;mov dx, offset crlf
	;call printstr	

	call stoi	; convert input to integer (stored in bx)
	mov num2, bx	; save in num2
	;------------------------------------------------------------------------------


	;------ subtract the numbers and display result--------
	mov ax, num1
	sub ax, num2
	call itos

	mov dx, offset submsg
	call printstr

	mov dx, offset bufferout
	call printstr
	;-------------------------------------------------

	mov ax, 4c00h
	int 21h
main endp
end main

