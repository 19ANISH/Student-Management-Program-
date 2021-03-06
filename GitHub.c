#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void insert_record();
void display_record();
void search_record();
void update_record();
void delete_record();
struct student
{
    int roll_num;
    char section[10];
    char name[15];
    char surname[15];
    int marks;
    float grade;
};
    struct student s;
    void main()
    {
        int choice;
        //we take input from user for the function they want to perform
        while(choice!=6)
        {
            printf("\n1. Insert New Record");
            printf("\n2. Display Records");
            printf("\n3. Search For Records");
            printf("\n4. Update Existing Record");
            printf("\n5. Delete Existing Record");
            printf("\n6. Exit Program\n");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                insert_record();
                break;
                case 2:
                display_record();
                break;
                case 3:
                search_record();
                break;
                case 4:
                update_record();
                break;
                case 5:
                delete_record();
                break;
                case 6:
                exit(1);
                default:
                printf("\n Wrong Input.\n Please Retry. \n :)");
            }
            printf("\n Press any Key to Continue\a");
            getche();
        }

    }
    void insert_record()
    {
        display_record();
        FILE *fp;
        fp=fopen("Record.txt","ab+");
        if(fp==NULL)
        {
        printf("\nError In Opening File");
        return;
        }
        printf("\nEnter Name of Student: ");
        scanf("%s",s.name);
        printf("\nEnter Surname of Student: ");
        scanf("%s",s.surname);
        printf("\nEnter Roll Number of Student: ");
        scanf("%d",&s.roll_num);
        printf("\nEnter Class of student: ");
        scanf("%s",s.section);
        printf("\nEnter Marks of Student: ");
        scanf("%d",&s.marks);
        printf("\nEnter Grade of Student: ");
        scanf("%f",&s.grade);
        fwrite(&s,sizeof(s),1,fp);
        {
            printf("\nStudent Record Inserted Successfully");
        }
        fclose(fp);

}
void display_record()
{
    FILE *fp;
    fp=fopen("Record.txt","rb");
    if(fp==NULL)
    {
        printf("\nError In Opening File");
        return;
    }
    printf("\nExisting Records");
    printf("\nRoll Number\tName of Student\t\tClass of Student\tMarks of Student\tGrade of Student");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
    printf("\n%d\t\t%s\t\t\t%s\t\t\t\t%d\t\t\t%f",s.roll_num,s.name,s.section,s.marks,s.grade);
    }
    fclose(fp);
}
void search_record()
{
    display_record();
    int roll,flag=0;
        FILE *fp;
        fp=fopen("Record.txt","rb");
        if(fp==NULL)
        {
            printf("\nError in Opening File");
            return;
        }
        printf("\nEnter Roll Number you wanna search in database:");
        scanf("%d",&roll);
        while(fread(&s,sizeof(s),1,fp)>0&&flag==0)
        {
            if(s.roll_num==roll)
            {
            flag=1;
            printf("\nRoll Number\tName of Student\tClass of Student\tMarks of Student\tGrade of Student");
            printf("\n%d\t%s.%s\t%s\t%d\t%f",s.roll_num,s.name,s.surname,s.section,s.marks,s.grade);
            }
        }
        if(flag==0)
        {
            printf("\n Error: No record found\a");
        }
}
void update_record()
{
    display_record();
    int flag=0;
    char b[15];
    FILE *fp;
    fp=fopen("Record.txt","rb+");
    if(fp==NULL)
    {
        printf("\nError In Opening File");
        return;
    }
    printf("\nEnter Name of Student:");
    scanf("%s",b);
    printf("\nWe Have Previously Stored Data By This Name\n\a");
        while(fread(&s,sizeof(s),1,fp)>0&&flag==0)
        {
            if(strcmp(s.name,b)==0)
            {
                 flag=1;
                    printf("\nEdit Record\n\t\a");
                    fflush(stdin);
                    printf("\nUpdate Student Name:\t\a");
                    scanf("%s",s.name);
                    printf("\nUpdate Student Surname:\a\t");
                    scanf("%s",s.surname);
                    printf("\nUpdate Student Roll Number:\t\a");
                    scanf("%d",&s.roll_num);
                    printf("\nEnter Class of student: ");
                    scanf("%s",s.section);
                    printf("\nUpdate Student Marks:\t\a");
                    scanf("%d",&s.marks);
                    printf("\nUpdate Student Garde:\t\a");
                    scanf("%f",&s.grade);
                    fseek(fp,-(long)sizeof(s),1);
                    fwrite(&s,sizeof(s),1,fp);
                    printf("\nRecord is Updated Successfully");
            }
            if(flag==0)
            {
                printf(" ");
            }

        }
        fclose(fp);
}
void delete_record()
{
    display_record();
    char n[15];
    unsigned flag=0;
    FILE *fp,*ft;
    fp=fopen("Record.txt","rb");
    //ft=fopen("RecordN.txt","ab+");
    if(fp==NULL)
       {
           printf("\nError In Opening File");
           return;
       }
       printf("\nEnter Name of Student:");
       scanf("%s",n);
       ft=fopen("RecordN.txt","ab+");
       while(fread(&s,sizeof(s),1,fp)==1)
        {
            if(strcmp(n,s.name)!=0)
            {
                printf(" ");
                fwrite(&s,sizeof(s),1,ft);
            }
            else
                flag=1;
        }
        if(flag==0)
        {
            printf("\nThere Is No Such Record In System");
        }
        else
        {
            printf("\nRecord Deleted Successfully");
        }
        fclose(fp);
        fclose(ft);
        remove("Record.txt");
        rename("RecordN.txt","Record.txt");
}

