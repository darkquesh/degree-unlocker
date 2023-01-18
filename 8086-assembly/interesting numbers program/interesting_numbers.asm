        .model small
        .stack 64
;--------------------------------
        .data
hello       db 'Welcome to Interesting Numbers Program!', 0Dh, 0Ah, '$'
prompt      db 0Dh, 0Ah, 0Dh, 0Ah,'Press 1-4 to select a menu: ', 0Dh, 0Ah, '$'
menu1_str   db 0Dh, 0Ah, 'MENU 1: Magical Fibonacci', 0Dh, 0Ah, '$'
menu2_str   db 0Dh, 0Ah, 'MENU 2: Factorial', 0Dh, 0Ah, '$'
menu3_str   db 0Dh, 0Ah, 'MENU 3: Squares and Square Roots', 0Dh, 0Ah, '$'
menu4_str   db 0Dh, 0Ah, 'MENU 4: Prime Numbers', 0Dh, 0Ah, 0Dh, 0Ah, '$'
about_str   db 0Dh, 0Ah, 'About the program (press A)', 0Dh, 0Ah, '$'
credits_Str db 0Dh, 0Ah, 'Credits (press C)', 0Dh, 0Ah, '$'
me1         db 'darkquesh', 0Dh, 0Ah, 0Dh, 0Ah, '$'
me2         db 0Dh, 0Ah, 'github.com/darkquesh', 0Dh, 0Ah, '$' 
me3         db 0Dh, 0Ah, ' ', 0Dh, 0Ah, '$'
me4         db 0Dh, 0Ah, '2021/2022 Spring Term Project', 0Dh, 0Ah, '$'

about0      db 'This is a program that gives several mathematical '
            db 'calculation options to the user with a Menu. 4 main '
            db 'functions that this program performs are', 0Dh, 0Ah, '$'
            
about1      db 0Dh, 0Ah, 2Ah, ' Menu 1: Check if a number entered by user '
            db 'is a "Fibonacci" number and print all Fibonacci numbers upto '
            db 'that number. If it is not a Fibonacci number, this function '
            db 'should give the nearest Fibonacci number that is smaller than '
            db 'the input and Fibonacci numbers before that.', 0Dh, 0Ah, '$'
            
about2      db 0Dh, 0Ah, 2Ah, ' Menu 2: Calculate the "Factorial" of a given number '
            db 'and print the result to the user.', 0Dh, 0Ah, '$'
            
about3      db 0Dh, 0Ah, 2Ah, ' Menu 3: Check if a number entered by user is "square" '
            db 'of an integer and print that integer to the user. If not, '
            db 'print the nearest square number that is smaller than the user '
            db 'input and print its square root as well.', 0Dh, 0Ah, '$'
            
about4      db 0Dh, 0Ah, 2Ah, ' Menu 4: Check if a number entered by user is a '
            db '"Prime" number and print the result. If not find the nearest '
            db 'Prime number that is smaller than the user input and print it.', 0Dh, 0Ah, '$'

about_end   db 0Dh, 0Ah, 2Ah, 2Ah, ' Press any key to go back...', 0Dh, 0Ah, '$'

egg         db 0Dh, 0Ah, 0Dh, 0Ah, 'DONT PANIC', 0Dh, 0Ah, '$'

menu1_str1  db 'Enter a max. 3-digit non-negative integer to check whether it is a Fibonacci one: ', '$' 
yes_Fib     db 0Dh, 0Ah, 0Dh, 0Ah, 'Bingo! It is indeed a Fibonacci number.', 0Dh, 0Ah, '$' 
no_Fib      db 0Dh, 0Ah, 0Dh, 0Ah, 'Try again, it is not a Fibonacci number  :(', 0Dh, 0Ah, '$'

menu2_str1  db 'Enter a non-negative integer (<7) to get its Factorial: ', '$' 
fact_str    db 0Dh, 0Ah, 0Dh, 0Ah, 'Its factorial value is ', '$'
fact_error  db 0Dh, 0Ah, 0Dh, 0Ah, 'The entered integer is not smaller than 7! Press any key to try again.', 0Dh, 0Ah, '$'

menu3_str1  db 'Enter a max. 3-digit non-negative integer to check whether it is a square of an integer: ', '$'
yes_sq      db 0Dh, 0Ah, 0Dh, 0Ah, 'Gotcha! It is the square of: ', '$' 
no_sq       db 0Dh, 0Ah, 0Dh, 0Ah, 'Nope, it is not a square of any integer', 0Dh, 0Ah, '$'
no_sq1      db 0Dh, 0Ah, 'The nearest square number is: ', '$'
no_sq2      db 0Dh, 0Ah, 'Its square root is: ', '$'

menu4_str1  db 'Enter a max. 3-digit non-negative integer to check whether it is a prime number: ', '$'
yes_Pr      db 0Dh, 0Ah, 0Dh, 0Ah, 'Yeah! ', '$'
yes_Pr2     db ' is a prime number.', 0Dh, 0Ah, '$' 
no_Pr       db 0Dh, 0Ah, 0Dh, 0Ah, 'Sorry, it is not a prime number.', 0Dh, 0Ah, '$' 
no_Pr1      db 0Dh, 0Ah, 'The nearest prime number is: ', '$'


num0        db 0, 0, 0
digit_count db 0
ten         db 10
;ten_w      dw 10
entered_num dw ?

fib_nums    dw 5 dup(?), '$'
fact_num    dw 5 dup(?), '$'
sq_num      dw 5 dup(?), '$'
sqrt_num    dw 5 dup(?), '$'
prime_num   dw 2 dup(?), '$' 

press_any   db 0Dh, 0Ah, 0Dh, 0Ah, 'Press any key to continue... ', 0Dh, 0Ah, '$'
newline     db 0Dh, 0Ah, '$'                    
exit        db 0Dh, 0Ah, 'Exit the program (press ESC)', 0Dh, 0Ah, '$'
stop_pr     db 0Dh, 0Ah, 0Dh, 0Ah, 'So long, and thanks for all the input', 0Dh, 0Ah, '$'  
;--------------------------------
        .code
        
CHECK_QUIT  PROC
    mov AH, 01h   ;read character from
	INT 21h       ; keyboard input
	cmp AL, 1Bh   ;is ESC pressed?
	jz stop       ;if yes, terminate program
	ret            
ENDP CHECK_QUIT


PRINT_MENU  PROC
    xor BX, BX    ;page number = 0
    
    call CLEAR_SCR
    
    lea AX, data
    mov DS, AX
        
    lea DX, hello
    mov AH, 09h   ;print hello to std output
    INT 21h
        
	lea DX, prompt
	mov AH, 09h   ;print prompt to std output
	INT 21h

	lea DX, menu1_str
	mov AH, 09h   ;print menu1 to std output
	INT 21h

	lea DX, menu2_str
	mov AH, 09h   ;print menu2 to std output
	INT 21h

	lea DX, menu3_str
	mov AH, 09h   ;print menu3 to std output
	INT 21h

	lea DX, menu4_str
	mov AH, 09h   ;print menu4 to std output
	INT 21h 

	lea DX, about_str
	mov AH, 09h   ;print about to std output
	INT 21h
	
	lea DX, credits_str
	mov AH, 09h   ;print credits to std output
	INT 21h

	lea DX, exit
	mov AH, 09h   ;print exit to std output
	INT 21h
	
	ret           
ENDP PRINT_MENU


CLEAR_SCR   PROC
    ;clear screen                 
    mov AX, 0600h   ;scroll window up
    mov BH, 07h     ;normal attribute
    xor CX, CX      ;X and Y of top left 0000
    mov DX, 184Fh   ;X and Y of bottom right
    INT 10h         
    
    ;cursor to the top left (0,0)
    mov AH, 02      ;set cursor position
    xor BX, BX      ;BH=0, page 0
    xor DX, DX      ;X and Y position 0,0
    INT 10h
    ret    
ENDP    CLEAR_SCR



ABOUT PROC
    call CLEAR_SCR  ;clear screen
    
    xor BX, BX    ;page number = 0
    
    lea DX, about0
	mov AH, 09h   ;print about0 to std output
	INT 21h
	
	lea DX, about1
	mov AH, 09h   ;print about1 to std output
	INT 21h
	
	lea DX, about2
	mov AH, 09h   ;print about2 to std output
	INT 21h
	
	lea DX, about3
	mov AH, 09h   ;print about3 to std output
	INT 21h
	
	lea DX, about4
	mov AH, 09h   ;print about4 to std output
	INT 21h
	
	lea DX, about_end
	mov AH, 09h   ;print about_end to std output
	INT 21h

	mov AH, 08h   ;press any key to continue
    INT 21h
    
    cmp AL, 1Bh   ;is ESC pressed?
	jz stop
	
	call MAIN     
ENDP ABOUT



CREDITS PROC
    call CLEAR_SCR  ;clear screen
    
    xor BX, BX    ;page number = 0
    
    lea DX, me1
	mov AH, 09h   ;Eren Karadag - 21947311
	INT 21h 	
	
	lea DX, me2
	mov AH, 09h   ;Hacettepe University EE
	INT 21h
	
	lea DX, me3
	mov AH, 09h   ;ELE338
	INT 21h
	
	lea DX, me4
	mov AH, 09h   ;21/22 Spring Term Project
	INT 21h
	
	lea DX, press_any
	mov AH, 09h   ;press any key to continue
	INT 21h

	mov AH, 08h   ;press any key to continue
    INT 21h
    
    cmp AL, 1Bh   ;is ESC pressed?
	jz stop
	
	call MAIN     
ENDP CREDITS



GET_INPUT PROC
    xor CX, CX      ;clear CX
    mov digit_count, 0
    mov CL, 3       ;expecting 3 digit numbers
    lea SI, num0    ;entered digits
    
    input:
	mov AH, 01h     ;read character from 
	INT 21h         ; keyboard input
	
	cmp AL, 1Bh     ;is ESC pressed?
	jz stop
	
	cmp AL, 0Dh     ;did user press enter?
	jz digits       ;if not, get more digits
	
	mov BL, AL      ;copy AL into BL 
	sub BL, 30h     ;ASCII conversion
	mov [SI], BL    ;store the digits in x_pixel variable
	inc digit_count ;increase digits
	inc SI          ;point to the next digit place
	loop input      ;repeat loop
	
	digits:
	dec SI          ;decrement SI to point the last digit
	xor AX, AX      ;clear AX
	xor CX, CX      ;clear CX
	mov DL, digit_count ;copy digit_count into DL
		
	mov CL, [SI]    ;move the last digit to CL
	dec DL          ;one digit done
	cmp DL, 0       ;if the number has only one digit 
	jz ret_chk      ;compute its sqrt
	dec SI          ;point to the tens place
	mov AL, [SI]    ;copy it into AL
	mul ten         ;multiply it by 10
	add CX, AX      ;CX = CX + AX
	dec SI          ;point to the hundreds place
	cmp DL, 1       ;if the number has only 2 digits
	jz ret_chk      ;jump to compute its sqrt
	mov AL, [SI]    ;move the first digit to AL
	mul ten         ;multiply it
	mul ten         ; by 100
	add CX, AX      ;CX = CX + AX
	
	ret_chk:
	mov entered_num, CX ;store the value in CX in the entered_num variable
	
	cmp entered_num, 42
	jnz ret_chk2
	
	call ANSWER2ALL
	 
	ret_chk2:	
	ret    
    
ENDP GET_INPUT


ANSWER2ALL PROC    
    lea DX, egg
	mov AH, 09h
	INT 21h
	ret
ENDP    ANSWER2ALL    
    

NEW_LINE PROC       
    lea DX, newline
	mov AH, 09h   ;print a new line
	INT 21h
	ret	        
ENDP NEW_LINE


CHECK_MENU  PROC
    
    cmp BP, 1   ;Menu1 selected
    jz address1
    
    cmp BP, 2   ;Menu2
    jz address2
    
    cmp BP, 3   ;Menu3
    jz address3
    
    cmp BP, 4   ;Menu4
    jz address4
    
    cmp BP, 5   ;/Menu3-sqrt\
    jz address5
    
    address1:   ;load the respective value addresses to DI
    lea DI, fib_nums
    jmp ret_check_menu
    
    address2:
    lea DI, fact_num
    jmp ret_check_menu
    
    address3:
    lea DI, sq_num
    jmp ret_check_menu
    
    address4:
    lea DI, prime_num 
    jmp ret_check_menu
    
    address5:
    lea DI, sqrt_num  
    
    ret_check_menu:
    ret
        
ENDP CHECK_MENU


HEX2DEC PROC  ;hex to dec conversion 
    
    call CHECK_MENU 
    
    mov DX, AX      ;copy AX into DX     
    mov [SI+2], 20h ;last digit is space (for 2-digit numbers)
      
    start_dec:
    cmp DX, 00FFh   ;is the value in DX greater than 255?
    jnb fix_it      ;if so, divide it by 10
    
    cont_dec:    
    cmp AH, 0       ;is AH zero?
    jnz write       ;if not, store it 
        
    div ten         ;divide by 10
    cmp AH, 0
    jz write
    cmp AL, ten     ;compare quotient with 10
    jae start_dec     ;if greater or equal, execute hex2dec again
        
    mov CX, AX      ;copy AX into CX   
    add CL, 30h     ;ASCII conversions
    add CH, 30h     
    mov [SI], CX    ;store the number in DS:SI 
        
    printY:         ;print the eentered value
    push BX         ;push BX for later use
    xor BX, BX      ;page number=0
    mov AH, 09h     ;write string to std output
    mov DX, DI
    INT 21h
    jmp ret_dec     ;return
                         
    write:
    add AH, 30h     ;ASCII conversion
    mov [SI+2], AH  ;store the last digit
    xor AH, AH      ;clear AH
    
    cmp AX, 0       ;is the entered number zero?
    jz printY       ;if so, print it
    jnz cont_dec    ;if not, get its decimal equivalent
    
        
    fix_it:    ;numbers > 255
    div ten
    jmp write         
    
    ret_dec:
    pop BX          ;pop BX to get its value back
    ret        
ENDP HEX2DEC


MENU1   PROC    ;***Fibonacci***
    
    mov BP, 1       ;Menu1   
    call CLEAR_SCR  ;clear screen
    
    lea DX, menu1_str1
	mov AH, 09h     ;print menu1_str1 to std output
	INT 21h 
	
    call GET_INPUT  ;get input from the user
    call NEW_LINE   ;print two
    call NEW_LINE   ; new lines
    
    lea SI, fib_nums   ;load the address of the variable fib_nums
    
    mov AX, entered_num ;copy the entered number into AX
    xor DX, DX    ;clear DX
       
    mov BX, 1     ;start BX
    mov CX, 1     ; and CX from 1
        
    fibonacci:  ;fibonacci loop
    cmp AX, DX    ;is the number less or equal than DX?
    jbe check_fib ;if yes check it
    add BX, CX    ;BX = BX + CX
    mov DX, CX    ;copy CX into DX
    mov CX, BX    ;move BX into CX 
    mov BX, DX    ;move DX into BX
       
    push AX       ;push AX
    push CX       ;     CX
    push DX       ;     DX for later use
    mov AX, DX
    call HEX2DEC  ;hexadecimal to decimal conversion
    pop DX        ;pop 'em
    pop CX
    pop AX
    
    check_fib:        
    cmp CX, entered_num 
    jna fibonacci
    cmp DX, AX    ;the entered value is
    jnz noF       ; not a Fibonacci number
    
    lea DX, yes_Fib
	mov AH, 09h   ;it's a Fibonacci number
	INT 21h    
    jmp ret_fib
    
    noF:
    xor BX, BX    ;page number=0
    lea DX, no_Fib
	mov AH, 09h   ;it's not Fibonacci number
	INT 21h
        
	ret_fib:
	xor BX, BX    ;page number = 0
	lea DX, press_any
	mov AH, 09h   ;press any key 
	INT 21h
	mov AH, 08h   ; to continue
	INT 21h
	ret
ENDP MENU1  ;**Fibonacci**



MENU2   PROC    ;***Factorial*** 
    
    mov BP, 2       ;Menu2   
    call CLEAR_SCR  ;clear screen
    
    xor BX, BX      ;page number = 0
    lea DX, menu2_str1
	mov AH, 09h     ;print menu1_str1 to std output
	INT 21h 
	
    call GET_INPUT  ;get keyboard input
    call NEW_LINE   ;print a new line
    
    lea SI, fact_num    ;load the address of the variable fact_num
    mov AX, entered_num ;copy the entered number into AX   
    mov BX, AX          ;   copy it into BX
    dec BX              ;decrement BX to compute its Factorial
    
    cmp AX, 6           ;is the Factorial value larger than 4 digits?
    ja factorial_error  ;if so, get input again
    
    cmp AX, 1       ;is the entered value 0 or 1?
    ja factorial    ;if not, calculate its factorial
    
    initfacts:
    mov AX, 1       ;0 and 1 has both factorial value of 1
    jmp print_fact
    
    factorial:
    mul BX         ;AX = AX * BX
    dec BX         ;BX = BX - 1
    cmp BX, 0      ;is factorial computation done?
    jnz factorial  ;if so, print it
        
    print_fact:
    push AX        ;push AX for later use
    xor BX, BX    ;page number = 0
    lea DX, fact_str   ;Factorial value is: 
	mov AH, 09h
	INT 21h
	pop AX         ;pop AX to use it in HEX2DEC function
    call HEX2DEC   ;hexadecimal to decimal conversion
    jmp ret_fact
    
    factorial_error:
    xor BX, BX    ;page number = 0
    lea DX, fact_error
	mov AH, 09h   ;entered number > 6 
	INT 21h
	mov AH, 08h   ; to continue
	INT 21h
	jmp MENU2
        
	ret_fact:
	xor BX, BX    ;page number = 0
	lea DX, press_any
	mov AH, 09h   ;press any key 
	INT 21h
	mov AH, 08h   ; to continue
	INT 21h
	
	ret
ENDP MENU2  ;***Factorial***



MENU3   PROC ; ** * Square * **
    mov BP, 3   ;Menu3
    
    xor BX, BX    ;page number = 0
    
    call CLEAR_SCR  ;clear screen
    
    lea DX, menu3_str1
	mov AH, 09h     ;print menu3_str1 to std output
	INT 21h 
	
    call GET_INPUT  ;get keyboard input
    call NEW_LINE   ;print a new line 
    
    lea SI, sq_num      ;load the address of the variable sq_num
    mov BX, entered_num ;copy the entered number into BX 
    mov CX, 1       ;start CX from 1
    
    cmp BX, 0       ;is BX zero?
    jnz square      ;if not, calculate its square
    mov CX, 0       ;if so, its square is zero
    jmp yes_square 
    
    square:
    mov DI, AX      ;copy AX into DI
    mov AX, CX      ;copy the counter into AX 
    mul CX          ;AX = AX*CX
    cmp AX, BX      ;is AX equal to BX
    je yes_square   ;if so, the entered value is a square of an integer
    cmp AX, BX
    ja no_square    ;if not, it is not a square
    inc CX          ;next multiplication
    jmp square
    
    yes_square:
    push BX
    xor BX, BX    ;page number = 0  
    lea DX, yes_sq ;print the yes_sq string
	mov AH, 09h    ;it's a square of an integer
	INT 21h
	pop BX
	mov AX, CX     ;copy CX into AX
	xor DX, DX     ;clear DX  
    call HEX2DEC   ;hex to dec conversion 
    jmp ret_sq
    
    no_square:
    push BX
    xor BX, BX    ;page number = 0
    lea DX, no_sq
	mov AH, 09h   ;it's not a square of an integer
	INT 21h
	
	lea DX, no_sq1
	mov AH, 09h   ;The nearest smaller square number
	INT 21h
	
	inc CX        ;increment CX
    mov AX, DI    ;copy DI into AX
	xor DX, DX    ;clear DX  
    call HEX2DEC
	
	xor BX, BX    ;page number = 0
	lea DX, no_sq2
	mov AH, 09h   ;Its square root
	INT 21h
	
	pop BX
	xor CX, CX    ;clear CX
	xor AX, AX    ;      AX
	call SQRT     ;calculate its square root value
	mov AX, CX    ;store the sqrt value into AX
	lea SI, sqrt_num ;load the address of the variable sqrt_num
	mov BP, 5       ;5th item is selected
	xor BX, BX    ;page number = 0
	call HEX2DEC    	
    
    ret_sq:
    xor BX, BX    ;page number = 0
    lea DX, press_any
	mov AH, 09h   ;press any key 
	INT 21h
	mov AH, 08h   ; to continue
	INT 21h
    ret
        
ENDP MENU3 ; ** * Square * **


SQRT PROC
     ;*Linear Search Algorithm*
    inc AX         ; //ascending order
    mul AX         ;  while( (L+1) * (L+1) <= y)
    cmp AX, BX     ;      L = L+1;
    ja ret_sqrt  ;
    inc CX         ;  return L;
    mov AX, CX     ;  // L+1: AX     L: CX
    jmp sqrt       ;  // y: CX <- square-rooted value
    
    ret_sqrt:
    ret      
ENDP SQRT
 

MENU4   PROC    ;* * * Prime Number * * *
    mov BP, 4   ;Menu4
    
    xor BX, BX    ;page number = 0
    
    call CLEAR_SCR  ;clear screen
    
    lea DX, menu4_str1
	mov AH, 09h     ;print menu4_str1 to std output
	INT 21h 
	
    call GET_INPUT  ;get keyboard input
    call NEW_LINE   ;print a new line 
    
    lea SI, prime_num   ;load the address of the variable prime_num
    mov AX, entered_num ;store the entered number in AX  
    
    cmp AX, 2     ;is the entered value 0 or 1?
    jb initprimes ;if so, they are not primes
    
    mov BX, 2    ;initial value of the divider
    mov CX, AX   ;copy AX into CX

    L1:
    xor DX, DX   ;clear DX
    mov AX, CX   ;copy CX into AX
    div BX       ;AX: quotient, DX: remainder
    inc BX       ;increment the divider
    cmp DX, 0    ;is the remainder (DX) zero?
    jnz L1       ;if not, keep checking prime numbers

    add AX, DX   ;remainder+quotient
    cmp AX, 1    ;is AX equal to 1?
    jnz no_prime ;if not, it is not a prime number

    yes_prime:
    xor BX, BX    ;page number = 0
    cmp DI, 1     ;DI=1 is set to calculate the smallest prime number of a number if it is not prime
    jz no_prime2
    lea DX, yes_Pr
	mov AH, 09h   ;it's a prime number!
	INT 21h
	
	mov AX, CX    ;copy CX into AX
	xor DX, DX    ;clear DX  
    call HEX2DEC
    
    lea DX, yes_Pr2
	mov AH, 09h   ;it's a prime number!
	INT 21h
    jmp ret_prime

    no_prime:
    dec CX      ;decrement CX to check the previous number
	mov DI, 1   ;set DI to 1
	jmp L1
		
	no_prime2:
	xor BX, BX    ;page number = 0
	lea DX, no_Pr
	mov AH, 09h   ;it's not a prime number!
	INT 21h
	
	lea DX, no_Pr1
	mov AH, 09h   ;The nearest smaller prime number
	INT 21h
	
	mov AX, CX    ;copy CX into AX 
    call HEX2DEC
    jmp ret_prime
    
    initprimes: ;for 0 and 1
    xor BX, BX    ;page number = 0
    lea DX, no_Pr
	mov AH, 09h   ;it's not a prime number!
	INT 21h
    
    ret_prime:
    xor BX, BX    ;page number = 0
    lea DX, press_any
	mov AH, 09h   ;press any key 
	INT 21h
	mov AH, 08h   ; to continue
	INT 21h
    ret
    
ENDP MENU4

 
CHECK_KEY  PROC
	call CHECK_QUIT
	
	cmp AL, 'a'   ;is a pressed?
	jz ABOUT
	cmp AL, 'A'   ;is A pressed?
	jz ABOUT
	
	cmp AL, '1'   ;is 1 pressed?
	jz call1
	cmp AL, '2'   ;is 2 pressed?
	jz call2
	cmp AL, '3'   ;is 3 pressed?
	jz call3
	cmp AL, '4'   ;is 4 pressed?
	jz call4
	cmp AL, 'c'   ;is c pressed?
	jz call5
	cmp AL, 'C'   ;is C pressed?
	jz call5
	call CHECK_KEY
	
	call1:
	call MENU1
	jmp repeat
	
	call2:
	call MENU2
	jmp repeat
	
	call3:
	call MENU3
	jmp repeat
	
	call4:
	call MENU4
	jmp repeat
	
	call5:
	call CREDITS
	
	repeat:
	call MAIN
	ret
	            
ENDP CHECK_KEY


MAIN    PROC      
	call PRINT_MENU
	
	call CHECK_KEY        

	stop:
	xor BX, BX    ;page number = 0
	call CLEAR_SCR
	lea DX, stop_pr
    mov AH, 09h   ;print stop_pr to std output 
    
    INT 21h
	mov AH, 4Ch   ;terminate program
	INT 21h

END     MAIN