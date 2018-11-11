#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "help.h"
#include "word_n_grams.h"
#include "character_n_grams.h"
#include "character_n_grams_f.h"

//function to get the number of each argument
int get_number(char argv[]) {
    int j;
    int number=0;

    j=2;         //string to integer according ASCII table
    while(argv[j]!='\0'){
        number = number * 10 + argv[j] - '0';
        j++;
    }
    return number;
}

int main(int argc, char *argv[]) {

    //initialize parameters with default values
    int parameters[3] = {0,1,1};   
    int i,j,par_n,num,c_par_w_par;
    int valid=0;
    int freq=0;
    char check;
    float total_time; //total execution time of program
    char type='c';   //character n-grams as default

    /* validation of arguments */ 
    if (argc==2 && argv[1][0]=='-' && argv[1][1]=='h') {
        help();
        exit(0); }
    if (argc<=3){          
        printf("\nNot enought arguments. Type -h for help\n");
        exit(0); }

    if (argc>7){          
        printf("\nToo many arguments. Type -h for help\n");
        exit(0); }

     
    for (i=1;i<argc;i++){       //find arguments starting with "-"
        if(argv[i][0]=='-') valid++;
    }

    for (i=1;i<argc-2;i++){       //in case of argument without "-"
        if(argv[i][0]!='-') {
            printf("Wrong syntax in options input. Type -h for help\n");
            exit(0);
        }
    }

    if (argc!=(valid+3)){      //check for input and output files
        printf("Missing input or output files. Type -h for help\n");
        exit(0);
    }

    par_n=0;
    c_par_w_par=0;

    for (i=1;i<argc-2;i++){     //parse all arguments
        check=argv[i][1];
        valid=0;
        for (j=1;j<argc-2;j++){       //check for duplicate arguments
            if (argv[j][1]==check) valid++;
            if (argv[j][1]=='n') par_n=1;
        }
        if (valid>1) {
            printf("One option is more than one time\n");
            exit(0);
        }

        //in case of unknown argument
        if (!(argv[i][1]=='c' || argv[i][1]=='w' || argv[i][1]=='n' || argv[i][1]=='f' || argv[i][1]=='s')){
                printf("Unknown parameter -%c.\n",argv[i][1]);
                exit(0); }

        //argument n is mandatory
        if (par_n==0) {
            printf("Parameter -n is required. Type -h for help.\n");
            exit(0);
        }

        if (argv[i][1]=='c' || argv[i][1]=='w') c_par_w_par++;    //if -c and -w co-exist

        if (argv[i][1]=='n' || argv[i][1]=='f' || argv[i][1]=='s'){
            if (argv[i][2]=='\0'){              //one number must exist next to each option
                printf("Not a number in parameter -%c. Type -h for help.\n",argv[i][1]);
                exit(0);
            }
            j=2;
            while(argv[i][j]!='\0'){       //check that it's a number - not a char 
                num=isdigit(argv[i][j]);
                if (num==0){
                    printf("Not a number in parameter -%c. Type -h for help.\n",argv[i][1]);
                        exit(0);
                }
                j++;
            }
        }

        if (c_par_w_par==2){     //-c and -w do co-exist
            printf("You can not use parameters -w -c at the same time. Type -h for help.\n");
            exit(0);
        }

    }

    /* decode parameters - get number of each argument */ 
    for (i=1;i<argc-2;i++){
        if(argv[i][1]=='w') type='w';
        if(argv[i][1]=='n'){
        parameters[0]=get_number(argv[i]);
        }
        if(argv[i][1]=='f'){
        parameters[1]=get_number(argv[i]);
        freq=1;
        }
        if(argv[i][1]=='s'){
        parameters[2]=get_number(argv[i]);
        }
    }

    //print input info to user
    printf("\nYou have selected %s %d-grams.\n",type=='w'?"word":"character",parameters[0]);
    printf("Frequency of %d-grams >= %d\n",parameters[0],parameters[1]);
    printf("Consecutive %d-grams: %d\n",parameters[0],parameters[2]);

    /* get files' names */ 
    printf("\nInput file: %s\n",argv[argc-2]);
    printf("Output file: %s\n",argv[argc-1]);

    if(type=='w')
        total_time=word_n_grams(parameters,freq,argv[argc-2],argv[argc-1]); //extract word n-grams
    else
        if(freq)
            total_time=character_n_grams_f(parameters,argv[argc-2],argv[argc-1]); 
        else
            total_time=character_n_grams(parameters,argv[argc-2],argv[argc-1]); //extract character n-grams

    //print execution time
    printf("Execution time: %.4f seconds\n",total_time);

    return 0;
}

