## Auto generated make tool, don't edit manually.

OBJ_FILES_jpg_decode := dct.o \
                        decode.o \
                        decode_fetch.o \
                        handlers.o \
                        huffman.o \
                        insert_colors.o \
                        parse_jpg.o \
                        stream.o \
                        stream_get.o \
                        zigzag.o

OBJECTS += $(patsubst %, jpg_decode/$(OBJECT_DIR)/%, $(OBJ_FILES_jpg_decode))