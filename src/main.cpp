//This is where the main function is run.

# include "Main code assignment.h"

int main(int argc, char *argv[]){
  
  bool error = false;      //If something goes wrong in a function, the functions will change error to true.
  
  if (wrong_number_of_arguments(argc,argv) == true){        //First check: Do we have the wrong input or not?
    cerr << "Wrong number of arguments." << endl;
    return 1;
  }
  
  unsigned k = set_K(error, argv);
  double alpha = set_alpha(error,argv);
  ifstream file; Open_file(error, file, argv);          //If file can not be opened, throw exception.
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





