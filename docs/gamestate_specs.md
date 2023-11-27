# Format of `gamestate.dat`

## Special padding: 3 bytes

0000 0000 0000 0000 0000 0000
---- ---- ---- ---- ---- ----


## Address of read pointer a: 32 bytes

- Address of score: 4 bytes
- Address of lanes' data: 4 bytes
- Address of player's data: 4 bytes
- Address of other objects' data: 16 bytes
- Padding: 4 bytes

## Data: unknown bytes

### Score: 4 bytes

### Lanes: $4N + 1$ bytes

- Number of lanes $N$: 1 bytes
- $y$ coordinate: $4N$ bytes

### Player: 5 bytes

- The numerical order of lane: 1 bytes
- Coordinate x: 4 bytes

### Cars, trucks, e.t.c: $5N + 1$ bytes

- Number of cars (or other) $N$: 1 bytes
- Objects data: $5N$ bytes
  - The numerical order of lane: 1 bytes
  - Coordinate x: 4 bytes