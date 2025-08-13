# STM32 Home Security System - UTN FRT

Este repositorio centraliza el desarrollo y documentación de distintos proyectos académicos y técnicos basados en **STM32**, junto con trabajos prácticos y experimentación en automatización de firmware.

## 📂 Estructura del repositorio

- **academic-projects/**  
  Trabajos prácticos AFP de *Técnicas Digitales II* (AFP 1 a AFP 5), con informes, presentaciones y/o código.

- **ci-cd-implementation/**  
  Proyecto experimental de **CI/CD para firmware de STM32**, que busca automatizar:
  - Compilación y pruebas unitarias con **GitHub Actions**.
  - Integración de **Docker** con toolchains ARM-GCC y OpenOCD.
  - Despliegue automático de binarios a servicios cloud (Azure/AWS).
  - Verificación de integridad del firmware antes de deploy.
  
  *Objetivo profesional:* demostrar habilidades en automatización de procesos para desarrollo embebido, integración cloud y prácticas DevOps aplicadas a hardware.

- **.metadata** / **.settings**  
  Configuración generada por **STM32CubeIDE** (no modificar manualmente).

- **.gitignore**  
  Archivos y carpetas que Git no versiona.

## 🛠️ Proyecto principal: Sistema de seguridad para el hogar

Desarrollado en **STM32CubeIDE**, este sistema incluye:
- Sensor magnético y sensor PIR para detección de intrusión.
- Teclado matricial 4x4 para control y desactivación.
- Pantalla OLED para mostrar mensajes y estados.
- Sirena con retardo configurable de 30 segundos.
- Comunicación I²C para dispositivos periféricos.

## 📜 Licencia
Este repositorio se distribuye bajo la licencia MIT. Ver el archivo [LICENSE](LICENSE) para más información.
