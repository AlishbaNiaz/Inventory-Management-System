# Inventory-Management-System
A console-based C++ program for inventory management system

# 📦 Inventory Management System (C++)

A **console-based Inventory and Order Management System** developed in **C++** using file handling and dynamic memory allocation.  
It allows **admins** to manage products (add, update, delete, view inventory) and **users** to browse products, add items to their cart, view total cost, and confirm orders.  
The project is designed for **learning purposes** to understand core C++ concepts like arrays, dynamic memory, custom string handling, and file I/O.

---

## ✨ Features

### User Features
- Register and login as a new user
- View available products
- Add items to shopping cart
- View cart items and calculate total cost
- Confirm orders (saves to admin records)
- Logout functionality

### Admin Features
- View product inventory
- Add new products
- Update product stock quantity
- Delete existing products
- View all confirmed orders from users
- Logout functionality

---

## 🧰 Technologies Used
- **C++** (Core programming language)
- **File Handling** (`ifstream` and `ofstream`)
- **Dynamic Memory Allocation** (`new` and `delete`)
- **Custom Functions** for:
  - Array manipulation
  - String comparison and copy
  - Formatted output

---

## 📁 File Structure
- **`main.cpp`** → Main program source code (contains menus, logic, and file handling)
- **`Product.txt`** → Stores available products (ID, Name, Cost, Quantity, Category)
- **`Admin.txt`** → Stores confirmed order details
- **User Files** → Individual files created for each registered user (for storing cart and order data)

---

## 🛠 Installation & Usage

### 1. Clone the repository
```bash
git clone https://github.com/your-username/Inventory-Management-System.git
cd Inventory-Management-System
