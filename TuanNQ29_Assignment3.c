#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct student
{
    char name[30];
    int ID;
    float score;
};

typedef struct student Student;

struct node
{
    Student *data;
    struct node *next;
};

typedef struct node Node;

struct list
{
    Node *head;
    Node *tail;
};

typedef struct list List;

List* InitList()
{
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Student *CreateStudentInfo()
{
    Student *new = malloc(sizeof(Student));
    char term;
    
    printf("\nStudent name: ");
    fflush(stdin);
    gets(new->name);
    while (1)
    {
        printf("\nStudent ID: ");
        if(scanf("%d%c", &new->ID, &term) != 2 || term != '\n' || new->ID <= 0) // Check input
        { 
			printf("\nPlease retry: ");       
            fseek(stdin, 0, SEEK_END);
            continue;
        }
        else
        {
            fseek(stdin, 0, SEEK_END);
            break;
        }
    }
    while (1)
    {
        printf("\nStudent math score: ");
        if(scanf("%f%c", &new->score, &term) != 2 || term != '\n' || new->score < 0 || new->score > 10)  // Check input
        {       
        	printf("\nPlease retry: "); 
            fseek(stdin, 0, SEEK_END);
            continue;
        }
        else
        {
            fseek(stdin, 0, SEEK_END);
            break;
        }
    }
    
    return new;
}

Node *CreateNode(Student *student)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode != NULL)
    {
        newNode->data = student;
        newNode->next = NULL;
    }
    else 
        printf("FAILURE!");
    
    return newNode;
}

void InsertLast(List *list, Student *student)
{
    Node *new = CreateNode(student);

    if (list->head == NULL)
    {
        list->head = new;
        list->tail = new;
        new->next = NULL;
    } 
    else
    {
        list->tail->next = new;
        list->tail = new;
        new->next = NULL;
    }
}

void InsertFirst(List *list, Student *student)
{
    Node *new = CreateNode(student);

    if (list->head == NULL)
    {
        list->head = new;
        list->tail = new;
        new->next = NULL;
    }
    else
    {
        new->next = list->head;
        list->head = new;
    }
}

void InsertKthPosition(List *list, Student *student, int k)
{
    Node *new = CreateNode(student);
    Node *current;
    int i;

    if (list->head == NULL)
    {
        list->head = new;
        list->tail = new;
        new->next = NULL;
    }
    else if (k == 1)
    {
        InsertFirst(list, student);
    }
    else
    {
        current = list->head;
        for (i = 2; i < k && current != NULL; i++)
        {
            current = current->next;
        }
        if (current == list->tail)
        {
            InsertLast(list, student);
        }
        else if (current == NULL)
        {
            printf("\nList don't have kth position. Information is stored at the end of the list.\n");
            InsertLast(list, student);
        }
        else
        {
            new->next = current->next;
            current->next = new;
        }
    }
}

void DeleteFirst(List *list)
{
    Node *old = list->head;

    if (list->head == NULL)
    {
        printf("\nList empty!");
    } 
    else
    {
        if (list->head->next == NULL)
            list->tail = NULL;
        list->head = list->head->next;
        free(old);
    }
}

void DeleteLast(List *list)
{
    Node *old = list->tail;
    Node *current = list->head;

    if (list->tail == NULL)
    {
        printf("\nList empty!");
    }
    else
    {
        if (list->head == list->tail)
        {
            list->head = list->tail = NULL;
            free(old);
        }
        else
        {
            while (current->next != list->tail)
            {
                current = current->next;
            }
            current->next = NULL;
            list->tail = current;
            free(old);
        }
    }
}

void DeleteByID(List *list, int ID)
{
    Node *current = list->head;
    Node *prev = list->head;

    while (current != NULL)
    {
        if (current->data->ID != ID)
        {
            prev = current;
            current = current->next;
        }    
        else 
            break;
    }
    
    if (current == NULL)
    {
        printf("\nList don't have this ID!");
    }
    else
    {
        if (current == list->head)
            DeleteFirst(list);
        else if (current == list->tail)
            DeleteLast(list);
        else
        {
            prev->next = current->next;
            free(current);
        }    
    }
}

Student* SearchByID(List *list, int ID)
{
    Node *current = list->head;
    Student *student;

    while(1)
    {
        if (current == NULL)
        {
            return NULL;
        }
        if (current->data->ID == ID)
        {
            break;
        }

        current = current->next;
    }

    student = current->data;

    return student;
}

void AddStudentInfo(List *list);
void AddStudentInfoInKthPosition(List *list, int k);
void RemoveStudentInfo(List *list);
void RemoveByID(List *list, int id);
void FindStudentByID(List *list, int id);
void DisplayInfo(List *list);
void InitProgram();
void ExitProgram();

List *list;

int main()
{
    list = InitList();
    int value;
    int k;
    int id;
    char term;
    
    while (1)
    {
        InitProgram();
        while (1)
        {
            if(scanf("%d%c", &value, &term) != 2 || term != '\n') 
            { 
                printf("\nPlease retry: ");            
                fseek(stdin, 0, SEEK_END); 
                continue;
            }
            else
            {
                fseek(stdin, 0, SEEK_END); 
                break;
            }
        }
    
        switch (value)
        {
        case 1:
            AddStudentInfo(list);
            system("pause");
            break;
        case 2:
            RemoveStudentInfo(list);
            system("pause");
            break;
        case 3:
            printf("\nPlease enter ID: ");
            while (1)
            {
                if(scanf("%d%c", &id, &term) != 2 || term != '\n') 
                { 
                    printf("\nPlease retry: ");            
                    fseek(stdin, 0, SEEK_END);
                    continue;
                }
                else if (id <= 0)
                {
                    printf("\nPlease retry: ");            
                    fseek(stdin, 0, SEEK_END);
                    continue;
                }
                else
                {
                    fseek(stdin, 0, SEEK_END);
                    break;
                }
            }
            FindStudentByID(list, id);
            system("pause");
            break;
        case 4:
            printf("\nPlease enter position k: ");
            while (1)
            {
                if(scanf("%d%c", &k, &term) != 2 || term != '\n' || k < 1) 
                { 
                    printf("\nPlease retry: ");            
                    fseek(stdin, 0, SEEK_END);
                    continue;
                }
                else if (k < 0)
                {
                    printf("\nPlease retry: ");            
                    fseek(stdin, 0, SEEK_END);
                    continue;
                }
                else
                {
                    fseek(stdin, 0, SEEK_END);
                    break;
                }
            }
            AddStudentInfoInKthPosition(list, k);
            system("pause");
            break;
        case 5:
            printf("\nPlease enter ID: ");
            while (1)
            {
                if(scanf("%d%c", &id, &term) != 2 || term != '\n' || id <= 0) 
                { 
                    printf("\nPlease retry: ");            
                    fseek(stdin, 0, SEEK_END);
                    continue;
                }
                else if (id < 0)
                {
                    printf("\nPlease retry: ");            
                    fseek(stdin, 0, SEEK_END);
                    continue;
                }
                else
                {
                    fseek(stdin, 0, SEEK_END);
                    break;
                }
            }
            RemoveByID(list, id);
            system("pause");
            break;
        case 6:
            DisplayInfo(list);
            system("pause");
            break;
        case 0:
            ExitProgram();
            break;
        default:
            break;
        }
        system("cls");
    }

    return 0;
}

void InitProgram()
{
    printf("-------------------- Student management program --------------------");
    printf("\n\nPlease:");
    printf("\n - Press 1 to add student information to the end of the list");
    printf("\n - Press 2 to remove student information from the end of the list");
    printf("\n - Press 3 to find student information by ID");
    printf("\n - Press 4 to add student information by position");
    printf("\n - Press 5 to remove student information by ID");
    printf("\n - Press 6 to display student information");
    printf("\n - Press 0 to exit program");
    printf("\n\n You press: ");
}

void AddStudentInfo(List *list)
{
    Student *p;
    Student *temp;
    p = CreateStudentInfo();
    temp = SearchByID(list, p->ID);
    if (temp != NULL)
    {
        printf("\nThis ID has exist!\n");
    }
    else
    {
        InsertLast(list, p);
        //InsertFirst(l, p);
        DisplayInfo(list);
    }   
}

void AddStudentInfoInKthPosition(List *list, int k)
{
    Student *p;
    Student *temp;
    p = CreateStudentInfo();
    temp = SearchByID(list, p->ID);
    if (temp != NULL)
    {
        printf("\nThis ID has exist!\n");
    }
    else
    {
        InsertKthPosition(list, p, k);
        DisplayInfo(list);
    }  
}

void RemoveStudentInfo(List *list)
{
    DeleteLast(list);
    //DeleteFisrt(list);
    DisplayInfo(list);
}

void RemoveByID(List *list, int id)
{
    DeleteByID(list, id);
    DisplayInfo(list);
}

void FindStudentByID(List *list, int id)
{
    Student *p;
    p = SearchByID(list, id);
    if (p != NULL)
    {
        printf("\nFound student with ID %d\n", id);
        printf("\nName: %s", p->name);
        printf("\nID: %d", p->ID);
        printf("\nMath score: %.2f\n", p->score);
    }
    else 
    {
        printf("\nNot found student with ID %d\n", id);
    }
}

void DisplayInfo(List *list)
{
    if (list->head == NULL && list->tail == NULL)
    {
        printf("\n--> List empty!\n\n");
    }
    else
    {
        printf("\n--> Student information: \n");
        Node *current = list->head;
        while (current != NULL)
        {
            printf("\nName: %s", current->data->name);
            printf("\nID: %d", current->data->ID);
            printf("\nMath score: %.2f\n", current->data->score);
            current = current->next;
        }
        printf("\n\n");
    }  
}

void ExitProgram()
{
    printf("\nExiting program...\n\n");
    sleep(1);
    exit(0);
}
