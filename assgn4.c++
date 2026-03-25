#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
using namespace std;

class component{
    
    string line;
    
    public:
    int type; //0=file,1=folder
    string name;
    vector<component*> contents;
    
    component* rootfolder;
    component(int i,component* current){
        type=i;
        if(type==0){
            cout<<"Enter File Name: ";
            cin>>name;
            ofstream Myfile(name+".txt");
            name=name+".txt";
            
            cout<<"Enter File Contents: \n";
            cin.ignore();
            while (getline(cin, line) && !line.empty()) {
                Myfile<<line<<endl;
            }
            Myfile.close();
            rootfolder=current;
        }


        else{
            type=1;
            cout<<"Enter Folder Name: ";
            cin>>name;
            rootfolder=current;
        }
    }
    component* add_component(int i,component* current){
        if(i==0 ){
           component* newfile= new component(0,current);
           contents.push_back(newfile);
           return newfile; 
        }
        else{
            component* newfolder=new component(1,current);
            contents.push_back(newfolder);
            return newfolder;
        }
    }
    void view_component(){
        if(1){
            cout<<"Contents: \n";
            for(int i=0;i<contents.size();i++){
                cout<<i+1<<". "<<contents[i]->name<<endl;
            }
        }
    }
    int read(){
        ifstream myFile(name);

    // 2. Check if the file opened successfully
    if (!myFile.is_open()) {
        cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    string line;
    // 3. Read the file line by line until the end
    while (getline(myFile, line)) {
        cout << line << std::endl;
    }

    // 4. Close the file (optional but good practice)
    myFile.close();
    }
    void delete_component(){
        for(int i=0;i<rootfolder->contents.size();i++){
            if(rootfolder->contents[i]->name==name){
                rootfolder->contents.erase(rootfolder->contents.begin()+i);
            }
        }
        if(type==0){
            if (remove(name.c_str()) != 0) {
                cerr << "Error deleting file: " << name <<endl;
            } else {
                cout << "File successfully deleted: " << name << endl;
            }
        }
        else{
            for(int i=0;i<contents.size();i++){
                contents[i]->delete_component();
            }
            delete this;
        }
    }
};

class filemanagementsystem{
    component* root=new component(1,NULL);
    component* current=root;
    component* temp;
    int choice;
    public:
    void FileOps(){
    
        while(current!=NULL){
            if(current->type==1){
                cout<<"Current Folder: "<<current->name<<" \nWhat do you want to do: \n1. Create folder\n2. Create file\n3. Go to root\n4. View contents\n5. Delete \n6. Exit\n";
                cout<<"Enter Your choice: ";
                cin>>choice;
                if(choice==1){
                    temp=current->add_component(1,current);
                    // current=temp;
                }
                else if(choice==2){
                    current->add_component(0,current);
                }
                else if(choice==3){
                    current=current->rootfolder;
                }
                else if(choice==4){
                    current->view_component();
                    cout<<"\nGo to content? 0 for root : ";
                    cin>>choice;
                    if(choice==0){
                        continue;
                    }
                    else{
                        current=current->contents[choice-1];
                    }
                }
                else if(choice==5){
                    temp=current;
                    current=current->rootfolder;
                    temp->delete_component();
                }
                else{
                    break;
                }
            }
            else{
                cout<<"Current File : "<<current->name<<endl;
                cout<<"What do you want to do: \n1. Go to root\n2. Read a file\n3. Delete\n4. Exit\n";
                cout<<"Enter Your choice: ";
                cin>>choice;
                if(choice==1){
                    current=current->rootfolder;
                }
                else if(choice==2){
                    current->read();
                }
                else if(choice==3){
                    temp=current;
                    current=current->rootfolder;
                    temp->delete_component();
                }
                else{
                    break;
                }
            }
            
        }
    }

};
int main(){
    filemanagementsystem f1;
    f1.FileOps();
}