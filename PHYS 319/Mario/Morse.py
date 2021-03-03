import os

morse = {"a": [1, 1, 2],
         "b": [2, 1, 1, 1, 1, 1, 1],
         "c": [2, 1, 1, 1, 2, 1, 1],
         "d": [2, 1, 1, 1, 1],
         "e": [1],
         "f": [1, 1, 1, 1, 2, 1, 1],
         "g": [2, 1, 2, 1, 1],
         "h": [1, 1, 1, 1, 1, 1, 1],
         "i": [1, 1, 1],
         "j": [1, 1, 2, 1, 2, 1, 2],
         "k": [2, 1, 1, 1, 2],
         "l": [1, 1, 2, 1, 1, 1, 1],
         "m": [2, 1, 2],
         "n": [2, 1, 1],
         "o": [2, 1, 2, 1, 2],
         "p": [1, 1, 2, 1, 2, 1, 1],
         "q": [2, 1, 2, 1, 1, 1, 2],
         "r": [1, 1, 2, 1, 1],
         "s": [1, 1, 1, 1, 1],
         "t": [2],
         "u": [1, 1, 1, 1, 2],
         "v": [1, 1, 1, 1, 1, 1, 2],
         "w": [1, 1, 2, 1, 2],
         "x": [2, 1, 1, 1, 1, 1, 2],
         "y": [2, 1, 1, 1, 2, 1, 2],
         "z": [2, 1, 2, 1, 1, 1, 1]}

message = raw_input("What message should be broadcast? ")
print message
message = message.lower()
messagemore = []
for indx in range(len(message)):
    if message[indx] == " ":
        messagemore[-1] = 7
    else:
        for indx2 in range(len(morse[message[indx]])):
            messagemore.append(morse[message[indx]][indx2])
        messagemore.append(3)
messagemore[-1] = 7

f = open("Morse.c", "w+")
f.write("#include \"msp430.h\"\n")
f.write("\n")
f.write("#define UNIT 5000\n")
f.write("\n")
f.write("void wait(unsigned int wait)\n")
f.write("{\n")
f.write("\tvolatile unsigned int count = UNIT;\n")
f.write("\tfor (wait; wait>0; wait--)\n")
f.write("\t{\n")
f.write("\t\tcount = UNIT;\n")
f.write("\t\twhile (count>0)\n")
f.write("\t\t\tcount--;\n")
f.write("\t}\n")
f.write("}\n")
f.write("\n")
f.write("void main(void)\n")
f.write("{\n")
f.write("\tWDTCTL = WDTPW + WDTHOLD;\n")
f.write("\n")
f.write("\tP1DIR |= BIT2;\n")
f.write("\tP1SEL |= BIT2;\n")
f.write("\n")
f.write("\tCCR0 = 2500-1;\n")
f.write("\tCCTL1 = OUTMOD_7;\n")
f.write("\tTACTL = TASSEL_2 + MC_1;\n")
f.write("\tCCR1 = 0;\n")
f.write("\n")
f.write("\tvolatile unsigned int message[{:d}] = ".format(len(messagemore)))
f.write("{")
f.write("{:d}".format(messagemore[0]))
for indx in range(1, len(messagemore)):
    f.write(", {:d}".format(messagemore[indx]))
f.write("};\n")
f.write("\tvolatile unsigned int indx = 0;\n")
f.write("\n")
f.write("\tfor(unsigned int i = {:d}; i>0; i--)".format(len(messagemore)//2))
f.write("\t{\n")
f.write("\t\tCCR0 = 2500-1;\n")
f.write("\t\tCCTL1 = OUTMOD_7;\n")
f.write("\t\tCCR1 = 1500;\n")
f.write("\t\tTACTL = TASSEL_2 + MC_1;\n")
f.write("\t\twait(message[indx]);\n")
f.write("\t\tindx++;\n")
f.write("\n")
f.write("\t\tCCR0 = 1-1;\n")
f.write("\t\tCCTL1 = OUTMOD_7;\n")
f.write("\t\tTACTL = TASSEL_2 + MC_1;\n")
f.write("\t\tCCR1 = 0;\n")
f.write("\t\twait(message[indx]);\n")
f.write("\t\tindx++;\n")
f.write("\t}\n")
f.write("\n")
f.write("\tCCR0 = 1-1;\n")
f.write("\tCCTL1 = OUTMOD_7;\n")
f.write("\tTACTL = TASSEL_2 + MC_1;\n")
f.write("\tCCR1 = 0;\n")
f.write("\t_BIS_SR(LPM0_bits);\n")
f.write("}\n")
f.close()

os.system("cd C:\\Users\\ryank\\Desktop\\Personal Files\\PHYS319\\C\\Mario")
os.system("make")
