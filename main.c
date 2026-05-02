#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int no_special = 0;
int no_numbers = 0;
int no_lowercase = 0;
int no_uppercase = 0;

const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char numbers[] = "0123456789";
const char special[] = "!@#$%^&*()_-+={}[]|;:,.<>?";

void generate_password(int size, int use_lower, int use_upper, int use_num, int use_spec) {
    char charset[128] = "";
    if (use_lower) strcat(charset, lowercase);
    if (use_upper) strcat(charset, uppercase);
    if (use_num) strcat(charset, numbers);
    if (use_spec) strcat(charset, special);

    int charset_length = strlen(charset);
    if (charset_length == 0) {
        printf("No characters available to generate password.\n");
        exit(1);
    }

    char password[size + 1];
    srand(time(0));

    for (int i = 0; i < size; i++) {
        password[i] = charset[rand() % charset_length];
    }
    password[size] = '\0';

    printf("%s\n", password);
}

int main(int argc, char const *argv[])
{
    int has_h = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            has_h = 1;
        }
    }
    if (has_h) {
        printf("Usage: %s <size> [-nn] [-ns] [-nl] [-nu] [-h]\n", argv[0]);
        printf("Options:\n");
        printf("  -nn  No numbers\n");
        printf("  -ns  No special characters\n");
        printf("  -nl  No lowercase letters\n");
        printf("  -nu  No uppercase letters\n");
        printf("  -h   Show this help message\n");
        exit(0);
    }

    if (argc < 2) {
        printf("Usage: %s <size> [-nn] [-ns] [-nl] [-nu]\n", argv[0]);
        exit(1);
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        printf("Password size must be a positive integer.\n");
        exit(1);
    }

    int use_lower = 1, use_upper = 1, use_num = 1, use_spec = 1;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printf("Usage: %s <size> [-nn] [-ns] [-nl] [-nu] [-h]\n", argv[0]);
            printf("Options:\n");
            printf("  -nn  No numbers\n");
            printf("  -ns  No special characters\n");
            printf("  -nl  No lowercase letters\n");
            printf("  -nu  No uppercase letters\n");
            printf("  -h   Show this help message\n");
            exit(0);
        } else if (strcmp(argv[i], "-nn") == 0) {
            use_num = 0;
        } else if (strcmp(argv[i], "-ns") == 0) {
            use_spec = 0;
        } else if (strcmp(argv[i], "-nl") == 0) {
            use_lower = 0;
        } else if (strcmp(argv[i], "-nu") == 0) {
            use_upper = 0;
        }
    }

    generate_password(size, use_lower, use_upper, use_num, use_spec);

    return 0;
}
