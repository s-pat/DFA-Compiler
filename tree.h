/*
 * parsetree.h
 */

#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "parse.h"
#include <map>
#include <string>
#include "value.h"
using std::vector;
using std::map;
using std::string;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

// a "forward declaration" for a class to hold values
class Value;
extern map<string, Value> evars;
extern void RunTimeError (string);

class ParseTree {
protected:
	int			linenum;
	ParseTree	*left;
	ParseTree	*right;

public:
	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
		: linenum(linenum), left(l), right(r) {}

	virtual ~ParseTree() {
		delete left;
		delete right;
	}

	int GetLinenum() const { return linenum; }

	virtual NodeType GetType() const { return ERRTYPE; }


	virtual bool IsIdent() const { return false; }
	virtual bool IsString() const { return false; }
	virtual bool IsOp() const { return false; }

	virtual string GetId() const { return ""; }

        virtual Value Eval(map<string, Value> &evars) = 0;

};

class StmtList : public ParseTree {

public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}
    
    virtual Value Eval(map <string, Value> &evars)
    {
        left->Eval(evars);
        if(right)
        {
            right->Eval(evars);
        }
        return Value();
    }


};

class IfStatement : public ParseTree {
public:
	IfStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
    
    virtual Value Eval(map <string, Value> &evars)
    {
       Value results = left->Eval(evars);
       if(results.GetInt() == 1)
       {
         if(results.GetInt() ==1)
         {
            return right->Eval(evars);  
         }
       }

        return Value();
    }
};

class SetStatement : public ParseTree {
	string id;

public:
	SetStatement(int line, string id, ParseTree *expr) : ParseTree(line, expr), id(id) {}
     virtual Value Eval(map <string, Value> &evars)
    {
               Value result = left->Eval(evars);

           if(evars.count(id) && !evars.empty())
           {
               
             evars[id] = result;
           }
           else
           {             
             evars.insert (std::pair<string, Value>(id, result));
           }
       
        return Value();
  
    } 
};

class PrintStatement : public ParseTree {
public:
	PrintStatement(int line, ParseTree *e) : ParseTree(line, e) {}
    virtual Value Eval(map <string, Value> &evars)
    {
      cout << left->Eval(evars);
      return Value();
    }

};

class LoopStatement : public ParseTree {
public:
	LoopStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
     virtual Value Eval(map <string, Value> &evars)
    {
     Value results = right->Eval(evars);
     right->Eval(evars);
     right->Eval(evars);
     right->Eval(evars);

           return Value();         
    }  
};

class Addition : public ParseTree {
public:
	Addition(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    virtual Value Eval(map <string, Value> &evars)
    {
      return left->Eval(evars) + right->Eval(evars);
    }
};

class Subtraction : public ParseTree {
public:
	Subtraction(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    virtual Value Eval(map <string, Value> &evars)
    {
      return left->Eval(evars) - right->Eval(evars);
    }
};

class Multiplication : public ParseTree {
public:
	Multiplication(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
	
      virtual Value Eval(map <string, Value> &evars)
    {
      return left->Eval(evars) * right->Eval(evars);
    }

};

class Division : public ParseTree {
public:
	Division(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
	 virtual Value Eval(map <string, Value> &evars)
    {
      return left->Eval(evars) / right->Eval(evars);
    }

};

class IConst : public ParseTree {
	int val;

public:
	IConst(int l, int i) : ParseTree(l), val(i) {}
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}

	NodeType GetType() const { return INTTYPE; }
    
     virtual Value Eval(map <string, Value> &evars)
    {
      return Value(val);
    }

};

class SConst : public ParseTree {
	string val;

public:
	SConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = t.GetLexeme();
	}

	NodeType GetType() const { return STRTYPE; }
	bool IsString() const { return true; }
    
       virtual Value Eval(map <string, Value> &evars)
    {
      return Value(val);
    }
};

class Ident : public ParseTree {
	string id;

public:
	Ident(Token& t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {}

	bool IsIdent() const { return true; }
	string GetId() const { return id; }
    
      virtual Value Eval(map <string, Value> &evars)
    {
      if(!evars.empty() && evars.count(id))
      {
        return evars[id];
      }
      else
      {
       RunTimeError("Symbol " + id + " not defined");
          return Value();
      }
    }

};




#endif /* TREE_H_ */
