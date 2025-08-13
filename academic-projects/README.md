Proyectos Académicos - AFP 2024
# TDII - Grupo 6  

Este repositorio contiene los proyectos y desarrollos realizados para la materia **Arquitectura de Funcionamiento de Procesadores** (AFP) en el año 2024, por el Grupo 6.  

## Estructura del Repositorio  

El repositorio está organizado en carpetas para facilitar el acceso a cada parte del proyecto:  

- `AFP1_TDII_Grupo6`: Primer trabajo práctico, contiene las bases de GPIO y los drivers iniciales.  
- `AFP2_TDII_Grupo6`: Segundo trabajo práctico, donde comenzamos con los drivers de funciones.  
- `AFP3_TDII_Grupo6`: Tercer trabajo práctico, que añade funcionalidades avanzadas y configuraciones adicionales, específicamente funciones no bloqueantes.  
- `AFP4_TDII_Grupo6`: Cuarto trabajo práctico, desarrollo de un sistema anti-rebote para pulsadores basado en una Máquina de Estados Finitos (MEF).  
- `AFP5_TDII_Grupo6`: Quinto trabajo práctico y proyecto final, implementación de un sistema de seguridad para detección de intrusos utilizando sensores PIR, final de carrera, y un módulo Bluetooth.
Cada carpeta incluye su propio código fuente y configuraciones específicas para cada etapa del proyecto.  

## Descripción de Funcionalidades  

### 1. Funciones de Retardo no Bloqueante  
En el segundo trabajo práctico, implementamos funciones de retardo no bloqueante para mejorar la eficiencia del código y evitar bloqueos en la ejecución. Las funciones desarrolladas incluyen:  

- **delayInit()**: Inicializa el retardo con un tiempo específico.  
- **delayRead()**: Verifica si el tiempo de retardo ha finalizado.  
- **delayWrite()**: Modifica la duración de un retardo ya inicializado.  

Estas funciones utilizan el timer interno del microcontrolador y permiten controlar el flujo de ejecución sin detener la CPU.  

### 2. Integración de Periféricos y Control de LEDs  
Durante el desarrollo, configuramos distintos periféricos para interactuar con los LEDs de la placa. Realizamos una secuencia de encendido y apagado de LEDs utilizando los drivers de GPIO y las funciones de retardo no bloqueante. Esto incluyó:  

- Definición de los pines de los LEDs (LD1, LD2, y LD3) en el archivo `main.h`.  
- Configuración y control de encendido y apagado mediante los drivers desarrollados.  

### 3. Sistema Anti-Rebote con Máquina de Estados Finitos (MEF)  
En el cuarto trabajo práctico, desarrollamos un sistema anti-rebote para pulsadores mecánicos, utilizando una Máquina de Estados Finitos (MEF).  

#### Características:  
- **Estados de la MEF**:  
  - `BUTTON_UP`: Estado estable cuando el botón no está presionado.  
  - `BUTTON_FALLING`: Estado transitorio durante la detección inicial de presión.  
  - `BUTTON_DOWN`: Estado estable cuando el botón está presionado.  
  - `BUTTON_RISING`: Estado transitorio durante la detección de liberación.  

- **Funciones implementadas**:  
  - `debounceFSM_init()`: Inicialización de la MEF.  
  - `debounceFSM_update()`: Actualización periódica de los estados.  
  - `readKey()`: Lectura del estado del pulsador.  
  - Callbacks: Manejo de eventos de presión (`buttonPressed()`) y liberación (`buttonReleased()`).  

- **Integración**: Se incorporó el sistema de retardos no bloqueantes con un tiempo de 40ms para filtrar los rebotes. También se utilizaron banderas (`flags`) para detectar eventos de presión del botón, lo que permitió manipular LEDs en respuesta a estos eventos.  

#### Aplicaciones desarrolladas:  
- **App 1.1**: Secuencia simple sin interacción.  
- **App 1.2 - App 1.4**: Implementación completa del sistema anti-rebote, manteniendo las secuencias de LEDs y lógica no bloqueante.  

### 4. Sistema de Seguridad con Detección de Intrusos

En el quinto trabajo práctico (AFP5), implementamos un Sistema de Seguridad para Detección de Intrusos utilizando una placa STM32 NUCLEO-F429ZI. Este sistema integra sensores PIR para detectar movimiento, un sensor magnético (reemplazado por un final de carrera) para monitorear la apertura de puertas o ventanas, y un módulo Bluetooth (HC-05) para la comunicación con dispositivos externos.

#### Características del Sistema
- **Detección de Intrusos**:

    Sensor PIR (SR-501): Detecta movimiento en un rango de 3 a 7 metros.

    Final de Carrera: Reemplaza al sensor magnético para detectar aperturas de puertas o ventanas.

- **Interfaz de Usuario**:

    Teclado Matricial 4x4: Permite al usuario ingresar un código de seguridad para desactivar la alarma.

    Display OLED 128x32: Muestra mensajes de estado y alertas en tiempo real.

    LEDs Indicadores: LED azul (inicialización), LED verde (monitoreo activo), LED rojo (alarma activa).

- **Comunicación Bluetooth**:

    Módulo HC-05: Permite la activación/desactivación remota del sistema mediante una aplicación móvil.

- **Alarma Sonora**:

    Sirena de 12V: Se activa cuando se detecta una intrusión y el usuario no desactiva el sistema en 30 segundos.

#### Funcionamiento del Sistema
El sistema opera mediante una Máquina de Estados Finitos (MEF) con los siguientes estados:

- **INICIALIZACIÓN:**

    El sistema se prepara para el monitoreo, mostrando un mensaje de inicio en el display OLED.

    El LED azul parpadea indicando que el sistema está en espera.

- **ESTADO ACTIVO:**

    El sistema monitorea los sensores PIR y magnético.

    Si se detecta movimiento o apertura de puerta, se muestra un mensaje de alerta en el display y se activa un contador de 30 segundos.

    El LED verde permanece encendido indicando que el sistema está activo.

- **ALARMA:**

    Si el usuario no desactiva el sistema en 30 segundos, se activa la sirena y el LED rojo parpadea.

    El usuario debe ingresar el código correcto en el teclado matricial para desactivar la alarma.

    Si el usuario falla tres veces, el teclado se bloquea y la sirena se activa automáticamente.

- **Módulos de Software Desarrollados**
Módulo de Inicialización: Configuración de periféricos como GPIO, UART, I2C y el display OLED.

Módulo de Control del Sistema (MEF): Implementa la Máquina de Estados Finitos que gestiona los estados del sistema.

Módulo de Monitoreo de Sensores: Lee los sensores PIR y magnético para detectar intrusiones.

Módulo de Gestión de Alertas: Muestra mensajes de alerta en el display y activa la sirena.

Módulo de Teclado: Gestiona la entrada del usuario a través del teclado matricial 4x4.

Módulo de Comunicación Bluetooth: Permite la comunicación con dispositivos externos mediante Bluetooth.

Módulo de Retardos No Bloqueantes: Controla el tiempo de las transiciones y acciones en el sistema.

Módulo de Control de LEDs: Gestiona los LEDs que indican el estado del sistema.

Módulo de Registro de Eventos: Registra eventos importantes como alertas de sensores o intentos fallidos de contraseña.

Módulo de Reinicio del Sistema: Permite reiniciar el sistema manualmente.

## Herramientas Utilizadas  

- **STM32CubeIDE**: IDE principal para la edición, compilación y carga de código en el microcontrolador STM32F429ZI.  
- **Git y GitHub**: Control de versiones y colaboración en equipo.  
- **STM32CubeMX**: Para la generación inicial de código y configuraciones de periféricos.  

## Instrucciones de Compilación  

1. Abre STM32CubeIDE y selecciona el workspace donde está clonado este repositorio.  
2. Importa los proyectos **AFP1_TDII_Grupo6**, **AFP2_TDII_Grupo6**, **AFP3_TDII_Grupo6** y **AFP4_TDII_Grupo6** siguiendo estos pasos:  
   - Selecciona `File > Import...`.  
   - Elige `General > Existing Projects into Workspace`.  
   - Selecciona la carpeta raíz donde están los proyectos y confirma.  
3. Compila y carga el proyecto en la placa STM32F429ZI.  

## Créditos  

Este proyecto fue desarrollado por el Grupo 6, como parte de los trabajos prácticos de Técnicas Digitales II.  
