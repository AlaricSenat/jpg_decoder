## Auto generated make tool, don't edit manually.
jpg_decode/$(OBJECT_DIR)/%.o: jpg_decode/%.c
	$(COMP) $@ $<
jpg_decode/$(OBJECT_DIR)/dct.o: jpg_decode/dct.c includes/jpg_decode.h \
  includes/fwd.h includes/huffman.h includes/utils.h
includes/jpg_decode.h:
includes/fwd.h:
includes/huffman.h:
includes/utils.h:
jpg_decode/$(OBJECT_DIR)/decode.o: jpg_decode/decode.c \
  includes/jpg_decode.h includes/fwd.h includes/huffman.h \
  includes/stream.h includes/utils.h
includes/stream.h:
jpg_decode/$(OBJECT_DIR)/decode_fetch.o: jpg_decode/decode_fetch.c \
  includes/jpg_decode.h includes/fwd.h includes/huffman.h \
  includes/stream.h includes/utils.h
jpg_decode/$(OBJECT_DIR)/handlers.o: jpg_decode/handlers.c \
  includes/handlers.h includes/fwd.h includes/jpg_decode.h \
  includes/huffman.h includes/stream.h
includes/handlers.h:
jpg_decode/$(OBJECT_DIR)/huffman.o: jpg_decode/huffman.c \
  includes/huffman.h includes/fwd.h includes/stream.h \
  includes/jpg_decode.h
jpg_decode/$(OBJECT_DIR)/insert_colors.o: jpg_decode/insert_colors.c \
  includes/jpg_decode.h includes/fwd.h includes/huffman.h \
  includes/utils.h
jpg_decode/$(OBJECT_DIR)/parse_jpg.o: jpg_decode/parse_jpg.c \
  includes/jpg_decode.h includes/fwd.h includes/huffman.h \
  includes/stream.h includes/handlers.h includes/utils.h
jpg_decode/$(OBJECT_DIR)/stream.o: jpg_decode/stream.c includes/stream.h \
  includes/fwd.h
jpg_decode/$(OBJECT_DIR)/stream_get.o: jpg_decode/stream_get.c \
  includes/stream.h includes/fwd.h
jpg_decode/$(OBJECT_DIR)/zigzag.o: jpg_decode/zigzag.c \
  includes/jpg_decode.h includes/fwd.h includes/huffman.h
