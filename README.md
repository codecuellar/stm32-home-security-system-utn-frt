# Proyecto AFP - TDII - Grupo 6

Este repositorio contiene los proyectos y desarrollos realizados para la materia **Arquitectura de Funcionamiento de Procesadores** (AFP) en el año 2024, por el Grupo 6.

## Estructura del Repositorio

El repositorio está organizado en carpetas para facilitar el acceso a cada parte del proyecto:

- `AFP1_TDII_Grupo6`: Primer trabajo práctico, contiene las bases de GPIO y los drivers iniciales.
- `AFP2_TDII_Grupo6`: Segundo trabajo práctico, donde comenzamos con los drivers de funciones.
- `AFP3_TDII_Grupo6`: Tercer trabajo práctico, que añade funcionalidades avanzadas y configuraciones adicionales, especificamente funciones no bloqueantes.
- `DRIVER_GPIO`: Driver personalizado para el manejo de pines GPIO sin uso de HAL, desarrollado desde cero para un mejor entendimiento de los registros y funcionamiento interno.

Cada carpeta incluye su propio código fuente y configuraciones específicas para cada etapa del proyecto.

## Descripción de Funcionalidades

### 1. Driver GPIO
Creamos un driver GPIO personalizado que no depende de la librería HAL de STM32. Este driver fue desarrollado como parte de la primera fase del proyecto y permite configurar y manipular directamente los pines del microcontrolador a nivel de registros. Esto fue clave para comprender cómo funcionan los periféricos internos del STM32.

### 2. Funciones de Retardo no Bloqueante
En el segundo trabajo práctico, implementamos funciones de retardo no bloqueante para mejorar la eficiencia del código y evitar bloqueos en la ejecución. Las funciones desarrolladas incluyen:

- **delayInit()**: Inicializa el retardo con un tiempo específico.
- **delayRead()**: Verifica si el tiempo de retardo ha finalizado.
- **delayWrite()**: Modifica la duración de un retardo ya inicializado.

Estas funciones utilizan el timer interno del microcontrolador y permiten controlar el flujo de ejecución sin detener la CPU.

### 3. Integración de Periféricos y Control de LEDs
Durante el desarrollo, configuramos distintos periféricos para interactuar con los LEDs de la placa. Realizamos una secuencia de encendido y apagado de LEDs utilizando los drivers de GPIO y las funciones de retardo no bloqueante. Esto incluyó:

- Definición de los pines de los LEDs (LD1, LD2, y LD3) en el archivo `main.h`.
- Configuración y control de encendido y apagado mediante los drivers desarrollados.

### 4. Organización y Estructura del Proyecto en STM32CubeIDE
Cada proyecto (`AFP1`, `AFP2`, y `AFP3`) está configurado en **STM32CubeIDE**. Los archivos `.ioc` se utilizaron para las configuraciones iniciales de cada trabajo práctico y se organizó la estructura de código en las carpetas `Core`, `Drivers`, e `Includes` para mantener la coherencia y facilitar el desarrollo.

## Herramientas Utilizadas

- **STM32CubeIDE**: IDE principal para la edición, compilación y carga de código en el microcontrolador STM32F429.
- **Git y GitHub**: Control de versiones y colaboración en equipo.
- **STM32CubeMX**: Para la generación inicial de código y configuraciones de periféricos.

## Instrucciones de Compilación

1. Abre STM32CubeIDE y selecciona el workspace donde está clonado este repositorio.
2. Importa los proyectos **AFP1_TDII_Grupo6**, **AFP2_TDII_Grupo6**, y **AFP3_TDII_Grupo6** siguiendo estos pasos:
   - Selecciona `File > Import...`
   - Elige `General > Existing Projects into Workspace`
   - Selecciona la carpeta raíz donde están los proyectos y confirma.
3. Compila y carga el proyecto en la placa STM32F429.

## Créditos

Este proyecto fue desarrollado por el Grupo 6 , como parte de los trabajos prácticos de Técnicas Digitales II.

---

Este README proporciona una visión general de las funcionalidades desarrolladas y la estructura del proyecto, útil para nuevos integrantes o revisores de la materia.
