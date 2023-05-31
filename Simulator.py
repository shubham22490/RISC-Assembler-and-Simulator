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


instructions = dict()
i = 0;
for line in sys.stdin:
    line = line.strip()
    if(line):
        instructions[i] = line
        i += 1

print(instructions)
