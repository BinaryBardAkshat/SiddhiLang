#if !defined(code_analysis2_Siddhiv3)
#define code_analysis2_Siddhiv3

    #include "filehand.h"
    #include "array.h"
    #include "dict.h"
    #include "str.h"
    #include "token.h"
    
    auto replace_class(str ln){
        str nln;
        if(find_str(ln.Str,str("class ").Str) == 1){
            nln = ln + " starts";
        }
        else{
            nln = ln;
        }
        return nln;
    }
    auto replace_meth(str ln){
        str nln;
        if(find_str(ln.Str,str("pub ").Str) == 1 || find_str(ln.Str,str("priv ").Str) == 1){
            nln = ln + " starts";
        }
        else{
            nln = ln;
        }
        return nln;
    }
    //This function will add semicolan at the end of line to avoid ; missing error in C++.
    auto semicolan_adder(array<str> raw_code){
        //Procedure:
        //1. Split the code into array of lines.
        //2. Work with each line and create a new array.
        //3. Return!
        //Delim is \n because we would like to read each line.
        array<str> newcode;
        for(auto i : raw_code)
            if(find_str(i.Str,str("pub ").Str) == 0 && find_str(i.Str,str("priv ").Str) == 0 && find_str(i.Str,str("if ").Str) == 0 && find_str(i.Str,str("else").Str) == 0 && find_str(i.Str,str("def ").Str) == 0 && find_str(i.Str,str("for ").Str) == 0 && find_str(i.Str,str("class ").Str) == 0 && find_str(i.Str,str("#include ").Str) == 0 && find_str(i.Str,str("//").Str) == 0 && find_str(i.Str,str(";").Str) == 0 && find_str(i.Str,str("import ").Str) == 0 && find_str(i.Str,str("ends").Str) == 0){
                newcode += i + ";";
            }
            else{
                if(find_str(i.Str,str("for ").Str) == 1 || find_str(i.Str,str("if ").Str) == 1){
                    newcode.add(str(i+"){"));
                }
                else if(find_str(i.Str,str("else").Str)){
                    newcode.add(str(i+"{"));
                }
                else{
                    newcode.add(i);
                }
            }
        return newcode;
    }

    auto replace_in_ln(str ln){
        for(auto k : tokens.keys){
            ln = replaceStr(ln.Str,k.Str,tokens[k].Str);
        }
        return ln;
    }
    //Replace operators with their meanings
    auto replace_tokens(array<str> raw_code){
        array<str> newcode;
        for(auto ln : raw_code){
            newcode += replace_in_ln(ln);
        }
        return newcode;
    }

    //This class will do analysis of the code.
    class codeAnalysis{
        public:
            array<str> raw_code;
            array<str> code;
            array<str> imports;
            array<str> functions;

            
            codeAnalysis(array<str> raw_code){
                this->raw_code = raw_code;
            }
            codeAnalysis(){}
            auto parse_down(){
                str fun;
                int ln_fnst;
                int ln_no = 1;
                array<str> ncode;
                array<str> fnblock;
                str fnname;
                bool fn_end = true;
                for(auto ln : raw_code){
                    if(find_str(ln.Str,str("def").Str) == 1 && find_str(ln.Str,str("//").Str) == 0 && find_str(ln.Str,str("#").Str) == 0){
                        fun += ln + " starts\n";
                        fn_end = false;
                        ln_fnst = ln_no;
                        str temp = replaceStr(ln.Str,"def ","");
                        for(int i = 0;i<temp.len();i++){
                            if(temp[i] == '('){
                                break;
                            }
                            else{
                                fnname.push_bk(temp[i]);
                            }
                        }
                        ln_no++;
                    }
                    else if((fnname + " ends") == ln && fn_end == false){
                        fun += replaceStr(ln.Str,(fnname+" ").Str,"") + "\n"; 
                        fnblock.add(fun);
                        fun = "";
                        fnname = "";
                        fn_end = true;
                        ln_fnst = 0;
                        ln_no++;
                    }
                    else if(fn_end == false){
                        fun += ln + "\n";
                        ln_no++;
                    }
                    
                    else if(find_str(ln.Str,str("import ").Str) == 1){
                        imports.add(ln);
                        ln_no++;
                    }
                    else if(find_str(ln.Str,str("//").Str) == 1 || find_str(ln.Str,str("#").Str) == 1){}
                    else{
                        ncode += ln;
                        ln_no++;
                    }
                }
                for(auto i : ncode){
                    this->code += i;
                }
                this->functions = fnblock;
            }
    };

#endif // code_analysis2_Siddhiv3
