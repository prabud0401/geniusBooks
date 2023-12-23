#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Structure to represent a book
struct Book {
    string title;
    string author;
    string ISBN;
    // Add other book details as needed
};

// Structure to represent a user
struct User {
    string username;
    string password;
    // Add other user details as needed
};

struct Sale {
    string bookTitle;
    int quantitySold;
    double totalPrice;
    string date;
};

// Function prototypes
bool loginUser(const string& username, const string& password);
void displayMainMenu();
void viewBookDetails();
void addBookDetails();
void updateBookDetails();
void deleteBookDetails();
void manageSalesDetails();
void viewSalesDetails();
void logout();
void exitApplication();

int main() {
    // Login
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (loginUser(username, password)) {
        // Display main menu if login is successful
        displayMainMenu();
    }
    else {
        cout << "Login failed. Exiting application." << endl;
    }

    return 0;
}

bool loginUser(const string& username, const string& password) {
    // Check user credentials from the users.txt file
    ifstream usersFile("users.txt");
    if (!usersFile) {
        cerr << "Error opening users file." << endl;
        exit(1);
    }

    User user;
    while (usersFile >> user.username >> user.password) {
        if (user.username == username && user.password == password) {
            usersFile.close();
            return true; // Login successful
        }
    }

    usersFile.close();
    return false; // Login failed
}

void displayMainMenu() {
    int choice;
    do {
        // Display main menu options
        cout << "\nMain Menu:" << endl;
        cout << "1. View Book Details\n";
        cout << "2. Add Book Details\n";
        cout << "3. Update Book Details\n";
        cout << "4. Delete Book Details\n";
        cout << "5. View Sales Details\n";
        cout << "6. Manage Sales Details\n";
        cout << "7. Logout\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Perform the selected action
        switch (choice) {
            case 1:
                viewBookDetails();
                break;
            case 2:
                addBookDetails();
                break;
            case 3:
                updateBookDetails();
                break;
            case 4:
                deleteBookDetails();
                break;
            case 5:
                viewSalesDetails();
                break;
            case 6:
                manageSalesDetails();
                break;
            case 7:
                logout();
                break;
            case 8:
                exitApplication();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);
}

void viewBookDetails() {
    // Implement logic to read and display book details from books.txt
    ifstream booksFile("books.txt");
    if (!booksFile) {
        cerr << "Error opening books file." << endl;
        return;
    }

    Book book;
    while (booksFile >> book.title >> book.author >> book.ISBN) {
        cout << "Title: " << book.title << "\nAuthor: " << book.author << "\nISBN: " << book.ISBN << "\n\n";
    }

    booksFile.close();
}

void addBookDetails() {
    // Implement logic to add new book details to books.txt
    ofstream booksFile("books.txt", ios::app);
    if (!booksFile) {
        cerr << "Error opening books file for writing." << endl;
        return;
    }

    Book newBook;
    cout << "Enter book title: ";
    cin >> newBook.title;
    cout << "Enter author: ";
    cin >> newBook.author;
    cout << "Enter ISBN: ";
    cin >> newBook.ISBN;

    booksFile << newBook.title << " " << newBook.author << " " << newBook.ISBN << "\n";
    booksFile.close();

    cout << "Book details added successfully.\n";
}

void updateBookDetails() {
    // Implement logic to update book details in books.txt
    string ISBN;
    cout << "Enter ISBN of the book to update: ";
    cin >> ISBN;

    ifstream booksFile("books.txt");
    if (!booksFile) {
        cerr << "Error opening books file for reading." << endl;
        return;
    }

    Book book;
    ofstream tempFile("temp.txt");
    while (booksFile >> book.title >> book.author >> book.ISBN) {
        if (book.ISBN == ISBN) {
            cout << "Enter new details for the book:\n";
            cout << "Enter book title: ";
            cin >> book.title;
            cout << "Enter author: ";
            cin >> book.author;
            // ISBN remains the same in the update
        }
        tempFile << book.title << " " << book.author << " " << book.ISBN << "\n";
    }

    booksFile.close();
    tempFile.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    cout << "Book details updated successfully.\n";
}

void deleteBookDetails() {
    // Implement logic to delete book details from books.txt
    string ISBN;
    cout << "Enter ISBN of the book to delete: ";
    cin >> ISBN;

    ifstream booksFile("books.txt");
    if (!booksFile) {
        cerr << "Error opening books file for reading." << endl;
        return;
    }

    Book book;
    ofstream tempFile("temp.txt");
    while (booksFile >> book.title >> book.author >> book.ISBN) {
        if (book.ISBN != ISBN) {
            tempFile << book.title << " " << book.author << " " << book.ISBN << "\n";
        }
    }

    booksFile.close();
    tempFile.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    cout << "Book details deleted successfully.\n";
}

void manageSalesDetails() {
    // Implement logic to manage sales details (e.g., record sales in sales.txt)
    ofstream salesFile("sales.txt", ios::app);
    if (!salesFile) {
        cerr << "Error opening sales file for writing." << endl;
        return;
    }

    // Get necessary information from the user
    string bookTitle;
    int quantitySold;
    double totalPrice;

    // Capture necessary information
    cout << "Enter the title of the book sold: ";
    cin.ignore(); // Ignore newline character in the input buffer
    getline(cin, bookTitle);

    cout << "Enter the quantity sold: ";
    cin >> quantitySold;

    cout << "Enter the total price: $";
    cin >> totalPrice;

    // Get the current date (you may need to include appropriate libraries for date handling)
    // For simplicity, I'll use a placeholder for the date.
    string currentDate = "2023-01-01";

    // Write the sales record to the sales.txt file
    salesFile << bookTitle << " " << quantitySold << " " << totalPrice << " " << currentDate << "\n";

    salesFile.close();
    cout << "Sales details managed successfully.\n";
}

void logout() {
    cout << "Logging out...\n";
    // You can add additional cleanup or logging out logic here if needed

    // For simplicity, let's assume that logging out just returns to the login screen
    main(); // Restart the application for a new user
}

void exitApplication() {
    cout << "Exiting application...\n";
    // You can add additional cleanup logic here if needed
    exit(0);
}

void viewSalesDetails() {
    // Implement logic to view sales details (read and display from sales.txt)
    ifstream salesFile("sales.txt");
    if (!salesFile) {
        cerr << "Error opening sales file for reading." << endl;
        return;
    }

    Sale sale;
    cout << "\nSales Details\n";
    cout << "---------------------------------\n";
    cout << "Book Title   Quantity   Total Price   Date\n";
    cout << "---------------------------------\n";

    // Read and display each sales record
    while (salesFile >> sale.bookTitle >> sale.quantitySold >> sale.totalPrice >> sale.date) {
        cout << setw(12) << left << sale.bookTitle;
        cout << setw(9) << right << sale.quantitySold;
        cout << setw(14) << right << fixed << setprecision(2) << sale.totalPrice;
        cout << setw(12) << right << sale.date << "\n";
    }

    cout << "---------------------------------\n";

    salesFile.close();
}
