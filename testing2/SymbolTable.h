#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Type {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_VOID,
    TYPE_ERROR
};

struct FunctionSignature {
    Type return_type;
    vector<Type> param_types;
    vector<string> param_id;
    int param_count;
};

class SymbolInfo {
public:
    int size;
    string value;
    Type type;
    bool isFunc;
    vector<Type> param_types;
    vector<string> param_id;

    SymbolInfo() : size(0), value(""), type(TYPE_VOID), isFunc(false) {}

    ~SymbolInfo() {}

    SymbolInfo& operator=(const SymbolInfo& rhs) {
        if (this != &rhs) {
            this->size = rhs.size;
            this->value = rhs.value;
            this->type = rhs.type;
            this->isFunc = rhs.isFunc;
            this->param_types = rhs.param_types;
            this->param_id = rhs.param_id;
        }
        return *this;
    }
};

class SymbolTable {
public:
    SymbolTable* Parent;
    unordered_map<string, SymbolInfo> Table;

    SymbolTable() {
        this->Parent = nullptr;
    }

    ~SymbolTable() {}

    void SetParent(SymbolTable* P) {
        this->Parent = P;
    }

    void AddFunctionToTable(const char* id, FunctionSignature Sig, Type return_type) {
        SymbolInfo func;
        func.type = return_type;
        func.isFunc = true;
        func.param_types = Sig.param_types;
        func.param_id = Sig.param_id;
        string name(id);
        cout<<"function added"<<name;
        this->Table[name] = func;
    }
};
