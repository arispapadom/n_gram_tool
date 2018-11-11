/*This function prints informations about the program   */


void help() {
     printf("\n");
     printf("N-grams tool V1.0 : N-grams construction tool\n");
     printf("\nCopyright: Aristeidis Papadomanolakis, papadomano@ceid.upatras.gr\n"); 
     printf("\nThis software is available for non-commercial use only.\n"); 
     printf("It must not be modified and distributed without prior permission\n");
     printf("of the author. The author is not responsible for implications from\n");
     printf("the use of this software.\n");
     
     printf("\n usage: n-grams-tool [options] input_file output_file\n");
     
     printf("\noptions: \n");
     
     printf("\t option1: -w \t constuction of word n-grams\n");
     printf("\t          -c \t constuction of character n-grams\n");
     printf("\t   default: -c\n");
     
     printf("\n\t option2: -n[number] \t constuction of [number]-grams\n");
     printf("\t   parameter required\n");
     
     printf("\n\t option3: -f[number] \t output n-grams with frequency >= [number]\n");
     printf("\t   default: if parameter does not exist all n-grams are produced\n");
     
     printf("\n\t option4: -s[number] \t manage [number] consecutive n-grams\n");
     printf("\t   default: -s1\n");
     
     printf("\nArguments:\n");
     printf("\t input_file -> file you want to transform in n-grams\n");  
     printf("\t output_file -> file you want to save the output n-grams\n");
     }
