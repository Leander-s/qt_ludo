# QtLudo

## Requirements
    sudo apt install qt6-base-dev qt6-tools-dev qt6-tools-dev-tools build-essential cmake ninja-build

## ToDo
 - If human move, do all the things you need to do and store them in a struct 
   in the game widget. Then you can print everything needed immediately and 
   only have to call things like getPossibleMoves once inside gameWidget. On 
   keyevent. Check which key and store in struct as well. This way we get 
   skipped immediately if we can't move and don't have to press a button. Also 
   we dont interfere with the game when pressing another button (other than 
   1 -> 4)
    - fix this

 - Testing scripts work fine. Need a better, more standartised testing suite

 - coloring the map with highlights for possible moves

 - Implement the actual game (maybe with ai agents at first)
    - fix the game so it works properly

 - Camera movement
    - Make a camera class with position and angles
    - Make controls manipulate camera position and angles (WASD, mouse)
    - compute lookat using that

