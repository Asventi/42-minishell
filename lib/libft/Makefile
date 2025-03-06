# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 11:53:22 by pjarnac           #+#    #+#              #
#    Updated: 2024/12/10 14:39:05 by pjarnac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# ================FILES================ #

MAKE_DIR		:=	.make/
BUILD_DIR		:=	$(MAKE_DIR)build_$(shell git branch --show-current)/
BASE_BUILD_DIR	:= normal/

SRC_DIR			=	src/

OBJS			=	$(patsubst %.c, $(BUILD_DIR)%.o, $(SRC))

DEPS			=	$(patsubst %.c, $(BUILD_DIR)%.d, $(SRC))

# ================ROOT================= #

SRC 		=

# ===============CHAINED=============== #

SRC += $(addprefix $(CHAINED_DIR), $(CHAINED_SRC))

CHAINED_DIR =	chained/
CHAINED_SRC =	ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \

# ==================IS================= #

SRC += $(addprefix $(IS_DIR), $(IS_SRC))

IS_DIR =		is/
IS_SRC =		ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \

# ================MEMORY=============== #

SRC += $(addprefix $(MEMORY_DIR), $(MEMORY_SRC))

MEMORY_DIR =	memory/
MEMORY_SRC =	ft_bzero.c \
				ft_calloc.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \

# =================PUT================= #

SRC += $(addprefix $(PUT_DIR), $(PUT_SRC))

PUT_DIR =		put/
PUT_SRC =		ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \

# =================STR================= #

SRC += $(addprefix $(STR_DIR), $(STR_SRC))

STR_DIR =		str/
STR_SRC =		ft_atoi.c \
				ft_itoa.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \

# ==================TO================= #

SRC += $(addprefix $(TO_DIR), $(TO_SRC))

TO_DIR =		to/
TO_SRC =		ft_tolower.c \
				ft_toupper.c \

# =================GNL================= #

SRC += $(addprefix $(GNL_DIR), $(GNL_SRC))

GNL_DIR =		gnl/
GNL_SRC =		get_next_line_utils.c \
				get_next_line.c \

# ================PRINTF=============== #

SRC += $(addprefix $(PRINTF_DIR), $(PRINTF_SRC))

PRINTF_DIR =	printf/
PRINTF_SRC =	ft_printf.c \

# ============PRINTF/FORMATS=========== #

SRC += $(addprefix $(FORMATS_DIR), $(FORMATS_SRC))

FORMATS_DIR =	$(PRINTF_DIR)formats/
FORMATS_SRC =	formats.c \
				hex_formats.c \
				num_formats.c \
				str_formats.c \

# ==========LIBS / INCLUDES============ #

LIBS_DIR	=
LIBS_PATH	=
LIBS_PATH	:=	$(addprefix $(LIBS_DIR), $(LIBS_PATH))
LIBS		=	$(patsubst lib%.a, %, $(notdir $(LIBS_PATH)))

INCS_DIR	=	includes/
INCLUDES	=	$(INCS_DIR) \
				$(dir $(LIBS_PATH))$(INCS_DIR)

# ===============CONFIGS=============== #

CC			=	cc
CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+=	$(addprefix -I, $(INCLUDES)) \
				-MMD -MP

LDFLAGS		+=	$(addprefix -L, $(dir $(LIBS_PATH)))
LDLIBS		+=	$(addprefix -l, $(LIBS))

AR			=	ar
ARFLAGS		=	-rcs

MAKEFLAGS	+=	--no-print-directory

# ================MODES================ #

MODES		:= debug fsanitize optimize full-optimize

MODE_TRACE	:= $(BUILD_DIR).mode_trace
LAST_MODE	:= $(shell cat $(MODE_TRACE) 2>/dev/null)

MODE ?=

ifneq ($(MODE), )
	BUILD_DIR := $(BUILD_DIR)$(MODE)/
else
	BUILD_DIR := $(BUILD_DIR)$(BASE_BUILD_DIR)
endif

ifeq ($(MODE), debug)
	CFLAGS = -g3
else ifeq ($(MODE), fsanitize)
	CFLAGS = -g3 -fsanitize=address
else ifeq ($(MODE), optimize)
	CFLAGS += -O2
else ifeq ($(MODE), full-optimize)
	CFLAGS += -O3
else ifneq ($(MODE),)
	ERROR = MODE
endif

ifneq ($(LAST_MODE), $(MODE))
$(NAME): force
endif

# ================TARGETS============== #

.PHONY: all
all: $(NAME)

show:
	@echo $(SRC_TEST)

$(NAME): $(OBJS)
	@echo $(MODE) > $(MODE_TRACE)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIBS_PATH): force
	$(MAKE) -C $(@D)

.PHONY: $(MODES)
$(MODES):
	$(MAKE) MODE=$@

.PHONY: clean
clean:
	-for lib in $(dir $(LIBS_PATH)); do $(MAKE) -s -C $$lib $@; done
	rm -rf $(MAKE_DIR)

.PHONY: fclean
fclean:
	-for lib in $(dir $(LIBS_PATH)); do $(MAKE) -s -C $$lib $@; done
	rm -rf $(MAKE_DIR) $(NAME)

.PHONY: re
re: fclean
	$(MAKE)

# ================MISC================= #

.PHONY: print-%
print-%:
	@echo $(patsubst print-%,%,$@)=
	@echo $($(patsubst print-%,%,$@))

.PHONY: force
force:

-include $(DEPS)

.DEFAULT_GOAL := all
