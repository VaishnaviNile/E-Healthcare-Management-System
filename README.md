# 🏥 E-Healthcare Management System (C++ OOP Project)

## 📘 Description
The **E-Healthcare Management System** is a console-based C++ project developed as part of an **Object-Oriented Programming (OOPs)** course.  
It allows hospital administrators to efficiently manage patient records, schedule appointments, view doctor details, generate prescriptions, and handle billing — all using core OOP concepts.

---

## 🎯 Project Objectives
- To implement **real-world healthcare management** using C++.
- To demonstrate **Encapsulation, Inheritance, and Polymorphism**.
- To store and retrieve patient data using **file handling**.
- To simulate an admin-controlled healthcare system.

---

## ⚙️ Features
### 👤 Patient Management
- Register a new patient  
- View all patient records  
- Search, update, and delete existing patients  
- Automatically saves patient data to a text file (`patients.txt`)  

### 🩺 Doctor Management
- View list of available doctors  
- Each doctor has an ID, specialty, and time slots  

### 📅 Appointment Scheduling
- Automatically assigns a doctor based on patient’s disease  
- Displays appointment confirmation with date and time  

### 💊 Prescription Handling
- Displays a fixed set of medicines based on doctor consultation  

### 💰 Billing System
- Calculates total charges (doctor + medicines)  
- Displays formatted bill receipt  

### 🔐 Admin Login
- Secure login required before accessing system features  


---

## 🧱 Class Structure Overview

| Class Name     | Description |
|----------------|--------------|
| **Patient**     | Handles patient registration, viewing, and file storage |
| **Doctor**      | Stores and displays doctor information |
| **Appointment** | Manages patient appointments with doctors |
| **Prescription**| Displays medicines prescribed by the doctor |
| **Billing**     | Generates and displays bill summary |

---

## 🧮 OOP Concepts Used
- **Encapsulation:** Each class manages its own data and functions.  
- **Abstraction:** Unnecessary details are hidden from the user.  
- **Composition:** Appointment, Billing, and Prescription depend on Doctor and Patient objects.  
- **File Handling:** Patient data is stored persistently in `patients.txt`.

---


