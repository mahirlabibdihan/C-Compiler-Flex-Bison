
/**
 * Author: Mahir Labib Dihan
 * Last modified: November 25, 2022
 */

#ifndef _SCOPE_TABLE_H
#define _SCOPE_TABLE_H 1
#include <vector>
#include "../include/1905072_SymbolInfo.hpp"

/**
 * Class to maintain the scope
 */
class ScopeTable
{
    int id;
    int num_buckets;
    ScopeTable *parent_scope;
    SymbolInfo **hash_table;

private:
    void operator=(const ScopeTable &) {}                // Protect assignment
    ScopeTable(const ScopeTable &) {}                    // Protect copy constructor
    unsigned int sdbmHash(const std::string &str) const; // Hash code
    int hash(const std::string &name) const;             // Compression function

public:
    /**
     * ScopeTable Constructor
     *
     * @param n number of buckets in a scope table
     */
    ScopeTable(int n);

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
