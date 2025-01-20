# push_swap

## Descripción del Proyecto

**push_swap** es un proyecto diseñado para poner a prueba tus habilidades en la manipulación de datos y algoritmos de ordenación utilizando pilas. El objetivo es ordenar una lista desordenada de enteros en la pila 'a' utilizando una serie de operaciones permitidas y la mínima cantidad de movimientos posibles.

## Reglas del Juego

- **Stacks**: Tienes dos pilas, llamadas 'a' y 'b'.
- **Inicialización**:
  - El stack 'a' contiene una cantidad aleatoria de números positivos y/o negativos, sin duplicados.
  - El stack 'b' está inicialmente vacío.
- **Objetivo**: Ordenar la pila 'a' en orden ascendente utilizando las siguientes operaciones:

| Operación | Descripción |
|-----------|-------------|
| `sa`      | Intercambia los dos primeros elementos del stack 'a'. No hace nada si hay uno o menos elementos. |
| `sb`      | Intercambia los dos primeros elementos del stack 'b'. No hace nada si hay uno o menos elementos. |
| `ss`      | Realiza `sa` y `sb` al mismo tiempo. |
| `pa`      | Mueve el primer elemento del stack 'b' al principio del stack 'a'. No hace nada si 'b' está vacío. |
| `pb`      | Mueve el primer elemento del stack 'a' al principio del stack 'b'. No hace nada si 'a' está vacío. |
| `ra`      | Rota hacia arriba todos los elementos del stack 'a', de modo que el primer elemento se convierte en el último. |
| `rb`      | Rota hacia arriba todos los elementos del stack 'b', de modo que el primer elemento se convierte en el último. |
| `rr`      | Realiza `ra` y `rb` al mismo tiempo. |
| `rra`     | Rota hacia abajo todos los elementos del stack 'a', de modo que el último elemento se convierte en el primero. |
| `rrb`     | Rota hacia abajo todos los elementos del stack 'b', de modo que el último elemento se convierte en el primero. |
| `rrr`     | Realiza `rra` y `rrb` al mismo tiempo. |

## Ejemplo de Uso

```shell
# Inicialización de stacks:
a: 2 1 3 6 5 8
b:

# Ejecución de operaciones:
sa: Intercambia 2 y 1 en 'a'
a: 1 2 3 6 5 8
b:

pb pb pb: Mueve 6, 5, 8 a 'b'
a: 1 2 3
b: 8 5 6

ra rb: Rota 'a' y 'b' hacia arriba
a: 2 3 1
b: 5 6 8

rra rrb: Rota 'a' y 'b' hacia abajo
a: 1 3 2
b: 8 5 6

sa: Intercambia 1 y 3 en 'a'
a: 3 1 2
b: 8 5 6

pa pa pa: Mueve 8, 5, 6 a 'a'
a: 1 2 3 5 6 8
b:
```

## Implementación

- **Nombre del programa**: push_swap
- **Archivos a entregar**: `Makefile`, `*.h`, `*.c`
- **Funciones permitidas**: `read`, `write`, `malloc`, `free`, `exit`, `ft_printf` (o funciones equivalentes creadas por ti)
- **Librerías permitidas**: `libft`

## Requisitos del Proyecto

- El programa deberá ordenarse el stack 'a' utilizando el menor número de operaciones posible.
- El programa debe manejar errores, como argumentos no válidos o números duplicados, mostrando `Error\n` en la salida estándar de errores.
- No se permiten variables globales.
- Se debe entregar un `Makefile` que compile los archivos fuente sin hacer relink.

## Rendimiento y Validación

Para validar el proyecto, el rendimiento será medido con las siguientes métricas:
- **Validación mínima**: Ordenar 100 números aleatorios con menos de 700 operaciones.
- **Validación máxima**: Ordenar 500 números aleatorios con menos de 5500 operaciones.
