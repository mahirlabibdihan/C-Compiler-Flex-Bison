# Lexical Analyzer

Character: We are allowing any single character except Single Quotation, Double Quotation and Newline inside ' ' for a VALID CHAR. With the exception of scape sequences like '\n','\a'.. etc. Other than this, if there is multiple characters inside ' ', then its an MULI CHAR ERROR. Since we are allowing \ as a single character inside ' ', '\n' can be treated as both VALID CHAR and MULTI CHAR. Since \ is one character and n is another. But \n is an escape sequence too. So, we want '\n' to be a VALID CHAR. That's why we will put pattern of VALID CHAR before MULTI CHAR.

String:  We are allowing any character except Single Quotation, Double Quotation and Newline inside " " for a VALID STRING. For MULTI LINE STRING, Backslash is needed to go from one line to another.  

SingleComment: We are allowing any character except NEWLINE after //. For MULTI LINE COMMENT, Backslash is needed to go from one line to another.  

MultiComment: We are allowing any character except / inside /* */. If we want to use /, we need to make sure there is not * before it.
