# Format of gamestate.dat

## Address of read pointer a: 32 bytes
- Address of lanes' data: 4 bytes
- Address of player's data: 4 bytes
- Address of other objects' data: 16 bytes
- Padding: 8 bytes

## Data: unknown bytes

### Lanes: $4N + 1$ bytes
- Number of lanes $N$: 1 bytes
- $y$ coordinate: $4N$ bytes

### Player: 8 or 5 bytes
- Address of corresponding lane (or the numerical order of lane): 4 bytes (or 1 bytes)
- Coordinate x: 4 bytes

### Cars, trucks, e.t.c: 8\*nC+1 or 5\*nC+1 bytes
- Number of cars (or other) nC: 1 bytes
- Objects data: 8\*nC bytes (or 5\*nC bytes)
    - Address of corresponding lane (or the numerical order of lane): 4 bytes (or 1 bytes)
    - Coordinate x: 4 bytes