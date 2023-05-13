#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct node
{
    char var[100];
    int num;
    struct node* next;
}node;

node* headVar = NULL;
node* headLabel = NULL;

void create(node ** head, char varname[], int num)
{
    node* temp;
    temp = (node*)malloc(sizeof(node));

    strcpy(temp->var, varname);
    temp->num = num;
    temp->next=NULL;
    // printf("%s\n", temp->var);

    if (*head == NULL){
        *head = temp;
    }

    else{
        node* ptr = *head;
        while (ptr->next){
            ptr = ptr->next;
        }

        ptr->next = temp;
    }
}

void initvars(node* head, int num){
    node *temp = head;
    while(temp){
        temp->num = num++;
        temp = temp->next;
    }
}

int checkMember(node* head, char var[]){
    node* ptr = head;
    int flag = 0;
    while(ptr){
        if(!strcmp(ptr->var, var)){
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }
    if(flag) return ptr->num;
    return -1;
}

void printLinked(node* head){
    node *temp = head;

    while(temp){
        printf("%s %d\n", temp->var, temp->num);
        temp = temp->next;
    }
    printf("\n");
}


static int ans[16]; // Storing ans of each data line

static int errorFlag;


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

//function to handle typeb commands
void  typeb(int opcode[], int reg1[], int binary[]){
    for(int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

    ans[5]=0;

    int j = 6;
    for(int i = 0; i < 3; i++){
        ans[j+i] = reg1[i];
        }

    j+=3;


    for(int i=0;i<7;i++){
        ans[i+j]=binary[i];
    }
    j+=7;

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


//function to handle typeD commands
void typeD(int opcode[], int reg[], int binary[]){
    for(int i = 0; i < 5; i++) ans[i] = opcode[i];
    ans[5] = 0;
    for(int i = 0; i < 3; i++) ans[i+6] = reg[i];
    for(int i = 0; i < 7; i++) ans[i+9] = binary[i];
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

void raiseError(char error[], int lineNum){
    FILE *filew;
    filew = fopen("Ans.txt", "w");
    if (lineNum) fprintf(filew, "Error in line %d: %s", lineNum, error);
    else fprintf(filew, "Error: %s", error);
    fclose(filew);
    errorFlag = 1;
}


void initial(){

    FILE *filer;
    filer = fopen("Assembly.txt", "r");
    int count = 0, lineCount = 0;

    int i, j;
    int flag = 0;

    while(1){
        i = 0, j = 0;
        char dataline[100];
        fgets(dataline, 100, filer);
        if(feof(filer)) break;
        lineCount++;


        if(strcmp(dataline, "\n")){
            char first_word[50];
            while(dataline[i] == ' ') i++;
			for(;dataline[i] != ' '; i++) first_word[j++] = dataline[i];
            first_word[j] = '\0';

            if(!strcmp(first_word, "var") && !flag){
                char second[50];
                j = 0;
                while(dataline[i] == ' ') i++;
                for(;dataline[i] != '\n'; i++) second[j++] = dataline[i];
                second[j] = '\0';
                create(&headVar, second, 0);
                continue;
            }
            flag = 1;
            char * ch;
            ch = strchr(dataline,':');

            if(ch == NULL){
                if(!strcmp(first_word, "var")){
                    raiseError("Variables not declared at the beginning.", lineCount);
                    break;
                }
            }

            else{
                j = 0, i=0;
                while(dataline[i] == ' ') i++;
                for(; dataline[i] != ':'; i++) first_word[j++] = dataline[i];
                first_word[j] = '\0';
                create(&headLabel, first_word, count);
            }

            count ++;

        }
    }

    initvars(headVar, count);
    fclose(filer);
}


int typo_reg(char reg[]){   // for checking typo error in registers.
    if (reg[0]!='R' || reg[1]=='7' || reg[1]=='8'|| reg[1]=='9' ){
        return 1;
    }

    else{
        return 0;
    }
}


int main(){
	 // To store the data of each dataline.
 
    initial(); //Checks and stores all the labels and variables.

    int hlt_error=0; int hlt_error2=0;

    if(!errorFlag){
        FILE *filer, *filew;
        filer = fopen("Assembly.txt", "r");
        filew = fopen("Ans.txt", "w");


        static int lineCount;
        while(!errorFlag){

            char dataline[100];
            fgets(dataline, 100, filer);
            if(feof(filer)) break;
            lineCount++;

            int i = 0, j = 0, k = 0;

            if (strcmp(dataline, "\n")){

                char * ch;
                ch=strchr(dataline,':');

                if(ch) i = ch-dataline+1;


                char opcode[4];

                while(dataline[i] == ' ') i++;
                for(;dataline[i] != ' '; i++) opcode[j++] = dataline[i];

                ch=strchr(dataline,'$');

                opcode[j] = '\0';
                if(!strcmp(opcode, "var")) continue;
                
                //To handle the bin code of TypeA Commands
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

                    if (typo_reg(reg1)==1 || typo_reg(reg2)==1 || typo_reg(reg3)==1 ){
                            fclose(filew);
                            raiseError("Typo in register!", lineCount);
                    }

                    if(dataline[i] != '\n'){
                      fclose(filew);
                      raiseError("Unnecessary elements in the instruction!", lineCount);
                    }

                    regBin(bin1, reg1);
                    regBin(bin2, reg2);
                    regBin(bin3, reg3);

                    typeA(opcodeBin, bin1, bin2, bin3);

                    for(int x = 0; x < 16; x++){
                        fprintf(filew,"%d", ans[x]);
                    }

                    fprintf(filew,"\n");

                }

                else if ((!strcmp(opcode, "mov") && ch != NULL) || !strcmp(opcode,"rs")|| !strcmp(opcode,"ls") ){


                    int value = atoi(ch + 1);
                    if(value>0 && value < 128){
                        int bin2[7];
                        toBin(bin2,value,7);
                        char reg1[2];
                        int bin1[3];
                        int opcodeBin[5];

                        if (!strcmp(opcode, "mov")) toBin(opcodeBin, 2, 5);
                        else if (!strcmp(opcode, "rs")) toBin(opcodeBin, 8, 5);
                        else if (!strcmp(opcode, "ls")) toBin(opcodeBin, 9, 5);

                        while(dataline[i] == ' ') i++;
                        for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];

                        i = ch-dataline+1;
                        for(; dataline[i] != ' ' && dataline[i]!='\n' && dataline[i] != '\0'; i++) continue;

                        if (typo_reg(reg1)==1){
                            fclose(filew);
                            raiseError("Typo in register!", lineCount);
                        }

                        if(dataline[i] != '\n'){
                            fclose(filew);
                            raiseError("Unnecessary elements in the instruction!", lineCount);
                        }

                        regBin(bin1, reg1);

                        typeb(opcodeBin, bin1, bin2);


                        for(int x = 0; x < 16; x++){
                            fprintf(filew,"%d", ans[x]);
                        }

                        fprintf(filew,"\n");
                    }

                    else{

                        fclose(filew);
                        raiseError("Illegal immediate value!", lineCount);

                    }

                }


                else if ( (!strcmp(opcode, "mov") && ch == NULL) || !strcmp(opcode, "div") || !strcmp(opcode, "not") || !strcmp(opcode, "cmp") ){



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

                    if (typo_reg(reg1)==1 || typo_reg(reg2)==1){
                        fclose(filew);
                        raiseError("Typo in register!", lineCount);
                    }

                    if(dataline[i] != '\n'){
                            fclose(filew);
                            raiseError("Unnecessary elements in the instruction!", lineCount);
                    }
                    

                    regBin(bin1, reg1);
                    regBin(bin2, reg2);

                    typeC(opcodeBin, bin1, bin2);


                    for(int x = 0; x < 16; x++){
                        fprintf(filew,"%d", ans[x]);
                    }

                    fprintf(filew,"\n");

                }

                else if (!strcmp(opcode, "hlt\n")) {
                    hlt_error2=1;
                    int opcodeBin[5];

                    toBin(opcodeBin, 26, 5);

                    typeF(opcodeBin);

                    for(int x = 0; x < 16; x++){
                        fprintf(filew, "%d", ans[x]);
                    }

                    fprintf(filew,"\n");

                    while(!errorFlag){
                        char dataline[100];
                        fgets(dataline, 100, filer);
                        if(feof(filer)) break;
                        if(!strcmp(dataline, "\n")) continue;
                        hlt_error = 1;
                        errorFlag = 1;
                        break;
                    }

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

                    int line_num = checkMember(headLabel, label);
                    if(line_num == -1){
                        fclose(filew);
                        raiseError("Using undefined labels!", lineCount);
                    }

                    int mem1[7];
                    toBin(mem1,line_num,7);
                    typeE(opcodeBin,mem1);
                    for(int x = 0; x < 16; x++){
                        fprintf(filew, "%d", ans[x]);
                    }


                    fprintf(filew,"\n");

                }

                else if(!strcmp(opcode, "ld") || !strcmp(opcode, "st")){
                    char reg1[2];
                    int bin1[3];

                    int opcodeBin[5];
                    if(!strcmp(opcode, "ld")) toBin(opcodeBin, 4, 5);
                    else if(!strcmp(opcode, "st")) toBin(opcodeBin, 5, 5);

                    while(dataline[i] == ' ') i++;
                    for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];
                    regBin(bin1, reg1);

                    char variable[50];
                    int x=0;
                    while(dataline[i] == ' ') i++;
                    //for(;dataline[i] != ' '; i++) variable[x++] = dataline[i];

                    for(int y=i;(dataline[y]!='\n');y++) variable[x++]=dataline[y];
                    variable[x]='\0';

                    int valVar = checkMember(headVar, variable);
                    if (valVar == -1){
                        fclose(filew);
                        raiseError("Usage of Invalid Variable!", lineCount);
                    }
                    int mem[7];
                    toBin(mem, valVar, 7);

                    typeD(opcodeBin,bin1, mem);
                    for(int x = 0; x < 16; x++){
                        fprintf(filew, "%d", ans[x]);
                    }


                    fprintf(filew,"\n");


                }

                else{
                   fclose(filew);
                   raiseError("Typo in instruction!", lineCount); 
                }
            }
        }


        if(hlt_error2==0 && errorFlag==0){
            fclose(filew);
            raiseError("Halt instruction is missing!", 0);
        }

        else if (hlt_error){
            fclose(filew);
            raiseError("Halt instruction is not last!", lineCount);
        }
    }

    return 0;
}