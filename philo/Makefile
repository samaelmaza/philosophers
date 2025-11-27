NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/clean.c \
		$(SRC_DIR)/monitor.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/threads.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/utils.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS = $(INC_DIR)/philosophers.h

all: $(NAME)
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(CYAN)Creating object directory...$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "$(RED)Object files removed.$(RESET)"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(RED)$(NAME) removed.$(RESET)"; \
	fi

test-0:
	@echo "$(BLUE)test-0$(RESET)"
	@echo "$(BLUE)Death test at 310ms$(RESET)"
	./$(NAME) 4 310 200 100

test-1:
	@echo "$(BLUE)test-1$(RESET)"
	@echo "$(BLUE)Death test at 310ms$(RESET)"
	./$(NAME) 5 410 200 200

test-2:
	@echo "$(BLUE)test-0$(RESET)"
	@echo "$(BLUE)Death test at 310ms$(RESET)"
	./$(NAME) 4 310 200 100

re: fclean all

help:
	@echo "$(CYAN)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)              - Build the program"
	@echo "  $(GREEN)clean$(RESET)            - Remove object files"
	@echo "  $(GREEN)fclean$(RESET)           - Remove object files and executable"
	@echo "  $(GREEN)re$(RESET)               - Rebuild everything"
	@echo "  $(GREEN)test-2$(RESET)           - A little test with 2 commands"
	@echo "  $(GREEN)test-3$(RESET)           - A little test with 3 commands"
	@echo "  $(GREEN)test-4$(RESET)           - A little test with 4 commands"
	@echo "  $(GREEN)help$(RESET)             - Show this help"

.PHONY: all clean fclean re help test-2 test-3 test-4
.PRECIOUS: $(OBJ_DIR)/%.o
