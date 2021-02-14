#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<direct.h>
#include<time.h>
#pragma warning(disable:4996)
struct user {
	char name[100];
	char username[100];
	char password[50];
	int pass_pow;
	int access;
	int wrong;
	int time;
	struct user *ptr;
};
struct file {
	char name[100];
	char address[200];
	char creator[100];
	char last_access[100];
	char last_change[100];
	int access;
	struct file *ptr;
};
struct directory
{
	char name[100];
	char address[200];
	char creator[100];
	int access;
	struct directory *ptr;
};
struct user *temp, *head = NULL, *p = NULL, *push;
struct file *temp_file, *head_file = NULL, *p_file, *_push;
struct directory *temp_dir, *head_dir = NULL, *p_dir, *push_;
char root_address[100];
time_t current_time = time(NULL);
char* c_time_string = ctime(&current_time);
void push_dir(char name[], char address[], char creator[], int access) {
	temp_dir = (struct directory *)malloc(sizeof(struct directory));
	strcpy(temp_dir->name, name);
	strcpy(temp_dir->address, address);
	strcpy(temp_dir->creator, creator);
	temp_dir->access = access;
	temp_dir->ptr = NULL;
	if (head_dir == NULL)
		head_dir = temp_dir;
	else {
		for (push_ = head_dir; push_->ptr != NULL; push_ = push_->ptr);
		push_->ptr = temp_dir;
	}
}
int search_dir(char address[]) {
	for (p_dir = head_dir; p_dir != NULL&&strcmp(p_dir->address, address) != 0; p_dir = p_dir->ptr);
	if (p_dir == NULL)
		return -1;
	else
		return 1;
}
void delete_dir() {
	for (temp_dir = head_dir; temp_dir->ptr != p_dir; temp_dir = temp_dir->ptr);
	temp_dir->ptr = p_dir->ptr;
	free(p_file);
}
void push_file(char name[], char address[], char creator[], char last_access[], char last_change[], int access) {
	temp_file = (struct file*)malloc(sizeof(struct file));
	strcpy(temp_file->name, name);
	strcpy(temp_file->address,address);
	strcpy(temp_file->creator, creator);
	strcpy(temp_file->last_access, last_access);
	strcpy(temp_file->last_change, last_change);
	temp_file->access = access;
	temp_file->ptr = NULL;
	if (head_file == NULL)
		head_file = temp_file;
	else {
		for (_push = head_file; _push->ptr != NULL; _push = _push->ptr);
		_push->ptr = temp_file;
	}
}
int search_file(char name[],char current_address[]) {
	for (p_file = head_file; p_file != NULL&&strcmp(p_file->name, name) != 0; p_file = p_file->ptr);
	if (p_file == NULL)
		return -1;
	else if (strcmp(p_file->address, current_address) != 0)
		return -1;
	else
		return 1;
}
void delete_file() {
	for (temp_file = head_file; temp_file->ptr != p_file; temp_file = temp_file->ptr);
	temp_file->ptr = p_file->ptr;
	free(p_file);
}
void push_user(char name[], char username[], char password[], int pass_pow, int access, int wrong,int time) {
	temp = (struct user *)malloc(sizeof(struct user));
	strcpy(temp->name, name);
	strcpy(temp->username, username);
	strcpy(temp->password, password);
	temp->pass_pow = pass_pow;
	temp->access = access;
	temp->wrong = wrong;
	temp->time = time;
	temp->ptr = NULL;
	if (head == NULL)
		head = temp;
	else {
		for (push = head;push->ptr != NULL;push = push->ptr);
		push->ptr = temp;
	}
}
int passpow(char password[]) {
	int pow = 0;
	for (int i = 0;i < strlen(password);i++) {
		if (isalpha(password[i]) != 0 && islower(password[i]) != 0)
			pow += 2;
		else if (isalpha(password[i]) != 0 && isupper(password[i]) != 0)
			pow += 4;
		else if (isdigit(password[i]) != 0)
			pow += 3;
		else if (isspace(password[i]) != 0)
			pow += 1;
		else
			pow += 8;
	}
	return pow;
}
int chartoint(char ch[]) {
	int x = strlen(ch);
	int y = x - 1;
	int integer = 0;
	for (int i = 0;i < x;i++) {
		integer += (ch[i] - '0')*pow(10, (y));
		y--;
	}
	return integer;
}
int search(char name[], char username[], char password[]) {
	for (p = head;p != NULL&&strcmp(p->name, name) != 0;p = p->ptr);
	if (p == NULL)
		return -1;
	else if (strcmp(p->username, username) == 0 && strcmp(p->password, password) == 0)
		return 1;
	else
		return 0;
}
int search_username(char username[]) {
	for (temp = head;temp != NULL&&strcmp(temp->username, username) != 0;temp = temp->ptr);
	if (temp == NULL)
		return -1;
	else
		return 1;
}
void print(void) {
	if (p->access == 1)
		printf("%s* --> ", p->name);
	else
		printf("%s --> ", p->name);
}
void writeintofile(char *filename) {
	FILE *pointer;
	char curr_address[200];
	getcwd(curr_address, 200);
	chdir(root_address);
	pointer = fopen(filename, "w");
	for (temp = head;temp != NULL;temp = temp->ptr)
		fprintf(pointer, "%s,%s,%s,%d,%d,%d,%d\n", temp->name, temp->username, temp->password, temp->pass_pow, temp->access, temp->wrong,temp->time);
	fclose(pointer);
	chdir(curr_address);
}
void writeintofile1(char *filename) {
	FILE *pointer;
	char curr_address[200];
	getcwd(curr_address, 200);
	chdir(root_address);
	pointer = fopen(filename, "w");
	for (temp_file = head_file; temp_file != NULL; temp_file = temp_file->ptr)
		fprintf(pointer,"%s,%s,%s,%s,%s,%d\n",temp_file->name,temp_file->address, temp_file->creator, temp_file->last_access, temp_file->last_change, temp_file->access);
	fclose(pointer);
	chdir(curr_address);
}
void writeintofile2(char *filename) {
	FILE *pointer;
	char curr_address[200];
	getcwd(curr_address, 200);
	chdir(root_address);
	pointer = fopen(filename, "w");
	for (temp_dir = head_dir; temp_dir != NULL; temp_dir = temp_dir->ptr)
		fprintf(pointer, "%s,%s,%s,%d\n", temp_dir->name, temp_dir->address, temp_dir->creator, temp_dir->access);
	fclose(pointer);
	chdir(curr_address);
}
int main() {
	c_time_string[strlen(c_time_string) - 1] = '\0';
	chdir("root");
	FILE *pointer;
	char name[100], username[100], password[50], temp1[300], statement[200], state_name[200] = "", *x, file1_name[200], file2_name[200], curr_address[200], address[200], creator[100], last_access[50], last_change[50];
	int pass_pow, access, wrong, time, a, i = 0, j = 0, k;
	clock_t t, t1;
	strcpy(root_address, "C:\\Users\\ya mahdi\\documents\\visual studio 2015\\Projects\\Project35\\Project35\\root");
	pointer = fopen("user root.txt", "r");
	while (!feof(pointer)) {
		fgets(temp1, 200, pointer);
		if (strcmp(temp1, "") == 0 || strcmp(temp1, "\n") == 0)
			break;
		strcpy(name, strtok(temp1, ","));
		strcpy(username, strtok(NULL, ","));
		strcpy(password, strtok(NULL, ","));
		pass_pow = chartoint(strtok(NULL, ","));
		access = chartoint(strtok(NULL, ","));
		wrong = chartoint(strtok(NULL, ","));
		time = chartoint(strtok(NULL, ",,\n"));
		push_user(name, username, password, pass_pow, access, wrong, time);
		strcpy(temp1, "");
	}
	fclose(pointer);
	pointer = fopen("file root.txt", "r");
	while (!feof(pointer))
	{
		fgets(temp1, 300, pointer);
		if (strcmp(temp1, "") == 0 || strcmp(temp1, "\n") == 0)
			break;
		strcpy(name, strtok(temp1, ",,\n"));
		strcpy(address, strtok(NULL, ",,\n"));
		strcpy(creator, strtok(NULL, ",,\n"));
		strcpy(last_access, strtok(NULL, ",,\n"));
		strcpy(last_change, strtok(NULL, ",,\n"));
		access = chartoint(strtok(NULL, ",\n"));
		push_file(name, address, creator, last_access, last_change, access);
		strcpy(temp1, "");
	}
	fclose(pointer);
	pointer = fopen("dir root.txt", "r");
	while (!feof(pointer)) {
		fgets(temp1, 300, pointer);
		if (strcmp(temp1, "") == 0 || strcmp(temp1, "\n") == 0)
			break;
		strcpy(name, strtok(temp1, ","));
		strcpy(address, strtok(NULL, ","));
		strcpy(creator, strtok(NULL, ","));
		access = chartoint(strtok(NULL, ",\n"));
		push_dir(name, address, creator, access);
		memset(temp1, NULL, sizeof(temp1));
	}
LOGIN:do
{
	printf("Enter Your Name: ");
	gets_s(name);
	printf("Enter Your Username: ");
	gets_s(username);
	printf("Enter Your Password: ");
	gets_s(password);
	if (search(name, username, password) == -1) {
		printf("First you should add by admin.\n");
	}
	else if (search(name, username, password) == 0)
		printf("Your username or password is incorrect.\n");
} while (search(name, username, password) != 1);
chdir(name);
t = clock();
system("Cls");
printf("\t\t\t\t***dear %s, welcome to my programm***\n", p->name);
print();
while (1) {
	gets_s(statement);
	for (i = 0; i < strlen(statement); i++)
		if (statement[i] == '>')
			break;
	if (i != strlen(statement) && statement[i + 1] != '>') {
		for (j = 0, k = 0; k < i - 1; j++, k++)
			file2_name[j] = statement[k];
		file2_name[j] = '\0';
		for (j = 0, k = i + 2; k < strlen(statement); k++, j++)
			file1_name[j] = statement[k];
		file1_name[j] = '\0';
		statement[0] = '>';
		statement[1] = '\0';
	}
	else if (i != strlen(statement) && statement[i + 1] == '>') {
		for (j = 0, k = 0; k < i - 1; j++, k++)
			file2_name[j] = statement[k];
		file2_name[j] = '\0';
		for (j = 0, k = i + 3; k < strlen(statement); k++, j++)
			file1_name[j] = statement[k];
		file1_name[j] = '\0';
		statement[0] = '>';
		statement[1] = '>';
		statement[2] = '\0';
	}
	else {
		strtok(statement, " ");
		x = strtok(NULL, " ");
		while (x != NULL) {
			strcat(state_name, x);
			x = strtok(NULL, " ");
			if (x != NULL)
				strcat(state_name, " ");
		}
	}
	if (strcmp(statement, "su") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		if (search_username(state_name) == -1)
			printf("Not exist.\n");
		else {
			if (p->access != 1) {
				printf("Enter Password : ");
				gets_s(password);
				if (strcmp(temp->password, password) != 0)
					printf("Password is incorrect.\n");
				else {
					p = temp;
					t = clock();
				}
			}
			else {
				p = temp;
				t = clock();
			}
			chdir(root_address);
			chdir(p->name);
		}
		printf("\t\t\t\t***dear %s, welcome to this programm***\n", p->name);
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "passwd") == 0 && strcmp(state_name, "") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		printf("Enter your new password: ");
		gets_s(password);
		if (passpow(password) > 33 && passpow(password) <= 100) {
			strcpy(p->password, password);
			temp->pass_pow = passpow(password);
		}
		else
			printf("This password is invalid.\n");
		writeintofile("user root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "passwd") == 0 && p->access == 1) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		if (search_username(state_name) == -1)
			printf("Not exist.\n");
		else {
			printf("Enter %s's new password: ", temp->name);
			gets_s(password);
			if (passpow(password) > 33 && passpow(password) <= 100) {
				strcpy(temp->password, password);
				temp->pass_pow = passpow(password);
			}
			else
				printf("This password is invalid.\n");
		}
		writeintofile("user root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "passwd-l") == 0 && p->access == 1) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		time = chartoint(strtok(state_name, " "));
		strcpy(username, "");
		x = strtok(NULL, " ");
		while (x != NULL) {
			strcat(username, x);
			x = strtok(NULL, " ");
			if (x != NULL)
				strcat(state_name, " ");
		}
		if (search_username(username) == -1)
			printf("Not exist.\n");
		else {
			printf("The %s's time is %d second.\n", temp->name, temp->time);
			temp->time += time;
		}
		writeintofile("user root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "create") == 0 && strcmp(state_name, "user") == 0 && p->access == 1) {
		printf("Enter name: ");
		gets_s(name);
		printf("Enter username: ");
		gets_s(username);
		if (search_username(username) == 1)
			printf("This user exist.\n");
		else {
			printf("Enter password: ");
			gets_s(password);
			if (passpow(password) <= 33 || passpow(password) > 100)
				printf("This password is invalid.\n");
			else {
				push_user(name, username, password, passpow(password), 0, 0, 3600);
				getcwd(curr_address, 200);
				chdir(root_address);
				mkdir(name);
				strcpy(address, root_address);
				strcat(address, "\\");
				strcat(address, name);
				push_dir(name, address, name, 3);
				chdir(curr_address);
				writeintofile2("dir root.txt");
			}
		}
		writeintofile("user root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "chgr") == 0 && p->access == 1) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		if (search_username(state_name) == -1)
			printf("Not exist.\n");
		else {
			if (temp->access == 1)
				printf("This user is admin.\n");
			else if (passpow(temp->password) <= 75)
				printf("User's password is not safe to being admin.\n");
			else if (temp->wrong > 10)
				printf("User's wrong answer is more than 10.\n");
			else
				temp->access = 1;
		}
		writeintofile("user root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "mkdir") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		getcwd(curr_address, 200);
		strcpy(address, state_name);
		for (i = strlen(address) - 1; address[i] != '\\'&&i != 0; i--);
		if (i != 0) {
			for (j = i + 1, k = 0; j < strlen(address); j++, k++)
				name[k] = address[j];
			name[k] = '\0';
			address[i] = '\0';
			if (chdir(address) == -1) {
				printf("This address is wrong.\n");
				goto X;
			}
			getcwd(address, 200);
			if (search_dir(address) == 1) {
				if (p_dir->access == 1 && p->access == 1 || p_dir->access == 2 && strcmp(p->name, p_dir->creator) == 0 || p_dir->access == 3) {
					chdir(curr_address);
					a = mkdir(state_name);
					if (a < 0)
						printf("The directory has already exist.\n");
					else {
						strcat(address, "\\");
						strcat(address, name);
						push_dir(state_name, address, p->name, 3);
					}
				}
				else
					printf("You can't access this directory.\n");
			}
			else
				printf("This address is wrong.\n");
			chdir(curr_address);
		}
		else {
			a = mkdir(state_name);
			if (a < 0)
				printf("The directory has already exist.\n");
			else {
				strcat(curr_address, "\\");
				strcat(curr_address, state_name);
				push_dir(state_name, curr_address, p->name, 3);
			}
		}
	X:writeintofile2("dir root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "cd") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		getcwd(curr_address, 200);
		a = chdir(state_name);
		if (a < 0)
			printf("This directory does'nt exist.\n");
		getcwd(address, 200);
		search_dir(address);
		if (!(p_dir->access == 1 && p->access == 1 || p_dir->access == 2 && strcmp(p->name, p_dir->creator) == 0 || p_dir->access == 3)) {
			chdir(curr_address);
			printf("You can't access This directory\n");
		}
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "pwd") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		getcwd(address, 200);
		printf("%s\n", address);
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "rm-r") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		getcwd(curr_address, 200);
		chdir(state_name);
		getcwd(address, 200);
		search_dir(address);
		if (p_dir->access == 1 && p->access == 1 || p_dir->access == 2 && strcmp(p->name, p_dir->creator) == 0 || p_dir->access == 3) {
			chdir(curr_address);
			strcpy(statement, "rmdir/s ");
			strcat(statement, state_name);
			system(statement);
			delete_dir();
		}
		else
			printf("You can't access this directory.\n");
		chdir(curr_address);
		writeintofile2("dir root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, ">") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		getcwd(curr_address, 200);
		if (search_file(file1_name, curr_address) == 1) {
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
				strcpy(p_file->last_change, c_time_string);
			}
			else {
				printf("You can't access %s.\n", file1_name);
				goto END;
			}
		}
		else
			push_file(file1_name, curr_address, p->name, c_time_string, c_time_string, 3);
		FILE *pointer2;
		FILE *pointer1;
		pointer1 = fopen(file1_name, "w");
		pointer2 = fopen(file2_name, "r");
		if (pointer2 == NULL) {
			fprintf(pointer1, file2_name);
		}
		else {
			search_file(file2_name, curr_address);
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcpy(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
			}
			else {
				printf("You can't access %s.\n", file2_name);
				goto END;
			}
			while (!feof(pointer2)) {
				fgets(temp1, 200, pointer2);
				fprintf(pointer1, temp1);
			}
			fclose(pointer2);
		}
		fclose(pointer1);
	END:writeintofile1("file root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, ">>") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		getcwd(curr_address, 200);
		if (search_file(file1_name, curr_address) == 1) {
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
				strcpy(p_file->last_change, c_time_string);
			}
			else {
				printf("You can't access %s.\n", file1_name);
				goto END1;
			}
		}
		else
			push_file(file1_name, curr_address, p->name, c_time_string, c_time_string, 3);
		FILE *pointer2;
		FILE *pointer1;
		pointer1 = fopen(file1_name, "a");
		pointer2 = fopen(file2_name, "r");
		if (pointer2 == NULL)
			fprintf(pointer1, file2_name);
		else {
			search_file(file2_name, curr_address);
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcpy(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
			}
			else {
				printf("You can't access %s.\n", file2_name);
				goto END;
			}
			while (!feof(pointer2)) {
				fgets(temp1, 200, pointer2);
				fprintf(pointer1, temp1);
			}
			fclose(pointer2);
		}
		fclose(pointer1);
	END1:writeintofile1("file root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "cat") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		FILE *pointer3;
		pointer3 = fopen(state_name, "r");
		if (pointer3 == NULL)
			printf("This file does't exist.\n");
		else {
			getcwd(curr_address, 200);
			search_file(state_name, curr_address);
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
			}
			else {
				printf("You can't access %s.\n", state_name);
				goto END2;
			}
			while (!feof(pointer3)) {
				fgets(temp1, 200, pointer3);
				if (temp1 != NULL)
					fprintf(stdout, temp1);
				memset(temp1, NULL, sizeof(temp1));
			}
			printf("\n");
		}
	END2:writeintofile1("file root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "rm") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		getcwd(curr_address, 200);
		if (search_file(state_name, curr_address) == 1) {
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
			}
			else {
				printf("You can't access %s.\n", state_name);
				goto END3;
			}
		}
		else {
			printf("This file does't exist.\n");
			goto END3;
		}
		a = remove(state_name);
		delete_file();
	END3:writeintofile1("file root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "cp") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		strcpy(file1_name, strtok(state_name, " "));
		strcpy(file2_name, strtok(NULL, " "));
		getcwd(curr_address, 200);
		if (search_file(file1_name, curr_address) == 1) {
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
			}
			else {
				printf("You can't access %s.\n", file1_name);
				goto END4;
			}
		}
		else {
			printf("This file doesn't exist.\n");
			goto END4;
		}
		FILE *pointer4, *pointer5;
		pointer4 = fopen(file1_name, "r");
		pointer5 = fopen(file2_name, "w");
		while (!feof(pointer4)) {
			fgets(temp1, 200, pointer4);
			fprintf(pointer5, temp1);
		}
		fclose(pointer4);
		fclose(pointer5);
		push_file(file2_name, curr_address, p->name, c_time_string, c_time_string, p_file->access);
	END4:writeintofile1("file root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "mv") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		strcpy(file1_name, strtok(state_name, " "));
		strcpy(file2_name, strtok(NULL, " "));
		getcwd(curr_address, 200);
		if (search_file(file1_name, curr_address) == 1) {
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
			}
			else {
				printf("You can't access %s.\n", file1_name);
				goto END5;
			}
		}
		else {
			printf("This file doesn't exist.\n");
			goto END5;
		}
		FILE *pointer6, *pointer7;
		pointer6 = fopen(file1_name, "r");
		pointer7 = fopen(file2_name, "w");
		while (!feof(pointer6)) {
			fgets(temp1, 200, pointer6);
			fprintf(pointer7, temp1);
		}
		fclose(pointer6);
		push_file(file2_name, curr_address, p->name, c_time_string, c_time_string, p_file->access);
		remove(file1_name);
		delete_file();
		fclose(pointer7);
	END5:writeintofile1("file root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "ls") == 0) {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		system("dir");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "exif") == 0) {
		getcwd(curr_address, 200);
		if (search_file(state_name, curr_address) == -1)
			printf("This file doesn't exist.\n");
		else
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				printf("file name: %s\n", p_file->name);
				printf("address: %s\n", p_file->address);
				printf("creator: %s\n", p_file->creator);
				printf("last access time: %s\n", p_file->last_access);
				printf("last change time: %s\n", p_file->last_change);
			}
			else
				printf("You can't access this file.\n");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "filechmode") == 0) {
		getcwd(curr_address, 200);
		if (search_file(state_name, curr_address) == -1)
			printf("This file doesn't exist.\n");
		else {
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				printf("Enter new access for this file(1 for admin, 2 for creator, 3 for everybody): ");
				scanf("%d", &p_file->access);
				getchar();
			}
			else
				printf("You can't access this file");
		}
		writeintofile1("file root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "dirchmode") == 0) {
		getcwd(curr_address, 200);
		chdir(state_name);
		getcwd(address, 200);
		if (search_dir(address) == 1) {
			if (p_dir->access == 1 && p->access == 1 || p_dir->access == 2 && strcmp(p->name, p_dir->creator) == 0 || p_dir->access == 3) {
				printf("Enter new access for this directory(1 for admin, 2 for creator, 3 for everybody): ");
				scanf("%d", &p_dir->access);
				getchar();
			}
			else
				printf("You can't access this directory.\n");
		}
		else
			printf("This directory doesn't exist.\n");
		chdir(curr_address);
		writeintofile2("dir root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "help") == 0) {
		getcwd(curr_address, 200);
		chdir(root_address);
		FILE *pointer8;
		pointer8 = fopen("help.txt", "r");
		fgets(temp1, 300, pointer8);
		while (!feof(pointer8))
		{
			printf("%s", temp1);
			fgets(temp1, 300, pointer8);
		}
		chdir(curr_address);
		print();
		strcpy(statement, "");
		strcpy(state_name, "");

	}
	else if (strcmp(statement, "wc") == 0) {
		i = 0, j = 0;
		getcwd(curr_address, 200);
		if (search_file(state_name, curr_address) == 1) {
			if (p_file->access == 1 && p->access == 1 || p_file->access == 2 && strcmp(p->name, p_file->creator) == 0 || p_file->access == 3) {
				strcpy(p_file->last_access, c_time_string);
			}
			else {
				printf("You can't access %s.\n", state_name);
				goto END6;
			}
		}
		else {
			printf("This file does't exist.\n");
			goto END6;
		}
		pointer = fopen(state_name, "r");
		i++;
		fgets(temp1, 200, pointer);
		while (!feof(pointer)) {
			fgets(temp1, 200, pointer);
			i++;
		}
		rewind(pointer);
		fscanf(pointer, "%s", temp1);
		j++;
		while (!feof(pointer)) {
			fscanf(pointer, "%s", temp1);
			j++;
		}
		printf("The number of words is : %d\nthe number of sentences is : %d\n", j, i);
	END6:print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "clear") == 0) {
		system("Cls");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "searchfile") == 0) {
		i = 0;
		printf("Enter filename to search: ");
		gets_s(name);
		for (temp_file = head_file; temp_file != NULL; temp_file = temp_file->ptr)
			if (strcmp(temp_file->name, name) == 0) {
				printf("%s\n", temp_file->address);
				i++;
			}
		if (i == 0)
			printf("This file doesn't exist.\n");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else if (strcmp(statement, "searchdir") == 0) {
		i = 0;
		printf("Enter directoryname to search: ");
		gets_s(name);
		for (temp_dir = head_dir; temp_dir != NULL; temp_dir = temp_dir->ptr)
			if (strcmp(temp_dir->name, name) == 0) {
				printf("%s\n", temp_dir->address);
				i++;
			}
		if (i == 0)
			printf("This directory doesn't exist.\n");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
	else {
		t1 = clock() - t;
		if ((double)(t1 / CLOCKS_PER_SEC) > p->time) {
			printf("Your time is finished.\n");
			goto LOGIN;
		}
		printf("Error\n");
		p->wrong++;
		writeintofile("user root.txt");
		print();
		strcpy(statement, "");
		strcpy(state_name, "");
	}
}
}