
/* BIN2C V1.0 CODED BY CHRISTIAN PADOVANO ON 17-MAY-1995

   this little utility translates a binary file in a useful C structure
   that can be included in a C source.

   to contact me write to EMAIL: Christian_Padovano@amp.flashnet.it
*/


#include <stdio.h>
#include <string.h>

#define BUF_LEN 1
#define LINE     12

/* Tell u the file size in bytes */

long int filesize( FILE *fp )
  {
    long int save_pos, size_of_file;

    save_pos = ftell( fp );
    fseek( fp, 0L, SEEK_END );
    size_of_file = ftell( fp );
    fseek( fp, save_pos, SEEK_SET );
    return( size_of_file );
  }


/* lower chars --> upper chars */

void Upper_chars(char *buffer)
{
 unsigned int c;

 for (c=0; c <= strlen(buffer)-1; c++) *(buffer+c)=toupper( *(buffer+c) );
}


void main( argc, argv )
int argc;
char *argv[];
{
    FILE *source,*dest;
    unsigned char buffer[BUF_LEN], Dummy[20];
    int c;

    if ( (argc < 4) )
    {

     if (  ( argc == 2 ) && ( strcmp(argv[1],"/?")==0 )  )
     {
      puts(" - <<< BIN2C V1.0 >>> by Christian Padovano - \n");
      puts("USAGE: Bin2C  <BINARY file name> <TARGET file name> <STRUCT name>");
      puts("\n <STRUCT > = name of the C structure in the destination file name.\n");
      puts("  <TARGET > = without extension '.h' it will be added by program.");
      exit(0L);
     }
     else
     {
      puts("Bad arguments !!! You must give me all the parameters !!!!\n"
           "Type 'BIN2C /?' to read the help !!!! ");
      exit(0L);
     }

    }

    if( (source=fopen( argv[1], "rb" )) == NULL )
    {
      printf("ERROR : I can't find source file   %s\n",argv[1]);
      exit(20L);
    }

    strcpy(Dummy,argv[2]);
    strcat(Dummy,".h");               /* add suffix .h to target name */

    if( (dest=fopen( Dummy, "wb+" )) == NULL )
    {
      printf("ERROR : I can't open destination file   %s\n",Dummy);
      (void)fcloseall();
      exit(20L);
    }


    strcpy(Dummy,argv[3]);
    Upper_chars(Dummy);  /* lower to upper chars */
    strcat(Dummy,"_LEN");  /* add the suffix _LEN to the struct name */
                           /* for the #define stantment              */


    /* It writes the header information */
    fprintf( dest, "\n#define %s %ld\n\n", Dummy, filesize(source) );
    fprintf( dest, " static unsigned char %s[]=\n {\n  ", argv[3] );

    if( ferror( dest ) )
    {
     printf( "ERROR writing on target file:  %s\n",argv[2] );
     (void)fcloseall();
     exit(20L);
    }

    do
    {
     for ( c=0; ((c <= LINE) && (! feof( source ) )) ; c++)
     {
      fread( buffer, 1, 1, source );
      if (! feof( source ) ) fprintf(dest,"0x%02x,",*buffer);
      else fprintf(dest,"0x%02x",*buffer);
     }
     fprintf(dest,"\n  ");
    }
    while( ! feof( source ) );

    fprintf(dest,"};\n\n");

    (void)fcloseall();

}



