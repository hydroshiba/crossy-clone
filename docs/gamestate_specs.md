# Format of `gamestate.dat`

## Special padding: 3 bytes

## Address of read pointer a: 32 bytes
- Address of lanes' data: 4 bytes
- Address of player's data: 4 bytes
- Address of other objects' data: 16 bytes
- Address of score: 4 bytes
- Padding: 4 bytes

## Data: unknown bytes

### Lanes: $4N + 1$ bytes
- Number of lanes $N$: 1 bytes
- $y$ coordinate: $4N$ bytes

### Player: 8 or 5 bytes
- Address of corresponding lane (or the numerical order of lane): 4 bytes (or 1 bytes)
- Coordinate x: 4 bytes

### Cars, trucks, e.t.c: $8N + 1$ or $5N + 1$ bytes
- Number of cars (or other) $N$: 1 bytes
- Objects data: $8N$ bytes (or $5N$ bytes)
    - Address of corresponding lane (or the numerical order of lane): 4 bytes (or 1 bytes)
    - Coordinate x: 4 bytes

### Score: 4 bytes