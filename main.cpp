#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
private:
    int bookID;
    char title[100];
    char author[100];
    bool issued;

public:
    void addBook();
    void displayBook() const;
    int getBookID() const;
    const char* getTitle() const;
    const char* getAuthor() const;
    bool isIssued() const;
    void issueBook();
    void returnBook();
};

void Book::addBook()
{
    cout << "\nEnter Book ID: ";
    cin >> bookID;

    cin.ignore();

    cout << "Enter Book Title: ";
    cin.getline(title, 100);

    cout << "Enter Author Name: ";
    cin.getline(author, 100);

    issued = false;
}

void Book::displayBook() const
{
    cout << "\n--------------------------------";
    cout << "\nBook ID   : " << bookID;
    cout << "\nTitle     : " << title;
    cout << "\nAuthor    : " << author;
    cout << "\nStatus    : " << (issued ? "Issued" : "Available");
    cout << "\n--------------------------------";
}

int Book::getBookID() const
{
    return bookID;
}

const char* Book::getTitle() const
{
    return title;
}

const char* Book::getAuthor() const
{
    return author;
}

bool Book::isIssued() const
{
    return issued;
}

void Book::issueBook()
{
    issued = true;
}

void Book::returnBook()
{
    issued = false;
}

// Add Book
void addBook()
{
    Book book;

    ofstream file("library.dat", ios::binary | ios::app);

    book.addBook();

    file.write((char*)&book, sizeof(book));

    file.close();

    cout << "\nBook Added Successfully!\n";
}

// View All Books
void displayBooks()
{
    Book book;

    ifstream file("library.dat", ios::binary);

    cout << "\n========= BOOK LIST =========\n";

    while(file.read((char*)&book, sizeof(book)))
    {
        book.displayBook();
    }

    file.close();
}

// Search by Title
void searchByTitle()
{
    Book book;
    char searchTitle[100];
    bool found = false;

    cin.ignore();

    cout << "\nEnter Book Title: ";
    cin.getline(searchTitle,100);

    ifstream file("library.dat", ios::binary);

    while(file.read((char*)&book,sizeof(book)))
    {
        if(strcmp(book.getTitle(), searchTitle)==0)
        {
            book.displayBook();
            found = true;
        }
    }

    file.close();

    if(!found)
        cout<<"\nBook Not Found!\n";
}

// Search by Author
void searchByAuthor()
{
    Book book;
    char searchAuthor[100];
    bool found = false;

    cin.ignore();

    cout << "\nEnter Author Name: ";
    cin.getline(searchAuthor,100);

    ifstream file("library.dat", ios::binary);

    while(file.read((char*)&book,sizeof(book)))
    {
        if(strcmp(book.getAuthor(), searchAuthor)==0)
        {
            book.displayBook();
            found = true;
        }
    }

    file.close();

    if(!found)
        cout<<"\nNo Books Found!\n";
}

// Issue Book
void issueBook()
{
    int id;
    bool found = false;

    Book book;

    fstream file("library.dat", ios::binary|ios::in|ios::out);

    cout << "\nEnter Book ID: ";
    cin >> id;

    while(file.read((char*)&book,sizeof(book)))
    {
        if(book.getBookID()==id)
        {
            if(book.isIssued())
            {
                cout<<"\nBook Already Issued!\n";
            }
            else
            {
                book.issueBook();

                int pos = -1 * sizeof(book);

                file.seekp(pos, ios::cur);

                file.write((char*)&book,sizeof(book));

                cout<<"\nBook Issued Successfully!\n";
            }

            found=true;
            break;
        }
    }

    file.close();

    if(!found)
        cout<<"\nBook Not Found!\n";
}

// Return Book
void returnBook()
{
    int id;
    bool found = false;

    Book book;

    fstream file("library.dat", ios::binary|ios::in|ios::out);

    cout<<"\nEnter Book ID: ";
    cin>>id;

    while(file.read((char*)&book,sizeof(book)))
    {
        if(book.getBookID()==id)
        {
            if(!book.isIssued())
            {
                cout<<"\nBook is already available.\n";
            }
            else
            {
                book.returnBook();

                int pos = -1 * sizeof(book);

                file.seekp(pos, ios::cur);

                file.write((char*)&book,sizeof(book));

                cout<<"\nBook Returned Successfully!\n";
            }

            found=true;
            break;
        }
    }

    file.close();

    if(!found)
        cout<<"\nBook Not Found!\n";
}

int main()
{
    int choice;

    while(true)
    {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Search by Title\n";
        cout << "4. Search by Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchByTitle();
                break;

            case 4:
                searchByAuthor();
                break;

            case 5:
                issueBook();
                break;

            case 6:
                returnBook();
                break;

            case 7:
                cout<<"\nThank You!\n";
                return 0;

            default:
                cout<<"\nInvalid Choice!\n";
        }
    }

    return 0;
}