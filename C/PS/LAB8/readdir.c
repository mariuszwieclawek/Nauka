#include        <dirent.h>
#include        <errno.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>



void listujPliki( const char * nazwa_sciezki ) {
    struct dirent * plik;
    DIR * sciezka;
   
    if(( sciezka = opendir( nazwa_sciezki ) ) ) {
        while(( plik = readdir( sciezka ) ) )
             puts( plik->d_name );
       
        closedir( sciezka );
    }
    else
         printf( "! wywo�uj�c funkcj� opendir(%s) pojawi� si� b��d otwarcia strumienia dla danej �cie�ki, mo�e nie istnieje, lub podano �cie�k� pust�\n", nazwa_sciezki );
   
}

int
main(int argc, char **argv)
{

	if (argc != 2){
		fprintf(stderr, "usage: %s <dir_path> \n", argv[0]);
		return 1;
	}
	listujPliki(argv[1]);
}