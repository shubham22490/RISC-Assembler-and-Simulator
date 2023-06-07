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
* Type A Instructions: add, sub, mul, xor, or, and 
* Type B Instructions: mov, rs, ls
* Type C Instructions: div, not, cmp
* Type D Instructions: jmp, jlt, jgt, je, hlt
* Type E Instructions: jmp, jlt, jgt, je, hltwith binary values
* Type F Instructions: hlt


**Usage**


To use the program, follow these steps:
1. Firstly we need to initialize a file Assembly.txt which has the assembly level
instructions encoded in it.
2. Secondly, we compile the main function and store the corresponding machine code in
Ans.txt file that is created.


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
2. Converter Functions
 * todeci(num): Converts a binary number represented as a list of bits to decimal.
 * toBin(n, bits): Converts a decimal number to binary represented as a list of bits with the specified number of bits.
3. We write the simulation program for all the instructions previously mentioned in the assembler
 * Each function takes an instruction (inst) as input and performs the corresponding operation on the registers, flags, or memory.
4. Memory Dump and Register Data Print
 * memorydump(instruct, i): Prints the contents of the memory.
 * print_me(lst): Prints the given list.
 * regDump(lineNum): Prints the register values along with the program counter and flags. 
5. Main Loop
 * Finally we execute the main loop and keep processing on instructions until we reach halt
