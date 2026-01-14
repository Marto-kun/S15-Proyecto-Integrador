#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[])
{

    Zona zonas[NUM_ZONAS];
    char entrada[50];
    int opc, count;
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

    //---- MENU PRINCIPAL ----
    do
    {
        int opcValida = 0;
        do
        {
            printf("\n------ MENU PRINCIPAL ------");
            printf("\n1) Ingresar nueva zona");
            printf("\n2) Monitoreo de límites actuales");
            printf("\n3) Predicciones de contaminacion (prox. 24 horas)");
            printf("\n4) Reporte de promedios históricos (ultimos 30 dias)");
            printf("\n5) Generar reporte final");
            printf("\n6) Salir");
            printf("\n>>>");

            if (fgets(entrada, 25, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }

            // Eliminar el salto de línea al final de la cadena
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionDigitos(entrada))
            {
                opc = atoi(entrada);
                opcValida = 1;
            }
            else
            {
                printf("\nSolo se permiten numeros enteros");
            }

        } while (opcValida == 0);


        switch (opc)
        {
        case 1:
            IngresarDatosZonas(zonas, count);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            printf("\nOpcion invalida, intentelo de nuevo...");
            break;
        }

    } while (opc != 6);

    return 0;
}