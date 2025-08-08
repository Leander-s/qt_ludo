# QtLudo

## Build
    For a complete rebuild of everything, run cleanRebuild.
    For building the game and running all the unit tests, run buildGame.

## Requirements
    sudo apt install qt6-base-dev qt6-tools-dev qt6-tools-dev-tools build-essential cmake ninja-build

## ToDo
 - Update positions of beaten pieces

 - Make it so that multiple pieces on one square don't overlap but are smaller 
   and to the side

 - Fix the HUD

 - coloring the map with highlights for possible moves

 - Camera movement
    - Make a camera class with position and angles
    - Make controls manipulate camera position and angles (WASD, mouse)
    - compute lookat using that

