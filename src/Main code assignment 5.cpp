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
# include <vector>
# include "main classes.h"

using namespace std;

class k_gram {
  public:
  string text;
  map<string,int> Probability_distribution;
  k_gram(string TEXT): text(TEXT){};

}
class k_plus_1_gram : public k_gram {
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
string Text_from_file(bool& error, ifstream& FILE, unsigned K){
  string string_to_import;
  string imported_word;
  while (FILE>>imported_word){
    string_to_import.append(imported_word);
    string_to_import.append("_");
  }
  if (size(string_to_import)<K){
    cerr << "The textfile must be larger than the given k." << endl;
    error = true;
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

void add_letter_to_alphabet_vector(string letter,vector<string>& VECTOR){
  auto it = find(VECTOR.begin(),VECTOR.end(),letter);
  if (it!=VECTOR.end()){
    VECTOR.push_back(letter);
  }
}

map<string,unsigned> import_k_grams_into_map(unsigned K, string TOTAL_TEXT){
  string text_to_insert_into_k_gram = "";
  map<string,unsigned> Map_of_k_grams;
  for (int j = 0; j! = K; ++j){
    text_to_insert_into_k_gram += TOTAL_TEXT[j];
  }
  k_gram K_G(text_to_insert_into_k_gram);
  
  for (int i = k; i != size(Total_text);++i){
    Map_of_k_grams[K_G.text] += 1;
    text_to_insert_into_k_gram += Total_text[i];
    text_to_insert_into_k_gram.erase(0,1);
    k_gram K_G(text_to_insert_into_k_gram);
  }
  return Map_of_k_grams;
  
}

map<string,unsigned> import_k_plus_1_grams_into_map(unsigned K, string TOTAL_TEXT)
  string text_to_insert_into_k_plus_1_gram = "";
  map<string,unsigned> Map_of_k_plus_1_grams;
  for (int j = 0; j! = K+1; ++j){
    text_to_insert_into_k_plus_1_gram += TOTAL_TEXT[j];
  }
  k_plus_1_gram K_P_1_G(text_to_insert_into_k_plus_1_gram);
  
  for (int i = k+1; i != size(Total_text);++i){
    Map_of_k_plus_1_grams[K_P_1_G.text] += 1;
    text_to_insert_into_k_plus_1_gram += Total_text[i];
    text_to_insert_into_k_plus_1_gram.erase(0,1);
    k_plus_1_gram K_P_1_G(text_to_insert_into_k_plus_1_gram);
  }
  return Map_of_k_plus_1_grams;
  
}

vector<string> Set_of_letters_used_in_file(string TOTAL_TEXT){
  vector<string> Alphabet_used_in_textfile;
  for (int i=0; i!=size(TOTAL_TEXT);++i){
    auto it = find(Alphabet_used_in_textfile.begin(),Alphabet_used_in_textfile.end(),TOTAL_TEXT[i]);
    if (it == Alphabet_used_in_textfile.end()){
      Alphabet_used_in_textfile.push_back(TOTAL_TEXT[i]);
    }
  }
  return Alphabet_used_in_textfile;
}

string Use_probability_distribution_to_generate_letter(vector<string> Alphabet,double ALPHA, string K_GRAM, map<string,unsigned> Map_of_K_GRAMS, map<string,unsigned> Map_of_K_plus_1_GRAMS){
  //Shall depend on alpha.
  vector<double> Probabilities;
  for (auto i: Alphabet){
    string K_plus_1_string = K_GRAM + i;
    unsigned number_of_K_plus_1_grams = Map_of_K_plus_1_GRAMS[K_plus_1_string];
    unsigned number_of_K_grams = Map_of_K_GRAMS[K_GRAM];
    Probabilities.push_back((number_of_K_plus_1_grams + ALPHA)/(number_of_K_grams + APLHA*size(Alphabet)));
  }
  random_device rd;
  mt19937 gen(rd());
  discrete_distribution<> dist(Probabilities.begin(),Probabilities.end());
  int index = dist(gen);
  return Alphabet[index];
}  

string generate_first_k_gram_in_text(map<string,unsigned> Map_of_k_grams){
  random_device rd;
  mt19937 gen(rd());
  uniform_distribution<size_t> random_K = dist(0,Map_of_k_grams.size()-1);
  size_t random_K = dist(gen);
  auto it = Map_of_k_grams.begin();
  advance(it,random_K);
  return it->first;
}

string generate_text(vector<string> Alphabet,map<string,unsigned> Map_of_k_grams,map<string,unsigned> Map_of_k_plus_1_grams, int text_length,double alpha);
  string k_gram = generate_first_k_gram_in_text(Map_of_k_grams);
  string text_to_output = k_gram;
  while (size(text_to_output)!=text_length){
    string letter_to_add = Use_probability_distribution_to_generate_letter(Alphabet,alpha, k_gram, Map_of_k_grams, Map_of_K_plus_1_grams)
    text_to_output += letter_to_add;
    k_gram += letter_to_add;
    k_gram.erase(0,1);
  }
  return text_to_output;
  

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
  string Total_text = Text_from_file(error,file,k);          //If length of Total_text is lower than k, there will be an exception.
  if (error == true){
    return 1;
  }
  map<string,unsigned> Map_of_k_grams = import_k_grams_into_map(k, Total_text);
  map<string,unsigned> Map_of_k_plus_1_grams = import_k_plus_1_grams_into_map(k, Total_text);
  vector<string> Alphabet_in_text_file = Set_of_letters_used_in_file(Total_text);

  string final_string_result = generate_text(Map_of_k_grams,Map_of_k_plus_1_grams,set_text_length);
  cout << final_string_result << endl;
  
  //If -a is given, the number af alpha will be the first argument.
  //argv[1] is k (the length of the "gram")
  //argv[2] is the name of the text file that is used to train the model.
  //argv[3] is an integer that decides how many characters to output.

  //For example: slm -a 0.01 3 moby_dick.txt 40.
  //or slm 2 moby_dick.txt 5
  
}



