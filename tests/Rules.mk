TEST_CC			:= clang
TEST_CFLAGS		:= -I./includes
TEST_LFLAGS		:= -L. -lparse_jpg -lm

CURR_DIR	:= tests
TEST_FILES	:=  tests.c \
				stream.c

TEST_OBJECTS	:= $(addprefix $(CURR_DIR)/$(OBJECT_DIR)/, $(TEST_FILES:.c=.o))
RUN_TEST_RULES	:= $(addprefix test_, $(TEST_FILES:.c=))

TEST_FILES	:= $(addprefix $(CURR_DIR)/, $(TEST_FILES))
TEST_TARGETS	:= $(TEST_FILES:.c=)
TEST_OBJ_DIR	:= $(CURR_DIR)/$(OBJECT_DIR)

OBJ_DIRS 	+= $(TEST_OBJ_DIR)

.PRECIOUS: $(TEST_TARGETS) $(TEST_OBJECTS)
.PHONY: test_all
test_all: $(RUN_TEST_RULES)

.PHONY: clear_tests
clear_tests:
	rm -rf $(TEST_OBJ_DIR)
	rm -f $(TEST_TARGETS)

test_%: all $(TEST_OBJ_DIR) $(CURR_DIR)/%
ifeq ($(shell uname -s), Darwin)
	$(eval FAIL := $(shell script -q $*.out $(CURR_DIR)/$* > /dev/null; echo $$?))
else
	$(eval FAIL := $(shell script -qec $(CURR_DIR)/$* $*.out > /dev/null; echo $$?))
endif
	@if [ $(FAIL) -gt 0 ]; \
		then \
		$(ECHO) "["$(RED)KO$(RESET)"] -" $*; \
		cat $*.out; \
		else \
		$(ECHO)  "["$(GREEN)OK$(RESET)"] -" $*; \
		fi
	@rm $*.out

$(CURR_DIR)/%: $(CURR_DIR)/$(OBJECT_DIR)/%.o $(NAME)
	$(TEST_CC) -o $@ $<  $(TEST_LFLAGS)

$(CURR_DIR)/$(OBJECT_DIR)/%.o: $(CURR_DIR)/%.c
	$(TEST_CC) $(CFLAGS) $(TEST_CFLAGS) -c -o $@ $<

$(TEST_OBJ_DIR):
	mkdir $@
