#include <sys/wait.h>
#include <unistd.h>
#include "helper.h"



int main(int argc, char** argv) {

   ofstream output("Output/output.txt");
   Manager package;
   cout << argv[1] << endl;
   cout << argv[2] << endl << endl;
   package.initilize(argv[1], argv[2]);

   output << "test" << endl;
   return 0;
}

