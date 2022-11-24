
#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__
#include "1905072_ScopeTable.hpp"

/**
 * Class to keep track of the scopes
 */
class SymbolTable
{
    ScopeTable *current_scope; // Current scope table
    int num_buckets;           // Number of buckets in a scope table
    int scope_count;           // Unique number for every scope

private:
    void operator=(const SymbolTable &) {} // Protect assignment
    SymbolTable(const SymbolTable &) {}    // Protect copy constructor

public:
    /**
     * SymbolTable Constructor
     *
     * @param size number of buckets in a scope table
     */
    SymbolTable(int n);

    /**
     * SymbolTable Destructor
     */
    ~SymbolTable();

    // Getters
    /**
     * @return pointer to the current scope table
     */
    ScopeTable *getCurrentScope() const;

    // Setters
    /**
     * @param curr pointer the new current scope table
     */
    void setCurrentScope(ScopeTable *curr);

    // Functionalities
    /**
     * Create a new scope table and makes it the current scope.
     * Also, make the previous "current" scope table as its parent_scope table.
     *
     * @return boolean value indicating whether entering a new scope is successful or not
     */
    bool enterScope();

    /**
     * Remove the current scope table.
     *
     * @return boolean value indicating whether exiting current scope is successful or not
     */
    bool exitScope();

    /**
     * Inserts a new symbol in the current scope table.
     *
     * @param name name of the symbol to insert
     * @param type type of the symbol to insert
     * @return boolean value indicating whether the insertion is successful
     */
    bool insert(const std::string &name, const std::string &type);

    /**
     * Remove a symbol from the current scope table
     *
     * @param name name of the symbol to remove
     * @return boolean value indicating whether the removal is successful
     */
    bool erase(const std::string &name);

    /**
     * Search a symbol in the symbol table.
     *
     * @param name name of the symbol to search
     * @return pointer to the object of SymbolInfo class representing the looked up symbol
     */
    SymbolInfo *find(const std::string &name) const;

    /**
     * Print the current scope table
     */
    void printCurrentScope() const;

    /**
     * Print all the scope tables currently in the symbol table
     */
    void printAllScope() const;

    /**
     * @param name symbol name
     * @return scope id of the scope table in which the given symbol exists
     */
    int getScopeIdOfSymbol(const std::string &name) const;

    /**
     * @param name name of the symbol whose location will be returned
     * @return location of the symbol, which means index of the bucket in scope table and the serial in the chain of that bucket
     */
    std::pair<int, int> getLocationOfSymbol(const std::string &name) const;
};
#endif
