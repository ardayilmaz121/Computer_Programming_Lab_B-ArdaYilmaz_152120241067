#include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page *next, *prev;
};

Page *head = nullptr;
Page *tail = nullptr;
Page *current = nullptr;

void visit(string url, string title, int h, int m, int s) {
    Page* newPage = new Page{url, title, {h, m, s}, nullptr, nullptr};
    if (!head) {
        head = tail = current = newPage;
    } else {
        tail->next = newPage;
        newPage->prev = tail;
        tail = newPage;
        current = newPage;
    }
}

void back() {
    if (current && current->prev) {
        current = current->prev;
    }
}


void forward() {
    if (current && current->next) {
        current = current->next;
    }
}

void deleteEntry() {
    if (!current) return;
    if (current == head && current == tail) {
        delete current;
        head = tail = current = nullptr;
        return;
    }
    if (current == head) {
        head = head->next;
        head->prev = nullptr;
        delete current;
        current = head;
        return;
    }
    if (current == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        delete current;
        current = tail;
        return;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    Page* temp = current;
    current = current->next ? current->next : current->prev;
    delete temp;
}

void display() {
    Page* temp = head;
    while (temp) {
        if (temp == current) cout << ">>> ";
        else cout << "    ";

        cout << temp->title << " (" << temp->url << ") - Time: ";
        for (int i = 0; i < 3; i++) {
            if (temp->accessTime[i] < 10) cout << "0";
            cout << temp->accessTime[i];
            if (i < 2) cout << ":";
        }
        cout << endl;
        
        temp = temp->next;
    }
    cout << "-----------------------------------" << endl;
}

void cleanup() {
    Page* temp = head;
    while (temp) {
        Page* next = temp->next;
        delete temp;
        temp = next;
    }
    head = tail = current = nullptr;
}

int main() {
    string command;
    while (cin >> command) {
        if (command == "VISIT") {
            string url, title;
            int h, m, s;
            cin >> url >> title >> h >> m >> s;
            visit(url, title, h, m, s);
        } else if (command == "BACK") {
            back();
        } else if (command == "FORWARD") {
            forward();
        } else if (command == "DELETE") {
            deleteEntry();
        } else if (command == "DISPLAY") {
            display();
        } else if (command == "EXIT") {
            cleanup();
            break;
        }
    }
    return 0;
}

