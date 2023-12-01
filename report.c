#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct StudentInfo
{
    char ID[10];
    char Name[20];
    char Email[30];
    char Phone[20];   
    char marks[100];
};

struct Marks{
    char id[10];
    int noOfSub;
    int marks[10];    
};

struct StudentInfo Students[100];
struct Marks marks[100];


// some global variables
int i,j;
int TotalStudents = 0;
char StudentID[10];
FILE *AllStudents;
FILE *ExistingAllStudents;
FILE *TempAllStudents;
// end

bool IsRunning = true;
void Menu();
void AddNewStudent();
void ShowAllStudents();
int  SearchStudent(char StudentID[10]);
int EditStudent(int StudentFoundIndex);
void DeleteStudent(int StudentIndex);
void DeleteAllStudents();
int  IsAlreadyExists(char GivenLine[30],char InfoType, char StudentID[300]);
void ErrorAndRestart(char *Error[100]);

void DeleteStudentByIndex(int CourseIndex);
void GoBackOrExit();
void ExitProject();
void generateRecord(int index);

int main()
{

    while(IsRunning)
    {
        Menu();
        int Option;
        scanf("%d",&Option);
        switch(Option)
        {
        case 0:
            IsRunning = false;
            ExitProject();
            break;
        case 1:
            system("cls");
            printf("\n\t\t **** Add A New Student ****\n\n");
            AddNewStudent();
            GoBackOrExit();
            break;
        case 2:
            system("cls");
            printf("\n\t\t **** All Students ****\n\n");
            ShowAllStudents();
            GoBackOrExit();
            break;
        case 3:
        {
            system("cls");
            printf("\n\t\t **** Search Students ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int IsFound = SearchStudent(StudentID);
            if(IsFound<0)
            {
                printf(" No Student Found\n\n");
            }
            printf("\n");
            GoBackOrExit();
            break;
        }
        case 5:            
            system("cls");
            printf("\n\t\t **** Generate Report****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int SFI= SearchStudent(StudentID);

            if(SFI >=0)
            {                                 
                generateRecord(SFI);
            }
            if(1==1){}
            else
            {
                printf(" No Student Found\n\n");
            }
            GoBackOrExit();
            break;
            
        case 4:
            system("cls");
            printf("\n\t\t **** Edit a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int StudentFoundIndex = SearchStudent(StudentID);

            if(StudentFoundIndex>=0)
            {
                EditStudent(StudentFoundIndex);
            }
            else
            {
                printf(" No Student Found\n\n");
            }
            GoBackOrExit();
            break;
        case 6:
            system("cls");
            printf("\n\t\t **** Delete a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);

            int DeleteStudentFoundIndex = SearchStudent(StudentID);

            if(DeleteStudentFoundIndex>=0)
            {
                char Sure = 'N';
                getchar();
                printf("\n\n");
                printf(" Are you sure want to delete this student? (Y/N): ");
                scanf("%c",&Sure);

                if(Sure == 'Y' || Sure == 'y')
                {
                    DeleteStudent(DeleteStudentFoundIndex);
                }
                else
                {
                    printf(" Your Data is Safe.\n\n");
                    GoBackOrExit();
                }

            }
            else
            {
                printf(" No Student Found\n\n");
                GoBackOrExit();
            }

            break;
        case 7:
        {
            char Sure = 'N';
            getchar();
            system("cls");
            printf("\n\t\t **** Delete ALL Students ****\n\n");

            printf(" Are you sure want to delete all the students? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y')
            {
                DeleteAllStudents();
            }
            else
            {
                printf(" Your Data is Safe.\n\n");
                GoBackOrExit();
            }
            break;
        }
        
        default:
            ExitProject();
            break;
        }
    }

    return 0;
} // end main function

void Menu()
{
    printf("\n\n\t***Student Management System Using C***\n\n");
    printf("\t\t\tMAIN MENU\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Add A New student.\n");
    printf("\t\t[2] Show All students.\n");
    printf("\t\t[3] Search A student.\n");
    printf("\t\t[4] Edit A student.\n");
    printf("\t\t[5] Generate Report.\n");
    printf("\t\t[6] Delete A student.\n");
    printf("\t\t[7] Delete All students.\n");      
    printf("\t\t[9] Exit the Program.\n");
    printf("\t\t=======================\n");
    printf("\t\tEnter The Choice: ");
} // end menu

void AddNewStudent()
{
    char StudentID[300];
    char Name[300];
    char Phone[300];
    char Email[300];
    int noOfSub = 0;
    
    int IsValidID = 0;
    while(!IsValidID)
    {
        printf(" Enter The ID: ");
        scanf("%s",&StudentID);
        if(IsAlreadyExists(StudentID,'i',StudentID) > 0)
        {
            printf(" Error: This ID is already exists.\n\n");
            IsValidID = 0;
        }
        else if(strlen(StudentID) > 10)
        {
            printf(" Error: ID can not be more than 10 characters.\n\n");
            IsValidID = 0;
        }
        else if(strlen(StudentID) <= 0)
        {
            printf(" Error: ID can not be empty.\n\n");
            IsValidID = 0;
        }
        else
        {
            IsValidID = 1;
        }
    }

    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Enter The Name: ");
        scanf(" %[^\n]s",&Name);
        if(strlen(Name) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        if(strlen(Name) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" Enter The Email: ");
        scanf("%s",&Email);
        if(IsAlreadyExists(Email,'e',StudentID) > 0)
        {
            printf(" This Email is Already Exists.\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) <= 0)
        {
            printf(" Error: Email can not be empty.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" Enter The Phone: ");
        scanf("%s",&Phone);
        if(IsAlreadyExists(Phone,'p',StudentID) > 0)
        {
            printf(" This Phone Number is Already Exists\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) <= 0)
        {
            printf(" Error: Phone can not be empty.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }
    
    
    printf(" Enter No. of Subjects : ");
    scanf("%d",&noOfSub);  
    marks[TotalStudents].noOfSub = noOfSub;   
    
    int total = 0;
    
    for (int j = 0; j < noOfSub; j++) {
        printf("Subject %d: ", j + 1);
        int m = 0;
        scanf("%d", &m);
        
        marks[TotalStudents].marks[j] = m;  
        total = total+m;
    }  
        
    float avg = total/noOfSub;
    char avgMarks[20];
    
    sprintf(avgMarks,"%.1f%%",avg);            
    strcpy(Students[TotalStudents].marks,avgMarks);     
    strcpy(marks[TotalStudents].id,StudentID);       
    strcpy(Students[TotalStudents].ID,StudentID);
    strcpy(Students[TotalStudents].Name,Name);
    strcpy(Students[TotalStudents].Phone,Phone);
    strcpy(Students[TotalStudents].Email,Email);        
    
   
    //printf("here%s",Students[TotalStudents].marks);
    TotalStudents++;
    printf("\n Student Added Successfully.\n\n");
}

void ShowAllStudents()
{
    printf("|==========|====================|==============================|====================|====================|\n");
    printf("|    ID    |        Name        |            Email             |       Phone        |       Marks        |\n");
    printf("|==========|====================|==============================|====================|====================|\n");
    
    for(i=0; i<TotalStudents; i++)
    {
        printf("|");
        printf("%s",Students[i].ID);
        for(j=0; j < (10-strlen(Students[i].ID)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Name);
        for(j=0; j < (20-strlen(Students[i].Name)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Email);
        for(j=0; j < (30-strlen(Students[i].Email)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Phone);
        for(j=0; j < (20-strlen(Students[i].Phone)); j++)
        {
            printf(" ");
        }
        
        printf("|");
        printf("%s",Students[i].marks);
        for(j=0; j < (20-strlen(Students[i].marks)); j++)
        {
            printf(" ");
        }
        
        printf("\n");
        printf("|----------|--------------------|------------------------------|--------------------|--------------------|\n");

    }
    printf("\n");
}

int SearchStudent(char StudentID[10])
{
    system("cls");
    int StudentFoundIndex = -1;

    int i;
    for(i=0; i<TotalStudents; i++)
    {
        if(strcmp(StudentID,Students[i].ID) == 0)
        {
            StudentFoundIndex = i;
            printf("\n One Student Found for ID: %s\n\n",StudentID);
            printf(" Student Informations\n");
            printf("-------------------------\n");

            printf(" ID:    %s\n",Students[i].ID);
            printf(" Name:  %s\n",Students[i].Name);
            printf(" Email: %s\n",Students[i].Email);
            printf(" Phone: %s\n",Students[i].Phone); 
            printf(" percentage : %s\n",Students[i].marks);                 
        }
    }
    
    printf("do you want to show detailed marks Y/N : ");
    char reply[10];
    scanf("%s",&reply); 
    
    if (strcmp(reply,"N") || strcmp(reply,"n"))
    {
        //return StudentFoundIndex;
    }  
        
    if(strcpy(reply,"Y") || strcpy(reply,"y")){
        int size = marks[StudentFoundIndex].noOfSub;
        for (int i=0; i<size; i++){
            printf("subject %d : %d\n",i+1,marks[StudentFoundIndex].marks[i]);
        }
    }    
   
    return StudentFoundIndex;
}

int countDigits(int number) {
    int count = 0;

    while (number != 0) {
        number /= 10;
        ++count;
    }

    return count;
}

void generateRecord(int index){
    FILE *file = fopen("report.txt", "w");   
    
    //int size = marks[0].noOfSub;
    int size = marks[index].noOfSub;
   
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    fprintf(file,"|===================STUDENT RECORD ==================|\n\n");
    
    fprintf(file,"Name : %s\n", Students[index].Name);
    fprintf(file,"Student ID : %s\n",Students[index].ID);
    fprintf(file,"Phone : %s\n",Students[index].Phone);
     fprintf(file,"Email : %s\n\n",Students[index].Email);    
    
    for (int i=0;i<size;i++){
        fprintf(file,"|============");
    }
    fprintf(file,"|\n");
  
      //fprintf(file,"|    sub1    |        sub        |            Email             |       Phone        |       Marks        |\n");
    
    
    for (int i=0; i<size;i++){        
        fprintf(file,"|    Sub%d    ",i+1);        
    }
    fprintf(file,"|\n");
    
    
    for (int i=0;i<size;i++){
        fprintf(file,"|============");
    }
    fprintf(file,"|\n");
    
    int arr[size];
    
    for (int i=0;i<size;i++){
        arr[i] = marks[index].marks[i];
    }
    
    for (int i=0;i<size;i++){        
        int len = countDigits(arr[i]);
        if (len==1){
            fprintf(file,"|    %d       ",arr[i]);
        }
        else if(len==2){
            fprintf(file,"|    %d      ",arr[i]);
        }
        else if(len==3){
            fprintf(file,"|    %d     ",arr[i]);
        }
    }
    fprintf(file,"|\n");
    
    for (int i=0;i<size;i++){
        fprintf(file,"|------------");
    }
    fprintf(file,"|\n");
    
    fclose(file);
    
    printf("\n\n  Report generated successfully \n");
}

int EditStudent(int StudentFoundIndex)
{    
    printf("\n\t\t **** Update The New Student ****\n\n");

    char NewName[300];
    char NewPhone[300];
    char NewEmail[300];
    char StudentID[300];
    strcpy(StudentID, Students[StudentFoundIndex].ID);
    
    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Enter The New Name(0 for skip): ");
        scanf(" %[^\n]s",&NewName);
        if(strlen(NewName) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        else if(strlen(NewName) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" Enter The New Email(0 for skip): ");
        scanf("%s",&NewEmail);

        if(strlen(NewEmail) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else if(strlen(NewEmail) <= 0)
        {
            printf(" Error: Email can not be empty.\n\n");
            IsValidEmail = 0;
        }
        else if(IsAlreadyExists(NewEmail,'e',StudentID) > 0)
        {
            printf(" Error: This Email Already Exists.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" Enter The New Phone(0 for skip): ");
        scanf("%s",&NewPhone);

        if(strlen(NewPhone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = 0;
        }
        else if(strlen(NewPhone) <= 0)
        {
            printf(" Error: Phone can not be empty.\n\n");
            IsValidPhone = 0;
        }
        else if(IsAlreadyExists(NewPhone,'p',StudentID) > 0)
        {
            printf(" Error: This Phone Number is Already Exists.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }
    
    int size = marks[StudentFoundIndex].noOfSub;
    
    int total = 0;
    
    for (int j = 0; j < size; j++) {
        printf("Subject %d(010 for skip): ", j + 1);
        int m = 0;
        scanf("%d", &m);
        
        if (m==010){
            return 0;
        }
        
        marks[TotalStudents].marks[j] = m;  
        total = total+m;
    }  
        
    float avg = total/size;
    char avgMarks[20];    
    
    sprintf(avgMarks,"%.1f%%",avg);            
    strcpy(Students[StudentFoundIndex].marks,avgMarks); 
    
    printf("%f, %s",avg,avgMarks);    
    

    if(strcmp(NewName,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Name,NewName);
    }

    if(strcmp(NewEmail,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Email,NewEmail);
    }

    if(strcmp(NewPhone,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Phone,NewPhone);
    }
    
        // after every delete array index will update (decrease by one)
        // we store the courses sequential
        // so if we know the first course index and total number of course we can delete all
        
    printf(" Student Updated Successfully.\n\n");

}

void DeleteStudent(int StudentIndex)
{    
    struct StudentInfo ThisStudents;
    ThisStudents = Students[StudentIndex];
           
    DeleteStudentByIndex(StudentIndex);
    printf(" Student Deleted Successfully.\n\n");
    GoBackOrExit();
}

void DeleteAllStudents()
{
    TotalStudents = 0;
    printf(" All Students Deleted Successfully.\n\n");
    GoBackOrExit();
}


void DeleteStudentByIndex(int CourseIndex)
{
    int s;
    for(s=0; s<TotalStudents-1; s++)
    {
        if(s>=CourseIndex)
        {
            Students[s] = Students[s+1];
        }
    }
    TotalStudents--;
}


int IsAlreadyExists(char GivenLine[300],char InfoType, char StudentID[300])
{
    int EmailExists = 0;
    int PhoneExists = 0;
    int IDExists = 0;
    int ep;

    for(ep=0; ep<TotalStudents; ep++)
    {
        if(strcmp(GivenLine,Students[ep].ID) == 0)
        {
            IDExists++;
        }
        if(strcmp(GivenLine,Students[ep].Email) == 0 && strcmp(StudentID,Students[ep].ID) != 0 )
        {
            EmailExists++;
        }
        if(strcmp(GivenLine,Students[ep].Phone) == 0 && strcmp(StudentID,Students[ep].ID) != 0)
        {
            PhoneExists++;
        }

    }

    if(InfoType == 'i')
    {
        return IDExists;
    }
    else if(InfoType == 'e')
    {
        return EmailExists;
    }
    else if(InfoType == 'p')
    {
        return PhoneExists;
    }
    else
    {
        return 0;
    }
}

void ErrorAndRestart(char *error[100])
{
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}


void GoBackOrExit()
{
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        ExitProject();
    }
    else
    {
        system("cls");
    }
}

void ExitProject()
{
    system("cls");
    int i;
    char ThankYou[100]     = " ========= Thank You =========\n";
    char SeeYouSoon[100]   = " ========= See You Soon ======\n";
    for(i=0; i<strlen(ThankYou); i++)
    {
        printf("%c",ThankYou[i]);
        Sleep(40);
    }
    for(i=0; i<strlen(SeeYouSoon); i++)
    {
        printf("%c",SeeYouSoon[i]);
        Sleep(40);
    }
    exit(0);
} }
    exit(0);
}