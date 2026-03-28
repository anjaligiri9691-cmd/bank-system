#include <stdio.h>

int main() {
    int choice;
    printf("===== BANK MANAGEMENT SYSTEM =====\n");
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
    return 0;
}
