float character_n_grams_f(int parameters[],char* input,char* output){  
      
      FILE *input_file;
	    FILE *output_file;
	    int j,total,position,rows,columns,f,*fr,thesh,count=0;
      long int i;
      char **text,ch;
      char **final;
      char *check;
      int end,start,pointer;
      clock_t start_t,end_t;
      
      input_file = fopen( input , "r" );
      total=0;
      /* check if file exists */
      if (input_file==NULL){
        printf("\nFile %s does not exist.\n",input);
        exit(0);
      }else{ //if exists then create the output file
	      output_file=fopen(output,"w");
        /*count file's input chars*/
	      while((ch=getc(input_file))!=EOF){
          if(ch!='\n') total++;     
        }
      }


      rows=total-parameters[0]-parameters[2]+2;
      columns=parameters[2]*parameters[0];


	  fseek(input_file,0,SEEK_SET); //pointer goes back to the beginning
       
	
    text=malloc(parameters[2]*sizeof(char*));
    //allocate memory according to "n" parameter
    for(i=0;i<parameters[2];i++)
      text[i]=malloc(parameters[0]*sizeof(char));

    //dhnamikh desmeush mnhmhs gia apothikeush twn ngrams
    final=malloc(rows*sizeof(char*));
	  fr=malloc(rows*sizeof(int));
    //final -> save final char n-grams
    for(i=0;i<rows;i++){
      final[i]=malloc(columns*sizeof(char));
    }

    check=malloc(parameters[0]*parameters[2]*sizeof(char));	

    start_t=clock();


		for(j=0;j<parameters[0];j++){   //insert first n-gram to text table
      ch=fgetc(input_file);
      while(ch=='\n'){
		    ch=fgetc(input_file);        
      }
			if(ch==' ') ch='_';
        text[0][j]=ch;
    }

    //insert next s-1 n-grams to the next s-1 rows of table "text"   
    for(i=0;i<parameters[2]-1;i++){  
      for(j=0;j<parameters[0]-1;j++){
        text[i+1][j]=text[i][j+1];
      }
      text[i+1][j]=fgetc(input_file);
	    if (text[i+1][j]==' ') text[i+1][j]='_';    
    }  
	    
	  position=0;
	  for(i=0;i<parameters[2];i++){  
      for(j=0;j<parameters[0];j++){
        final[0][position]=text[i][j];
		    position++;
      }       
    }  
  
    fr[0]=1;  
    thesh=1;
    end=total=1;

	  while ((ch=fgetc(input_file))!='\0') { 
		  while(ch=='\n'){
		    ch=fgetc(input_file);
      }
      if(ch==EOF || total==(rows-1)) break;
      //replace space character with "_"
      for(i=0;i<parameters[2];i++){
        for(j=0;j<parameters[0];j++){
          if(text[i][j]==' ')
            text[i][j]='_';
          }
      }       
        
      //move all n-grams up by one
      for(i=0;i<parameters[2]-1;i++){
        for(j=0;j<parameters[0];j++){
          text[i][j]=text[i+1][j];                
        }              
      }
      //shift one position left for the last n-gram
      for(j=0;j<parameters[0]-1;j++)
        text[parameters[2]-1][j]=text[parameters[2]-1][j+1];
        //insert the new character to the far right position of last n-gram
	      if(ch==' ') ch='_';
          text[parameters[2]-1][parameters[0]-1]=ch;
       		
      strcpy(check,text[0]);
      for (i=1;i<parameters[2];i++){
      strcat(check,text[i]);
      }

      for(i=0;i<thesh+1;i++){
        if(!strcmp(check,final[i])) {fr[i]++; break;}
        if(i==thesh) {
          thesh++;
          strcpy(final[i],check);
          fr[i]=1;
          break;
        }
      }	

      printf("%d of %d completed\n",total+1,rows-1);
                    total++;

	  }


	  for(i=0;i<thesh;i++){
		  if(fr[i]>=parameters[1])
		  fprintf(output_file,"%s %d\n",final[i],fr[i]);	
	  }

    memset(text, '\0', sizeof(text));
    memset(final, '\0', sizeof(final));      
      
    end_t=clock();
      
    return (float)(end_t - start_t) / CLOCKS_PER_SEC;

      
}
