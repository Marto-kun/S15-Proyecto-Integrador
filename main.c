/**
 * @file main.c
 * @author Martin Vozmediano, Helen Benalcazar
 * @brief Sistema Integral de Gestion y Prediccion de Contaminacion del Aire en Zonas Urbanas
 * @version 1.0
 * @date 2026-01-15
 * * @details Este programa permite el monitoreo de 5 zonas urbanas, calcula
 * predicciones basadas en factores climáticos y genera reportes ejecutivos
 * persistentes en archivos .txt
 */

#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[])
{

    Zona zonas[NUM_ZONAS];
    char entrada[50];
    int opc, count = ContarZonasEnArchivo();
    FILE *archivo = fopen("zonas.txt", "r");

    printf("\n================================================================");
    printf("\n          Sistema Integral de Gestion y \nPrediccion de Contaminacion del Aire en Zonas Urbanas");
    printf("\n================================================================");

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
            printf("\n1) Ingresar nuevas zonas");
            printf("\n2) Monitoreo de limites actuales (OMS)");
            printf("\n3) Predicciones de contaminacion (prox. 24 horas)");
            printf("\n4) Reporte de promedios historicos (ultimos 30 dias)");
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
            IngresarDatosZonas(zonas, &count);
            break;
        case 2:
            MonitorearLimites(count);
            break;
        case 3:
            CalcularPrediccion(count);
            break;
        case 4:
            CalcularPromediosHist(count);
            break;
        case 5:
            if (VerificarFichero("zonas.txt") == 1 && VerificarFichero("historicos.txt") == 1)
            {
                GenerarReporte(count);
            }
            else
            {
                printf("\nArchivos necesarios insuficientes, revise la existencia de: zonas.txt e historicos.txt ");
            }
            break;
        case 6:
            printf("\nMuchas gracias por usar nuestro programa. Saliendo...\n");
            break;
        default:
            printf("\nOpcion invalida, intentelo de nuevo...");
            break;
        }

    } while (opc != 6);

    return 0;
}