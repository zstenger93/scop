NAME = scop
CFLAGS =  -Wno-c++11-extensions -std=c++11
LDFLAGS = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -framework OpenGL -framework CoreGraphics -framework CoreFoundation
INCLUDES = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include
GLEWSHIT = -I/Users/zstenger/.brew/Cellar/glew/2.2.0_1/include -L/Users/zstenger/.brew/Cellar/glew/2.2.0_1/lib -lGLEW -framework OpenGL

RM		= rm -rf
CC		= c++
SRC_DIR = src/
OBJ_DIR = objects/

SRC		= scop \
		  readObjectFile \
		  object \
		  glfw \
		  debugPrint \
		  mouse \
		  shader \
		  texture \

SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling..$(COLOR_END)"
	@$(CC) $(CFLAGS) $(GLEWSHIT) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)The project is compiled..$(COLOR_END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning...$(COLOR_END)"
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Cleaning done.$(COLOR_END)"


fclean: clean
	@echo "$(YELLOW)Cleaning everything...$(COLOR_END)"
	@$(RM) $(NAME) home_shrubbery
	@echo "$(GREEN)Cleaning done.$(COLOR_END)"

re:
	@echo "$(YELLOW)Recompiling...$(COLOR_END)"
	@make fclean
	@make all
	@echo "$(GREEN)The project has been recompiled.$(COLOR_END)"

t:
	./scop resources/42.obj textures/ok.jpg

.PHONY: all clean fclean re test

COLOR_END = \033[0;39m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
RED = \033[1;91m
GREEN = \033[1;92m
CYAN2 = \x1B[1;36m
CYAN = \033[1;96m