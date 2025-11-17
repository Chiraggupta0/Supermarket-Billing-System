# C++ File-Handling Based Billing, Refund & Premium Membership System

A console-based Supermarket Billing System implemented using C++, featuring product management, user management, transaction logging, premium membership, and refund system.

---

## ✔ This README Includes
- Project Overview  
- Features  
- Folder Structure  
- How to Run  
- All Diagrams (DFD, Use Case, Class Diagram, Sequence Diagram, ER Diagram)

---

## 📌 1. Project Overview
This system allows:
- Administrator to add, edit, delete products  
- Buyers to purchase or refund products  
- System to generate receipt & store transactions  
- Users to become premium members and get extra discounts  
- Uses file handling with `database.txt`, `users.txt`, and `transactions.txt`.

---

## ⭐ 2. Features

### 👨‍💼 Admin
- Add products  
- Edit products  
- Delete products  

### 🛍 Buyer
- Buy products  
- Refund items  
- Get printed receipt  
- Premium membership option  

### 📂 File Handling
- Stores all users  
- Stores all product data  
- Stores complete transactions  

---

## 📁 3. Folder Structure
Supermarket-Billing-System/
│
├── main.cpp
├── database.txt
├── users.txt
├── transactions.txt
├── README.md


---

## ⚙️ 4. How to Run

### **Compile**
bash
g++ main.cpp -o market


Run
./market

#🧩 5. Diagrams 

## 5.1 Use Case Diagram


usecaseDiagram
actor Admin
actor Buyer

Admin --> (Add Product)
Admin --> (Edit Product)
Admin --> (Delete Product)

Buyer --> (Buy Product)
Buyer --> (Refund Product)
Buyer --> (Become Premium Member)
Buyer --> (View Receipt)

##5.2 Level-0 Data Flow Diagram (DFD)

➡ Place under DFD Level-0 heading

flowchart LR
User -->|Buys/Refunds| System
Admin -->|Manage Products| System
System -->|Store Data| Database[(Files)]
System -->|Generate Receipt| User

##5.3 Level-1 DFD

➡ Place under Level-1 DFD heading

flowchart LR
A[Admin] --> B[Product Management]
B --> DB[(database.txt)]

C[Buyer] --> D[Purchase Module]
C --> E[Refund Module]
D --> T[(transactions.txt)]
E --> T[(transactions.txt)]

C --> F[Premium Membership Module]
F --> U[(users.txt)]

##5.4 Class Diagram

➡ Place under Class Diagram heading

classDiagram
class shopping {
    -int pcode
    -float price
    -float dis
    -string pname
    -bool isPremiumMember
    +menu()
    +administrator()
    +buyer()
    +add()
    +edit()
    +rem()
    +list()
    +receipt()
    +refund()
    +addUserDetails()
    +becomePremiumMember()
    +saveTransaction()
}

##5.5 Sequence Diagram (Buying a Product)

➡ Place here under Sequence Diagram heading

sequenceDiagram
participant Buyer
participant System
participant Database

Buyer->>System: Select Buy
System->>Database: Fetch product list
Database-->>System: Return products
Buyer->>System: Enter product code & qty
System->>Database: Calculate amount & discounts
System->>Buyer: Show receipt
System->>Database: Save transaction

##5.6 Entity Relationship Diagram (ERD)

➡ Place under ER Diagram heading

erDiagram
    USER {
        string name
        string email
        string phone
        bool premium
    }

    PRODUCT {
        int pcode
        string pname
        float price
        float discount
    }

    TRANSACTION {
        int tid
        int pcode
        int quantity
        float total
        string type
    }

    USER ||--o{ TRANSACTION : "makes"
    PRODUCT ||--o{ TRANSACTION : "included in"

#📝 6. Conclusion

This project is a complete file-based C++ supermarket billing system featuring:

Product management

Real billing

Refund system

User & membership storage

Transaction logs

Clean console UI

You can expand it using:

OOP classes

STL (vectors/maps)

GUI (Qt / Tk / Web)

Database (MySQL / SQLite)




