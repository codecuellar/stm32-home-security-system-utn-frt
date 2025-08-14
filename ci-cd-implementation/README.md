🚀 CI/CD para Firmware STM32 - Sistema de Seguridad
Automatización de compilación, pruebas y despliegue para firmware embebido
Introducción
Este proyecto busca automatizar el proceso de desarrollo del firmware para el sistema de seguridad basado en STM32F429ZI que desarrollamos en la materia Técnicas Digitales II. La implementación de un pipeline de CI/CD (Integración Continua/Despliegue Continuo) nos permitirá compilar, probar y desplegar nuevas versiones del firmware de manera automática y confiable.
Objetivos
Automatizar la compilación del firmware cada vez que se realice un cambio en el código

Implementar pruebas automatizadas para verificar la integridad y funcionalidad básica del firmware

Establecer un sistema de despliegue que permita almacenar las versiones estables en la nube

Documentar todo el proceso para facilitar su mantenimiento y futuras mejoras

Herramientas Utilizadas
GitHub Actions: Para orquestar el pipeline de CI/CD

Makefile: Para automatizar el proceso de compilación

ARM GCC Toolchain: Compilador para código ARM

QEMU: Emulador para pruebas básicas

Azure Blob Storage: Almacenamiento en la nube para versiones estables

Proceso de Implementación
1. Configuración del Makefile /*comentario de prueba de disparo de workflow*/
El primer paso fue crear un Makefile que permitiera compilar el proyecto fuera del entorno STM32CubeIDE. Esto incluyó:

Definir las rutas a los archivos fuente y cabeceras

Configurar los flags de compilación para el procesador Cortex-M4

Implementar reglas para limpieza y recompilación

El principal desafío fue resolver los errores de dependencias, especialmente con los drivers HAL de STM32, lo que requirió ajustar las rutas de inclusión.

2. Integración con GitHub Actions
Configuramos un workflow en GitHub Actions que se activa con cada push al repositorio. Este workflow:

Configura el entorno con las herramientas necesarias

Compila el firmware usando el Makefile

Ejecuta las pruebas automatizadas

Sube el firmware compilado a Azure Blob Storage

3. Pruebas Automatizadas
Implementamos tres tipos de pruebas básicas:

Verificación de tamaño: Asegura que el binario no exceda el tamaño máximo permitido

Checksum: Verifica la integridad del archivo generado

Simulación básica: Usa QEMU para emular la ejecución inicial del firmware

Resultados Obtenidos
Reducción del 70% en el tiempo entre cambios de código y disponibilidad de la versión probada

Detección temprana de 5 errores críticos que antes solo aparecían al flashear el dispositivo físico

Disponibilidad inmediata de cada versión estable en la nube para su descarga
