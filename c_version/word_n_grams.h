#include "find_frequence.h"


float word_n_grams(int parameters[],int freq,char* input,char* output){    
      
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
	   
       start=clock();  //start timer
	   //count all file's chars - after this the pointer shows at the end of file
	   while(ch=fgetc(input_file)!=EOF){
            j++;
        }
                                       
	   text=malloc(j*sizeof(char)); 
	   fseek(input_file,0,SEEK_SET);  //reutn back to the beggining
       
	   while((ch=fgetc(input_file))!=EOF){   //copy input file's content to a table
            text[i]=ch;                       
            i++;
       }
       
       space=0;
       i=0; count=0; sum=0;
       while(i<j){     //parse table
            if(text[i]==' ' || text[i]=='\n') {space++; count++;}
            while(text[i]=='\n' || text[i]==' '){ i++;  }    //pointer's offset till char !="\n" && !=" " 
            if(space==1) { next=i; space++; } //keep the position of next space character
                                                           //and a new word starts
            if(text[i-1]=='\n' || text[i-1]==' ')
                fprintf(output_file, " ");
            if(i==j) break; 
            if(count==ngrams){                 //if the n-gram has reached "n" parameter 
                space=0; 
                count=0;
                sum++;
                fprintf(output_file,"\n"); //new line for the next n-gram
                i=next; 
            }  
                            
            fprintf(output_file, "%c", text[i]);  //print each character of word
            i++;
       }
       
       fprintf(output_file, "\n");
       
      fclose(input_file);
      fclose(output_file);
      memset(text, '\0', sizeof(text));
      
      if(freq)
      find_frequence(parameters,freq,output);  //find frequencies
      
      end=clock();
      
      printf("\n%d word %d-grams created\n",sum+1,parameters[0]);
      return (float)(end - start) / CLOCKS_PER_SEC;
      }
