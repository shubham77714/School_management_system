#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void admin_menu(void);
void student_menu(int);
void faculty_menu(void);
void quit(void);
void fac_login(void);
int stu_login(void);

struct marks
{
    float maths;
    float english;
    float hindi;
    float ssc;
    float science;
    float percentage;
};

struct date
{
    int day;
    int month;
    int year;
};

struct student
{
    char name[30];
    int roll;
    char gender;
    char father[30], mother[30];
    int adm_no;
    long long int contact;
    char class[4];
    char address[80];
    struct date dob;
    struct marks term1, term2;
} stu, tstu[50], tmp;

struct staff
{
    char name[30];
    char dept[20];
    char classt[5];
    struct date dob, doj;
    char id[11];

} faculty;
char id[11];
char ct[5];
int ad_no, wopn;

void main(void)
{
    system("cls");
    system("color 8f");
    char choice[10];
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tWELCOME\n");
    printf("\n\n\n\t\tLOGIN AS:\n\t\t\tADMIN\n\t\t\tFACULTY\n\t\t\tSTUDENT\n");
    printf("\n\t\tenter your choice: ");
    scanf("%s", choice);
    if (strcmp(choice, "admin") == 0 || strcmp(choice, "ADMIN") == 0)
        admin_menu();
    else if (strcmp(choice, "faculty") == 0 || strcmp(choice, "FACULTY") == 0)
    {
        fac_login();
        faculty_menu();
    }
    else if (strcmp(choice, "STUDENT") == 0 || strcmp(choice, "student") == 0)
    {
        ad_no = stu_login();
        student_menu(ad_no);
    }
    else
    {
        printf("\a\n\t\tinvalid input.");
        sleep(2);
        int ch;
        printf("\n\t\tenter 1 to try again or 0 to exit : ");
        scanf("%d", &ch);
        if (ch == 1)
            main();
        else
            quit();
    }
}

void create_id(char s[], char d[], int y)
{

    int i, k = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (i == 0 || s[i - 1] == ' ')
        {
            id[k] = s[i];
            k++;
        }
    }
    id[k++] = d[0];
    id[k++] = d[1];
    id[k] = '\0';
    for (i = 0; i < strlen(id); i++)
    {
        if (id[i] >= 97 && id[i] <= 122)
        {
            id[i] -= 32;
        }
    }
    sprintf(id, "%s%d", id, y);
}

void delay(void)
{
    int i = 0;
    for (i = 0; i <= 100000000; i++)
    {
    }
    return;
}

int stu_login(void)
{
    system("cls");
    system("color 8f");
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\tSTUDENT LOGIN WINDOW\n");
    FILE *fr;
    int userid, pass, password;
    int flag = 0;
    printf("\t\tenter userid: ");
    scanf("%d", &userid);
    printf("\t\tenter password: ");
    scanf("%d", &pass);
    fr = fopen("studentdatabase.dat", "rb");
    while (fread(&stu, sizeof(stu), 1, fr) == 1)
    {
        password = 0;
        password = stu.dob.day;
        password = (password * 100) + stu.dob.month;
        password = (password * 10000) + stu.dob.year;
        if ((userid == stu.adm_no) && (pass == password))
        {
            printf("\n\n\t\twelcome");
            int i = 0;
            for (i = 0; i < 5; i++)
            {
                printf(". ");
                delay();
            }
            flag = 1;
            fclose(fr);
            return userid;
        }
    }
    fclose(fr);
    if (flag == 0)
    {
        int choice;
        printf("\a\n\n\t\tincorrect userid or password\n");
    invalid_login:
        printf("\n\t\t1. main menu\n\t\t2. try again.\n\t\t0. exit.\n");
        printf("\n\t\tenter your choice : ");
        scanf("%d", &choice);
        if (choice == 1)
            main();
        else if (choice == 2)
            stu_login();
        else if (choice == 0)
            quit();
        else
        {
            printf("\a\n\n\t\tinvalid choice.\n");
            sleep(2);
            system("cls");
            goto invalid_login;
        }
    }
    return 0;
}

void fac_login(void)
{
    system("cls");
    system("color 8f");
    FILE *fl;
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\tFACULTY LOGIN WINDOW\n");
    printf("\n\n\t\tenter your ID : ");
    scanf("%s", id);
    int flag = 0;
    fl = fopen("teacherdatabase.dat", "rb");
    while (fread(&faculty, sizeof(faculty), 1, fl) == 1)
    {
        strcpy(ct, faculty.classt);
        if (strcmp(id, faculty.id) == 0)
        {
            printf("\n\n\t\twelcome");
            int i = 0;
            for (i = 0; i < 5; i++)
            {
                printf(". ");
                delay();
            }
            flag = 1;
            fclose(fl);
            return;
        }
    }
    fclose(fl);
    if (flag == 0)
    {
        int choice;
        printf("\a\n\n\t\tincorrect ID\n");
    invalid_login:
        printf("\n\t\t1. main menu\n\t\t2. try again.\n\t\t0. exit.\n");
        printf("\n\t\tnenter your choice : ");
        scanf("%d", &choice);
        if (choice == 1)
            main();
        else if (choice == 2)
            fac_login();
        else if (choice == 0)
            quit();
        else
        {
            printf("\a\n\n\t\t\tinvalid choice.\n");
            sleep(2);
            system("cls");
            goto invalid_login;
        }
    }
    return;
}

void add_stu_data(void)
{
    system("cls");
    FILE *fp;
    int choice, rol;
    system("color e0");
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t ADD STUDENT DATA\n");
    fp = fopen("studentdatabase.dat", "ab+");
    fflush(stdin);
    printf("\t\t\tENTER STUDENT DATA:\n");
    printf("\t\troll no. : ");
    scanf("%d", &rol);
    while (fread(&stu, sizeof(stu), 1, fp) == 1)
    {
        if ((rol == stu.roll) && (strcmp(ct, stu.class) == 0))
        {
            printf("\n\t\trecord already exist.\n");
        invalid_add1:
            printf("\n\t\tenter 1 to try again 2 for faculty menu 3 for main menu or 0 for exit: ");
            scanf("%d", &choice);
            if (choice == 1)
                add_stu_data();
            else if (choice == 2)
                faculty_menu();
            else if (choice == 3)
                main();
            else if (choice == 0)
                quit();
            else
            {
                printf("\a\n\n\t\t\tinvalid input.\n");
                sleep(2);
                system("cls");
                goto invalid_add1;
            }
        }
    }
    fflush(stdin);
    printf("\t\tname : ");
    scanf("%[^\n]s", stu.name);
    fflush(stdin);
    strcpy(stu.class, ct);
    stu.roll = rol;
    printf("\t\tadmission no. :  ");
    scanf("%d", &stu.adm_no);
    fflush(stdin);
    printf("\t\tgender(M/F) : ");
    scanf("%c", &stu.gender);
    fflush(stdin);
    printf("\t\tdatte of birth(dd/mm/yyyy) : ");
    scanf("%d/%d/%d", &stu.dob.day, &stu.dob.month, &stu.dob.year);
    printf("\t\tfather name : ");
    fflush(stdin);
    scanf("%[^\n]s", stu.father);
    printf("\t\tmother name : ");
    fflush(stdin);
    scanf("%[^\n]s", stu.mother);
    fflush(stdin);
    printf("\t\tcontact no. : ");
    scanf("%lli", &stu.contact);
    fflush(stdin);
    printf("\t\taddress : ");
    scanf("%[^\n]s", stu.address);
    fflush(stdin);
    fwrite(&stu, sizeof(stu), 1, fp);
    fclose(fp);
    printf("\n\n\tdata added successfully.\n");
invalid_add2:
    printf("\n\t\t\tenter 1 for faculty menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        faculty_menu();
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\n\t\t\tinvalid input.");
        sleep(2);
        system("cls");
        goto invalid_add2;
    }
}

void view_data(int add_num)
{
    FILE *fv;
    int choice;
    system("cls");
    system("color 8e");
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t STUDENT PROFILE\n");
    fv = fopen("studentdatabase.dat", "rb");
    printf("\n\n\n");
    while (fread(&stu, sizeof(stu), 1, fv) == 1)
    {
        if (add_num == stu.adm_no)
        {
            printf("\t\tADMISSION NO.-\t%d\n", stu.adm_no);
            printf("\t\tNAME-\t%s\n", stu.name);
            printf("\t\tCLASS-\t%s\n", stu.class);
            printf("\t\tROLL-\t%d\n\t\tGENDER-\t\t%c\n\t\tD.O.B-\t%d/%d/%d\n\t\tFATHER'S NAME-\t%s\n\t\tMOTHER'S NAME-\t%s\n\t\tADDRESS-\t%s\n\n\t\tPERCENTAGE :\n\t\t\tTERM 1- %.2f\n\t\t\tTERM 2- %.2f\n\n", stu.roll, stu.gender, stu.dob.day, stu.dob.month, stu.dob.year, stu.father, stu.mother, stu.address, stu.term1.percentage, stu.term2.percentage);
        }
    }
    fclose(fv);
invalid_view:
    printf("\n\t\tenter 1 for student menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        student_menu(ad_no);
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\n\t\tinvalid input.");
        sleep(2);
        system("cls");
        goto invalid_view;
    }
}

void edit_stu_data(void)
{
    FILE *fedit;
    int rol, flag = 0, choice;
    system("cls");
    system("color f1");
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t EDIT STUDENT DATA\n");
    printf("\n\n\t\tenter student roll number : ");
    scanf("%d", &rol);
    printf("\n\n");
    fedit = fopen("studentdatabase.dat", "rb+");
    while (fread(&stu, sizeof(stu), 1, fedit) == 1)
    {
        if ((rol == stu.roll) && strcmp(stu.class, ct) == 0)
        {
            fflush(stdin);
            printf("\t\tname : ");
            scanf("%[^\n]s", stu.name);
            fflush(stdin);
            printf("\t\tadmission no. : ");
            scanf("%d", &stu.adm_no);
            fflush(stdin);
            printf("\t\tgender(M/F) : ");
            scanf("%c", &stu.gender);
            fflush(stdin);
            printf("\t\tdate of birth(dd/mm/yyyy) : ");
            scanf("%d/%d/%d", &stu.dob.day, &stu.dob.month, &stu.dob.year);
            fflush(stdin);
            printf("\t\tfather name : ");
            scanf("%[^\n]s", stu.father);
            fflush(stdin);
            printf("\t\tmother name : ");
            scanf("%[^\n]s", stu.mother);
            fflush(stdin);
            printf("\t\tcontact no. : ");
            scanf("%lli", &stu.contact);
            fflush(stdin);
            printf("\t\taddress : ");
            scanf("%[^\n]s", stu.address);
            flag = 1;
            fseek(fedit, -sizeof(stu), 1);
            fwrite(&stu, sizeof(stu), 1, fedit);
            break;
        }
    }
    fclose(fedit);
    fflush(stdin);
    if (flag == 0)
    {
        printf("\a\n\n\t\trecord not found.\n\n");
    }
    else
    {
        printf("\n\n\t\trecord updated successfully.\n");
    }
invalid_add2:
    printf("\n\t\tenter 1 for faculty menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        faculty_menu();
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\n\t\tinvalid input.\n");
        sleep(2);
        system("cls");
        goto invalid_add2;
    }
}

void report_card(int adm_num)
{
    system("cls");
    system("color b1");
    printf("\n\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tSTUDENT MARKSHEET\n");
    FILE *frp;
    frp = fopen("studentdatabase.dat", "rb");
    printf("\n\n");
    int zero = 0;
    while (fread(&stu, sizeof(stu), 1, frp) == 1)
    {
        if (adm_num == stu.adm_no)
        {
            printf("\t\t\t\t+----------------------------------+-------------------+------------+\n");
            printf("\t\t\t\t|NAME: %-28s|CLASS:  %-8s   |ROLL:  %5d|\n", stu.name, stu.class, stu.roll);
            printf("\t\t\t\t+----------------------------------+-------------------+------------+\n");
            printf("\t\t\t\t|DATE OF BIRTH: %11d/%2d/%d|ADM.NO.: %10d|GENDER:  %-3c|\n", stu.dob.day, stu.dob.month, stu.dob.year, stu.adm_no, stu.gender);
            printf("\t\t\t\t+----------------------------------+-------------------+------------+\n");
            printf("\t\t\t\t|FATHER'S NAME: %-52s|\n", stu.father);
            printf("\t\t\t\t+-------------------------------------------------------------------+\n");
            printf("\t\t\t\t|MOTHER'S NAME: %-52s|\n", stu.mother);
            printf("\t\t\t\t+-------------------------------------------------------------------+\n");
            printf("\t\t\t\t|-------------------------------------------------------------------|\n");
            printf("\t\t\t\t|      SUBJETS           |   TERM 1   |   TERM 2   |    TERM(1+2)   |\n");
            printf("\t\t\t\t+------------------------+------------+------------+----------------+\n");
            printf("\t\t\t\t|  HINDI                 | %10.0f | %10.0f | %14.0f |\n", stu.term1.hindi, stu.term2.hindi, ((stu.term1.hindi + stu.term2.hindi) / 2));
            printf("\t\t\t\t+------------------------+------------+------------+----------------+\n");
            printf("\t\t\t\t|  ENGLISH               | %10.0f | %10.0f | %14.0f |\n", stu.term1.english, stu.term2.english, ((stu.term1.english + stu.term2.english) / 2));
            printf("\t\t\t\t+------------------------+------------+------------+----------------+\n");
            printf("\t\t\t\t|  MATHEMATICS           | %10.0f | %10.0f | %14.0f |\n", stu.term1.maths, stu.term2.maths, ((stu.term1.maths + stu.term2.maths) / 2));
            printf("\t\t\t\t+------------------------+------------+------------+----------------+\n");
            printf("\t\t\t\t|  SCIENCE               | %10.0f | %10.0f | %14.0f |\n", stu.term1.science, stu.term2.science, ((stu.term1.science + stu.term2.science) / 2));
            printf("\t\t\t\t+------------------------+------------+------------+----------------+\n");
            printf("\t\t\t\t|  SOCIAL SCIENCE        | %10.0f | %10.0f | %14.0f |\n", stu.term1.ssc, stu.term2.ssc, ((stu.term1.ssc + stu.term2.ssc) / 2));
            printf("\t\t\t\t+------------------------+------------+------------+----------------+\n");
            printf("\t\t\t\t+------------------------+------------+------------+----------------+\n");
            printf("\t\t\t\t|  PERCENTAGE            | %10.2f | %10.2f | %14.2f |\n", stu.term1.percentage, stu.term2.percentage, ((stu.term1.percentage + stu.term2.percentage) / 2));
            printf("\t\t\t\t+------------------------+------------+------------+----------------+\n");
            printf("\n\t\t\t\tSTATUS :   ");
            float status = (stu.term1.percentage + stu.term2.percentage) / 2;
            if (stu.term1.hindi < 30 || stu.term2.hindi < 30 || stu.term1.maths < 30 || stu.term2.maths < 30 || stu.term1.english < 30 || stu.term2.english < 30 || stu.term1.science < 30 || stu.term2.science < 30 || stu.term1.ssc < 30 || stu.term2.ssc < 30)
            {
                zero = 1;
            }
            (status >= 30 && zero == 0) ? printf("ELIGIBLE") : printf("NOT ELIGIBLE");
            printf(" FOR PROMOTION TO HIGHER CLASS.\n\n\t\t\t\t\t\t\t\t\t\t\t\tBEST WISHES :-)");
            printf("\n\n\t\t\t\tNOTE:\n\t\t\t\t\tminimum 30%% marks is required to qualify the exam.\n");
            break;
        }
    }
    fclose(frp);
    int choice;
invalid_view:
    fflush(stdin);
    printf("\n\t\tenter 1 for student menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        student_menu(ad_no);
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\n\t\tinvalid input.");
        sleep(2);
        system("cls");
        goto invalid_view;
    }
}

void add_fac(void)
{
    FILE *ft;
    system("cls");
    system("color b0");
    printf("\n\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\tADD FACULTY DATA\n");
    char name[30], dept[20];
    int d, m, y, choice;
    ft = fopen("teacherdatabase.dat", "ab+");
    printf("\n\n");
    fflush(stdin);
    printf("\t\tname : ");
    scanf("%[^\n]s", name);
    fflush(stdin);
    printf("\t\tdepartment : ");
    scanf("%[^\n]s", dept);
    fflush(stdin);
    printf("\t\tdate of birth(dd/mm/yyyy) : ");
    scanf("%d/%d/%d", &d, &m, &y);
    fflush(stdin);
    create_id(name, dept, y);
    while (fread(&faculty, sizeof(faculty), 1, ft) == 1)
    {
        if (id == faculty.id)
        {
            printf("\a\n\t\trecord already exist.\n");
            fclose(ft);
        invalid_add1:
            printf("\n\t\tenter 1 to try again 2 for admin menu 3 for main menu or 0 for exit: ");
            scanf("%d", &choice);
            if (choice == 1)
                add_fac();
            else if (choice == 2)
                admin_menu();
            else if (choice == 3)
                main();
            else if (choice == 0)
                quit();
            else
            {
                printf("\a\n\n\t\t\tinvalid input.");
                sleep(2);
                system("cls");
                goto invalid_add1;
            }
            break;
        }
    }
    strcpy(faculty.name, name);
    strcpy(faculty.dept, dept);
    faculty.dob.day = d;
    faculty.dob.month = m;
    faculty.dob.year = y;
    strcpy(faculty.id, id);
    fflush(stdin);
    printf("\t\tclass teacher of : ");
    scanf("%s", faculty.classt);
    fflush(stdin);
    printf("\t\tdate of joining(dd/mm/yyyy) : ");
    scanf("%d/%d/%d", &faculty.doj.day, &faculty.doj.month, &faculty.doj.year);
    fwrite(&faculty, sizeof(faculty), 1, ft);
    printf("\n\n\t\trecord added successfully.\n");
    fclose(ft);
invalid_add2:
    printf("\n\t\tenter 1 to add more record 2 for admin menu 3 for main menu or 0 for exit: ");
    scanf("%d", &choice);
    if (choice == 1)
        add_fac();
    else if (choice == 2)
        admin_menu();
    else if (choice == 3)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\n\t\tinvalid input.");
        sleep(2);
        system("cls");
        goto invalid_add2;
    }
}

void edit_fac(void)
{
    FILE *fe;
    int flag = 0, choice;
    system("cls");
    system("color c0");
    printf("\n\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\tEDIT FACULTY DATA\n");
    printf("\n\n");
    printf("\t\tenter faculty ID no. : ");
    scanf("%s", id);
    fe = fopen("teacherdatabase.dat", "rb+");
    while (fread(&faculty, sizeof(faculty), 1, fe) == 1)
    {
        if (strcmp(id, faculty.id) == 0)
        {
            fflush(stdin);
            printf("\t\tname : ");
            scanf("%[^\n]s", faculty.name);
            fflush(stdin);
            printf("\t\tdepartment : ");
            scanf("%[^\n]s", faculty.dept);
            fflush(stdin);
            printf("\t\tdate of birth(dd/mm/yyyy) : ");
            scanf("%d/%d/%d", &faculty.dob.day, &faculty.dob.month, &faculty.dob.year);
            create_id(faculty.name, faculty.dept, faculty.dob.year);
            strcpy(faculty.id, id);
            fflush(stdin);
            printf("\t\tclass teacher of : ");
            scanf("%s", faculty.classt);
            fflush(stdin);
            printf("\t\tdate of joining(dd/mm/yyyy) : ");
            scanf("%d/%d/%d", &faculty.doj.day, &faculty.doj.month, &faculty.doj.year);
            fseek(fe, -sizeof(faculty), 1);
            fwrite(&faculty, sizeof(faculty), 1, fe);
            flag = 1;
            break;
        }
    }
    fclose(fe);
    if (flag == 0)
    {
        printf("\a\n\n\t\trecord not found.\n\n");
    }
    else
    {
        printf("\n\n\t\trecord updated successfully.\n");
    }
invalid_add2:
    printf("\n\t\tenter 1 for admin menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        admin_menu();
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\t\tinvalid input.\n");
        sleep(2);
        system("cls");
        goto invalid_add2;
    }
}

void delete_fac(void)
{
    FILE *fd, *ftmp;
    int flag = 0, choice;
    system("cls");
    system("color de");
    printf("\n\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\tDELETE FACULTY DATA\n");
    printf("\n\n");
    printf("\t\tenter faculty id to delete : ");
    scanf("%s", id);
    ftmp = fopen("tempdatabase.dat", "ab+");
    fd = fopen("teacherdatabase.dat", "rb");
    while (fread(&faculty, sizeof(faculty), 1, fd) == 1)
    {
        if (strcmp(faculty.id, id) != 0)
        {
            fwrite(&faculty, sizeof(faculty), 1, ftmp);
        }
        else
        {
            flag = 1;
        }
    }
    fclose(fd);
    fclose(ftmp);
    remove("teacherdatabase.dat");
    rename("tempdatabase.dat", "teacherdatabase.dat");
    if (flag == 0)
    {
        printf("\a\n\n\t\trecord not found.\n\n");
    }
    else
    {
        printf("\n\n\t\trecord deleted successfully.\n");
    }
invalid_add:
    printf("\n\t\tenter 1 for admin menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        admin_menu();
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\n\t\tinvalid input.\n");
        sleep(2);
        system("cls");
        goto invalid_add;
    }
}

void delete_stu_data(void)
{
    FILE *fd, *ftmp;
    int rol, choice, flag = 0;
    system("cls");
    system("color 2f");
    printf("\n\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\tDELETE STUDENT DATA\n");
    printf("\n\n");
    fd = fopen("studentdatabase.dat", "rb");
    ftmp = fopen("tempdatabase.dat", "wb");
    printf("\t\tenter student roll no. : ");
    scanf("%d", &rol);
    while (fread(&stu, sizeof(stu), 1, fd) == 1)
    {
        if ((stu.roll != rol) || (strcmp(stu.class, ct) != 0))
        {
            fwrite(&stu, sizeof(stu), 1, ftmp);
        }
        else
        {
            flag = 1;
        }
    }
    fclose(fd);
    fclose(ftmp);
    remove("studentdatabase.dat");
    rename("tempdatabase.dat", "studentdatabase.dat");
    if (flag == 0)
    {
        printf("\a\n\n\t\trecord not found.\n\n");
    }
    else
    {
        printf("\n\n\t\trecord deleted successfully.\n");
    }
invalid_add:
    printf("\n\t\tenter 1 for faculty menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        faculty_menu();
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\t\t\tinvalid input.\n");
        sleep(2);
        system("cls");
        goto invalid_add;
    }
}

void pcalc(int t)
{
    float term;
    if (t == 1)
    {
        term = stu.term1.hindi + stu.term1.english + stu.term1.maths + stu.term1.science + stu.term1.ssc;
        stu.term1.percentage = term / 5;
    }
    else if (t == 2)
    {
        term = stu.term2.hindi + stu.term2.english + stu.term2.maths + stu.term2.science + stu.term2.ssc;
        stu.term2.percentage = term / 5;
    }
}

void add_stu_marks(void)
{
    int tchoice, flag = 0;
    char sub[20], clas[5];
    FILE *fm, *ft, *ftmp;
    system("cls");
    system("color 34");
    printf("\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\tADD STUDENT MARKS\n");
    printf("\n\n");
    fm = fopen("studentdatabase.dat", "rb+");
    ft = fopen("teacherdatabase.dat", "rb");
    while (fread(&faculty, sizeof(faculty), 1, ft) == 1)
    {
        if (strcmp(id, faculty.id) == 0)
        {
            strcpy(sub, faculty.dept);
            break;
        }
    }
    fclose(ft);
    printf("\t\tenter 1 for term1 and 2 for term2 : ");
    scanf("%d", &tchoice);
    fflush(stdin);
    printf("\t\tenter class to add marks : ");
    scanf("%s", clas);
    printf("\n");
    ftmp = fopen("tempdatabase.dat", "wb");
    //   ********term 1**********
    if (tchoice == 1)
    {
        if ((strcmp(sub, "hindi") == 0) || (strcmp(sub, "HINDI") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tHINDI\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term1.hindi);
                    pcalc(1);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else if ((strcmp(sub, "english") == 0) || (strcmp(sub, "ENGLISH") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tENGLISH\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term1.english);
                    pcalc(1);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else if ((strcmp(sub, "mathematics") == 0) || (strcmp(sub, "MATHS") == 0) || (strcmp(sub, "maths") == 0) || (strcmp(sub, "MATHEMATICS") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tMATHEMATICS\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term1.maths);
                    pcalc(1);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else if ((strcmp(sub, "science") == 0) || (strcmp(sub, "SCIENCE") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tSCIENCE\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term1.science);
                    pcalc(1);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else if ((strcmp(sub, "social science") == 0) || (strcmp(sub, "SOCIAL SCIENCE") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tSOCIAL SCIENCE\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term1.ssc);
                    pcalc(1);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else
        {
            printf("\a\n\t\tno any subject by this name.\n");
        }
    }
    // **********term 2*********
    else if (tchoice == 2)
    {
        if ((strcmp(sub, "hindi") == 0) || (strcmp(sub, "HINDI") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tHINDI\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term2.hindi);
                    pcalc(2);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else if ((strcmp(sub, "english") == 0) || (strcmp(sub, "ENGLISH") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tENGLISH\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term2.english);
                    pcalc(2);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else if ((strcmp(sub, "maths") == 0) || (strcmp(sub, "MATHS") == 0) || (strcmp(sub, "mathematics") == 0) || (strcmp(sub, "MATHEMATICS") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tMATHEMATICS\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term2.maths);
                    pcalc(2);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else if ((strcmp(sub, "science") == 0) || (strcmp(sub, "SCIENCE") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tSCIENCE\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term2.science);
                    pcalc(2);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else if ((strcmp(sub, "social science") == 0) || (strcmp(sub, "SOCIAL SCIENCE") == 0))
        {
            printf("\n\t\t\t\tSUBJECT : \tSOCIAL SCIENCE\n");
            while (fread(&stu, sizeof(stu), 1, fm) == 1)
            {
                if (strcmp(stu.class, clas) == 0)
                {
                    fflush(stdin);
                    printf("\t\tenter marks of roll no. %d : ", stu.roll);
                    scanf("%f", &stu.term2.ssc);
                    pcalc(2);
                    printf("\n");
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                    flag = 1;
                }
                else
                {
                    fwrite(&stu, sizeof(stu), 1, ftmp);
                }
            }
            if (flag == 0)
            {
                printf("\n\n\t\tstudent record is not available for this class.\n");
            }
        }
        else
        {
            printf("\a\n\t\tno any subject by this name.\n");
        }
    }
    fclose(fm);
    fclose(ftmp);
    remove("studentdatabase.dat");
    rename("tempdatabase.dat", "studentdatabase.dat");
    int choice;
invalid_marks:
    printf("\n\t\tenter 1 to add more marks 2 for main menu 3 for faculty menu or 0 for exit.\n");
    printf("\t\tenter your choice: ");
    scanf("%d", &choice);
    if (choice == 1)
        add_stu_marks();
    else if (choice == 2)
        main();
    else if (choice == 3)
        faculty_menu();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\n\t\tinvalid option.\n");
        sleep(2);
        system("cls");
        goto invalid_marks;
    }
}

void view_fac_list(void)
{
    FILE *fview;
    int flag = 0;
    system("cls");
    system("color 9f");
    printf("\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tFACULTY LIST\n");
    printf("\n\n");
    fview = fopen("teacherdatabase.dat", "rb+");
    printf("\t\t+----------------+----------------------------------------------+----------------------+--------------------+--------------------+------------------+\n");
    printf("\t\t|  FACULTY ID    |                      NAME                    |      DEPARTMENT      |  CLASS TEACHER OF  |   DATE OF BIRTH    |  DATE OF JOINING |\n");
    printf("\t\t+----------------+----------------------------------------------+----------------------+--------------------+--------------------+------------------+\n");
    while (fread(&faculty, sizeof(faculty), 1, fview) == 1)
    {
        printf("\t\t|  %-13s | %-44s | %-20s |     %-14s |  %5d/%2d/%-7d  |  %5d/%2d/%-5d  |\n", faculty.id, faculty.name, faculty.dept, faculty.classt, faculty.dob.day, faculty.dob.month, faculty.dob.year, faculty.doj.day, faculty.doj.month, faculty.doj.year);
        printf("\t\t+----------------+----------------------------------------------+----------------------+--------------------+--------------------+------------------+\n");
        flag = 1;
    }
    fclose(fview);
    if (flag == 0)
    {
        printf("\a\n\n\t\tno record available.\n");
    }
    int choice;
invalid_view:
    printf("\n\t\tenter 1 for admin menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        admin_menu();
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\a\n\n\t\tinvalid input.\n");
        sleep(2);
        system("cls");
        goto invalid_view;
    }
}

void view_stu_list(void)
{
    FILE *fview;
    fview = fopen("studentdatabase.dat", "rb");
    char clas[5];
    int flag = 0, k = 0;
    system("cls");
    system("color e4");
    printf("\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tSTUDENT LIST\n");
    printf("\n\n");
    printf("\t\tenter the class : ");
    scanf("%s", clas);
    while (fread(&stu, sizeof(stu), 1, fview) == 1)
    {
        if (strcmp(clas, stu.class) == 0)
        {
            tstu[k++] = stu;
            flag = 1;
        }
    }
    ///   *******sorting********
    int i = 0, j = 0;
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k - 1 - i; j++)
        {
            if (tstu[j].roll > tstu[j + 1].roll)
            {
                tmp = tstu[j];
                tstu[j] = tstu[j + 1];
                tstu[j + 1] = tmp;
            }
        }
    }
    fflush(stdin);
    printf("   +------+--------------------------------+---------------+----------------------------------+---------------+----------------------------------------------------------------+--------+---------------+\n");
    printf("   | ROLL |             NAME               | ADMISSION NO. |          FATHER'S NAME           | DATE OF BIRTH |                            ADDRESS                             | GENDER |  CONTACT NO.  |\n");
    printf("   +------+--------------------------------+---------------+----------------------------------+---------------+----------------------------------------------------------------+--------+---------------+\n");
    if (flag == 1)
    {
        for (i = 0; i < k; i++)
        {
            printf("   | %3d  | %-30s | %12d  |  %-30s  |  %2d/%2d/%-5d  |  %-60s  | %4c   | %12lli  |\n", tstu[i].roll, tstu[i].name, tstu[i].adm_no, tstu[i].father, tstu[i].dob.day, tstu[i].dob.month, tstu[i].dob.year, tstu[i].address, tstu[i].gender, tstu[i].contact);
            printf("   +------+--------------------------------+---------------+----------------------------------+---------------+----------------------------------------------------------------+--------+---------------+\n");
        }
    }

    fclose(fview);
    if (flag == 0)
    {
        printf("\a\n\n\t\tno record available.\n");
    }
    int choice;
    if (wopn == 1)
    {
    invalid_view:
        printf("\n\n\t\tenter 1 main menu 2. for faculty menu or 0 for exit : ");
        scanf("%d", &choice);
        if (choice == 1)
            main();
        else if (choice == 2)
            faculty_menu();
        else if (choice == 0)
            quit();
        else
        {
            printf("\a\n\n\t\tinvalid input.\n");
            sleep(2);
            system("cls");
            goto invalid_view;
        }
    }
    else if (wopn == 2)
    {
    invalid_view_:
        printf("\n\n\t\tenter 1 main menu 2 for admin menu or 0 for exit : ");
        scanf("%d", &choice);
        if (choice == 1)
            main();
        else if (choice == 2)
            admin_menu();
        else if (choice == 0)
            quit();
        else
        {
            printf("\a\n\n\t\tinvalid input.\n");
            sleep(2);
            system("cls");
            goto invalid_view_;
        }
    }
}

void view_fac(void)
{
    FILE *fv;
    int choice;
    system("cls");
    system("color 9f");
    printf("\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tFACULTY PROFILE\n");
    printf("\n\n");
    fv = fopen("teacherdatabase.dat", "rb");
    while (fread(&faculty, sizeof(faculty), 1, fv) == 1)
    {
        if (strcmp(id, faculty.id) == 0)
        {
            printf("\t\tID :\t%s\n", faculty.id);
            printf("\t\tNAME :\t%s\n", faculty.name);
            printf("\t\tCLASS TEACHER OF :\t%s\n", faculty.classt);
            printf("\t\tDEPARTMENT :\t%s\n\t\tD.O.B :\t%d/%d/%d\n\t\tD.O.J :\t%d/%d/%d\n", faculty.dept, faculty.dob.day, faculty.dob.month, faculty.dob.year, faculty.doj.day, faculty.doj.month, faculty.doj.year);
        }
    }
    fclose(fv);
invalid_view:
    printf("\n\t\tenter 1 for faculty menu 2 for main menu or 0 for exit : ");
    scanf("%d", &choice);
    if (choice == 1)
        faculty_menu();
    else if (choice == 2)
        main();
    else if (choice == 0)
        quit();
    else
    {
        printf("\n\t\tinvalid input.");
        sleep(2);
        system("cls");
        goto invalid_view;
    }
}

void quit(void)
{
    system("cls");
    system("color 01");
    printf("\n\n\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tTHANK YOU\n");
    printf("\n\n\t\t\tcreated by SHUBHAM SINGH\n\n\n\n\tpress any key to exit.");
    getch();
    exit(0);
}

void student_menu(int admission)
{
    int choice;
    system("cls");
    system("color 1e");
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tSTUDENT WINDOW\n");
    printf("\n\n\n\t\t1. view your profile.\n\t\t2. get report card.\n\t\t3. main menu\n\t\t0. exit\n");
    printf("\n\t\tenter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        view_data(admission);
        break;
    case 2:
        report_card(admission);
        break;
    case 3:
        main();
        break;
    case 0:
        quit();
    default:
    {
        printf("\n\ainvalid input.\n");
        sleep(2);
        student_menu(ad_no);
    }
    }
}

void faculty_menu(void)
{
    system("cls");
    system("color 60");
    int choice;
    wopn = 1;
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tFACULTY WINDOW\n");
    if ((strcmp(ct, "none") == 0) || (strcmp(ct, "NONE") == 0))
    {
        printf("\n\n\n\t\t1. view your profile.\n\t\t2. add student marks\n\t\t3. view student list\n\t\t4. main menu.\n\t\t0. exit\n");
        printf("\n\t\tenter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            view_fac();
            break;
        case 2:
            add_stu_marks();
            break;
        case 3:
            view_stu_list();
            break;
        case 4:
            main();
            break;
        case 0:
            quit();
            break;
        default:
            printf("\n\ninvalid input.\n");
            sleep(2);
            system("cls");
            faculty_menu();
            break;
        }
    }
    else
    {
        printf("\n\n\n\t\t1. view your profile.\n\t\t2. add student data.\n\t\t3. edit student data\n\t\t4. delete student data.\n\t\t5. add student marks\n\t\t6. view student list\n\t\t7. main menu\n\t\t0. exit\n");
        printf("\n\t\tenter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            view_fac();
            break;
        case 2:
            add_stu_data();
            break;
        case 3:
            edit_stu_data();
            break;
        case 4:
            delete_stu_data();
            break;
        case 5:
            add_stu_marks();
            break;
        case 6:
            view_stu_list();
            break;
        case 7:
            main();
            break;
        case 0:
            quit();
            break;
        default:
            printf("\n\ninvalid input.\n");
            sleep(2);
            system("cls");
            faculty_menu();
            break;
        }
    }
}

void admin_menu(void)
{
    system("cls");
    int choice;
    system("color e8");
    wopn = 2;
    printf("\n\n\n\t\t\tSCHOOL MANAGEMENT SYSTEM\n\t\t------------------------------------------\n\t\t\t\tADMIN WINDOW\n");
    printf("\n\n\n\t\t1. add faculty.\n\t\t2. edit faculty record.\n\t\t3. delete faculty record.\n\t\t4. view faculty list.\n\t\t5. view student list\n\t\t6. main menu.\n\t\t0. exit\n");
    printf("\n\n\t\tenter your choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        add_fac();
        break;
    case 2:
        edit_fac();
        break;
    case 3:
        delete_fac();
        break;
    case 4:
        view_fac_list();
        break;
    case 5:
        view_stu_list();
        break;
    case 6:
        main();
        break;
    case 0:
        quit();
        break;
    default:
    {
        printf("\n\ninvalid input.\n");
        sleep(2);
        system("cls");
        admin_menu();
        break;
    }
    }
}
