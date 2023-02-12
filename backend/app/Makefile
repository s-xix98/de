# DE
# ------------------------------------------------------------------------------------------
NAME			:=		de
TARGET			:=		target
CC				:=		gcc
CFLAGS			:=		-Wall -Wextra -Werror -MMD -MP 
INCLUDE			:=		-I include
LIBS			:=		-lreadline

UNAME_M			:=		$(shell uname -m)

ifeq ($(UNAME_M), aarch64)
CFLAGS			+=		-D IS_ARM=1
endif

# SRCS
# ------------------------------------------------------------------------------------------
SRCS_DIR		:=		src
SRCS			:=		$(shell find $(SRCS_DIR) -type f -name '*.c')

# OBJS
# ------------------------------------------------------------------------------------------
OBJS_DIR		:=		obj
OBJS			:=		$(patsubst $(SRCS_DIR)%, $(OBJS_DIR)%, $(SRCS:%.c=%.o))
DEPENDS			:=		$(patsubst $(SRCS_DIR)%, $(OBJS_DIR)%, $(SRCS:%.c=%.d))

# MAKE
# ------------------------------------------------------------------------------------------
PHONY	:=	all
all: $(NAME) $(TARGET)

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBS) -o $(NAME)

# -mno-red-zone
$(TARGET): target.c Makefile
	$(CC) $(CFLAGS) -no-pie -static -g3 -o $(TARGET) target.c

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

PHONY	+=	clean
clean:
	rm -f $(OBJS)
	rm -f $(DEPENDS)

PHONY	+=	fclean
fclean: clean
	rm -rf $(OBJS_DIR)
	rm -f $(NAME) $(TARGET)

PHONY	+=	re
re: fclean all

PHONY	+=	fmt
fmt:
	clang-format -i $(shell find . -type f -name '*.c' -o -name '*.hpp')

# etc.
# ------------------------------------------------------------------------------------------
-include $(DEPENDS)

.PHONY: $(PHONY)
