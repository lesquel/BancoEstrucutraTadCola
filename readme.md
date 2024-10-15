# Banco Pichincha

## Descripción
El Banco Pichincha es un banco de prueba que permite realizar operaciones bancarias (DEPOSITO, RETIRO) entre clientes. El banco tiene un sistema de gestión de clientes y un sistema de servicio.

## PREGUNTAS PARA REFLEXIÓN:
1. ¿Cómo cambiaría la simulación si se añaden más cajas de atención?
- En caso de que se añadan más cajas a la simulación, se atenderá a esa cantidad de clientes al mismo tiempo, ya que, en el caso del código desarrollado, se usó un hilo por cada caja que trabajara, como en la siguiente imagen, donde se podría simplemente descomentar esa ultima línea de código y la cantidad de hilos trabajando al mismo tiempo (además del principal) pasaría de ser 3 a ser 

2. ¿Qué sucedería si los tiempos de transacción fueran aleatorios?

- Para el desarrollo de este código, hicimos uso de un enum como se puede apreciar aquí:, por lo que los tiempos de cada caja y los de las personas son constantes según la operación que se realice. Por ello, en caso de que se quiera modificar esto, la clase caja ya no tomaría ningún valor constante, y la clase persona seria la que determine este valor aleatorio 

3. ¿Cómo implementarías una política de prioridad distinta, como atender primero a quienes tienen transacciones más rápidas?
- En este caso, cada que se ingrese un elemento, comparamos este elemento al primer elemento de la cola, si este es más rápido, entonces hacemos un dequeue y un enqueue al primer elemento, seguimos con este proceso hasta que el elemento que quede al frente sea el de la transacción más rápida



## ejecución

- Ejecutar el archivo `main.cpp` para ejecutar el programa.
