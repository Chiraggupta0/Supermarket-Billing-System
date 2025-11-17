#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float dis;
    string pname;
    bool isPremiumMember; 
public:
    shopping() : isPremiumMember(false) {}
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt(bool isPremiumMember);
    void addUserDetails();
    void becomePremiumMember();
    void refund();
    void saveTransaction(const vector<int>& arrc, const vector<int>& arrq, float total, const string& transactionType, const string& customerName, const string& customerPhone); 
};


void shopping::menu() {
    int choice;
    string email;
    string password;

    while (true) {
        cout << "\t\t\t\t______________________________\n";
        cout << "\t\t\t\t    Supermarket Main Market   \n";
        cout << "\t\t\t\t______________________________\n";
        cout << "\t\t\t\t|  1) Administrator  |\n";
        cout << "\t\t\t\t|  2) Buyer          |\n";
        cout << "\t\t\t\t|  3) Exit           |\n";
        cout << "\n\t\t\t Please select: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\t\t\t Please Login \n";
            cout << "\t\t\t Enter Email: ";
            cin >> email;
            cout << "\t\t\t Password: ";
            cin >> password;
            if (email == "chirag@email.com" && password == "chirag123") {
                administrator();
            } else {
                cout << "Invalid email/password\n";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);

        default:
            cout << "Please select from the given options\n";
        }
    }
}

void shopping::administrator() {
    cout << "Entered administrator function\n"; 
    int choice;

    while (true) {
        cout << "\n\n\t\t\t Administrator menu ";
        cout << "\n\t\t\t|____1) Add the product____|";
        cout << "\n\t\t\t|____2) Modify the product_|";
        cout << "\n\t\t\t|____3) Delete the product_|";
        cout << "\n\t\t\t|____4) Back to main menu__|";
        cout << "\n\n\t Please enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            return; // Back to main menu
        default:
            cout << "Invalid choice!\n";
        }
    }
}
void shopping::becomePremiumMember() {
    char choice;
    cout << "Do you want to become a premium member for 500 Rupees per month? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        isPremiumMember = true;
        cout << "You are now a premium member! You will receive an extra 5% discount on all products.\n";
    } else {
        cout << "You chose not to become a premium member.\n";
    }
}

void shopping::addUserDetails() {
    ofstream userFile("users.txt", ios::app);
    if (!userFile) {
        cout << "Error opening file to save user details.\n";
        return;
    }

    string name, email, phone;
    cout << "\nEnter your Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your Email: ";
    getline(cin, email);
    cout << "Enter your Phone Number: ";
    getline(cin, phone);

    userFile << name << "," << email << "," << phone << endl; 
    userFile.close();
    cout << "User details saved successfully!\n";
    becomePremiumMember(); 
}


void shopping::buyer() {
    int choice;

    addUserDetails(); 
    while (true) {
        cout << "\t\t\t  Buyer \n";
        cout << "\t\t\t 1) Buy Product \n";
        cout << "\t\t\t 2) Refund Product \n"; 
        cout << "\t\t\t 3) Go back \n";
        cout << "\t\t\t Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            receipt(isPremiumMember);
            break;
        case 2:
            refund(); 
            break;
        case 3:
            return; 
        default:
            cout << "Invalid choice\n";
        }
    }
}
void shopping::add() {
    fstream data;
    int c;
    string n;
    float p, d;

    while (true) {
        bool duplicateFound = false;

        cout << "\n\n\t\t\t Add new product";
        cout << "\n\n\t Product code of the product: ";
        cin >> pcode;

        cout << "\n\n Name of the product: ";
        cin >> pname;

        cout << "\n\n\t Price of the product: ";
        cin >> price;
        if (price < 0) {
            cout << "Price cannot be negative. Please enter again.\n";
            continue; 
        }

        cout << "\n\n\t Discount on the product: ";
        cin >> dis;
        if (dis < 0 || dis > 100) {
            cout << "Discount must be between 0 and 100. Please enter again.\n";
            continue; 
        }

        data.open("database.txt", ios::in);
        if (data) {
            while (data >> c >> n >> p >> d) {
                if (c == pcode) {
                    duplicateFound = true;
                    cout << "\n\n\t Product code already exists. Try again.\n";
                    break;
                }
            }
            data.close();
        }

        if (!duplicateFound) {
            data.open("database.txt", ios::app);
            data << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
            cout << "\n\n\t\t Record inserted!\n";
            break; 
        }
    }
}

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n File doesn't exist!\n";
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    while (data >> pcode >> pname >> price >> dis) {
        if (pkey == pcode) {
            cout << "\n\t\t New product code: ";
            cin >> pcode;
            cout << "\n\t\t Name of the product: ";
            cin >> pname;
            cout << "\n\t\t Price: ";
            cin >> price;
            cout << "\n\t\t Discount: ";
            cin >> dis;
            cout << "\n\n\t\t Record edited\n";
            token++;
        }
        data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
    }
    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0) {
        cout << "\n\n Record not found, sorry!\n";
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File doesn't exist\n";
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    while (data >> pcode >> pname >> price >> dis) {
        if (pcode == pkey) {
            cout << "\n\n\t Product deleted successfully\n";
            token++;
        } else {
            data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
    }
    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0) {
        cout << "\n\n Record not found\n";
    }
}

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|____________________________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "|____________________________________________________\n";
    
    while (data >> pcode >> pname >> price >> dis) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
    }
    data.close();
}
void shopping::saveTransaction(const vector<int>& arrc, const vector<int>& arrq, 
                                float total, const string& transactionType, 
                                const string& customerName, const string& customerPhone) {
    ofstream transactionFile("transactions.txt", ios::app);
    if (!transactionFile) {
        cout << "Error opening transaction file.\n";
        return;
    }

    transactionFile << "\nTransaction Type: " << transactionType << "\n";
    transactionFile << "Customer Name: " << customerName << "\n";
    transactionFile << "Customer Contact: " << customerPhone << "\n";
    transactionFile << "Products " << (transactionType == "Purchase" ? "Purchased" : "Returned") << ":\n";
    
    for (size_t i = 0; i < arrc.size(); i++) {
        transactionFile << "Product Code: " << arrc[i] << ", Quantity: " << arrq[i] << "\n";
    }
    transactionFile << "Total Amount: " << total << "\n\n";
    transactionFile.close();
}

void shopping::receipt(bool isPremiumMember) {
    fstream data;
    vector<int> arrc;
    vector<int> arrq;
    char choice;
    float amount = 0, total = 0;

    string customerName, customerPhone;
  
    cout << "\nEnter your Name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter your Phone Number: ";
    getline(cin, customerPhone);

    cout << "\n\n\t\t\t\t  RECEIPT";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database\n";
        return;
    }

    list();
    cout << "\n______________________________________________________\n";
    cout << "\n                 Please place the order               \n";
    cout << "______________________________________________________\n";

    do {
        int productCode;
        cout << "\n\n Enter product code: ";
        cin >> productCode;

        bool validProductCode = false;
        data.clear();
        data.seekg(0);
        while (data >> pcode >> pname >> price >> dis) {
            if (productCode == pcode) {
                validProductCode = true;
                arrc.push_back(pcode);
                break;
            }
        }

        if (!validProductCode) {
            cout << "\n\n Invalid product code. Please try again!";
            continue;
        }

        int quantity;
        cout << "\n\n Enter the product quantity: ";
        cin >> quantity;
        arrq.push_back(quantity);

        cout << "\n\n Do you want to buy another product? (Y/N): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\n\n\t\t\t__________________________________RECEIPT_______________________________________\n";
    cout << "Product no\t Product Name\t\t Product Quantity\t Price\t Amount\t Amount after discount\n";
    cout << "_____________________________________________________________________________________\n";

    for (size_t i = 0; i < arrc.size(); i++) {
        data.clear();
        data.seekg(0);
        while (data >> pcode >> pname >> price >> dis) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                float discountAmount = amount * (dis / 100);
                float amountAfterStandardDiscount = amount - discountAmount;

              
                if (isPremiumMember) {
                    float premiumDiscount = amountAfterStandardDiscount * 0.05;
                    amountAfterStandardDiscount -= premiumDiscount; 
                }
                
                total += amountAfterStandardDiscount;

                
                cout << fixed;
                cout.precision(2); 
                cout << pcode << "\t\t" << pname << "\t\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t" << amountAfterStandardDiscount << endl;
            }
        }
    }

    cout << "\nTotal Amount: " << total << endl;

   
    saveTransaction(arrc, arrq, total, "Purchase", customerName, customerPhone);
}
void shopping::refund() {
    fstream data;
    vector<int> arrc;
    vector<int> arrq;
    char choice;
    float amount = 0, total = 0;

    string customerName, customerPhone;

   
    cout << "\nEnter your Name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter your Phone Number: ";
    getline(cin, customerPhone);

    cout << "\n\n\t\t\t\t  REFUND";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database\n";
        return;
    }

    list();
    cout << "\n______________________________________________________\n";
    cout << "\n                 Please place the refund request      \n";
    cout << "______________________________________________________\n";

    do {
        int productCode;
        cout << "\n\n Enter product code: ";
        cin >> productCode;

        bool validProductCode = false;
        data.clear();
        data.seekg(0);
        while (data >> pcode >> pname >> price >> dis) {
            if (productCode == pcode) {
                validProductCode = true;
                arrc.push_back(pcode);
                break;
            }
        }

        if (!validProductCode) {
            cout << "\n\n Invalid product code. Please try again!";
            continue;
        }

        int quantity;
        cout << "\n\n Enter the product quantity to refund: ";
        cin >> quantity;
        arrq.push_back(quantity);

        cout << "\n\n Do you want to refund another product? (Y/N): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\n\n\t\t\t__________________________________REFUND_______________________________________\n";
    cout << "Product no\t Product Name\t\t Product Quantity\t Price\t Refund Amount\n";
    cout << "_____________________________________________________________________________________\n";

    for (size_t i = 0; i < arrc.size(); i++) {
        data.clear();
        data.seekg(0);
        while (data >> pcode >> pname >> price >> dis) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                float discountAmount = amount * (dis / 100);
                float amountAfterDiscount = amount - discountAmount;
                
                total += amountAfterDiscount;
                cout << fixed;
                cout.precision(2);
                cout << pcode << "\t\t" << pname << "\t\t\t" << arrq[i] << "\t\t" << price << "\t" << amountAfterDiscount << endl;
            }
        }
    }

    cout << "\nTotal Refund Amount: " << total << endl;

   
    saveTransaction(arrc, arrq, total, "Refund", customerName, customerPhone);
}

int main() {
    shopping s;
    s.menu();
    return 0;
}
