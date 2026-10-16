// This is the file with the code.
// To be done:
  // Write a makefile (for easy compilation).
  // Use exceptions to handle user errros.
  // Write a small report, to be found in your git repository.
  // Create a header file for the classes (2 in total).

  // Have a look at std::discrete_distribution

# include <iostream>
# include <fstream>
# include <map>
# include <random>

bool wrong_number_of_arguments(int argcount,char *arglist[]){
  // If -a is not written in the beginning, then argcount should be 4. Otherwise, it should be 6.
  
  if (argcount < 4){
    return true;
  }
  string First_argument = arglist[1];
  
  if (First_argument=="-a" && argcount != 6){
    return true;
  }
  if (First_argument == "-a" && argcount == 6){
    return false;
  }
  if (argc != 4){
    return true;
  }
  return false;
}

bool No_errors(int argcount,char *arglist[]){
  
  //a k or an output length that is not a positive integer, or an output length smaller than k,
  //an option -a that is not followed by an non-negative number, or an unknown option,
  //a training file that cannot be opened, and
  //a training text that i too short to contain any k-gram followed by a character.

  //Wrong number of arguments.
  if (wrong_number_of_arguments(argcount,arglist) == true){
    return false;
    //throw std::invalid_argument
    //return 1
  } 
  string First_argument = arglist[1];
  if (First_argument == "-a" && )
  string First_argument = arglist[1];
  string Second_argument = arglist[2];

  if 
  if arglist[1]
  
}

using namespace std;

int main(int argc, char *argv[]){
  //If -a is given, the number af alpha will be the first argument.
  //argv[0] is k (the length of the "gram")
  //argv[1] is the name of the text file that is used to train the model.
  //argv[2] is an integer that decides how many characters to output.

  //For example: slm -a 0.01 3 moby_dick.txt 40.
  //or slm 2 moby_dick.txt 5

  if (No_errors(argc,argv)==false){
    return 1;
  }
  
}



