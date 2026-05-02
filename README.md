# Space Invaders Game - Strawhats Edition 🚀

A classic arcade-style Space Invaders game developed in C++. Defend your territory against incoming waves of alien invaders!

## 👥 Authors
- **24L-0576**
- **24L-0852**

---

## 🎮 Features

- **Classic Gameplay**: Navigate your spaceship, dodge incoming aliens, and shoot them down before they cross the border.
- **Persistent High Scores**: Tracks and maintains the top 5 high scores across games via `highscore.txt`.
- **Save and Load**: Save your current game state and resume from where you left off via `savegame.txt`.
- **Lives System**: You start with 3 lives. Colliding with aliens or letting them reach the left border costs a life.
- **Winning Condition**: Reaching a score of 500 points wins the game!

---

## 🕹️ Controls

| Action | Key |
| :--- | :--- |
| **Start Game** | `S` (from main menu) |
| **Resume Game** | `R` (from main menu or pause menu) |
| **View High Scores**| `H` (from main menu) |
| **Spawn Spaceship** | `Spacebar` (at game start) |
| **Move Left** | `Left Arrow` |
| **Move Up** | `Up Arrow` |
| **Move Right** | `Right Arrow` |
| **Move Down** | `Down Arrow` |
| **Shoot Bullet** | `Enter` |
| **Pause Game** | `Escape` |
| **Save Game** | `S` (while paused) |
| **Quit Game** | `Q` |

---

## 📂 File Persistence

The game includes advanced file handling to manage high scores and save states:

- **`highscore.txt`**: Stores the top 5 high scores using an insertion sort algorithm to maintain ordering.
- **`savegame.txt`**: Saves the player's position, lives, current score, and alien locations, which can be loaded later to resume the session.

---

## 🛠️ Requirements & Setup

- **Language**: C++ (C++11 or higher recommended)
- **Dependencies**: Uses a local graphics and input helper library (`help.h`).
- **Compilation**: Compile all `.cpp` files in your C++ IDE or with your favorite compiler:
  ```bash
  g++ -o SpaceShooter "24L-0576 & 24L-0852.cpp.cpp"
  ```
