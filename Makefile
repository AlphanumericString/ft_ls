# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/11 11:47:20 by bgoulard          #+#    #+#              #
#    Updated: 2026/03/11 11:47:20 by bgoulard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := $(NAME)
# -- commands
ECHO	=	$(shell which echo)
RM		=	$(shell which rm)
MKDIR	=	$(shell which mkdir)
CP		=	$(shell which cp)
PRINT	=	$(shell which printf)
AR		=	$(shell which ar)
CC		=	$(shell which clang)
MAKE_SL =	$(shell which make) --no-print-directory

AUTHOR	=	B.Goulard
VERSION	=	$(shell git describe --tags --dirty 2> /dev/null || echo "0.0.1")

# -- Defaults vars
#  -- Colors
GRAY        = \e[90m
GREEN       = \e[42m
RED         = \e[41m
RESET       = \e[0m
BOLD        = \e[1m
YELLOW      = \e[33m

OK		=	$(GREEN)
KO		=	$(RED)
LOG_MIN	=	$(GRAY)
LOG_MAJ	=	$(YELLOW)


#  -- Dirs
INCLUDES_DIRS	=	./include ./c42libs/include
SRC_DIR			=	src
TST_DIR			=	tests_src
BUILD_DIR		=	build

# -- Files
MAKE_SELF		=	$(abs_path $(lastword $(MAKEFILE_LIST)))
LOGFILE			=	makeinfo.log

# -- Flags
PASSED_VALUES	=	AUTHOR VERSION
CPPFLGS			:=\
				-MMD -MP $(foreach v,$(PASSED_VALUES), -D$v=$($v)) \
				$(foreach d,$(INCLUDES_DIRS),-I$d)
WFLAGS			=\
				-Wall -Wextra -Werror -Wno-unused-parameter \
				-Wmissing-prototypes
C_STD			=	c99
CXX_STD			=	c++98

INCLUDES		=	$(addprefix -I, $(INCLUDES_DIRS))
GLB_FLAGS		=	$(WFLAGS) -pedantic $(INCLUDES) $(CPPFLGS)

CFLAGS			:=	 $(GLB_FLAGS)
CXXFLAGS		:=	-xc++ -std=$(CXX_STD) $(GLB_FLAGS)

DEBUG_LEVEL		?=	0
DBG_FLAGS		:=	-g2 -ggdb -fno-inline -fno-inline-functions -DDEBUG

LD_FLAGS		:=	-L./c42libs -lc42lib


ifeq ($(DEBUG_LEVEL),0)
	CXXFLAGS	:=	$(CXXFLAGS)
	CFLAGS		:=	$(CFLAGS)
else
	CXXFLAGS	:=	$(CXXFLAGS)	$(DBG_FLAGS) -DDEBUG_LEVEL=$(DEBUG_LEVEL)
	CFLAGS		:=	$(CFLAGS)	$(DBG_FLAGS) -DDEBUG_LEVEL=$(DEBUG_LEVEL)
endif

NAME			=	ft_ls
# $(error "You must define the 'NAME' variable with your target name")
# -- sources
SRCS			=\
				$(SRC_DIR)/comparators.c	\
				$(SRC_DIR)/dir_core.c		\
				$(SRC_DIR)/dir_dumps.c		\
				$(SRC_DIR)/epoch_to_date.c	\
				$(SRC_DIR)/file_core.c		\
				$(SRC_DIR)/file_dumps.c		\
				$(SRC_DIR)/link_dump.c		\
				$(SRC_DIR)/main.c			\
				$(SRC_DIR)/parse_opt.c		\
				$(SRC_DIR)/path_utils.c		\
				$(SRC_DIR)/print_help.c		\
				$(SRC_DIR)/stat_dump.c		\
				$(SRC_DIR)/util.c			\
				$(SRC_DIR)/util_dump.c		\

OBJS			=	$(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(SRCS)))
REQS			=	$(patsubst %.o, %.d, $(OBJS))
TSRCS			=	$(shell find $(TST_DIR) -name "*.c" -or -name "*.cpp" -type f 2>/dev/null)
TOBJS			=	$(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(TSRCS)))
TREQS			=	$(patsubst %.o, %.d, $(TOBJS))


all:$(NAME)

$(BUILD_DIR)/:
	@$(PRINT) "$(LOG_MAJ)making dir $(dir $@)$(RESET)" &&	\
	mkdir -p $(dir $@)	&&						\
	$(PRINT) "$(OK)Success$(RESET)\n"			|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"

# -- Rules
define create_dir
	if [ ! -d $1	] ; then \
		$(PRINT) "$(LOG_MAJ)making dir $1$(RESET)\n" && \
		$(MKDIR) -p $1 ; fi
endef

#  normal obj
$(BUILD_DIR)/%.o:%.c | $(BUILD_DIR)/
	@$(call create_dir,$(dir $@))							&& \
	$(PRINT) "$(LOG_MIN)Compiling $(notdir $<)...$(RESET)"	&& \
	$(CC) $(CFLAGS) -c $< -o $@ 2>> $(LOGFILE)				&& \
	$(PRINT) "$(OK)Success$(RESET)\n"						|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
$(BUILD_DIR)/%.o:%.cpp | $(BUILD_DIR)/
	@$(call create_dir,$(dir $@))							&& \
	$(PRINT) "$(LOG_MIN)Compiling $(notdir $<)...$(RESET)"	&& \
	$(CC) $(CXXFLAGS) -c $< -o $@ 2>> $(LOGFILE)			&& \
	$(PRINT) "$(OK)Success$(RESET)\n"						|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
#	tests objs
$(BUILD_DIR)/%.o:$(TST_DIR)/%.c | $(BUILD_DIR)/
	@$(call create_dir,$(dir $@))							&& \
	$(PRINT) "$(LOG_MIN)Compiling $(notdir $<)...$(RESET)"	&& \
	$(CC) $(CFLAGS) -c $< -o $@ 2>> $(LOGFILE)				&& \
	$(PRINT) "$(OK)Success$(RESET)\n"						|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
$(BUILD_DIR)/%.o:$(TST_DIR)/%.cpp | $(BUILD_DIR)/
	@$(call create_dir,$(dir $@))							&& \
	$(PRINT) "$(LOG_MIN)Compiling $(notdir $<)...$(RESET)"	&& \
	$(CC) $(CXXFLAGS) -c $< -o $@ 2>> $(LOGFILE)			&& \
	$(PRINT) "$(OK)Success$(RESET)\n"						|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
# -- Targets
./c42libs/libc42lib.a:
	@$(MAKE) -C $(dir $@)
$(NAME): $(OBJS) ./c42libs/libc42lib.a
	@$(PRINT) "$(LOG_MAJ)Linking $(NAME)...$(RESET)"	&& \
	$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)		&& \
	$(PRINT) "$(OK)Success$(RESET)\n"					|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
$(NAME)_tests: $(TOBJS)
	@$(PRINT) "$(LOG_MAJ)Linking $(NAME)'s tests...$(RESET)"	&& \
	$(CC) $(TOBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)				&& \
	$(PRINT) "$(OK)Success$(RESET)\n"							|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
clean:
	@$(PRINT) "$(LOG_MAJ)Cleaning build files...$(RESET)"	&& \
	$(RM) -rf $(BUILD_DIR) $(LOGFILE)						&& \
	$(PRINT) "$(OK)Success$(RESET)\n"						|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
fclean: clean
	@$(PRINT) "$(LOG_MAJ)Cleaning compiled files...$(RESET)"		&& \
	$(RM) -f $(NAME) 										&& \
	$(MAKE_SL) -C c42libs fclean								&& \
	$(PRINT) "$(OK)Success$(RESET)\n"						|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
uclean: fclean
	@$(PRINT) "$(LOG_MAJ)Cleaning all dev files...$(RESET)"		&& \
	$(RM) -f .clangd $(LOGFILE) ./tags ./compile_commands.json	\
	.clang-format callgrind.* vgcore.*							&& \
	$(PRINT) "$(OK)Success$(RESET)\n"							|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
re: fclean all
re_env: uclean dev_env
tags: $(SRCS)
	@$(PRINT) "$(LOG_MAJ)Creating tags file...$(RESET)"					&& \
	ctags -R --languages=$(TARGET_LANG) --exclude=.git --exclude=build	&& \
	$(PRINT) "$(OK)Success$(RESET)\n"									|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
.clangd: $(MAKE_SELF)
	@$(PRINT) "$(LOG_MAJ)Creating .clangd file...$(RESET)"		&& \
		\
	$(ECHO) -en "Completion:\n"	> .clangd &&\
	$(ECHO) -en "  IncludeInsertion: always\n" >> .clangd	&&\
	$(ECHO) -en "CompileFlags:\n"	>> .clangd &&\
	$(ECHO) -en "    Compiler: clang\n"	>> .clangd &&\
	$(ECHO) -en "    Add: [\n"	>> .clangd &&\
	$(ECHO) -en "     \"$(WFLAGS)\",\n"	>> .clangd && \
	for d in $(PASSED_VALUES) ; do \
		$(ECHO) -en "     \"$$d\",\n" >> .clangd ;	\
	done && \
	for i in $(INCLUDES) ; do	\
		$(ECHO) -en "     \"$$i\",\n" >> .clangd ;	\
	done && \
	$(PRINT) "$(OK)Success$(RESET)\n"							|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"

compile_commands.json: $(MAKE_SELF)
	@$(PRINT) "$(LOG_MAJ)Creating compile_commands.json file...$(RESET)"	&& \
	$(MAKE_SL) fclean														&& \
	bear -- $(MAKE_SL) -j													&& \
	$(PRINT) "$(OK)Success$(RESET)\n"										|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"
dev_env: .clangd compile_commands.json tags $(MAKE_SELF)
	$(PRINT) "$(OK)Success$(RESET)\n"									|| \
	$(PRINT) "$(KO)Fail$(RESET)\n"

-include $(REQS)
-include $(TREQS)

.PHONY: all clean fclean re dbg_make .clangd
