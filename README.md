*This proect was something something 42 curriculum by pfreire-, rmedeiro*

# Pac-Man 3D
## A faituful-ish recreating of the classic 80s arcade game

## Description
Pac-Man is a arcade, top down maze runner where your hero, Pac-Man, must eat all pacdots ina inescapable maze while running away from mean ghosts.


# Chracters
## Pac-Man
Pac-Man is faster than the ghosts in most cases, exept when eating pacdots. Pac-Man has the ability of corner cutting, he can trun inot a corner a bit early or a bit later than exactly 90 degres. When used by a skilled player it can be used to get an edge on the ghosts and run away in time.

## Ghosts
### Shadow "Blinky"
The most agressive of the ghosts, it pursues Pac-Man directy, it is also the fastest ghost, this agressive little guy will be sure to keep the presure on the player, espeially when few pacdots are left in the maze
### Speedy "Pinky"
This ghost works directly with Blinky to trap Pac-Man, aiming for 4 tiles in front of the player, Pinky is sure to corner Pac-Man with the help of Blinky
### Bashful "Inky"
This ghost is the hardest to predict, using Blinky's current possition along with Pac-Man's it will work to flank him where least expected
### Pokey "Clyde"
This ghost is unique, it will pursue pacman directly but at the last second shy away to it's corner

# Instructons
Compile the game using `make`
Run it as so
```bash
./cub3d ./path/to/map.ber [debug_mode=y] [XX]
```

Where the game must receive a map file in a .ber extension. If you wish to run it in Debug_mode you may includ the flag "debug_mode=y"
and XX is the number of the event corresponding to your controller
Yoy may find this number by running
```bash
cat /proc/bus/input/devices
```
in your terminal while your command is connected and find this line





