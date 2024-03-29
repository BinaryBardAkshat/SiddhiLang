#if !defined(errors_Siddhi_h)
#define errors_Siddhi_h

    #include "str.h"
    //This function will show error
    void error(str err){
        printf("\033[31m%s %s ","Traceback:\n \t \033[0m",err.Str);
        exit(EXIT_FAILURE);
    }

    namespace Siddhi_error{
        class SyntaxError{
            public:
                int line;
                str text;
                SyntaxError(int line,str text = "Syntax error at line "){this->line = line;this->text = text;}
                void geterror(){
                    error(text+to_str(line));
                }
        };
        class ImportError{
            public:
                str filename;
                void geterror(){
                    error(str("ImportError file ")+filename+" doesn't exists\n");
                }
        };
    }

    void raise(Siddhi_error::SyntaxError se){
        se.geterror();
    }
    void raise(Siddhi_error::ImportError ie){
        ie.geterror();
    }

#endif // errors_Siddhi_h
