#include "crow_all.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// ================== DATA STRUCTURES ==================
struct Patient {
    string id, name, age, gender, disease;
};

struct Appointment {
    string patientID, doctorName, date, time;
};

struct Bill {
    string patientID, name, disease, doctorFee, medCost, total;
};

// ================== READ PATIENTS ==================
vector<Patient> readPatients() {
    vector<Patient> data;
    ifstream file("patients.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Patient p;
        getline(ss, p.id, ',');
        getline(ss, p.name, ',');
        getline(ss, p.age, ',');
        getline(ss, p.gender, ',');
        getline(ss, p.disease, ',');
        if (!p.id.empty())
            data.push_back(p);
    }
    return data;
}

// ================== READ APPOINTMENTS ==================
vector<Appointment> readAppointments() {
    vector<Appointment> data;
    ifstream file("appointments.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Appointment a;
        getline(ss, a.patientID, ',');
        getline(ss, a.doctorName, ',');
        getline(ss, a.date, ',');
        getline(ss, a.time, ',');
        if (!a.patientID.empty())
            data.push_back(a);
    }
    return data;
}

// ================== READ BILLS ==================
vector<Bill> readBills() {
    vector<Bill> data;
    ifstream file("bills.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Bill b;
        getline(ss, b.patientID, ',');
        getline(ss, b.name, ',');
        getline(ss, b.disease, ',');
        getline(ss, b.doctorFee, ',');
        getline(ss, b.medCost, ',');
        getline(ss, b.total, ',');
        if (!b.patientID.empty())
            data.push_back(b);
    }
    return data;
}
void addPatient(const Patient& p) {
    ofstream file("patients.txt", ios::app);
    file << p.id << "," << p.name << "," << p.age << "," << p.gender << "," << p.disease << "\n";
    file.close();
}

void addAppointment(const Appointment& a) {
    ofstream file("appointments.txt", ios::app);
    file << a.patientID << "," << a.doctorName << "," << a.date << "," << a.time << "\n";
    file.close();
}

void addBill(const Bill& b) {
    ofstream file("bills.txt", ios::app);
    file << b.patientID << "," << b.name << "," << b.disease << "," << b.doctorFee << "," << b.medCost << "," << b.total << "\n";
    file.close();
}


// ================== MAIN SERVER ==================
int main() {
    crow::SimpleApp app;

    // Root
    CROW_ROUTE(app, "/")([]() {
        return "✅ E-Healthcare Backend is running!";
    });

    // ================== PATIENTS ==================
    CROW_ROUTE(app, "/patients")
    ([]() {
        auto patients = readPatients();
        crow::json::wvalue x;
        for (size_t i = 0; i < patients.size(); i++) {
            x["patients"][i]["PatientID"] = patients[i].id;
            x["patients"][i]["Name"] = patients[i].name;
            x["patients"][i]["Age"] = patients[i].age;
            x["patients"][i]["Gender"] = patients[i].gender;
            x["patients"][i]["Disease"] = patients[i].disease;
        }
        return x;
    });

    // ================== APPOINTMENTS ==================
    CROW_ROUTE(app, "/appointments")
    ([]() {
        auto appointments = readAppointments();
        crow::json::wvalue x;
        for (size_t i = 0; i < appointments.size(); i++) {
            x["appointments"][i]["PatientID"] = appointments[i].patientID;
            x["appointments"][i]["Doctor"] = appointments[i].doctorName;
            x["appointments"][i]["Date"] = appointments[i].date;
            x["appointments"][i]["Time"] = appointments[i].time;
        }
        return x;
    });

    // ================== BILLING ==================
    CROW_ROUTE(app, "/bills")
    ([]() {
        auto bills = readBills();
        crow::json::wvalue x;
        for (size_t i = 0; i < bills.size(); i++) {
            x["bills"][i]["PatientID"] = bills[i].patientID;
            x["bills"][i]["Name"] = bills[i].name;
            x["bills"][i]["Disease"] = bills[i].disease;
            x["bills"][i]["DoctorFee"] = bills[i].doctorFee;
            x["bills"][i]["MedicineCost"] = bills[i].medCost;
            x["bills"][i]["Total"] = bills[i].total;
        }
        return x;
    });
CROW_ROUTE(app, "/addPatient").methods("POST"_method)
([](const crow::request& req){
    auto data = crow::json::load(req.body);
    if(!data) return crow::response(400);

    Patient p;
    p.id = data["PatientID"].s();
    p.name = data["Name"].s();
    p.age = data["Age"].s();
    p.gender = data["Gender"].s();
    p.disease = data["Disease"].s();
    addPatient(p);

    return crow::response(200, "Patient Saved Successfully");
});

CROW_ROUTE(app, "/addAppointment").methods("POST"_method)
([](const crow::request& req){
    auto data = crow::json::load(req.body);
    if(!data) return crow::response(400);

    Appointment a;
    a.patientID = data["PatientID"].s();
    a.doctorName = data["DoctorName"].s();
    a.date = data["Date"].s();
    a.time = data["Time"].s();
    addAppointment(a);

    return crow::response(200, "Appointment Saved Successfully");
});

CROW_ROUTE(app, "/addBill").methods("POST"_method)
([](const crow::request& req){
    auto data = crow::json::load(req.body);
    if(!data) return crow::response(400);

    Bill b;
    b.patientID = data["PatientID"].s();
    b.name = data["Name"].s();
    b.disease = data["Disease"].s();
    b.doctorFee = data["DoctorFee"].s();
    b.medCost = data["MedicineCost"].s();
    b.total = data["Total"].s();
    addBill(b);

    return crow::response(200, "Bill Saved Successfully");
});

    app.port(5000).multithreaded().run();
}
