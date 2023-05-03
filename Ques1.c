#include<stdio.h>
#include<stdbool.h>
#include<strings.h>

static bool ans[16];

void typeA (bool opcode[], bool reg1[], bool reg2[], bool reg3[]){
    for(int i = 0; i < 5; i++){
        ans[i] = opcode[i];
    }

    int j = 7;
    for(int i = 0; i < 3; i++){
        ans[j+i] = reg1[i];
    }
    j += 3;

}

int toBin(bool var[], int n, int bits){
    for(int i = 0; i < bits; i++){
        var[i] = 0;
    }
    int j = n-1;
    while(n > 0){
        var[j] = (bool) (n % 2);
        n /= 2;
        j--;
        if (j < 0){
            return 0;
        }
    }

    return 1;
}



int main(){
	char dataline[100];

	FILE* filer, filew;
	filer = fopen("Assembly.txt", "r");
	filew = fopen('Ans.txt', "w");

	while(1){
		fgets(dataline, 100, filew);
		if(feof(filew)) break;
		if (dataline){

		}
	}




    return 0;
}
