#include "find_frequence.h"


float word_n_grams(int parameters[],int freq,char* input,char* output){    //e3agwgh n-gram le3ewn
      
      FILE *input_file;
	  FILE *output_file;
	  
	  int ngrams=parameters[0]*parameters[2];
	  int i,j,space,next,count,sum;
      clock_t start,end;
	  char *text,ch;
	  
	  input_file = fopen( input , "r" );
	  
	  /* check if file exists */
	  if (input_file==NULL){
           printf("\nFile %s does not exist.\n",input);
           exit(0);
      }else //if exists then create the output file
	       output_file=fopen(output,"w");
	   
	   j=0;i=0;
	   
       start=clock();  //enar3h xronometrith
	   //metrame tous xarakthres tou keimenou
	   while(ch=fgetc(input_file)!=EOF){
                                        j++;
                                       }
                                       
	   text=malloc(j*sizeof(char)); //dunamikh desmeush mnhmhs megethous osoi kai oi xarakthres tu keimenou
	   fseek(input_file,0,SEEK_SET);  //epistrofh sthn arxh tou arxeiou eisodou
       
	   while((ch=fgetc(input_file))!=EOF){   //kataxwrhsh tou keimenou ston pinaka text
              text[i]=ch;                       
              i++;
       }
       
       space=0;
       i=0; count=0; sum=0;
       while(i<j){     //prospelash tou pinaka text
                       if(text[i]==' ' || text[i]=='\n') {space++; count++;}
                       while(text[i]=='\n' || text[i]==' '){ i++;  }    //metatophsh tou deikth se xarakthra tou keimenou se xarakthra !="\n" && !=" "
                       if(space==1) { next=i; space++; } //molis entopistei to prwto keno diasthma kratame thn epomenh thesh
                                                           //pou ksekinaei h leksh
                        if(text[i-1]=='\n' || text[i-1]==' ')
                                  fprintf(output_file, " ");
                         if(i==j) break; 
                        if(count==ngrams){                 //an plhrountai oi proupotheseis twn epilogwn tou xrhsth ksekinaei h 
                                                           //h ektupwsh neou n-gram
                               space=0; 
                               count=0;
                               sum++;
                               fprintf(output_file,"\n"); //epomeno n-gram
                               i=next; //epomenh thesh pou tha ksekinhsei h ektupwsh sto keimeno
                        }  
                            
                fprintf(output_file, "%c", text[i]);  //ektupwsh kathe xarakthra n-gram
                i++;
       }
       
       fprintf(output_file, "\n");
       
      fclose(input_file);
      fclose(output_file);
      memset(text, '\0', sizeof(text));      //eleutherosh ths mnhmhs pou desmeuse o pinakas text
      
      if(freq)
      find_frequence(parameters,freq,output);  //euresh suxnothtwn n-grams
      
      end=clock();
      
      printf("\n%d word %d-grams created\n",sum+1,parameters[0]);
      return (float)(end - start) / CLOCKS_PER_SEC;
      }
