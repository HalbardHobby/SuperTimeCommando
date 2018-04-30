# Super Time Commando

## Estructura del proyecto

- `Content/Geometry`: Contiene Meshes básicas para la creación de niveles.
- `Content/Mannequin`: Contiene el maniquí para los diferentes personajes.
- `Content/TimeCommandoPrototype`: Contiene un prototipo de las mecánicas de
  juego elaboradas a partir de blueprints.
- `Source`: Acá se tiene el código en C++ del juego.

## Configuraciones especiales

- **Entradas**:

![bindings](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/configs/inputs.PNG)

## Mecánicas
**Nota:** Los Blueprints acá presentados son solo una muestra de los prototipos
conceptuales y no reflejan necesariamente su implementación final en C++

### Jugador

Implementado en `Source/SuperTimeCommando/Player/PlayerCharacter.cpp` y
`Source/SuperTimeCommando/Player/PlayerCharacter.h`

- **Movimiento**:  
  El personaje del jugador siempre se mueve de forma relativa a la posición de
  la cámara.

![movement](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/blueprints/movement.PNG)

- **Mirar hacia el cursor**:  
  El personaje siempre mira hacia la posición del cursor en la pantalla. Se coloca
  una interpolación para limitar la velocidad de rotación del personaje.

![look at cursor](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/blueprints/look_at_cursor.PNG)

- **Desplazar la vista**:  
  La cámara se desplaza un poco en la dirección que se encuentra el cursor
  relativo al personaje.

![camera offset](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/blueprints/camera_offset.PNG)

- **Rotación de la cámara (Extra)**:  
  El jugador es capaz de rotar la cámara del personaje.

![camera rotation](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/blueprints/camera_rotation.PNG)

### Patrulla IA

- **Cono de visión**:  
  Para el cono de visión se rastrea la geometría usando un EQS.

  ![eqs cone](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/on_scene/eqs_cone.PNG)

- **Tarea de Patrullaje**:  
  El Agente patrulla una serie de puntos predefinidos en un orden especifico.

  ![patrol task](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/blueprints/ai_patrol/patrol_task.PNG)

  `TODO:` Añadir lógica para comportamiento de combate y busqueda, adicional a
  máquina de estados finitos o arbol de comportamiento para manejar el estado
  general de la IA.

### Regresar el tiempo

- **Componente de actor**:  
  En primer lugar se tiene un componente personalizado que cada cierto tiempo
  toma un frame con la posición y rotación del actor que lo posee.

  ![record frame](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/blueprints/rewind_time/record_frame.png)

  Este mismo componente es capaz de regresar los frames interpolando entre ellos
  una vez recibe el flag requerido.

  ![rewind frames](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/blueprints/rewind_time/rewind_frames.PNG)

  Finalmente para poder coordinar la grabación y reproducción de los frames cada
  instancia de este componente se registra a un delegado manejado por el
  controlador del jugador.

  ![event bind](https://raw.githubusercontent.com/HalbardHobby/SuperTimeCommando/master/images/blueprints/rewind_time/event_bind.PNG)

  `TODO:` Añadir lógica para guardar estado de la IA
