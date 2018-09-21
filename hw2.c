#include <stdio.h>
#include <stdlib.h>
struct client/*client and surver*/
{
    int top;
    int Max_Stack_Size;
    char *stk_array;
    int front;
    int rear;
    int Max_Queue_Size;
    char *que_array;
};
struct client *ptr;
struct wrt/* for the write output file. for each structure*/
{
	int top;
	int size;
	char *arr;
};
struct wrt *result;
void client_add_queue(char ,int, int);
void client_add_stack(char ,int ,int);
char client_delete_stack(int, int);
char client_delete_queue(int,int);
void push(char,int);
void commend_processing(char commend,char client_char,char value,int piece){
	char arr[1]={client_char};
	int client_num=atoi(arr);// char to integer.
	int server=piece-1;/*Because it started at 0 when assigning values to a struct pointer. */
	int a = client_num-1;/*for the server number*/
	if(commend=='A'){// will only add to the client's queue
				client_add_queue(value,client_num-1,piece);
	}
	if(commend=='I'){// it will add to the stack for both server and client.
				client_add_stack(value,client_num-1,piece);//2 ve 3
	}
	if(commend=='S'){
	/* The client will do the unloading from the queue first if there is no Stack.
		Only the server's queue will be filled. If the server queue is full, it will fail and not pass to the stack!!!*/
		if((ptr+a)->top!=0){// if stack not null
			char x;
			x=client_delete_stack(client_num-1,piece);
			push(x,a);
			client_add_queue(x,piece-1,piece);
		}else if((ptr+a)->rear!=(ptr+a)->front){// if queue not null
			char y;
			y=client_delete_queue(client_num-1,piece);
			push(y,a);
			client_add_queue(y,piece-1,piece);
		}else{// stack and queue null
			push('3',a);
		}
	}
	if(commend=='O'){/* operate only server will empties. Firstly Stack !!!*/
			if((ptr+server)->top!=0){// server stack not null
				char s;
				s=client_delete_stack(server,piece);
				push(s,piece-1);
			}else if((ptr+server)->rear!=(ptr+server)->front){// server queue not null
				char q;
				q=client_delete_queue(server,piece);
				push(q,piece-1);
			}else{// server stack and server queue null
				push('3',piece-1);
		}
	}
}
char client_delete_queue(int number,int piece){/* The Circular queue*/
	if(number+1==piece){/* delete surver queue*/
		if((ptr+number)->front!=(ptr+number)->rear){
			(ptr+number)->front++;
		    return (ptr+number)->que_array[(ptr+number)->front%((ptr+number)->Max_Queue_Size+1)];/*because of circular queue*/
		}
	}else{
		if((ptr+number)->front!=(ptr+number)->rear){
			(ptr+number)->front++;
			return (ptr+number)->que_array[(ptr+number)->front%((ptr+number)->Max_Queue_Size+1)];
		}
	}
}
char client_delete_stack(int number,int piece){/*the number of the client or server to delete*/
	if(number+1==piece){/* server stack delete*/
		if((ptr+number)->top!=0){
			(ptr+number)->top--;
			return (ptr+number)->stk_array[(ptr+number)->top+1];
			}
	}else{/* client stack delete*/
		if((ptr+number)->top!=0){
			(ptr+number)->top--;
			return (ptr+number)->stk_array[(ptr+number)->top+1];
		}
	}
	
}
void client_add_queue(char value,int number,int piece){/*circular queue*/
	if(number+1==piece){/* server queue adding*/
			if((ptr+number)->front==((ptr+number)->rear+1)%((ptr+number)->Max_Queue_Size+1)){
				push('1',number);
			}else{
				(ptr+number)->rear=((ptr+number)->rear+1)%((ptr+number)->Max_Queue_Size+1);
				(ptr+number)->que_array[(ptr+number)->rear]=value;
			}
	}else{/* client queue adding*/
			if((ptr+number)->front==((ptr+number)->rear+1)%((ptr+number)->Max_Queue_Size+1)){
				push('1',number);
			}else{
				(ptr+number)->rear=((ptr+number)->rear+1)%((ptr+number)->Max_Queue_Size+1);
				(ptr+number)->que_array[(ptr+number)->rear]=value;
			}
		}
	
}
void client_add_stack(char value,int number,int piece){
	if(number+1==piece){/* server stack adding*/
		if((ptr+number)->Max_Stack_Size==(ptr+number)->top){
				push('2',number);
		}else{
				(ptr+number)->top++;
				(ptr+number)->stk_array[(ptr+number)->top]=value;
	}
	}
	else{/* client stack adding*/
		if((ptr+number)->Max_Stack_Size==(ptr+number)->top){
			push('2',number);
		}else{
			(ptr+number)->top++;
			(ptr+number)->stk_array[(ptr+number)->top]=value;
		}
	}
	
}
void push(char a,int number){/*for the results*/
	if((result+number)->top>=(result+number)->size){
		char *dizi2 =(char*)malloc(sizeof(char)*(result+number)->size*2);
		int i;
		for(i=0;i<(result+number)->size;i++){
			dizi2[i]=(result+number)->arr[i];
		}
		free((result+number)->arr);
		(result+number)->size*=2;
		(result+number)->arr=dizi2;
	}
	(result+number)->arr[(result+number)->top++]=a;
}
int main(int argc,char *argv[]){
	
	const char* file = NULL;
	file = argv[1];
	const char* file1 = NULL;
	file1 = argv[2];
	FILE *input1 = fopen (file,"r");
	if(input1==NULL){
		printf("input.txt not found");
		return 0;
	}
	int piece;/* value giving the number of rows*/
	fscanf(input1,"%d",&piece);
	ptr = (struct client*) malloc(piece * sizeof(struct client));/* space for server and client*/
	result = (struct wrt*) malloc(piece * sizeof(struct wrt));/*open space for result stack*/
	int stack_size[piece],queue_size[piece];
	int queue,stack;
	int i;
	for(i=0;i<piece;i++){/*piece-1== Server*/
		(result+i)->size=2;
		(result+i)->top=0;
		(result+i)->arr= (char*)malloc(sizeof(char)*2);
		fscanf(input1,"%d",&queue_size[i]);
		(ptr+i)->Max_Queue_Size=queue_size[i];
		queue=queue_size[i];
		(ptr+i)->que_array= (char*)malloc(sizeof(char)*queue);
		(ptr+i)->front=0;
		(ptr+i)->rear=0;
		fscanf(input1,"%d",&stack_size[i]);
		stack = stack_size[i];
		(ptr+i)->stk_array = (char*)malloc(sizeof(char)*stack);
		(ptr+i)->Max_Stack_Size=stack_size[i];
		(ptr+i)->top=0;
	}
		fclose(input1);
	//****input2*****
	FILE *input2 = fopen (file1,"r");
	char line[256];
		if(input2==NULL){
				printf("input2.txt not found");
				return 0;
			}
		int piece_input2;/* value giving the number of rows for input2*/
		fscanf(input2,"%d",&piece_input2);
		while(fgets(line,sizeof(line),input2)){
		if(line[2]!='\0'){
				commend_processing(line[0],line[2],line[4],piece);
				}
		}
		fclose(input2);
		const char* file2 = NULL;
		file2 = argv[3];
		FILE *fp_write;/*for the writing.*/
		fp_write=fopen(file2,"w");
		for(i=0;i<piece;i++){
			fwrite((result+i)->arr,1,(result+i)->top,fp_write);
			fprintf(fp_write,"\n");
		}
}