#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int ans[16]; // Storing ans of


//Function to handle the typeA commands.
void typeA (int opcode[], int reg1[], int reg2[], int reg3[]){
    for(int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

    ans[5] = 0; // unused bit
	ans[6] = 0; // unused bit

    int j = 7;

    for(int i = 0; i < 3; i++){
        ans[j+i] = reg1[i];
    }
    j += 3;

	for(int i = 0; i < 3; i++){
        ans[j+i] = reg2[i];
    }
    j += 3;

	for(int i = 0; i < 3; i++){
        ans[j+i] = reg3[i];
    }
    j += 3;

}


void  typeb(int opcode[], int reg1[], int a){
    for(int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

    ans[5]=0;

    int j = 6;
    for(int i = 0; i < 3; i++){
        ans[j+i] = reg1[i];
        }

    int brr[7];

    toBin(brr,a,7);

    for(int i=9;i<16;i++){
        ans[i]=brr[i-9];
    }

}

//function to handle typeC commands
void typeC(int opcode[], int reg1[], int reg2[]){
	for (int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

	ans[5] = 0; ans[6] = 0; ans[7] = 0; ans[8] = 0; ans[9] = 0;

	int j = 10;

    for (int i = 0; i < 3; i++){
        ans[j+i] = reg1[i];
    }
    j += 3;

	for (int i = 0; i < 3; i++){
        ans[j+i] = reg2[i];
    }
    j += 3;

}



void  typed(int opcode[], int reg1[], int mem_addr[]){
    for(int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

    ans[5]=0;

    int j = 6;
    for(int i = 0; i < 3; i++){
        ans[j+i] = reg1[i];
        }

    j +=3; 

    for(int i=0;i<7;i++){
        ans[j+i]=mem_addr[i];
    }

}


//function to handle typeF commands
void typeF(int opcode[]){
	
	for (int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

	for(int i=5; i<16; i++){
		ans[i]=0;
	}
}


//Function to convert number to binary in specific number of bits.
int toBin(int var[], int n, int bits){
    for(int i = 0; i < bits; i++){
        var[i] = 0;
    }
    int j = bits-1;
    while(n > 0){
        var[j] =  (n % 2);
        n /= 2;
        j--;
        if (j < 0){
            return 0;
        }
    }

    return 1;
}


//Function to convert register to binary
void regBin(int bin[], char reg[]){

	int num = reg[1] - '0';
	toBin(bin, num, 3);
}


int main(){
	 // To store the data of each dataline.

	FILE *filer, *filew;
	filer = fopen("Assembly.txt", "r");
	filew = fopen("Ans.txt", "w");

	while(1){
		char dataline[100];
		fgets(dataline, 100, filer);
		if(feof(filer)) break;
		if (dataline){
			
			char opcode[4];
			int i = 0, j = 0, k = 0;

			while(dataline[i] == ' ') i++;
			for(;dataline[i] != ' '; i++) opcode[j++] = dataline[i];
			
			opcode[j] = '\0';
			
			if (!strcmp(opcode, "add") || !strcmp(opcode, "sub") || !strcmp(opcode, "mul") || !strcmp(opcode, "xor") || !strcmp(opcode, "or") || !strcmp(opcode, "and")){
				char reg1[2], reg2[2], reg3[2];
				int bin1[3], bin2[3], bin3[3];
				int opcodeBin[5];

				if (!strcmp(opcode, "add")) toBin(opcodeBin, 0, 5);
				else if (!strcmp(opcode, "sub")) toBin(opcodeBin, 1, 5);
				else if (!strcmp(opcode, "mul")) toBin(opcodeBin, 6, 5);
				else if (!strcmp(opcode, "xor")) toBin(opcodeBin, 10, 5);
				else if (!strcmp(opcode, "or")) toBin(opcodeBin, 11, 5);
				else if (!strcmp(opcode, "and")) toBin(opcodeBin, 12, 5);


				while(dataline[i] == ' ') i++;
				for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];


				while(dataline[i] == ' ') i++;
				for(int x = 0; x < 2; x++,i++) reg2[x] = dataline[i];

				while(dataline[i] == ' ') i++;
				for(int x = 0; x < 2; x++,i++) reg3[x] = dataline[i];

				regBin(bin1, reg1);
				regBin(bin2, reg2);
				regBin(bin3, reg3);

				typeA(opcodeBin, bin1, bin2, bin3);

				for(int x = 0; x < 16; x++){
					fprintf(filew,"%d", ans[x]);
				}

				fprintf(filew,"\n");
				
			}

            else if (!strcmp(opcode, "mov") || !strcmp(opcode, "div") || !strcmp(opcode, "not") || !strcmp(opcode, "cmp")){
				
  				char * ch;
  				ch=strchr(dataline,'$');
  				if (ch==NULL)
				{
				char reg1[2], reg2[2];
				int bin1[3], bin2[3];
				int opcodeBin[5];
				
				if (!strcmp(opcode, "mov")) toBin(opcodeBin, 3, 5);
				else if (!strcmp(opcode, "div")) toBin(opcodeBin, 7, 5);
				else if (!strcmp(opcode, "not")) toBin(opcodeBin, 13, 5);
				else if (!strcmp(opcode, "cmp")) toBin(opcodeBin, 14, 5);
				
				while(dataline[i] == ' ') i++;
				for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];
				

				while(dataline[i] == ' ') i++;
				for(int x = 0; x < 2; x++,i++) reg2[x] = dataline[i];
				
				

				regBin(bin1, reg1);
				regBin(bin2, reg2);

				typeC(opcodeBin, bin1, bin2);


				for(int x = 0; x < 16; x++){
					fprintf(filew,"%d", ans[x]);
				}
				
				fprintf(filew,"\n");
			}
			}

			else if (!strcmp(opcode, "hlt\n")){
				
				int opcodeBin[5];

				toBin(opcodeBin, 26, 5);

				typeF(opcodeBin);

				for(int x = 0; x < 16; x++){
					fprintf(filew, "%d", ans[x]);
				}
				

				fprintf(filew,"\n");

			}
		}
	}
	
    return 0;
}
