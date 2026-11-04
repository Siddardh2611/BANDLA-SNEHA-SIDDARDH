#include <stdio.h>
#include <stdlib.h>

struct student
{
    char name[100];
    int roll;
    char phone[15];   /* char array: a 10-digit number overflows int */
    float marks;
};

void display(struct student *s, int n)
{
    struct student *ptr;
    if (n == 0)
    {
        printf("NO STUDENTS FOUND\n");
        return;
    }
    for (ptr = s; ptr < s + n; ptr++)
    {
        printf("NAME OF STUDENT = %s\n", ptr->name);
        printf("ROLL NUMBER = %d\n", ptr->roll);
        printf("CONTACT NUMBER = %s\n", ptr->phone);
        printf("MARKS OBTAINED = %.2f\n\n", ptr->marks);
    }
}

void readStudent(struct student *ptr)
{
    printf("ENTER THE NAME\n");
    scanf(" %99[^\n]", ptr->name);
    printf("ENTER THE ROLL NUMBER\n");
    scanf("%d", &ptr->roll);
    printf("ENTER THE CONTACT NUMBER\n");
    scanf("%14s", ptr->phone);
    printf("ENTER THE MARKS\n");
    scanf("%f", &ptr->marks);
}

void sortByRoll(struct student *s, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if ((s + j)->roll > (s + j + 1)->roll)
            {
                struct student temp = *(s + j);
                *(s + j) = *(s + j + 1);
                *(s + j + 1) = temp;
            }
}

void sortByMarks(struct student *s, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if ((s + j)->marks < (s + j + 1)->marks)
            {
                struct student temp = *(s + j);
                *(s + j) = *(s + j + 1);
                *(s + j + 1) = temp;
            }
}

int main(void)
{
    struct student *s, *ptr;
    int n, i;

    printf("ENTER THE NUMBER OF STUDENTS\n");
    scanf("%d", &n);

    /* dynamic memory instead of a fixed array of 100 */
    s = (struct student *)malloc(n * sizeof(struct student));
    if (s == NULL)
    {
        printf("MEMORY ALLOCATION FAILED\n");
        return 1;
    }

    i = 1;
    for (ptr = s; ptr < s + n; ptr++)
    {
        printf("ENTER THE DETAILS OF STUDENT %d\n", i++);
        readStudent(ptr);
    }

    printf("\n--- STUDENT DETAILS ---\n");
    display(s, n);

    int des;
    printf("ENTER 1 IF YOU WANT TO MAKE ANY CHANGES TO THE DATA\n");
    scanf("%d", &des);

    while (des == 1)
    {
        int choice;   /* separate variable, so n (student count) is not lost */
        printf("ENTER\n 1 TO ADD A NEW STUDENT\n 2 TO DELETE A STUDENT\n"
               " 3 TO SORT BY ROLL NUMBER\n 4 TO SORT BY MARKS\n"
               " 5 TO FIND A STUDENT\n 6 TO DISPLAY ALL\n 0 TO EXIT\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                struct student *temp = realloc(s, (n + 1) * sizeof(struct student));
                if (temp == NULL)
                {
                    printf("MEMORY ALLOCATION FAILED\n");
                    break;
                }
                s = temp;
                printf("ENTER THE DETAILS OF THE STUDENT YOU WANT TO ADD\n");
                readStudent(s + n);   /* the new slot at the end */
                n++;
                break;
            }
            case 2:
            {
                int roll, found = -1;
                printf("ENTER THE ROLL NUMBER TO DELETE\n");
                scanf("%d", &roll);
                for (i = 0; i < n; i++)
                    if ((s + i)->roll == roll)
                    {
                        found = i;
                        break;
                    }
                if (found == -1)
                {
                    printf("STUDENT NOT FOUND\n");
                    break;
                }
                for (i = found; i < n - 1; i++)
                    *(s + i) = *(s + i + 1);   /* shift records left */
                n--;
                if (n > 0)
                {
                    struct student *temp = realloc(s, n * sizeof(struct student));
                    if (temp != NULL)
                        s = temp;
                }
                printf("STUDENT DELETED\n");
                break;
            }
            case 3:
                sortByRoll(s, n);
                display(s, n);
                break;
            case 4:
                sortByMarks(s, n);
                display(s, n);
                break;
            case 5:
            {
                int roll, found = 0;
                printf("ENTER THE ROLL NUMBER TO FIND\n");
                scanf("%d", &roll);
                for (ptr = s; ptr < s + n; ptr++)
                    if (ptr->roll == roll)
                    {
                        display(ptr, 1);
                        found = 1;
                        break;
                    }
                if (!found)
                    printf("STUDENT NOT FOUND\n");
                break;
            }
            case 6:
                display(s, n);
                break;
            case 0:
                des = 0;
                break;
            default:
                printf("INVALID CHOICE\n");
        }
    }

    free(s);
    return 0;
}
