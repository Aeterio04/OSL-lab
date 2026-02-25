#include <iostream>
using namespace std;

class process {
public:
    int memory_req;
    bool isAllocated = false; // Track if process found a home
};

class fragment {
public:
    int total_mem;
    process* proc = NULL;
};

class implement {
public:
    int numproc, numfrag;
    process* temp;
    fragment* frag;

    implement() {
        cout << "Number of processes: ";
        cin >> numproc;
        temp = new process[numproc];
        
        
        for (int i = 0; i < numproc; i++) {
            cout << "Memory required for process " << i + 1 << ": ";
            cin >> temp[i].memory_req;
        }

        cout << "Number of fragments (Total 1000MB): ";
        cin >> numfrag;
        
        frag = new fragment[numfrag];

        while (true) {
            int sum = 0;
            for (int i = 0; i < numfrag; i++) {
                cout << "Enter memory for block " << i + 1 << ": ";
                cin >> frag[i].total_mem;
             
                sum += frag[i].total_mem;
             }
            if (sum <= 1000) break;
            cout << "Sum exceeds 1000MB. Try again.\n";
        }
    }

    void next_Fit() {
        int j = 0;
        int allocated_count = 0;

        for (int i = 0; i < numproc; i++) {
        
        
            int start_point = j;
            bool found = false;

            do {
        
        
            if (frag[j].proc == NULL && temp[i].memory_req <= frag[j].total_mem) {
    
                frag[j].proc = &temp[i];
                    temp[i].isAllocated = true;
    
                    cout << "Process " << i + 1 << " allocated to fragment " << j + 1 << endl;
                    
                    j = (j + 1) % numfrag; 
                    allocated_count++;
                    found = true;
                    break;
                }
                j = (j + 1) % numfrag;
            } while (j != start_point);

            if (!found) {
                cout << "Process " << i + 1 << " could not be allocated." << endl;
            }
        }

        if (allocated_count == numproc) cout << "\nAll processes allocated successfully.\n";
        else cout << "\nSome processes remain unallocated.\n";
    }

    void calc() {
        int total_internal_frag = 0;
        for (int i = 0; i < numfrag; i++) {
            if (frag[i].proc != NULL) {
                int wasted = frag[i].total_mem - frag[i].proc->memory_req;
                total_internal_frag += wasted;
                cout << "Fragment " << i + 1 << " wasted: " << wasted << " MB" << endl;
            }
        }
        cout << "Total Internal Fragmentation: " << total_internal_frag << " MB" << endl;
    }
};

int main() {
    implement i1;
    i1.next_Fit();
    i1.calc();
    return 0;
}
