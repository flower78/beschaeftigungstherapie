#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

int simulate_particle(int number_pockets);
void increment_pocket_index(int pocket_index, int *pockets);
int resolution(int num_pockets, int num_particles);
void draw_histogram(int *histogram, int number_pockets);
int maximum_of_array(int *array, int length_of_array);

int main(int argc, char **argv)
{
    // ./Titel, Einlesen zu verfolgender Kugeln, Zahl der Fächer
    if(argc < 3)
    {
        printf("[./Titel] [Anzahl_Kugeln] [Anzahl_Faecher] verwenden\n");
        exit(-1);
    }

    //Einlesen
    int number_particles;
    int number_pockets;
    
    //char arrays zu integern
    number_particles = atoi(argv[1]);
    number_pockets = atoi(argv[2]);


    //Simulation: Jede Kugel muss number_pockets - 1 Ebenen durchlaufen 
    //Initialisiere RNG
    time_t t;
    srand((unsigned) time(&t));


    //Initialisier Dyn. Array für Fächer
    int *pockets = (int *) malloc(number_pockets * sizeof(int));
    for(int i = 0; i < number_pockets; i++)
    {
        pockets[i] = 0;
    }

    //Die eigentliche Simulation
    for(int i = 0; i < number_particles; i++)
    {
        //Index of one single particle
        int index = simulate_particle(number_pockets);
        increment_pocket_index(index, pockets);

    }

    int *histogram; 
    int res_value;
    res_value = resolution(number_pockets, number_particles);

    printf("\n\n");
    for(int i = 0; i < number_pockets; i++)
    {
        //Teile Anzahl durch Auflösung um neue Anzahl an 'x'-Symbolen zu bestimmen
        histogram[i] = pockets[i] / res_value;
        printf("%d ", *(histogram + i));
    }

    draw_histogram(histogram, number_pockets);
    


    free(pockets);
    free(histogram);

    return 0;
}


int simulate_particle(int number_pockets)
{
    /**
     * Aus Kugelperspektive:
     * 
     *
     * Gehe Links: addiere 1 
     * Gehe Rechts: addiere 0
     * Auf diese Weise muss man sich nicht merken an welcher 
     * Abzweigung die Kugel, auf welche Weise lief.
     * 
     */
    int counter = 0;
    int direction = 0;
    for(int i = 0; i < number_pockets; i++)
    {
        direction = rand() % 2; 
        counter += direction; 
    }


    //counter symbolisiert Summe alle "Linksabbiegungen" von der Kugelperspektive
    //Diese Summe bestimmt Index des Fachs [0, 1, 2, ..., number_pockets - 1]
    return counter; 
}

void increment_pocket_index(int pocket_index, int *pockets)
{
 
    pockets[pocket_index] += 1;
    
}   

//Anzahl Bälle pro 'x' - Symbol 
//Bei vielen Fächern: tendenziell weniger Kugeln pro Symbol
//Integer-Division liefert abgerundeten Floor-Wert
int resolution(int num_pockets, int num_particles)
{
    int resolution = num_particles / num_pockets;

    //Genauer aber immer noch zu hohe Histogram-Säulen
    //int resolution = (int)(log(num_particles)/log(num_pockets));
    printf("Resolution: %d are one 'x'\n", resolution);

    return resolution;
   
}


void draw_histogram(int *histogram, int number_pockets)
{
    //Konstantenwert verlangt,  für number_pockets wird als Fehler angezeigt
    //Es compiled trotzdem, das versteh ich nicht
    char *x_histogram[number_pockets];
    
    int histogram_count = 0; //Zähle nur Fächer die mehr als Null ganzzahlige Gruppen Kugeln haben.
    int x_count;
    int maximum_value_hist;

    //Bestimme Maximum um Zeichnung von Histogram später einfacher zu spiegeln
    maximum_value_hist = maximum_of_array(histogram, number_pockets);

   
    for(int i = 0; i < number_pockets; i++)
    {
        
        x_count = histogram[i];
        if(x_count > 0)
        {


            //Zeichne erst alle Reihen mit leeren Zeichen, überschreibe dann nach Bedarf mit 'x'
            char *hist_row = (char *)malloc((maximum_value_hist ) * sizeof(char));
            for(int m = 0; m < maximum_value_hist; m++)
            {
                *(hist_row + m) = ' ';
            }
            for(int j = 0; j < x_count; j++)
            {  
                *(hist_row + j) = 'X';

            }

            //Zeile für Zeile
            x_histogram[histogram_count] = hist_row; 
            histogram_count++;
           
        }
    }
    
    for(int l = maximum_value_hist - 1; l >= 0; l--)
    {

        for(int n = 0; n < histogram_count; n++)
        {
            printf("%c   ", x_histogram[n][l]);
        }
        printf("\n");
    }
        
    printf("\n");
}


int maximum_of_array(int *array, int length_of_array)
{
    int max = 0;
    for(int i = 0; i < length_of_array; i++)
    {
        if(array[i] > max)
            max = array[i];
    }
    //printf("\nTest_Max_Array: %d\n", max);
    return max;
    
}