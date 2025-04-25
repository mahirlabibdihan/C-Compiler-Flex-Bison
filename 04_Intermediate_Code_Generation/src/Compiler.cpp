#include "../include/Compiler.hpp"
#include "../include/ASTGenerator.hpp"
#include "../include/Optimizer.hpp"
#include <iostream>
Compiler::Compiler(std::function<Program *(FILE *)> runParser, LexicalAnalyzer *lexer, SemanticAnalyzer *sem_anlzr, ErrorHandler *error_hndlr, std::ofstream &log, std::ofstream &parse) : logout(log), astout(parse)
{
    this->lexer = lexer;
    this->sem_anlzr = sem_anlzr;
    this->error_hndlr = error_hndlr;
    this->runParser = runParser;
}

void Compiler::setASTRoot(Program *ast_root)
{
    this->ast_root = ast_root;
}
Program *Compiler::getASTRoot()
{
    return ast_root;
}
int Compiler::compile(const string &code_file)
{
    FILE *fin = fopen(code_file.c_str(), "r");
    if (fin == NULL)
    {
        printf("Cannot open specified file\n");
        return EXIT_FAILURE;
    }
    if (runParser(fin)) // Main Parser
    {
        Program *prog = ast_root;

        astout << ASTGenerator::getAST(prog) << std::endl;
        prog->checkSemantics();
        prog->toCode();

        logout << "Total Lines: " << lexer->getLineCount() << std::endl;
        logout << "Total Errors: " << lexer->getErrorCount() << std::endl;
        if (error_hndlr->getErrorCount())
        {
            std::cout << "Code compiled with errors" << std::endl;
        }
        else
        {
            cout << "Code compiled successfully" << endl;
            prog->toAssembly();
            (new Optimizer())->optimize("io/code.asm", "io/optcode.asm");
        }
    }
    fclose(fin);
    return EXIT_SUCCESS;
}