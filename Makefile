SRC_DIR = src/

all:
	$(MAKE) -C $(SRC_DIR) all

clean:
	$(MAKE) -C $(SRC_DIR) clean

fclean: clean
	$(MAKE) -C $(SRC_DIR) fclean

re: clean all