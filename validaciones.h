#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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