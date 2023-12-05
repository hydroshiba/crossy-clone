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
- Address of other objects' data: 4 bytes
- Padding: 16 bytes

## Data: unknown bytes

### Score and offset: $8$ bytes

- Score: 4 bytes ------------------------------------- ($gamestate[0][0] -> gamestate[0][3]$)
- Offset: 4 bytes ------------------------------------- ($gamestate[0][4] -> gamestate[0][7]$)

### Lanes: $13N$ bytes

- Number of lanes: $N$ (this isn't a stored data)
- Lanes data: $9N$ bytes ----------------------------- ($gamestate[1][0] -> gamestate[1][13 * N - 1]$)
  - $y$ coordinate: $4$ bytes
  - Speed: $4$ bytes
  - Traffic state: $1$ bytes

### Player: $5 + ???$ bytes

- The numerical order of lane: $1$ bytes ------------- ($gamestate[2][0]$) ($lanes[this]$ has this player)
- $x$ coordinate: $4$ bytes ----------------------------- ($gamestate[2][1] -> gamestate[2][8]$)
- Name: unknown bytes ---------------------------- ($gamestate[2][9] -> gamestate[2][Name.size() + 4]$)


### Cars, trucks: $5N$ bytes

- Number of cars (and trucks): $N$ (this isn't a stored data)
- Objects data: $9N$ bytes ---------------------------- ($gamestate[n][0] -> gamestate[n][9 * N - 1]$)
  - The numerical order of lane: 1 bytes ($lanes[this]$ contains this vehicles)
  - $x$ coordinate: 5 bytes