# C++ ncurses Snake Game
A Snake game using `ncurses` library to control terminal IO.

## Classes
1. `class Game`
- Basic game functionalities: 
	- read keyboard
	- set fresh rate based on given FPS
	- check it's time to update a frame
- `init()`: setup initial state pattern object
- `start()`: game loop, keep updating timer, reading input, calling `state->update()`, and state object determine what to do 
- Use `State Pattern` to control what to update in game loop

2. `class SnakeGame`
- Inherited from `game`
- Use `SnakeMap` and `Snake` to maintain current state of game
- Define inherited `StateBase` types for different game stage
- (on every frame) Update snake direction(from user input), snake movement, check collision, and most importantly draw game scene

3. `class SnakeMap`
- Maintain info of map size, offset (for calculate actual pos from drawn pos)
- Record which position is occupied (i.e. by snake, boundary, food...), only knows a pos is not empty, no idea what the item is
- Convert Coord2D (the pos shown on terminal) to real index of internal map
- To generate a non-occupied pos for SnakeGame to generate food

4. `class Snake`
- Maintain the pos of body by doubly-ended queue
- Use direction (left, right, up, down...) to determine next movement pos
- Record ate food, to increase the length of body


## TODO
1. menu, pause, resume, restart, replay
