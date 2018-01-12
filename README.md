# life-the-game
A c++ game I made at a summer camp.

## Compiling

To play this game, just navigate to and compile the included files in the `src` directory. Directions for Gcc:
```shell
g++ -o lifethegame Source.cpp item.h
chmod +x ./lifethegame.out
```
and to play:
```shell
./lifethegame.out
```
For Visual Studio, set up developer console and type:
```shell
cl /EHsc Source.cpp item.h /link /out:lifethegame.exe
```
And run the `exe` generated. (Or just create a new Visual Studio project, input both files, and run the program)

### Or...

Just run the exe in the `dist` folder. ¯\\_(ツ)_/¯

## Playing

Start by typing `help` to learn the commands then have fun! I'll let you find out the secrets on your own

## Savefiles

The file `save.txt` is a savefile for the game that is very overpowered. You can use it or any other savefiles by putting it in the same directory as the `lifethegame.exe` and running the `open` command in the game. Currently, items are buggy, so you might lose your items.
