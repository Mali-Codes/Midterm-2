#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    int size() {
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
    
    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

}
    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    string get_front() {
        if (head) return head->data;        
        return "";
    };

    string get_back() {
        if (tail) return tail->data;       
        return "";
    };
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS << "\n";  // dummy statement to avoid compiler warning

    srand(time(0));   // for randomization, was already random in choices but not per execution 
    // will now produce different results each execution

    vector<string> names;
    ifstream nameFile("names.txt");
    string name;
    
    while (nameFile >> name) {
        names.push_back(name);
    }
    nameFile.close(); // gotta close the file after reading

    cout << "Names loaded: " << names.size() << endl; //successful loading check 
    

    DoublyLinkedList line;  //list is initialized here


    // for (int run = 0; run < 20; ++run) {    //fill the list 
    //     int randomIndex = rand() % names.size();
    //     string customersName = names[randomIndex];
    //     line.push_back(customersName);    
    //     };

    // cout << "just a full list to check" << endl;
    // line.print();  //print full list to check
    // cout << "Front of the list: " << line.get_front() << endl; //test front
    // cout << "Back of the list: " << line.get_back() << endl;
    
    
    // first 5 inserts
    cout << "Welcome in :)" << endl;
    for (int i = 0; i < 5; ++i) {
        int randomIndex = rand() % names.size();
        string customersName = names[randomIndex];
        line.push_back(customersName);
        cout << customersName << " has entered the line." << endl;
    };

    // now we have a base list we can run the 20 runs

    for (int minute = 1; minute <=20; minute++) {
        cout << "Minute " << minute << ":" << endl;
        
        // ENTERING BACK
        int prob = rand() % 100 + 1;
        if (prob <= 60) {
            int randomIndex = rand() % names.size(); // this gets the random name
            string customersName = names[randomIndex]; //this assigns it to a string - will be using these two repeatedly like in the 20 names test
            line.push_back(customersName);
            cout << customersName << " has enterd the line." << endl;
        };

        // VIP FRONT
        prob = rand() % 100 + 1;
        if (prob <= 10) {
            
            int randomIndex = rand() % names.size(); 
            string VIP = names[randomIndex]; 
            line.push_front(VIP);
            cout << VIP << " has VIP." << endl;
        

        };

        // LEAVING BACK
        prob = rand() % 100 + 1; // we do every if statement for a new random chance
        if (prob <= 20) {
            string leaving = line.get_back();
            line.pop_back();
            cout << leaving << " has left the line from the back." << endl;
        };

        // SERVING FRONT
        prob = rand() % 100 + 1;
        if (prob <= 40) {
            string served = line.get_front();
            if (served != "") {
                cout << served << " is served" << endl;
                line.pop_front();
            }
        }

        prob = rand() % 100 + 1;
        if (prob <=10) {
            int lineSize = line.size(); //whole line

        // delete random in whole line
            if (lineSize > 0) {
                int somePos = rand() % lineSize;
                string leaving = line.get_at(somePos)
            }
        };



    };

    cout << "Resulting line:" << endl;
        cout << "  ";
        line.print();
        cout << endl;








    // for looop for all 20 runs

    // gotta have a list and its gonna be strings so mod list build FIRST*****

    // going to be calling a bunch of different methods in the for loop

    // gonna use randoms to see what methods are done and what arent
        //giving each a chance to run or not run

    //gotta have methods for getting front back and to display size of list
    
    return 0;
}