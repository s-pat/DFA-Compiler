#include "tokens.h"
#include "parse.h"
#include <fstream>
using namespace std;
map<string, Value> holder;

void RunTimeError(string errormsg)
{
    cout << "RUNTIME ERROR " << errormsg << endl;
    exit(1);

}
int main(int argc, char *argv[]) {
 
    ifstream fileIN;
	istream *in;
	int linecount = 0;

	if( argc == 1 ) {
		in = &cin;
	}

	else if( argc == 2 ) {
		fileIN.open(argv[1]);
		if( fileIN.is_open() == false ) {
			cout << "COULD NOT OPEN " << argv[1] << endl;
			return 1;
		}
		in = &fileIN;
	}
	else {
		cout << "TOO MANY FILENAMES" << endl;
		return 1;
	}
	ParseTree *prog = Prog(*in, linecount);
     if (prog == 0){
        return 0;
}
   prog->Eval(holder);
   return 0;
}