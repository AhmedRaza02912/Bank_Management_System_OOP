
1. USER-DEFINED CLASSES
------------------------
Two main classes are used:

- class User:
  Stores details like name, ID, password, and account balance.
  It also handles operations like:
    - Account creation
    - Searching account
    - Depositing money
    - Withdrawing money

- class Admin:
  Provides administrative controls:
    - Adjust user balances
    - View all user details (password protected)

2. CLASS CONSTRUCTOR
---------------------
- Constructor `User::User()` is called when a new user object is created.
- Displays a welcome message.

3. ENCAPSULATION
------------------
Private data members (like name, ID, password, amount) are accessed using public getter/setter methods:
- setName(), getName()
- setID(), getID()
- setPassword(), getPassword()
- setAmount(), getAmount()

4. VECTORS
-----------
- `vector<User>` is used to store all registered users dynamically in memory.
- Vectors provide flexibility and scalability compared to static arrays.

5. FILE HANDLING
-----------------
Data persistence is done using the following files:

- "users.txt": stores username and ID
- "amounts.txt": stores ID and balance
- "transactions.txt": logs deposits and withdrawals with updated balance

C++ File Streams:
- ofstream: to write to files
- ifstream: to read from files
- ios::app: to append to existing file data

6. TRANSACTIONS
----------------
- A simple `Transaction` structure/object is used to store:
  - Type: Deposit or Withdraw
  - Amount: how much was deposited/withdrawn
  - UpdatedAmount: balance after the transaction
  - userID: associated user ID

7. PASSWORD PROTECTION
-----------------------
- User access requires correct ID and password.
- Admin access is protected by a hardcoded admin password ("admin123").

8. CONTROL FLOW & MENU SYSTEM
------------------------------
- A main loop (do-while) repeatedly shows the main menu until the user exits.
- A switch-case block handles menu options:
  - Add account
  - Search account
  - Deposit money
  - Withdraw money
  - Admin controls
  - Show all accounts
  - Exit

9. ERROR HANDLING (BASIC)
---------------------------
- Prevents duplicate user IDs
- Validates deposit/withdrawal amounts
- Checks password and ID match
- Displays error messages on incorrect actions

10. BANK CHARGES
-----------------
- Every deposit and withdrawal includes a bank charge of 0.333 units deducted from the user's balance.
- `bank_charges` is a float field in User to accumulate total charges paid.

11. FRIEND FUNCTION
--------------------
- `displayAllUsers()` is a friend-like function (though not declared with `friend`) that takes a vector of users and displays them. It's protected with an admin password.
