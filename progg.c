#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_BOOKS 100
#define USER_FILE "users.txt"
#define BOOK_FILE "books.txt"

typedef struct {
    char username[50];
    char password[50];
    char role[10]; // "Admin" ou "Member"
} User;

typedef struct {
    int id;
    char title[100];
    char author[100];
    float price;
    int quantity;
} Book;

User users[MAX_USERS];
Book books[MAX_BOOKS];
int userCount = 0;
int bookCount = 0;

// Prototypes des fonctions
void loadUsers();
void saveUsers();
void registerUser();
int loginUser(char *username, char *password);
void addUser(User user);
void loadBooks();
void saveBooks();
void addBook();
void viewBooks();
void deleteBook();
void borrowBook();
void adminMenu();
void memberMenu();

void loadUsers() {
    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL) {
        printf("No users file found. Starting fresh.\n");
        return;
    }

    userCount = 0;
    while (fscanf(file, "%s %s %s", users[userCount].username, users[userCount].password, users[userCount].role) != EOF) {
        userCount++;
    }
    fclose(file);
}

void saveUsers() {
    FILE *file = fopen(USER_FILE, "w");
    if (file == NULL) {
        printf("Error: Could not create or open the users file.\n");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].role);
    }
    fclose(file);
}

void registerUser() {
    char username[50], password[50], role[10];
    printf("Enter username: ");
    scanf("%s", username);
    
    // Vérifier que le nom d'utilisateur est unique
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists.\n");
            return; // Quitter la fonction si le nom d'utilisateur existe déjà
        }
    }

    printf("Enter password: ");
    scanf("%s", password);
    
    // Boucle pour valider l'entrée du rôle
    while (1) {
        printf("Enter role (Admin/Member): ");
        scanf("%s", role);
        if (strcmp(role, "Admin") == 0 || strcmp(role, "Member") == 0) {
            break; // Rôle valide, sortir de la boucle
        } else {
            printf("Invalid role. Please enter 'Admin' or 'Member'.\n");
        }
    }

    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    strcpy(newUser.role, role);

    addUser(newUser); // Ajouter le nouvel utilisateur
    saveUsers(); // Sauvegarder les utilisateurs dans le fichier
    printf("User registered successfully.\n");
}

void addUser(User user) {
    if (userCount < MAX_USERS) {
        users[userCount++] = user;
    } else {
        printf("User limit reached.\n");
    }
}

int loginUser(char *username, char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful. Role: %s\n", users[i].role);
            return i; // Retourner l'index de l'utilisateur connecté
        }
    }
    printf("Invalid username or password.\n");
    return -1;
}

void loadBooks() {
    FILE *file = fopen(BOOK_FILE, "r");
    if (file == NULL) {
        printf("No books file found. Starting fresh.\n");
        return;
    }

    bookCount = 0;
    while (fscanf(file, "%d %s %s %f %d", &books[bookCount].id, books[bookCount].title, books[bookCount].author, &books[bookCount].price, &books[bookCount].quantity) != EOF) {
        bookCount++;
    }
    fclose(file);
}

void saveBooks() {
    FILE *file = fopen(BOOK_FILE, "w");
    if (file == NULL) {
        printf("Error: Could not create or open the books file.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%d %s %s %.2f %d\n", books[i].id, books[i].title, books[i].author, books[i].price, books[i].quantity);
    }
    fclose(file);
}

void addBook() {
    Book book;
    printf("Enter book ID: ");
    scanf("%d", &book.id);
    printf("Enter book title: ");
    scanf("%s", book.title);
    printf("Enter book author: ");
    scanf("%s", book.author);
    printf("Enter book price: ");
    scanf("%f", &book.price);
    printf("Enter book quantity: ");
    scanf("%d", &book.quantity);

    if (bookCount < MAX_BOOKS) {
        books[bookCount++] = book;
        saveBooks(); // Sauvegarder les livres après avoir ajouté un nouveau livre
        printf("Book added successfully.\n");
    } else {
        printf("Book limit reached.\n");
    }
}

void viewBooks() {
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Price: %.2f, Quantity: %d\n", books[i].id, books[i].title, books[i].author, books[i].price, books[i].quantity);
    }
}

void deleteBook() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            saveBooks();
            printf("Book deleted successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void borrowBook() {
    int id, quantity;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);
    printf("Enter quantity to borrow: ");
    scanf("%d", &quantity);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            if (books[i].quantity >= quantity) {
                books[i].quantity -= quantity;
                saveBooks();
                printf("Book borrowed successfully.\n");
            } else {
                printf("Not enough quantity in stock.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void adminMenu() {
    int choice;
    while (1) {
        printf("\n1. Add Book\n2. View Books\n3. Delete Book\n4. Logout\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                return; // Sortir du menu admin
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void memberMenu() {
    int choice;
    while (1) {
        printf("\n1. View Books\n2. Borrow Book\n3. Logout\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                viewBooks();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                return; // Sortir du menu membre
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    loadUsers();
    loadBooks();

    int choice, userIndex;
    char username[50], password[50];
    printf(" WELCOMME TO THE ELECTRONIC LIBRARY  \n \n ");

    while (1) {
        printf("-------------------------------------\n1. Register\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        printf("-------------------------------------\n");
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                userIndex = loginUser(username, password);
                if (userIndex != -1) {
                    if (strcmp(users[userIndex].role, "Admin") == 0) {
                        adminMenu();
                    } else if (strcmp(users[userIndex].role, "Member") == 0) {
                        memberMenu();
                    }
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
