
# Records Company – Assignment 2 (Wet Part)  
**Course:** Data Structures 234218, Spring 2023  

---

## Overview  
This project simulates a **records company system** that manages record stock, customers, membership, purchases, and promotions. The core system is implemented with custom data structures such as:

- **HashTable** (for customer management)
- **AVL Tree** (for club members and expenses)
- **Union-Find** (for stacking records)
- **Dynamic Array** (to manage record nodes)

All operations are designed to meet strict time and space complexity constraints specified in the assignment.

---

## Core Functionalities

### Initialization
- `RecordsCompany()` – Initializes an empty records company.
- `~RecordsCompany()` – Frees all allocated memory.

### Monthly Reset
- `newMonth(int* records_stocks, int number_of_records)`  
  Initializes the stock levels and record groups for a new month. All customer expenses and record stacks are reset.

### Customer Operations
- `addCostumer(int c_id, int phone)`  
  Adds a new customer with a phone number.
- `getPhone(int c_id)`  
  Retrieves the phone number of a specific customer.
- `makeMember(int c_id)`  
  Converts a customer to a club member.
- `isMember(int c_id)`  
  Checks if a customer is a club member.
- `buyRecord(int c_id, int r_id)`  
  Simulates the purchase of a record, adding expenses if the customer is a member.
- `addPrize(int c_id1, int c_id2, double amount)`  
  Grants a promotional discount to a range of club members.
- `getExpenses(int c_id)`  
  Returns the total expenses of a club member, including discount adjustments.

### Record Operations
- `putOnTop(int r_id1, int r_id2)`  
  Merges two record stacks, putting `r_id1` on top of `r_id2`.
- `getPlace(int r_id, int* column, int* height)`  
  Returns the position of a record within its stack (column and height).

---

## Compilation

To compile the project on `3csl` server (Technion), use the following command:

```bash
g++ -std=c++11 -DNDEBUG -Wall *.cpp
```

Make sure your `mainWet2.cpp` and `utilesWet2.h` remain unchanged and are not submitted.

---

## File Structure

```
📁 Submission/
├── recordsCompany.cpp
├── recordsCompany.h
├── UnionFind.cpp
├── UnionFind.h
├── Costumer.cpp
├── Costumer.h
├── HashTable.h
├── RankAvlTree.h
├── dynamicArr.h
├── linkedList.h
├── GenericNode.h
├── README.md       <-- This file
├── pdf.dry         <-- Dry part in PDF format
├── txt.submissions <-- Submission metadata
```

---

## Notes

- STL usage (e.g., `std::vector`, `std::pair`, `std::map`) is strictly forbidden.
- All data structures and algorithms are implemented manually.
- Memory management was handled carefully; use of tools like `valgrind` is recommended to ensure correctness.

---

