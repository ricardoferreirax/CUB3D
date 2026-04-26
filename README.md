*This proect was something something 42 curriculum by pfreire-, rmedeiro*

# Pac-Man 3D
## A faituful-ish recreating of the classic 80s arcade game

## Description
Pac-Man is a arcade, top down maze runner where your hero, Pac-Man, must eat all pacdots ina inescapable maze while running away from mean ghosts.

# Modes
The game features 2 modes, Pac-Man Mode and Cub3d mode.
In Pac-Man mode the game will be ghosts will be active and you'll control Pac-Man by global directions, based on North, East, West and South (see control scheme for more details). In Cub3d mode will will be able to explore the Maze without the ghostly apparitions and be able to access some restricted areas.

# Instructons
Compile the game using `make`
Run it as so
```bash
./cub3d ./path/to/map.ber [debug_mode=y] [XX]
```

Where the game must receive a map file in a .ber extension. If you wish to run it in Debug Mode you may include the flag "debug_mode=y"
XX is the number of the event corresponding to your controller
You may find this number by running ```cat /proc/bus/input/devices``` in your terminal while your command is connected and find this line

```bash
I: Bus=0005 Vendor=054c Product=09cc Version=8100
N: Name="Wireless Controller"
P: Phys=
S: Sysfs=/devices/virtual/misc/uhid/0005:054C:09CC.0010/input/input39
U: Uniq=84:30:95:10:46:23
H: Handlers=event24 <- This number js0  
B: PROP=0
B: EV=20000b
B: KEY=7fdb000000000000 0 0 0 0
B: ABS=3003f
B: FF=107030000 0
```

The game was only tested with a Dualshock 4 but any standard command should work.


# Pac-Man Mode
### Run around and eathem all. just don't get caught
Classic Pac-Man. Your objective is to simple eat all dots on the maze. The ghosts will pursue you, if you touch them it will hurt. Those bigger pellets might give them a taste fo their own medicine,

Use the provided file original.ber to play on the original map.

## Basics
Ghosts will pursue Pac-Man until they don't. They are 4 possible states: Chase, Scatter, Frightened and Eaten. Using Debug mode you may understand exactly what they do in each state and see when they change their state.

# Controls
This control scheme is made for a Dualshock 5 but it should work with any controller.
![alt text](assets/sprites/Pac_Man_Control_Scheme.png)
# Chracters
## Pac-Man
Pac-Man is faster than the ghosts in most cases, execpt when eating pacdots. Pac-Man has the ability of corner cutting, he can turn in to a corner a bit early or a bit later than exactly 90 degres. When used by a skilled player it can be used to get an edge on the ghosts and run away in time.

## Ghosts
### Shadow "Blinky" <img src="assets/textures/ghosts/blinky_0.png" alt="Blinky" width="24" />
The most agressive of the ghosts, it pursues Pac-Man directy, it is also the fastest ghost, this agressive little guy will be sure to keep the presure on the player, espeially when few pacdots are left in the maze
### Speedy "Pinky" <img src="assets/textures/ghosts/pinky_0.png" alt="Blinky" width="24" />
This ghost works directly with Blinky to trap Pac-Man, aiming for 4 tiles in front of the player, Pinky is sure to corner Pac-Man with the help of Blinky
### Bashful "Inky" <img src="assets/textures/ghosts/inky_0.png" alt="Blinky" width="24" />
This ghost is the hardest to predict, using Blinky's current possition along with Pac-Man's it will work to flank him where least expected
### Pokey "Clyde" <img src="assets/textures/ghosts/clyde_0.png" alt="Blinky" width="24" />
This ghost is unique, it will pursue pacman directly but at the last second shy away to it's corner

# Cube3D Mode
In this mode you wil be able to look around the map, open gates and take a nice peaceful stroll.

This control scheme is made for a Dualshock 5 but it should work with any controller.
![alt text](assets/sprites/Cube_Control_Scheme.png.png)

# Custom Map
Both Cub3D and Pac-Man mode allow for a custom map to be used. As long as the map follows the following requirements

### No Forbidden Characters
The map must contain only expected characters and those are:
'1' - Wall  
'0' - Open Space  
'.' - Pac-dot  

[NEWS] - The player position and to where it spawns looking (e.g. N ->   North, E-> East W-> West, S -> Sounth)

'b' - Blinky's Scatter Target  
'p' - Pinky's Scatter Target  
'i' - Inky's Scatter Target  
'c' - Clyde's Scatter Target  
(Ghosts with missing Scatter Targets will be considered Disabled and will not appear during gameplay)

