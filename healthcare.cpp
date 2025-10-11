#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Patient {
public:
    string patientID, name, gender, contact, disease;
    int age;

    void registerPatient() {
        cout << "Enter Patient ID: ";
        cin >> patientID;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender: ";
        cin >> gender;
        cout << "Enter Contact: ";
        cin >> contact;
        cout << "Enter Disease: ";
        cin.ignore();
        getline(cin, disease);
        cout << "Patient registered successfully!\n";
    }

    void viewPatient() const {
        cout << "Patient ID: " << patientID << endl;
        cout << "Name      : " << name << endl;
        cout << "Age       : " << age << endl;
        cout << "Gender    : " << gender << endl;
        cout << "Contact   : " << contact << endl;
        cout << "Disease   : " << disease << endl;
    }
};

class Doctor {
public:
    string doctorID, name, specialty;
    vector<string> slots;

    Doctor(string id, string n, string spec, vector<string> s)
        : doctorID(id), name(n), specialty(spec), slots(s) {}

    void showDoctorDetails() const {
        cout << "Doctor ID: " << doctorID << endl;
        cout << "Name     : " << name << endl;
        cout << "Specialty: " << specialty << endl;
        cout << "Available Slots: ";
        for (const string& slot : slots) cout << slot << ", ";
        cout << endl;
    }
};

class Appointment {
public:
    string date = "27-Sep-2025";
    string time = "10:30 AM";
    Doctor doc;

    Appointment(const Doctor& d) : doc(d) {}

    void scheduleAppointment() const {
        cout << "Appointment scheduled with " << doc.name << " (" << doc.specialty << ") on " << date << " at " << time << endl;
    }
};

class Prescription {
public:
    void showPrescription(string patientID, string doctorName) {
        cout << "Patient ID: " << patientID << endl;
        cout << "Doctor: " << doctorName << endl;
        cout << "Prescription:\n";
        cout << "1. Paracetamol 500mg - Twice a day for 5 days\n";
        cout << "2. Vitamin C - Once daily\n";
    }
};

class Billing {
public:
    void generateBill(string patientID, string patientName) {
        int doctorFee = 500;
        int medicineCost = 250;
        int total = doctorFee + medicineCost;

        cout << "===== Bill Receipt =====\n";
        cout << "Patient ID   : " << patientID << endl;
        cout << "Patient Name : " << patientName << endl;
        cout << "Doctor Fee   : ₹" << doctorFee << endl;
        cout << "Medicine Cost: ₹" << medicineCost << endl;
        cout << "Total Amount : ₹" << total << endl;
        cout << "========================\n";
    }
};

bool login() {
    string username, password;
    cout << "===== Admin Login =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    if (username == "admin" && password == "1234") {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid credentials. Exiting...\n";
        return false;
    }
}

void savePatientsToFile(const vector<Patient>& patients) {
    ofstream file("patients.txt");
    for (const auto& p : patients) {
        file << p.patientID << "," << p.name << "," << p.age << "," << p.gender << "," << p.contact << "," << p.disease << "\n";
    }
    file.close();
}

void loadPatientsFromFile(vector<Patient>& patients) {
    ifstream file("patients.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Patient p;
        getline(ss, p.patientID, ',');
        getline(ss, p.name, ',');
        ss >> p.age;
        ss.ignore();
        getline(ss, p.gender, ',');
        getline(ss, p.contact, ',');
        getline(ss, p.disease, ',');
        patients.push_back(p);
    }
    file.close();
}

int findPatientIndex(const vector<Patient>& patients, const string& id) {
    for (size_t i = 0; i < patients.size(); ++i) {
        if (patients[i].patientID == id) return i;
    }
    return -1;
}

string getSpecialtyForDisease(const string& disease) {
    if (disease == "cold" || disease == "fever") return "General Physician";
    if (disease == "heart pain" || disease == "hypertension") return "Cardiologist";
    if (disease == "rash" || disease == "acne") return "Dermatologist";
    if (disease == "migraine" || disease == "seizure") return "Neurologist";
    return "General Physician";
}

int main() {
    if (!login()) return 0;

    vector<Patient> patients;
    loadPatientsFromFile(patients);

    vector<Doctor> doctors = {
        Doctor("D201", "Dr. Verma", "General Physician", {"10:30 AM", "11:30 AM", "3:00 PM"}),
        Doctor("D202", "Dr. Mehta", "Cardiologist", {"9:00 AM", "1:00 PM"}),
        Doctor("D203", "Dr. Rao", "Dermatologist", {"2:00 PM", "4:00 PM"}),
        Doctor("D204", "Dr. Kapoor", "Neurologist", {"11:00 AM", "5:00 PM"})
    };

    Prescription prescription;
    Billing billing;

    int choice;
    do {
        cout << "\n===== E-Healthcare Management System =====\n";
        cout << "1. Register New Patient\n";
        cout << "2. View Patient Records\n";
        cout << "3. Schedule Appointment\n";
        cout << "4. Doctor Details\n";
        cout << "5. Prescriptions & Medicines\n";
        cout << "6. Generate Bill\n";
        cout << "7. Search Patient\n";
        cout << "8. Update Patient\n";
        cout << "9. Delete Patient\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Patient newPatient;
                newPatient.registerPatient();
                patients.push_back(newPatient);
                savePatientsToFile(patients);
                break;
            }
            case 2: {
                for (const auto& p : patients) {
                    p.viewPatient();
                    cout << "------------------------\n";
                }
                break;
            }
            case 3: {
                string id;
                cout << "Enter Patient ID: ";
                cin >> id;
                int index = findPatientIndex(patients, id);
                if (index != -1) {
                    string disease = patients[index].disease;
                    string requiredSpecialty = getSpecialtyForDisease(disease);

                    bool found = false;
                    for (const auto& doc : doctors) {
                        if (doc.specialty == requiredSpecialty) {
                            Appointment appt(doc);
                            appt.scheduleAppointment();
                            found = true;
                            break;
                        }
                    }
                    if (!found) cout << "No doctor available for the disease: " << disease << endl;
                } else {
                    cout << "Patient not found.\n";
                }
                break;
            }
            case 4: {
                for (const auto& doc : doctors) {
                    doc.showDoctorDetails();
                    cout << "------------------------\n";
                }
                break;
            }
            case 5: {
                string id;
                cout << "Enter Patient ID: ";
                cin >> id;
                int index = findPatientIndex(patients, id);
                if (index != -1) {
                    string specialty = getSpecialtyForDisease(patients[index].disease);
                    for (const auto& doc : doctors) {
                        if (doc.specialty == specialty) {
                            prescription.showPrescription(id, doc.name);
                            break;
                        }
                    }
                } else {
                    cout << "Patient not found.\n";
                }
                break;
            }
            case 6: {
                string id;
                cout << "Enter Patient ID: ";
                cin >> id;
                int index = findPatientIndex(patients, id);
                if (index != -1)
                    billing.generateBill(id, patients[index].name);
                else
                    cout << "Patient not found.\n";
                break;
            }
            case 7: {
                string id;
                cout << "Enter Patient ID to search: ";
                cin >> id;
                int index = findPatientIndex(patients, id);
                if (index != -1)
                    patients[index].viewPatient();
                    else
                    cout << "Patient not found.\n";
                break;
            }
            case 8: {
                string id;
                cout << "Enter Patient ID to update: ";
                cin >> id;
                int index = findPatientIndex(patients, id);
                if (index != -1) {
                    cout << "Updating patient details...\n";
                    patients[index].registerPatient();
                    savePatientsToFile(patients);
                } else {
                    cout << "Patient not found.\n";
                }
                break;
            }
            case 9: {
                string id;
                cout << "Enter Patient ID to delete: ";
                cin >> id;
                int index = findPatientIndex(patients, id);
                if (index != -1) {
                    patients.erase(patients.begin() + index);
                    savePatientsToFile(patients);
                    cout << "Patient deleted successfully.\n";
                } else {
                    cout << "Patient not found.\n";
                }
                break;
            }
            case 10:
                cout << "Exiting System...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 10);

    return 0;
}
