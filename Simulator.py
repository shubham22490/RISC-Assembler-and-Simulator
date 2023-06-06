import sys
import math

global pc
pc = 0

global RegInBin
RegInBin= ['000', '001', '010', '011', '100', '101', '110']

global RegList
RegList = [0]*7

global flag
flag = [0]*16

def todeci(num):
    ans = 0
    j = len(num)

    for i in range(len(num)):
        if (num[i] == "1" or num[i] == 1):
            ans += 2**(j-i-1)

    return ans


def toBin(n, bits):
    var = [0]*bits

    j = bits - 1
    while n > 0:
        var[j] = n % 2
        n //= 2
        j -= 1
        
    return var

#print(todeci([0,0,1,0]))

def add(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    val = RegList[ir2]+RegList[ir3]

    if(val >= 0 and val < 65536):
        RegList[ir1] = val
        flag = [0]*16
    else:
        RegList[ir1] = 0
        flag[12] = 1


def sub(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    val = RegList[ir2] - RegList[ir3]

    if(val >= 0 and val < 65536):
        RegList[ir1] = val
        flag = [0]*16
    else:
        RegList[ir1] = 0
        flag = [0]*16
        flag[12] = 1

def mul(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    val = RegList[ir2] * RegList[ir3]

    if(val >= 0 and val < 65536):
        RegList[ir1] = val
        flag = [0]*16
    else:
        RegList[ir1] = 0
        flag = [0]*16
        flag[12] = 1


def xor(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    RegList[ir1] = RegList[ir2] ^ RegList[ir3]
    flag = [0]*16


def Or(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    RegList[ir1] = RegList[ir2] | RegList[ir3]
    flag = [0]*16


def And(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])
    flag = [0]*16

    RegList[ir1] = RegList[ir2] & RegList[ir3]

def uJmp(inst):
    mem=RegInBin.index(inst[9:15])
    line_num=todeci(mem)
    pc=line_num-1
    
    return pc

def ltJmp(inst):
    if (flag[-3]==1):

        mem=RegInBin.index(inst[9:15])
        line_num=todeci(mem)
        pc=line_num-1
        return pc
    
def gtJmp(inst):
    if (flag[-2]==1):
        mem=RegInBin.index(inst[9:15])
        line_num=todeci(mem)
        pc=line_num-1
        return pc
    
def eJmp(inst):
    if (flag[-1]==1):
        mem=RegInBin.index(inst[9:15])
        line_num=todeci(mem)
        pc=line_num-1
        return pc
    

def movi(ins):
    ir1 = RegInBin.index(ins[6:9])
    imm = RegInBin.index(ins[9:16])
    immediate = todeci(imm)
    RegList[ir1] = imm
    flag = [0]*16


def leftshift(ins):
    ir1 = RegInBin.index(ins[6:9])
    imm = RegInBin.index(ins[9:16])
    immediate = todeci(imm)

    val = RegList[ir1] << imm
    RegList[ir1] = val
    flag = [0]*16

def rightshift(ins):
    ir1 = RegInBin.index(ins[6:9])
    imm = RegInBin.index(ins[9:16])
    immediate = todeci(imm)
    val = RegList[ir1] >> imm
    RegList[ir1] = val
    flag = [0]*16


def movi(ins):
    x = ins[6:9]
    ir1 = RegInBin.index(x)
    val = todeci(ins[9:])
    RegList[ir1] = val
    flag = [0]*16

def mov(ins):
    global flag
    ir1 = RegInBin.index(ins[10:13])
    if ins[13:16]=='111':
        RegList[ir1] = todeci(flag)
    else:
        ir2 = RegInBin.index(ins[13:16])
        RegList[ir1] = RegList[ir2]
    flag = [0]*16

def cmp(ins):
    ir1 = RegInBin.index(ins[10:13])
    ir2 = RegInBin.index(ins[13:16])
    flag = [0]*16
    if RegList[ir1]<RegList[ir2]:
        flag[13]=1
    elif RegList[ir1]>RegList[ir2]:
        flag[14]=1
    else:
        flag[15]=1


def invert(ins):
    ir1 = RegInBin.index(ins[10:13])
    ir2 = RegInBin.index(ins[13:16])
    num=RegList[ir2]
    n=int(math.log(num,2))+1
    L=toBin(num, n)
    for i in range(len(L)):
        if L[i]==1:
            L[i]=0
        else:
            L[i]=1
    RegList[ir1]=todeci(L)
    flag = [0]*16
    


def div(ins):
    ir1 = RegInBin.index(ins[10:13])
    ir2 = RegInBin.index(ins[13:16])
    if RegList[ir2]!=0:
        q=RegList[ir1]//RegList[ir2]
        r=RegList[ir1]%RegList[ir2]
        RegList[0]=q
        RegList[1]=r
    else:
        flag = [0]*16
        flag[12]=1
        RegList[0]=0
        RegList[1]=0


def memorydump(instruct,i):
    for j in range(i):
        print(instruct[j])

    for j in range(128-i):
        print("0000000000000000")


def print_me(lst):
    for i in lst:
        print(i,end="")
    print(" ", end = "")

def regDump(lineNum):
    print_me(toBin(lineNum,7))
    print(" "*7, end = "")
    print_me(toBin(RegList[0],16))
    print_me(toBin(RegList[1],16))
    print_me(toBin(RegList[2],16))
    print_me(toBin(RegList[3],16))
    print_me(toBin(RegList[4],16))
    print_me(toBin(RegList[5],16))
    print_me(toBin(RegList[6],16))
    print_me(flag)
    print()

instructions = dict()

i = 0 

for line in sys.stdin:
    line = line.strip()
    if(line):
        instructions[i] = line
        i += 1
        
j=0
#print(instructions)

#Main function begins here
while(j<i and (instructions[j][0:5])!="11010"):
    opcode=(instructions[j][0:5])
    
    if (opcode=="00000"):
        add(instructions[j])
    elif (opcode=="00001"):
        sub(instructions[j])
    elif (opcode=="00010"):
        movi(instructions[j])
    elif (opcode=="00110"):
        mul(instructions[j])
    elif (opcode=="01010"):
        xor(instructions[j])
    elif (opcode=="01011"):
        Or(instructions[j])
    elif (opcode=="01100"):
        And(instructions[j])
    elif (opcode=="00011"):
        mov(instructions[j])
    elif (opcode=="00111"):
        div(instructions[j])
    elif (opcode=="01101"):
        invert(instructions[j])
    elif (opcode=="01110"):
        cmp(instructions[j])
    elif (opcode=="01111"):
        j=uJmp(instructions[j])
    elif (opcode=="11100"):
        j=ltJmp(instructions[j])
    elif (opcode=="11101"):
        j=gtJmp(instructions[j])
    elif (opcode=="11111"):
        j=eJmp(instructions[j])

    regDump(j)
    j+=1

memorydump(instructions,i)
