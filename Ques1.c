#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char error_list[131][100];
//defining a new data type node
typedef struct node
{
    char var[50];
    int num;
    struct node* next;
}node;
//defining heads of two linked lists one to store variables second to store labels
node* headVar = NULL;
node* headLabel = NULL;
//function to create a linked list as well as add new members to the existing ones
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
//funxtion to assign memory locations to variables
void initvars(node* head, int num){
    if(head != NULL){
        node *temp = head;
        while(temp){
            temp->num = num++;
            temp = temp->next;
        }
    }
}
//checks if the variables are previously defined or not or if the labels are initialised or not
int checkMember(node** head, char variable[]){
    
    int flag = 0;
    int ans = -1;
    node* ptr;
    ptr = (node *)malloc(sizeof(node));
    if(*head != NULL){
        node* ptr = *head;
        while(ptr){
            if(!strcmp(ptr->var, variable)){
                ans = ptr->num;
                flag = 1;
                break;
            }
            ptr = ptr->next;
        }
    }
    if(flag) return ans;
    return -1;
}
//for debugging purpose(check all members of linked list)
void printLinked(node* head){
    if(head != NULL){
        node *temp = head;

        while(temp){
            //printf("%s %d\n", temp->var, temp->num);
            temp = temp->next;
        }
        //printf("\n");
    }
}

//final answer storing list
static int ans[16]; // Storing ans of each data line
//to check whether error exists or not (=1 means error exists)
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
//if error exists this will close file reading and write the error in a new file 
void raiseError(char error[], int lineNum){

    
    if(lineNum) strcpy(error_list[lineNum], error);
    else strcpy(error_list[130], error);
    
    errorFlag = 1;
}

//stores all the initialised variables and intialised labels
void initial(){

    FILE *filer;
    filer = fopen("Assembly.txt", "r");
    int count = 0, lineCount = 0;
	//count only counts those lines which have instruction codes 
	//lineCount counts all instruction lines as well as blanks

    int i, j;
    int flag = 0;

    while(1){
        i = 0, j = 0;
        char dataline[100];
        fgets(dataline, 100, filer);
        if(feof(filer)) break;
	//checks if file end has been reached or not
        lineCount++;


        if(strcmp(dataline, "\n"))
		//checks if line is empty or not
	{
            char first_word[50];
            while(dataline[i] == ' ') i++;
			for(;dataline[i] != ' ' && dataline[i] != '\n' && dataline[i] != '\0'; i++) first_word[j++] = dataline[i];
            first_word[j] = '\0';


            if (strlen(first_word) == 3){
                if(!strcmp(first_word, "var") && !flag){
                    char second[50];
                    j = 0;
                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                    for(;dataline[i] != '\n'; i++) second[j++] = dataline[i];
                    second[j] = '\0';
                    create(&headVar, second, 0);
			//adds initialised variables to the linked list
                    continue;
                }
            }
            flag = 1;
            char * ch;
            ch = strchr(dataline,':');
		//jumps to the position where ":" exists if it doesnt exist, will return NULL

            if(ch == NULL){
                if(!strcmp(first_word, "var")){
                    raiseError("Variables not declared at the beginning.", lineCount);
                    
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

//checks if there is any type of typing error in register declaration
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
    int hlt_error=0; int hlt_error2=0; int hlthlt=0;

    //printLinked(headVar);


    
        FILE *filer, *filew;
        filer = fopen("Assembly.txt", "r");
        filew = fopen("Ans.txt", "w");
	char dataline[100];
	int hltFlag = 0;


        static int lineCount;

        while(1){
	    //code runs untill the break statement.       


            if(hltFlag == 0){
		    fgets(dataline, 100, filer);
		    // printf("%s", dataline);
		    if(feof(filer)) break;
		    lineCount++;
	    }
	    htlFlag = 0;

            int i = 0, j = 0, k = 0;

            if (strcmp(dataline, "\n")){

                char * ch;
                ch = strchr(dataline,':');

                if(ch) {
                    i = ch-dataline+1;
                }


                char opcode[4];

                while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                for(;dataline[i] != ' ' && j != 3; i++) opcode[j++] = dataline[i];
                ch=strchr(dataline,'$');

                opcode[j] = '\0';
                if(!strcmp(opcode, "var")) continue;
                
                //To handle the bin code of TypeA Commands
                if (!strcmp(opcode, "add") || !strcmp(opcode, "sub") || !strcmp(opcode, "mul") || !strcmp(opcode, "xor") || !strcmp(opcode, "or") || !strcmp(opcode, "and")){
                    char reg1[2], reg2[2], reg3[2];
                    int bin1[3], bin2[3], bin3[3];
                    int opcodeBin[5];
			//opcodebin stores the bits needed to represent opcode

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
                            
                            raiseError("Either typo in register(s) or register(s) not defined!", lineCount);
                    }

                    if(dataline[i] != '\n'){
			                 //if last element in the string is not "\n" then there may be possible extra unnecessary elements in the string
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

			//atoi takes $number and extracts out the number from it
                    int value = atoi(ch + 1);
                    if(value >=0 && value < 128){
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
                            
                            raiseError("Either typo in register(s) or register(s) not defined!", lineCount);
                        }

                        if(dataline[i] != '\n'){
                            
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

                        
                        raiseError("Illegal immediate value!", lineCount);
			    //if immediate value is not withtin the given range this error will be raised

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
			//isflag determines if it has been setup or not
                    int isFlag = 0;
			//if FLAGS is initialised register code will be 111.
                    if(strstr(dataline+i, "FLAGS")) {

                            bin2[0] = 1;
                            bin2[1] = 1;
                            bin2[2] = 1;
                            isFlag = 1;
                            i = i+5;

                    }
                    if(!isFlag) for(int x = 0; x < 2; x++,i++) reg2[x] = dataline[i];


        if(isFlag && strcmp(opcode, "mov")) 
		    //checks if there are any other operations used except for "mov" or if flag has been initialised or not
		    {
                        fclose(filew);
                        raiseError("Invalid use of FLAGS register.", lineCount);
                    }

                    if (typo_reg(reg1)==1 || (typo_reg(reg2)==1)){
                        if(isFlag) goto next;
                       
                        raiseError("Either typo in register(s) or register(s) not defined!", lineCount);
                    }

                    if(dataline[i] != '\n'){
                            
                            raiseError("Unnecessary elements in the instruction!", lineCount);
                    }

		//jumps to next if there are no prior errors related to flags
                    next:
                    regBin(bin1, reg1);
                    if(!isFlag) regBin(bin2, reg2);

                    typeC(opcodeBin, bin1, bin2);


                    for(int x = 0; x < 16; x++){
                        fprintf(filew,"%d", ans[x]);
                    }

                    fprintf(filew,"\n");

                }

                else if (!strcmp(opcode, "hlt")) {
                    hlt_error2=1;
                    int opcodeBin[5];

                    toBin(opcodeBin, 26, 5);

                    typeF(opcodeBin);

                    for(int x = 0; x < 16; x++){
                        fprintf(filew, "%d", ans[x]);
                    }

                    fprintf(filew,"\n");

                    while(1){
                        
                        fgets(dataline, 100, filer);
			linCount++;
                        if(feof(filer)) break;
                        if(!strcmp(dataline, "\n")) continue;
			hltFlag = 1;
                        hlt_error = 1;
                        hlthlt=lineCount;
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
			//line_num to check the line of label and valvar to check for variable line
                    int line_num = checkMember(&headLabel, label);
                    int valVar = checkMember(&headVar, label);
                    // printf("%d %d", line_num, valVar);
                    if(line_num == -1 && valVar == -1){
                        
                        raiseError("Using undefined labels!", lineCount);
                    }

                    else if (line_num == -1 && valVar != -1){
                        
                        raiseError("Usage of Varible as Label!", lineCount);
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

                    int valVar = checkMember(&headVar, variable);
                    int valLabel = checkMember(&headLabel, variable);
                    if (valVar == -1 && valLabel == -1){
                        
                        raiseError("Usage of Invalid Variable!", lineCount);
                    }

                    else if (valVar == -1 && valLabel != -1){
                        
                        raiseError("Usage of Label as Variable!", lineCount);
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
                   
                   raiseError("Typo in instruction!", lineCount); 
                }
            }
        }


        if(hlt_error2==0){
            
            raiseError("Halt instruction is missing!", 0);
        }

        else if (hlt_error){
            
            raiseError("Halt instruction is not last!", hlthlt);
        }
    

    fclose(filew);
    if(errorFlag==1){
        FILE *filew;
        filew = fopen("Ans.txt", "w");
        for(int i=0; i<=130; i++){
            if(strcmp(error_list[i], "")){

                if(i==130) fprintf(filew, "Error: %s\n", error_list[i]);
                else fprintf(filew, "Error in line %d: %s\n", i, error_list[i]);

            }
        }
        fclose(filew);
    }

    return 0;
   
}
