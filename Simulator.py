import sys

pc = 0
RegInBin = ['000', '001', '010', '011', '100', '101', '110']
RegList = [0]*7

flag = [0]*16


def add(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    val = RegList[ir2]+RegList[ir3]

    if(val >= 0 and val < 65536):
        RegList[ir1] = val
    else:
        RegList[ir1] = 0
        flag = [0]*16
        flag[12] = 1


def sub(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    val = RegList[ir2] - RegList[ir3]

    if(val >= 0 and val < 65536):
        RegList[ir1] = val
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
    else:
        RegList[ir1] = 0
        flag = [0]*16
        flag[12] = 1


def xor(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    RegList[ir1] = RegList[ir2] ^ RegList[ir3]


def Or(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

    RegList[ir1] = RegList[ir2] | RegList[ir3]




def And(inst):
    ir1 = RegInBin.index(inst[7:10])
    ir2 = RegInBin.index(inst[10:13])
    ir3 = RegInBin.index(inst[13:16])

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

def mov(ins):
    ir1 = RegInBin.index(ins[10:13])
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
while(j<=i and instructions[j][0:5]!="11010"):
    if (instructions[j][0:4]=="00000"):
        add(instructions[j])
    elif (instructions[j][0:4]=="00001"):
        sub(instructions[j])
    elif (instructions[j][0:4]=="00110"):
        mul(instructions[j])
    elif (instructions[j][0:4]=="01010"):
        xor(instructions[j])
    elif (instructions[j][0:4]=="01011"):
        Or(instructions[j])
    elif (instructions[j][0:4]=="01100"):
        And(instructions[j])
    elif (instructions[j][0:4]=="00011"):
        mov(instructions[j])
    elif (instructions[j][0:4]=="00111"):
        div(instructions[j])
    elif (instructions[j][0:4]=="01101"):
        invert(instructions[j])
    elif (instructions[j][0:4]=="01110"):
        cmp(instructions[j])
    elif (instructions[j][0:4]=="01111"):
        j=uJmp(instructions[j])
    elif (instructions[j][0:4]=="11100"):
        j=ltJmp(instructions[j])
    elif (instructions[j][0:4]=="11101"):
        j=gtJmp(instructions[j])
    elif (instructions[j][0:4]=="11111"):
        j=eJmp(instructions[j])
    j+=1
    

