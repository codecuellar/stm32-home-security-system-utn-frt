Proyecto AFP - TDII - Grupo 6
Este repositorio contiene los proyectos y desarrollos realizados para la materia Arquitectura de Funcionamiento de Procesadores (AFP) en el año 2024, por el Grupo 6.

Estructura del Repositorio
El repositorio está organizado en carpetas para facilitar el acceso a cada parte del proyecto:

AFP1_TDII_Grupo6: Primer trabajo práctico, contiene las bases de GPIO y los drivers iniciales.
AFP2_TDII_Grupo6: Segundo trabajo práctico, donde comenzamos con los drivers de funciones.
AFP3_TDII_Grupo6: Tercer trabajo práctico, que añade funcionalidades avanzadas y configuraciones adicionales, específicamente funciones no bloqueantes.
AFP4_TDII_Grupo6: Cuarto trabajo práctico, desarrollo de un sistema anti-rebote para pulsadores basado en una Máquina de Estados Finitos (MEF).
Cada carpeta incluye su propio código fuente y configuraciones específicas para cada etapa del proyecto.

Descripción de Funcionalidades
1. Funciones de Retardo no Bloqueante
En el segundo trabajo práctico, implementamos funciones de retardo no bloqueante para mejorar la eficiencia del código y evitar bloqueos en la ejecución. Las funciones desarrolladas incluyen:

delayInit(): Inicializa el retardo con un tiempo específico.
delayRead(): Verifica si el tiempo de retardo ha finalizado.
delayWrite(): Modifica la duración de un retardo ya inicializado.
Estas funciones utilizan el timer interno del microcontrolador y permiten controlar el flujo de ejecución sin detener la CPU.

2. Integración de Periféricos y Control de LEDs
Durante el desarrollo, configuramos distintos periféricos para interactuar con los LEDs de la placa. Realizamos una secuencia de encendido y apagado de LEDs utilizando los drivers de GPIO y las funciones de retardo no bloqueante. Esto incluyó:

Definición de los pines de los LEDs (LD1, LD2, y LD3) en el archivo main.h.
Configuración y control de encendido y apagado mediante los drivers desarrollados.
3. Sistema Anti-Rebote con Máquina de Estados Finitos (MEF)
En el cuarto trabajo práctico, desarrollamos un sistema anti-rebote para pulsadores mecánicos, utilizando una Máquina de Estados Finitos (MEF).

Características:
Estados de la MEF:

BUTTON_UP: Estado estable cuando el botón no está presionado.
BUTTON_FALLING: Estado transitorio durante la detección inicial de presión.
BUTTON_DOWN: Estado estable cuando el botón está presionado.
BUTTON_RISING: Estado transitorio durante la detección de liberación.
Funciones implementadas:

debounceFSM_init(): Inicialización de la MEF.
debounceFSM_update(): Actualización periódica de los estados.
readKey(): Lectura del estado del pulsador.
Callbacks: Manejo de eventos de presión (buttonPressed()) y liberación (buttonReleased()).
Integración: Se incorporó el sistema de retardos no bloqueantes con un tiempo de 40ms para filtrar los rebotes. También se utilizaron banderas (flags) para detectar eventos de presión del botón, lo que permitió manipular LEDs en respuesta a estos eventos.

Aplicaciones desarrolladas:
App 1.1: Secuencia simple sin interacción.
App 1.2 - App 1.4: Implementación completa del sistema anti-rebote, manteniendo las secuencias de LEDs y lógica no bloqueante.
Herramientas Utilizadas
STM32CubeIDE: IDE principal para la edición, compilación y carga de código en el microcontrolador STM32F429ZI.
Git y GitHub: Control de versiones y colaboración en equipo.
STM32CubeMX: Para la generación inicial de código y configuraciones de periféricos.
Instrucciones de Compilación
Abre STM32CubeIDE y selecciona el workspace donde está clonado este repositorio.
Importa los proyectos AFP1_TDII_Grupo6, AFP2_TDII_Grupo6, AFP3_TDII_Grupo6 y AFP4_TDII_Grupo6 siguiendo estos pasos:
Selecciona File > Import....
Elige General > Existing Projects into Workspace.
Selecciona la carpeta raíz donde están los proyectos y confirma.
Compila y carga el proyecto en la placa STM32F429ZI.
Créditos
Este proyecto fue desarrollado por el Grupo 6, como parte de los trabajos prácticos de Técnicas Digitales II.
