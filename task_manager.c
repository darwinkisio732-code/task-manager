#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100

struct Task
{
    char title[100];
    int priority;
    int status;
    char dueDate[12];
};

void addTask(struct Task s[], int *count)
{
    int numToAdd;

    printf("\nEnter number of Tasks: ");
    scanf("%d", &numToAdd);
    getchar();

    printf("\n\n===============INPUT TASK DETAILS================");
    for (int i = 0; i < numToAdd; i++)
    {
        if (*count >= MAX_TASKS)
        {
            printf("\nToo many Tasks!");
            break;
        }

        printf("\n-----Task %d-----", i + 1);

        int idx = *count;
        printf("\nTitle: ");
        fgets(s[idx].title, sizeof(s[idx].title), stdin);
        s[idx].title[strcspn(s[idx].title, "\n")] = 0;

        printf("\nPriority: ");
        scanf("%d", &s[idx].priority);
        getchar();

        s[idx].status = 0;

        printf("\nDue Date: ");
        fgets(s[idx].dueDate, sizeof(s[idx].dueDate), stdin);
        s[idx].dueDate[strcspn(s[idx].dueDate, "\n")] = 0;

        (*count)++;
    }
}

void viewAll(struct Task s[], int count)
{
    printf("\n\n====================================================");
    printf("\n===================AVAILABLE TASKS===================");
    printf("\n%-20s %-10s %-10s %-20s",
           "Title",
           "Priority",
           "Status",
           "Due Date");
    printf("\n-----------------------------------------------------");

    for (int i = 0; i < count; i++)
    {
        char *priorityText = (s[i].priority == 1) ? "High" : (s[i].priority == 2) ? "Medium"
                                                                                  : "Low";
        char *statusText = (s[i].status == 0) ? "Pending" : "Done";

        printf("\n%-20s %-10s %-10s %-20s",
               s[i].title,
               priorityText,
               statusText,
               s[i].dueDate);
    }
    printf("\n----------------------------------------------------");
}

void viewPendingSorted(struct Task s[], int count)
{
    int found = 0;

    printf("\n\n======================================================");
    printf("\n=====================PENDING TASKS=====================");
    printf("\n%-20s %-10s %-10s %-20s",
           "Title",
           "Priority",
           "Status",
           "Due Date");
    printf("\n-------------------------------------------------------");
    for (int i = 0; i < count; i++)
    {
        if (s[i].status == 0)
        {
            found = 1;
            char *priorityText = (s[i].priority == 1) ? "High" : (s[i].priority == 2) ? "Medium"
                                                                                      : "Low";
            char *statusText = (s[i].status == 0) ? "Pending" : "Done";

            printf("\n%-20s %-10s %-10s %-20s",
                   s[i].title,
                   priorityText,
                   statusText,
                   s[i].dueDate);
        }
    }
    if (!found)
    {
        printf("\nNo pending Tasks found!");
    }
}

void markDone(struct Task s[], int count)
{
    char search[50];
    int found = 0, choice;

    printf("\n\n===============MARK DONE==================");

    printf("\nEnter Title: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(s[i].title, search) == 0)
        {
            found = 1;
            printf("\nMark Done? ");
            printf("\n1. Yes");
            printf("\n2. No");

            printf("\n\nOption: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                s[i].status = 1;
                break;
            case 2:
                printf("\nThanks for your participation!");
                break;
            default:
                printf("\nChoose between 1 & 2.");
                break;
            }
        }
    }
    if (!found)
    {
        printf("\nTask NOT found!");
    }
}

void deleteTask(struct Task s[], int *count)
{
    char search[50];
    int found = 0;

    printf("\n\n===============DELETE TASK===============");

    printf("\nEnter Title: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0;

    for (int i = 0; i < *count; i++)
    {
        if (strcmp(s[i].title, search) == 0)
        {
            found = 1;
            for (int j = i; j < *count - 1; j++)
            {
                s[j] = s[j + 1];
            }
            (*count)--;
            printf("\n\nTask Deleted Successfully!");
            break;
        }
    }
    if (!found)
    {
        printf("\nTask NOT found!");
    }
}

int main()
{

    struct Task task[MAX_TASKS];
    int count = 0;
    int choice, sub_choice;

    do
    {
        printf("\n\n===============TASK MANAGER===============");
        printf("\n1. ADD TASK");
        printf("\n2. VIEW ALL");
        printf("\n3. VIEW PENDING");
        printf("\n4. MARK DONE");
        printf("\n5. DELETE");
        printf("\n6. EXIT");

        printf("\n\nOption: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            addTask(task, &count);
            break;
        case 2:
            if (count > 0)
            {
                viewAll(task, count);
            }
            else
            {
                printf("\n\nNo tasks available. Do you want to Add? ");
                printf("\n1. Yes");
                printf("\n2. No");

                printf("\n\nOption: ");
                scanf("%d", &sub_choice);
                getchar();

                switch (sub_choice)
                {
                case 1:
                    addTask(task, &count);
                    break;
                case 2:
                    printf("\nHave a nice Day!");
                    break;
                default:
                    printf("\nChoose between 1 & 2. Thank You!");
                }
            }
            break;
        case 3:
            if (count > 0)
            {
                viewPendingSorted(task, count);
            }
            else
            {
                printf("\n\nNo tasks available. Do you want to Add? ");
                printf("\n1. Yes");
                printf("\n2. No");

                printf("\n\nOption: ");
                scanf("%d", &sub_choice);
                getchar();

                switch (sub_choice)
                {
                case 1:
                    addTask(task, &count);
                    break;
                case 2:
                    printf("\nHave a nice Day!");
                    break;
                default:
                    printf("\nChoose between 1 & 2. Thank You!");
                }
            }
            break;
        case 4:
            markDone(task, count);
            break;
        case 5:
            deleteTask(task, &count);
            break;
        case 6:
            printf("\nThank You! Goodbye!");
            break;
        default:
            printf("\nChoose a valid number in the menu!");
            break;
        }
    } while (choice != 6);

    return 0;
}