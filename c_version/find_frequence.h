void find_frequence(int parameters[],int freq,char* file){
     
     FILE *read;
     FILE *write;
     FILE *tmp;
     int i,j,f;
     char ch;
     char text_read[100];
     char text_write[100];
     
     read = fopen( file , "r" );
     tmp = fopen("temp.txt", "w+");    //proswrino arxeio--kataxwrish n-gram xwris diplotipa

     fgets(text_read,100,read);       //diavasma ths prwths grammhs tou arxeiou me ta n-grams
     fprintf(tmp,"%s", text_read);    //ektupwsh ths grammhs sto prwsorino arxeio
     fseek(tmp,0,SEEK_SET);           //epistrofh sthn arxh tou proswrinou arxeiou
     
     while((fgets(text_read,100,read))!=NULL){   //diavasma grammh-grammh tou arxeiou me ta n-grams
                       f=0;
                       while((fgets(text_write,100,tmp))!=NULL){
                              if(strcmp(text_read,text_write)==0) {f++; break;}     //metrish ths suxnothtas tou n-gram mesa sto proswrino arxeio
                             memset(text_write, '\0', sizeof(text_write)); //eleutherosh ths mnhmhs pou desmeuse o pinakas text_write
                       }                                        
                    if (f==0) //an den uparxei sto proswrino arxeio tote ektupwsh mesa sto arxeio
                             fprintf(tmp,"%s", text_read);      
                    fseek(tmp,0,SEEK_SET);                              
     }
     
 fclose(read);
 fclose(tmp); 
 memset(text_write, '\0', sizeof(text_write));  //eleutherosh ths mnhmhs pou desmeuse o pinakas text_write
 memset(text_read, '\0', sizeof(text_read));  
     
     
     tmp = fopen("temp.txt", "r");
     read = fopen( file , "r" );
     write = fopen( "final.txt" , "w");  //prwsorino arxeio pou periexei tis suxnothtes

     while((fgets(text_write,100,tmp))!=NULL){
         f=0;
          while((fgets(text_read,100,read))!=NULL){
               if(strcmp(text_read,text_write)==0) {f++;}  //metrish suxnothtas emfanishs
                      memset(text_read, '\0', sizeof(text_read));
          }
          
          if(f>=parameters[1]){    //ean h suxnothta einai megaluterh h ish apo thn epilogh tou xrhsth 
                     i=0;
                     while(text_write[i]!='\n'){
                         fprintf(write,"%c", text_write[i]);  //ektupwsh tou n-gram
                         i++;
                     }       
              fprintf(write,"%d\n",f);    //ektupwsh ths suxnothtas tou n-gram
          }
          fseek(read,0,SEEK_SET);
       memset(text_write, '\0', sizeof(text_write));
       
       
     }
                
    memset(text_write, '\0', sizeof(text_write));             
     memset(text_read, '\0', sizeof(text_read));

fclose(write);
fclose(read);
fclose(tmp); 

remove("temp.txt");    //diagrafh tou prwsorinou prwtou arxeiou

write = fopen( file , "w" );
read = fopen( "final.txt" , "r");

while((ch=fgetc(read))!=EOF) {    //antigrafh tou periexomenou tou prwsorinou arxeiou me tis suxnothtes sto teliko
                                  //arxeio e3odou
                             fprintf(write,"%c",ch);
                             }
fclose(write);
fclose(read);

remove("final.txt");       //diagrafh tou prwsorinou prwtou arxeiou me tis suxnothtes twn n-gram               
}
