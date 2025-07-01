# QtLudo

## Requirements
    sudo apt install qt6-base-dev qt6-tools-dev qt6-tools-dev-tools build-essential cmake ninja-build

## ToDo
 - color the "map" in the correct way
    - make it possible to color single tiles
    - do we want to implement tiles in this way or do I want a single model for the entire grid
    - maybe use a texture for the grid and figure out the positions?

 - Implement the actual game (maybe with ai agents at first)
    - implement the game
    - get player input (ray marching required...)
        - click on figures and then on space where they should move
 - Camera movement
    - Make a camera class with position and angles
    - Make controls manipulate camera position and angles (WASD, mouse)
    - compute lookat using that

