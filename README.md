# Algoritmo de Huffman Canónico

### Autores: Samuel Henao y Nicolás Ospina
### Language: C++ (Version 17)  
### OS: Windows 11  

## Descripción

Este programa fue creado como parte del curso **Estructura de Datos II** en la **Universidad EAFIT**. El objetivo es implementar el algoritmo de **Huffman Canónico** y generar una versión 
**canónica** de los códigos para una palabra o texto ingresado por el usuario. La codificación de Huffman es una
técnica de compresión sin pérdida que asigna códigos de longitud variable a los caracteres de una cadena, basándose en la frecuencia de aparición de cada carácter.

## Funcionalidad

El programa sigue estos pasos:

1. **Entrada**: Se ingresa una palabra o texto.
2. **Cálculo de frecuencias**: Se cuenta cuántas veces aparece cada caracter.
3. **Construcción del Árbol de Huffman**: Se utiliza una cola de prioridad para construir un árbol binario basado en las frecuencias de los caracteres.
4. **Generación de códigos de Huffman**: A partir del árbol de Huffman, se generan los códigos binarios para cada caracter.
5. **Conversión a Códigos Canónicos**: Los códigos generados se reorganizan en su forma canónica (ordenados por longitud y lexicográficamente).
6. **Salida**: Se muestran los códigos canónicos y los códigos concatenados en función de los caracteres ingresados.

## Explicación
Puede hallarse un video explicando el funcionamiento del código en el siguiente video de YouTube: https://youtu.be/iOu6i6FEDxM

## Como correr el programa

### Pasos:
1. Compilar el archivo usando un compilador compatible con C++ 17.
2. Correr el programa en un IDE o en la consola.
3. Ingresar un string, al que luego se le generarán los códigos de Huffman canónicos.

### Ejemplo de compilación y ejecución:
```bash
g++ huffman.cpp -o project
./project
```

