#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// ======================= HELPER: lowercase normalize =======================
string normalize(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// ======================= PATIENT CLASS =======================
class Patient {
public:
    string patientID, name, gender, contact, disease;
    int age;

    void registerPatient() {
        cout << "Enter Patient ID: ";
        cin >> patientID;
        if (patientID.empty()) {
            cout << "⚠️ Patient ID cannot be empty.\n";
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        if (name.empty()) {
            cout << "⚠️ Name cannot be empty.\n";
            return;
        }

        cout << "Enter Age: ";
        cin >> age;
        if (age <= 0 || age > 120) {
            cout << "⚠️ Invalid age entered.\n";
            return;
        }

        cout << "Enter Gender (Male/Female/Other): ";
        cin >> gender;
        if (gender != "Male" && gender != "Female" && gender != "Other") {
            cout << "⚠️ Please enter Male, Female, or Other.\n";
            return;
        }

        cout << "Enter Contact (10 digits): ";
        cin >> contact;
        if (contact.length() != 10 || !all_of(contact.begin(), contact.end(), ::isdigit)) {
            cout << "⚠️ Contact number must be 10 digits.\n";
            return;
        }

        cout << "Enter Disease: ";
        cin.ignore();
        getline(cin, disease);
        if (disease.empty()) {
            cout << "⚠️ Disease cannot be empty.\n";
            return;
        }

        cout << "✅ Patient registered successfully!\n";
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

// ======================= DOCTOR CLASS =======================
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

// ======================= APPOINTMENT CLASS =======================
class Appointment {
public:
    string date, appointmentTime;
    Doctor doc;

    Appointment(const Doctor& d) : doc(d) {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int day = ltm->tm_mday;
        int month = 1 + ltm->tm_mon;
        int year = 1900 + ltm->tm_year;
        string monthName[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
        date = (day < 10 ? "0" : "") + to_string(day) + "-" + monthName[month-1] + "-" + to_string(year);

        srand(static_cast<unsigned>(time(0)));
        int delayMinutes = (rand() % 3 + 1) * 30;

        time_t future = now + delayMinutes * 60;
        tm *ftm = localtime(&future);
        stringstream ss;
        int hour = ftm->tm_hour;
        int minute = ftm->tm_min;
        string ampm = (hour >= 12) ? "PM" : "AM";
        hour = (hour % 12 == 0) ? 12 : hour % 12;
        ss << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " " << ampm;
        appointmentTime = ss.str();
    }

    void scheduleAppointment() const {
        cout << "📅 Appointment scheduled with " << doc.name
             << " (" << doc.specialty << ") on "
             << date << " at " << appointmentTime << endl;
    }
};

// ======================= PRESCRIPTION CLASS =======================
class Prescription {
public:
    void showPrescription(string patientID, string doctorName, string disease, int age) {
        cout << "\n===== Prescription Details =====\n";
        cout << "Patient ID : " << patientID << endl;
        cout << "Doctor     : " << doctorName << endl;
        cout << "Disease    : " << disease << endl;
        cout << "Age        : " << age << " years\n\n";
        cout << "Prescription:\n";

        bool isChild = age < 12;
        bool isElderly = age >= 60;
        string d = normalize(disease);

        if (d == "cold" || d == "fever") {
            if (isChild)
                cout << "1. Paracetamol Syrup (250mg) - 5ml twice a day for 3 days\n2. Cough Syrup - 5ml twice daily\n";
            else if (isElderly)
                cout << "1. Paracetamol 500mg - Once daily\n2. Hydration and rest recommended\n";
            else
                cout << "1. Paracetamol 500mg - Twice a day for 3 days\n2. Cough Syrup - 10ml twice daily\n";
        } 
        else if (d == "heart pain" || d == "hypertension") {
            cout << "1. Aspirin 75mg - Once daily\n2. Atorvastatin 10mg - Once at night\n3. Regular BP monitoring advised\n";
        } 
        else if (d == "rash" || d == "acne")
            cout << "1. Topical Cream - Apply twice daily\n2. Cetirizine 10mg - Once daily\n";
        else if (d == "migraine" || d == "seizure")
            cout << "1. Sumatriptan 50mg - When migraine occurs\n2. Magnesium supplement - Once daily\n";
        else if (d == "asthma")
            cout << "1. Inhaler (Salbutamol) - As prescribed\n2. Montelukast 10mg - Once daily\n";
        else if (d == "diabetes")
            cout << "1. Metformin 500mg - Twice daily after meals\n2. Regular sugar monitoring advised\n";
        else if (d == "thyroid")
            cout << "1. Thyroxine 50mcg - Once daily (empty stomach)\n2. Avoid oily foods\n";
        else if (d == "fracture" || d == "joint pain")
            cout << "1. Calcium supplements - Twice daily\n2. Physiotherapy and rest advised\n";
        else if (d == "stomach pain" || d == "ulcer")
            cout << "1. Pantoprazole 40mg - Before breakfast\n2. Avoid spicy food and caffeine\n";
        else
            cout << "1. Multivitamin - Once daily\n2. Drink plenty of fluids and rest\n";

        cout << "===============================\n";
    }
};

// ======================= BILLING CLASS =======================
class Billing {
public:
    void generateBill(string patientID, string patientName, string disease) {
        int doctorFee = 0, medicineCost = 0;
        string d = normalize(disease);

        if (d == "cold" || d == "fever") {doctorFee=300; medicineCost=150;}
        else if (d == "heart pain" || d == "hypertension") {doctorFee=800; medicineCost=400;}
        else if (d == "rash" || d == "acne") {doctorFee=400; medicineCost=200;}
        else if (d == "migraine" || d == "seizure") {doctorFee=600; medicineCost=300;}
        else if (d == "asthma") {doctorFee=700; medicineCost=350;}
        else if (d == "diabetes") {doctorFee=900; medicineCost=500;}
        else if (d == "thyroid") {doctorFee=650; medicineCost=300;}
        else if (d == "fracture" || d == "joint pain") {doctorFee=1000; medicineCost=700;}
        else if (d == "stomach pain" || d == "ulcer") {doctorFee=500; medicineCost=250;}
        else {doctorFee=250; medicineCost=100;}

        int total = doctorFee + medicineCost;
        cout << "\n===== Bill Receipt =====\n";
        cout << "Patient ID   : " << patientID << endl;
        cout << "Patient Name : " << patientName << endl;
        cout << "Disease      : " << disease << endl;
        cout << "Doctor Fee   : ₹" << doctorFee << endl;
        cout << "Medicine Cost: ₹" << medicineCost << endl;
        cout << "--------------------------\n";
        cout << "Total Amount : ₹" << total << endl;
        cout << "==========================\n";
    }
};

// ======================= LOGIN FUNCTION =======================
bool login() {
    string username, password;
    cout << "===== Admin Login =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    if (username.empty() || password.empty()) {
        cout << "⚠️ Username or password cannot be empty.\n";
        return false;
    }
    if (username == "admin" && password == "1234") {
        cout << "✅ Login successful!\n";
        return true;
    } else {
        cout << "❌ Invalid credentials. Exiting...\n";
        return false;
    }
}

// ======================= FILE FUNCTIONS =======================
void savePatientsToFile(const vector<Patient>& patients) {
    ofstream file("patients.txt");
    if (!file) {
        cout << "❌ Error saving data to file.\n";
        return;
    }
    for (const auto& p : patients) {
        file << p.patientID << "," << p.name << "," << p.age << "," << p.gender << ","
             << p.contact << "," << p.disease << "\n";
    }
}

void loadPatientsFromFile(vector<Patient>& patients) {
    ifstream file("patients.txt");
    if (!file) {
        cout << "ℹ️ No saved data found. Starting fresh.\n";
        return;
    }
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
}

// ======================= FILE FUNCTIONS FOR APPOINTMENTS =======================
void saveAppointmentToFile(string patientID, string doctorName, string date, string time) {
    ofstream file("appointments.txt", ios::app);
    if (!file) {
        cout << "❌ Error saving appointment to file.\n";
        return;
    }
    file << patientID << "," << doctorName << "," << date << "," << time << "\n";
    file.close();
    cout << "📁 Appointment saved successfully!\n";
}

void viewAppointmentsFromFile() {
    ifstream file("appointments.txt");
    if (!file) {
        cout << "ℹ️ No appointment data found.\n";
        return;
    }

    string line;
    cout << "\n===== Appointment Records =====\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string patientID, doctorName, date, time;
        getline(ss, patientID, ',');
        getline(ss, doctorName, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        cout << "Patient ID: " << patientID << "\nDoctor: " << doctorName
             << "\nDate: " << date << "\nTime: " << time << "\n------------------------\n";
    }
    file.close();
}

// ======================= FILE FUNCTIONS FOR BILLS =======================
void saveBillToFile(string patientID, string patientName, string disease, int doctorFee, int medicineCost, int total) {
    ofstream file("bills.txt", ios::app);
    if (!file) {
        cout << "❌ Error saving bill to file.\n";
        return;
    }
    file << patientID << "," << patientName << "," << disease << ",₹" << doctorFee
         << ",₹" << medicineCost << ",₹" << total << "\n";
    file.close();
    cout << "📁 Bill saved successfully!\n";
}

void viewBillsFromFile() {
    ifstream file("bills.txt");
    if (!file) {
        cout << "ℹ️ No bill records found.\n";
        return;
    }

    string line;
    cout << "\n===== All Bill Records =====\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string patientID, name, disease, docFee, medCost, total;
        getline(ss, patientID, ',');
        getline(ss, name, ',');
        getline(ss, disease, ',');
        getline(ss, docFee, ',');
        getline(ss, medCost, ',');
        getline(ss, total, ',');
        cout << "Patient ID : " << patientID
             << "\nName       : " << name
             << "\nDisease    : " << disease
             << "\nDoctor Fee : " << docFee
             << "\nMedicine   : " << medCost
             << "\nTotal      : " << total
             << "\n--------------------------\n";
    }
    file.close();
}

int findPatientIndex(const vector<Patient>& patients, const string& id) {
    for (size_t i = 0; i < patients.size(); ++i)
        if (patients[i].patientID == id) return i;
    return -1;
}

string getSpecialtyForDisease(const string& disease) {
    string d = normalize(disease);
    if (d == "cold" || d == "fever") return "General Physician";
    if (d == "heart pain" || d == "hypertension") return "Cardiologist";
    if (d == "rash" || d == "acne") return "Dermatologist";
    if (d == "migraine" || d == "seizure") return "Neurologist";
    if (d == "asthma") return "Pulmonologist";
    if (d == "diabetes" || d == "thyroid") return "Endocrinologist";
    if (d == "fracture" || d == "joint pain") return "Orthopedic";
    if (d == "stomach pain" || d == "ulcer") return "Gastroenterologist";
    return "";
}

// ======================= MAIN FUNCTION =======================
int main() {
    if (!login()) return 0;

    vector<Patient> patients;
    loadPatientsFromFile(patients);

    vector<Doctor> doctors = {
        {"D201", "Dr. Verma", "General Physician", {"10:30 AM", "11:30 AM", "3:00 PM"}},
        {"D202", "Dr. Mehta", "Cardiologist", {"9:00 AM", "1:00 PM"}},
        {"D203", "Dr. Rao", "Dermatologist", {"2:00 PM", "4:00 PM"}},
        {"D204", "Dr. Kapoor", "Neurologist", {"11:00 AM", "5:00 PM"}},
        {"D205", "Dr. Iyer", "Pulmonologist", {"12:00 PM", "6:00 PM"}},
        {"D206", "Dr. Joshi", "Endocrinologist", {"10:00 AM", "3:00 PM"}},
        {"D207", "Dr. Singh", "Orthopedic", {"9:30 AM", "4:00 PM"}},
        {"D208", "Dr. Shah", "Gastroenterologist", {"2:30 PM", "6:30 PM"}}
    };

    Prescription prescription;
    Billing billing;
    int choice;

    do {
        cout << "\n===== E-Healthcare Management System =====\n";
        cout << "1. Register New Patient\n2. View Patient Records\n3. Schedule Appointment\n4. Doctor Details\n5. Prescriptions & Medicines\n6. Generate Bill\n7. Search Patient\n8. Update Patient\n9. Delete Patient\n10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Patient newPatient;
                newPatient.registerPatient();
                if (newPatient.patientID.empty()) break;
                bool exists = any_of(patients.begin(), patients.end(), [&](const Patient& p){return p.patientID == newPatient.patientID;});
                if (exists) {cout << "⚠️ Patient ID already exists.\n"; break;}
                patients.push_back(newPatient);
                savePatientsToFile(patients);
                break;
            }
            case 2:
                if (patients.empty()) cout << "No patients found.\n";
                else for (const auto& p : patients){p.viewPatient(); cout << "------------------------\n";}
                break;
            case 3: {
              string id;
              cout << "Enter Patient ID: ";
              cin >> id;
              int i = findPatientIndex(patients, id);
              if (i == -1) {
              cout << "Patient not found.\n";
              break;
              }

             string spec = getSpecialtyForDisease(patients[i].disease);
             if (spec.empty()) {
             cout << "⚠️ Unknown disease. Consult General Physician.\n";
             break;
             }

            auto it = find_if(doctors.begin(), doctors.end(), [&](Doctor d) { return d.specialty == spec; });
            if (it == doctors.end())
            cout << "No doctor available.\n";
            else {
            Appointment a(*it);
            a.scheduleAppointment();
            saveAppointmentToFile(patients[i].patientID, it->name, a.date, a.appointmentTime);
            }
            break;
        }

            case 4:
                for (const auto& d : doctors){d.showDoctorDetails(); cout<<"------------------------\n";}
                break;
            case 5: {
                string id; cout << "Enter Patient ID: "; cin >> id;
                int i = findPatientIndex(patients, id);
                if (i==-1){cout<<"Patient not found.\n"; break;}
                string spec = getSpecialtyForDisease(patients[i].disease);
                if (spec.empty()){cout<<"⚠️ Unknown disease.\n"; break;}
                auto it = find_if(doctors.begin(), doctors.end(), [&](Doctor d){return d.specialty==spec;});
                if (it!=doctors.end()) prescription.showPrescription(id, it->name, patients[i].disease, patients[i].age);
                else cout<<"No doctor available.\n";
                break;
            }
             case 6: {
               string id;
               cout << "Enter Patient ID: ";
               cin >> id;
               int i = findPatientIndex(patients, id);
               if (i == -1)
                    cout << "Patient not found.\n";
        else {
               string disease = patients[i].disease;
               string name = patients[i].name;
               int doctorFee = 0, medicineCost = 0;
               string d = normalize(disease);

               if (d == "cold" || d == "fever") {doctorFee=300; medicineCost=150;}
               else if (d == "heart pain" || d == "hypertension") {doctorFee=800; medicineCost=400;}
               else if (d == "rash" || d == "acne") {doctorFee=400; medicineCost=200;}
               else if (d == "migraine" || d == "seizure") {doctorFee=600; medicineCost=300;}
               else if (d == "asthma") {doctorFee=700; medicineCost=350;}
               else if (d == "diabetes") {doctorFee=900; medicineCost=500;}
               else if (d == "thyroid") {doctorFee=650; medicineCost=300;}
               else if (d == "fracture" || d == "joint pain") {doctorFee=1000; medicineCost=700;}
               else if (d == "stomach pain" || d == "ulcer") {doctorFee=500; medicineCost=250;}
               else {doctorFee=250; medicineCost=100;}

              int total = doctorFee + medicineCost;
              billing.generateBill(id, name, disease);
              saveBillToFile(id, name, disease, doctorFee, medicineCost, total);
            }
             break;
        }

            case 7: {
                string id; cout<<"Enter Patient ID: "; cin>>id;
                int i = findPatientIndex(patients, id);
                if (i==-1) cout<<"Patient not found.\n";
                else patients[i].viewPatient();
                break;
            }
            case 8: {
                string id; cout<<"Enter Patient ID to update: "; cin>>id;
                int i = findPatientIndex(patients, id);
                if (i==-1){cout<<"Patient not found.\n"; break;}
                cout<<"--- Current Details ---\n"; patients[i].viewPatient();
                cout<<"--- Enter Updated Details ---\n";
                Patient u; u.patientID=id;
                cout<<"Enter Name: "; cin.ignore(); getline(cin,u.name);
                cout<<"Enter Age: "; cin>>u.age;
                cout<<"Enter Gender: "; cin>>u.gender;
                cout<<"Enter Contact: "; cin>>u.contact;
                cout<<"Enter Disease: "; cin.ignore(); getline(cin,u.disease);
                if(u.age<=0||u.age>120){cout<<"⚠️ Invalid age.\n"; break;}
                patients[i]=u; savePatientsToFile(patients);
                cout<<"✅ Updated successfully!\n";
                break;
            }
            case 9: {
                string id; cout<<"Enter Patient ID to delete: "; cin>>id;
                int i = findPatientIndex(patients,id);
                if (i==-1){cout<<"Patient not found.\n"; break;}
                char confirm; cout<<"Are you sure to delete? (y/n): "; cin>>confirm;
                if(confirm=='y'||confirm=='Y'){patients.erase(patients.begin()+i); savePatientsToFile(patients); cout<<"Deleted successfully.\n";}
                else cout<<"Deletion cancelled.\n";
                break;
            }
            case 10:
                cout<<"Exiting System...\n"; break;
            default:
                cout<<"Invalid choice.\n"; break;
        }
    } while(choice!=10);

    return 0;
}
