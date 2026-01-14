#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_ZONAS 5
#define HISTORICOS 30
#define LIMITE_CO2 400.0
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
 * @brief Funcion para ingresar datos actuales de una nueva zona
 *        e imprimir los valores dentro de un fichero
 *
 * @param zonas Arreglo para guardar datos a imprimir
 * @param totalZonas Cantidad de zonas a ingresar
 */
void IngresarDatosZonas(Zona zonas[], int *totalZonas)
{
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
