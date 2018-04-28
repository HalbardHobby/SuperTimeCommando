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

### Jugador

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
