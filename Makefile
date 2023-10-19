NAME = scop
CFLAGS =  -Wno-deprecated-declarations -Wno-macro-redefined -Wno-c++11-extensions -std=c++11
LDFLAGS = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -framework OpenGL -framework CoreGraphics -framework CoreFoundation
INCLUDES = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include
GLEWSHIT = -I/Users/${USER}/.brew/Cellar/glew/2.2.0_1/include -L/Users/${USER}/.brew/Cellar/glew/2.2.0_1/lib -lGLEW -framework OpenGL

GLAD = glad.o
GLADLIB = gcc -c src/includes/glad/glad.c -Ilibs

EXEC = ./scop
VERTEX_SOURCE = ../src/shader/vertexSource.vertex
FRAGMENT_SOURCE = ../src/shader/fragmentSource.fragment

# Textures
TEXTURE_OK = ../textures/ok.jpeg
TEXTURE_COLORS = ../textures/colors.jpeg
TEXTURE_SKULL = ../textures/skull.jpeg
TEXTURE_CAMEL = ../textures/camel.jpeg
TEXTURE_UVMAP = ../textures/uvmap.jpeg
TEXTURE_TREX = ../textures/trex.jpeg
# TEXTURE_PARROT = ../textures/parrot.png
# TEXTURE_PUMPKIN = ../textures/pumpkin.png
# TEXTURE_TCP = ../textures/tcp.jpeg

TEXTURES = ${TEXTURE_OK} ${TEXTURE_COLORS} ${TEXTURE_CAMEL} \
		   ${TEXTURE_SKULL} ${TEXTURE_TREX} ${TEXTURE_UVMAP} \

# Objects
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
OBJECT_CASTLE = ../resources/castle.obj
OBJECT_TREX = ../resources/trex.obj
OBJECT_PUMPKIN = ../resources/pumpkin.obj
OBJECT_HOUSE = ../resources/ohouse.obj
OBJECT_PARROT = ../resources/parrot.obj
OBJECT_TCP = ../resources/tcp.obj
OBJECT_PLANE = ../resources/pyramids.obj

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
	@${GLADLIB}
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
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_42} ${TEXTURES}

tp:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_TEAPOT} ${TEXTURES}

sp:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_SPIDER} ${TEXTURES}

sk:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_SKULL} ${TEXTURES}

ax:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_AXE} ${TEXTURES}

am:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_ARMOR} ${TEXTURES}

an:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_ALIENANIMAL} ${TEXTURES}

bf:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_BUILDING} ${TEXTURES}

sw:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_STARWARS} ${TEXTURES}

hb:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_HEILBRONN} ${TEXTURES}

cm:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_CAMEL} ${TEXTURES}

cs:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_CASTLE} ${TEXTURES}

tx:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_TREX} ${TEXTURES}

hs:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_HOUSE} ${TEXTURES}

pr:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_PARROT} ${TEXTURES}

tc:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_TCP} ${TEXTURES}

pl:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_PLANE} ${TEXTURES}

.PHONY: all clean fclean re 42 tp sp sk ax am an bf sw hb cm cs tx hs pr tc pl

COLOR_END = \033[0;39m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
RED = \033[1;91m
GREEN = \033[1;92m
CYAN2 = \x1B[1;36m
CYAN = \033[1;96m