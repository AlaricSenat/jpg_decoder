# jpg_decoder
Toy jpeg image decoder library, for educational purpose only

Only baseline compression is supported yet.

## Build & Usage

To build just use `make`, it will generate `libjpg_decode.a`

To decode a jpeg image into a rgb stream simply include `./include/jpg_decode.h` and call `jpg_decode(const char *path, unsigned *w, unsigned *h)` and don't forget to free the stream after use.

**This project is a student exercise and is by no mean intended to be used in 'real life' programs**
