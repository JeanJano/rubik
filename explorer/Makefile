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

### FILES ###
SOURCES		=	main.cpp \
				parser.cpp \
				cubeCubie.cpp \
				cornerOrientation.cpp \
				edgeOrientation.cpp \
				utils.cpp \

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

$(NAME): $(OBJS)
		@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
		@echo "$(GREEN) Compilation succesfully.$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
		@$(RM) $(OBJ_PATH)
		@echo "$(GREEN) Non-executable files removed.$(NOC)"
	
fclean: clean
		@$(RM) $(NAME)
		@$(RM) $(MOVE_TABLE_PATH)
		@echo "$(GREEN) Executable removed$(NOC)"

re: fclean all

RM			=	rm -rf

-include $(DEPS)

.PHONY: all clean fclean re 