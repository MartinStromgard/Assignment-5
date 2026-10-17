// This is the file with the code.
// To be done:
  // Write a makefile (for easy compilation).
  // Use exceptions to handle user errros.
  // Write a small report, to be found in your git repository.
  // Create a header file for the classes (2 in total).

  // Have a look at std::discrete_distribution


  //a k or an output length that is not a positive integer, or an output length smaller than k,
  //an option -a that is not followed by an non-negative number, or an unknown option,
  //a training file that cannot be opened, and
  //a training text that i too short to contain any k-gram followed by a character.
  //Wrong number of arguments.

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <random>
# include <cstdlib> //for the strtod function.
# include <stdexcept>
# include "main classes.h"

using namespace std;

class k_gram {
}
class k_plus_1_gram {
}

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

double set_alpha(bool& error, char* LIST[]){
  string First_argument = LIST[1];
  if (First_argument == "-a"){
    char* endPtr;
    alpha = strtod(LIST[2],&endPtr);
    if (ALPHA <= 0){
      cerr << "Alpha must be a double larger than zero if -a is written." << endl;
      error = true;
    }
  } else {
    alpha = 0;
  }
  return alpha;
}

unsigned set_K(bool& ERROR, char* arglist[]){
  string First_argument = arglist[1];
  if (First_argument == "-a"){
    int alpha_is_given = 2;
  } else {
    int alpha_is_given = 0;
  }
  try {
    double K_d = stod(arglist[alpha_is_given+1]);
    int K = stoi(arglist[alpha_is_given+1]);
    if (K_d <= 0 || K_d != K){
      cerr << "K must be an integer larger than 0." << endl;
      ERROR = true;
    }
  } catch (invalid_argument) {
    cerr << "K must be an integer larger than 0." << endl;
    ERROR = true;
  }
  return K_d;
}

void Open_file(bool& ERROR, ifstream& FILE, char* LIST[]){
  string First_argument = arglist[1];
  if (First_argument == "-a"){
    int alpha_is_given = 2;
  } else {
    int alpha_is_given = 0;
  }
  string file_string = LIST[alpha_is_given+2];
  try {
    FILE.open(file_string);
  } catch (const ios_base::failure& e){
    cerr << "Could not open file." << endl;
    ERROR = true;
  }
}
string Text_from_file(ifstream& FILE){
  string string_to_import;
  string imported_word;
  while (FILE>>imported_word){
    string_to_import.append(imported_word);
    string_to_import.append("_");
  }
  return string_to_import;
}

int set_text_length(bool& ERROR, unsigned K,char* ARGV[]){
  int text_length = 0;
  string First_argument = arglist[1];
  if (First_argument == "-a"){
    int alpha_is_given = 2;
  } else {
    int alpha_is_given = 0;
  }
  try {
    text_length = stoi(arglist[alpha_is_given+3]);
    if (text_length < K){
      cerr << "Text length must be an integer larger than the chosen K." << endl;
      ERROR = true;
    }
  } catch (invalid_argument) {
    cerr << "Text length must be an integer larger than the chosen K." << endl;
    ERROR = true;
  }
  return text_length;
}

int main(int argc, char *argv[]){
  
  bool error = false;      //If something goes wrong in a function, the functions will change error to true.
  
  if (wrong_number_of_arguments(argc,argv) == true){
    cerr << "Wrong number of arguments." << endl;
    return 1;
  }
  
  unsigned k = set_K(error, argv);
  double alpha = set_alpha(error,argv);
  ifstream file; Open_file(error, file, argv);          //If file can not be opened, throw exception.
  int text_length = set_text_length(error, k,argv);     //text length can not be lower than the chosen k.
  if (error == true){
    return 1;
  }
  string Total_text = Text_from_file(file);
  

  
  //If -a is given, the number af alpha will be the first argument.
  //argv[1] is k (the length of the "gram")
  //argv[2] is the name of the text file that is used to train the model.
  //argv[3] is an integer that decides how many characters to output.

  //For example: slm -a 0.01 3 moby_dick.txt 40.
  //or slm 2 moby_dick.txt 5
  
}



