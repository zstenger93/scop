NAME = scop
CFLAGS =  -Wno-deprecated-declarations -Wno-macro-redefined -Wno-c++11-extensions -std=c++11
LDFLAGS = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -framework OpenGL -framework CoreGraphics -framework CoreFoundation
INCLUDES = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include
GLEWSHIT = -I/Users/${USER}/.brew/Cellar/glew/2.2.0_1/include -L/Users/${USER}/.brew/Cellar/glew/2.2.0_1/lib -lGLEW -framework OpenGL

GLAD = glad.o
GLADLIB = gcc -c src/includes/glad/glad.c -Ilibs

# maybe adding multiple texture option later
# change the files here for the texures
TEXTURE_NAME= ok

EXEC = ./scop
VERTEX_SOURCE = ../src/shader/vertexSource.vertex
FRAGMENT_SOURCE = ../src/shader/fragmentSource.fragment
TEXTURE = ../textures/${TEXTURE_NAME}.jpeg
OBJECT_42 = ../resources/42.obj
OBJECT_TEAPOT = ../resources/teapot.obj
OBJECT_SPIDER = ../resources/spider.obj
OBJECT_SKULL = ../resources/skull.obj
OBJECT_AXE = ../resources/axe.obj
OBJECT_ARMOR = ../resources/armor.obj
OBJECT_ALIENANIMAL = ../resources/alienanimal.obj
OBJECT_BUILDING = ../resources/building.obj
OBJECT_STARWARS = ../resources/sw.obj
OBJECT_HEILBRONN = ../resources/hb.obj
OBJECT_CAMEL = ../resources/Camel.obj

REBUILD = make re
RM		= rm -rf
CC		= c++
SRC_DIR = src/
OBJ_DIR = objects/

SRC = scop \
	  glfw \
	  camera \
	  render \
	  object \
	  texture \
	  keyPress \
	  renderText \
	  shader/shader \
	  processObjFile \

SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling..$(COLOR_END)"
	@${GLAD_LIB}
	@$(CC) $(CFLAGS) $(GLEWSHIT) $(INCLUDES) ${GLAD} $(LDFLAGS) $(OBJS) -o $(NAME)
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

42:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_42}

tp:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_TEAPOT}

sp:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_SPIDER}

sk:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_SKULL}

ax:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_AXE}

am:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_ARMOR}

an:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_ALIENANIMAL}

bf:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_BUILDING}

sw:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_STARWARS}

hb:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_HEILBRONN}

cm:
	@${REBUILD}
	@${EXEC} ${TEXTURE} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_CAMEL}

.PHONY: all clean fclean re 42 tp sp sk ax am an bf sw hb wp

COLOR_END = \033[0;39m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
RED = \033[1;91m
GREEN = \033[1;92m
CYAN2 = \x1B[1;36m
CYAN = \033[1;96m