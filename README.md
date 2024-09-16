# Snake
My very first project - a straightforward snake game written in C++. 
The code could use some refinement, considering I was in my early stages of learning programming at the time.
 
## Features
- Move using **W A S D**
- Monitor your current score and highscore
- Options to adjust the snake speed, start a new game or quit

## Quick Start

### 1. Clone the project

```sh
git clone https://github.com/JellyGamez/Snake.git
```

### 2. Go to the project directory

```sh
cd Snake
```

### 3. Compile

- Windows
```sh
g++ main.cpp -o main
```

- Linux
  
The linux version uses an external library you need to install:
```sh
sudo apt-get install ncurses-dev
g++ main.cpp -lncurses -o main
```

### 4. Launch the game

```sh
./main
```

## Note
The default terminal window may be too small, so make sure to resize it to fit the whole board and menu.
