#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "help.h"
#include "word_n_grams.h"
#include "character_n_grams.h"
#include "character_n_grams_f.h"

//synarthsh pou epistrefei ton arithmo apo ta orismata
int get_number(char argv[]) {
int j;
int number=0;

j=2;         //metatroph tou string se integer
             while(argv[j]!='\0'){
                                  number = number * 10 + argv[j] - '0';
                             j++;
             }
 return number;
}

int main(int argc, char *argv[]) {

int parameters[3] = {0,1,1};   //arxikopoihsh twn parametrwn me tis default times
int i,j,par_n,num,c_par_w_par;
int valid=0;
int freq=0;
char check;
float total_time; //metavlhth gia to sunoliko xrono ekteleshs tou programmatos
char type='c';   //arxikopoihsh me thn default timh gia ti eidous n-gram theloume na kanoume

/* elegxos tou plithous twn orismatwn */ 
if (argc==2 && argv[1][0]=='-' && argv[1][1]=='h') {    //an to orisma einai -h kai mono auto
             help();
             exit(0); }
if (argc<=3){             //an ta orismata einai ligotera i isa apo treia tote den einai arketa
             printf("\nNot enought arguments. Type -h for help\n");
             exit(0); }

if (argc>7){               //an ta orismata einai perisotera apo 7 tote einai para polla
             printf("\nToo many arguments. Type -h for help\n");
             exit(0); }

/* elegxos egkurothtaw twn orismatwn */ 
for (i=1;i<argc;i++){       //euresh epilogwn pou ksekinane me "-"
       if(argv[i][0]=='-') valid++;
       }

for (i=1;i<argc-2;i++){       //otan uparxei epilogh xwris "-" tote emfanizei katallhlo mhnuma
       if(argv[i][0]!='-') {
                           printf("Wrong syntax in options input. Type -h for help\n");
                           exit(0);
                           }
       }

if (argc!=(valid+3)){      //elegxei an uparxei toso arxeio eisodou oso kai arxeio eksodou
                     printf("Missing input or output files. Type -h for help\n");
                     exit(0);
                     }
par_n=0;
c_par_w_par=0;

for (i=1;i<argc-2;i++){
      check=argv[i][1];
      valid=0;
      for (j=1;j<argc-2;j++){       //elegxos an uparxei kapoia epilogh parapanw apo mia fora
          if (argv[j][1]==check) valid++;
          if (argv[j][1]=='n') par_n=1;
          }
      if (valid>1) {
                        printf("One option is more than one time\n");
                        exit(0);
          }
       //emfanish katallhlou mhnumatos otan kapoia epilogh einai agnwsth
      if (!(argv[i][1]=='c' || argv[i][1]=='w' || argv[i][1]=='n' || argv[i][1]=='f' || argv[i][1]=='s')){
                            printf("Unknown parameter -%c.\n",argv[i][1]);
                            exit(0); }
      //emfanish lathous otan den uparxei h upoxrewtikh epilogh -n
      if (par_n==0) {
                    printf("Parameter -n is required. Type -h for help.\n");
                    exit(0);
                    }

      if (argv[i][1]=='c' || argv[i][1]=='w') c_par_w_par++;    //elegxos an uparxei -w kai -c tautoxrona

      if (argv[i][1]=='n' || argv[i][1]=='f' || argv[i][1]=='s'){
         if (argv[i][2]=='\0'){              //dipla apo kathe option prepei na uparxei kai enas arithmos
                               printf("Not a number in parameter -%c. Type -h for help.\n",argv[i][1]);
                               exit(0);
                               }
         j=2;
             while(argv[i][j]!='\0'){       //elegxos oti uparxei arithmos dipla apo ta option kai oxi kapoios allos xarakthras
                             num=isdigit(argv[i][j]);
                             if (num==0){
                                         printf("Not a number in parameter -%c. Type -h for help.\n",argv[i][1]);
                                         exit(0);
                                         }
                             j++;
             }
      }

     if (c_par_w_par==2){     //emfanish mhnumatos otan uparxei -w kai -c tautoxrona
                         printf("You can not use parameters -w -c at the same time. Type -h for help.\n");
                         exit(0);
                         }

}

/* decode parameters */ 
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
//epivevaiwsh dedomenwn sthn othonh tou xrhsth
printf("\nYou have selected %s %d-grams.\n",type=='w'?"word":"character",parameters[0]);
printf("Frequency of %d-grams >= %d\n",parameters[0],parameters[1]);
printf("Consecutive %d-grams: %d\n",parameters[0],parameters[2]);

/* get files' names */ 
printf("\nInput file: %s\n",argv[argc-2]);
printf("Output file: %s\n",argv[argc-1]);

if(type=='w')
total_time=word_n_grams(parameters,freq,argv[argc-2],argv[argc-1]); //sunarthsh gia thn kataskeuh word n-grams
else
if(freq)
total_time=character_n_grams_f(parameters,argv[argc-2],argv[argc-1]); 
else
total_time=character_n_grams(parameters,argv[argc-2],argv[argc-1]); //sunarthsh gia thn kataskeuh character n-grams

//ektupwsh sunolikou xronou ekteleshs
printf("Execution time: %.4f seconds\n",total_time);

return 0;
}

