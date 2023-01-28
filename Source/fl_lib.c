#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#include "D:\Code\Tasks\Make_Note\Includes\fl_lib.h"



static char * add_suffix(const char *fname)
{
	int fn_length, suf_length, full_length;
	char * name_suffix;
	char suffix[] = ".txt";
	fn_length = strlen(fname);
	suf_length = strlen(suffix);
	full_length = fn_length + suf_length + 1;

#ifdef DEBUG
	printf(N_("Length of filename = %d, suffix = %d, full length = %d", fn_length, suf_length, full_length));
#endif

	name_suffix = malloc(full_length * sizeof(char));
	strcpy(name_suffix, fname);
	strcpy(&name_suffix[fn_length], suffix);
	
	name_suffix[full_length-1] = '\0';

#ifdef DEBUG
	printf(N_("For returning: filename = %s\n", name_suffix));
#endif

	return name_suffix;
}



int mk_file(const char *file_name)
{

	char *new_file_name;

#ifdef DEBUG
	printf(N_("Function mk_file is called\n"));
#endif
	if (!file_name)
	{
		// printf(_("Void filename\n"));
		printf("Void filename\n");
		return -1;
	}
	FILE* new_file;

	new_file_name = add_suffix(file_name);

#ifdef DEBUG
	printf(N_("It is the argument of fopen: %s\n", new_file_name));
#endif

	new_file = fopen(new_file_name, "wb+");
#ifdef DEBUG
	printf(N_("Address of stream = %p\n", new_file));
#endif

	if(!new_file)
		{
#ifdef DEBUG
			printf(N_("Function mk_file can not make your file\n"));
#endif
			perror(new_file_name);//Diagnosic info into stderror
			//fprintf(stderr, "%s\n", stderror(errno));
			return -2;
		}
	fclose(new_file);

#ifdef DEBUG
	printf(N_("Function mk_file closed %s file\n", new_file_name));
#endif
	return 0;
}

int addin_file(const char *file_name, const char *new_txt_line)
{
#ifdef DEBUG
	printf(N_("Function addin_file is called\n"));
#endif
	FILE* file_for_add;

#ifdef DATA
	long int s_time;
	struct tm *m_time;
	s_time = time(NULL);
	m_time = localtime(&s_time);
#endif

	if ((file_for_add = fopen(add_suffix(file_name), "ab")))
	{
#ifdef DEBUG
		printf(N_("File %s is opened\n", file_name));
#endif

#ifdef DATA
		// fprintf(_(file_for_add, "%d.%02d.%d %02d:%02d:%02d ", m_time->tm_mday, m_time->tm_mon+1, m_time->tm_year+1900, m_time->tm_hour, m_time->tm_min, m_time->tm_sec));
		fprintf(file_for_add, "%d.%02d.%d %02d:%02d:%02d ", m_time->tm_mday, m_time->tm_mon+1, m_time->tm_year+1900, m_time->tm_hour, m_time->tm_min, m_time->tm_sec);
#endif

		fputs(new_txt_line, file_for_add);
		fputc('\n', file_for_add);
		fclose(file_for_add);
		return 0;
	}
	else
	{
		// fputs(_("Error in addin_file().\n", stderr));
		fputs("Error in addin_file().\n", stderr);
		perror(add_suffix(file_name));
		return -1;
	}
}
