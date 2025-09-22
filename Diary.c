#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Diary
{

    char date[11];
    char note[1000];

} Diary;

Diary d;
void Add_Note();
void View_Note();
int main()
{
int choice;

while(1)
{
    printf("Menu \n 1.Add note to the diary \n 2.View note from the diary\n 3.Exit:\n Enter Choice:");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1: Add_Note();
            break;
        case 2:
                View_Note();
            break;
        case 3:
                exit(0);
            break;
        default :
                printf("Invalid Choice! \n");
                
    }
}
    return 0;
}
#define DATA_FILE "Diary.txt"
void Add_Note()
{
    printf("Enter date (DD-MM-YYYY):");
    scanf("%10s", d.date);

    while (getchar() != '\n')
        ;

    printf("Enter note:");
    fgets(d.note, sizeof(d.note), stdin);
    d.note[strcspn(d.note, "\n")] = 0;

    FILE *ptr = fopen(DATA_FILE, "a");
    if (ptr == NULL)
    {
        printf("Error opening file! \n");
        return;
    }
    fprintf(ptr, "%s|%s\n", d.date, d.note);
    fclose(ptr);
    printf("Notes added sucessfully. \n");
}
void View_Note()
{
    FILE *ptr = fopen(DATA_FILE, "r");
    char *buffer;
    long length;
    size_t read_size;
    if (!ptr)
    {
        printf("No notes found.");
        return;
    }

    fseek(ptr, 0, SEEK_END);
    length = ftell(ptr);
    fseek(ptr, 0, SEEK_SET);
    buffer = (char *)malloc(length + 1);

    if (buffer == NULL)
    {
        perror("Error!");
        fclose(ptr);
        return;
    }
    printf("Date   |    Note\n");
    printf("--------------------- \n");
    read_size = fread(buffer, 1, length, ptr);
    buffer[read_size] = '\0';
    fclose(ptr);
    printf("\n%s\n", buffer);
    free(buffer);
}
