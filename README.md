# libvint

Free your C programs from the shackles of fixed-width integer data types!

## Introduction 

Ever wished to be able to add 1 into `UINT_MAX` without ending up with a wrap-around back to zero? Ever dreamed of bit-shifting an integer variable 150 places to the left? How about having an `uint<w>_t` data type, where w is any multiple of 8, at your disposal?

Me neither, but nonetheless **libvint** makes all this possible. It does this by throwing more bytes at the problem, at a great expense of processing speed.

## Description

Libvint uses dynamically allocated arrays of `uint8_t` for representing integer numbers of varying widths. Such array is typedef'd as a `vint` for convenience. Each element of a `vint` variable/array is typedef'd as a `vbyte`.

The most significant bit of the `vbyte` elements works as an end marker for the dynamic array. This is why the MSB is always "1" in the final `vbyte` of the array, while the most significant bits of all preceding `vbyte` elements are always "0".

A `vint` variable changes its memory allocation dynamically as its value is changed. A `vint` may also be manually resized.

## Usage

For short descriptions of the procedures, see the header file `libvint.h`. In addition, the test procedures in `main.c` show some usage instructions.

Use either `vint_new()` to create a new zero-initialized `vint` variable. Alternatively `vint_from_uint(uint64_t value)` can be used for creating a new `vint` variable and initializing it with an unsigned integer value.

After use, the memory taken by each `vint` variable should be freed with a corresponding call to `vint_erase(vint vnum)`.

## Bugs, limitations

Only unsigned integers are supported.
Libvint is just a fun hobby project, and as such may contain bugs or errors. Use at your own risk.  

## License

MIT

