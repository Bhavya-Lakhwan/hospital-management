/*
 * ============================================================
 *  HOSPITAL MANAGEMENT SYSTEM
 *  Level   : Intermediate
 *  Modules : Structures, File Handling
 *
 *  Year-1  : Works perfectly as-is
 * ============================================================
 */

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Flush leftover '\n' from input buffer ──────────────────── */
void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ── Constants ─────────────────────────────────────────────── */
#define MAX_PATIENTS     100
#define MAX_DOCTORS      20
#define MAX_APPOINTMENTS 200
#define STR_LEN          50
#define PATIENTS_FILE    "patients.dat"
#define DOCTORS_FILE     "doctors.dat"
#define APPT_FILE        "appointments.dat"

/* ── Structures ─────────────────────────────────────────────── */
typedef struct {
    int  id;
    char name[STR_LEN];
    int  age;
    char gender;
    char disease[STR_LEN];
    char phone[15];
} Patient;

typedef struct {
    int  id;
    char name[STR_LEN];
    char specialization[STR_LEN];
    char phone[15];
} Doctor;

typedef struct {
    int  appt_id;
    int  patient_id;
    int  doctor_id;
    char date[15];
    char time[10];
    char status[15];
} Appointment;

/* ── Globals ────────────────────────────────────────────────── */
Patient     patients[MAX_PATIENTS];
Doctor      doctors[MAX_DOCTORS];
Appointment appointments[MAX_APPOINTMENTS];
int pcount = 0, dcount = 0, acount = 0;

/* ── File I/O ───────────────────────────────────────────────── */
void save_all() {
    FILE *fp;
    fp = fopen(PATIENTS_FILE, "wb");
    fwrite(&pcount,  sizeof(int),     1,      fp); fwrite(patients, sizeof(Patient), pcount, fp); fclose(fp);
    fp = fopen(DOCTORS_FILE,  "wb");
    fwrite(&dcount,  sizeof(int),     1,      fp); fwrite(doctors,  sizeof(Doctor),  dcount, fp); fclose(fp);
    fp = fopen(APPT_FILE,     "wb");
    fwrite(&acount,  sizeof(int),     1,      fp); fwrite(appointments, sizeof(Appointment), acount, fp); fclose(fp);
    printf("All data saved successfully.\n");
}

void load_all() {
    FILE *fp;
    fp = fopen(PATIENTS_FILE, "rb");
    if (fp) { fread(&pcount, sizeof(int), 1, fp); fread(patients,      sizeof(Patient),     pcount, fp); fclose(fp); }
    fp = fopen(DOCTORS_FILE,  "rb");
    if (fp) { fread(&dcount, sizeof(int), 1, fp); fread(doctors,       sizeof(Doctor),      dcount, fp); fclose(fp); }
    fp = fopen(APPT_FILE,     "rb");
    if (fp) { fread(&acount, sizeof(int), 1, fp); fread(appointments,  sizeof(Appointment), acount, fp); fclose(fp); }
    printf("Loaded: %d patient(s), %d doctor(s), %d appointment(s).\n", pcount, dcount, acount);
}

/* ════════════════════════════════════════════════════════════
 *  PATIENT MODULE
 * ════════════════════════════════════════════════════════════ */
void add_patient() {
    if (pcount >= MAX_PATIENTS) { printf("Patient list full!\n"); return; }
    Patient p;
    printf("\n--- Register New Patient ---\n");
    printf("Patient ID   : "); scanf("%d", &p.id); flush_input();
    printf("Name         : "); fgets(p.name, STR_LEN, stdin); p.name[strcspn(p.name,"\n")] = 0;
    printf("Age          : "); scanf("%d", &p.age); flush_input();
    printf("Gender (M/F) : "); scanf("%c", &p.gender); flush_input();
    printf("Disease      : "); fgets(p.disease, STR_LEN, stdin); p.disease[strcspn(p.disease,"\n")] = 0;
    printf("Phone        : "); fgets(p.phone, sizeof(p.phone), stdin); p.phone[strcspn(p.phone,"\n")] = 0;
    patients[pcount++] = p;
    printf("Patient registered successfully!\n");
}

void display_patients() {
    if (pcount == 0) { printf("No patients registered.\n"); return; }
    printf("\n%-5s %-20s %-4s %-2s %-20s %-12s\n", "ID","Name","Age","G","Disease","Phone");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < pcount; i++)
        printf("%-5d %-20s %-4d %-2c %-20s %-12s\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].gender, patients[i].disease, patients[i].phone);
}

void search_patient() {
    int id; printf("Enter Patient ID: "); scanf("%d", &id); flush_input();
    for (int i = 0; i < pcount; i++) {
        if (patients[i].id == id) {
            Patient *p = &patients[i];
            printf("\nID: %d | Name: %s | Age: %d | Gender: %c\nDisease: %s | Phone: %s\n",
                   p->id, p->name, p->age, p->gender, p->disease, p->phone);
            return;
        }
    }
    printf("Patient %d not found.\n", id);
}

void delete_patient() {
    int id; printf("Enter Patient ID to delete: "); scanf("%d", &id); flush_input();
    for (int i = 0; i < pcount; i++) {
        if (patients[i].id == id) {
            for (int j = i; j < pcount - 1; j++) patients[j] = patients[j+1];
            pcount--; printf("Patient deleted.\n"); return;
        }
    }
    printf("Patient %d not found.\n", id);
}

/* ════════════════════════════════════════════════════════════
 *  DOCTOR MODULE
 * ════════════════════════════════════════════════════════════ */
void add_doctor() {
    if (dcount >= MAX_DOCTORS) { printf("Doctor list full!\n"); return; }
    Doctor d;
    printf("\n--- Add New Doctor ---\n");
    printf("Doctor ID       : "); scanf("%d", &d.id); flush_input();
    printf("Name            : "); fgets(d.name, STR_LEN, stdin); d.name[strcspn(d.name,"\n")] = 0;
    printf("Specialization  : "); fgets(d.specialization, STR_LEN, stdin); d.specialization[strcspn(d.specialization,"\n")] = 0;
    printf("Phone           : "); fgets(d.phone, sizeof(d.phone), stdin); d.phone[strcspn(d.phone,"\n")] = 0;
    doctors[dcount++] = d;
    printf("Doctor added successfully!\n");
}

void display_doctors() {
    if (dcount == 0) { printf("No doctors on record.\n"); return; }
    printf("\n%-5s %-20s %-25s %-12s\n", "ID","Name","Specialization","Phone");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < dcount; i++)
        printf("%-5d %-20s %-25s %-12s\n",
               doctors[i].id, doctors[i].name,
               doctors[i].specialization, doctors[i].phone);
}

/* ════════════════════════════════════════════════════════════
 *  APPOINTMENT MODULE
 * ════════════════════════════════════════════════════════════ */
void book_appointment() {
    if (acount >= MAX_APPOINTMENTS) { printf("Appointment list full!\n"); return; }
    Appointment a;
    printf("\n--- Book Appointment ---\n");
    printf("Appointment ID    : "); scanf("%d", &a.appt_id);    flush_input();
    printf("Patient ID        : "); scanf("%d", &a.patient_id); flush_input();
    printf("Doctor ID         : "); scanf("%d", &a.doctor_id);  flush_input();
    printf("Date (DD-MM-YYYY) : "); fgets(a.date, sizeof(a.date), stdin); a.date[strcspn(a.date,"\n")] = 0;
    printf("Time (HH:MM AM/PM): "); fgets(a.time, sizeof(a.time), stdin); a.time[strcspn(a.time,"\n")] = 0;
    strcpy(a.status, "Scheduled");
    appointments[acount++] = a;
    printf("Appointment booked successfully!\n");
}

void display_appointments() {
    if (acount == 0) { printf("No appointments found.\n"); return; }
    printf("\n%-6s %-10s %-9s %-12s %-10s %-12s\n",
           "ApID","PatientID","DoctorID","Date","Time","Status");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < acount; i++)
        printf("%-6d %-10d %-9d %-12s %-10s %-12s\n",
               appointments[i].appt_id, appointments[i].patient_id,
               appointments[i].doctor_id, appointments[i].date,
               appointments[i].time, appointments[i].status);
}

void update_appointment_status() {
    int id; printf("Enter Appointment ID: "); scanf("%d", &id); flush_input();
    for (int i = 0; i < acount; i++) {
        if (appointments[i].appt_id == id) {
            printf("New status (Completed / Cancelled / Scheduled): ");
            fgets(appointments[i].status, sizeof(appointments[i].status), stdin);
            appointments[i].status[strcspn(appointments[i].status,"\n")] = 0;
            printf("Status updated.\n"); return;
        }
    }
    printf("Appointment %d not found.\n", id);
}

/* ── Sub-menus ──────────────────────────────────────────────── */
void patient_menu() {
    int ch;
    do {
        printf("\n--- Patient Menu ---\n1. Register\n2. Display All\n3. Search\n4. Delete\n5. Back\n");
        printf("Choice: ");
        if (scanf("%d", &ch) != 1) { ch = 0; } flush_input();
        switch (ch) {
            case 1: add_patient();      break;
            case 2: display_patients(); break;
            case 3: search_patient();   break;
            case 4: delete_patient();   break;
        }
    } while (ch != 5);
}

void doctor_menu() {
    int ch;
    do {
        printf("\n--- Doctor Menu ---\n1. Add Doctor\n2. Display All\n3. Back\n");
        printf("Choice: ");
        if (scanf("%d", &ch) != 1) { ch = 0; } flush_input();
        switch (ch) {
            case 1: add_doctor();      break;
            case 2: display_doctors(); break;
        }
    } while (ch != 3);
}

void appointment_menu() {
    int ch;
    do {
        printf("\n--- Appointment Menu ---\n1. Book\n2. Display All\n3. Update Status\n4. Back\n");
        printf("Choice: ");
        if (scanf("%d", &ch) != 1) { ch = 0; } flush_input();
        switch (ch) {
            case 1: book_appointment();          break;
            case 2: display_appointments();      break;
            case 3: update_appointment_status(); break;
        }
    } while (ch != 4);
}

/* ── Main ───────────────────────────────────────────────────── */
int main() {
    load_all();
    int choice;
    do {
        printf("\n======= Hospital Management System =======\n");
        printf("1. Patient Management\n2. Doctor Management\n");
        printf("3. Appointment Management\n4. Save & Exit\n");
        printf("==========================================\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) { choice = 0; } flush_input();
        switch (choice) {
            case 1: patient_menu();     break;
            case 2: doctor_menu();      break;
            case 3: appointment_menu(); break;
            case 4: save_all(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
    return 0;
}