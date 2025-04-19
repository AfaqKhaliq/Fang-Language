#include<unordered_map>
#include<iostream>
#include<string>
using namespace std;
class SymbolInfo{
    public:
    int size;
    string value;
    string type;

    SymbolInfo() : size(0), value(""), type("") {}
    SymbolInfo(int size, string value, string type)
    : size(size), value(value), type(type) {}
    ~SymbolInfo(){};
    SymbolInfo& operator=(const SymbolInfo& rhs) {
        if (this != &rhs) {
            this->size = rhs.size;
            this->value = rhs.value;
            this->type = rhs.type;
        }
        return *this;
    }
    
};

class SymbolTable
{
    private:
    public:
    SymbolTable* Parent;
    unordered_map<string,SymbolInfo> Table;
    SymbolTable(){
        this->Parent=nullptr;
    }
    ~SymbolTable(){
    }
    void SetParent(SymbolTable* P){
        this->Parent=P;
    }
    void AddtoTable(const char*id ,SymbolInfo val){
        string name(id);
        this->Table[name]=val;   
    }

};
