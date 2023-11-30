# Format of `gamestate.dat`

## Special padding: 3 bytes
- These data used to check if the file contains gamestate or not

0000 0000  0000 0000  0000 0000
---- ----  ---- ----  ---- ----
D    E     F    C     A    D

## Address of read pointer a: 32 bytes (= 8 address at most, each address is an integer)
- These data will be stored right after the checking padding, it use for seek the read pointer for easier read data because there are some data that doesn't have a specifically size like name of player (type string) and more.

- Address of score and name: 4 bytes
- Address of lanes' data: 4 bytes
- Address of player's data: 4 bytes
- Address of other objects' data: 16 bytes
- Padding: 4 bytes

## Data: unknown bytes

### Score and name: $? + 4$ bytes

- Score: 4 bytes ------------------------------------- ($gamestate[0][0] -> gamestate[0][3]$)
- Name: unknown bytes ---------------------------- ($gamestate[0][4] -> gamestate[0][Name.size() + 4]$)

### Lanes: $4N + 1$ bytes

- Number of lanes $N$: 1 bytes ---------------------- ($gamestate[1][0]$)
- Lanes data: $8N$ bytes ----------------------------- ($gamestate[1][1] -> gamestate[1][4 * gamestate[1][0] + 4]$)
  - $y$ coordinate: $4$ bytes
  - Spawning time: $4$ bytes

### Player: 5 bytes

- The numerical order of lane: 1 bytes -------------- ($gamestate[2][0]$)
- Coordinate x: 4 bytes ------------------------------ ($gamestate[2][1] -> gamestate[2][4]$)

### Cars, trucks, e.t.c: $5N + 1$ bytes

- Number of cars (or other) $N$: 1 bytes ------------- ($gamestate[n][0]$)
- Objects data: $5N$ bytes ---------------------------- ($gamestate[n][1] -> gamestate[n][5 * gamestate[n][0] + 1]$)
  - The numerical order of lane: 1 bytes
  - Coordinate x: 4 bytes