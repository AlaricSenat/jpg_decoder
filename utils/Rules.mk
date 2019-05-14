## Auto generated make tool, don't edit manually.
utils/$(OBJECT_DIR)/%.o: utils/%.c
	$(COMP) $@ $<
utils/$(OBJECT_DIR)/clip.o: utils/clip.c includes/utils.h includes/fwd.h
includes/utils.h:
includes/fwd.h:
utils/$(OBJECT_DIR)/map_file.o: utils/map_file.c includes/utils.h \
  includes/fwd.h
utils/$(OBJECT_DIR)/sampling.o: utils/sampling.c includes/utils.h \
  includes/fwd.h includes/jpg_decode.h includes/huffman.h
includes/jpg_decode.h:
includes/huffman.h:
