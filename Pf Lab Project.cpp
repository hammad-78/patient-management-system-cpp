#include <iostream>
#include<windows.h>
#include<sstream>
using namespace std;

// --- 1. STRUCT DATATYPE ---
struct Patient {
    int patientID;       // Unique ID
    string name;       // C-style string (array of characters)
    int age;
    int severity;        // 1-10
    float priorityScore; 
};

// --- GLOBAL CONSTANT ---
const int MAX = 50;

// --- GLOBAL ID COUNTER ---
int nextID = 1;   // Auto-incrementing patient ID

// --- 2. FUNCTIONS ---

// Manual buffer clearer to prevent input bugs
void clearBuffer() {
    while (cin.get() != '\n'); 
}

void searchPatient(Patient queue[], int count){
	system("cls");
	int id;
	bool found=false;
	cout<<"Enter Id of patient to search: ";
	cin>>id;
	for(int i=0;i<count;i++){
		if(queue[i].patientID==id){
			cout<<queue[i].name;
			found = true;
		}
	}
	if(found == false)
		{
			cout<<"ID not found";
		}
		Sleep(3000);
}


void sortTriage(Patient queue[], int count) {
    // Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (queue[j].priorityScore < queue[j + 1].priorityScore) {
                Patient temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }
}

void addPatient(Patient queue[], int &count) {
	system("cls");
    if (count >= MAX) {
        cout << "\nER is full!\n";
        return;
    }

    Patient p;
    cout << "\n--- New Registration ---\n";

    // Assign unique ID
    p.patientID = nextID++;
    
    cout << "Enter Patient Name: ";
    cin.ignore(); 
    getline(cin, p.name);

    // Validate Age
    cout << "Enter Age: ";
    while (true) {
        cin >> p.age;
        if (cin.fail() || p.age < 0 || p.age > 120) {
            cout << "Invalid Age! Enter again (0-120): ";
            cin.clear();
            clearBuffer();
        } else {
            break;
        }
    }

    // Validate Severity
    cout << "Enter Severity (1-10): ";
    while (true) {
        cin >> p.severity;
        if (cin.fail() || p.severity < 1 || p.severity > 10) {
            cout << "Invalid Severity! Enter again (1-10): ";
            cin.clear();
            clearBuffer();
        } else {
            break;
        }
    }

    // Priority Score Calculation
    p.priorityScore = (p.severity * 10.0f) + (p.age * 0.2f);

    queue[count] = p;
    count++;

    sortTriage(queue, count);
    cout << "Patient Triaged Successfully. Assigned ID: " << p.patientID << "\n";
    
    Sleep(3000);
}

void treatPatient(Patient queue[], int &count) {
	system("cls");
    if (count == 0) {
        cout << "\nNo patients waiting.\n";
        return;
    }

    cout << "\n>>> NOW TREATING: [ID " << queue[0].patientID 
         << "] " << queue[0].name << "\n";
    
    for (int i = 0; i < count - 1; i++) {
        queue[i] = queue[i + 1];
    }
    count--;
    Sleep(3000);
}

void displayQueue(Patient queue[], int count) {
    if (count == 0) {
        cout << "\nQueue is empty.\n";
        return;
    }

    cout << "\nPos\tID\tName\t\tAge\tSev\tScore\n";
    cout << "---------------------------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << (i + 1) << "\t" 
             << queue[i].patientID << "\t" 
             << queue[i].name << "\t\t" 
             << queue[i].age << "\t" 
             << queue[i].severity << "\t" 
             << queue[i].priorityScore << endl;
    }
    Sleep(3000);
}
void showStatistics(Patient queue[], int count) {
    if (count == 0) {
        cout << "\nNo data available.\n";
        return;
    }

    int critical = 0, urgent = 0, minor = 0;

    for (int i = 0; i < count; i++) {
        if (queue[i].severity >= 8) critical++;
        else if (queue[i].severity >= 4) urgent++;
        else minor++;
    }

    float occupancy = (count / (float)MAX) * 100;

    cout << "\n--- HOSPITAL DASHBOARD ---";
    cout << "\nTotal Patients: " << count;
    cout << "\nCritical Cases: " << critical;
    cout << "\nUrgent Cases:   " << urgent;
    cout << "\nMinor Cases:    " << minor;
    cout << "\nOccupancy:      " << occupancy << "%";
    cout << "\n--------------------------\n";
    
    Sleep(3000);
}
int main() {
    Patient waitingRoom[MAX];
    int currentCount = 0;
    int choice;

    // MAIN MENU LOOP
    while (true) {
    	system("cls");
        cout << "\n--- HOSPITAL TRIAGE SYSTEM ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Treat Next\n";
        cout << "3. View Queue\n";
        cout << "4. Show Statistics\n";
        cout << "5. Search Patient\n";
        cout << "6. Exit\n";

        cout << "Choice: ";

        // Validate Menu Choice
        while (true) {
            cin >> choice;
            if (cin.fail() || choice < 1 || choice > 6) {
                cout << "Invalid choice! Enter again (1-5): ";
                cin.clear();
                clearBuffer();
            } else {
                break;
            }
        }

        if (choice == 1) {
            addPatient(waitingRoom, currentCount);
        } else if (choice == 2) {
            treatPatient(waitingRoom, currentCount);
        } else if (choice == 3) {
            displayQueue(waitingRoom, currentCount);
        } else if (choice == 4) {
			showStatistics(waitingRoom, currentCount);
        }
        else if(choice == 5){
        	searchPatient(waitingRoom, currentCount);
		}
		else{
			break;
		}
    }
    Sleep(3000);

    return 0;
}
