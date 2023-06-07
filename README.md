# **Assembly Code Conversion**

The program is designed to take input in assembly code from a file named Assembly.txt and write
the corresponding machine language for the instructions in a file names Ans.txt.


**File Structure**

The code consists of the following files:
• main.c: Contains the main program logic and functions for parsing andconverting
assembly code.
• README.md: This file, providing information about the code.
• Assembly.txt: Input file containing the assembly code.
• Ans.txt: Output file where the machine code will be written.


**Supported Instructions**

The program supports the following assembly instructions:
* Type A Instructions: add, sub, mul, xor, or, and, addf, subf
* Type B Instructions: mov, rs, ls, movf
* Type C Instructions: div, not, cmp, sqr, cub
* Type D Instructions: jmp, jlt, jgt, je, hlt
* Type E Instructions: jmp, jlt, jgt, je, hltwith binary values
* Type F Instructions: hlt
* Type G Instructions: push, pop
* Type H Instructions: pushi


**Usage**


To use the program, follow these steps:
1. Firstly we need to initialize a file Assembly.txt which has the assembly level
instructions encoded in it.
2. Secondly, we compile the main function and store the corresponding machine code in
Ans.txt file that is created.

**Floating Point Operations**
typebf, addf, subf and movf are used to handle the float operations and store them in the given format.
**Error Handling**


The program performs basic error handling and provides error messages in the following cases:
* Typo in register name: If there is a typo in the register name used in the assembly code,the
program will raise this error.
* Unnecessary elements in the instruction: If there are unnecessary elements (e.g., extra spaces
or characters) in an instruction, the program will raise this error.
* Illegal immediate value: If the immediate value used in the assembly code is not within the
range of numbers (0 to 127), the program will raise this error.
* Variables not declared at the beginning: If any variables are used before initialized using the
"var" keyword at the beginning of the code, the program will this error.
* Variables used as labels and vice versa: If any variable is used in place of a label or a label is
called in place of a variable, this error will be raised.
* Illegal use of FLAGS register: If the flag register is used without setup, this error shall be
raised.
* Hlt not mentioned or not mentioned at the end of code: If halt is not mentioned in the code or
mentioned in between the code, this error is raised.
Limitations
* The program assumes that the assembly code provided follows a specific format, and
any change in the format may result in errors or unexpected behavior.
* The program only supports the instructions mentioned above. Additional instructions or
variations may not be recognized.
* The program does not perform extensive error checking or syntax analysis. It assumes that
the input assembly code is valid and all other differences are treated as errors.



# **Simulator Working**
This program is designed to take input as machine code and then perform the operations on the registers on the basis of the opcode.

**Code Structure**
1. Importing Modules and Setting up Global Variables
 * Firstly we import two modules sys and math.
 * Then we set up the following global variables 
   .  pc: Program Counter, which keeps track of the current instruction being executed.
   .  RegInBin: A list of binary representations of registers.
   .  RegList: A list representing the registers, initially filled with zeros.
   .  flag: A list representing the flags, initially filled with zeros.
   .  memory: A dictionary representing the memory storage. 
   .  stack: A stack storing the values pushed into it.
2. Converter Functions
 * todeci(num): Converts a binary number represented as a list of bits to decimal.
 * toBin(n, bits): Converts a decimal number to binary represented as a list of bits with the specified number of bits.
3. We write the simulation program for all the instructions previously mentioned in the assembler
 * add(inst): Executes an add instruction by adding the values of two registers and storing the result in another register.
 * addf(inst): Executes an add instruction by adding the values of two registers(float numbers) and storing the result in another register.
 * sub(inst): Executes a subtract instruction by subtracting the value of one register from another and storing the result in another register.
 * subf(inst): Executes a subtract instruction by subtracting the value of one register from another(float numbers) and storing the result in another register.
 * mul(inst): Executes a multiply instruction by multiplying the values of two registers and storing the result in another register.
 * xor(inst): Executes a bitwise XOR instruction by performing a bitwise XOR operation between two registers and storing the result in another register.
 * Or(inst): Executes a bitwise OR instruction by performing a bitwise OR operation between two registers and storing the result in another register.
 * And(inst): Executes a bitwise AND instruction by performing a bitwise AND operation between two registers and storing the result in another register.
 * uJmp(inst): Executes an unconditional jump instruction by setting the program counter to the specified memory address.
 * movi(ins): Executes a move immediate instruction by storing an immediate value in a register.
 * movf(ins): Executes a move immediate instruction by storing an immediate floating point value in a register.
 * leftshift(ins): Executes a left shift instruction by shifting the bits of a register to the left by a specified number of positions.
 * rightshift(ins): Executes a right shift instruction by shifting the bits of a register to the right by a specified number of positions.
 * mov(ins): Executes a move instruction by copying the value of one register to another register or the flag register.
 * cmpr(ins): Executes a compare instruction by comparing the values of two registers and setting the flag register accordingly.
 * invert(ins): Executes an invert instruction by inverting the bits of a register.
 * div(ins): Executes a divide instruction by dividing the value of one register by another and storing the quotient and remainder in two specific registers.
 * load(inst): Executes a load instruction by loading the value from memory into a register.
 * store(inst): Executes a store instruction by storing the value from a register into memory.
 * sqr(ins): Executes a square instruction by squaring the value of a register and storing the result in another register.
 * cube(ins): Executes a cube instruction by cubing the value of a register and storing the result in another register.
 * push(ins): Executes a push instruction by pushing the value of a register onto the stack.
 * pushi(ins): Executes a push immediate instruction by pushing an immediate value onto the stack.
 * pop(ins)
4. Memory Dump and Register Data Print
 * memorydump(instruct, i): Prints the contents of the memory.
 * print_me(lst): Prints the given list.
 * regDump(lineNum): Prints the register values along with the program counter and flags. 
5. Main Loop
 * Finally we execute the main loop and keep processing on instructions until we reach halt
