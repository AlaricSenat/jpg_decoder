## Auto generated make tool, don't edit manually.
jpg_decode/handlers/$(OBJECT_DIR)/%.o: jpg_decode/handlers/%.c
	$(COMP) $@ $<
jpg_decode/handlers/$(OBJECT_DIR)/huffman.o: \
  jpg_decode/handlers/huffman.c includes/handlers.h includes/fwd.h \
  includes/jpg_decode.h includes/huffman.h includes/stream.h
includes/handlers.h:
includes/fwd.h:
includes/jpg_decode.h:
includes/huffman.h:
includes/stream.h:
jpg_decode/handlers/$(OBJECT_DIR)/qt.o: jpg_decode/handlers/qt.c \
  includes/jpg_decode.h includes/fwd.h includes/huffman.h \
  includes/stream.h includes/utils.h
includes/utils.h:
jpg_decode/handlers/$(OBJECT_DIR)/sof.o: jpg_decode/handlers/sof.c \
  includes/handlers.h includes/fwd.h includes/jpg_decode.h \
  includes/huffman.h includes/stream.h includes/utils.h
jpg_decode/handlers/$(OBJECT_DIR)/sos.o: jpg_decode/handlers/sos.c \
  includes/handlers.h includes/fwd.h includes/jpg_decode.h \
  includes/huffman.h includes/stream.h includes/utils.h
