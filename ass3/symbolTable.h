#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

// // // // // // // // // // // // // // // // // // // // 
//
// Class: Scope
//

// feel free to replace std::string  with std::string
class Scope {
private:
    static bool debugFlg;                      // turn on tedious debugging
    std::string name;                          // name of scope
    std::map<std::string, void *> symbols;    // use an ordered map (not as fast as unordered)

public:
    Scope(std::string);
    ~Scope();
    std::string scopeName();                   // returns name of scope
    void debug(bool);                    // sets the debug flag to new state
    void print(void (*printData)(void *));     // prints the table using the supplied function to print the void *
    void applyToAll(void (*action)(std::string, void *));  // applies func to all symbol/data pairs 
    bool insert(std::string, void *);   // inserts a new ptr associated with symbol sym 
                                               // returns false if already defined
    void *lookup(std::string);             // returns the ptr associated with sym
                                               // returns NULL if symbol not found
};

// // // // // // // // // // // // // // // // // // // // 
//
// Class: SymbolTable
//
// Is a stack of scopes.   The global scope is created when the table is
// is constructed and remains for the lifetime of the object instance.
//

class SymbolTable {
private:
    std::vector<Scope *> stack;
    bool debugFlg;

public:
    SymbolTable();
    void debug(bool);                                // sets the debug flags
    int depth();                                     // what is the depth of the scope stack?
    void print(void (*printData)(void *));           // print all scopes using data printing function
    void enter(std::string);                    // enter a scope with given name
    void leave();                                    // leave a scope (not allowed to leave global)
    void *lookup(std::string);                   // returns ptr associated with sym anywhere in symbol table
                                                     // returns NULL if symbol not found
    void *lookupGlobal(std::string);             // returns ptr associated with sym in globals
                                                     // returns NULL if symbol not found
    bool insert(std::string, void *);         // inserts new ptr associated with symbol sym in current scope
                                                     // returns false if already defined
    bool insertGlobal(std::string, void *);   // inserts a new ptr associated with symbol sym 
                                                     // returns false if already defined
    void applyToAll(void (*action)(std::string , void *));        // apply func to all symbol/data pairs in local scope
    void applyToAllGlobal(void (*action)(std::string , void *));  // apply func to all symbol/data pairs in global scope
};

#endif