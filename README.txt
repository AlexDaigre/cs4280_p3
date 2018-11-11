This project is option #3: FSA table + driver.
The fsa table is contained in fsaTable.c and is called fsaTable.
The driver for the table is stored in scanner.c and is called getNextToken().
The testing driver is stored in testScanner.c and called testScanner().

    My outlines for the FSA, FSA Table, charecter groups, and
keyword list are included as a pdf named AlexDaigre_FSAInfo.pdf.

    This driver is invoked from main.c againt the input file. 
Each invocation produces one token. main.c continues to call
getNextToken() untill an eof token is produced.

    fsaTable.c provies some additional functions and lists to
provide both keyword lookup and charecter groups. The charecter
groups allow the fsa table to treat all of a set of charecters
(e.g. all lowercase letters) as one input. This allowed me to 
simplify the table a good bit, and made the proccess closer
to programs like lex.


