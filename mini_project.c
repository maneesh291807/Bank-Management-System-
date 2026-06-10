#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Account
{
    int accNo;
    char name[50];
    float balance;
    struct Account *next;
};
struct Account *head = NULL;
void loadFromFile();
void saveToFile();
void createAccount();
void deposit();
void withdrawMoney();
void checkBalance();
void displayAccounts();
void loadFromFile()
{
    FILE *fp = fopen("bank.dat", "rb");
    if (fp == NULL)
        return;
    struct Account temp;
    while (fread(&temp, sizeof(struct Account), 1, fp))
    {
        struct Account *newNode =
            (struct Account *)malloc(sizeof(struct Account));

        newNode->accNo = temp.accNo;
        strcpy(newNode->name, temp.name);
        newNode->balance = temp.balance;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            struct Account *ptr = head;
            while (ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = newNode;
        }
    }

    fclose(fp);
}
void saveToFile() {
    FILE *fp = fopen("bank.dat", "wb");

    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    struct Account *ptr = head;

    while (ptr != NULL) {
        fwrite(ptr, sizeof(struct Account), 1, fp);
        ptr = ptr->next;
    }

    fclose(fp);
}
void createAccount()
{

    struct Account *newNode =
        (struct Account *)malloc(sizeof(struct Account));

    printf("\nEnter Account Number: ");
    scanf("%d", &newNode->accNo);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", newNode->name);

    printf("Enter Initial Balance: ");
    scanf("%f", &newNode->balance);

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Account *ptr = head;

        while (ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = newNode;
    }

    saveToFile();

    printf("Account Created Successfully!\n");
}
void deposit()
{

    int acc;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    struct Account *ptr = head;

    while (ptr != NULL) {

        if (ptr->accNo == acc) {

            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);

            ptr->balance += amount;

            saveToFile();

            printf("Amount Deposited Successfully!\n");
            return;
        }

        ptr = ptr->next;
    }

    printf("Account Not Found!\n");
}
void withdrawMoney()
{

    int acc;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    struct Account *ptr = head;

    while (ptr != NULL) {

        if (ptr->accNo == acc) {

            printf("Enter Withdraw Amount: ");
            scanf("%f", &amount);

            if (amount > ptr->balance) {
                printf("Insufficient Balance!\n");
                return;
            }

            ptr->balance -= amount;

            saveToFile();

            printf("Withdrawal Successful!\n");
            return;
        }

        ptr = ptr->next;
    }

    printf("Account Not Found!\n");
}
void checkBalance()
{

    int acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    struct Account *ptr = head;

    while (ptr != NULL) {

        if (ptr->accNo == acc) {

            printf("\nAccount Number : %d\n", ptr->accNo);
            printf("Name           : %s\n", ptr->name);
            printf("Balance        : %.2f\n", ptr->balance);

            return;
        }

        ptr = ptr->next;
    }

    printf("Account Not Found!\n");
}
void displayAccounts()
{

    struct Account *ptr = head;

    if (head == NULL) {
        printf("No Accounts Available!\n");
        return;
    }

    printf("\n===== Account List =====\n");

    while (ptr != NULL) {

        printf("\nAccount No : %d", ptr->accNo);
        printf("\nName       : %s", ptr->name);
        printf("\nBalance    : %.2f\n", ptr->balance);

        ptr = ptr->next;
    }
}

int main() {

    int choice;

    loadFromFile();

    do
    {

        printf("\n=============================\n");
        printf(" BANK MANAGEMENT SYSTEM\n");
        printf("=============================\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Display Accounts\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                displayAccounts();
                break;

            case 6:
                saveToFile();
                printf("Data Saved. Exiting...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 6);

    return 0;
}