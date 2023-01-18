/**
 * Author: Mahir Labib Dihan
 * Last modified: December 05, 2022
 */

#ifndef _SYMBOL_INFO_H
#define _SYMBOL_INFO_H 1
#include <string>
/**
 * Class to store the scope information
 */
class SymbolInfo
{
    std::string name;
    std::string type;
    SymbolInfo *next;

private:
    SymbolInfo(const SymbolInfo &) {}     // Protect copy constructor
    void operator=(const SymbolInfo &) {} // Protect assignment

public:
    /**
     * SymbolInfo Constructor
     *
     * @param name symbol name
     * @param type symbol type
     * @param next pointer to the next symbol
     */
    SymbolInfo(const std::string &name = "", const std::string &type = "", SymbolInfo *next = nullptr);

    /**
     * ScopeTable Destructor
     */
    ~SymbolInfo();

    // Getters
    /**
     * @return symbol name
     */
    const std::string &getSymbol() const;

    /**
     * @return symbol type
     */
    const std::string &getType() const;

    /**
     * @return pointer to the next symbol
     */
    SymbolInfo *getNext() const;

    // Setters
    /**
     * @param next pointer to the next symbol
     */
    void setNext(SymbolInfo *next);

    /**
     * @param name new symbol name
     */
    void setSymbol(const std::string &name);

    /**
     * @param type new symbol type
     */
    void setType(const std::string &type);
};
#endif
