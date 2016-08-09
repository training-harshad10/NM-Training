
/*
project    : show n number of toppers where n is user defined .
filename   : high_marks.c
version    : 1.0.10
date       : july 27,2016.

Copyright (c) 2016, Mansi Upadhyaya
All rights reserved

VERSION HISTORY:
----------------
Version : 1
Date : Jul 27,2016
Revised by :Mansi Upadhyaya
Description : Original version.
*/

/**** header file inclusion*****/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

/**** macros declarations *****/

#define FUNCTION_SUCCESS        1                             /* it states that marks are valid       */
#define FUNCTION_ERROR          0                             /* it staes that marks are invalid      */ 
#define RED_COLOR          "\e[0;31m"                         /* it represents the ASCII code of red color */
#define BLACK_COLOR        "\e[0;30m"                         /* it represents the ASCII code of black color */
#define BLUE_COLOR         "\e[0;34m"                         /* it represents the ASCII code of blue  color */ 
#define FILE_NOT_FOUND          2
/***
 it defines the students record structure i.e name and marks 
***/
 
typedef struct stud_mark
{
    char   *stud_name;
    double  marks;
    struct stud_mark *next;
}StudentType;

/**** function declaration ****/
 
char  TakeValues(int );
void SortMarks(int );
char PrintResult(int );
char  CheckForValid(int );
void LogRecords(char[], char[]);
char *  GetTimeStamp(void);
char CheckMark(double );
char InputFromFile(void);

/**** head pointer declaration used with linked list *** */

StudentType *head = NULL;                           /* To store the students records  */
long int Student_count = 0;

void main(int argc, char * argv[])
{
    int  student_no;                               /* it represents the total number of students */
    int  no_highmarks;                             /* it represents the number of toppers that user wants */
    char ret_value;                          /* it checks the whether the students marks are valid */
    char *msg;                                     /* it sets the error message */
    char check_scanf;                              /* it checks whether scanf has accepted a value */
    char input_type;
    char c;
    char *cmd_arg;
    char *arg_cmp;

   // printf("%s %d", argv[1], argc );

    if (argc > 1)
    {  
       cmd_arg = argv[1];
       arg_cmp = "-help";
       
       if(strcmp(cmd_arg, arg_cmp) == 0)
       {  
          FILE *help_file;
          help_file = fopen("help", "r");
         // printf("%s i am here", argv[1]);
          if(help_file == NULL)
          {
             perror("error is:");
          }
          while(!feof(help_file))
          {
               c = fgetc(help_file);
               printf("%c", c);
          }
         
        
          
       }
       exit(0);
    }
 
    printf("Student records are to be taken from file :[Y/N]");
  
    input_type = getchar();
    

    if(toupper(input_type) == 'Y')
    {
       printf("calling input from file");
       ret_value = InputFromFile();
 
      
       
       if(ret_value == FILE_NOT_FOUND);
       {
          msg = "input file not found";
          goto EXIT;
       }

       if(Student_count == 0)
       {
          msg = "input file is empty";
          goto EXIT;
       }
       
       student_no = Student_count;
       
    }
 
    if(toupper(input_type) == 'N')
    {
   
    printf("enter total no of students \n ");


    check_scanf = scanf ("%d", &student_no);

    /* checks whether user has entered the integer value */

    if(check_scanf != 1)
    {
       msg = "enter a stundent number as an integer  ";
       goto EXIT;
    }

    /* to check whether entered data is valid */  

    ret_value = CheckForValid(student_no);

    if(ret_value == FUNCTION_ERROR)
    {
       msg = "enter a valid no of students ";

       goto EXIT;

    } 

    printf("enter total no of topppers \n ");

    check_scanf =  scanf("%d", &no_highmarks);
  
    /*checks whether user has entered the integer value */
      
    if(check_scanf != 1)
    {
       msg = "enter a topper number as an integer  ";

       goto EXIT;
    }

    /* checks whether entered data is valid */

    ret_value =  CheckForValid(no_highmarks);

    if(ret_value == FUNCTION_ERROR)
    {
        msg = "enter a valid no of toppers ";

        goto EXIT;
    }

    /* checks whether no of toppers are lesser than a total student no */ 
 
    if(student_no < no_highmarks)
    {
        msg = " no of topper are greater than a total no of students ";

        goto EXIT;
    }

    printf("enter student records i.e name and marks.\n ");
 
    /* accepts the student data */
  
    ret_value = TakeValues(student_no);
   
    /* checks wether the student data are accepted correctly */
    
    if (ret_value == FUNCTION_ERROR)
    {

        msg = "marks are not valid ";
        
        goto EXIT;
        
    }
 
    }

    else
    {
       msg = "entered option is in correct";
       goto EXIT;
    }
    /* sorts the data according to student's marks */
   
    SortMarks(student_no);

    /* prints the toppers */
    
    ret_value = PrintResult(no_highmarks);

    /* checks whether toppers are printed correctly , if so then log the details in log file */
  
    if(ret_value == FUNCTION_SUCCESS)
    { 
       LogRecords("Info", "   toppers are printed correctly ");
    }

  EXIT:	if(msg != NULL)
        {
           printf("%s %s \n ",RED_COLOR, msg);
           LogRecords("Warning", msg);
           printf("%s", BLACK_COLOR);
           exit(0);
         }
}

/********************************************************
* 
* FUNCTION NAME: TakeValues()
* 
* Description: It takes the student records from user and stores into a linked list.
* 
* ARGUMENTS: student_no
* 
* ARGUMENT        TYPE        DESCRIPTION 
* student_no      int         it represents the total number of students  
* 
* RETURNS: char 
  FUNCTION_SUCCESS: if student data stored correctly
  FUNCTION_ERROR  : if there is an erroe which storing the data
* 
*********************************************************/

char TakeValues (int student_no)
{   
    StudentType *new_node, *current_node;             /* are the pointers used to store the data in linked list */
    char name[100];                                   /* accepts the name from user and store into it temporarily*/
    char *stud_name_buff;                             /* allocates the exact space of the size of the name entered */
    int student_iterator;                             /* is used to iterate through student records */
    double mark;                                      /* accepts the marks from user and store into it temporarily*/
    int check_scanf;                                  /* it checks whether scanf has accepted a value */
    int validate_mark;                                /* is used to check marks whether they are valid */
 
    for (student_iterator=0; student_iterator < student_no; student_iterator++)
    {  
        new_node = (StudentType *) malloc(sizeof(StudentType));

        scanf("%s", name);

        stud_name_buff = (char *) malloc(sizeof(name)+1);

        strcpy(stud_name_buff, name);

        new_node->stud_name = stud_name_buff;

        check_scanf = scanf ("%lf", &mark);
      
        /* checks whether the entered mark is integer */

        if(check_scanf != 1)
        { 
           return FUNCTION_ERROR;
        }
        
        /* checks whether the mark is valid */

        validate_mark = CheckMark(mark);
        
        if(validate_mark == FUNCTION_ERROR)
        {
           return FUNCTION_ERROR;

        }
        
        new_node->marks = mark;

        printf(" \n ");

        new_node->next = NULL;
        
        if(head == NULL)
        {
           head = new_node;   
           current_node = new_node;
  	}
        else
        {
           current_node->next = new_node;
           current_node = new_node;
        }
    }

    return FUNCTION_SUCCESS;

}


char InputFromFile()
{  

   char file_name[50];
   char name[50];
   StudentType *new_node, *current_node;
   double mark;
   FILE *input_file;
   
   printf("enter a file name. \n");
   scanf("%s", file_name);
   printf("%s", file_name);
   input_file = fopen("temp", "r+");
   printf("taking input from file \n");
   
   perror("and the error is");
   
   if(input_file == NULL)
   {
       return FILE_NOT_FOUND; 
   }
   while(feof(input_file))
   {
       printf("i am here");
       new_node = (StudentType *) malloc(sizeof(StudentType));
       fscanf(input_file, "%s %lf \n", name, &mark );
       new_node->marks = mark;
       printf("%lf", new_node->marks);
       new_node->stud_name = (char *) malloc(sizeof(name)+1);
       strcpy(new_node->stud_name, name);
    
       new_node->next = NULL;

       if(head == NULL)
       {
           head = new_node;
           current_node = new_node;
       }
       else
       {
           current_node->next = new_node;
           current_node = new_node;
       }
       
       Student_count++;
 
   }
  
   return FUNCTION_SUCCESS;
   
   
}

/********************************************************
* 
* FUNCTION NAME: SortMarks()
* 
* desciption: it sorts the students records according to marks by sorting in  acsording order with bubble sort
              stored in linked list.
* 
* ARGUMENTS: student_no

* ARGUMENT          TYPE    DESCRIPTION *
* student_no        int     store the total no of student records
* 
* RETURNS: void
* 
*********************************************************/


void SortMarks (int student_no)
{
    int i,j;                                        /* are the indices used for bubble sort */
    int temp_mark;                                  /* stores the mark temporarily (for swapping purpose)*/
    char *temp_name;                                /* stores the student name temprarily (for swapping purpose) */
    StudentType *current , *next, *prev;            /* are the pointers ccreated to sort the marks in linked list */

    current = head; 
    next  = current->next;
    prev = head; 
    
/***
 bubble sort is used to sort the student marks
***/

   for (i=1; i<student_no; i++)
   {  
        current = head;
        next    = current->next;


        while(next != NULL)
        {
            if (current->marks < next->marks)
            {  
               if (current == head)
               {
                  current->next = next->next;
                  next->next = current;
                  head = next;
                  current = next;
                  next = next->next;

               }
               else
               {
                  current->next = next->next;
                  next->next = current;
                  prev->next = next;
                  prev = next;
                  next = current->next;
               }
            }     
            else
            { 
               prev = current;
               current = next;
               next   = next->next;
                        
            }

        }
     
    }
}

/********************************************************
* 
* FUNCTION NAME: PrintResult()
* 
* desciption: it prints the result i.e toppers stored in linked list.
* 
* ARGUMENTS: no_highmarks
* 
* ARGUMENT          TYPE       DESCRIPTION 
* no_highmarks      int        stores number of toppers.
*       
* RETURNS: char
  FUNCTION_SUCCESS: if toppers are printed correctly
  FUNCTION_ERROR  : if toppers are not printed correctly.
* 
*********************************************************/

char PrintResult(int no_highmarks)
{
     int student_iterator;                    /* is used to iterate through student records */
     StudentType *print_topper;               /* pointer used to deal with linked list */
    
     print_topper = head;
 
     printf(" toppers are: \n \n ");
  
     printf("%s", BLUE_COLOR);
 
     for (student_iterator = 0; student_iterator < no_highmarks; student_iterator++)
     { 
          printf("%s \n \n ", print_topper->stud_name);
          print_topper = print_topper->next;
     }

     printf("%s", BLACK_COLOR);
     
     return FUNCTION_SUCCESS;
     
    
}

/********************************************************
* 
* FUNCTION NAME: CheckForValid() 
* 
* DESCRIPTION: it checks whether the entered data is valid.
* 
* ARGUMENTS: student_no
* 
* ARGUMENT        TYPE     DESCRIPTION 
* student_no      int      stores the total number of student records
* 
* RETURNS:  char
  FUNCTION_SUCCESS: if the entered data is valid
  FUNCTION_ERROR  : if entered data is not valid.
* 
*********************************************************/

char CheckForValid (int check_term)
{
   if(check_term < 0)
   { 
     return FUNCTION_ERROR;
   }
   else
   {
     return FUNCTION_SUCCESS;
   } 
}

/********************************************************
*
* FUNCTION NAME: LogRecords()
*
* DESCRIPTION: it logs the entry into a file.
*
* ARGUMENTS: void
*
* ARGUMENT        TYPE     DESCRIPTION
* 
* RETURNS:   void
*
*********************************************************/

void LogRecords(char log_type[30], char log_description[100])
{
   FILE *checkfile_log;                       /* creates a pointer to a file */
   char *time_stamp;                          /* stores a timestamp */
   int i;
   int index;
   char buff[200], index_strn[30];                          

   checkfile_log = fopen("log.txt", "a+");

   time_stamp = GetTimeStamp();

   fseek(checkfile_log, 0, SEEK_END); 
 
   if(ftell(checkfile_log) == 0)
   { 
      fprintf(checkfile_log, "index \t\t  timestamp \t\t\t\t\t type \t\t\t Description \n");
      fprintf(checkfile_log, "%d    \t\t  %s                        %s \t\t   %s \n", 1, time_stamp, log_type, log_description) ;
   }

   else
   { 
      fseek(checkfile_log, 0, SEEK_SET);

      while(fscanf(checkfile_log, "%[^\n]\n", buff) > 0)
      {
        fscanf(checkfile_log, "%[^\n]\n", buff);  
      }

      for(i=0; buff[i] != ' '; i++)
      {
         index_strn[i] = buff[i];
 
      }

      index_strn[i] = '\0';

      index = atoi(index_strn);        

      fprintf(checkfile_log, "%d   \t\t %s                          %s           %s \n", ++index,  time_stamp, log_type, log_description);

   } 
}

/********************************************************
*
* FUNCTION NAME: GetTimeStamp()
*
* DESCRIPTION: it returns the timestamp.
*
* ARGUMENTS: void
*
* ARGUMENT    TYPE     DESCRIPTION
*
* RETURNS:   char *    (a pointer to a string carrying timestamp)
*
*********************************************************/


char * GetTimeStamp(void)
{ 
  time_t current_time;
  struct tm *loc_time;
  char   *time_stamp; 

  time_stamp = malloc(sizeof(50));

  current_time = time(NULL);
  
  loc_time = localtime(&current_time);

  strftime(time_stamp, 80, "%d %B %Y %X", loc_time );

  return time_stamp;

}


char CheckMark(double  mark)
{
   if (0 > mark || mark > 100 )
   {
      return FUNCTION_ERROR;
   }
   else
   {
      return FUNCTION_SUCCESS;
   }
}

