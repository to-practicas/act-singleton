# Lista de pruebas

| # | Prueba | Cómo hacerla | Resultado esperado |
|---|---|---|---|
| 1 | Pruebas automáticas | `./build/test_singleton` | Muestra "Todas las pruebas pasaron correctamente" |
| 2 | Instancia única (consola) | `./build/singleton_console`, opción 9 | Las dos direcciones son iguales |
| 3 | Persistencia (consola) | Opción 2 (cambiar nombre), 6 (guardar), salir y abrir de nuevo, opción 1 | El nombre cambiado se mantiene |
| 4 | Cambio de tema (Qt) | Elegir `dark` y pulsar "Aplicar y guardar" | La ventana cambia a tema oscuro |
| 5 | Misma instancia (Qt) | Abrir el visor y cambiar el idioma en la ventana principal | El visor muestra el valor nuevo |
| 6 | Restaurar (Qt) | Pulsar "Restaurar" | Vuelven los valores por defecto |

Responsable de las pruebas: Gerson.
