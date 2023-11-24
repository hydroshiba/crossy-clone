# Format of `setting.dat`

## Volumes & sprites

These data will be stored at the start of the file:

- A 3-byte magic padding number is used at the beginning for a quick check of the file's validity. The value `0xDECADE` is used because it remains the same no matter the endianness of the system (reading from the most significant byte or the least significant byte is the same), and it also spells out "decade" which is nice. The remaining byte is used to contain 2 `Volume` types and a `Sprite`.

- A `Volume` type has 5 possible values (`min`, `low`, `medium`, `high`, `max`) which takes up 3 bits, hence 2 `Volume` types (one for music, one for SFX) can be stored with 6 bits. Since the `Sprite` enum current only has 3 options of `duck`, `chicken` or `cat` (3 possible values), it can be stored with the remaining 2 bits, filling a full byte.

Follow up these data are the highscores. The format of this section is as follows:

```
0000 0000  0000 0000  0000 0000  000 000 00
---- ----  ---- ----  ---- ----  --- --- --
D    E     C    A     D    E     MUS SFX SP
```

## Highscores

The game has 3 highscores for 1st, 2nd and 3rd place, each highscore is a `word` (`unsigned int`) type. Storing these highscores are straightforward as follows:

```
0000 0000 0000 0000 0000 0000 0000 0000
---- ---- ---- ---- ---- ---- ---- ----
1st place (4 bytes)

0000 0000 0000 0000 0000 0000 0000 0000
---- ---- ---- ---- ---- ---- ---- ----
2nd place (4 bytes)

0000 0000 0000 0000 0000 0000 0000 0000
---- ---- ---- ---- ---- ---- ---- ----
3rd place (4 bytes)
```

*These bytes are actually consecutive, I'm out of space*

To avoid the difference in endianness between systems, the highscores are stored in the settings as an array of 12 `byte` types instead of 3 `word` types. Endianness only affects the relative position between the bytes but not the bytes themselves, hence printing byte by byte will always result in the same value. To attain the highscores, pointer casting is used to retrieve `word` values from the array of `byte` types.
