# projectVoid
A work-in-progress space shooter video game inspired by Space Invaders and others, written in pure C.  
The name isn't final. In fact, it is only a placeholder.

#### Dependencies  
- Some C compiler (obviously) - gcc was used for this project.
- [make](https://www.gnu.org/software/make/) - The build system.
- [raylib](http://www.raylib.com/) - The beginner-friendly, no frills video games programming library  
  - To install raylib on Linux, build it following the instructions [here](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux).
#### Structure of the project
Here's what the project structure looks like:
```
├── bin
│   └── void
├── dat
│   ├── em1.enmap
│   ├── em2.enmap
│   └── em3.enmap
├── LICENSE
├── Makefile
├── README.md
└── src
    ├── actors.c
    ├── collections.c
    ├── game.c
    ├── include
    │   ├── actors.h
    │   ├── collections.h
    │   ├── defaults.h
    │   ├── game.h
    │   ├── misc.h
    │   └── types.h
    ├── main.c
    └── misc.c

```
The `dat` folder will, in future, contain all assets like images, textures, sound files, files related to enemies and files describing levels etc.  
The `src` folder contains .c files and the `include` folder which contains the header files.
#### How to build?
After you've configured your environment, just do `make run` in the `projectVoid` folder.  
So `projectVoid$ make run` This will build and run the game.  
Please note that this was only tested on a Linux system (Pop!_OS 20.04), with gcc version 9.4.0 and raylib version 3.8.
#### Current state
The basic features like levels are still being developed.  
Right now, upon running the game, you see a player you control. It can shoot bullets at the various enemies which kill them instantly. The player has a few lives which are lost upon contact with any enemy, also destroying the enemy. 
The enemies don't fire back and upon finishing off one wave, another enemy wave spawns. Destroying all of them gives you a 'you win' screen while losing all lives throws a 'game over' screen. There are also, inevitably, a few bugs which need to be fixed.
#### Wishlist/Planned features
- Multiple levels
- Graphics for everything, e.g. player, enemies, bullets etc.
- Bosses and challenging boss fights
- Different enemy movement patterns
- Enemies that fire back
- Enemies that have health and can take a few shots--depending on the type of bullets--before dying
- Decorations for everything, like a starry space, or a planet in the background
- Sounds, like that of bullet fire, impact, damage, winning, losing etc.
- Everything retro themed like Space Invaders, Galaga and others
- Multiple player and enemy weapons, because only one simple bullet would be boring
- Power-Ups and Bonuses
- Score system
- A story (No idea how to accomplish this)
- And many more things which I may be missing currently
