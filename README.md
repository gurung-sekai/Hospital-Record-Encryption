# Hospital-Record-Encryption
Two C programs for nurses and consultants to securely store and retrieve patient records with simple Caesar-cipher encryption

# Secure Patient Record System – Nurse & Consultant Programs (C)

This repository contains **two improved C console applications** plus a detailed
PDF report documenting their design and testing.  
The project demonstrates secure handling of patient records for a small
medical-charity scenario.

---

## Overview
The system is split into two role-specific programs:

* **Nurse Program**  
  - Authenticates one of five authorised nurses.  
  - Collects patient details: name, DOB, height, weight, waist measurement,
    and comments.  
  - Encrypts sensitive fields and writes them to a per-patient file named
    `lastnameDDMMYYYY_record.aow`.

* **Consultant Program**  
  - Authenticates an authorised consultant.  
  - Retrieves and decrypts a patient file by last name and DOB.  
  - Allows the consultant to append new comments, then re-encrypts and saves
    the updated record.

---

## Key Features
* **Caesar-cipher encryption** (shift of 7) for passwords and patient data to
  maintain confidentiality.  
* **Struct-based design** for clear data modelling of both patients and users.  
* **File-based persistence** so each patient record is independent and easily
  retrievable.  
* **Improved code** over the original coursework:
  - Cleaner function separation.
  - Clearer prompts and comments.
  - Better handling of string input and edge cases.

---

## Repository Structure

├── nurse_improved.c # Improved nurse program
├── consultant_improved.c # Improved consultant program
├── hospitalproject.pdf # Full design, testing and evaluation report
└── README.md
