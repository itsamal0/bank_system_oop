# Bank Management System (OOP Version)

A professional **Object-Oriented Bank Management System** written in C++, focusing on clean architecture and modular design.

This project is part of my **Learning Path**, done during **Course 11 (OOP Level 2)**  
from the **Programming Advices roadmap**.  
You can explore my full Learning Path repository here: [Learning Path Repository](https://github.com/itsamal0/learning-path)

---

## Project Structure & Architecture
The project follows a **Layered Architecture** to ensure maintainability and scalability:

- **`Core/`**: Contains the main business logic (Clients, Users, Currencies, and Persons).
- **`Screens/`**: Managed UI layers, subdivided into logical modules (Login, Clients, Currencies, etc.).
- **`Lib/`**: Reusable utility libraries (Date, String, Validation, and Utilities).
- **`Data/`**: Persistent storage using flat files (.txt).

---

## Features
- **Client Management**: Full CRUD operations (Add, Delete, Update, Find).

- **Transaction System**: 
    - Secure Deposit & Withdraw.
    - Transfer money between accounts.
    - Comprehensive Transfer Log.
- **Currency Exchange**: 
    - Real-time currency conversion.
    - Update exchange rates.
    - Currency Calculator tool.
- **User Management**: 
    - Permissions-based access control.
    - Full User CRUD (Add, Delete, Update, Find).
    - Login/Register history logging.
- **Security**: Basic password encryption/decryption using a custom utility library.

---

## Getting Started

### 1. Clone the repository  
If you have Git installed, run:
```bash
git clone https://github.com/itsamal0/bank_system_oop.git
cd bank_system_oop
```
Or download the project as a ZIP file and extract it.

### 2. Build the project  
Make sure you have a C++ compiler (e.g., g++ or clang) installed. Then build the project:
```bash
g++ main.cpp -o bank_system
```

### 3. Run the program  
After building successfully, run the program:
```bash
./bank_system
```