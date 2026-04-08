#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>

using namespace std;

class component {

    string line;

public:
    int type; // 0 = file, 1 = folder
    string name;
    vector<component*> contents;
    component* rootfolder;

    component(int i, component* current) {
        type = i;

        if (type == 0) {
            cout << "Enter File Name: ";
            cin >> name;

            if (current != NULL)
                name = current->name + "/" + name;

            string filename = name + ".txt";
            ofstream Myfile(filename);
            name = filename;

            cout << "Enter File Contents:\n";
            cin.ignore();

            while (getline(cin, line) && !line.empty()) {
                Myfile << line << endl;
            }

            Myfile.close();
            rootfolder = current;
        }

        else {
            cout << "Enter Folder Name: ";
            cin >> name;

            if (current != NULL)
                name = current->name + "/" + name;

            string cmd = "mkdir -p \"" + name + "\"";
            system(cmd.c_str());  // ✅ Linux mkdir

            rootfolder = current;
        }
    }

    component* add_component(int i, component* current) {
        component* newComp = new component(i, current);
        contents.push_back(newComp);
        return newComp;
    }

    void view_component() {
        cout << "Contents:\n";
        for (int i = 0; i < contents.size(); i++) {
            cout << i + 1 << ". " << contents[i]->name << endl;
        }
    }

    void read() {
        ifstream myFile(name);

        if (!myFile.is_open()) {
            cerr << "Error opening file\n";
            return;
        }

        while (getline(myFile, line)) {
            cout << line << endl;
        }

        myFile.close();
    }

    void copy_component(string dest) {
        string cmd;

        if (type == 0) {
            cmd = "cp \"" + name + "\" \"" + dest + "/\"";
        } else {
            cmd = "cp -r \"" + name + "\" \"" + dest + "/\"";
        }

        int result = system(cmd.c_str());

        if (result == 0)
            cout << "Copied successfully!\n";
        else
            cerr << "Copy failed\n";
    }

    void delete_component() {

        // remove from parent vector
        if (rootfolder != NULL) {
            for (int i = 0; i < rootfolder->contents.size(); i++) {
                if (rootfolder->contents[i] == this) {
                    rootfolder->contents.erase(rootfolder->contents.begin() + i);
                    break;
                }
            }
        }

        string cmd;

        if (type == 0) {
            cmd = "rm \"" + name + "\"";
        } else {
            cmd = "rm -rf \"" + name + "\"";
        }

        int result = system(cmd.c_str());

        if (result == 0)
            cout << "Deleted successfully\n";
        else
            cerr << "Delete failed\n";

        delete this;
    }
};

class filemanagementsystem {
    component* root;
    component* current;
    component* temp;
    int choice;

public:
    filemanagementsystem() {
        root = new component(1, NULL);
        current = root;
    }

    void FileOps() {

        while (current != NULL) {

            if (current->type == 1) {
                cout << "\nCurrent Folder: " << current->name;
                cout << "\n1. Create folder\n2. Create file\n3. Go to parent\n4. View contents\n5. Delete\n6. Copy\n7. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                if (choice == 1) {
                    current->add_component(1, current);
                }
                else if (choice == 2) {
                    current->add_component(0, current);
                }
                else if (choice == 3) {
                    current = current->rootfolder;
                }
                else if (choice == 4) {
                    current->view_component();
                    cout << "Enter index (0 to stay): ";
                    cin >> choice;

                    if (choice != 0)
                        current = current->contents[choice - 1];
                }
                else if (choice == 5) {
                    temp = current;
                    current = current->rootfolder;
                    temp->delete_component();
                }
                else if (choice == 6) {
                    string dest;
                    cout << "Enter destination path: ";
                    cin >> dest;
                    current->copy_component(dest);
                }
                else {
                    break;
                }
            }

            else {
                cout << "\nCurrent File: " << current->name;
                cout << "\n1. Go to parent\n2. Read file\n3. Delete\n4. Copy\n5. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                if (choice == 1) {
                    current = current->rootfolder;
                }
                else if (choice == 2) {
                    current->read();
                }
                else if (choice == 3) {
                    temp = current;
                    current = current->rootfolder;
                    temp->delete_component();
                }
                else if (choice == 4) {
                    string dest;
                    cout << "Enter destination path: ";
                    cin >> dest;
                    current->copy_component(dest);
                }
                else {
                    break;
                }
            }
        }
    }
};

int main() {
    filemanagementsystem f;
    f.FileOps();
    return 0;
}
