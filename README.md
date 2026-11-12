# Grupo 1 - Patrón Singleton

Sistema de configuración global para una aplicación de escritorio.

**Integrantes:** 
- Wilber Jesus Guerra Pilco
- Jhon Deyvis Cuyo Ccapa
- Diego Sebastian Santa Cruz Villa
- Cristhian Matias Bravo Arredondo
- Jaime Daniel Igreda Alvarado
- Fernando Gerson Luque Guevara

## Explicación breve
`ConfigManager` es un **Singleton**: solo existe una instancia en toda la aplicación
y cualquier módulo (ventanas, encabezado, tema, etc.) la obtiene con
`ConfigManager::instance()`. Así, si una ventana cambia el tema o el idioma, todas las
demás ven el mismo valor sin pasar objetos de configuración de un lado a otro.


Cómo se implementa:
- Constructor **privado**: nadie puede hacer `new ConfigManager`.
- Copia y asignación **eliminadas** (`= delete`).
- Instancia `static` dentro de `instance()` (Meyers Singleton, segura entre hilos en C++11+).
- Un `mutex` protege los datos si varios hilos leen o escriben.


## POO usada
- **Clases y encapsulamiento:** datos privados (`data_`, `storage_`, `path_`), acceso solo por métodos.
- **Herencia y polimorfismo:** `ConfigStorage` (abstracta) -> `FileConfigStorage`;
  `AppModule` (abstracta) -> `HeaderModule`, `ThemeModule` (consola).
- **Qt:** `MainWindow` y `ConfigViewerWindow` heredan de `QMainWindow` / `QWidget`.


## Estructura
```
src/core/     ConfigManager, ConfigStorage (C++ puro, reutilizable)
src/console/  Demo por consola
src/qt/       Interfaz gráfica Qt (MainWindow, ConfigViewerWindow)
tests/        Pruebas del Singleton
docs/         Diagrama de clases y lista de pruebas
```


## Compilar
```
cmake -S . -B build
cmake --build build
./build/singleton_console
./build/singleton_qt
./build/test_singleton
```
En Qt Creator: abrir `CMakeLists.txt` y ejecutar.


## Responsables
| Integrante | Rama | Aporte |
|---|---|---|
| Wilber | `feature/wilber-estructura-build` | Estructura del repo, CMake, README, integración |
| Jhon | `feature/jhon-singleton-core` | Clase Singleton `ConfigManager` |
| Diego | `feature/diego-storage` | Interfaz `ConfigStorage` y `FileConfigStorage` |
| Cristhian | `feature/cristhian-consola` | Demo por consola con `AppModule` |
| Jaime | `feature/jaime-qt-ventana` | Ventana principal Qt y `main_qt.cpp` |
| Gerson | `feature/gerson-visor-docs` | Ventana visor, pruebas y documentación |


Todas las ramas se integraron en `main` mediante Pull Request.