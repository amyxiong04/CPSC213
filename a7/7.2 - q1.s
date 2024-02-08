.pos 0x0
    ld   $sb, r5         # 
    inca r5              # Set stack pointer at the bottom of the stack
    gpc  $6, r6          # Set r6 as return address for this address
    j    0x300           # Go to main (0x300)
    halt                 # End program

.pos 0x100
    .long 0x00001000     #

.pos 0x200               # foo(arg1, arg2)
    ld   (r5), r0        # Load arguments into registers
    ld   4(r5), r1       # ^
    ld   $0x100, r2      # r2 = 0x100
    ld   (r2), r2        # r2 = 0x1000 (pointer to an array of size 10)
    ld   (r2, r1, 4), r3 # 
    add  r3, r0          # Add array[arg2] + arg1
    st   r0, (r2, r1, 4) # Store array[arg2] + arg1 in array[arg2]
    j    (r6)            # Return 

.pos 0x300               # main()
    ld   $-12, r0        # BEGINNING OF CALLEE PROLOGUE FOR main
    add  r0, r5          # Allocate space in stack for this activation frame
    st   r6, 8(r5)       # Store return address in activation frame below locals
    ld   $1, r0          # 
    st   r0, (r5)        # Store 1 in local 1
    ld   $2, r0          #
    st   r0, 4(r5)       # Store 2 in local 2
    ld   $-8, r0         # BEGINNING OF CALLER PROLOGUE FOR foo
    add  r0, r5          # Allocate space in stack for arguments of foo
    ld   $3, r0          #
    st   r0, (r5)        # Store 3 in arg 1
    ld   $4, r0          # 
    st   r0, 4(r5)       # Store 4 in arg 2
    gpc  $6, r6          # Store return address in r6
    j    0x200           # Go to foo
    ld   $8, r0          # BEGINNING OF CALLER EPILOGUE FOR foo
    add  r0, r5          # Deallocate space in stack for arguments
    ld   (r5), r1        # Load local variables into registers
    ld   4(r5), r2       # ^
    ld   $-8, r0         # BEGINNING OF CALLER PROLOGUE FOR foo
    add  r0, r5          # Allocate space in stack for arguments 
    st   r1, (r5)        # Store local 1 in arg 1
    st   r2, 4(r5)       # Store local 2 in arg 2
    gpc  $6, r6          # Store return address in r6
    j    0x200           # Go to foo
    ld   $8, r0          # BEGINNING OF CALLER EPILOGUE FOR foo
    add  r0, r5          # Deallocate space in stack for arguments
    ld   8(r5), r6       # Load return address of main
    ld   $12, r0         # BEGINNING OF CALLER EPILOGUE FOR main
    add  r0, r5          # Deallocate activation frame of main
    j    (r6)            # Return

.pos 0x1000
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

.pos 0x8000
    # These are here so you can see (some of) the stack contents
    # while running the code on the simulator.
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