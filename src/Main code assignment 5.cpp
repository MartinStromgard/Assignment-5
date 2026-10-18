# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <random>
# include <cstdlib> //for the strtod function.
# include <stdexcept>
# include <vector>
# include "Main code assignment.h"

using namespace std;

k_gram::k_gram(string TEXT): text(TEXT){};

k_plus_1_gram::k_plus_1_gram(string TEXT): text(TEXT){};

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
  if (argcount != 4){
    return true;
  }
  return false;
}

double set_alpha(bool& error, char* LIST[]){
  string First_argument = LIST[1];
  double alpha;
  if (First_argument == "-a"){
    char* endPtr;
    alpha = strtod(LIST[2],&endPtr);
    if (alpha <= 0){
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
  int alpha_is_given;
  if (First_argument == "-a"){
    alpha_is_given = 2;
  } else {
    alpha_is_given = 0;
  }
  double K_d;
  try {
    K_d = stod(arglist[alpha_is_given+1]);
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

string Text_from_file(bool& error, ifstream& FILE, unsigned K){
  string string_to_import;
  string imported_word;
  while (FILE>>imported_word){
    string_to_import.append(imported_word);
    string_to_import.append("_");
  }
  string_to_import.erase(string_to_import.end()-1);
  if (size(string_to_import)<K){
    cerr << "The textfile must be larger than the given k." << endl;
    error = true;
  }
  return string_to_import;
}

int set_text_length(bool& ERROR, unsigned K,char* ARGV[]){
  int text_length = 0;
  int text_length2 = 0;
  int alpha_is_given;
  string First_argument = ARGV[1];
  if (First_argument == "-a"){
    alpha_is_given = 2;
  } else {
    alpha_is_given = 0;
  }
  try {
    text_length = stoi(ARGV[alpha_is_given+3]);
    text_length2 = stod(ARGV[alpha_is_given+3]);
    if (text_length < K||text_length!=text_length2){
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
  bool Found_character = false;
    for (int i=0;i!=size(VECTOR);++i){
        if (VECTOR[i]==letter){
            Found_character = true;
            break;
        }
    }
    if (Found_character==false){
        VECTOR.push_back(letter);
    }
}

map<string,unsigned> import_k_grams_into_map(unsigned K, string TOTAL_TEXT){
  string text_to_insert_into_k_gram = "";
  map<string,unsigned> Map_of_k_grams;
  for (int j = 0; j != K; ++j){
    text_to_insert_into_k_gram += TOTAL_TEXT[j];
  }
  
  for (int i = K; i != size(TOTAL_TEXT);++i){
      Map_of_k_grams[text_to_insert_into_k_gram] += 1;
      text_to_insert_into_k_gram += TOTAL_TEXT[i];
      text_to_insert_into_k_gram.erase(0,1);
  }
  return Map_of_k_grams;
}

map<string,unsigned> import_k_plus_1_grams_into_map(unsigned K, string TOTAL_TEXT){
  string text_to_insert_into_k_plus_1_gram = "";
  map<string,unsigned> Map_of_k_plus_1_grams;
  for (int j = 0; j != K+1; ++j){
    text_to_insert_into_k_plus_1_gram += TOTAL_TEXT[j];
  }
  for (int i = K+1; i != size(TOTAL_TEXT);++i){
    Map_of_k_plus_1_grams[text_to_insert_into_k_plus_1_gram] += 1;
    text_to_insert_into_k_plus_1_gram += TOTAL_TEXT[i];
    text_to_insert_into_k_plus_1_gram.erase(0,1);
  }
  return Map_of_k_plus_1_grams;
  
}

vector<string> Set_of_letters_used_in_file(string TOTAL_TEXT){
  vector<string> Alphabet_used_in_textfile;
  for (int i=0; i!=size(TOTAL_TEXT);++i){
    string character(1,TOTAL_TEXT[i]);
    add_letter_to_alphabet_vector(character,Alphabet_used_in_textfile);
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
    Probabilities.push_back((number_of_K_plus_1_grams + ALPHA)/(number_of_K_grams + ALPHA*size(Alphabet)));
  }
  random_device rd;
  mt19937 gen(rd());
  discrete_distribution<> dist(Probabilities.begin(),Probabilities.end());
  int index = dist(gen);
  return Alphabet[index];
}  

string generate_first_k_gram_in_text(map<string,unsigned> Map_of_k_grams){
  random_device rd;
  mt19937 generator(rd());
  uniform_int_distribution<int> distribution(0,size(Map_of_k_grams)-1);
  int random_K = distribution(generator);
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
  

