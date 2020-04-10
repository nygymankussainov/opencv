NAME = blur

CONFIG = ./options-config.ini

INCLUDES = ./includes

SRCDIR = src
OBJDIR = obj

SOURCES = main.cpp ini_parser.cpp

SRC = $(addprefix $(SRCDIR)/, $(SOURCES))

OBJ = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

.PHONY: all clean fclean re

all: obj_dir $(NAME)

obj_dir:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(CONFIG)
	g++ -o $@ -c $< -I $(INCLUDES)

$(NAME): $(OBJ)
	g++ -o $@ $(OBJ) `pkg-config --cflags --libs opencv`
clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
