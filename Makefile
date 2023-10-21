NAME = scop
CFLAGS =  -Wno-deprecated-declarations -Wno-macro-redefined -Wno-c++11-extensions -std=c++11
CPPFLAGS=`pkg-config --cflags freetype2`
LDFLAGS = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -framework OpenGL -framework CoreGraphics -framework CoreFoundation
GLFW = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include
FREETYPE = -I/Users/zstenger/.brew/include/freetype2
GLEWSHIT = -I/Users/${USER}/.brew/Cellar/glew/2.2.0_1/include -L/Users/${USER}/.brew/Cellar/glew/2.2.0_1/lib -lGLEW -framework OpenGL

GLAD = glad.o
GLADLIB = gcc -c src/includes/glad/glad.c -Ilibs

EXEC = ./scop

# Vertex and Fragment shader source files
VERTEX_SOURCE = ../src/shader/vertexSource.vertex
FRAGMENT_SOURCE = ../src/shader/fragmentSource.fragment

RS = ../resources/
TX = ../textures/

# Textures
TEXTURE_OK = ${TX}ok.jpeg
TEXTURE_COLORS = ${TX}colors.jpeg
TEXTURE_SKULL = ${TX}skull.jpeg
TEXTURE_CAMEL = ${TX}camel.jpeg
TEXTURE_UVMAP = ${TX}uvmap.jpeg
TEXTURE_TREX = ${TX}trex.jpeg
TEXTURE_PUMPKIN = ${TX}pumpkin.png
TEXTURE_MONSTER = ${TX}monster.jpeg

TEXTURES = ${TEXTURE_OK} ${TEXTURE_COLORS} ${TEXTURE_CAMEL} \
		   ${TEXTURE_SKULL} ${TEXTURE_TREX} ${TEXTURE_UVMAP} \
		   ${TEXTURE_MONSTER} ${TEXTURE_PUMPKIN} \

# Objects
OBJECT_42 = ${RS}42.obj
OBJECT_TEAPOT = ${RS}teapot.obj
OBJECT_SPIDER = ${RS}spider.obj
OBJECT_SKULL = ${RS}skull.obj
OBJECT_AXE = ${RS}axe.obj
OBJECT_ARMOR = ${RS}armor.obj
OBJECT_ALIENANIMAL = ${RS}alienanimal.obj
OBJECT_BUILDING = ${RS}building.obj
OBJECT_STARWARS = ${RS}sw.obj
OBJECT_HEILBRONN = ${RS}hb.obj
OBJECT_CAMEL = ${RS}Camel.obj
OBJECT_CASTLE = ${RS}castle.obj
OBJECT_TREX = ${RS}trex.obj
OBJECT_PUMPKIN = ${RS}pumpkin.obj
OBJECT_HOUSE = ${RS}ohouse.obj
OBJECT_PARROT = ${RS}parrot.obj
OBJECT_TCP = ${RS}tcp.obj
OBJECT_PLANE = ${RS}plane.obj
OBJECT_SCULP = ${RS}sculp.obj
OBJECT_MONSTER = ${RS}monster.obj

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
	  includes/imgui/imgui \
	  includes/imgui/imgui_demo \
	  includes/imgui/imgui_draw \
	  includes/imgui/imgui_tables \
	  includes/imgui/imgui_widgets \
	  includes/imgui/imgui_impl_glfw \
	  includes/imgui/imgui_impl_opengl3 \

SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling..$(COLOR_END)"
	@${GLADLIB}
	@$(CC) $(CFLAGS) ${CPPFLAGS} $(GLEWSHIT) $(GLFW) ${FREETYPE} ${GLAD} $(LDFLAGS) $(OBJS) -o $(NAME)
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

teapot:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_TEAPOT} ${TEXTURES}

spider:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_SPIDER} ${TEXTURES}

skull:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_SKULL} ${TEXTURES}

axe:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_AXE} ${TEXTURES}

alien:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_ALIENANIMAL} ${TEXTURES}

building:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_BUILDING} ${TEXTURES}

sw:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_STARWARS} ${TEXTURES}

hb:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_HEILBRONN} ${TEXTURES}

camel:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_CAMEL} ${TEXTURES}

castle:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_CASTLE} ${TEXTURES}

trex:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_TREX} ${TEXTURES}

house:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_HOUSE} ${TEXTURES}

parrot:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_PARROT} ${TEXTURES}

tric:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_TCP} ${TEXTURES}

plane:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_PLANE} ${TEXTURES}

pumpkin:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_PUMPKIN} ${TEXTURES}

monster:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_MONSTER} ${TEXTURES}

sculp:
	@${REBUILD}
	@${EXEC} ${VERTEX_SOURCE} ${FRAGMENT_SOURCE} ${OBJECT_SCULP} ${TEXTURES}

.PHONY: all clean fclean re 42 teapot spider skull axe alien building sw hb camel castle trex house parrot tricc plane monster sculp

COLOR_END = \033[0;39m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
RED = \033[1;91m
GREEN = \033[1;92m
CYAN2 = \x1B[1;36m
CYAN = \033[1;96m