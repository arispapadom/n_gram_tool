void find_frequence(int parameters[],int freq,char* file){
     
    FILE *read;
    FILE *write;
    FILE *tmp;
    int i,j,f;
    char ch;
    char text_read[100];
    char text_write[100];
    
    read = fopen( file , "r" );
    tmp = fopen("temp.txt", "w+");    //temp file - insert unique n-grams
    fgets(text_read,100,read);       //read first line of file with n-grams
    fprintf(tmp,"%s", text_read);    //print to file first row
    fseek(tmp,0,SEEK_SET);           //return to the beggining of file
    
    while((fgets(text_read,100,read))!=NULL){   //read line by line
       f=0;
       while((fgets(text_write,100,tmp))!=NULL){
           if(strcmp(text_read,text_write)==0) {f++; break;}     //count n-gram frequency
           memset(text_write, '\0', sizeof(text_write));
                      }                                        
           if (f==0) //if not exist - add it
               fprintf(tmp,"%s", text_read);      
           fseek(tmp,0,SEEK_SET);                              
    }
     
    fclose(read);
    fclose(tmp); 
    memset(text_write, '\0', sizeof(text_write)); 
    memset(text_read, '\0', sizeof(text_read));  
     
     
    tmp = fopen("temp.txt", "r");
    read = fopen( file , "r" );
    write = fopen( "final.txt" , "w");  //temp file for frequencies

    while((fgets(text_write,100,tmp))!=NULL){
        f=0;
        while((fgets(text_read,100,read))!=NULL){
            if(strcmp(text_read,text_write)==0) {f++;}  //count frequency
                memset(text_read, '\0', sizeof(text_read));
        }
          
        if(f>=parameters[1]){    //if the frequency is equal or greater than "f" parameter
            i=0;
            while(text_write[i]!='\n'){
                fprintf(write,"%c", text_write[i]);  //print char of n-gram
                i++;
            }       
            fprintf(write,"%d\n",f);    //print n-gram's frequency
        }
        fseek(read,0,SEEK_SET);
        memset(text_write, '\0', sizeof(text_write));      
     }
                
    memset(text_write, '\0', sizeof(text_write));             
    memset(text_read, '\0', sizeof(text_read));

    fclose(write);
    fclose(read);
    fclose(tmp); 

    remove("temp.txt");    //delete temp file
    write = fopen( file , "w" );
    read = fopen( "final.txt" , "r");

    while((ch=fgetc(read))!=EOF) {    //copy content of 2nd temp file's to output file
        fprintf(write,"%c",ch);
    }

    fclose(write);
    fclose(read);

    remove("final.txt");       //temp 2nd temp file holding frequencies               
}
