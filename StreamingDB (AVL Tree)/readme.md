# 📽️ StreamingDB – Wet Assignment 1 (234218, אביב תשפ"ג)

## 📝 Overview
This project implements a custom **streaming service database** (`streaming_database`) as specified in **Wet 1** of the Data Structures course. It is a full-featured data structure that supports operations on movies, users, and groups, with support for VIP logic, viewing history, and genre-based recommendations.

The solution is fully implemented in **C++ (C++11 standard)** using **custom AVL trees**, with **no usage of STL containers**, as required.

## 📁 File Structure

```
.
├── StreamingDBa1.cpp          # Main implementation of the streaming_database class
├── StreamingDBa1.h            # Class declaration for streaming_database
├── AVLTree.h                  # Generic AVL Tree implementation
├── Node.h                     # Node structure used in the AVL tree
├── movie.h / movie.cpp        # Movie class
├── user.h / user.cpp          # User class
├── group.h / group.cpp        # Group class
├── wet1util.h                 # Provided utility header (DO NOT EDIT)
├── main1.cpp                  # Provided main for testing (DO NOT EDIT)
```

## ⚙️ Compilation

Ensure all files are in the root directory and compile using:
```bash
g++ -std=c++11 -DNDEBUG -Wall *.cpp
```

## 🚀 Running the Program

Use the provided `main1.cpp` and input files for testing:
```bash
./a.out < input.txt > output.txt
```

Make sure to test on the `3csl` server environment and verify memory management with tools like `valgrind`.

---

## 🔧 Implemented Functionalities

- **Movie Operations**
  - Add / remove movie
  - Get all movies by genre, sorted by rating and views
  - Get total number of movies by genre
  - Rate a movie

- **User Operations**
  - Add / remove user
  - Watch movie (individual and group)
  - Track viewing stats per genre
  - Restrict VIP-only content

- **Group Operations**
  - Add / remove group
  - Add user to group (single-group constraint)
  - Group watch
  - Genre preference and movie recommendation

---

## ✅ Data Structures

- **AVL Trees**
  - Used for maintaining all movies, users, and groups with O(log n) operations
  - Specialized AVL trees for:
    - `movies_by_id`
    - `movies_by_rating` (per genre and global)
    - `users_by_id`
    - `groups_by_id`
  - `Movie`, `User`, and `Group` objects stored via raw pointers

---

## 💾 Memory Management

- All objects are dynamically allocated.
- Trees are properly destructed in `streaming_database::~streaming_database()` by flattening and deleting nodes.
- No STL containers used.
- `valgrind` tested for leaks and invalid accesses.

