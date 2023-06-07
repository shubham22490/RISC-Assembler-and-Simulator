#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10
#define BUFFER_SIZE 256

static char error_list[131][100];

static int Ans[130][16];
//defining a new data type node
typedef struct node
{
    char var[100];
    int num;
    struct node* next;
}node;

//defining heads of two linked lists one to store variables second to store labels
node* headVar = NULL;
node* headAssembly = NULL;
node* headBin = NULL;
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
            printf("%s %d\n", temp->var, temp->num);
            temp = temp->next;
        }
        printf("\n");
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

//function to handle typeb command with floating point representation
void  typebf(int opcode[], int reg1[], int binary[]){
    for(int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

    int j = 5;
    for(int i = 0; i < 3; i++){
        ans[j+i] = reg1[i];
        }

    j+=3;

    for(int i=0;i<8;i++){
        ans[i+j]=binary[i];
    }
    j+=8;

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


    if(lineNum>=0) strcpy(error_list[lineNum], error);
    else strcpy(error_list[130], error);

    errorFlag = 1;
}

void ReadFile(){
    int count = 0;
    char** lines = malloc(INITIAL_CAPACITY * sizeof(char*));
    if (lines == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return;
    }

    size_t capacity = INITIAL_CAPACITY;
    size_t size = 0;

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        size_t lineLength = strlen(buffer);

        // Allocate memory for the line
        lines[size] = malloc((lineLength + 1) * sizeof(char));
        if (lines[size] == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            return;
        }

        // Copy the line to the array
        strcpy(lines[size], buffer);

        size++;

        // Resize the array if needed
        if (size >= capacity) {
            capacity *= 2;
            char** newLines = realloc(lines, capacity * sizeof(char*));
            if (newLines == NULL) {
                fprintf(stderr, "Memory reallocation error.\n");
                return;
            }
            lines = newLines;
        }
    }

    for (size_t i = 0; i < size; i++) {
        // Process each line here
        if(strcmp(lines[i], "\n")) create(&headAssembly, lines[i], count++);
        free(lines[i]);
    }

}

//stores all the initialised variables and intialised labels
void initial(){
	//count only counts those lines which have instruction codes
	//count counts all instruction lines as well as blanks

    int i, j;
    int flag = 0;
    node* ptr = headAssembly;
    int count;
    int lineWithoutVar = 0;

    while(ptr){
        i = 0, j = 0;
        count = ptr -> num;
        char dataline[100];
        strcpy(dataline, ptr->var);
        ptr = ptr->next;


        char first_word[50];
        while(dataline[i] == ' ' || dataline[i] == '\t') i++;
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
                raiseError("Variables not declared at the beginning.", count);

            }
        }

        else{
            j = 0, i=0;
            while(dataline[i] == ' ' || dataline[i] == '\t') i++;
            for(; dataline[i] != ':'; i++) first_word[j++] = dataline[i];
            first_word[j] = '\0';
            create(&headLabel, first_word, lineWithoutVar);
        }
        lineWithoutVar++;

    }
        count = lineWithoutVar++;
        initvars(headVar, count);
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

int tobinfloating(float value, int final[], int n){
    int i = (int)value;
    float fr = value-i;
    int arri[5]={0}; int arrf[5]={0};

    
    toBin(arri, i, 5);
    int l=0;
    float h=fr;
    while(h>0 && l<5){
        h=h*2;
        arrf[l]=(int)h;
        h=h-(int)h;
        l++;
    }

    
    int con[10];
    int index=0;
    for(int g=0; g<5; g++, index++) con[index]=arri[g];
        
    con[index++]=-1;
    
    for(int g=0; g<l; g++, index++) con[index]=arrf[g];
    
    int flag=0; int count=0;
    int v=0;
    for(int x=0; x<index; x++){
        if (con[x]==-1) flag=1;
        if (con[x]==1 && flag==0){
            for(int j=x+1; j<index; j++){
                
                if (con[j]==-1) {
                    v=1;
                    break; 
                }
                count++;
            }
        }
        
        else if (flag==1){
            for(int f=x+1; f<index; f++){
                count--;
                if (con[f]==1) {
                    v=1;
                    break;
                }
            }
        }
        if (v==1) break;
    }
    //printf("\ncount:%d", count);
    
    int exp=3+count;
    int expo[3];
    //printf("\nexp:%d\n", exp);
    
    if (exp == 0) {expo[0] = 0; expo[1] = 0; expo[2] = 0;}
    else if (exp == 1) {expo[0] = 0; expo[1] = 0; expo[2] = 1;}
    else if (exp == 2) {expo[0] = 0; expo[1] = 1; expo[2] = 0;}
    else if (exp == 3 ) {expo[0] = 0; expo[1] = 1; expo[2] = 1;}
    else if (exp == -1 || exp==5) {expo[0] = 1; expo[1] = 0; expo[2] = 1;}
    else if (exp == -2 || exp==6) {expo[0] = 1; expo[1] = 1; expo[2] = 0;}
    else if (exp == -3 || exp==7) {expo[0] = 1; expo[1] = 1; expo[2] = 1;}
    else if (exp == -4 || exp==4) {expo[0] = 1; expo[1] = 0; expo[2] = 0;}
    
    int mantissa[5]; int m=0;
    int o;
    for(o=0; o< 10; o++){
        if (con[o]==1) break;
    }
    
    o++;
    
   
    for(int q=0; q<n; q++) final[q]=0;
    
    for(int t=0; t<3; t++){
        final[t]=expo[t];
    }
    for(; o<index ; o++){
        if(con[o]!=-1){
        mantissa[m]=con[o];
        m++;
    }
    }

    
    for(int w=3, y=0; w<8, y<m; w++, y++){
        final[w]=mantissa[y];
    }
    // for(int g=0; g<8; g++) printf("%d ", final[g]);
}


int main(){
	 // To store the data of each dataline.

    ReadFile();

    initial(); //Checks and stores all the labels and variables.

    int hlt_error=0; int hlt_error2=0; int hlthlt=0;
    int count = 0;

    char dataline[100];

    node* ptr = headAssembly;


    while(ptr){
    //code runs untill the break statement.

            strcpy(dataline, ptr->var);
            if(ptr) count = ptr->num;

            ptr = ptr->next;


        int i = 0, j = 0, k = 0;



                char * ch;
                ch = strchr(dataline,':');

                if(ch) {
                    i = ch-dataline+1;
                }


                char opcode[4];

                while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                for(;dataline[i] != ' ' && dataline[i] != '\n'  && j != 4; i++) opcode[j++] = dataline[i];
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


                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                    for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];


                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                    for(int x = 0; x < 2; x++,i++) reg2[x] = dataline[i];

                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                    for(int x = 0; x < 2; x++,i++) reg3[x] = dataline[i];
                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;

                    if (typo_reg(reg1)==1 || typo_reg(reg2)==1 || typo_reg(reg3)==1 ){

                            raiseError("Either typo in register(s) or register(s) not defined!", count);
                    }



                    else if(dataline[i] != '\n'){
			                 //if last element in the string is not "\n" then there may be possible extra unnecessary elements in the string
                        raiseError("Unnecessary elements in the instruction!", count);
                    }

                    regBin(bin1, reg1);
                    regBin(bin2, reg2);
                    regBin(bin3, reg3);

                    typeA(opcodeBin, bin1, bin2, bin3);


                    for(int x = 0; x < 16; x++){
                        Ans[count][x]=ans[x];
                    }



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

                        while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                        for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];

                        i = ch-dataline+1;
                        for(; dataline[i] != ' ' && dataline[i]!='\n' && dataline[i] != '\0'; i++) continue;

                        if (typo_reg(reg1)==1){

                            raiseError("Either typo in register(s) or register(s) not defined!", count);
                        }

                        else if(dataline[i] != '\n'){

                            raiseError("Unnecessary elements in the instruction!", count);
                        }

                        regBin(bin1, reg1);

                        typeb(opcodeBin, bin1, bin2);


                        for(int x = 0; x < 16; x++){
                            Ans[count][x]=ans[x];
                        }


                    }

                    else{


                        raiseError("Illegal immediate value!", count);
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

                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                    for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];

                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
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

                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;


                    if(isFlag && strcmp(opcode, "mov"))
		    //checks if there are any other operations used except for "mov" or if flag has been initialised or not
		    {
                        raiseError("Invalid use of FLAGS register.", count);
                    }

                    if (typo_reg(reg1)==1 || (typo_reg(reg2)==1)){
                        if(isFlag) goto next;

                        raiseError("Either typo in register(s) or register(s) not defined!", count);
                    }

                    else if(dataline[i] != '\n'){

                            raiseError("Unnecessary elements in the instruction!", count);
                    }

		//jumps to next if there are no prior errors related to flags
                    next:
                    regBin(bin1, reg1);
                    if(!isFlag) regBin(bin2, reg2);

                    typeC(opcodeBin, bin1, bin2);


                    for(int x = 0; x < 16; x++){
                        Ans[count][x]=ans[x];
                    }



                }

                else if (!strcmp(opcode, "hlt")) {
                    hlt_error2=1;
                    int opcodeBin[5];

                    toBin(opcodeBin, 26, 5);

                    typeF(opcodeBin);

                    for(int x = 0; x < 16; x++){
                        Ans[count][x]=ans[x];
                    }

                    if(ptr){
                        hlt_error = 1;
                        hlthlt = count;
                        errorFlag = 1;
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
                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                    //for(;dataline[i] != ' '; i++) label[x++] = dataline[i];
                    for(int y=i;(dataline[y]!='\n' && dataline[y]!=' ' && dataline[y] != '\t');y++)
                    {
                        label[x]=dataline[y];
                        x++;

                    }
                    label[x]='\0';
                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
			//line_num to check the line of label and valvar to check for variable line
                    int line_num = checkMember(&headLabel, label);
                    int valVar = checkMember(&headVar, label);
                    // printf("%d %d", line_num, valVar);
                    if(line_num == -1 && valVar == -1){

                        raiseError("Using undefined labels!", count);
                    }

                    else if (line_num == -1 && valVar != -1){

                        raiseError("Usage of Varible as Label!", count);
                    }


                    int mem1[7];
                    toBin(mem1,line_num,7);
                    typeE(opcodeBin,mem1);

                    for(int x = 0; x < 16; x++){
                        Ans[count][x]=ans[x];
                    }




                }

                else if(!strcmp(opcode, "ld") || !strcmp(opcode, "st")){
                    char reg1[2];
                    int bin1[3];

                    int opcodeBin[5];
                    if(!strcmp(opcode, "ld")) toBin(opcodeBin, 4, 5);
                    else if(!strcmp(opcode, "st")) toBin(opcodeBin, 5, 5);

                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                    for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];
                    regBin(bin1, reg1);

                    char variable[50];
                    int x=0;
                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;
                    //for(;dataline[i] != ' '; i++) variable[x++] = dataline[i];

                    for(int y=i;(dataline[y]!='\n' && dataline[y]!=' ' && dataline[y] != '\t');y++) variable[x++]=dataline[y];
                    variable[x]='\0';
                    while(dataline[i] == ' ' || dataline[i] == '\t') i++;

                    int valVar = checkMember(&headVar, variable);
                    int valLabel = checkMember(&headLabel, variable);
                    if (valVar == -1 && valLabel == -1){

                        raiseError("Usage of Invalid Variable!", count);
                    }

                    else if (valVar == -1 && valLabel != -1){

                        raiseError("Usage of Label as Variable!", count);
                    }

                    else if (typo_reg(reg1)==1){

                            raiseError("Either typo in register(s) or register(s) not defined!", count);
                        }



                    int mem[7];
                    toBin(mem, valVar, 7);

                    typeD(opcodeBin,bin1, mem);

                    for(int x = 0; x < 16; x++){
                        Ans[count][x]=ans[x];
                    }





                }

                //for question 3
                else if (!strcmp(opcode, "addf") || !strcmp(opcode, "subf")){
                    char reg1[2], reg2[2], reg3[2];
                    int bin1[3], bin2[3], bin3[3];
                    int opcodeBin[5];
			        //opcodebin stores the bits needed to represent opcode

                    if (!strcmp(opcode, "addf")) toBin(opcodeBin, 16, 5);
                    else if (!strcmp(opcode, "subf")) toBin(opcodeBin, 17, 5);
                

                    while(dataline[i] == ' ') i++;
                    for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];


                    while(dataline[i] == ' ') i++;
                    for(int x = 0; x < 2; x++,i++) reg2[x] = dataline[i];

                    while(dataline[i] == ' ') i++;
                    for(int x = 0; x < 2; x++,i++) reg3[x] = dataline[i];

                    if (typo_reg(reg1)==1 || typo_reg(reg2)==1 || typo_reg(reg3)==1 ){

                            raiseError("Either typo in register(s) or register(s) not defined!", count);
                    }

                    else if(dataline[i] != '\n'){
			                 //if last element in the string is not "\n" then there may be possible extra unnecessary elements in the string
                        raiseError("Unnecessary elements in the instruction!", count);
                    }

                    regBin(bin1, reg1);
                    regBin(bin2, reg2);
                    regBin(bin3, reg3);

                    typeA(opcodeBin, bin1, bin2, bin3);


                    for(int x = 0; x < 16; x++){
                        Ans[count][x]=ans[x];
                    }



                }

                else if (!strcmp(opcode, "movf")){

                    float value = atof(ch + 1);
                    if(value >=0 && value <= 15.75){

                        int final[8];
                        tobinfloating(value,final,8);
                        char reg1[2];
                        int bin1[3];
                        int opcodeBin[5];

                        if (!strcmp(opcode, "movf")) toBin(opcodeBin, 18, 5);
                        

                        while(dataline[i] == ' ') i++;
                        for(int x = 0; x < 2; x++,i++) reg1[x] = dataline[i];

                        i = ch-dataline+1;
                        for(; dataline[i] != ' ' && dataline[i]!='\n' && dataline[i] != '\0'; i++) continue;

                        if (typo_reg(reg1)==1){

                            raiseError("Either typo in register(s) or register(s) not defined!", count);
                        }

                        else if(dataline[i] != '\n'){

                            raiseError("Unnecessary elements in the instruction!", count);
                        }

                        regBin(bin1, reg1);

                        typebf(opcodeBin, bin1, final);


                        for(int x = 0; x < 16; x++){
                            Ans[count][x]=ans[x];
                        }


                    }

                    else{


                        raiseError("Illegal immediate value!", count);
			    //if immediate value is not withtin the given range this error will be raised

                    }

                }

                else{

                   raiseError("Typo in instruction!", count);
                }

        }


        if(hlt_error2==0){

            raiseError("Halt instruction is missing!", -1);
        }

        else if (hlt_error){

            raiseError("Halt instruction is not last!", hlthlt);
        }

    char arr[16];
    if(errorFlag==1){

        for(int i=0; i<=130; i++){
            if(strcmp(error_list[i], "")){

                if(i==130) printf("Error: %s\n", error_list[i]);
                else printf("Error in line %d: %s\n", i+1, error_list[i]);

            }
        }
    }

    else{
        for(int i = 0; i <130; i++){

            for(int j = 0; j < 16; j++){
                if(Ans[i][j] == 1) arr[j] = '1';
                else arr[j] = '0';
            }

            if(strcmp(arr, "0000000000000000")){
                if(hlthlt>1)
                printf("%s", arr);
                else printf("%s\n", arr);
                hlthlt--;

            }
        }
    }

    return 0;

}
