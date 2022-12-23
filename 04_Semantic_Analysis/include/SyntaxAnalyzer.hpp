class SyntaxAnalyzer
{
    bool in_function;

public:
    void handleInvalidFunctionScoping();
    void startScope();
};