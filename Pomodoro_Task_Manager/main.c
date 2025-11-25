#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

void add_task();
void header();
void press_enter_to_continue();
int timer(int minutes);
void quotes();
void view();
void update_time(int time,int position);
void work();
void remove_task();
void completed_tasks();
void other_options();

int main()
{
    srand(time(NULL));
    int choice;
    char choice_buffer[10];
    do {
        system("cls");
        header();
        printf("Choose Option Number\n");
        printf("[1]--Add New Task\n");
        printf("[2]--View All Tasks\n");
        printf("[3]--Work on a Task\n");
        printf("[4]--Complete a Task\n");
        printf("[5]--Other Options\n");
        printf("[6]--Exit Program\n");
        printf("\nSelect an option:\n");
        fgets(choice_buffer, 10, stdin);
        choice = atoi(choice_buffer);
        switch (choice){
            case 1:
                system("cls");
                printf("--ADD TASK--\n");
                add_task();
                press_enter_to_continue();
                break;

            case 2:
                system("cls");
                printf("--- VIEWING ALL TASKS ---\n");
                view();
                press_enter_to_continue();
                break;
            case 3:
                system("cls");
                work();
                press_enter_to_continue();
                break;
            case 4:
                system("cls");
                printf("--- REMOVE A TASK ---\n");
                printf("\n");
                remove_task();
                press_enter_to_continue();
                break;
            case 5:
                system("cls");
                other_options();
                press_enter_to_continue();
                break;

            case 6:
                printf("Goodbye! Stay Productive!\n");
                printf("Exiting Program....\n");
                break;
            default:
                printf("\nInvalid choice. Please enter 1, 2, 3,4,5 or 6.\n");
                Sleep(2000);
                break;

        }


    }while (choice!=6);

}
