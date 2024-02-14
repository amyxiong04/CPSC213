.pos 0x100
start:
    ld   $sb, r5         #
    inca r5              # Set stack pointer to the bottom of the stack
    gpc  $6, r6          # Store return address in r6
    j    main            # Go to main 
    halt

f:
    deca r5              # Allocate space in stack for local variable
    ld   $0, r0          # Load return value (default 0) into r0
    ld   4(r5), r1       # Load argument into r1
    ld   $0x80000000, r2 # r2 = largest negative integer
f_loop:
    beq  r1, f_end       # Go to f_end if r1 = 0
    mov  r1, r3          # Copy r1 into r3
    and  r2, r3          # Mask out all bits except for leftmost
    beq  r3, f_if1       # If leftmost bit is 0, do not increment return value
    inc  r0              # If leftmost bit is 1, increment return value
f_if1:
    shl  $1, r1          # Shift bits left by 1
    br   f_loop          # 
f_end:
    inca r5              # Deallocate space in stack for local variable
    j    (r6)            # Return r0 

main:
    deca r5              # Allocate space in stack for return address
    deca r5              # Allocate space in stack for local variable (local 1)
    st   r6, 4(r5)       # Store r6 as return address
    ld   $8, r4          # r4 = i = 8 (loop counter)
main_loop:
    beq  r4, main_end    # If i = 0, go to main_end
    dec  r4              # Decrement i
    ld   $x, r0          # 
    ld   (r0, r4, 4), r0 # Load x[i] into r0
    deca r5              # Allocate space in stack for argument (arg 1)
    st   r0, (r5)        # Store x[i] into arg 1
    gpc  $6, r6          # Store return address in r6
    j    f               # Go to f
    inca r5              # Deallocate space in stack for argument
    ld   $y, r1          # 
    st   r0, (r1, r4, 4) # Store return value in y[i]
    br   main_loop       # Go to main_loop
main_end:
    ld   4(r5), r6       # Load return address from start
    inca r5              # Deallocate space for local variable 
    inca r5              # Deallocate space for return address
    j    (r6)            # Return to start

.pos 0x2000
x:
    .long 1
    .long 2
    .long 3
    .long -1
    .long -2
    .long 0
    .long 184
    .long 340057058

y:
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0

.pos 0x8000
# These are here so you can see (some of) the stack contents.
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
sb: .long 0