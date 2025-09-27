# Hospital Record Encryption (C)

Two complementary C programs that demonstrate secure collection and retrieval of patient records:

* **Nurse Program** – creates encrypted patient files.
* **Consultant Program** – retrieves and updates those files.

A project to showcase **C programming**, **file I/O**, and **basic encryption** concepts.

---

## Features

### Nurse Program (`nurse.c`)
* Authenticates nurse with username and password (stored as Caesar-cipher text).
* Accepts patient first name, last name, date of birth, and notes.
* Encrypts and saves data to a file named `<lastname><dob>_record.aow`.

### Consultant Program (`consultant.c`)
* Authenticates consultant credentials.
* Requests patient last name and DOB to locate the encrypted file.
* Decrypts, displays patient details, and optionally appends new notes.
* Re-encrypts and saves the updated record.

---

## File Structure

```
├── nurse.c              # Nurse-side program
├── consultant.c         # Consultant-side program
├── hospitalproject.pdf  # Full design and test report
└── README.md
```

---

## Build

Use any C11-compatible compiler (e.g. GCC or Clang):

```bash
gcc -std=c11 -O2 -Wall -Wextra -o nurse nurse.c
gcc -std=c11 -O2 -Wall -Wextra -o consultant consultant.c
```

This produces two executables: `nurse` and `consultant`.

---

## Run

### Nurse Program
```bash
./nurse
```
You’ll be prompted for:
1. **User** (default demo: `nurse`)
2. **Password** (demo: `nursepass`)

Then enter patient details:
* First name
* Last name
* DOB (DDMMYYYY)
* Initial notes

The program creates an encrypted record file such as:
```
<lastname><dob>_record.aow
```

### Consultant Program
```bash
./consultant
```
Steps:
1. Enter consultant credentials (demo user: `consultant`, password: `consultpass`).
2. Provide the patient’s last name and DOB.
3. View decrypted details and optionally add extra notes, which are re-encrypted on save.

---

## Example Session

```
== Nurse Login ==
User: nurse
Pass: nursepass

== New Patient Entry ==
First name: Alice
Last name: Smith
DOB (DDMMYYYY): 01012000
Initial notes: Routine check-up
Saved encrypted record: smith01012000_record.aow
```

Consultant side:

```
== Consultant Login ==
User: consultant
Pass: consultpass

== Open Patient Record ==
Last name: smith
DOB (DDMMYYYY): 01012000

-- Current Record --
First: Alice
Last: Smith
DOB: 01012000
Notes: Routine check-up
Add consultant notes (blank to skip): Follow-up in 6 months
Updated and re-encrypted.
```

---

## Documentation

Full design, implementation details, testing, and evaluation are provided in the project report:

[Hospital Project Report (PDF)](ActionOnWeight-Patient-System/hospitalproject.pdf)

---

## Key Learning Points

* **C Programming:** structured design, input validation, and modular functions.
* **File I/O:** creation, reading, and updating of structured text records.
* **Encryption Basics:** implementing a Caesar cipher for simple data protection.
* **User Authentication:** verifying credentials against encrypted password storage.

---

## Future Improvements

* Replace Caesar cipher with modern cryptography (e.g., AES via OpenSSL or libsodium).
* Improve input validation and error handling.
* Add unit tests and a Makefile for easier builds.
* Expand to a database backend (SQLite) for scalable record management.

---

Developed by **Pritam Gurung**  
