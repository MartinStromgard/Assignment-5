# include <iostream>

class {
}

class {
}
bool wrong_number_of_arguments(int argcount,char *arglist[])     // A part of error checking in the beginning of the program.

double set_alpha(bool& error, char* LIST[])      //Is used to extract the value of alpha from argv (if given any).

unsigned set_K(bool& ERROR, char* arglist[])      //Is used to extract the value of k from argv.

void Open_file(bool& ERROR, ifstream& FILE, char* LIST[])    //Opens the file written in command input into FILE.

string Text_from_file(ifstream& FILE)        //Returns the whole text from a file into a single string.

int set_text_length(bool& ERROR, unsigned K,char* ARGV[])    //Sets the length of the text the program is going to run (extracted from argv).
