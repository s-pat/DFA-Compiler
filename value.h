#include <stdexcept>
#include <string>

using std::string;

#include <iostream>

using std::ostream;

#ifndef _VALUE_H_
#define _VALUE_H_

extern void RunTimeError(string);

class Value {
public:
    enum ValType {
        ERRVAL, INTVAL, STRVAL
    };

private:
    ValType theType;
    int theInt;
    string theStr;

public:
    Value() : theType(ERRVAL), theInt(0) {}

    Value(int i) : theType(INTVAL), theInt(i) {}

    Value(string s) : theType(STRVAL), theInt(0), theStr(s) {}

    bool isInt() const { return theType == INTVAL; }

    bool isStr() const { return theType == STRVAL; }

    bool isErr() const { return theType == ERRVAL; }

    int GetInt() const {
        if (isInt()) return theInt;
        throw std::logic_error("This Value is not an int");
    }

    string GetStr() const {
        if (isStr()) return theStr;
        throw std::logic_error("This Value is not a string");
    }

    bool GetBool() const {
        if (isErr()) return theType;
        throw std::logic_error("This Value is not a boolean typed");
    }


    Value operator+(const Value &o) const {
        if (this->isInt() && o.theType == INTVAL) {
            return Value(this->GetInt() + o.GetInt());

        }
        if (this->isStr() && o.isStr()) {
            return Value(this->GetStr() + o.GetStr());
        } else {

            RunTimeError("Type mismatch for arguments of +");
            return Value();
        }


    }

    Value operator-(const Value &o) const {

        if (this->isInt() && o.theType == INTVAL) {
            return Value(this->GetInt() - o.GetInt());

        } else {
            RunTimeError("Type mismatch for arguments of -");
            return Value();
        }

    }

    Value operator*(const Value &o) const {

        if (this->isInt() && o.theType == INTVAL) {
            return Value(this->GetInt() * o.GetInt());

        } else if (this->isInt() && o.isStr()) {
            if (this->GetInt() >= 0) {
                string x = "";
                for (int i = 0; i < this->GetInt(); i++) {
                    x = x + o.GetStr();
                }
                return x;
            } else if (o.GetInt() == 0) {
                string x = "";
                return x;
            } else {
                RunTimeError("Cannot multiply a string by a negative integer");
                return Value();
            }


        } else if (this->isStr() && o.isInt()) {
            if (o.GetInt() > 0) {
                string x = "";

                for (int i = 0; i < o.GetInt(); i++) {
                    x = x + this->GetStr();
                }
                return x;
            } else if (o.GetInt() == 0) {
                string x = "";
                return x;
            } else {
                RunTimeError("Cannot multiply a string by a negative integer");
                return Value();
            }


        } else {
            RunTimeError("Type mismatch for arguments of *");
            return Value();
        }

    }

    Value operator/(const Value &o) const {
        if (this->isInt() && o.isInt()) {
            if (o.theInt != 0) {
                //return response;
                return Value(this->GetInt() / o.GetInt());
            } else {
                RunTimeError("Cannot divide by 0");
                return Value();
            }
        } else {
            RunTimeError("Cannot divide these two values");
            return Value();
        }
    }

    friend ostream &operator<<(ostream &out, const Value &v) {
        switch (v.theType) {
            case ERRVAL:
                out << "RUNTIME ERROR: " << v.theStr;
                break;
            case INTVAL:
                out << v.theInt;
                break;
            case STRVAL:
                out << v.theStr;
                break;
        }

        return out;
    }
};

#endif