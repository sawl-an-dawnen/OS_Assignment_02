#include <sys/wait.h>
#include <unistd.h>
#include "helper.h"



int main(int argc, char** argv) {

   ofstream output("Output/output.txt");
   Manager package;
   cout << argv[1] << endl;
   package.initilize(argv[1]);

   output << "test" << endl;
   return 0;
}
