#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 10

typedef struct {
    int id;
    char name[100];
    double balance;
} Account;

void create_account(Account accounts[], int *num_accounts);
void deposit(Account accounts[], int num_accounts);
void withdraw(Account accounts[], int num_accounts);
void transfer(Account accounts[], int num_accounts);

int main() {
    Account accounts[MAX_ACCOUNTS];
    int num_accounts = 0;
    int choice;

    printf("Welcome to the banking system\n");

    while (1) {
        printf("\n1. Create account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Exit\n\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account(accounts, &num_accounts);
                break;
            case 2:
                deposit(accounts, num_accounts);
                break;
            case 3:
                withdraw(accounts, num_accounts);
                break;
            case 4:
                transfer(accounts, num_accounts);
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

void create_account(Account accounts[], int *num_accounts) {
    if (*num_accounts == MAX_ACCOUNTS) {
        printf("Maximum number of accounts reached\n");
        return;
    }

    Account account;
    account.id = *num_accounts + 1;

    printf("Enter account name: ");
    scanf("%s", account.name);

    printf("Enter initial balance: ");
    scanf("%lf", &account.balance);

    accounts[*num_accounts] = account;
    (*num_accounts)++;

    printf("Account created with ID %d\n", account.id);
}

void deposit(Account accounts[], int num_accounts) {
    int id;
    double amount;

    printf("Enter account ID: ");
    scanf("%d", &id);

    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].id == id) {
            printf("Enter deposit amount: ");
            scanf("%lf", &amount);

            accounts[i].balance += amount;

            printf("Deposit successful. New balance: $%.2lf\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found\n");
}

void withdraw(Account accounts[], int num_accounts) {
    int id;
    double amount;

    printf("Enter account ID: ");
    scanf("%d", &id);

    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].id == id) {
            printf("Enter withdrawal amount: ");
            scanf("%lf", &amount);

            if (amount > accounts[i].balance) {
                printf("Insufficient funds\n");
                return;
            }

            accounts[i].balance -= amount;

            printf("Withdrawal successful. New balance: $%.2lf\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found\n");
}

void transfer(Account accounts[], int num_accounts) {
    int id1, id2;
    double amount;

    printf("Enter account ID to transfer from: ");
    scanf("%d", &id1);

    printf("Enter account ID to transfer to: ");
    scanf("%d", &id2);

    if (id1 == id2) {
        printf("Cannot transfer to the same account\n");
        return;
    }

    int index1 = -1, index2 = -1;
    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].id == id1) {
            index1 = i;
        }
        if (accounts[i].id == id2) {
            index2 = i;
        }
        if (index1 != -1 && index2 != -1) {
            break;
        }
    }

    if (index1 == -1 || index2 == -1) {
        printf("One or both accounts not found\n");
        return;
    }

    printf("Enter transfer amount: ");
    scanf("%lf", &amount);

    if (amount > accounts[index1].balance) {
        printf("Insufficient funds\n");
        return;
    }

    accounts[index1].balance -= amount;
    accounts[index2].balance += amount;

    printf("Transfer successful. New balance for account %d: $%.2lf\n", accounts[index1].id, accounts[index1].balance);
    printf("New balance for account %d: $%.2lf\n", accounts[index2].id, accounts[index2].balance);

}
