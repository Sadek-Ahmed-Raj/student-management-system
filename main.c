#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STU 300
#define MAX_COU 150
#define FILE_NAME "data.dat"

/* ---------------- Data Structure ---------------- */

typedef struct {
    char courseCode[20];
    float quiz1, quiz2, quiz3, mid, final;
} Result;

typedef struct {
    int id;
    char name[50];
    char dept[50];
    char gender[10];
    char dob[15];
    char blood[10];
    char address[100];
    char phone[20];
    char password[20];
    float cgpa;

    char courseList[MAX_COU][20];
    int courseCount;

    Result results[MAX_COU];
    int resultCount;

} Student;

typedef struct {
    char code[20];
    char title[50];
    int credit;
} Course;

Student students[MAX_STU];
Course courses[MAX_COU];

int stuCount = 0;
int couCount = 0;

/* ---------------- Admin Password ---------------- */

char adminPass[20] = "1234";

/* ---------------- Utils ---------------- */

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void flush(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

void pause(){
    printf("\nPress Enter to continue...");
    flush();
    clearScreen();
}

int findStudent(int id){
    for(int i=0;i<stuCount;i++)
        if(students[i].id==id) return i;
    return -1;
}

int findCourse(char *code){
    for(int i=0;i<couCount;i++)
        if(strcmp(courses[i].code,code)==0) return i;
    return -1;
}

/* ---------------- File ---------------- */

void save(){
    FILE *fp = fopen(FILE_NAME,"wb");
    if(!fp){printf("Error\n");return;}

    fwrite(&stuCount,sizeof(int),1,fp);
    fwrite(students,sizeof(Student),stuCount,fp);

    fwrite(&couCount,sizeof(int),1,fp);
    fwrite(courses,sizeof(Course),couCount,fp);

    fwrite(adminPass,sizeof(adminPass),1,fp);

    fclose(fp);

    printf("Saved.\n");
}

void load(){
    FILE *fp = fopen(FILE_NAME,"rb");
    if(!fp){printf("No data.\n");return;}

    fread(&stuCount,sizeof(int),1,fp);
    fread(students,sizeof(Student),stuCount,fp);

    fread(&couCount,sizeof(int),1,fp);
    fread(courses,sizeof(Course),couCount,fp);

    fread(adminPass,sizeof(adminPass),1,fp);

    fclose(fp);

    printf("Loaded.\n");
}

/* ---------------- Student Mgmt ---------------- */

void createStudent(){
    clearScreen();
    Student s;
    char temp[200];

    printf("Enter ID (C to cancel): ");
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    s.id = atoi(temp);

    // Check if ID already exists
    if(findStudent(s.id) != -1){
        printf("Error: Student with ID %d already exists!\n", s.id);
        pause();
        return;
    }

    printf("Full Name (Enter to skip, C to cancel): "); 
    fgets(s.name,50,stdin);
    if(s.name[0]=='C' || s.name[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(s.name[0]=='\n') strcpy(s.name, "N/A\n");

    printf("Department (Enter to skip, C to cancel): "); 
    fgets(s.dept,50,stdin);
    if(s.dept[0]=='C' || s.dept[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(s.dept[0]=='\n') strcpy(s.dept, "N/A\n");

    printf("Gender (Enter to skip, C to cancel): "); 
    fgets(s.gender,10,stdin);
    if(s.gender[0]=='C' || s.gender[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(s.gender[0]=='\n') strcpy(s.gender, "N/A\n");

    printf("DOB (Enter to skip, C to cancel): "); 
    fgets(s.dob,15,stdin);
    if(s.dob[0]=='C' || s.dob[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(s.dob[0]=='\n') strcpy(s.dob, "N/A\n");

    printf("Blood (Enter to skip, C to cancel): "); 
    fgets(s.blood,10,stdin);
    if(s.blood[0]=='C' || s.blood[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(s.blood[0]=='\n') strcpy(s.blood, "N/A\n");

    printf("Address (Enter to skip, C to cancel): "); 
    fgets(s.address,100,stdin);
    if(s.address[0]=='C' || s.address[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(s.address[0]=='\n') strcpy(s.address, "N/A\n");

    printf("Phone (Enter to skip, C to cancel): "); 
    fgets(s.phone,20,stdin);
    if(s.phone[0]=='C' || s.phone[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(s.phone[0]=='\n') strcpy(s.phone, "N/A\n");

    printf("Set Password (C to cancel): ");
    fgets(s.password,20,stdin);
    if(s.password[0]=='C' || s.password[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    s.password[strcspn(s.password,"\n")] = 0;

    printf("CGPA (Enter to skip, C to cancel): "); 
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(temp[0]=='\n') s.cgpa = 0.0;
    else s.cgpa = atof(temp);

    s.courseCount = 0;
    s.resultCount = 0;

    students[stuCount++] = s;

    printf("Student created.\n");
    pause();
}

void updateStudent(){
    clearScreen();
    char temp[200];

    printf("ID to update (C to cancel): ");
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(temp[0]=='\n'){ return; }
    int id = atoi(temp);

    int x = findStudent(id);
    if(x==-1){ printf("Not Found\n"); pause(); return; }

    Student *s = &students[x];

    // Show current info
    printf("\n--- Current Info ---\n");
    printf("Name: %s", s->name);
    printf("Dept: %s", s->dept);
    printf("Gender: %s", s->gender);
    printf("DOB: %s", s->dob);
    printf("Blood: %s", s->blood);
    printf("Address: %s", s->address);
    printf("Phone: %s", s->phone);
    printf("CGPA: %.2f\n", s->cgpa);
    printf("-------------------\n\n");

    char temp2[200];

    char newName[50], newDept[50], newGender[10], newDob[15], newBlood[10];
    char newAddr[100], newPhone[20], newPass[20];
    float newCgpa = s->cgpa;

    strcpy(newName, s->name);
    strcpy(newDept, s->dept);
    strcpy(newGender, s->gender);
    strcpy(newDob, s->dob);
    strcpy(newBlood, s->blood);
    strcpy(newAddr, s->address);
    strcpy(newPhone, s->phone);
    strcpy(newPass, s->password);

    printf("New Name (Enter to skip): ");
    fgets(temp2,200,stdin); if(temp2[0]!='\n') strcpy(newName,temp2);

    printf("New Dept (Enter to skip): ");
    fgets(temp2,200,stdin); if(temp2[0]!='\n') strcpy(newDept,temp2);

    printf("New Gender (Enter to skip): ");
    fgets(temp2,200,stdin); if(temp2[0]!='\n') strcpy(newGender,temp2);

    printf("New DOB (Enter to skip): ");
    fgets(temp2,200,stdin); if(temp2[0]!='\n') strcpy(newDob,temp2);

    printf("New Blood (Enter to skip): ");
    fgets(temp2,200,stdin); if(temp2[0]!='\n') strcpy(newBlood,temp2);

    printf("New Address (Enter to skip): ");
    fgets(temp2,200,stdin); if(temp2[0]!='\n') strcpy(newAddr,temp2);

    printf("New Phone (Enter to skip): ");
    fgets(temp2,200,stdin); if(temp2[0]!='\n') strcpy(newPhone,temp2);

    printf("New Password (Enter to skip): ");
    fgets(temp2,200,stdin); 
    if(temp2[0]!='\n'){
        temp2[strcspn(temp2,"\n")] = 0;
        strcpy(newPass,temp2);
    }

    printf("New CGPA (Enter to skip): ");
    fgets(temp2,200,stdin);
    if(temp2[0]!='\n') newCgpa = atof(temp2);

    char c;

    while(1){

        printf("\nPress C to CANCEL or S to SAVE: ");
        c = getchar();

        if(c=='C' || c=='c'){
            printf("Update Cancelled.\n");
            flush();
            pause();
            return;
        }

        if(c=='S' || c=='s'){
            flush();
            break;
        }

        printf("Invalid key! Please press S to save or C to cancel.\n");

        flush();
    }

    strcpy(s->name, newName);
    strcpy(s->dept, newDept);
    strcpy(s->gender, newGender);
    strcpy(s->dob, newDob);
    strcpy(s->blood, newBlood);
    strcpy(s->address, newAddr);
    strcpy(s->phone, newPhone);
    strcpy(s->password, newPass);
    s->cgpa = newCgpa;

    printf("Profile Updated.\n");
    pause();
}


void deleteStudent(){
    clearScreen();
    char temp[200];

    printf("ID to delete (C to cancel): ");
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(temp[0]=='\n'){ printf("Cancelled.\n"); pause(); return; }
    int id = atoi(temp);

    int x = findStudent(id);
    if(x==-1){printf("Not Found\n");pause();return;}

    for(int i=x;i<stuCount-1;i++)
        students[i]=students[i+1];

    stuCount--;

    printf("Deleted.\n");
    pause();
}

void displayStudents(){
    clearScreen();
    if(stuCount==0){printf("No Students.\n");pause();return;}

    for(int i=0;i<stuCount;i++){
        printf("\n===============================\n");
        printf("ID          : %d\n", students[i].id);
        printf("Name        : %s", students[i].name);
        printf("Department  : %s", students[i].dept);
        printf("Gender      : %s", students[i].gender);
        printf("DOB         : %s", students[i].dob);
        printf("Blood       : %s", students[i].blood);
        printf("Address     : %s", students[i].address);
        printf("Phone       : %s", students[i].phone);
        printf("CGPA        : %.2f\n", students[i].cgpa);

        printf("\nRegistered Courses:\n");
        if(students[i].courseCount==0){
            printf("  Not assigned\n");
        }
        else {
            int displayCount = 0;
            for(int j=0;j<students[i].courseCount;j++){
                int c = findCourse(students[i].courseList[j]);
                if(c != -1){
                    displayCount++;
                    printf("  %d. %s - %s (%d credits)\n", 
                           displayCount, courses[c].code, courses[c].title, courses[c].credit);
                }
            }
            if(displayCount == 0){
                printf("  Not assigned\n");
            }
        }
        printf("===============================\n");
    }
    pause();
}

/* ---------------- Course Mgmt ---------------- */

void createCourse(){
    clearScreen();
    Course c;
    char temp[200];

    printf("Course Code (C to cancel): "); 
    fgets(c.code,20,stdin);
    if(c.code[0]=='C' || c.code[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    c.code[strcspn(c.code,"\n")] = 0;

    printf("Title (Enter to skip, C to cancel): "); 
    fgets(c.title,50,stdin);
    if(c.title[0]=='C' || c.title[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(c.title[0]=='\n') strcpy(c.title, "N/A");
    else c.title[strcspn(c.title,"\n")] = 0;

    printf("Credit (Enter to skip, C to cancel): "); 
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(temp[0]=='\n') c.credit = 0;
    else c.credit = atoi(temp);

    courses[couCount++] = c;

    printf("Course created.\n");
    pause();
}

void displayCourses(){
    clearScreen();
    if(couCount==0){printf("No Courses.\n");pause();return;}

    for(int i=0;i<couCount;i++){
        printf("\n-----------------------------\n");
        printf("Course Code  : %s\n",courses[i].code);
        printf("Course Title : %s\n",courses[i].title);
        printf("Credits      : %d\n",courses[i].credit);
        printf("-----------------------------\n");
    }
    pause();
}

void deleteCourse(){
    clearScreen();
    char code[20];

    printf("Course Code to delete (C to cancel): ");
    fgets(code,20,stdin);
    if(code[0]=='C' || code[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(code[0]=='\n'){ printf("Cancelled.\n"); pause(); return; }
    code[strcspn(code,"\n")] = 0;

    int x = findCourse(code);
    if(x==-1){printf("Course Not Found\n");pause();return;}

    for(int i=x;i<couCount-1;i++)
        courses[i]=courses[i+1];

    couCount--;

    printf("Course Deleted.\n");
    pause();
}

void assignCourse(){
    clearScreen();
    char temp[200];
    char ccode[20];

    printf("Student ID (C to cancel): "); 
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(temp[0]=='\n'){ printf("Cancelled.\n"); pause(); return; }
    int sid = atoi(temp);

    printf("Course Code (C to cancel): "); 
    fgets(ccode,20,stdin);
    if(ccode[0]=='C' || ccode[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    if(ccode[0]=='\n'){ printf("Cancelled.\n"); pause(); return; }
    ccode[strcspn(ccode,"\n")] = 0;

    int s=findStudent(sid);
    int c=findCourse(ccode);

    if(s==-1){
        printf("Student not found\n");
        pause();
        return;
    }

    if(c==-1){
        printf("Course not found\n");
        pause();
        return;
    }

    // Check if already assigned
    for(int i=0; i<students[s].courseCount; i++){
        if(strcmp(students[s].courseList[i], ccode)==0){
            printf("Course already assigned to this student!\n");
            pause();
            return;
        }
    }

    strcpy(students[s].courseList[students[s].courseCount], ccode);
    students[s].courseCount++;

    printf("Course assigned successfully.\n");
    pause();
}

void unassignCourse(){
    clearScreen();
    char temp[200];
    char ccode[20];

    printf("Student ID (C to cancel): "); 
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    int sid = atoi(temp);

    printf("Course Code (C to cancel): "); 
    fgets(ccode,20,stdin);
    if(ccode[0]=='C' || ccode[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    ccode[strcspn(ccode,"\n")] = 0;

    int s=findStudent(sid);
    if(s==-1){printf("Student not found\n");pause();return;}

    for(int i=0;i<students[s].courseCount;i++)
        if(strcmp(students[s].courseList[i], ccode)==0){
            for(int j=i;j<students[s].courseCount-1;j++)
                strcpy(students[s].courseList[j], students[s].courseList[j+1]);
            students[s].courseCount--;
            printf("Unassigned.\n");
            pause();
            return;
        }

    printf("Course not assigned to this student.\n");
    pause();
}

/* ---------------- Result Mgmt ---------------- */

void addResult(){
    clearScreen();
    char temp[200];

    printf("Student ID (C to cancel): ");
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    int sid = atoi(temp);

    int s=findStudent(sid);
    if(s==-1){printf("Not Found\n");pause();return;}

    Result r;

    printf("Course Code (C to cancel): ");
    char temp2[50];
    fgets(temp2,50,stdin);

    if(temp2[0]=='C' || temp2[0]=='c'){
        printf("Cancelled.\n");
        pause();
        return;
    }
    temp2[strcspn(temp2,"\n")] = 0;
    strcpy(r.courseCode, temp2);

    printf("Quiz1 (Enter to skip): ");
    fgets(temp2,50,stdin);
    if(temp2[0]!='\n') r.quiz1 = atof(temp2); else r.quiz1 = -1;

    printf("Quiz2 (Enter to skip): ");
    fgets(temp2,50,stdin);
    if(temp2[0]!='\n') r.quiz2 = atof(temp2); else r.quiz2 = -1;

    printf("Quiz3 (Enter to skip): ");
    fgets(temp2,50,stdin);
    if(temp2[0]!='\n') r.quiz3 = atof(temp2); else r.quiz3 = -1;

    printf("Mid (Enter to skip): ");
    fgets(temp2,50,stdin);
    if(temp2[0]!='\n') r.mid = atof(temp2); else r.mid = -1;

    printf("Final (Enter to skip): ");
    fgets(temp2,50,stdin);
    if(temp2[0]!='\n') r.final = atof(temp2); else r.final = -1;

    char ch;
    while(1){
        printf("\nPress C to CANCEL or S to SAVE: ");
        ch = getchar();

        if(ch=='C' || ch=='c'){
            printf("Cancelled.\n");
            flush();
            pause();
            return;
        }

        if(ch=='S' || ch=='s'){
            flush();
            break;
        }

        printf("Invalid key! Press S to save or C to cancel.\n");
        flush();
    }

    students[s].results[students[s].resultCount++] = r;

    printf("Result Saved.\n");
    pause();
}


void viewResults(int x){
    clearScreen();
    if(students[x].resultCount==0){printf("No Results.\n");pause();return;}

    printf("\n------ Your Results ------\n");
    for(int i=0;i<students[x].resultCount;i++){
        Result *r=&students[x].results[i];
        
        printf("\n------------------------------\n");
        printf("Course Code : %s\n",r->courseCode);
        
        if(r->quiz1 != -1) printf("Quiz 1      : %.2f\n",r->quiz1);
        if(r->quiz2 != -1) printf("Quiz 2      : %.2f\n",r->quiz2);
        if(r->quiz3 != -1) printf("Quiz 3      : %.2f\n",r->quiz3);
        if(r->mid != -1) printf("Mid Term    : %.2f\n",r->mid);
        if(r->final != -1) printf("Final Exam  : %.2f\n",r->final);
        
        printf("------------------------------\n");
    }
    pause();
}

/* ---------------- Student Login ---------------- */

void studentMenu(){
    clearScreen();
    char temp[200];

    printf("ID (C to cancel): "); 
    fgets(temp,200,stdin);
    if(temp[0]=='C' || temp[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    int id = atoi(temp);

    printf("Password (C to cancel): "); 
    char pass[20];
    fgets(pass,20,stdin);
    if(pass[0]=='C' || pass[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    pass[strcspn(pass,"\n")] = 0;

    int x = findStudent(id);

    if(x==-1 || strcmp(pass, students[x].password)!=0){
        printf("Login Failed.\n");
        pause();
        return;
    }

    int ch;

    do{
        clearScreen();
        printf("\n--- Student Menu ---\n");
        printf("1.View Profile\n");
        printf("2.Registered Courses\n");
        printf("3.View Results\n");
        printf("4.Change Password\n");
        printf("5.Logout\n");

        printf("Choose: ");
        fgets(temp,200,stdin);
        ch = atoi(temp);

        switch(ch){

        case 1:
            clearScreen();
            printf("\n----------- Your Profile -----------\n");

            printf("ID          : %d\n", students[x].id);
            printf("Full Name   : %s", students[x].name);
            printf("Department  : %s", students[x].dept);
            printf("Gender      : %s", students[x].gender);
            printf("DOB         : %s", students[x].dob);
            printf("Blood Group : %s", students[x].blood);
            printf("Address     : %s", students[x].address);
            printf("Phone       : %s", students[x].phone);
            printf("CGPA        : %.2f\n", students[x].cgpa);

            printf("------------------------------------\n");

            pause();
            break;

        case 2:
            clearScreen();
            printf("\n------ Registered Courses ------\n");

            if(students[x].courseCount == 0){
                printf("No courses registered.\n");
                pause();
                break;
            }

            int displayCount = 0;
            for(int i=0; i<students[x].courseCount; i++){

                int c = findCourse(students[x].courseList[i]);

                if(c != -1){
                    displayCount++;
                    printf("\n------------------------------\n");
                    printf("%d. Course Code  : %s\n", displayCount, courses[c].code);
                    printf("   Course Title : %s\n", courses[c].title);
                    printf("   Credits      : %d\n", courses[c].credit);
                    printf("------------------------------\n");
                }
            }

            if(displayCount == 0){
                printf("Not assigned\n");
            }

            pause();
            break;

        case 3:
            viewResults(x);
            break;

        case 4:
            clearScreen();

            char newpass[20];
            char temp2;

            printf("New Password (C to cancel): ");
            fgets(newpass,20,stdin);

            if(newpass[0]=='C' || newpass[0]=='c'){
                printf("Password change cancelled.\n");
                pause();
                break;
            }

            newpass[strcspn(newpass,"\n")] = 0;

            while(1){

                printf("\nPress C to CANCEL or S to SAVE: ");
                temp2 = getchar();

                if(temp2=='C' || temp2=='c'){
                    printf("Password change cancelled.\n");
                    flush();
                    pause();
                    break;
                }

                if(temp2=='S' || temp2=='s'){
                    strcpy(students[x].password,newpass);
                    printf("Password changed successfully.\n");
                    flush();
                    pause();
                    break;
                }

                printf("Invalid key! Press S to save or C to cancel.\n");

                flush();
            }

            break;

        }

    }while(ch!=5);
}

/* ---------------- Admin ---------------- */

void changeAdminPass(){
    clearScreen();
    char temp[20];

    printf("New Admin Password (C to cancel): ");
    fgets(temp,20,stdin);

    if(temp[0]=='C' || temp[0]=='c'){printf("Cancelled.\n");pause();return;}

    temp[strcspn(temp,"\n")]=0;
    strcpy(adminPass,temp);

    printf("Password Updated.\n");
    pause();
}

void studentMgmt(){
    int ch;
    char temp[200];

    do{
        clearScreen();
        printf("\n-- Student Mgmt --\n");
        printf("1.Create\n2.Update\n3.Delete\n4.Back\nChoose: ");
        fgets(temp,200,stdin);
        ch = atoi(temp);

        switch(ch){
        case 1: createStudent(); break;
        case 2: updateStudent(); break;
        case 3: deleteStudent(); break;
        }
    }while(ch!=4);
}

void courseMgmt(){
    int ch;
    char temp[200];

    do{
        clearScreen();
        printf("\n-- Course Mgmt --\n");
        printf("1.Create\n2.Display\n3.Delete\n4.Assign\n5.Unassign\n6.Back\nChoose: ");
        fgets(temp,200,stdin);
        ch = atoi(temp);

        switch(ch){
        case 1: createCourse(); break;
        case 2: displayCourses(); break;
        case 3: deleteCourse(); break;
        case 4: assignCourse(); break;
        case 5: unassignCourse(); break;
        }
    }while(ch!=6);
}

void admin(){
    clearScreen();
    char u[20],p[20];

    printf("Admin Login\nUsername (C to cancel): ");
    fgets(u,20,stdin);
    if(u[0]=='C' || u[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    u[strcspn(u,"\n")] = 0;

    printf("Password (C to cancel): ");
    fgets(p,20,stdin);
    if(p[0]=='C' || p[0]=='c'){ printf("Cancelled.\n"); pause(); return; }
    p[strcspn(p,"\n")] = 0;

    if(strcmp(u,"admin")!=0 || strcmp(p,adminPass)!=0){
        printf("Wrong login\n"); pause(); return;
    }

    int ch;
    char temp[200];

    do{
        clearScreen();
        printf("\n--- Admin Menu ---\n");
        printf("1.Student Mgmt\n2.Course Mgmt\n3.Display Students\n");
        printf("4.Display Courses\n5.Add Result\n6.Change Password\n");
        printf("7.Save\n8.Load\n9.Logout\nChoose: ");

        fgets(temp,200,stdin);
        ch = atoi(temp);

        switch(ch){
        case 1: studentMgmt(); break;
        case 2: courseMgmt(); break;
        case 3: displayStudents(); break;
        case 4: displayCourses(); break;
        case 5: addResult(); break;
        case 6: changeAdminPass(); break;
        case 7: save(); pause(); break;
        case 8: load(); pause(); break;
        }

    }while(ch!=9);
}

/* ---------------- Main ---------------- */

int main(){
    load();

    int ch;
    char temp[200];

    do{
        clearScreen();
        printf("\n=== Student Management System ===\n");
        printf("1.Admin Login\n2.Student Login\n3.Exit\nChoose: ");
        fgets(temp,200,stdin);
        ch = atoi(temp);

        switch(ch){
        case 1: admin(); break;
        case 2: studentMenu(); break;
        }

    }while(ch!=3);

    save();

    return 0;
}
