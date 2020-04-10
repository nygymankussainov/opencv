NAME = blur

CONFIG = ./options-config.ini

INCLUDES = ./

SOURCES = main.cpp ini_parser.cpp

OBJDIR = obj

OBJ = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

.PHONY: all clean fclean re

all: obj_dir $(NAME)

obj_dir:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp $(CONFIG)
	g++ -o $@ -c $<

$(NAME): $(OBJ)
	g++ -o $@ $(OBJ) `pkg-config --cflags --libs opencv`

clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
