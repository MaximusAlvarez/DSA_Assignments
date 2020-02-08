#include<stdio.h>
#include<stdlib.h>

int n=2,i=0;
int *A;

int POP(){
	if(i>0){
		printf("Element %d with value %d popped.\n",i,A[i-1]);
		i--;
	}
	else
	printf("There is no element to pop.\n");
	return 0;
}
int PUSH(){
	if(i==n){
		int *B;
		B = (int*)malloc(2*n*sizeof(int));
		for(int j=0;j<n;j++)
			B[j]=A[j];
		free(A);
		A = B;
		n*=2;
	}
	int val;
	printf("Enter the value to be Pushed:");
	scanf("%d",&val);
	A[i++]=val;
	return 0;
}

int main(){
	A=(int*)malloc(n*sizeof(int));
	int choice;
	printf("MENU:\n1.PUSH\n2.POP\n3.Exit\n");
	while(1){
		printf("Enter your Choice:");
		scanf("%d",&choice);
		switch(choice){
			case 1: PUSH();
				break;
			case 2: POP();
				break;
			case 3: return 0;
			default: printf("\nInvalid Choice.\n");
		}
	}
}	
