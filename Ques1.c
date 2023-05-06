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
//function to handle typeE commands
void typeE(int opcode[],int binaryvalue[])
{
    for (int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

	for(int i=5; i<9; i++){
		ans[i]=0;
	}

    for(int i=0;i<7;i++)
    {
        ans[i+9]=binaryvalue[i];
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

//Function to convert memory to binary
void memBin(int bin[], char mem[]){

	int num = mem[1] - '0';
	toBin(bin, num, 7);
}


//Function to caluclate the line number at which label is present
int check(char arr[])
{
    FILE *file1r;
    file1r = fopen("Assembly.txt", "r");
    int lin_check=0,flag=0;
    int len=strlen(arr);
    while(flag==0)
    {
        char dataline[100];
		fgets(dataline, 100, file1r);
        lin_check++;
        int set=0;
        for(int i=0;i<len;i++)
        {
            set=0;
            if (dataline[i]==arr[i])
            {
                continue;
            }
            else
            {
                set=1;
                break;
            }
        }
        if (set==0)
        {
            flag=1;
        
        }

    }
    return lin_check;
    
}

int main(){
	 // To store the data of each dataline.

	FILE *filer, *filew;
	filer = fopen("Assembly.txt", "r");
	filew = fopen("Ans.txt", "w");
    int count=0,count_list[100][2],count_list_index=0;

	while(1){

		char dataline[100];
		fgets(dataline, 100, filer);
        
		
        count++;
        int i = 0, j = 0, k = 0,flag=0,index;
        for(index=0;index<count_list_index;index++)
        {
            if (count==count_list[index][0])
            {
                flag=1;
                break;
            }
        }
        if (flag==1)
        {
            i+=count_list[index][1];
            i++;
            
        }
		if (dataline){
			
			char opcode[4];
			

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


            else if ( !strcmp(opcode, "ld") || !strcmp(opcode, "st") ){
				char reg1[2], mem[2];
				int bin1[3], bin2[3];
				int opcodeBin[5];

				if (!strcmp(opcode, "ld")) toBin(opcodeBin, 4, 5);
				else if (!strcmp(opcode, "st")) toBin(opcodeBin, 5, 5);
				


				while(dataline[i] == ' ') i++;
				for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];


				while(dataline[i] == ' ') i++;
				for(int x = 0; x < 2; x++,i++) mem[x] = dataline[i];

				regBin(bin1, reg1);
				memBin(bin2, mem);

				typed(opcodeBin, bin1, bin2);

				for(int x = 0; x < 16; x++){
					fprintf(filew,"%d", ans[x]);
				}

				fprintf(filew,"\n");
				
			}

			else if ((!strcmp(opcode, "hlt\n")) || ((!strcmp(opcode, "hlt\0")))){
				
				int opcodeBin[5];

				toBin(opcodeBin, 26, 5);

				typeF(opcodeBin);

				for(int x = 0; x < 16; x++){
					fprintf(filew, "%d", ans[x]);
				}
				

				fprintf(filew,"\n");

			}


            else if (!strcmp(opcode, "jmp") || !strcmp(opcode, "jlt") || !strcmp(opcode, "jgt") || !strcmp(opcode ,"je"))
			{
				int opcodeBin[5];
				if (!strcmp(opcode, "jmp")) toBin(opcodeBin,15,5);
				else if (!strcmp(opcode, "jlt")) toBin(opcodeBin,28,5);
				else if (!strcmp(opcode, "jgt")) toBin(opcodeBin,29,5);
				else if (!strcmp(opcode, "je")) toBin(opcodeBin,31,5);
                i++;
                char label[50];
                int x=0;
                while(dataline[i] == ' ') i++;
                //for(;dataline[i] != ' '; i++) label[x++] = dataline[i];
                for(int y=i;(dataline[y]!='\n');y++)
                {
                    label[x]=dataline[y];
                    x++;

                }
                label[x]='\0';
                int line_num=check(label);
                count_list[count_list_index][0]=line_num;
                count_list[count_list_index][1]=x;
                count_list_index++;
                int mem1[7];
                toBin(mem1,line_num,7);
                typeE(opcodeBin,mem1);
                for(int x = 0; x < 16; x++){
					fprintf(filew, "%d", ans[x]);
				}
				

				fprintf(filew,"\n");



				


			}
		}
        if(feof(filer)) break;
	}

	
    return 0;
}
