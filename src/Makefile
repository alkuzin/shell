include common.mk

INCLUDE_DIR  = ../include/
BUILTINS_DIR = builtins/
SHELL_DIR    = shell/

NAME = sh
SRC  = shell utils builtins

OBJS_PREFIXED = $(BUILTINS_DIR)shell_builtins.o $(SHELL_DIR)shell_main.o

$(OBJS_PREFIXED):
	$(MAKE) -C $(SHELL_DIR) all
	$(MAKE) -C $(BUILTINS_DIR) all

$(NAME): $(OBJS_PREFIXED)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) $(OBJS_PREFIXED) main.c -o $(NAME)

all: $(NAME)
	mv $(NAME) ../

clean:
	$(MAKE) -C $(SHELL_DIR) fclean
	$(MAKE) -C $(BUILTINS_DIR) fclean

fclean: clean
	rm -f ../$(NAME)

re: clean all