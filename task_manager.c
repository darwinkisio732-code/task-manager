#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100

struct Task
{
    char title[100];
    int priority; // 1: High, 2: Medium, 3: Low
    int status;   // 0: Pending, 1: Done
    char dueDate[12];
};

// Helper function to safely flush stdin buffer
void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addTask(struct Task s[], int *count)
{
    int numToAdd;

    printf("\nEnter number of Tasks: ");
    if (scanf("%d", &numToAdd) != 1 || numToAdd <= 0)
    {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("\n===============INPUT TASK DETAILS================");
    for (int i = 0; i < numToAdd; i++)
    {
        if (*count >= MAX_TASKS)
        {
            printf("\nTask limit reached (%d max)!", MAX_TASKS);
            break;
        }

        int idx = *count;
        printf("\n----- Task %d -----", idx + 1);

        printf("\nTitle: ");
        fgets(s[idx].title, sizeof(s[idx].title), stdin);
        s[idx].title[strcspn(s[idx].title, "\n")] = 0;

        printf("Priority (1-High, 2-Medium, 3-Low): ");
        scanf("%d", &s[idx].priority);
        clearBuffer();

        s[idx].status = 0; // Default to Pending

        printf("Due Date (DD/MM/YYYY): ");
        fgets(s[idx].dueDate, sizeof(s[idx].dueDate), stdin);
        s[idx].dueDate[strcspn(s[idx].dueDate, "\n")] = 0;

        (*count)++;
    }
    printf("\nTasks added successfully!\n");
}

void printTaskRow(struct Task t)
{
    char *priorityText = (t.priority == 1) ? "High" : (t.priority == 2) ? "Medium" : "Low";
    char *statusText = (t.status == 0) ? "Pending" : "Done";

    printf("\n%-25s %-10s %-10s %-15s", t.title, priorityText, statusText, t.dueDate);
}

void viewAll(struct Task s[], int count)
{
    printf("\n===========================================================");
    printf("\n===================== AVAILABLE TASKS =====================");
    printf("\n%-25s %-10s %-10s %-15s", "Title", "Priority", "Status", "Due Date");
    printf("\n-----------------------------------------------------------");

    for (int i = 0; i < count; i++)
    {
        printTaskRow(s[i]);
    }
    printf("\n-----------------------------------------------------------\n");
}

void viewPending(struct Task s[], int count)
{
    int found = 0;

    printf("\n===========================================================");
    printf("\n====================== PENDING TASKS ======================");
    printf("\n%-25s %-10s %-10s %-15s", "Title", "Priority", "Status", "Due Date");
    printf("\n-----------------------------------------------------------");

    for (int i = 0; i < count; i++)
    {
        if (s[i].status == 0)
        {
            found = 1;
            printTaskRow(s[i]);
        }
    }

    if (!found)
    {
        printf("\nNo pending tasks found!");
    }
    printf("\n-----------------------------------------------------------\n");
}

void markDone(struct Task s[], int count)
{
    char search[100];
    int found = 0, choice;

    printf("\n=============== MARK TASK AS DONE ===============");
    printf("\nEnter Title: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(s[i].title, search) == 0)
        {
            found = 1;
            if (s[i].status == 1)
            {
                printf("Task is already marked as Done!\n");
                return;
            }

            printf("\nMark \"%s\" as Done?\n1. Yes\n2. No\nOption: ", s[i].title);
            scanf("%d", &choice);
            clearBuffer();

            if (choice == 1)
            {
                s[i].status = 1;
                printf("Status updated to Done!\n");
            }
            else
            {
                printf("Action cancelled.\n");
            }
            break;
        }
    }

    if (!found)
    {
        printf("Task NOT found!\n");
    }
}

void deleteTask(struct Task s[], int *count)
{
    char search[100];
    int found = 0;

    printf("\n=============== DELETE TASK ===============");
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
            printf("Task Deleted Successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("Task NOT found!\n");
    }
}

int handleEmptyList(struct Task task[], int *count)
{
    int choice;
    printf("\nNo tasks available. Do you want to add one?\n1. Yes\n2. No\nOption: ");
    scanf("%d", &choice);
    clearBuffer();

    if (choice == 1)
    {
        addTask(task, count);
        return 1;
    }
    return 0;
}

int main()
{
    struct Task task[MAX_TASKS];
    int count = 0;
    int choice;

    do
    {
        printf("\n=============== TASK MANAGER ===============");
        printf("\n1. ADD TASK");
        printf("\n2. VIEW ALL");
        printf("\n3. VIEW PENDING");
        printf("\n4. MARK DONE");
        printf("\n5. DELETE TASK");
        printf("\n6. EXIT");
        printf("\n\nOption: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid selection! Try again.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice)
        {
        case 1:
            addTask(task, &count);
            break;

        case 2:
            if (count > 0)
                viewAll(task, count);
            else
                handleEmptyList(task, &count);
            break;

        case 3:
            if (count > 0)
                viewPending(task, count);
            else
                handleEmptyList(task, &count);
            break;

        case 4:
            if (count > 0)
                markDone(task, count);
            else
                printf("\nNo tasks to update!\n");
            break;

        case 5:
            if (count > 0)
                deleteTask(task, &count);
            else
                printf("\nNo tasks to delete!\n");
            break;

        case 6:
            printf("\nThank You! Goodbye!\n");
            break;

        default:
            printf("\nPlease enter a valid menu option (1-6).\n");
            break;
        }
    } while (choice != 6);

    return 0;
}
