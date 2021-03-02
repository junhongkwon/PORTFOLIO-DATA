#include <stdio.h>

#include <unistd.h>

#include <string.h>

#include <sys/wait.h>



int forkexec() {

    int n=0, status;

    char buf[256];

    char *argv[100];

    char *ptr=buf;

    int length, i;

    while(1)

    {

    printf("\nmysh>");



    fgets(buf, sizeof(buf), stdin);

    buf[strlen(buf)-1]='\0';

    if ( !strcmp( buf, "exit" ) )

         {

           printf("Bye\n");

           return 0;

         }



        n=0;

        ptr=buf;

        argv[n]=ptr;

        length=strlen(argv[0]);

       (argv[0])[length]='\0';



    while(*ptr!='\0' && n<100)

      {

       if( *ptr==' ' )

       {

            n++;

          *ptr='\0';

           argv[n]=ptr+1;

           length=strlen(argv[n]);

          (argv[n])[length]='\0';

       }

        ptr++;

      }

      

      argv[n+1]=NULL;



           //for( i=0; argv[i]!=NULL; i++)

            //printf("%s\n", argv[i]);

     







      int j=fork();

      if( j==0 )

      {

       if(execvp(argv[0], argv)==-1);

          printf("Error Message");

          return 0;

      }

      else

      {

        wait(&status);

      }   

}         

}

int main()

{

  forkexec();

}       
