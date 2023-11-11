# Format of gamestate.dat

## Address of read pointer a: 32 bytes
- Address of lanes' data: 4 bytes
- Address of player's data: 4 bytes
- Address of other objects' data: 16 bytes
- Padding: 8 bytes

## Data

### Lanes
- Number of lanes b: 1 bytes
- Coordinate y: 4*b bytes

### Player
- Address of corresponding lane (or the numerical order of lane): 4 bytes (or 1 bytes)
- Coordinate x: 4 bytes

### Cars, trucks, e.t.c
- Number of cars (or other): 1 bytes
- Objects data:
    - Address of corresponding lane (or the numerical order of lane): 4 bytes (or 1 bytes)
    - Coordinate x: 4 bytes