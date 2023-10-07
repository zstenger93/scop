NAME = scop
CFLAGS =  -Wno-deprecated-declarations -Wno-macro-redefined -Wno-c++11-extensions -std=c++11
LDFLAGS = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -framework OpenGL -framework CoreGraphics -framework CoreFoundation
INCLUDES = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include
GLEWSHIT = -I/Users/${USER}/.brew/Cellar/glew/2.2.0_1/include -L/Users/${USER}/.brew/Cellar/glew/2.2.0_1/lib -lGLEW -framework OpenGL

RM		= rm -rf
CC		= c++
SRC_DIR = src/
OBJ_DIR = objects/

# SRC		= scop \
# 		  readObjectFile \
# 		  object \
# 		  glfw \
# 		  debugPrint \
# 		  mouse \
# 		  shader \
# 		  texture \

SRC = new/scop \
	  new/shader \
	  new/camera \
	  new/glfw \
	  new/processObjFile \

SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling..$(COLOR_END)"
	@gcc -c src/includes/glad/glad.c -Ilibs
	@$(CC) $(CFLAGS) $(GLEWSHIT) $(INCLUDES) glad.o $(LDFLAGS) $(OBJS) -o $(NAME)
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
	@rm -rf ${OBJ_DIR}
	@make all
	@echo "$(GREEN)The project has been recompiled.$(COLOR_END)"

t:
	make re
	./scop resources/42.obj textures/ok.jpg

tp:
	make re
	./scop resources/teapot.obj textures/ok.jpg

tsk:
	make re
	./scop resources/skull.obj textures/ok.jpg

tsp:
	make re
	./scop resources/spider.obj textures/ok.jpg

tsa:
	make re
	./scop resources/alienanimal.obj textures/ok.jpg


tx:
	make re
	./scop ../textures/ok.jpg ../src/new/vertexSource.vertex ../src/new/fragmentSource.fragment ../resources/spider.obj

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