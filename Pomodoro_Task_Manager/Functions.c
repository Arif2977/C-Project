#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>


int worktime=25;
int breaktime=5;

void press_enter_to_continue() {
    printf("\n\nPress any key to return to the main menu...");
    _getch();
}

void header() {

    printf("\n");
    printf("\t=============================================\n");
    printf("\t  P O M O D O R O   T A S K   M A N A G E R  \n");
    printf("\t=============================================\n");
    printf("\n");

}

int timer(int minutes) {
    int total_seconds = minutes * 60;
    int is_paused = 0; // 0 = running, 1 = paused

    while (total_seconds > 0) {


        for (int i = 0; i < 10; i++) {
            if (_kbhit()) { // Check if a key press
                char key = _getch();

                if (key == 'p' || key == 'P') {
                    is_paused = !is_paused;
                } else if (key == 'q' || key == 'Q') {

                    printf("\rAre you sure you want to quit? Progress will not be saved. (y/n) ");
                    char confirm = _getch();

                    if (confirm == 'y' || confirm == 'Y') {
                        printf("\rQuitting timer...                                          \n");
                        return 0;
                    }
                }
            }
            Sleep(100); // Sleep for 1/10th of a second
        }
        int mins_remaining = total_seconds / 60;
        int secs_remaining = total_seconds % 60;

        if (is_paused) {
            printf("\rTIMER: %02d:%02d PAUSED (Press 'p' to resume, 'q' to quit)               ", mins_remaining, secs_remaining);
        }
        else {
            printf("\rTIMER: %02d:%02d RUNNING (Press 'p' to pause, 'q' to quit)              ", mins_remaining, secs_remaining);
            total_seconds--;
        }
        fflush(stdout); // Force the print
    }

    printf("\rTIMER: Time's up!                                       \n");
    fflush(stdout);

    //alarm
    for (int i = 0; i < 8; i++) {
        Beep(2600, 100);
        Sleep(50);
        Beep(2000, 100);
        Sleep(50);
    }
    Beep(1500, 1000);

    printf("\n");
    return 1;
}

void quotes() {

    char quotes[10][255];
    strcpy(quotes[0], "THE ONLY WAY TO DO GREAT WORK IS TO LOVE WHAT YOU DO.");
    strcpy(quotes[1], "SUCCESS IS NOT FINAL, FAILURE IS NOT FATAL...");
    strcpy(quotes[2], "BELIEVE YOU CAN AND YOU'RE HALFWAY THERE.");
    strcpy(quotes[3], "IT DOES NOT MATTER HOW SLOWLY YOU GO AS LONG AS YOU DO NOT STOP.");
    strcpy(quotes[4], "YOUR TIME IS LIMITED, DON'T WASTE IT...");
    strcpy(quotes[5], "NOTHING WILL WORK UNLESS YOU DO!");
    strcpy(quotes[6], "A 25-MINUTE BURST OF FOCUSED WORK IS BETTER THAN A DISTRACTED HOUR");
    strcpy(quotes[7], "DON'T STOP. ONE POMODORO AT A TIME, YOU ARE BUILDING A MOUNTAIN");
    strcpy(quotes[8], "FOCUS ON BEING PRODUCTIVE INSTEAD OF BUSY. - TIM FERRISS");
    strcpy(quotes[9], "THE SHORTER THE TIME, THE MORE INTENSE THE FOCUS. THAT'S THE POMODORO SECRET");

    int num = 10;
    int random_index = rand() % num;
    printf("--------------------------------\n");
    printf("%s\n", quotes[random_index]);
}


void view() {
    FILE *fptr1;
    FILE *fptr2;
    char txtline[100];
    char time[10];

    fptr1 = fopen("Tasks.txt", "r");
    fptr2 = fopen("Time.txt", "r");
    if (fptr1 == NULL || fptr2 == NULL) {
        printf("Error: Could not open one or both files.\n");
        printf("Make sure the files exist.\n");
        if (fptr1 != NULL) fclose(fptr1);
        if (fptr2 != NULL) fclose(fptr2);
        return;
    }
    printf("%-50s | %-15s\n", "Task", "Time Spent");
    printf("-------------------------------------------------- | ----------------\n");

    while (fgets(txtline, 100, fptr1) != NULL && fgets(time, 10, fptr2) != NULL) {
        txtline[strcspn(txtline, "\n")] = 0;
        time[strcspn(time, "\n")] = 0;
        printf("%-50s | %-15s\n", txtline, time);
    }
    fclose(fptr1);
    fclose(fptr2);
}

void update_time(int time,int position){
    char file1[20]="newtime.txt";
    char file2[20]="Time.txt";
    char line[20];
    FILE* rptr;
    FILE* wptr;
    int filepos=0;
    rptr=fopen(file2,"r");
    wptr=fopen(file1,"w");
    while(fgets(line,20,rptr)!=NULL){
        filepos++;
        if (filepos==position){
            fprintf(wptr,"%d\n",time);
        }
        else{
            fprintf(wptr,"%s",line);
        }
    }
    fclose(rptr);
    fclose(wptr);
    remove(file2);
    rename(file1,file2);
}


void work(){
    view();
    char name[50];
    char line[50];
    char time[10];
    int flag=0;
    FILE* fptr1;
    FILE* fptr2;
    int current_line=0;
    printf("\n\nEnter the name of the task you would like to work On:\n");
    fgets(name,50,stdin);
    name[strcspn(name,"\n")]=0;
    fptr1=fopen("Tasks.txt","r");
    fptr2=fopen("Time.txt","r");
    while(fgets(line,50,fptr1)!=NULL && flag==0){
        current_line++;
        fgets(time,10,fptr2);
        line[strcspn(line,"\n")]=0;
        if (strcmpi(line,name)==0){
            flag=1;
        }

    }
    fclose(fptr1);
    fclose(fptr2);

    if(flag){
        printf("\nStarting timer for %s\nGoodLuck!\n\n",name);
        quotes();
        int done=timer(worktime);
        if (done){
            printf("Time's up! Take a 5-minute break.\n");
            timer(breaktime);
            int new_time=atoi(time)+worktime;
            update_time(new_time,current_line);
            printf("Updated time spent on %s to %d minutes.\n",name,new_time);
        }
        else{
            printf("Timer exited early! Progress lost\n");
        }
    }
    else{
        printf("Task not found.\n");
    }

}

void remove_task(){
    view();
    char name [50];
    FILE * fptr;
    char line[50];
    int counter=0,flag=0;
    printf("Please enter the name of the task You would like to remove:");
    fgets(name,50,stdin);
    name[strcspn(name,"\n")]=0;
    fptr=fopen("Tasks.txt","r");
    if (fptr == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }
    while (fgets(line,50,fptr)!=NULL && flag==0){
        line[strcspn(line,"\n")]=0;
        counter++;
        if (strcmpi(line,name)==0){
            flag=1;
        }
    }
    fclose(fptr);
    if (flag){
        char file1[20]="Tasks.txt";
        char file2[20]="newtask.txt";
        char file3[20]="Time.txt";
        char file4[20]="newtime.txt";
        char writeline[50];
        char writetime[20];
        int filecounter=0;
        FILE * fptr1,*fptr2,*fptr3,*fptr4,*fptr5;
        fptr1=fopen(file1,"r");
        fptr2=fopen(file2,"w");
        fptr3=fopen(file3,"r");
        fptr4=fopen(file4,"w");
        fptr5=fopen("Completed.txt","a");

        if (fptr1 == NULL || fptr2 == NULL || fptr3 == NULL || fptr4 == NULL || fptr5 == NULL) {
            printf("Error: Could not open all files for editing.\n");
            if (fptr1) fclose(fptr1);
            if (fptr2) fclose(fptr2);
            if (fptr3) fclose(fptr3);
            if (fptr4) fclose(fptr4);
            if (fptr5) fclose(fptr5);
            return;
        }
        while(fgets(writeline,50,fptr1)!=NULL && fgets(writetime,20,fptr3)!=NULL){
            filecounter++;
            if(filecounter!=counter){
                fprintf(fptr2,writeline);
                fprintf(fptr4,writetime);
            }
            else{
                fprintf(fptr5,"Task:%s",writeline);
                fprintf(fptr5,"Time Spent:%s",writetime);
                fprintf(fptr5,"--------------------------\n");
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        fclose(fptr3);
        fclose(fptr4);
        fclose(fptr5);
        remove(file1);
        remove(file3);
        rename(file2,file1);
        rename(file4,file3);
        printf("Task '%s' removed successfully.\n",name);
    }
    else{
        printf("task not found.\n");
    }
}


void completed_tasks() {
    FILE *fptr = fopen("Completed.txt", "r");
    char line[100];

    if (fptr == NULL) {
        printf("\nNo completed tasks found (File does not exist)\n");
        return;
    }

    printf("\n--- COMPLETED TASKS HISTORY ---\n");
    while (fgets(line, 100, fptr) != NULL) {
        printf("%s", line);
    }
    fclose(fptr);
}

void other_options() {
    char buffer[10];
    int choose = 0;

    do {
        system("cls");
        printf("\n");
        printf("\t-------------------------------\n");
        printf("\t  O T H E R   O P T I O N S\n");
        printf("\t-------------------------------\n");
        printf("\nChoose one of the following:\n");
        printf("  [1] Instructions\n");
        printf("  [2] Change Timer Duration (Current: %d min)\n", worktime);
        printf("  [3] Show Completed Tasks\n");
        printf("  [4] Back to Main Menu\n");
        printf("\n  Select an option: ");
        fgets(buffer, 10, stdin);
        choose = atoi(buffer);

        switch (choose) {
            case 1:
                system("cls");
                printf("--- INSTRUCTIONS ---\n\n");
                printf("1. The Pomodoro Technique uses a timer to break down work.\n");
                printf("2. Traditionally, you work for 25 minutes, then break for 5.\n");
                printf("3. Select 'Work on a Task' to start the timer.\n");
                printf("4. Use 'p' to pause/resume and 'q' to quit the timer.\n");
                printf("5. When a task is done, remove it to archive it.\n");
                press_enter_to_continue();
                break;

            case 2:
                system("cls");
                printf("--- CHANGE TIMER DURATION ---\n\n");
                printf("Current Work Duration: %d minutes\n", worktime);
                printf("Enter new duration (in minutes): ");

                fgets(buffer, 10, stdin);
                int new_time = atoi(buffer);

                if (new_time > 0 && new_time <= 100) {
                    worktime= new_time;
                    printf("\nSuccess! Work timer set to %d minutes.\n", worktime);
                } else {
                    printf("\nInvalid time. Please enter 1-100 minutes.\n");
                }
                press_enter_to_continue();
                break;

            case 3:
                system("cls");
                completed_tasks();
                press_enter_to_continue();
                break;

            case 4:

                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
                Sleep(1000);
                break;
        }

    } while (choose != 4);
}
