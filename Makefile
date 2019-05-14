## Standard things
#
.SUFFIXES:
NAME		:= libjpg_decode.a
CC 		:= clang
AR		:= ar
AR_FLAGS	:= rc
CFLAGS		:= -I./includes -Wall -Wextra -Werror -g
LFLAGS		:= -lm
RM		:= rm -f
OBJECT_DIR	:= obj
COMP		:= $(CC) $(CFLAGS) -c -o
ifeq ($(shell uname -s), Darwin)
ECHO		:= echo
else
ECHO		:= echo -e
endif
#

## Sources directories
#
TEST_DIRS	:= tests
SRC_DIRS	:= jpg_decode jpg_decode/handlers utils
#

## Colors
#
BLUE		:= "\033[34m"
GREEN		:= "\033[32m"
RED		:= "\033[31m"
RESET		:= "\033[0m"
PNAME		:= $(BLUE)$(NAME)$(RESET)
#

.PHONY: all
all: $(NAME) $(SHORT_NAME)

## Including sources files
#
include $(patsubst %, %/Sources.mk, $(SRC_DIRS))
#

OBJ_DIRS	:= $(patsubst %, %/obj, $(SRC_DIRS))

$(NAME): $(LIBFT) $(OBJ_DIRS) $(OBJECTS) $(IMPL_OBJS)
	$(AR) $(AR_FLAGS) $(NAME) $(OBJECTS) $(IMPL_OBJS)
	@$(ECHO) $(PNAME)$(GREEN) "linking complete"$(RESET)

## Including compilation rules
#
include $(patsubst %, %/Rules.mk, $(SRC_DIRS))
#

$(LIBFT):
	@$(MAKELIBFT)

%/$(OBJECT_DIR):
	mkdir $@

## Including tests
#
-include $(patsubst %, %/Rules.mk, $(TEST_DIRS))
#

.PHONY: clean
clean:
	@$(RM) -r $(OBJ_DIRS)
	@$(ECHO) "Objects directories removed"

.PHONY: fclean
fclean: clean
	@$(RM) $(NAME) $(TEST_TARGETS)
	@$(ECHO) $(NAME) "deleted"

.PHONY: re
re: fclean all

.PHONY: makedeps
makedeps:
	python3 tools/gen_make_sources.py $(SRC_DIRS)
