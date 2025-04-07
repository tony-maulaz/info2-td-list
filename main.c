#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_file()
{
    // data.txt
    FILE* f = fopen("data.txt", "w");
    if (f)
    {
        fprintf(f, "5\n12\n8\n1\n19\n");
        fclose(f);
    }

    // data2.txt
    f = fopen("data2.txt", "w");
    if (f)
    {
        fprintf(f, "10\n20\n30\n");
        fclose(f);
    }

    // data3.txt
    f = fopen("data3.txt", "w");
    if (f)
    {
        fprintf(f, "1\n2\n3\n4\n5\n");
        fclose(f);
    }

    // data_vide.txt
    f = fopen("data_vide.txt", "w");
    if (f)
    {
        fclose(f);  // fichier vide
    }
}

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

typedef struct
{
    Node* head;
    Node* tail;
} List;

// Fonctions de base
void append(List* list, int value)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    if (list->tail)
        list->tail->next = new_node;
    else
        list->head = new_node;
    list->tail = new_node;
}

void free_list(List* list)
{
    Node* current = list->head;
    while (current)
    {
        Node* tmp = current;
        current = current->next;
        free(tmp);
    }
    list->head = list->tail = NULL;
}

void print_list(const List* list)
{
    Node* current = list->head;
    printf("Liste :");
    while (current)
    {
        printf(" %d", current->value);
        if (current->next) printf(" ->");
        current = current->next;
    }
    printf("\n");
}

void reverse_list(List* list)
{
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    list->tail = list->head;
    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

int sum_list(const List* list)
{
    int sum = 0;
    for (Node* cur = list->head; cur; cur = cur->next) sum += cur->value;
    return sum;
}

int min_list(const List* list)
{
    if (!list->head) return 0;
    int min = list->head->value;
    for (Node* cur = list->head; cur; cur = cur->next)
        if (cur->value < min) min = cur->value;
    return min;
}

int max_list(const List* list)
{
    if (!list->head) return 0;
    int max = list->head->value;
    for (Node* cur = list->head; cur; cur = cur->next)
        if (cur->value > max) max = cur->value;
    return max;
}

void filter_list(List* list, int threshold)
{
    Node* current = list->head;
    Node* prev = NULL;
    while (current)
    {
        if (current->value < threshold)
        {
            Node* to_delete = current;
            if (prev)
                prev->next = current->next;
            else
                list->head = current->next;

            if (current == list->tail) list->tail = prev;

            current = current->next;
            free(to_delete);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

void usage()
{
    printf("Utilisation : ./app <fichier> [options]\n\n");
    printf("Options disponibles :\n");
    printf("  --reverse         Inverse l'ordre des éléments\n");
    printf("  --sum             Affiche la somme des éléments\n");
    printf("  --filter <val>    Filtre les éléments >= val\n");
    printf("  --add <val>       Ajoute une valeur à la fin du fichier\n");
    printf("  --help            Affiche ce message d'aide\n");
    printf("  --version, -v     Affiche la version du programme\n");
    printf("  --min             Affiche la valeur minimale de la liste\n");
    printf("  --max             Affiche la valeur maximale de la liste\n");
}

// Lecture fichier
bool read_file(const char* filename, List* list)
{
    FILE* f = fopen(filename, "r");
    if (!f) return false;
    int value;
    while (fscanf(f, "%d", &value) == 1) append(list, value);
    fclose(f);
    return true;
}

bool add_to_file(const char* filename, int value)
{
    FILE* f = fopen(filename, "a");
    if (!f) return false;
    fprintf(f, "%d\n", value);
    fclose(f);
    return true;
}

int main(int argc, char* argv[])
{
    init_file();

    if (argc < 2)
    {
        fprintf(stderr, "Erreur : fichier manquant\n");
        return 1;
    }

    const char* filename = NULL;
    bool has_add = false;
    int add_value = 0;
    bool reverse = false, do_sum = false, do_min = false, do_max = false;
    int filter_value = 0;
    bool do_filter = false;

    // Analyse des arguments (dans n'importe quel ordre)
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            usage();
            return 0;
        }
        else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0)
        {
            printf("version 1.0\n");
            return 0;
        }
        else if (strcmp(argv[i], "--reverse") == 0)
        {
            reverse = true;
        }
        else if (strcmp(argv[i], "--sum") == 0)
        {
            do_sum = true;
        }
        else if (strcmp(argv[i], "--min") == 0)
        {
            do_min = true;
        }
        else if (strcmp(argv[i], "--max") == 0)
        {
            do_max = true;
        }
        else if (strcmp(argv[i], "--filter") == 0 && i + 1 < argc)
        {
            filter_value = atoi(argv[++i]);
            do_filter = true;
        }
        else if (strcmp(argv[i], "--add") == 0 && i + 1 < argc)
        {
            add_value = atoi(argv[++i]);
            has_add = true;
        }
        else if (argv[i][0] != '-')
        {
            if (filename == NULL)
                filename = argv[i];
            else
            {
                fprintf(stderr, "Erreur : plusieurs fichiers spécifiés\n");
                return 1;
            }
        }
        else
        {
            fprintf(stderr, "Option inconnue : %s\n", argv[i]);
            return 3;
        }
    }

    if (filename == NULL)
    {
        fprintf(stderr, "Erreur : fichier manquant\n");
        return 1;
    }

    if (has_add)
    {
        if (!add_to_file(filename, add_value))
        {
            fprintf(stderr, "Erreur : impossible d'ajouter au fichier\n");
            return 4;
        }
        printf("Valeur %d ajoutée au fichier.\n", add_value);
        return 0;
    }

    List list = {0};
    if (!read_file(filename, &list))
    {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier '%s'\n", filename);
        return 2;
    }

    if (do_filter) filter_list(&list, filter_value);
    if (reverse) reverse_list(&list);

    print_list(&list);

    if (do_sum) printf("Somme : %d\n", sum_list(&list));
    if (do_min) printf("Minimum : %d\n", min_list(&list));
    if (do_max) printf("Maximum : %d\n", max_list(&list));

    free_list(&list);
    return 0;
}