# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <random>
# include <cstdlib> //for the strtod function.
# include <stdexcept>
# include <vector>
# include "Assignment 5 header.h"

using namespace std;

int main(int argc, char *argv[]){
  
  bool error = false;      //If something goes wrong in a function, the functions will change error to true.
  
  if (wrong_number_of_arguments(argc,argv) == true){
    cerr << "Wrong number of arguments." << endl;
    return 1;
  }
  
  unsigned k = set_K(error, argv);
  double alpha = set_alpha(error,argv);
  int Index_to_extract_filename_from;
  if (alpha!=0){
      Index_to_extract_filename_from = 4;
  } else {
      Index_to_extract_filename_from = 2;
  }
  ifstream file(argv[Index_to_extract_filename_from]);            //If file can not be opened, throw exception.
  if (!file.is_open()){
    cerr << "Could not open file." << endl;
    return 1;
  }
  int text_length = set_text_length(error, k,argv);     //text length can not be lower than the chosen k.
  string Total_text = Text_from_file(error,file,k);          //If length of Total_text is lower than k, there will be an exception.
  if (error == true){
    return 1;
  }
  map<string,unsigned> Map_of_k_grams = import_k_grams_into_map(k, Total_text);
  map<string,unsigned> Map_of_k_plus_1_grams = import_k_plus_1_grams_into_map(k, Total_text);
  vector<string> Alphabet_in_text_file = Set_of_letters_used_in_file(Total_text);

  string final_string_result = generate_text(Map_of_k_grams,Map_of_k_plus_1_grams,set_text_length);
  cout << final_string_result << endl;
}
