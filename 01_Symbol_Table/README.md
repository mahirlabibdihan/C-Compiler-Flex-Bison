# Symbol Table

- SymbolInfo
  - `name: string`
  - `type: string`
  - `next: SymbolInfo*`
- ScopeTable
  - `id: int`
  - `num_buckets: int`
  - `parent_scope: ScopeTable*`
  - `insert(name:string, type:string): bool`
  - `find(name:string): SymbolInfo*`
  - `erase(name:string): bool`
- SymbolTable
  - `current_scope: ScopeTable*`
  - `enterScope(): bool`
  - `exitScope(): bool`
  - `insert(name:string, type:string): bool`
  - `find(name:string): SymbolInfo*`
  - `erase(name:string): bool`
  - `printCurrentScope(): void`
  - `printAllScope(): void`