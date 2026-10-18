//Readme file

This program is supposed to be a slm model (small language model), a model that, with text input training, generates text. You run the program in the command line, and you either give 3 or 5 arguments depending on what you would like to do. The program works like this: It reads a textfile and stores the text inside the program. From there, it reads all the pairs of "k" letters. For example: In a textfile with the text "Hey_there", the pairs with three letters are: "Hey", "ey_", "y_t", "_th", "the", "her", "ere", and the pairs with four letters are: "Hey_", "ey_t", "y_th", "_the", "ther", "here", and so on. From this input, the program generates text randomly, but with a probability distribution that depends on the text file you train the program with. In the command line you specify the value of k, which file to read text from and how long the generated text should be. If you would like to, you can also specify a value alpha in the beginning. The alpha makes the letter generation more random than without alpha.

Basically, the command line input should be on either of these two forms:

1)   ./slm -a alpha k file.txt length_of_text

2)   ./slm k file.txt length_of_text

where alpha is a double larger than 0 (if -a is written, otherwise it is set to zero), k is a integer larger than or equal to 1, file.txt is a name of a textfile (you have to write the name of the file correctly, and whether it is written correctly or not depends on where this textfile is located) and length_of_text is an integer larger than k.

In order to run the program, you simply download the zip-file, open it with the command prompt, type "make" and afterwards you type the command on one of the two forms stated above.





