/*
mknote.c is used to make a short .txt file and write some text in it.
It helps you make quick notes. Usage:
mknote -fn "file name" -ad "some text"
If a name of file is not given, it will be named "readme.txt" or "readme(N).txt".
Ih you don't enter a text of notes the program will make new file only.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
//#include <libintl.h>
#include "D:\Code\Tasks\Make_Note\Includes\fl_lib.h"
#include "D:\Code\Tasks\Make_Note\Source\fl_lib.c"

//#define DEBUG

// #define LOCALEBASEDIR "."
// #define TEXTDOMAIN "mknote"

// #define _(STR) gettext(STR)
// #define N_(STR) (STR)


#define DATA
#define STR_FILE_NAME_FLAG "-fn"
#define ADD_NOTE_FLAG "-ad"


							/*Global variables and types*/
enum state_lst { no_args, no_file_name, no_note, incorrect_input, file_and_note } state;



							/*Functions prototypes*/
enum state_lst check_input(char const *argv[]);
void printhelp(void);



									/*Code*/
int main(int argc, char const *argv[])
{
	//setlocale(LC_CTYPE, "");
	//setlocale(LC_MESSAGES, "");
	//bindtextdomain(TEXTDOMAIN, LOCALEBASEDIR);
	//textdomain(TEXTDOMAIN);


	char default_file_name_arr[] = "note";
	state = check_input(&argv[0]);// Getting console args and analize it 

	switch(state)//Run in choosen mode
	{
		case no_args:
#ifdef DEBUG
			//printf(N_("Case no_args is choosen\n"));
			printf("Case no_args is choosen\n");
#endif
			printhelp();
			break;
		case no_file_name:
#ifdef DEBUG
			// printf(N_("Case no_file_name is choosen\n"));
			printf("Case no_file_name is choosen\n");
#endif
			addin_file(default_file_name_arr, argv[2]);
			break;
		case no_note:
#ifdef DEBUG
			// printf(N_("Case no_note is choosen\n"));
			printf("Case no_note is choosen\n");
#endif
			mk_file(argv[2]);
			break;
		case incorrect_input:
#ifdef DEBUG
			// printf(N_("Case incorrect_input is choosen\n"));
			printf("Case incorrect_input is choosen\n");
#endif
			printhelp();
			break;
		case file_and_note:
#ifdef DEBUG
			// printf(N_("Case file_and_note is choosen\n"));
			printf("Case file_and_note is choosen\n");
#endif
			addin_file(argv[2], argv[4]);
			break;
	}
	return 0;
}


enum state_lst check_input(char const *argv[])
{
	int args_num = 1;
	if(!(argv[args_num])) return no_args;

	if (!strcmp(argv[args_num], STR_FILE_NAME_FLAG))	//if argv[1] == file_name_flag
	{

#ifdef DEBUG
		// printf(N_("Args[1] = flag name of file\n"));
		printf("Args[1] = flag name of file\n");
#endif
		args_num++;//args_num==2


		if(!(argv[args_num]))   //if first argument is file_name_flag, but second one == NULL
		{
#ifdef DEBUG
			// printf(N_("Args[2] is NULL\n"));
			printf("Args[2] is NULL\n");
#endif
			return incorrect_input;
		}

		if(!strcmp(argv[args_num], ADD_NOTE_FLAG))   //if first argument is file_name_flag, but second one == add_note_flag
		{
#ifdef DEBUG
// 			printf(N_("Args[2] is not a name of a file\n"));
			printf("Args[2] is not a name of a file\n");
#endif
			return incorrect_input;
		}

#ifdef DEBUG
			// printf(N_("Args[2] is correct name of a file\n"));
			printf("Args[2] is correct name of a file\n");
#endif


		args_num++;//args_num==3
		if(!(argv[args_num]))
		{
#ifdef DEBUG
			// printf(N_("Args[3] is NULL\n"));
			printf("Args[3] is NULL\n");
#endif
			return no_note;
		}

		else if (strcmp(argv[args_num], ADD_NOTE_FLAG))
		{
#ifdef DEBUG
			// printf(N_("Args[3] is not NULL or flag ADD_NOTE\n"));
			printf("Args[3] is not NULL or flag ADD_NOTE\n");
#endif
			return incorrect_input;	
		}
		
#ifdef DEBUG
		// printf(N_("Args[3] is flag ADD_NOTE\n"));
		printf("Args[3] is flag ADD_NOTE\n");
#endif
		args_num++;//args_num==4
		if(!(argv[args_num]))
		{
#ifdef DEBUG
			// printf(N_("Args[4] is NULL\n"));
			printf("Args[4] is NULL\n");
#endif
			return incorrect_input;
		} else
		{
			return file_and_note;
		}
	}
	else if (!strcmp(argv[args_num], ADD_NOTE_FLAG))
	{
#ifdef DEBUG
		// printf(N_("Args[1] is flag ADD_NOTE\n"));
		printf("Args[1] is flag ADD_NOTE\n");
#endif
		args_num++;//args_num==2
		if(!(argv[args_num]))
		{
#ifdef DEBUG
			// printf(N_("Args[2] is NULL\n"));
			printf("Args[2] is NULL\n");
#endif
			return incorrect_input;
		}
		else return no_file_name;
	} else
	{
#ifdef DEBUG
		// printf(N_("Args[1] is not a flag at all!\n"));
		printf("Args[1] is not a flag at all!\n");
#endif
		return incorrect_input;	
	}
}


void printhelp(void)
{
#ifdef DEBUG
	printf(_("\t\t\t***\nIt is a help text\n\t\t\t***\n"));
#else
	// puts(N_("\n\t\t\t* * * * *\n"));
	// puts(_("mknote.c is used to make a short .txt file and write some text in it.\n"));
	// puts(_("It helps you make quick notes. Usage:\n"));
	// puts(_("mknote -fn \"file name\" -ad \"some text\"\n"));
	// puts(_("If a name of file is not given, it will be named by default.\n"));
	// puts(_("If you don't enter a text of notes the program will make new file only.\n"));
	// puts(N_("\t\t\t* * * * *\n"));
	puts("\n\t\t\t* * * * *\n");
	puts("mknote.c is used to make a short .txt file and write some text in it.\n");
	puts("It helps you make quick notes. Usage:\n");
	puts("mknote -fn \"file name\" -ad \"some text\"\n");
	puts("If a name of file is not given, it will be named by default.\n");
	puts("If you don't enter a text of notes the program will make new file only.\n");
	puts("\t\t\t* * * * *\n");
#endif
}