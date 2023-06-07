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

global stack
stack = []

memory = dict()

def todeci(num):
    ans = 0
    j = len(num)

    for i in range(len(num)):
        if (num[i] == "1" or num[i] == 1):
            ans += 2**(j-i-1)

    return ans


def toBin(n, bits):
    if type(n)==int:
        var = [0]*bits

        j = bits - 1
        while n > 0:
            var[j] = n % 2
            n //= 2
            j -= 1

        return var
    elif type(n)==float:
        var=toBinF(n)
        return var

# print(todeci([0,0,1,0]))

def add(inst):
    global flag
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
    global flag
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
    global flag
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
    global flag
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    RegList[ir1] = RegList[ir2] ^ RegList[ir3]
    flag = [0]*16


def Or(inst):
    global flag
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    RegList[ir1] = RegList[ir2] | RegList[ir3]
    flag = [0]*16


def And(inst):
    global flag
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])
    flag = [0]*16

    RegList[ir1] = RegList[ir2] & RegList[ir3]

def uJmp(inst):
    mem = inst[9:]
    line_num = todeci(mem)
    pc = line_num-1

    return pc

def toDeciF(list):
    exp=[0]*3
    for i in range(0,3):
        exp[i]=list[i]
    Exp=todeci(exp)

    e=Exp-3
    man=[0]*5
    for i in range(3,8):
        man[i-3]=list[i]
    sum=0
    a=1
    for i in range(0,5):
        sum+=man[i]*(2**(-a))
        a=a+1
    final=(1+sum)(2*e)
    return final

def toBinF(value):
    i=int(value)
    f=value-i
    arri=toBin(i,5)

    arrf=[0]*5
    a=0
    while(f>0):
        f=f*2
        arrf[a]=int(f)
        f=f-int(f)
        a+=1


    mix=[0]*11
    index=0
    for i in range(0,5):
        mix[index]=arri[i]
        index+=1
    mix[index]=-1
    index+=1
    for i in range(0,5):
        mix[index]=arrf[i]
        index+=1

    count=0
    flag=0
    v=0
    for i in range(0,11):
        if mix[i]==-1:
            flag=1
        if (mix[i]==1) and (flag==0):
            for j in range(i+1, 11):
                if mix[j]==-1:
                    v=1
                    break
                count+=1

        elif flag==1:
            for k in range(i+1, 11):
                count=count-1
                if mix[k]==1:
                    v=1
                    break
        if v==1:
            break
    exp=3+count

    EXPO=toBin(exp,3)

    man=[0]*5
    o=0
    for i in range(0,11):
        if mix[i]==1:
            o=i
            break
    o+=1
    bin=[0]*16
    for i in range(8,11):
        bin[i]=EXPO[8 - i]
    z=0
    for x in range(o,11):
        if (mix[x]!=-1) and (z<5):
            man[z]=mix[x]
            z+=1
    y=11
    for i in range(0,z):
        bin[y+i]=man[i]

    return bin

def addf(inst):
    global flag
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])


    val = RegList[ir2]+RegList[ir3]

    if(val >= 0 and val < 64):
        RegList[ir1] = val
        flag = [0]*16
    else:
        RegList[ir1] = 0
        flag[12] = 1

def subf(inst):
    global flag
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    val = RegList[ir2] - RegList[ir3]

    if(val >= 0):
        RegList[ir1] = val
        flag = [0]*16
    else:
        RegList[ir1] = 0
        flag = [0]*16
        flag[12] = 1

def movf(inst):
    global flag
    ir1 = RegInBin.index(inst[5:8])
    d=toDeciF(inst[8:])
    RegList[ir1]=d
    flag = [0]*1


def leftshift(ins):
    global flag
    ir1 = RegInBin.index(ins[6:9])
    imm = ins[9:16]
    immediate = todeci(imm)

    val = RegList[ir1] << imm
    RegList[ir1] = val
    flag = [0]*16

def rightshift(ins):
    global flag
    ir1 = RegInBin.index(ins[6:9])
    imm = ins[9:16]
    immediate = todeci(imm)
    val = RegList[ir1] >> imm
    RegList[ir1] = val
    flag = [0]*16


def movi(ins):
    global flag
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

def cmpr(ins):
    global flag
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
    global flag
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
    global flag
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

def load(inst):
    global memory
    global flag
    flag = [0]*16
    mem = inst[9:]
    ir1 = RegInBin.index(inst[6:9])
    if(mem in memory.keys()):
        RegList[ir1] = memory[mem]
        return
    RegList[ir1] = 0

def store(inst):
    global memory
    global flag
    flag = [0]*16
    mem = inst[9:]
    ir1 = RegInBin.index(inst[6:9])
    memory[mem] = RegList[ir1]
    return

def sqr(ins):
    global flag
    ir1 = RegInBin.index(ins[10:13])
    ir2 = RegInBin.index(ins[13:16])
    finalv=RegList[ir2]
    finalv=finalv**2
    if (finalv< 65536):
        RegList[ir1]=finalv
        flag = [0]*16
    else:
        RegList[ir1]=0
        flag[12]=1


def cube(ins):
    global flag
    ir1 = RegInBin.index(ins[10:13])
    ir2 = RegInBin.index(ins[13:16])
    finalv=RegList[ir2]
    finalv=finalv**3
    if (finalv< 65536):
        RegList[ir1]=finalv
        flag = [0]*16
    else:
        RegList[ir1]=0
        flag[12]=1

def push(ins):
    global flag
    ir1 = RegInBin.index(ins[13:16])
    element=RegList[ir1]

    stack.append(element)
    flag = [0]*16

def pushi(ins):
    global flag
    immediate = todeci(ins[9:16])
    stack.append(immediate)
    flag = [0]*16

def pop(ins):
    global flag
    ir1 = RegInBin.index(ins[13:16])
    if (len(stack)>0):
        RegList[ir1]=stack.pop()
    else:
        RegList[ir1]=0
        flag[11] = 1



def memorydump(instruct,i):
    global memory
    for j in range(i):
        print(instruct[j])

    for j in memory.values():
        ans = [str(i) for i in toBin(j, 16)]
        print("".join(ans))

    total = i+len(memory)

    for j in range(128-total):
        print("0000000000000000")


def print_me(lst):
    for i in lst:
        print(i,end="")
    print(" ", end = "")

def regDump(lineNum):
    global flag
    print_me(toBin(lineNum,7))
    print(" "*7, end = "")
    print_me(toBin(RegList[0],16))
    print_me(toBin(RegList[1],16))
    print_me(toBin(RegList[2],16))
    print_me(toBin(RegList[3],16))
    print_me(toBin(RegList[4],16))
    print_me(toBin(RegList[5],16))
    print_me(toBin(RegList[6],16))
    # print(flag)
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
    elif (opcode=="00100"):
        load(instructions[j])
    elif (opcode=="00101"):
        store(instructions[j])
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
        cmpr(instructions[j])
    elif (opcode=="01111"):
        flag = [0]*16
        regDump(j)
        j=uJmp(instructions[j])
        j+=1
        continue
    elif(opcode == "10000"):
        sqr(instructions[j])
    elif(opcode == "10001"):
        cube(instructions[j])
    elif(opcode == "10010"):
        push(instructions[j])
    elif(opcode == "10011"):
        pushi(instructions[j])
    elif(opcode == "10100"):
        pop(instructions[j])
    elif (opcode=="10000"):
        addf(instructions[j])
    elif (opcode=="10001"):
        subf(instructions[j])
    elif (opcode=="10010"):
        movf(instructions[j])
    elif (opcode=="11100"):
        if (flag[-3]==1):
            flag = [0]*16
            regDump(j)
            j=uJmp(instructions[j])
            j+=1
            continue
        flag = [0]*16
    elif (opcode=="11101"):
        if (flag[-2]==1):
            flag = [0]*16
            regDump(j)
            j=uJmp(instructions[j])
            j+=1
            continue
        flag = [0]*16
    elif (opcode=="11111"):
        if (flag[-1]==1):
            flag = [0]*16
            regDump(j)
            j=uJmp(instructions[j])
            j+=1
            continue
        flag = [0]*16

    regDump(j)
    j+=1

regDump(j)

memorydump(instructions,i)
