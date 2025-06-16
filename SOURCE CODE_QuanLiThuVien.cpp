#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

const int MAX_BOOKS = 100;
const int MAX_USERS = 100;

struct Book 
{
    string isbn;
    string title;
    string subject;
    string author;
    string publisher;
    string date;
    
    int pages;
    int copies;
};

struct User 
{
    string userid;
    string username;
    string password;
    string usertype;
};

Book library[MAX_BOOKS];
User users[MAX_USERS];

int numBooks = 0;
int numUsers = 0;

User currentUser;

bool hasUserInformation = false;

bool isValidString(const string& str) 
{
    for (size_t i = 0; i < str.length(); ++i) 
	{
        char ch = str[i];
        if (!isalnum(ch) && ch != ' ') 
		{
            return false;
        }
    }
    return true;
}

bool isValidDate(const string& str) 
{
    if (str.length() != 7) return false;
    if (str[2] != '/') return false;
    if (!isdigit(str[0]) || !isdigit(str[1])) return false;
    
    int month = (str[0] - '0') * 10 + (str[1] - '0');
    
    if (month < 1 || month > 12) return false;

    for (int i = 3; i < 7; ++i) 
	{
        if (!isdigit(str[i])) return false;
    }

    return true;
}

bool isValidId(const string& id) 
{
    for (size_t i = 0; i < id.length(); ++i) 
	{
        if (!isdigit(id[i])) 
		{
            return false;
        }
    }
    return true;
}

bool isExistingUser(const string& userId) 
{
    for (int i = 0; i < numUsers; ++i) 
	{
        if (users[i].userid == userId) 
		{
            return true;
        }
    }
    return false;
}

void addBook() 
{
    if (numBooks >= MAX_BOOKS) 
	{
        cout << "Thu vien da dat toi gioi han so sach." << endl;
        return;
    }

    Book newBook;
    cout << "Nhap thong tin sach:" << endl;

    cout << "ISBN: ";
    cin >> newBook.isbn;

    while (!isValidString(newBook.isbn)) 
	{
        cout << "ISBN phai la chuoi. Nhap lai: ";
        cin >> newBook.isbn;
    }

    cout << "Title: ";
    cin.ignore();
    getline(cin, newBook.title);

    while (!isValidString(newBook.title)) 
	{
        cout << "Title phai la chuoi. Nhap lai: ";
        getline(cin, newBook.title);
    }

    cout << "Subject: ";
    getline(cin, newBook.subject);

    while (!isValidString(newBook.subject)) 
	{
        cout << "Subject phai la chuoi. Nhap lai: ";
        getline(cin, newBook.subject);
    }

    cout << "Author: ";
    getline(cin, newBook.author);

    while (!isValidString(newBook.author)) 
	{
        cout << "Author phai la chuoi. Nhap lai: ";
        getline(cin, newBook.author);
    }

    cout << "Publisher: ";
    getline(cin, newBook.publisher);

    while (!isValidString(newBook.publisher)) 
	{
        cout << "Publisher phai la chuoi. Nhap lai: ";
        getline(cin, newBook.publisher);
    }

    cout << "Date (mm/yyyy): ";
    cin >> newBook.date;

    while (!isValidDate(newBook.date)) 
	{
        cout << "Date phai dung dinh dang (mm/yyyy). Nhap lai: ";
        cin >> newBook.date;
    }

    cout << "Pages: ";
    cin >> newBook.pages;

    while (!cin) 
	{
        cout << "Pages phai la mot so. Nhap lai: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> newBook.pages;
    }

    cout << "Copies: ";
    cin >> newBook.copies;

    while (!cin) 
	{
        cout << "Copies phai la mot so. Nhap lai: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> newBook.copies;
    }

    library[numBooks++] = newBook;
    cout << "Sach da duoc them vao thu vien." << endl;
}

void deleteBook() 
{
    if (numBooks == 0) 
	{
        cout << "Thu vien hien chua co sach nao." << endl;
        return;
    }

    string title;
    
    cout << "Nhap ten sach muon xoa: ";
    cin.ignore();
    getline(cin, title);

    bool found = false;
    
    for (int i = 0; i < numBooks; ++i) 
	{
        if (library[i].title == title) 
		{
            found = true;
            
            for (int j = i; j < numBooks - 1; ++j) 
			{
                library[j] = library[j + 1];
            }
            
            numBooks--;
            
            cout << "Sach da duoc xoa khoi thu vien." << endl;
            break;
        }
    }

    if (!found) 
	{
        cout << "Khong tim thay sach co ten nay trong thu vien." << endl;
    }
}

void editBook() 
{
    if (numBooks == 0) 
	{
        cout << "Thu vien hien chua co sach nao." << endl;
        return;
    }
    
    string title;
    bool found = false;

    while (!found) 
	{
        cout << "Nhap ten sach muon sua thong tin: ";
        cin.ignore();
        getline(cin, title);

        for (int i = 0; i < numBooks; ++i) 
		{
            if (library[i].title == title) 
			{
                found = true;
                cout << "Nhap thong tin moi cho sach '" << title << "':" << endl;
                
                string field;
                bool validField = false;
                
                while (!validField) 
				{
                    cout << "Chon phan muon sua (isbn, title, subject, author, publisher, date, pages, copies): ";
                    cin >> field;
                    
                    if (field == "isbn" || field == "title" || field == "subject" || field == "author" || field == "publisher" || field == "date" || field == "pages" || field == "copies") 
					{
                        validField = true;
                    } 
					
					else 
					
					{
                        cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                    }
                }

                if (field == "isbn") 
				{
                    cout << "ISBN: ";
                    cin >> library[i].isbn;
                    
                    while (!isValidString(library[i].isbn)) 
					{
                        cout << "ISBN phai la chuoi. Nhap lai: ";
                        cin >> library[i].isbn;
                    }
                } 
				
				else if (field == "title") 
				{
                    cout << "Title: ";
                    cin.ignore();
                    getline(cin, library[i].title);
                    
                    while (!isValidString(library[i].title)) 
					{
                        cout << "Title phai la chuoi. Nhap lai: ";
                        getline(cin, library[i].title);
                    }
                } 
				
				else if (field == "subject") 
				{
                    cout << "Subject: ";
                    cin.ignore();
                    getline(cin, library[i].subject);
                    
                    while (!isValidString(library[i].subject)) 
					{
                        cout << "Subject phai la chuoi. Nhap lai: ";
                        getline(cin, library[i].subject);
                    }
                } 
				
				else if (field == "author") 
				{
                    cout << "Author: ";
                    cin.ignore();
                    getline(cin, library[i].author);
                    
                    while (!isValidString(library[i].author)) 
					{
                        cout << "Author phai la chuoi. Nhap lai: ";
                        getline(cin, library[i].author);
                    }
                }
				
				 else if (field == "publisher") 
				 {
                    cout << "Publisher: ";
                    cin.ignore();
                    getline(cin, library[i].publisher);
                    
                    while (!isValidString(library[i].publisher)) 
					{
                        cout << "Publisher phai la chuoi. Nhap lai: ";
                        getline(cin, library[i].publisher);
                    }
                } 
				
				else if (field == "date") 
				{
                    cout << "Date (mm/yyyy): ";
                    cin >> library[i].date;
                    
                    while (!isValidDate(library[i].date)) 
					{
                        cout << "Date phai dung dinh dang (mm/yyyy). Nhap lai: ";
                        cin >> library[i].date;
                    }
                } 
				
				else if (field == "pages") 
				{
                    cout << "Pages: ";
                    cin >> library[i].pages;
                    
                    while (!cin) 
					{
                        cout << "Pages phai la mot so. Nhap lai: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> library[i].pages;
                    }
                } 
				
				else if (field == "copies") 
				{
                    cout << "Copies: ";
                    cin >> library[i].copies;
                    
                    while (!cin) 
					{
                        cout << "Copies phai la mot so. Nhap lai: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> library[i].copies;
                    }
                } 
				
				else 
				{
                    cout << "Phan muon sua khong hop le." << endl;
                    return;
                }
                
                cout << "Thong tin sach da duoc cap nhat." << endl;
                break;
            }
        }

        if (!found) 
		{
            cout << "Khong tim thay sach co ten nay trong thu vien. Vui long nhap lai." << endl;
        }
    }
}

void displayBooks() 
{
    cout << "Danh sach sach trong thu vien:" << endl;

    if (numBooks == 0) 
	{
        cout << "Thu vien hien chua co sach nao." << endl;
    } 
	
	else 
	{
        for (int i = 0; i < numBooks; ++i) 
		{
            Book& book = library[i];
            cout << endl;
            cout << "-----------------------------------------" << endl;
            cout << "QUYEN SACH " << i+1 << " - " << library[i].title << endl;
            cout << "THONG TIN CUA SACH " << endl;
            cout << "Title: " << library[i].title << "\nSubject: " << library[i].subject
                 << "\nAuthor: " << library[i].author << "\nPublisher: " << library[i].publisher << "\nDate: " << library[i].date << endl;
        }
	}
}

void addUser() 
{
    if (numUsers >= MAX_USERS) 
	{
        cout << "He thong da dat toi gioi han so nguoi dung." << endl;
        return;
    }

    User newUser;
    cout << "Nhap thong tin nguoi dung:" << endl;

    cout << "User ID: ";
    cin >> newUser.userid;

    while (!isValidId(newUser.userid) || isExistingUser(newUser.userid)) 
	{
        if (!isValidId(newUser.userid)) 
		{
            cout << "User ID phai la chuoi so. Nhap lai: ";
            cin >> newUser.userid;
        } 
		
		else 
		
		{
            cout << "User ID da ton tai. Nhap lai: ";
            cin >> newUser.userid;
        }
    }
    cout << "Username: ";
    cin.ignore();
    getline(cin, newUser.username);

    while (!isValidString(newUser.username)) 
	{
        cout << "Username phai la chuoi. Nhap lai: ";
        getline(cin, newUser.username);
    }

    cout << "Password: ";
    getline(cin, newUser.password);

    while (!isValidString(newUser.password)) 
	{
        cout << "Password phai la chuoi. Nhap lai: ";
        getline(cin, newUser.password);
    }

    cout << "User type (user/admin): ";
    cin >> newUser.usertype;

    while (newUser.usertype != "user" && newUser.usertype != "admin") 
	{
        cout << "User type phai la 'user' hoac 'admin'. Nhap lai: ";
        cin >> newUser.usertype;
    }

    users[numUsers++] = newUser;
    cout << "Nguoi dung da duoc them vao co so du lieu." << endl;
}

void deleteUser() 
{
    if (numUsers == 0) 
	{
        cout << "Co so du lieu hien khong co nguoi dung nao." << endl;
        return;
    }

    string userId;
    cout << "Nhap ma nguoi dung muon xoa: ";
    cin >> userId;

    bool found = false;
    
    for (int i = 0; i < numUsers; ++i) 
	{
        if (users[i].userid == userId) 
		{
            found = true;
            
            for (int j = i; j < numUsers - 1; ++j) 
			{
                users[j] = users[j + 1];
            }
            
            numUsers--;
            
            cout << "Nguoi dung da duoc xoa khoi co so du lieu." << endl;
            break;
        }
    }

    if (!found) 
	{
        cout << "Khong tim thay nguoi dung co ma nay trong co so du lieu." << endl;
    }
}

void editUser() 
{
    if (numUsers == 0) 
	{
        cout << "Co so du lieu hien khong co nguoi dung nao." << endl;
        return;
    }

    string userId;
    
    cout << "Nhap ma nguoi dung muon sua thong tin: ";
    cin >> userId;

    bool found = false;
    
    for (int i = 0; i < numUsers; ++i) 
	{
        if (users[i].userid == userId) 
		{
            found = true;
            
            cout << "Nhap thong tin moi cho nguoi dung '" << userId << "':" << endl;
            
            string field;
            
            bool validField = false;

            while (!validField) 
			{
                cout << "Chon phan muon sua (username, password, usertype): ";
                cin >> field;

                if (field == "username" || field == "password" || field == "usertype") 
				{
                    validField = true;
                } 
				
				else 
				{
                    cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                }
            }

            if (field == "username") 
			{
                cout << "Username: ";
                cin.ignore();
                getline(cin, users[i].username);

                while (!isValidString(users[i].username)) 
				{
                    cout << "Username phai la chuoi. Nhap lai: ";
                    getline(cin, users[i].username);
                }
            } 
			
			else if (field == "password") 
			{
                cout << "Password: ";
                cin.ignore();
                getline(cin, users[i].password);

                while (!isValidString(users[i].password)) 
				{
                    cout << "Password phai la chuoi. Nhap lai: ";
                    getline(cin, users[i].password);
                }
            } 
			
			else if (field == "usertype") 
			{
                cout << "User type (user/admin): ";
                cin >> users[i].usertype;

                while (users[i].usertype != "user" && users[i].usertype != "admin") 
				{
                    cout << "User type phai la 'user' hoac 'admin'. Nhap lai: ";
                    cin >> users[i].usertype;
                }
            } 
			
			else 
			{
                cout << "Phan muon sua khong hop le." << endl;
                return;
            }

            cout << "Thong tin nguoi dung da duoc cap nhat." << endl;
            break;
        }
    }

    if (!found) 
	{
        cout << "Khong tim thay nguoi dung co ma nay trong he thong. Vui long nhap lai." << endl;
    }
}

void displayUsers() 
{
    cout << "Danh sach nguoi dung trong co so du lieu:" << endl;

    if (numUsers == 0) 
	{
        cout << "Co so du lieu hien khong co nguoi dung nao." << endl;
    } 
	
	else 
	{
        for (int i = 0; i < numUsers; ++i) 
		{
            cout << "-----------------------------------------" << endl;
            cout << "NGUOI DUNG " << i + 1 << endl;
            cout << "THONG TIN CUA NGUOI DUNG " << endl;
            cout << "UserID: " << users[i].userid << endl;
            cout << "Username: " << users[i].username << endl;
            cout << "Password: " << users[i].password << endl;
            cout << "User type: " << users[i].usertype << endl;
        }
    }
}

void login() 
{
    string userType;
    
    cout << "Ban la user hay admin? (user/admin): ";
    cin >> userType;

    if (userType == "user") 
	{
        cout << "Chao mung user!" << endl;
        
        while (true) 
		{
            cout << endl;
            cout << "Menu user:" << endl;
            cout << "1. Hien thi tat ca sach" << endl;
            cout << "2. Thoat" << endl;
            cout << "Chon: ";
            
            int choice;
            cin >> choice;

            switch (choice) 
			{
                case 1:
                    displayBooks();
                    break;
                case 2:
                    cout << "Thoat ra ngoai thanh cong!" << endl;
                    return;
                default:
                    cout << "Lua chon khong hop le. Vui long chon lai." << endl;
            }
        }
    } 
	
	else if (userType == "admin") 
	{
        string username, password;
        
        bool isValidLogin = false;

        cout << "Nhap ten dang nhap: ";
        cin >> username;
        cout << "Nhap mat khau: ";
        cin >> password;

        for (int i = 0; i < numUsers; ++i) 
		{
            if (users[i].username == username && users[i].password == password && users[i].usertype == "admin") 
			{
                isValidLogin = true;
                
                currentUser = users[i];
                
                cout << "Dang nhap thanh cong! Chao mung admin." << endl;
                
                while (true) 
				{
                    cout << endl;
                    cout << "Menu admin:" << endl;
                    cout << "1. Them sach" << endl;
                    cout << "2. Xoa sach" << endl;
                    cout << "3. Sua thong tin sach" << endl;
                    cout << "4. Hien thi tat ca sach" << endl;
                    cout << "5. Dang xuat" << endl;
                    cout << "Chon: ";
                    
                    int choice;
                    cin >> choice;

                    switch (choice) 
					{
                        case 1:
                            addBook();
                            break;
                        case 2:
                            deleteBook();
                            break;
                        case 3:
                            editBook();
                            break;
                        case 4:
                            displayBooks();
                            break;
                        case 5:
                            cout << "Dang xuat...";
                            return;
                        default:
                            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                    }
                }
            }
        }

        if (!isValidLogin) 
		{
            cout << "Thong tin dang nhap khong hop le. Vui long nhap lai." << endl;
        }
    } 
	
	else
	{
        cout << "Loai nguoi dung khong hop le." << endl;
    }
}

int main() 
{
    while (true) 
	{
        cout << "\n===== CHUONG TRINH QUAN LY THU VIEN =====" << endl;
        cout << "1. Them sach" << endl;
        cout << "2. Xoa sach" << endl;
        cout << "3. Sua thong tin sach" << endl;
        cout << "4. Hien thi tat ca sach" << endl;
        cout << "5. Them nguoi dung" << endl;
        cout << "6. Xoa nguoi dung" << endl;
        cout << "7. Sua thong tin nguoi dung" << endl;
        cout << "8. Hien thi tat ca nguoi dung" << endl;
        cout << "9. Dang nhap nguoi dung" << endl;
        cout << "0. Thoat chuong trinh " << endl;
        cout << "Nhap lua chon cua ban: ";
				
		int choice;
        cin >> choice;
        
        switch (choice) 
		{
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                editBook();
                break;
            case 4:
                displayBooks();
                break;
            case 5:
                addUser();
                break;
            case 6:
                deleteUser();
                break;
            case 7:
                editUser();
                break;
            case 8:
                displayUsers();
                break;
            case 9:
                login();
                break;
            case 0:
                cout << "Cam on ban da su dung chuong trinh." << endl;
                return 0;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
        }
    }		
		return 0;
}


