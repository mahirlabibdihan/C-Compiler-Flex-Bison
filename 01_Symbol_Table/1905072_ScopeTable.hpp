
#ifndef __SCOPE_TABLE__
#define __SCOPE_TABLE__
#include <vector>
#include "1905072_SymbolInfo.hpp"

/**
 * Class to maintain the scope
 */
class ScopeTable
{
    ScopeTable *parent_scope;
    int id;
    size_t num_buckets;
    SymbolInfo **hash_table;

private:
    void operator=(const ScopeTable &) {} // Protect assignment
    ScopeTable(const ScopeTable &) {}     // Protect copy constructor
    unsigned long sdbmHash(const std::string &str) const;
    int hash(const std::string &name) const;

public:
    /**
     * ScopeTable Constructor
     *
     * @param size number of buckets in a scope table
     */
    ScopeTable(size_t size);

    /**
     * ScopeTable Destructor
     */
    ~ScopeTable();

    // Getters
    /**
     * @return id of the scope
     */
    int getId() const;

    /**
     * @return pointer to the parent scope table
     */
    ScopeTable *getParentScope() const;

    // Setters
    /**
     * @param id id of the scope
     */
    void setId(int id);

    /**
     * @param parent pointer to the parent scope table
     */
    void setParentScope(ScopeTable *parent);

    // Functionalities
    /**
     * Inserts a new symbol in the scope table.
     *
     * @param name name of the symbol to insert
     * @param type type of the symbol to insert
     * @return boolean value indicating whether the insertion is successful
     */
    bool insert(const std::string &name, const std::string &type);

    /**
     * Search a symbol in the symbol table.
     *
     * @param name name of the symbol to search
     * @return pointer to the object of SymbolInfo class representing the looked up symbol
     */
    SymbolInfo *find(const std::string &name) const;

    /**
     * Remove a symbol from the scope table
     *
     * @param name name of the symbol to remove
     * @return boolean value indicating whether the removal is successful
     */
    bool erase(const std::string &name);

    /**
     * Print the scope table.
     * Should be defined by the user itself.
     */
    void print() const;

    /**
     * @param name name of the symbol whose location will be returned
     * @return location of the symbol, which means index of the bucket in scope table and the serial in the chain of that bucket
     */
    std::pair<int, int> getLocationOfSymbol(const std::string &name) const;
};
#endif