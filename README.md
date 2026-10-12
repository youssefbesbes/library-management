# Library Management (Gestion d'une bibliothèque)

A console application written in **C** to manage a library: books, loans and returns, and usage statistics. Everything is driven by an interactive text menu.

## Features

### 1. Library management
- Display all books (number, title, copies)
- Add a book
- Delete a book
- Change the number of copies
- Search a book by title or by number
- List available books

### 2. Loan management
- Add a loan (with date checks)
- View the loans of a member (by CIN)
- Record the return of a book
- Display current loans
- Display overdue books for a given current date
- Display loans due on a given return date
- Delete a set of loans within a date range

### 3. Statistics
- Total number of books, members and loans
- Most borrowed book(s)
- Books that were never borrowed
- Most borrowed book(s) during a given period
- Most frequent borrower(s)

## Rules implemented

- A member is identified by a **CIN of 8 digits**, starting with `0` or `1`.
- A member can have at most **7 active loans**.
- The loan duration cannot exceed **30 days**, and the return date cannot be before the loan date.
- A loan is refused if no copy is available. In that case, the program shows the date when the book will be available again.
- Dates are entered as `J/M/A` (day/month/year) and validated, including leap years (years 1900 to 2100).

## How it works

- Books and loans are stored in **arrays** (`T_Titre`, `T_NLivre`, `T_Nbr_exp` for books, `T_emp` for current loans,
