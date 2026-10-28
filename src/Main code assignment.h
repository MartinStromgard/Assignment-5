# include <iostream>
# include <string>

using namespace std;

class k_gram {
  public:
  string text;
  k_gram(string TEXT);
};

class k_plus_1_gram {
  public:
  string text;
  k_plus_1_gram(string TEXT);
};

bool wrong_number_of_arguments(int argcount,char *arglist[]);     // A part of error checking in the beginning of the program.

double set_alpha(bool& error, char* LIST[]);      //Is used to extract the value of alpha from argv (if given any).

unsigned set_K(bool& ERROR, char* arglist[]);      //Is used to extract the value of k from argv.

string Text_from_file(bool& error, ifstream& FILE, unsigned K);        //Returns the whole text from a file into a single string.

int set_text_length(bool& ERROR, unsigned K,char* ARGV[]);    //Sets the length of the text the program is going to run (extracted from argv).

void add_letter_to_alphabet_vector(string letter,vector<string>& VECTOR);    //In the exercise you are supposed to generate characters that are already there in the file you read from. All those characters will be stored in a vector, and this function helps to collect the characters that are in the document.

map<string,unsigned> import_k_grams_into_map(unsigned K, string TOTAL_TEXT);

map<string,unsigned> import_k_plus_1_grams_into_map(unsigned K, string TOTAL_TEXT);

vector<string> Set_of_letters_used_in_file(string TOTAL_TEXT);

string Use_probability_distribution_to_generate_letter(vector<string> Alphabet,double ALPHA, string K_GRAM, map<string,unsigned> Map_of_K_GRAMS, map<string,unsigned> Map_of_K_plus_1_GRAMS);

string generate_first_k_gram_in_text(map<string,unsigned> Map_of_k_grams);

string generate_text(vector<string> Alphabet,map<string,unsigned> Map_of_k_grams,map<string,unsigned> Map_of_k_plus_1_grams, int text_length,double alpha);


