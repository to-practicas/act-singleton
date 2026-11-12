# Diagrama de clases

```mermaid
classDiagram
    class ConfigStorage {
        <<abstract>>
        +load(data) bool
        +save(data) bool
    }
    class FileConfigStorage {
        -path_ : string
        +load(data) bool
        +save(data) bool
    }
    class ConfigManager {
        <<singleton>>
        -data_ : map
        -storage_ : ConfigStorage
        -ConfigManager()
        +instance() ConfigManager&
        +get(key, def) string
        +set(key, value) void
        +load() bool
        +save() bool
        +resetDefaults() void
    }
    class AppModule {
        <<abstract>>
        +show() void
    }
    class HeaderModule
    class ThemeModule
    class MainWindow
    class ConfigViewerWindow

    ConfigStorage <|-- FileConfigStorage
    ConfigManager o-- ConfigStorage
    AppModule <|-- HeaderModule
    AppModule <|-- ThemeModule
    AppModule ..> ConfigManager : usa
    MainWindow ..> ConfigManager : usa
    ConfigViewerWindow ..> ConfigManager : usa
```

## Lectura del diagrama
- **ConfigManager** es el único Singleton. Tiene constructor privado y se obtiene con `instance()`.
- **ConfigStorage** es una interfaz: `ConfigManager` no sabe si guarda en archivo, base de datos, etc.
- **FileConfigStorage** hereda de `ConfigStorage` y guarda en `config.ini`.
- **AppModule** (consola) y las ventanas Qt (`MainWindow`, `ConfigViewerWindow`) consumen la misma instancia.
```