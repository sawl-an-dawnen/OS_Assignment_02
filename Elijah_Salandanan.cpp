#include <sys/wait.h>
#include <unistd.h>
#include "helper.h"

int timePassed = 0;//used to sync

int main(int argc, char** argv) {

   ofstream output("Output/output.txt");
   Manager package;
   cout << argv[1] << endl;
   cout << argv[2] << endl << endl;
   package.initilize(argv[1], argv[2]);

   int pnum = -1;
   int pid;
   for(int k =0; k<package.p; k++)  { //will create the number of processes in package
      pid = fork();
	   if(pid ==0) {
	      pnum = k;
	      break;
	   }
   }

   if (pid == 0)  {//is a child process
      /*---functions---
      request //makes are request for resources and if allocated will sit waiting to be 'used' passes 1 time unit
      calculate //just passes time in ()
      use_resource //commits the allocated resources to master string and passes time in ()
      print //prints current process master string passes 1 unit time
      release //releases indicated resources passes 1 unit time
      end. //ends process, shuts down
      */
      int instr = -1;
      int unit = 1;
      string prompt;
      for (int i = 0; i < package.processes[pnum].instructions.size(); i ++)  {
         prompt = package.processes[pnum].instructions[i];
         if (prompt.find("request") != string::npos) {instr = 0;}
         if (prompt.find("calculate") != string::npos) {instr = 1;}
         if (prompt.find("use") != string::npos) {instr = 2;}
         if (prompt.find("print") != string::npos) {instr = 3;}
         if (prompt.find("release") != string::npos) {instr = 4;}
         if (prompt.find("end") != string::npos) {instr = 5;}
         switch (instr) {
            case 0:
               cout << "process " << pnum << " calling request function..." << endl;
               break;
            case 1:
               cout << "process " << pnum << " calling calculate function..." << endl;
               break;
            case 2:
               cout << "process " << pnum << " calling use function..." << endl;
               break;
            case 3:
               cout << "process " << pnum << " calling print function..." << endl;
               break;
            case 4:
               cout << "process " << pnum << " calling release function..." << endl;
               break;
            case 5:
               cout << "process " << pnum << " calling end function..." << endl;
               break;
            default:
               break;
         }
         
      }
      //cout << "PROCESS " << pnum + 1 << " instruction: " << package.processes[pnum].instructions[0] << endl;
      write(package.processes[pnum].pipeWrite[1], &unit, sizeof(unit));//used to increment time
      return 0;
   }

   for (int i = 0; i < package.p; i++){
      wait(0);
   }
   for (int i = 0; i < package.p; i++){
      int unit;
      read(package.processes[i].pipeWrite[0], &unit, sizeof(unit));
      timePassed = timePassed + unit;
   }
   cout << timePassed << endl;

   for (int i = 0; i < package.p; i ++)   {
      close(package.processes[i].pipeRead[0]);
      close(package.processes[i].pipeRead[1]);
      close(package.processes[i].pipeWrite[0]);
      close(package.processes[i].pipeWrite[1]);
   }

   return 0;
}

