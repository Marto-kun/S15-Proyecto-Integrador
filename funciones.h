#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_ZONAS 5
#define HISTORICOS 30

// Limites OMS
#define LIMITE_CO2 400.0
#define LIMITE_SO2 20.0
#define LIMITE_NO2 40.0
#define LIMITE_PM25 15.0

typedef struct
{
    char nombre[50];
    float co2, so2, no2, pm25;          // Niveles actuales
    float historicos[30];               // Promedios Historicos
    float temperatura, viento, humedad; // Factores climaticos
} Zona;

/**
 * @brief Funcion para verificar numeros enteros
 *
 * @param string
 * @return int
 */
int VerificacionDigitos(char string[])
{

    if (strlen(string) == 0)
    {
        return 0; // Comprobar que la cadena no este vacia
    }

    for (int i = 0; i < strlen(string); i++)
    {
        if (!isdigit(string[i]))
        {
            return 0; // Si el elemento de la cadena no es caracter retorna 0
        }
    }
    return 1; // Si la cadena son solo digitos entonces se retorna verdadero
}

/**
 * @brief Funcion para validar datos decimales
 *
 * @param string
 * @return int
 */
int VerificacionFloat(char string[])
{
    int nPuntos = 0;
    if (strlen(string) == 0)
    {
        return 0; // Comprobar que la cadena no este vacia
    }

    for (int i = 0; i < strlen(string); i++)
    {
        char c = string[i];
        if (isdigit(c))
        {
            continue; // Si el elemento de la cadena es digito continua el bucle
        }
        else if (c == '.')
        {
            nPuntos++;
        }
        else
        {
            return 0; // Si no es digito o punto, es invalido
        }
    }

    if (nPuntos > 1)
    {
        return 0; // No pueden haber mas de 1 punto en el numero decimal
    }

    if (strlen(string) == 1 && (string[0] == '.'))
    {
        return 0; // Cadena invalida si solo es un punto
    }

    return 1; // Si la cadena son digitos validos entonces se retorna verdadero
}

/**
 * @brief Funcion para limpieza de buffer
 * evitar buffer overflow
 *
 */
void LimpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * @brief Funcion para verificar solo letras
 *
 * @param string
 * @return int
 */
int VerificacionChar(char string[])
{
    if (strlen(string) == 0)
    {
        return 0; // Comprobar que la cadena no este vacia
    }

    size_t len = strlen(string);

    for (int i = 0; i < len; i++)
    {
        if (!isalpha(string[i]))
        {
            return 0; // Si el elemento de la cadena es digito retorna 0
        }
    }
    return 1; // Si la cadena son solo caracteres entonces se retorna 1
}

/**
 * @brief Funcion para verificar solo letras
 *
 * @param string
 * @return int
 */
int VerificacionCharEspacios(char string[])
{
    if (strlen(string) == 0)
    {
        return 0; // Comprobar que la cadena no este vacia
    }

    size_t len = strlen(string);

    for (int i = 0; i < len; i++)
    {
        if (!isalpha(string[i]) && string[i] != ' ')
        {
            return 0; // Si el elemento de la cadena es digito retorna 0
        }
    }
    return 1; // Si la cadena son solo caracteres o espacios entonces se retorna 1
}

/**
 * @brief Funcion para verificar si es que una cadena ingresada esta vacia
 *
 * @param str
 * @return 0 si es valida, 1 si esta vacia
 */
int esVacia(char *str)
{
    if (str[0] == '\0')
    {
        return 1;
    }
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\t')
            return 0;
    }
    return 1;
}

/**
 * @brief Funcion para validar la existencia de un fichero
 *
 * @param archivo Nombre del archivo a comprobar
 * @return int 0 si no existe, 1 si existe
 */
int VerificarFichero(const char *archivo)
{
    FILE *file;
    file = fopen(archivo, "r");
    if (file == NULL)
    {
        fclose(file);
        return 0; // 0 si no existe el archivo
    }
    else
    {
        return 1; // 1 si el archivo existe
    }
}

/**
 * @brief Funcion para contar cuantas zonas existen en el archivo
 *
 * @return int Numero de lineas con informacion en el archivo
 */
int ContarZonasEnArchivo()
{
    FILE *archivo = fopen("zonas.txt", "r");
    if (archivo == NULL)
        return 0;

    char linea[200];
    int contador = 0;

    // Saltamos la primera linea (el encabezado)
    fgets(linea, sizeof(linea), archivo);

    // Contamos cuantas lineas con datos hay
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        if (strlen(linea) > 5) // Evita contar lineas vacias
        {
            contador++;
        }
    }

    fclose(archivo);
    return contador;
}

/**
 * @brief Funcion para ingresar datos actuales de una nueva zona
 *        e imprimir los valores dentro de un fichero
 *
 * @param zonas Arreglo para guardar datos a imprimir
 * @param totalZonas Cantidad de zonas a ingresar
 */
void IngresarDatosZonas(Zona zonas[], int *totalZonas)
{
    if (*totalZonas >= 5)
    {
        printf("\nEl archivo ya contiene 5 zonas. Intente con el resto de opciones");
        printf("\nRegresando al Menu Principal...");
        return;
    }

    char entrada[50];
    int n = 5;

    for (int i = 0; i < n; i++)
    {
        printf("\n--- Registro de la Zona #%d ---", i + 1);

        // Ingreso de nombre
        int nombreValido = 0;
        do
        {
            printf("\nIngrese el nombre de la zona: ");
            if (fgets(entrada, 50, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionCharEspacios(entrada) == 1)
            {
                strcpy(zonas[i].nombre, entrada);
                nombreValido = 1;
            }
            else
            {
                printf("\nError: Solo se permiten letras y espacios.");
            }
        } while (nombreValido == 0);

        // Ingreso de CO2
        int co2Valido = 0;
        do
        {
            printf("\nIngrese el nivel de CO2: ");
            if (fgets(entrada, 25, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                float valor = atof(entrada);
                if (valor >= 0)
                { // Validación lógica de no negatividad
                    zonas[i].co2 = valor;
                    co2Valido = 1;
                }
            }
            else
            {
                printf("\nError: Ingrese un valor decimal válido (ej: 400.5).");
            }
        } while (co2Valido == 0);

        // Ingreso de SO2
        int so2Valido = 0;
        do
        {
            printf("\nIngrese el nivel de SO2: ");
            if (fgets(entrada, 25, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                float valor = atof(entrada);
                if (valor >= 0)
                {
                    zonas[i].so2 = valor;
                    so2Valido = 1;
                }
            }
            else
            {
                printf("\nError: Ingrese un valor decimal válido (ej: 400.5).");
            }
        } while (so2Valido == 0);

        // Ingreso NO2
        int no2Valido = 0;
        do
        {
            printf("\nIngrese el nivel de NO2: ");
            if (fgets(entrada, 25, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                float valor = atof(entrada);
                if (valor >= 0)
                {
                    zonas[i].no2 = valor;
                    no2Valido = 1;
                }
            }
            else
            {
                printf("\nError: Ingrese un valor decimal válido (ej: 400.5).");
            }
        } while (no2Valido == 0);

        // Ingreso de PM2.5
        int PM25Valido = 0;
        do
        {
            printf("\nIngrese el nivel de PM 2.5: ");
            if (fgets(entrada, 25, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                float valor = atof(entrada);
                if (valor >= 0)
                {
                    zonas[i].pm25 = valor;
                    PM25Valido = 1;
                }
            }
            else
            {
                printf("\nError: Ingrese un valor decimal válido (ej: 400.5).");
            }
        } while (PM25Valido == 0);

        // Ingreso de temperatura
        int tempValida = 0;
        do
        {
            printf("\nIngrese el nivel de Temperatura: ");
            if (fgets(entrada, 25, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                float valor = atof(entrada);
                if (valor >= 0 && valor < 40)
                {
                    zonas[i].temperatura = valor;
                    tempValida = 1;
                }
            }
            else
            {
                printf("\nError: Ingrese una temperatura entre 0 y 40°C");
            }
        } while (tempValida == 0);

        // Ingreso de viento
        int vientoValido = 0;
        do
        {
            printf("\nIngrese la velocidad del viento (km/h): ");
            if (fgets(entrada, 25, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                float valorViento = atof(entrada);
                if (valorViento >= 0)
                {
                    zonas[i].viento = valorViento;
                    vientoValido = 1;
                }
                else
                {
                    printf("\nError: La velocidad debe ser un valor positivo.");
                }
            }
            else
            {
                printf("\nError: Ingrese un numero valido.");
            }
        } while (vientoValido == 0);

        // Ingreso de humedad
        int humValida = 0;
        do
        {
            printf("\nIngrese el nivel de humedad (0 - 100%%): ");
            if (fgets(entrada, 25, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                float valorHum = atof(entrada);
                if (valorHum >= 0 && valorHum <= 100)
                {
                    zonas[i].humedad = valorHum;
                    humValida = 1;
                }
                else
                {
                    printf("\nError: La humedad debe estar entre 0 y 100.");
                }
            }
            else
            {
                printf("\nError: Ingrese un numero decimal valido.");
            }
        } while (humValida == 0);

        FILE *f = fopen("zonas.txt", "a");
        if (f != NULL)
        {

            fprintf(f, "%-20s %-10.2f %-10.2f %-10.2f %-10.2f %-10.1f %-10.1f %-10.1f\n",
                    zonas[i].nombre, zonas[i].co2, zonas[i].so2,
                    zonas[i].no2, zonas[i].pm25, zonas[i].temperatura,
                    zonas[i].viento, zonas[i].humedad);
            fclose(f);
        }
    }
    *totalZonas = n;
}

/**
 * @brief Funcion para comparar la contaminacion actual con los
 *        limites de la OMS
 *
 * @param total Cantidad de zonas registradas
 */
void MonitorearLimites(int total)
{
    if (total < NUM_ZONAS)
    {
        printf("\nNo hay suficientes datos ingresados. Por favor, use la opcion 1 primero.\n");
        return;
    }

    printf("\nLimites OMS: \nCO2: %.2f, S02: %.2f, NO2: %.2f, PM2.5: %.2f",
           LIMITE_CO2, LIMITE_SO2, LIMITE_NO2, LIMITE_PM25);

    FILE *archivo = fopen("zonas.txt", "r");
    if (archivo == NULL)
    {
        printf("\nError: No se pudo abrir el archivo de datos.\n");
        return;
    }

    char linea[256];
    char nombre[50];
    float co2, so2, no2, pm25, temp, viento, hum;
    int contador = 0;

    printf("\n================================================================");
    printf("\n           ESTADO ACTUAL Y MONITOREO DE LIMITES");
    printf("\n================================================================");
    printf("\n%-15s %-10s %-10s %-10s %-10s", "Zona", "CO2", "SO2", "NO2", "PM2.5");
    printf("\n----------------------------------------------------------------");

    // 1. Saltar la primera línea
    if (fgets(linea, sizeof(linea), archivo) == NULL)
    {
        printf("\nEl archivo esta vacio.");
        fclose(archivo);
        return;
    }

    // 2. Leer los datos fila por fila
    while (fscanf(archivo, "%s %f %f %f %f %f %f %f",
                  nombre, &co2, &so2, &no2, &pm25, &temp, &viento, &hum) == 8)
    {

        contador++;
        printf("\n%-15s %-10.2f %-10.2f %-10.2f %-10.2f",
               nombre, co2, so2, no2, pm25);

        int riesgo = 0;
        printf("\n  >> ALERTAS: ");

        if (co2 > LIMITE_CO2)
        {
            printf("[EXCESO CO2] ");
            riesgo = 1;
        }
        if (pm25 > LIMITE_PM25)
        {
            printf("[EXCESO PM2.5] ");
            riesgo = 1;
        }

        if (riesgo == 0)
        {
            printf("Niveles dentro de lo normal.");
        }
        else
        {
            printf("\n  >> RECOMENDACION: Se sugiere limitar actividades al aire libre.");
        }
        printf("\n----------------------------------------------------------------");
    }

    // Validación de la consigna: comprobar si hay al menos 5
    if (contador < 5)
    {
        printf("\nSolo se encontraron %i zonas. Se requieren 5 para el reporte completo.", contador);
    }

    fclose(archivo);
}

/**
 * @brief Función para calcular y mostrar las predicciones para las proximas 24h
 *
 * @param total Cantidad de zonas registradas
 */
void CalcularPrediccion(int total)
{
    if (total < NUM_ZONAS)
    {
        printf("\nNo hay suficientes datos ingresados. Por favor, use la opcion 1 primero.\n");
        return;
    }

    FILE *archivo = fopen("zonas.txt", "r");
    if (archivo == NULL)
    {
        printf("\nError: No se pudo abrir el archivo de datos.\n");
        return;
    }

    char linea[250], nombre[50];
    float co2, so2, no2, pm25, temp, viento, hum;
    int contador = 0;

    printf("\n====================================================================================");
    printf("\n               PREDICCION DE CONTAMINACION (PROXIMAS 24 HORAS)");
    printf("\n====================================================================================");
    // Ajuste de columnas para incluir SO2 y NO2
    printf("\n%-18s %-10s %-10s %-10s %-10s %-10s", "Zona", "CO2 Pred.", "SO2 Pred.", "NO2 Pred.", "PM2.5 Pred.", "Tendencia");
    printf("\n------------------------------------------------------------------------------------");

    // Saltar encabezado
    fgets(linea, sizeof(linea), archivo);

    // Leer segun el formato de tu archivo [cite: 1, 2, 3, 4]
    while (fscanf(archivo, "%s %f %f %f %f %f %f %f",
                  nombre, &co2, &so2, &no2, &pm25, &temp, &viento, &hum) == 8)
    {

        contador++;

        // FACTORES DE PREDICCION
        // El viento reduce la concentracion (dispersión)
        // La humedad afecta principalmente a las partículas (PM2.5)
        float factorViento = viento * 0.05;
        float factorHum = hum * 0.02;

        // Calculo de Predicciones
        float predCO2 = co2 - factorViento + (factorHum * 0.1);
        float predSO2 = so2 - (factorViento * 0.8); // El SO2 se dispersa facil con viento
        float predNO2 = no2 - (factorViento * 0.6);
        float predPM25 = pm25 - (factorViento * 0.1) + factorHum;

        // Validacion: No pueden existir valores negativos
        if (predCO2 < 0)
        {
            predCO2 = 0;
        }

        if (predSO2 < 0)
        {
            predSO2 = 0;
        }

        if (predNO2 < 0)
        {
            predNO2 = 0;
        }

        if (predPM25 < 0)
        {
            predPM25 = 0;
        }

        printf("\n%-18s %-10.2f %-10.2f %-10.2f %-10.2f ",
               nombre, predCO2, predSO2, predNO2, predPM25);

        // Lógica de Tendencia basada en PM2.5 (el contaminante más crítico)
        if (predPM25 > pm25)
        {
            printf("[SUBE]");
        }
        else
        {
            printf("[BAJA]");
        }
    }

    if (contador < 5)
    {
        printf("\nSolo se encontraron %i zonas. Se requieren 5 para el reporte completo.", contador);
    }
    printf("\n------------------------------------------------------------------------------------\n");

    fclose(archivo);
}

/**
 * @brief Funcion para calcular los promedios historicos de cada zona
 *
 * @param total Cantidad de zonas registradas
 */
void CalcularPromediosHist(int total)
{
    if (total < NUM_ZONAS)
    {
        printf("\nNo hay suficientes datos ingresados. Por favor, use la opcion 1 primero.\n");
        return;
    }

    FILE *archivo = fopen("historicos.txt", "r");
    if (archivo == NULL)
    {
        printf("\nError: No se encontro el archivo 'historicos.txt'.");
        return;
    }

    char linea[1024]; // Linea larga para los 30 datos
    char nombreZona[50];
    float suma, valor, promedio;
    int contadorZonas = 0;

    printf("\n================================================================");
    printf("\n         ANALISIS DE PROMEDIOS HISTORICOS (30 DIAS)");
    printf("\n================================================================");
    printf("\n%-20s %-15s %-15s", "Zona", "Promedio Mes", "Estado Mensual");
    printf("\n----------------------------------------------------------------");

    // Saltar el encabezado del archivo historicos.txt
    fgets(linea, sizeof(linea), archivo);

    // Leer cada zona y sus 30 datos
    while (fscanf(archivo, "%s", nombreZona) == 1)
    {
        suma = 0;

        // Bucle para leer los 30 valores flotantes de la fila
        for (int i = 0; i < HISTORICOS; i++)
        {
            if (fscanf(archivo, "%f", &valor) == 1)
            {
                suma += valor;
            }
        }

        promedio = suma / HISTORICOS;
        contadorZonas++;

        printf("\n%-20s %-15.2f ", nombreZona, promedio);

        // Comparativa con limite de la OMS para el mes
        if (promedio > 15.0)
        {
            printf("[CRITICO]");
        }
        else
        {
            printf("[ESTABLE]");
        }
    }

    if (contadorZonas == 0)
    {
        printf("\nNo se encontraron datos historicos procesables.");
    }

    printf("\n----------------------------------------------------------------\n");
    fclose(archivo);
}

/**
 * @brief Función para generar el reporte completo de cada zona 
 *        sobre su contaminacion ambiental
 * 
 * @param total Cantidad de zonas registradas
 */
void GenerarReporte(int total)
{
    if (total < NUM_ZONAS)
    {
        printf("\nNo hay suficientes datos ingresados. Por favor, use la opcion 1 primero.\n");
        return;
    }

    FILE *zonas = fopen("zonas.txt", "r");
    FILE *histo = fopen("historicos.txt", "r");
    FILE *repo = fopen("reporteFinal.txt", "w");

    if (zonas == NULL || histo == NULL || repo == NULL)
    {
        printf("\nError: Faltan archivos base para generar el reporte.\n");
        return;
    }

    char Lzonas[256], Lhisto[1024], nombre[50];
    float co2, so2, no2, pm25, temp, viento, hum, valor_h, suma_h;
    int contador = 0;

    // Encabezado del reporte
    printf("\n================================================================");
    printf("\n          Sistema Integral de Gestion y \nPrediccion de Contaminacion del Aire en Zonas Urbanas");
    printf("\n================================================================");

    // Saltarse linea de encabezados en los archivos de zonas y de historicos
    fgets(Lzonas, sizeof(Lzonas), zonas);
    fgets(Lhisto, sizeof(Lhisto), histo);

    // Proceso de cada zona mediante bucle while
    while (fscanf(zonas, "%s %f %f %f %f %f %f %f",
                  nombre, &co2, &so2, &no2, &pm25, &temp, &viento, &hum) == 8)
    {
        // Calculo de promedio historico para zona actual
        char nombreH[50];
        suma_h = 0;
        fscanf(histo, "%s", nombreH);
        for (int i = 0; i < HISTORICOS; i++)
        {
            fscanf(histo, "%f", &valor_h);
            suma_h += valor_h;
        }
        float promedioMes = suma_h / HISTORICOS;

        // Prediccion para zona actual (24h)
        float fViento = viento * 0.05;
        float fHum = hum * 0.02;

        float predCO2 = co2 - fViento + (fHum * 0.1);
        float predSO2 = so2 - (fViento * 0.8); // Se disipa mas facilmente
        float predNO2 = no2 - (fViento * 0.6);
        float predPM25 = pm25 - (fViento * 0.1) + fHum;

        // Escritura de resultados en archivo persistente
        {
            fprintf(repo, "ZONA: %-20s\n", nombre);
            fprintf(repo, "--------------------------------------------------------------\n");
            fprintf(repo, "ANÁLISIS HISTÓRICO:\n");
            fprintf(repo, "  > Promedio Mensual (PM2.5): %.2f ug/m3\n", promedioMes);
            fprintf(repo, "  > Estado del Mes: %s\n", (promedioMes > 15.0) ? "CRÍTICO" : "DENTRO DEL LÍMITE");

            fprintf(repo, "\nPREDICCIONES PRÓXIMAS 24 HORAS:\n");
            fprintf(repo, "  > CO2:  %7.2f | SO2:  %7.2f\n", predCO2, predSO2);
            fprintf(repo, "  > NO2:  %7.2f | PM2.5: %7.2f\n", predNO2, predPM25);
        }

        // Alerta y recomendaciones
        {
            fprintf(repo, "\nCONCLUSIÓN:\n");
            if (predPM25 > 15.0 || predCO2 > 400.0)
            {
                fprintf(repo, "  ESTADO: [ALERTA PREVENTIVA]\n");
                fprintf(repo, "  ACCIÓN: Notificar a Salud Pública y restringir tráfico.\n");
            }
            else
            {
                fprintf(repo, "  ESTADO: [CALIDAD ÓPTIMA]\n");
                fprintf(repo, "  ACCIÓN: No se requieren medidas restrictivas.\n");
            }
            fprintf(repo, "==============================================================\n\n");

            contador++;
        }
    }

    fclose(zonas);
    fclose(histo);
    fclose(repo);

    printf("\n[PROCESO COMPLETADO]: Se han analizado %d zonas.", contador);
    printf("\nEl archivo 'reporte_final.txt' está listo para su revisión.\n");
}
