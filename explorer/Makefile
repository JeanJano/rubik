### COMPILATION ###
NAME		=	explorer_rubik	
CC			=	g++
FLAGS		=	-Wall -Wextra -Werror -std=c++17
INCLUDES	=	-I $(HEADER)

###  PATHS ###
SRC_PATH	=	sources/
HEADER		=	includes/
OBJ_PATH	=	objs/
MOVE_TABLE_PATH = move_tables/
PRUNING_PATH = pruning_tables/

### FILES ###

SOURCES		=	main.cpp \
				general/cubeCubie.cpp \
				general/utils.cpp \
				fase_one_coordinates/cornerOrientation.cpp \
				fase_one_coordinates/edgeOrientation.cpp \
				fase_one_coordinates/UDSlice.cpp \
				faseOne/faseOne.cpp \
				faseOne/SolveFaseOne.cpp \
				parser/parser.cpp \
# 				symetry/EdgeOriSym.cpp \


### FILE MANAGEMENT ###
SRCS		=	$(addprefix $(SRC_PATH),$(SOURCES))
OBJS		=	$(addprefix $(OBJ_PATH),$(SOURCES:.cpp=.o))
DEPS		=	$(addprefix $(OBJ_PATH),$(SOURCES:.cpp=.d))	

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m

### RULES ###

all: tmp $(NAME)


tmp:
		@mkdir -p $(OBJ_PATH)
		@mkdir -p $(OBJ_PATH)parser
		@mkdir -p $(OBJ_PATH)fase_one_coordinates
		@mkdir -p $(OBJ_PATH)faseOne
		@mkdir -p $(OBJ_PATH)general

$(NAME): $(OBJS)
		@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
		@echo "$(GREEN) Compilation succesfully.$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@$(CC) $(FLAGS) -MMD -MP $(INCLUDES) -c $< -o $@

clean:
		@$(RM) $(OBJ_PATH)
		@echo "$(GREEN) Non-executable files removed.$(NOC)"
	
fclean: clean
		@$(RM) $(NAME)
		@$(RM) $(MOVE_TABLE_PATH)
		@$(RM) $(PRUNING_PATH)
		@echo "$(GREEN) Executable removed$(NOC)"

re: fclean all

RM			=	rm -rf

-include $(DEPS)

.PHONY: all clean fclean re 