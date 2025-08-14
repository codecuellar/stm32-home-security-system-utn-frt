# Makefile simplificado para CI/CD
PROJECT_NAME = PD-V2-Funciona- #uso un nombre sin caracteres especiales
BUILD_DIR = Debug

# Compilación principal (usa el Makefile generado por CubeIDE)
# Este comando ahora se ejecutará directamente desde el workflow.
all:
	@echo "🔨 Compilando firmware desde el Makefile de CubeIDE..."
	make -C Proyecto-2024-utnfrt/Debug

# Limpieza
clean:
	@echo "🧹 Limpiando archivos..."
	rm -rf /*

# Genera el .bin usando el compilador del entorno, no una ruta fija.
bin:
	arm-none-eabi-objcopy -O binary "Proyecto-2024-utnfrt/Debug/$(PROJECT_NAME).elf" "Proyecto-2024-utnfrt/Debug/$(PROJECT_NAME).bin"