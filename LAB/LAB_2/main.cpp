#include <iostream>
#include <string>

using namespace std;

struct Node{
    string songTitle;
    Node* next;
};

Node* head = nullptr;

void addingSong(string newSong){
    Node* newNode = new Node();
    newNode->songTitle = newSong;
    
    newNode->next = head;

    head = newNode;

    cout << "\"" << newSong << "\" added to the top of the playlist.\n";

}

void searchSong(string title){
    Node* temp = head;
    bool found = false;

    while (temp != nullptr) {
        if (temp->songTitle == title) {
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (found) {
        cout << "Song \"" << title << "\" was found in the playlist!\n";
    } else {
        cout << "Song \"" << title << "\" not found.\n";
    }
}

void listSongs() {
    if (head == nullptr) {
        cout << "The playlist is empty.\n";
        return;
    }

    Node* temp = head;
    int count = 1;
    cout << "\n--- Current Playlist ---\n";
    while (temp != nullptr) {
        cout << count << ". " << temp->songTitle << endl;
        temp = temp->next;
        count++;
    }
    cout << "------------------------\n";
}

int main(){
    int input;
    string songName;
    do
    {
        cout << "\nMenu" << endl;
        cout << "1. Add" << endl;
        cout << "2. Search" << endl;
        cout << "3. List" << endl;
        cout << "4. Exit" << endl;
        cout << "Choise: ";
        cin >> input;

        cin.ignore();

        if (input == 1){
            cout << "Enter Song Name: ";
            getline(cin, songName);
            addingSong(songName);
        }

        else if (input == 2){
            cout << "Enter a Song Name For Search: ";
            getline(cin, songName);
            searchSong(songName);
        }
        
        else if (input == 3){
            listSongs();
        }
        else if (input == 4) {
            cout << "Exiting program. Goodbye!" << endl;
        }
        else {
            cout << "Invalid Number, Please Try Again!" << endl;
        }
        
    } while (input != 4);

    return 0;
    
}