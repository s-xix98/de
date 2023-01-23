# DE
# ------------------------------------------------------------------------------------------
NAME			:=		de
TARGET			:=		target
CC				:=		gcc
CFLAGS			:=		-Wall -Wextra -Werror -MMD -MP 
INCLUDE			:=		-I include

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

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

$(TARGET): target.c
	$(CC) $(CFLAGS) -no-pie -o $(TARGET) target.c

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

PHONY	+=	clean
clean:
	rm -f $(OBJS)
	rm -f $(DEPENDS)

PHONY	+=	fclean
fclean: clean
	rm -rf $(OBJS_DIR)
	rm -f $(NAME)

PHONY	+=	re
re: fclean all

# etc.
# ------------------------------------------------------------------------------------------
-include $(DEPENDS)

.PHONY: $(PHONY)
