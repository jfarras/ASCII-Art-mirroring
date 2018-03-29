/**
 * @mainpage
 * @author: Jordi Farràs
 * @author: Marc tula.
 * @date: 30/11/12
 */

#include <ctype.h>
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
/**
 *  La funció, llegirà el fitxer, demanarà memória per la matriu i l'omplirà segons les dades del fitxer.
 * @param: Aquesta funció rep dos enters per referècia que s'ompliran amb els valors de les columnes i files màximes.
 * @return: La funció retorna char**, la matriu omplerta.
 *
 */



char** tractafitxer(int* colum,int * files,char* fileentry){


	char **m;
	FILE *f;
	char linea[500];
    int ok=1;
    int columnes,i, j, k,w;

    *files=1;
    *colum=1,
    f = fopen(fileentry ,"r");
    if ( f == NULL){
    	printf("Error al obrir fitxer !\n");
    }else {
    	fgets (linea ,500, f );
    	linea[strlen(linea)-1]='\0';
    	//printf( "holafitxer\n");
    	while ( !feof(f)){
    		columnes = strlen (linea);
    		if ( *colum< columnes){
    			*colum = columnes;
    		}
    		*files= *(files)+1;
    		fgets (linea ,500, f );
    		linea[strlen(linea)-1]='\0';

    	}
    	//printf("Surt bucle 1");
    	//printf("FILES %d COLUM %d",*files,*colum);
    	m = (char**)malloc(*(files) *sizeof(char*));
    	if(m == NULL){
    		printf("Error MEM !\n");
    	}
    	else{
    		for (i=0 ;i<*(files) && ok;i++){
    			m[i] = (char*)malloc(*(colum)*sizeof(char));
    			if (m[i] == NULL){
    				printf("Error de mem!\n");
    				ok= 0;
    				for(j=i;j>=0;--j){
    					free(m[j]);
    				}
    			free (m);
    			}
    		 }
    	}
    	fclose(f);
    	i = 0;
    	j = 0;
        f = fopen(fileentry ,"r");
        if ( f == NULL){
        	printf("Error al obrir fitxer !\n");
        }else {
        	fgets (linea ,500, f );
        	linea[strlen(linea)-1]='\0';
        	//printf("linea %s\n",linea);
        	while(!feof(f)){
        			//printf("\n OMPLU\n");
        			for(w = 0;w<*colum;++w){
        				m[i][w]= ' ';
        			}
        			strcpy(m[i],linea);
        			//printf("\n\nfila matriu: %s\n\n",m[i]);
        			i++;
            		fgets (linea ,500, f );
            		linea[strlen(linea)-1]='\0';
            		//printf("linea %s\n",linea);
            		if (feof(f)){
            			//printf("\n OMPLU\n");
                		//printf("linea ultima linea %s\n",linea);

            			for( w = 0;w<*colum;++w){
            				m[i][w]= ' ';
            			}
            			strcpy(m[i],linea);
            			//printf("\n\nFila matriu: %s\n\n",m[i]);
            		}
        		}
        	fclose(f);

        	}


        	printf("\nMatriu original\n");
    		for (j=0;j<*files-1;j++){
    			for(k=0;k<*colum;k++){
    				printf("%c",m[j][k]);
    			}
    			printf("\n");
    		}

    	 }

    	return m;
 }


     /**
      *  Aquesta funció, rebrà la matriu i farà el flip horitzontal
      * @param: Com a paràmetres, es rep la matriu ( char**) i dos enters que farem servir per anar-la recorrent. A més
      * rebrà un enter que marcarà les files màximes.
      * @return: La funció retorna la matriu girada horitzontalment.
      *
      */

char** fliphoritzontal(char **m, int i, int j,int filesmax){

	char aux;
    int q;
    //printf("\entrorec%d\n:",filesmax);
    if(i>=j){
    	return m ;
    }else{
    	for (q=0; q<filesmax ; q++){
    		aux = m[q][i];
    	    //printf("\ncar%c\n:",m[q][i]);
    		m[q][i] = m[q][j];
    		m[q][j] = aux;

    	}
		//printf("\n %s\n",m[0]);
    	return fliphoritzontal(m,i+1,j-1,filesmax);
    }
}


char** fliphoritzontalit(char** m,int zi,int zj,int filesmax){
	char aux;
	int q;
	for(zi=0;zi<zj;zi++){
		for(q=0;q<filesmax;q++){
			aux=m[q][zi];
			m[q][zi]=m[q][zj];
			m[q][zj]=aux;

		}
		zj--;
	}
	return m;

	}




char**flipverticalit(char **m,int zi,int zj,int columnesmax){
	char aux;
	int q=0;

	for(zi=0;zi<zj;zi++){
		for(q=0;q<columnesmax;q++){
			printf("ENTROREC\n");
			aux=m[zi][q];
			m[zi][q]=m[zj][q];
			m[zj][q]=aux;

		}
		zj--;
	}
	return m;

}

/**
 * Aquesta funció farà el flip vertical de la matriu original.
 * @param:com a paràmetres es rep, la matriu (char**) i dos enters per anar-la recorrent. A més, es rep un enter que marcarà
 * les columnes màximes.
 * @return: La funció retorna la matriu girada verticalment.
 */

char** flipvertical (char**m, int i, int j,int columnesmax){
   char aux;
   int q=0;

    printf("\n rec ver\n");
    printf("\nJ: %d\n",j);
    if (i>=j ){
    	return m;
    }else{
    	for (q=0; q<columnesmax ; q++){
    		aux= m [i][q];
    		m[i][q] = m[j][q];
    		m[j][q] = aux;
    	}

    return flipvertical(m,i+1,j-1,columnesmax);
  }
}

/**
 * Aquesta funció escriurà la matriu sobre un nou fitxer, el qual serà el fitxer de sortida.
 * @param: Com a paràmetres es rep, el nom del fitxer que s'haurà de crear, la matriu i el nombre de files de la matriu.
 *
 */
void escriufitxer(char* nom,char** matriu,int files,int opcio,int colum){

	FILE *g;
	int i,j,k;
	g = fopen(nom,"w");
	if (g== NULL){
		printf("Error creant fitxer sortida!\n");
	}else{
		switch (opcio){
		case 2:
		for (j=1;j<files;j++){
			for(k=0;k<colum;k++){
			    fprintf(g,"%c",matriu[j][k]);
			 }
		fprintf(g,"\n");
		}
		break;

		case 1:
    		for (j=0;j<files-1;j++){
    			for(k=0;k<colum;k++){
    				fprintf(g,"%c",matriu[j][k]);
    			}
    			fprintf(g,"\n");
    		}
			break;

		/*case 3:
    		for (j=0;j<files-2;j++){
    			for(k=0;k<colum;k++){
    				fprintf(g,"%c",matriu[j][k]);
    			}
    			printf("\n");
    		}
    		break;
    		*/
	}
	}
}
/**La funció desplaca matriu desplaça totes les files de la matriu una posició cap a la esquerra per poder eliminar els
 * '\0'.
 * @param: La funció rep com a paràmetres la mtriu, el nombre màxim de files i de columnes.
 * @return: La funció retorna la matriu desplaçada.
 *
 */

char** desplacamatriu(char** m, int colum, int files){
	int c,f;
	for(f=0;f<files;f++){
		for (c=0;c<colum;c++){
			m[f][c]=m[f][c+1];
		}
	}
	return m;
}


     /**
      * Aquest és el main, desde aquí, cridarem totes les funcions segons els paràmetres de la consola de comandes que llegirem amb
      * la funció getopt i mostrarem el resultat.
      * @param: La funció rep com a paràmetres la cadena d'arguments i un enter que representa la quantitat d'arguments entrats.
      *
      */

int main (int argc, char **argv) {
	float t1,t2;
	double final;
	int files,colum,j,k;
    char** matriuorig,**m,**m2,**matriufinal;
    static int vlongflag;
    static int hlongflag;
    static int dlongflag;
    int vflag = 0;
    int hflag = 0;
    int dflag = 0;
    int iflag = 0;
    int index;
    int c;
    char* filenameh = NULL;
    char* filenamev = NULL;
    char* filenamed = NULL;
    char* fileentry = NULL;
    opterr = 0;
    fileentry = argv[argc-1];
    printf("Fitxer entrada: %s",fileentry);
    matriuorig = tractafitxer(&colum,&files,fileentry);
    printf("FILES %d COLUM %d",files,colum);
    m = tractafitxer(&colum,&files,fileentry);
    m2= tractafitxer(&colum,&files,fileentry);
	//printf("\n %s\n",m[files-1]);
    //printf("SURTU");
    while (1){
    	static struct option long_options[] =
    	             {
    	               /* These options set a flag. */
    	               {"horitzontal",  required_argument,       &hlongflag, 1},
    	               {"vertical",  required_argument,       &hlongflag, 1},
    	               {"diagonal",  required_argument,       &vlongflag, 1},

    	             };

    	int option_index = 0;

    	           c = getopt_long (argc, argv, "h:v:d:r:i",
    	                            long_options, &option_index);

    	           /* Detect the end of the options. */
    	if (c == -1)
    		break;

    	switch (c){
    		case 0:
    	               /* If this option set a flag, do nothing else now. */
    	               if (long_options[option_index].flag != 0) {
        	               if (vlongflag) {
        	               	printf("\nFlip vertical: \n");
        	               	filenamev = optarg;
        	                	vflag = 1;
        	                   flipvertical(matriuorig,0,files-1,colum);
        	           		/*for (j=0;j<files-1;j++){
        	           			for(k=0;k<colum;k++){
        	           				printf("%c",matriufinal[j][k]);
        	           			}
        	           			printf("\n");
        	           		}
        	           		*/
        	                   escriufitxer(filenamev,matriuorig,files,2,colum);
        	                   vlongflag = 0;
        	               }
        	               if (hlongflag) {
        	            	   printf("\nFlip horitzontal: \n");
        	            	                   filenameh= optarg;
        	            	                   hflag = 1;
        	            	                   fliphoritzontal(m2,0,colum,files);
        	            	                   matriufinal=desplacamatriu(m2,colum,files);
        	            	           		for (j=0;j<files-1;j++){
        	            	           			for(k=0;k<colum;k++){
        	            	           				printf("%c",matriufinal[j][k]);
        	            	           			}
        	            	           			printf("\n");
        	            	           		}
        	            	                   //printf("\n\nfileh%s\n",filenameh);
        	            	                   escriufitxer(filenameh,matriufinal,files,1,colum);
        	            	                   hlongflag = 0;
        	               }
        	               if (dlongflag) {
        	               	printf("\nFlip diagonal: \n");
        	                   fliphoritzontal(m,0,colum,files);
        	                   matriufinal=desplacamatriu(m,colum,files);
        	           		for (j=0;j<files-1;j++){
        	           			for(k=0;k<colum;k++){
        	           				printf("%c",matriufinal[j][k]);
        	           			}
        	           			printf("\n");
        	           		}
        	               	dflag = 1;
        	                   filenamed = optarg;
        	                   flipvertical(matriufinal,0,files-1,colum);
        	                   printf("\e fet verti\n");
        	           		for (j=0;j<files-1;j++){
        	           			for(k=0;k<colum;k++){
        	           				printf("%c",matriufinal[j][k]);
        	           			}
        	           			printf("\n");
        	           		}
        	                   escriufitxer(filenamed,matriufinal,files,2,colum);
        	                   dlongflag = 0;

        	           }

    	               }
    	                 break;
    	               printf ("option %s", long_options[option_index].name);
    	               if (optarg)
    	                 printf (" with arg %s", optarg);
    	               printf ("\n");
    	               break;
    		case 'i' :
    			printf("ENTRO  I\n");
    		iflag=1;
    		break;

    		case 'h':

        		printf("\nFlip horitzontal: \n");
                filenameh= optarg;
                hflag = 1;
                if(!iflag){
                t1= clock();
                fliphoritzontal(m2,0,colum,files);
                matriufinal=desplacamatriu(m2,colum,files);
                t2 = clock();
                final=((double)(t2-t1))/CLOCKS_PER_SEC;
            	printf("Temps flip horitzontal %fl\n",final);

                }
                else{
                	printf("Es iteratiu\n");
                	t1= clock();
                	fliphoritzontalit(m2,0,colum,files);
                    matriufinal=desplacamatriu(m2,colum,files);
                    t2 = clock();
                    final=((double)(t2-t1)/CLOCKS_PER_SEC);
                	printf("Temps flip horitzontal %fl\n",final);
                }
        		for (j=0;j<files-1;j++){
        			for(k=0;k<colum;k++){
        				printf("%c",matriufinal[j][k]);
        			}
        			printf("\n");
        		}
                escriufitxer(filenameh,matriufinal,files,1,colum);

                break;
            case 'v':
            	printf("\nFlip vertical: \n");
            	filenamev = optarg;
             	vflag = 1;
             	if(!iflag){
             		t1=clock();
             		flipvertical(matriuorig,0,files-1,colum);
                    t2 = clock();
                    final=((double)(t2-t1)/CLOCKS_PER_SEC);
                	printf("Temps flip vert no it %fl\n",final);
             	}
             	else{
             	printf("ITERATIU\n");
             	t1=clock();
             	flipverticalit(matriuorig,0,files-1,colum);
        		/*for (j=0;j<files-1;j++){
        			for(k=0;k<colum;k++){
        				printf("%c",matriufinal[j][k]);
        			}
        			printf("\n");
        		}
        		*/
                t2 = clock();
                final=((double)(t2-t1)/CLOCKS_PER_SEC);
            	printf("Temps flip vert it%fl\n",final);
             	}
                escriufitxer(filenamev,matriuorig,files,2,colum);

             	break;
            case 'd':
            	printf("\nFlip diagonal: \n");
            	if(iflag) {
                	printf("Es iteratiu\n");
                	t1=clock();
                	fliphoritzontalit(m,0,colum,files);
                    matriufinal=desplacamatriu(m,colum,files);
             		flipverticalit(matriufinal,0,files-1,colum);
                    t2 = clock();
                    final=((double)(t2-t1)/CLOCKS_PER_SEC);
                	printf("Temps flip diag it%fl\n",final);
            	}
            	else{
            	t1=clock();
                fliphoritzontal(m,0,colum,files);
                matriufinal=desplacamatriu(m,colum,files);
            	dflag = 1;
                filenamed = optarg;
                flipvertical(matriufinal,0,files-1,colum);
                t2 = clock();
                final=((double)(t2-t1)/CLOCKS_PER_SEC);
            	printf("Temps flip diag no it %fl\n",final);
            	}
                printf("\e fet verti\n");
        		for (j=0;j<files-1;j++){
        			for(k=0;k<colum;k++){
        				printf("%c",matriufinal[j][k]);
        			}
        			printf("\n");
        		}
                escriufitxer(filenamed,matriufinal,files,2,colum);
                break;
            case '?':
                if (optopt == 'c'){



                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                }else{
                	if (isprint (optopt)){
                		fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                	}else{
                    fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
                    return 1;
                	default:abort ();
                	}
                }
               break;

         }
    	printf ("hflag = %d, vflag = %d, hvalue = %s\n",hflag, vflag, filenameh);
      }

    return 0;
}
