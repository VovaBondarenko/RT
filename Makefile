 NAME = RT

SRC_PATH = ./src/

EXTRA_FUNCTION_SRC_PATH = ./src/extra_function/

PARSER_FUCTION_SRC_PATH = ./src/parser/

EFFECTS_SRC_PATH = ./src/effects/

INTERSECTION_SRC_PATH = ./src/intersection/

NORMAL_SRC_PATH = ./src/normal/
 
INCLUDE_PATH = ./include/  $(LIB_PATH)libft/ $(LIB_PATH)mlx/

LIB_PATH = ./lib/

OBJ_PATH = ./obj/

CC = gcc

FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -framework OpenGL -framework AppKit

# SDL = 

LIB_NAME = libft mlx 

SRC_EXTRA_FUNCTION_FILE_NAME =	color_to_vec3.c create_vec3.c create_vec3i.c vec3_is_zero.c \
								vec3_add.c vec3_convert.c vec3_cross.c vec3_dot.c vec3_fmult.c \
								vec3_mult.c vec3_norm.c vec3_normalize.c vec3_reflect.c vec3_rot.c \
								vec3_rotate.c vec3_scale.c vec3_sub.c vec3_to_color.c \
								atof.c atoi_base.c clampf.c hex_vec3.c vec3_hex.c powerf.c str_del.c \
								vec3_min_max.c

SRC_FILE_NAME = init.c main.c cam.c init_intersection.c init_normal.c \
				init_type_obj_str.c raytracing.c draw.c hook.c image.c map.c\
				math_op.c math_op2.c math_op3.c root.c root_adds.c
				
SRC_PARSER_FILE_NAME = add_new_elem5.c add_new_elem4.c add_new_elem3.c add_new_elem2.c \
            some_defoult_elem.c useful_func.c useful_func2.c add_noise.c fill_func3.c\
            useful_func3.c get_func.c fill_func2.c fill_func.c generate_func.c awesome_parser.c

SRC_EFFECTS_FILE_NAME = color.c recursive.c shadow.c antialiasing.c filter.c fresnel_coef.c

SRC_INTERSECTION_FILE_NAME = inter.c inter2.c inter3.c inter4.c inter5.c

SRC_NORMAL_FILE_NAME = normal.c normal2.c normal3.c

SRC_NAME_OBJ = $(SRC_FILE_NAME:.c=.o)
SRC_EXTRA_FUNCTION_FILE_NAME_OBJ = $(SRC_EXTRA_FUNCTION_FILE_NAME:.c=.o)
SRC_PARSER_FILE_NAME_OBJ = $(SRC_PARSER_FILE_NAME:.c=.o)
SRC_EFFECTS_FILE_NAME_OBJ = $(SRC_EFFECTS_FILE_NAME:.c=.o)
SRC_NORMAL_FILE_NAME_OBJ = $(SRC_NORMAL_FILE_NAME:.c=.o)
SRC_INTERSECTION_FILE_NAME_OBJ = $(SRC_INTERSECTION_FILE_NAME:.c=.o)

SRC 	= $(addprefix $(SRC_PATH), $(SRC_FILE_NAME))
INCLUDE = $(addprefix -I, $(INCLUDE_PATH))
OBJ 	= $(addprefix $(OBJ_PATH),$(SRC_INTERSECTION_FILE_NAME_OBJ) $(SRC_NAME_OBJ) $(SRC_EXTRA_FUNCTION_FILE_NAME_OBJ) $(SRC_PARSER_FILE_NAME_OBJ) $(SRC_EFFECTS_FILE_NAME_OBJ) $(SRC_NORMAL_FILE_NAME_OBJ) )
LIB 	= $(addprefix -L$(LIB_PATH),$(LIB_NAME))

.PHONY: re all clean fclean

all: $(NAME) 

$(NAME): $(OBJ)
	make -C $(LIB_PATH)libft -j
	make -C $(LIB_PATH)mlx -j
	$(CC) $(LIB) -lft -lmlx $(INCLUDE) $(OBJ) $(MLX_FLAGS) -o $(NAME) $(FLAGS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(INCLUDE) -o $@ -c $<

$(OBJ_PATH)%.o: $(EXTRA_FUNCTION_SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(INCLUDE) -o $@ -c $<

$(OBJ_PATH)%.o: $(PARSER_FUCTION_SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(INCLUDE) -o $@ -c $<

$(OBJ_PATH)%.o: $(EFFECTS_SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(INCLUDE) -o $@ -c $<

$(OBJ_PATH)%.o: $(INTERSECTION_SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(INCLUDE) -o $@ -c $<

$(OBJ_PATH)%.o: $(NORMAL_SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(INCLUDE) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIB_PATH)libft fclean
	make -C $(LIB_PATH)mlx clean
	rm -fv $(NAME)

re: fclean all


