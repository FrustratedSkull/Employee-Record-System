#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50
typedef struct Employee{
	int Eid;
	char Name[SIZE];
	char Email[SIZE];
	struct Employee *Next;
} Employee;
Employee *empHead= NULL;
FILE *file;
int fileOpen();
void fileStore(int);
// To open the file, return 0 if couldn't open the file else return 1
int fileOpen(){
    file = fopen("data2.txt","a+");
    if(file == NULL){
        printf("\n\n\t Sorry! Unable to open/create the file");
        return 0;
    }
    else{
        return 1;
    }
}
// Closing the file 
void fileClose(){
    fclose(file);
}
// Initializing the first node
void initialization(){
    empHead = (Employee*)malloc(sizeof( Employee));
    Employee *tempHead = ( Employee*)malloc(sizeof( Employee));
	int Eid;
	char Name[SIZE];
	char Email[SIZE];
	empHead->Next = NULL;
	while(fscanf(file, "%d %s %s",&Eid,Name,Email) != EOF){
	    Employee *newEmployee = (Employee*)malloc(sizeof( Employee));
	    newEmployee->Eid = Eid;
	    strcpy(newEmployee->Name,Name);
	    strcpy(newEmployee->Email,Email);
		newEmployee->Next = NULL;
			if(empHead->Next == NULL){
				empHead->Next = newEmployee;
			}
			else{
				tempHead = empHead->Next;
				while(tempHead != NULL){
					if(tempHead->Next == NULL){
						tempHead->Next = newEmployee;
						break;
					}
					tempHead = tempHead->Next;
				}
			}
	}
	fileClose();
}

// To create a new node
void create(){
	//system("cls");
	int f = 0, Eid;
	Employee *newEmployee = (Employee*)malloc(sizeof( Employee));
	Employee *tempHead = ( Employee*)malloc(sizeof( Employee));
	printf("\n\t ID :");
	scanf("%d",&Eid);
	tempHead = empHead->Next;
	f = 0;
	while(tempHead != NULL){
		if(tempHead->Eid == Eid){
			f = 1;
			printf("\n\n\t Sorry! Employee with same ID already exists");
			break;
		}
		tempHead = tempHead->Next;
	}
	if(f == 0){
		newEmployee->Eid = Eid;
		printf("\n\t Name :");
		getchar();
		gets(newEmployee->Name);
		printf("\n\t Email :");
		gets(newEmployee->Email);
		newEmployee->Next = NULL;
		if(empHead->Next == NULL){
			empHead->Next = newEmployee;
		}
		else{
			tempHead = empHead->Next;
			while(tempHead != NULL){
				if(tempHead->Next == NULL){
					tempHead->Next = newEmployee;
					break;
				}
				tempHead = tempHead->Next;	
			}
		}
	}
	fileStore(newEmployee->Eid);
	tempHead = NULL;
	newEmployee = NULL;
	fflush(stdin);
	getchar();
}
// To update a particular Employee record
void update(){
	system("cls");
    Employee *tempHead = ( Employee*)malloc(sizeof( Employee));
    int Eid, i = 0;                            // Taking Employee ID as input to search for the specific employee
	printf("\nEnter Employee ID:");
	scanf("%d",&Eid);
	getchar();
	tempHead = empHead->Next;
	while(tempHead != NULL){
	    if(tempHead->Eid == Eid){       // If Employee ID is matched, showing the Employee record
	        printf("\nCurrent \t-\t ID : %d \t New \t-\t ID :",tempHead->Eid);
	        printf("%d",tempHead->Eid);
	        //getchar();
	        printf("\nCurrent \t-\t Name : %s \t New \t-\t Name :",tempHead->Name);
	        gets(tempHead->Name);
	        printf("\nCurrent \t-\t Email : %s \t New \t-\t Email :",tempHead->Email);
	        gets(tempHead->Email);
	        i = 1;
	        break;
	    }           // Validating Employee ID
		tempHead = tempHead->Next;	
	}
	if(i == 0){
		printf("\n\n\t Sorry! No matching record found.");
	}
	// Updating from file
    file = fopen("data2.txt","w");
    tempHead = empHead->Next;
    while(tempHead != NULL){
    	fprintf(file,"%d %s %s \n",tempHead->Eid,tempHead->Name,tempHead->Email);
		tempHead = tempHead->Next;
	}
	fileClose();
	getchar();
}
// Display specific employee data
void displayOne(){
	system("cls");
    Employee *tempHead = ( Employee*)malloc(sizeof( Employee));
    int Eid, f = 0;                            // Taking Employee ID as input to search for the specific employee
	printf("\nEnter Employee ID:");
	scanf("%d",&Eid);
	tempHead = empHead->Next;
	while(tempHead != NULL){
	    if(tempHead->Eid == Eid){       // If Employee ID is matched, showing the Employee record
	        printf("\n\t ID : %d",tempHead->Eid);
	        printf("\n\t Name : %s",tempHead->Name);
	        printf("\n\t Email : %s",tempHead->Email);
	        f = 1;
	        break;
	    }           // Validating Employee ID
		tempHead = tempHead->Next;	
	}
	if(f == 0){
		printf("\n\n\t Sorry! No matching record found.");
	}
	getchar();
}

// Display
void displayAll(){
	system("cls");
	Employee *tempHead = ( Employee*)malloc(sizeof( Employee));
	tempHead = empHead->Next;
	if(tempHead == NULL){
		printf("\n\n\t Sorry! There is no record available");
	}
	else{
		printf("\n\n\t List of all employees \n\n");
		while(tempHead != NULL){
			printf("\n\t ID : %d",tempHead->Eid);
			printf("\n\t Name : %s",tempHead->Name);
			printf("\n\t Email : %s",tempHead->Email);
			tempHead = tempHead->Next;
		}
	}
	getchar();
}
// Deallocating Memory
void dealloc(){
	system("cls");
	Employee *delEmployee = (Employee*)malloc(sizeof( Employee));
	Employee *prevEmployee = (Employee*)malloc(sizeof( Employee));
	int Eid;
	printf("\n Enter Employee ID:");
	scanf("%d",&Eid);
	if(empHead->Next == NULL){
		printf("\n No record found");
	}
	else{
		delEmployee = empHead->Next;
		prevEmployee = empHead;
		while(delEmployee != NULL){
			if(delEmployee->Eid == Eid){
					prevEmployee->Next = delEmployee->Next;
					free(delEmployee);
					printf("\n\t Record has been deleted");
					break;
			}
			prevEmployee = delEmployee;
			delEmployee = delEmployee->Next;
		}
	}
	// Deleting from file
    file = fopen("data2.txt","w");
    Employee *tempHead = (Employee*)malloc(sizeof( Employee));
    tempHead = empHead->Next;
    while(tempHead != NULL){
    	fprintf(file,"%d %s %s \n",tempHead->Eid,tempHead->Name,tempHead->Email);
		tempHead = tempHead->Next;
	}
	fileClose();
	getchar();
}
void fileDisplay(){
    if(fileOpen()){
        int Eid;
    	char Name[SIZE];
    	char Email[SIZE];
        fseek(file,1,0);
        while(fscanf(file,"%d %s %s",&Eid,Name,Email) != EOF){
            printf("\n %d %s %s",Eid,Name,Email);
        }   
    }
    else{
    	system("cls");
        printf("\n\n\t File could not be opened");
        getchar();
    }
    fileClose();
}
// Strong into file
void fileStore(int Eid){
	fileOpen();
    Employee *tempHead = (Employee*)malloc(sizeof( Employee));
    tempHead = empHead->Next;
    while(tempHead != NULL){
	    if(tempHead->Eid == Eid){       // If Employee ID is matched, showing the Employee record
	        fprintf(file,"%d %s %s \n",tempHead->Eid,tempHead->Name,tempHead->Email);
	        system("cls");
	        //printf("\n\t %d",tempHead->Eid);
	        //printf("\n\t %s",tempHead->Name);
	        //printf("\n\t %s",tempHead->Email);
	        printf("\n\n Record has been saved");
	        break;
	    }           // Validating Employee ID
		tempHead = tempHead->Next;	
	}
	fileClose();
}

int main()
{
	
	 int i = 0;
    if(fileOpen()){
        initialization();
        while(i < 5 ){
        	system("cls");
        	printf("\n 1. Insert Record");
        	printf("\n 2. Update Record");
        	printf("\n 3. Delete Record");
        	printf("\n 4. Display Record");
        	printf("\n 5. Exit \n");
        	scanf(" %d",&i);
        	switch(i){
        	case 1: create(); break;
        	case 2: update(); break;
        	case 3: dealloc(); break;
        	case 4: system("cls");
        			printf("\n 1. Display One Record");
        			printf("\n 2. Display All \n");
        			scanf(" %d",&i);
        			if(i == 1) displayOne();
        			else displayAll();
        			break;
        	}
        	getchar();
        }
    }
    /*
    fileOpen();
	initialization();
	create();
	create();
	create();
	displayAll();
	*/
	return 0;
}
 
