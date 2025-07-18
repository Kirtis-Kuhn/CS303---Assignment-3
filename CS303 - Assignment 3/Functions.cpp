#include "Functions.h"

//Q1
//==================================================================================================================================

// Explicit instantiations
template void readFile<int>(ifstream& dataFile, Queue<int>& q);

// Helper function to check if a string is an Integer
bool isInteger(const string& str) {
    if (str.empty()) return false;
    return str.find_first_not_of("0123456789") == string::npos;
}

void mainMenu(Queue<int>& intQueue, Queue<string>& strQueue, Queue<float>& floQueue) {
    // Format
    string title = "Main Menu";
    int titleFormat = (102 - title.length()) / 2;

    // Options
    vector<string> options = {
        "String",
        "Integer",
        "Float",
        "Exit"
    };

    // Choice
    string choiceOG;
    int choice = 0;

    while (choice != options.size()) {
        // Display Title
        cout << "\n\n" << string(titleFormat, ' ') << title << endl;
        cout << '!' << string(100, '-') << '!' << endl;

        // Display Options
        for (int i = 0; i < options.size(); ++i) {
            cout << setw(3) << i + 1 << ") " << options[i];
            if (i != options.size() - 1) { cout << " Queue"; } //Queue suffix
            cout << endl;
        }
        cout << '!' << string(100, '-') << '!' << endl;

        // Input
        cout << "Enter your choice: ";
        cin >> choiceOG;

        try {
            //Choice validation
			if (!isInteger(choiceOG)) throw invalid_argument("Input is not a number - " + choiceOG); 

            choice = stoi(choiceOG);
            if (choice < 1 || choice > options.size())
                throw out_of_range("Choice out of range - " + choiceOG);

            // Process Choice
            switch (choice) {
            case 1:
                cout << "String Queue selected..." << endl;
                menu(strQueue, options[0]);
                break;
            case 2:
                cout << "Integer Queue selected..." << endl;
                menu(intQueue, options[1]);
                break;
            case 3:
                cout << "Float Queue selected..." << endl;
                menu(floQueue, options[2]);
                break;
            case 4:
                cout << "Exiting program..." << endl;
                return;
            default:
                throw out_of_range("Invalid choice - " + choiceOG);
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n\n";
            continue;
        }
    }
}


template <typename T>
void menu(Queue<T>& q, string& menuTitle) {
    // Format
    string title = "Queue Menu: " + menuTitle;
    int titleFormat = (102 - title.length()) / 2;

    // Options
    vector<string> options = {
        "Display Queue",
        "Check Empty",
        "Check Size",
        "Front Element",
        "Push Element",
        "Pop Element",
        "Move Front to Rear",
		"Search for Last",
         "Sort Queue (Insertion Sort)",
        "Exit"
    };

    // Choice
    string choiceOG;
    int choice = 0;

    while (choice != options.size()) {
        // Display Title
        cout << "\n\n" << string(titleFormat, ' ') << title << endl;
        cout << '!' << string(100, '-') << '!' << endl;

        // Display Options
        for (int i = 0; i < options.size(); ++i) {
            cout << setw(3) << i + 1 << ") " << options[i] << endl;
        }
        cout << '!' << string(100, '-') << '!' << endl;

        // Input
        cout << "Enter your choice: ";
        cin >> choiceOG;

        try {
            if (!isInteger(choiceOG)) throw invalid_argument("Input is not a number - " + choiceOG);

            choice = stoi(choiceOG);
            if (choice < 1 || choice > options.size())
                throw out_of_range("Choice out of range - " + choiceOG);

            // Process Choice
            switch (choice) {
            case 1:
                cout << "Queue contents: ";
                if(q.empty()) { cout << "Queue is empty." << endl; } 

                else { q.display();	}
                
                break;
            case 2:
                cout << (q.empty() ? "Queue is empty." : "Queue is not empty.") << endl;
                break;
            case 3:
                cout << "Queue size: " << q.size() << endl;
                break;
            case 4:
                try {
                    cout << "Front element: " << q.front() << endl;
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 5: {
                T val;
                cout << "Enter element to push: ";
                cin >> val;
                q.push(val);
                cout << "Pushed " << val << " to queue.\n";
                break;
            }
            case 6:
                q.pop();
                cout << "Front element removed.\n";
                break;
            case 7:
                q.move_to_rear();
                cout << "Moved front element to rear.\n";
                break;
            case 8: {
                if (q.empty()) {
                    cout << "Queue is empty, cannot search." << endl;
                    break;
                }

                // Display current queue
                cout << "Current Queue: ";
                q.display();

                // Get search target from user
                cout << "Enter the value you want to search: ";
                T choiceVal;
                cin >> choiceVal;

                // Deep copy queue into a vector for safe searching
                vector<T> items = deepCopyToVector(q);

                // Call the recursive function
                int result = linear_search_last(items, choiceVal, 0);

                // Output result
                if (result != -1)
                    cout << "Last occurrence of \"" << choiceVal << "\" found at position " << result << " in the queue." << endl;
                else
                    cout << "Value \"" << choiceVal << "\" not found in queue." << endl;

                break;
            }
            case 9:
                if constexpr (is_same<T, int>::value) {
                    insertion_sort_queue(q);
                    cout << "Queue sorted using insertion sort." << endl;
                }
                else {
                    cout << "Sorting only available for integer queues." << endl;
                }
                break;
            case 10:
                cout << "Exiting menu..." << endl;
                return;
            }

        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n\n";
            continue;
        }
    }
}


template <typename T>
void readFile(ifstream& dataFile, Queue<T>& q) {
    cout << "Reading file..." << endl;

    string line;
    T token;

    while (getline(dataFile, line)) {
        try {
            stringstream ss(line);
            while (ss >> token) {
                q.push(token);
            }
        }
        catch (const exception& e) {
            cout << "Error processing line: " << line << endl;
            cout << "Exception: " << e.what() << endl;
        }
    }

    cout << "readFile complete..." << endl;
    dataFile.close();
}


//Q2
//=============================================================================================================================================
template <typename T>
int linear_search_last(const vector<T>& items, const T& target, size_t pos) {
    if (pos == items.size()) return -1;

    int index_in_rest = linear_search_last(items, target, pos + 1);

    if (index_in_rest != -1)
        return index_in_rest;

    if (items[pos] == target)
        return static_cast<int>(pos);

    return -1;
}
template <typename T>
vector<T> deepCopyToVector(Queue<T> q) {
    // Passed by value deep copy (if your Queue class is copy-safe)
    vector<T> items;
    while (!q.empty()) {
        items.push_back(q.front());
        q.pop();
    }
    return items;
}



//Q3
//=============================================================================================================================================
void insertion_sort_queue(Queue<int>& q) {
    // Step 1: Transfer queue contents to vector
    vector<int> items;
    while (!q.empty()) {
        items.push_back(q.front());
        q.pop();
    }

    // Step 2: Perform insertion sort
    for (int j = 1; j < items.size(); ++j) {
        int key = items[j];
        int i = j - 1;

        while (i >= 0 && items[i] > key) {
            items[i + 1] = items[i];
            i--;
        }
        items[i + 1] = key;
    }

    // Step 3: Push sorted values back into queue
    for (int val : items) {
        q.push(val);
    }
}
