#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[])
{

    Zona zonas[NUM_ZONAS];
    FILE *archivo = fopen("zonas.txt", "r");

    printf("\n----------------------------------------------------------------");
    printf("\n          Sistema Integral de Gestion y \nPrediccion de Contaminacion del Aire en Zonas Urbanas");
    printf("\n----------------------------------------------------------------\n");

    if (VerificarFichero("zonas.txt") == 1)
    {
        fclose(archivo);
    }
    else
    {
        archivo = fopen("zonas.txt", "a");

        if (archivo == NULL)
        {
            perror("\nError al abrir el archivo");
            return 1;
        }

        fprintf(archivo, "%-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
                "Zona", "CO2", "SO2", "NO2", "PM2.5", "Temp", "Viento", "Hum");
        fclose(archivo);
        printf("\nEl archivo fue creado con exito!");
    }

    return 0;
}