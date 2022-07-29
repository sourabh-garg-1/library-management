//author : sourabh garg

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_YR  9999
#define MIN_YR  1900

typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

/*typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;*/

typedef struct
{
    unsigned int books_id; 
    char bookName[50];
    int issuedst;
    char issuer_Name[30];
    Date issuedDate;
 //   Date returnDate;
} Book;

int isFileExists(const char *path);
void displayBooks();
void addBookInDataBase();
int isNameValid(const char *name);
int  IsLeapYear(int year);
int isValidDate(Date *validDate);
void searchBooks();
void deleteBooks();
void issue_or_return();

int main()
{	
	int choice;
	do
    {
     //   headMessage("MAIN MENU");
        printf("\n\n\n\t\t1.Display Books");
        printf("\n\t\t2.Search Books");
        printf("\n\t\t3.add books");
        printf("\n\t\t4.Delete Book");
        printf("\n\t\t5.issue or return a book");
        printf("\n\t\t0.Exit");
        printf("\n\n\n\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
        	displayBooks();
            break;
        case 2:
         	searchBooks();
            break;
        case 3:
            addBookInDataBase();
            break;
        case 4:
         	deleteBooks();
            break;
        case 5:
     		issue_or_return();
           break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...\n\n");
        }     
		
		printf("\n\n\n\t\t\tPress any key to go to main menu.....");                                      
        getch();
        system("cls");
    }
    while(choice!=0);                                    
	
	return 0;
}

void displayBooks()
{
	int found = 0;
	FILE *fp = fopen("data.txt","r");
	Book addBook = {0};
	if(!isFileExists("data.txt"))
    {
        printf("\n\t\tFile is not opened\n");
        return;
    }
    else
    {
    	printf("\t\tBOOK DETAILS\n\n");
		printf("\tBook id\tBook name\tIssued status\tStudent name\tIssued date\n\n");
    	while(fread(&addBook, sizeof(addBook), 1, fp))
    	{
        	printf("\t%u\t%s\t",addBook.books_id,addBook.bookName);
        	if(addBook.issuedst)
        	{
        		printf("Issued\t\t%s\t",addBook.issuer_Name);
        		printf("\t(%d/%d/%d)\n",addBook.issuedDate.dd,addBook.issuedDate.mm, addBook.issuedDate.yyyy);
        //		printf("\t(%d/%d/%d)\n",addBook.returnDate.dd,addBook.returnDate.mm, addBook.returnDate.yyyy);
        	}
        	else
        	{
        		printf("\tNOT ISSUED\t------\t\t--------\n");
			}
        	found = 1;
    	}
	}
	if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    
}

int isFileExists(const char *path)
{
    FILE *fp = fopen(path, "r");
    int status = 0;
    if (fp != NULL)
    {
        status = 1;
        fclose(fp);
    }
    return status;
}

void addBookInDataBase()
{
	int status = 0;
	FILE *fp = NULL;
	Book addBook = {0};
	if(!isFileExists("data.txt"))
		fp = fopen("data.txt","w+");
	else
		fp = fopen("data.txt","a+");
	
	if(fp == NULL)
    {
        printf("File is not opened\n");
        return;
    }
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\tBook ID NO  = ");
    fflush(stdin);
    scanf("%u",&addBook.books_id);
    
	do
    {
        printf("\n\t\tBook Name  = ");
        fflush(stdin);
        scanf("%s",addBook.bookName);
  //      fgets(addBook.bookName,50,stdin);
        status = isNameValid(addBook.bookName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    
    fflush(stdin);
	printf("\t\tIssued status(0 or 1) : ");
    scanf("%d",&addBook.issuedst);
    
    if(addBook.issuedst)
    {
    	do
   	 	{
        	printf("\t\tIssuer name : ");
        	fflush(stdin);
        	scanf("%s",addBook.issuer_Name);
  //      	fgets(addBook.issuer_Name,30,stdin);
        	status = isNameValid(addBook.issuer_Name);
        	if (!status)
        	{
        	    printf("\n\t\t\tName contain invalid character. Please enter again.");
        	}
    	}
    	while(!status);
    	do
    	{
        	printf("\n\t\t\tEnter issued date in format (day/month/year): ");
        	scanf("%d/%d/%d",&addBook.issuedDate.dd,&addBook.issuedDate.mm,&addBook.issuedDate.yyyy);
        	status = isValidDate(&addBook.issuedDate);
        	if (!status)
        	{
        	    printf("\n\t\t\tPlease enter a valid date.\n");
        	}
    	}	
    	while(!status);	
	}
	else{
		addBook.issuer_Name[0] = 'a';
		addBook.issuedDate.dd = 1; addBook.issuedDate.mm=1; addBook.issuedDate.yyyy = 1901;
	}
	fwrite(&addBook,sizeof(addBook), 1, fp);
    fclose(fp);

}

int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}

int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}

void searchBooks()
{
	int found = 0;
    char bookName[50] = {0};
    Book addBook = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen("data.txt","r");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        return;
    }
    
    printf("\n\n\t\tEnter Book Name to search:");
    fflush(stdin);
    scanf("%s",bookName);
    while (fread (&addBook, sizeof(addBook), 1, fp))
    {
        if(!strcmp(addBook.bookName, bookName))
        {
            found = 1;
            break;
        }
    }
    
    if(found)
    {
        printf("\n\tBook id\tBook name\tIssued status\tStudent name\tIssued date\n\n");
        printf("\t%u\t%s\t",addBook.books_id,addBook.bookName);
        if(addBook.issuedst)
        {
        	printf("Issued\t\t%s",addBook.issuer_Name);
        	printf("\t\t(%d/%d/%d)\n",addBook.issuedDate.dd,addBook.issuedDate.mm, addBook.issuedDate.yyyy);
        //	printf("\t(%d/%d/%d)\n",addBook.returnDate.dd,addBook.returnDate.mm, addBook.returnDate.yyyy);
        }
        else
        {
        	printf("\tNOT ISSUED\t------\t\t--------\n");
		}	 	
	}
	 else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
}

void deleteBooks()
{
    int found = 0;
    int bookDelete = 0;
    char bookName[50] = {0};
    Book addBook = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    fp = fopen("data.txt","r");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        return;
    }
    tmpFp = fopen("tmp.txt","w");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        return;
    }
    printf("\n\n\t\tEnter Book Name to delete:");
    fflush(stdin);
    scanf("%s",bookName);
    
    while (fread (&addBook, sizeof(addBook), 1, fp))
    {
        if(strcmp(addBook.bookName, bookName))
        {
        	fwrite(&addBook,sizeof(addBook), 1, tmpFp);
        }
        else
        {
        	found = 1;
		}
    }
    (found)? printf("\n\t\tRecord deleted successfully....."):printf("\n\t\tRecord not found");
    
    fclose(fp);
    fclose(tmpFp);
    remove("data.txt");
    rename("tmp.txt","data.txt");  
}

void issue_or_return()
{
	int found = 0, ch;
	int status = 0, fine =0, date_diff=0, mon_diff=0, year_diff = 0;
	Date returndate;
    char bookName[50] = {0};
    Book addBook = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    fp = fopen("data.txt","r");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        return;
    }
    tmpFp = fopen("tmp.txt","w");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        return;
    }
    
    
	printf("\n\t\t1. issue a book \n\t\t2. return a book\n\t\t0. return to main menu\n");
	printf("\t\tenter your choice  : ");
	scanf("%d",&ch);
	
	if(ch == 1)
	{
		int flag=0;
		printf("\t\tenter the book to be issued : ");
		fflush(stdin);
		scanf("%s",bookName);
	 	while (fread (&addBook, sizeof(addBook), 1, fp))
    	{
    	    if(!strcmp(addBook.bookName, bookName))
    	    {
    	    	if(addBook.issuedst == 1)
        		{
        			flag = 1;
				}
				else
				{	
        			addBook.issuedst = 1;
        			do
   	 				{
        				printf("\t\tIssuer name : ");
        				fflush(stdin);
        				scanf("%s",addBook.issuer_Name);

        				status = isNameValid(addBook.issuer_Name);
        				if (!status)
        				{
        				    printf("\n\t\tName contain invalid character. Please enter again.");
        				}
    				}
    				while(!status);
    				
        			do
    				{	
        				printf("\n\t\tEnter issued date in format (day/month/year): ");
        				scanf("%d/%d/%d",&addBook.issuedDate.dd,&addBook.issuedDate.mm,&addBook.issuedDate.yyyy);
        				status = isValidDate(&addBook.issuedDate);
        				if (!status)
        				{
        				    printf("\n\t\tPlease enter a valid date.\n");
        				}
    				}			
    				while(!status);
    				found = 1;
       	 		}			
        	}
        	fwrite(&addBook,sizeof(addBook), 1, tmpFp);
        }
        	if(flag)
        	{
        		printf("\n\t\tBook already issued !!");
			}
			else{
				(found)? printf("\n\t\tBook issued successfully....."):printf("\n\t\tRecord not found");
			}
    		fclose(fp);
    		fclose(tmpFp);
    		remove("data.txt");
    		rename("tmp.txt","data.txt");
    		return;
	}
	else if(ch==2)
	{
		printf("\t\tenter the book to be returned : ");
		fflush(stdin);
		scanf("%s",bookName);
		
		while (fread (&addBook, sizeof(addBook), 1, fp))
    	{
    	    if(!strcmp(addBook.bookName, bookName))
    	    {
        		int st=1;
        		label:
        		do{
        			printf("\n\t\tEnter return date in format (day/month/year): ");
        			scanf("%d/%d/%d",&returndate.dd,&returndate.mm,&returndate.yyyy);
        			status = isValidDate(&addBook.issuedDate);
        			if (!status)
        			{
        			    printf("\n\t\tPlease enter a valid date.\n");
        			}
    			}		
    			while(!status);
        		
        		if(returndate.yyyy<addBook.issuedDate.yyyy) {
        			st = 0;
        		}
				else if(returndate.yyyy == addBook.issuedDate.yyyy)
				{
					if(returndate.mm<addBook.issuedDate.mm) {
						st = 0;
					}
					else if(returndate.mm==addBook.issuedDate.mm){
						if(returndate.dd<addBook.issuedDate.dd){
							st = 0;	
						}
					}	
				}
				if(!st){
					printf("\n\t\t\tPlease enter a valid  return date.\n");
					goto label;
				}
				else{
					int total_diff=0;
					date_diff = returndate.dd - addBook.issuedDate.dd;
					mon_diff = returndate.mm - addBook.issuedDate.mm;
					year_diff = returndate.yyyy - addBook.issuedDate.yyyy;
					if(date_diff<0)
					{
						date_diff = date_diff + 30;
						mon_diff = mon_diff -1;
					}
					if(mon_diff<0)
					{
						mon_diff = mon_diff + 12;
						year_diff = year_diff - 1;
					}
					total_diff = date_diff + (mon_diff *30) + (year_diff*365);
					if(total_diff <=7)
					{
						printf("\n\t\tyour fine : Nil \n");
					}
					else if(total_diff>7 && total_diff<30)
					{
						fine = total_diff-7;
						printf("\n\t\tyour fine : Rs. %d",fine);
					}
					else{
						fine = 100;
						printf("\n\t\tyour fine : Rs. %d",fine);
					}
					printf("\n\t\tenter any key after paying the fine => ");
					getch();
				}
				
        		addBook.issuedst = 0;
        		addBook.issuer_Name[0] = 'a';
				addBook.issuedDate.dd = 1; addBook.issuedDate.mm=1; addBook.issuedDate.yyyy = 1901;
        		found = 1;
			}
				fwrite(&addBook,sizeof(addBook), 1, tmpFp);
    	}
		(found)? printf("\n\t\tBook returned successfully....."):printf("\n\t\tRecord not found");
    	fclose(fp);
    	fclose(tmpFp);
    	remove("data.txt");
    	rename("tmp.txt","data.txt"); 
		return;	
	}
	else if(ch ==0)
	{
		return;
	}
	else{
		printf("\n\t\tenter a valid choice!!");
		return;
	}
}

