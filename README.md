# Projecto Taller
## Descripción
La eficiencia es importante a la hora de programar, se busca que el codigo haga lo que tenga que hacer de la manera mas rapida o la mas economica a la hora de usar RAM. El contenido de esta carpeta busca experimentar con distintas soluciones a los problemas de eficiencia, para llegar a una conclusion sobre la conveniencia a la hora de elegir una estructura a utilizar dependiendo del contexto en el que nos manejemos.

## Solucion 1: Arreglo Dinamico
La Solución 1 consiste en implementar una estructura de datos basada en un arreglo dinámico ordenado lexicográficamente, donde cada celda almacena una palabra. La estructura aumenta automáticamente su capacidad cuando el arreglo se llena, utilizando un overhead para evitar redimensionamientos constantes. Además, la búsqueda se optimiza mediante una adaptación de la búsqueda binaria, acotando primero el rango según la letra inicial de la palabra usando un arreglo auxiliar de índices.

## Solución 2: Grilla de Listas enlazadas
La solución 2 consiste en una estructura de datos organizada como una grilla multinivel de nodos doblemente enlazados, diseñada para almacenar palabras de manera ordenada y optimizar las búsquedas. Cada nivel permite reducir el espacio de búsqueda mediante saltos entre nodos, mejorando el rendimiento respecto a una lista enlazada tradicional.

## Solución 3: Arbol de busqueda K-ario
La Solución 3 consiste en un arbol K-ario que almacena K palabras y con cada nodo teniendo K + 1 hijos, esto permitira separar el problema en busquedas mas pequeñas y acotadas, cuyo rendimiento va a depender de que tan balanceado este el arbol y cual sea el K elegido para hacer el arbol.

## Requisitos
- Tener el compilador g++ instalado, actualizado y utilizable.
- Tener makefile a disposición del comando make

```bash
make
```

## Pasos
1. Compilar los archivos

Compilar todas las soluciones
```bash
make
```
o Compilar Solucion 1
```bash
make S1
```
o Compilar Solucion 2
```bash
make S2
```
o Compilar Solucion 3
```bash
make S3
```

2. Ejecutar

Ejecutar Solucion 1
```bash
./demostracion1
```
Ejecutar Solucion 2
```bash
./demostracion2
```
Ejecutar Solucion 3
```bash
./demostracion3
```

## Estructura de Archivos
```
├── D1.txt
├── D2.txt
├── demostracion1.cpp
├── demostracion2.cpp
├── demostracion3.cpp
├── solucion1.h
├── solucion2.h
├── solucion3.h
├── makefile
├── LICENSE
└── README.md
```
  
## Desarrollado por:
- Diego Fernández
- Gabriel Poblete
- Dalma Redoles
- Heidi Santisteban
  
