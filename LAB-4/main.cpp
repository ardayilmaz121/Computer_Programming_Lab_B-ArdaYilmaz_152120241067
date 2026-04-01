#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer {
    string customerName;
    string transactionType;
};

MoneyBundle* top = nullptr;

const int MAX_CUSTOMERS = 5;
Customer queue[MAX_CUSTOMERS];
int front = -1; 
int rear = -1;
int currentCount = 0;

void receiveMoney(string serial, string currency, int c100, int c50, int c20) {
    MoneyBundle* newBundle = new MoneyBundle;
    newBundle->serialNumber = serial;
    newBundle->currencyType = currency;
    newBundle->billCounts[0] = c100;
    newBundle->billCounts[1] = c50;
    newBundle->billCounts[2] = c20;
    newBundle->next = top;
    top = newBundle;
    cout << "Money received: " << currency << " bundle added to safe." << endl;
}

void newCustomer(string name, string type) {
    if (currentCount == MAX_CUSTOMERS) {
        cout << "Queue is full." << endl;
        return;
    }
    rear = (rear + 1) % MAX_CUSTOMERS;
    queue[rear].customerName = name;
    queue[rear].transactionType = type;
    currentCount++;
    cout << "Customer joined in line! "<<  name <<  endl;
}

void processTransaction() {
    if (currentCount == 0) {
        cout << "No customer in line!" << endl;
        return;
    }
    if (top == nullptr) {
        cout << "Safe is empty! Cannot serve " << queue[front].customerName << endl;
        return;
    }
    
    cout << "Serving: " << queue[front].customerName << "(" << queue[front].transactionType << ")" << endl;
    front = (front + 1) % MAX_CUSTOMERS;
    currentCount--;

    MoneyBundle* bundleToUse = top;
    top = top->next;
    cout << "Given bundle: " << bundleToUse->serialNumber << " (" << bundleToUse->currencyType << ")" << endl;
    delete bundleToUse;
}

int main() {
    receiveMoney("SN123", "USD", 10, 5, 2);
    receiveMoney("SN124", "EUR", 5, 10, 5);

    newCustomer("Ahmet", "Withdraw");
    newCustomer("Mehmet", "Withdraw");

    cout << "Processing transactions..." << endl;
    processTransaction();
    processTransaction();
    processTransaction();

    return 0;
}