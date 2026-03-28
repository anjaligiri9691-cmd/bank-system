#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[50];
    char type[10];
    float balance;
};

void createAccount() {
    struct Account acc;
    FILE *fp;

    fp = fopen("accounts.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);
    while(getchar() != '\n');

    printf("Enter Name: ");
    fgets(acc.name, 50, stdin);
    acc.name[strcspn(acc.name, "\n")] = 0;

    printf("Enter Account Type (savings/current): ");
    fgets(acc.type, 10, stdin);
    acc.type[strcspn(acc.type, "\n")] = 0;

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("Account created successfully!\n");
}

void viewAllAccounts() {
    struct Account acc;
    FILE *fp;

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    printf("\n%-10s %-20s %-10s %-10s\n",
           "Acc No", "Name", "Type", "Balance");
    printf("--------------------------------------------\n");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        printf("%-10d %-20s %-10s %-10.2f\n",
               acc.accountNumber, acc.name,
               acc.type, acc.balance);
    }

    fclose(fp);
}

void deposit() {
    struct Account acc;
    FILE *fp;
    int accNo;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while(getchar() != '\n');

    fp = fopen("accounts.dat", "rb+");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("Deposited successfully! New balance: %.2f\n",
                   acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) printf("Account not found!\n");
    fclose(fp);
}

void withdraw() {
    struct Account acc;
    FILE *fp;
    int accNo;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while(getchar() != '\n');

    fp = fopen("accounts.dat", "rb+");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > acc.balance) {
                printf("Insufficient balance!\n");
            } else {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("Withdrawn successfully! New balance: %.2f\n",
                       acc.balance);
            }
            found = 1;
            break;
        }
    }

    if (!found) printf("Account not found!\n");
    fclose(fp);
}

void checkBalance() {
    struct Account acc;
    FILE *fp;
    int accNo;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while(getchar() != '\n');

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accNo) {
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) printf("Account not found!\n");
    fclose(fp);
}

void searchAccount() {
    struct Account acc;
    FILE *fp;
    int accNo;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while(getchar() != '\n');

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accNo) {
            printf("\nAccount Number: %d\n", acc.accountNumber);
            printf("Name: %s\n", acc.name);
            printf("Type: %s\n", acc.type);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) printf("Account not found!\n");
    fclose(fp);
}

void deleteAccount() {
    struct Account acc;
    FILE *fp, *temp;
    int accNo;
    int found = 0;

    printf("Enter Account Number to delete: ");
    scanf("%d", &accNo);
    while(getchar() != '\n');

    fp = fopen("accounts.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accNo) {
            found = 1;
        } else {
            fwrite(&acc, sizeof(acc), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found) printf("Account deleted successfully!\n");
    else printf("Account not found!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. View All Accounts\n");
        printf("6. Search Account\n");
        printf("7. Delete Account\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: viewAllAccounts(); break;
            case 6: searchAccount(); break;
            case 7: deleteAccount(); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);

    return 0;
}
