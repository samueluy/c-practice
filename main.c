/*
TODO:
encryption
for loop for all arrays to make them all 0
password input '*"
No need enter
Ascii art (Joshua)
*/

#include <stdio.h>
#include <string.h>

#define STRING_SIZE 256
#define MAX_LINE 512

typedef struct{
	char account_name[STRING_SIZE];
	char username[STRING_SIZE];
	char password[STRING_SIZE];
} credentials;

int validInput(int nMaxInput){ // Asks the user for input till valid (use for integer-navigated menus)
	int nInput, nValid=0;
	
	printf("Enter: ");
	scanf("%d", &nInput);
	while(!nValid){
		fflush(stdin);
		if(nInput <= 0 || nInput > nMaxInput){
		nValid=0;
		printf("Invalid!\nPlease enter a valid input: ");
		scanf("%d", &nInput);
		}
		else
			nValid=1;
	}
	
	return nInput;
}

int welcomeScreen(){
	
	printf("[1] Login\n");
	printf("[2] Create a new account\n");
	
	return validInput(2);
}

void login(char filename[STRING_SIZE]){ // goto main menu, make key do something
	FILE *common;
	common = fopen("common", "r");
	
	int nValidUser=0, nValid=0, count=0, flag=0;
	char key[STRING_SIZE], line_buffer[STRING_SIZE];
	credentials user;
	
	printf("Enter username: ");
	fgets(user.username, STRING_SIZE, stdin);
	
	printf("Enter password: ");
	fgets(user.password, STRING_SIZE, stdin);
	
	while(fgets(line_buffer, MAX_LINE, common) != NULL && !flag){
		count++;
		
		if(count==1 && strcmp(user.username, line_buffer) == 0) // check every username
			nValidUser=1;
			
		if(count==2 && nValidUser){ // check password if username is valid
			if(strcmp(user.password, line_buffer) == 0)
				nValid=1;
			else
				flag=1; // exit loop if username does not match password
		}
		
		if(nValid && count==3) // copy line_buffer to filename to use in main
			strcpy(filename, line_buffer);
			
		if(count==3) // reset count -> move to next user
			count=0;
	}
	
	if(!nValid)
		printf("Username/Password not found.\n");
	else{
		printf("Enter key: ");
		fgets(key, STRING_SIZE, stdin);
	}
	strtok(filename, "\n");
	fclose(common);
}

void newAccount(char filename[STRING_SIZE]){ // TODO: create key
	FILE *common, *user_file;
	common = fopen("common", "a+");
	
	int nValid=1, nValidUsername=1, nValidFilename=1, count=0;
	char line_buffer[STRING_SIZE];
	credentials user;
	
	printf("Enter username: ");
	fgets(user.username, STRING_SIZE, stdin);
	
	printf("Enter password: ");
	fgets(user.password, STRING_SIZE, stdin);
	
	printf("Enter file name: ");
	fgets(filename, STRING_SIZE, stdin);
	
	while(fgets(line_buffer, MAX_LINE, common) != NULL && nValid==1){
		count++;
		if(count==1 && strcmp(user.username, line_buffer) == 0){ // check every username
			nValidUsername=0;
			nValid=0;
		}
		
		if(count==3 && strcmp(filename, line_buffer) == 0){ // check every filename
			nValidFilename=0;
			nValid=0;
		}
		
		if(count == 3) // reset count to 0
			count = 0;
	}
	
	if(!nValidFilename)
		printf("Filename is already in use.\n");
	else if(!nValidUsername)
		printf("Username is already in use.\n");
	else{
		fprintf(common, "%s", user.username);
		fprintf(common, "%s", user.password);
		fprintf(common, "%s", filename);
		
		strtok(filename, "\n");
		user_file = fopen(filename, "w"); // create user file
		fclose(user_file);
	}
	
	fclose(common);
}

int mainMenu(){
	
	printf("[1] Display all passwords\n");
	printf("[2] Add a password\n");
	printf("[3] Change a password\n");
	printf("[4] Delete a password\n");
	printf("[5] Change your password for Password Keeper\n");
	printf("[6] Logout and exit Password Keeper\n");
	
	return validInput(6);
}

void displayCredentials(char filename[STRING_SIZE]){
	FILE *user_file;
	user_file = fopen(filename, "r");
	
	int count;
	char line_buffer[STRING_SIZE];
	
	while(fgets(line_buffer, MAX_LINE, user_file) != NULL){
		count++;
		if(count==1)
			printf("Account: %s", line_buffer); // change bring to center.
		else if(count==2)
			printf("Username: %s", line_buffer);
		else if(count==3){
			printf("Password: %s\n", line_buffer);
			count=0;
		}
	}
	fclose(user_file);
}

void addPassword(char filename[STRING_SIZE]){ // check if unique application
	FILE *user_file;
	user_file = fopen(filename, "a+");
	
	int unique_name=1, count=0;
	char line_buffer[STRING_SIZE];
	credentials user;
	
	printf("Enter account name: ");
	fgets(user.account_name, STRING_SIZE, stdin);
	printf("Enter username: ");
	fgets(user.username, STRING_SIZE, stdin);
	printf("Enter password: ");
	fgets(user.password, STRING_SIZE, stdin);
	
	while(fgets(line_buffer, MAX_LINE, user_file) != NULL){
		count++;
		if(count==1 && strcmp(user.account_name, line_buffer)==0)
			unique_name=0;
		
		if(count==3)
			count=0;
	}
	
	if(unique_name){
		fprintf(user_file, "%s", user.account_name);
		fprintf(user_file, "%s", user.username);
		fprintf(user_file, "%s", user.password);
	}
	else
		printf("Account name already exists.\n");
	
	fclose(user_file);
}

void changePassword(char filename[STRING_SIZE]){
	FILE *user_file, *temp;
	user_file = fopen(filename, "r");
	
	
	int valid_account_name=0, valid_password=0, line_number=0, count=0;
	char new_password[STRING_SIZE], line_buffer[STRING_SIZE];
	credentials user;
	
	printf("Enter account name: ");
	fgets(user.account_name, STRING_SIZE, stdin);
	printf("Enter password: ");
	fgets(user.password, STRING_SIZE, stdin);
	
	while(fgets(line_buffer, MAX_LINE, user_file) != NULL && !valid_password){ //stop loop if user->password is valid
		line_number++;
		count++;
		if(!valid_account_name && (count==1 && strcmp(user.account_name, line_buffer)==0)) // check for username
			valid_account_name=1;
		
		if(valid_account_name && (count==3 && strcmp(user.password, line_buffer) == 0)){ // check for password below username
			valid_password=1;
			printf("Enter new password: ");
			fgets(new_password, STRING_SIZE, stdin);
		}
		
		if(count==3)
			count=0;
	}
	fclose(user_file);
	
	if(!valid_account_name || !valid_password)
		printf("Invalid account name/password\n");
	else{ // replace file with changed password instead of old
		user_file = fopen(filename, "r");
		temp = fopen("temp", "w");
			while(fgets(line_buffer, MAX_LINE, user_file) != NULL){
				count++;
				if(line_number==count)
					fprintf(temp, "%s", new_password);
				else
					fprintf(temp, "%s", line_buffer);
			}
			fclose(user_file);
			fclose(temp);
			remove(filename);
			rename("temp", filename);
	}
}

void deletePassword(){
}

void endScreen(){
	
	printf("Thank you for using Password Keeper!\n");
	printf("See you next time!");
}


int main(void){
	// FILE *common, *user_file;
	//	user_file = fopen(filename, "r");
	
	int nInput;
	char filename[STRING_SIZE];
	
	nInput = welcomeScreen(); // open welcome screen. return user input to nInput
	
	switch (nInput){
		case 1:
			login(filename);
			break;
		case 2:
			newAccount(filename); // fix if wrong
			break;
	}
	
	while(nInput!=6){
		nInput = mainMenu(); // open main menu. return user input to nInput
	
		switch (nInput){ // main menu choices
			case 1:
				displayCredentials(filename);
				break;
			case 2:
				addPassword(filename);
				break;
			case 3:
				changePassword(filename);
				break;
			case 4:
				deletePassword(filename);
				break;
			case 5:
				break;
			case 6:
				endScreen();
				break;
		}
	}
	
//	fclose(common);

	
		
	return 0;
}
