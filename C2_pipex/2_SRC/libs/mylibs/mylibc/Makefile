# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 11:09:01 by dinepomu          #+#    #+#              #
#    Updated: 2025/03/26 17:22:25 by dinepomu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# https://linktr.ee/diegonmarcos											   #
# **************************************************************************** #

###  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  ###
# ############################################################################ #
#                                 MAKEFILE                                     #
# ############################################################################ #
#
# 1. DESCRIPTION:
# -	This is make file for build either PROGRAM, LIBRARY, PROGRAM+LIBRARY 
#		with their dependecies connected.
#
#
# 2. USAGE:
#	2.1 OPTIONS:
#	 - To build the program, run the command "make"
#	 - To generate the log files, run the command "make log_alles"
#	 - To clean the project, run the command "make fclean_all"
#
#	2.2 INPUTS::
#	 - Headers.h, files all them must be placed inside the folder "inc".
#	 - The source files must be inside of the folder "src/"
#	 - Library.a, files all them must be inside of the folder "libs"
#	 - The library makefile must be inside of the folder "libs/[LIB_NAME]"
#	 - The expcted file structure is:
#	  - inc/
#	  - src/
#	  - libs/
#	  - Makefile
#
#	2.3 OPTIONS MORE:
#
#	- LOG ALLES
#	  - STATIC ANALYSIS
#	  - LEAKS
#	  - DYNAMIC ANALYSIS
#	  - DEBUGGERS
#	  - DOC
#	  - TOOLS
#	  - EXTRAS
#
#	- ENV, COMPILING AND LINKING PIPELINE
#	  - DEFINITIONS VARIABLES
#	  - ENVIROMENT SET
#	  - COMPILING PIPELINE
#	  - LINKING PIPELINE
#
#	- HELPERS
#	  - hello, check_up_to_date, code_cleaner, files_lns_creator
#	  -	library_clean, library_fclean, library_re
#
#





















###  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  ###
# ############################################################################ #
#                          VARIABLES INITIALIZATIONS                           #
# ############################################################################ #
# ************************************************************************ #
# MAIN (NAME, IS? AND SOURCE FILES)										   #
# ************************************************************************ #
# *** Name Output *** #
NAME0 					= mylibc
NAME_REPO				= https://github.com/diegonmarcos/mylibs

# *** ../ or ../../ or empty *** # Libraries autocmactly already have the ../
OUTPUT_PLACE 			=

# ***Is? *** #
IS_PROGRAM_AND_NOT_LIB 	= 0# 0 or 1
INCLUDE_LIB 			= 0# 0 or 1
BUILD_LIBRARY 			= 0# 0 or 1
BONUS 					= 0# 0 or 1
VERBOSE 				= 0# 0, 1 or 2 - Vebosity of the makefile
DOCKER					= 0# 0 or 1
DBG 					= 0# 0 or 1 - Debug mode for the program

# ************************************************************************ #
# *** Files source *.c *** #
SOURCE_MAIN 	=								\		

SOURCE_FILES = 									\
				0_ft_malloc.c					\
				0_memory_arena_pool.c			\
				0a_ft_exec.c					\
				0a_ft_pipe.c					\
				1a_ft_calloc.c					\
				1a_ft_calloc_fd.c				\
				1a_ft_free.c					\
				1a_ft_garbage_collector_1.c		\
				1a_ft_garbage_collector_2.c		\
				1a_ft_garbage_collector_bff.c	\
				1a_halt_exit.c					\
				1b_ft_close.c					\
				1b_ft_fgets_gnl.c				\
				1b_ft_open.c					\
				1b_ft_sed.c						\
				1b_ft_sscanf.c					\
				1b_gnl_join_split.c				\
				1c_0_ft_memcpy.c				\
				1c_0_ft_memset.c				\
				1c_0_ft_strlcat.c				\
				1c_1_ft_memchr.c				\
				1c_1_ft_memchr1.c				\
				1c_1_ft_memcmp.c				\
				1c_ft_atoi.c					\
				1c_ft_atoi_base.c				\
				1c_ft_is_sorted.c				\
				1c_ft_isalnumascii.c			\
				1c_ft_isdigit.c					\
				1c_ft_itoa.c					\
				1c_ft_math.c					\
				1c_ft_snprintf.c				\
				1c_ft_striteri.c				\
				1c_ft_strlen.c					\
				1c_ft_strmapi.c					\
				1d_0_ft_strcat_.c				\
				1d_0_ft_strdup.c				\
				1d_ft_asprintf.c				\
				1d_ft_strtok_split.c			\
				1d_ft_strtok_split1.c			\
				1e_ft_fprintf.c					\
				1e_ft_fprintf1.c				\
				1e_ft_hexa_mayusc.c				\
				1e_ft_hexa_minusc.c				\
				1e_ft_num_unsign.c				\
				1e_ft_pointer_hexa.c			\
				1e_ft_pointer_hexa_fd_fpr.c		\
				1e_ft_printf.c					\
				1e_ft_putchar.c					\
				1e_ft_putnbr.c					\
				1e_ft_putstr1.c					\
				2_0_ft_slinked_list.c			\
				2_0_ft_slinked_list1.c			\
				2_0_ft_slinked_list3.c			\
				2_1_ft_array_to_d_linked_list.c	\
				2_1_ft_free_list_doubly.c		\
				2_1_ft_swap_pointers.c			\
				2_1_linked_list_doubly1.c		\
				2_1_linked_list_doubly2.c		\
				2_ft_list_foreach.c				\
				2_ft_list_remove_if.c			\
				2_hashtable_headarray.c			\
				2_hashtable_headnode.c			\
				2_heapfy_array_bst.c			\
				2_merge_sort_lsd.c				\
				2_merge_sort_lss.c				\
				2_sort_list.c					\
				3_0_bubble_sort.c				\
				3_0_insertion_sort.c			\
				3_0_selection_sort.c			\
				3_1_fizzbuzz.c					\
				3_1_merge_sort.c				\
				3_1_quick_sort.c				\
				3_2_radix_sort.c				\
				3_2_union.c						\
				3_2_wdmatch.c					\
				3_3_expand_str.c				\
				3_3_ft_toupper.c				\
				3_3_intro_sort0.c				\
				3_3_intro_sort1.c				\
				3_4_rev_wstr.c					\
				3_4_rostring.c					\
				3_bitwise.c						\
				3_ft_fibonacci.c				\
				3_ft_prime.c					\
				3_math.c						\
				3_probability.c					\
				3_raster_scan_bresenham.c		\
				3_raster_scan_flood_fill.c		\
				3_raytracing_montecarlo.c		\
				3_statistics.c					\
				3_statistics1.c					\
				3_statistics2.c					\
				4_ft_data_parser.c				\
				4_ft_memory_design.c			\
				4_ft_spliter.c					\
				4_ft_sscanf.c

VPATH 			= src/src_all:			\

# *** HEADERS *.h *** #
HEADER_DIR 		= inc

# ************************************************************************ #
# *** Extra Rules (Bonus) ***	 #
CHECKER_BONUS_DIR = src/checker_bonus

# ************************************************************************ #
# DEPENDENCIES (NAMES AND SOURCES)										   #
# ************************************************************************ #
# *** Shared Libraries *** #
LIBS_SO 		=


# *** Library *.a (libraries to be included) THE ORDER MATTERS!!! *** #
LIBS_DIR 	= libs

LIB_1_NAME		= 0
LIB_1_PATH		= 
LIB_1_FILE		= 
LIB_1_REPO		= 
LIB_1_CONFIG	=

LIB_2_NAME		= 0
LIB_2_PATH		= 
LIB_2_FILE		=
LIB_2_REPO		=
LIB_2_CONFIG	=

LIB_3_NAME		= 0
LIB_3_PATH		= 
LIB_3_FILE		=
LIB_3_REPO		=
LIB_3_CONFIG	= 


# ************************************************************************ #
# COMPILER AND LINKER VARS												   #
# ************************************************************************ #
# *** Compiler, Make and Library compilers Declar *** #
MAKE 				= make -j -O
COMPILER 			= clang
PIC 				= -fPIC
LIB_LINK_STATIC 	= ar rcs
#LIB_LINK_DYNAMIC 	= shared
RM 					= rm -rf
GCL 				= git clone --depth=1
WGET 				= wget























# ############################################################################ #
#                                 VARIABLES HELPERS                            #
# ############################################################################ #
# ************************************************************************ #
#                         NAME AND SOURCES  	                           #
# ************************************************************************ #
# *** Name definition *** #
NAME1 			= $(OUTPUT_PLACE)$(NAME0)

ifeq ($(IS_PROGRAM_AND_NOT_LIB), 1)
	NAME 		= $(NAME1)
else
	NAME		= lib$(NAME1).a
endif

# *** Source Files .c Definition path *** #
SOURCE_SRC_ALL 	= $(addprefix src/src_all/,$(SOURCE_MAIN)) $(addprefix src/src_all/,$(SOURCE_FILES))
SOURCES			= $(SOURCE_MAIN) $(SOURCE_FILES)

# ************************************************************************ #
#                         OBJECTS AND DEPENDENCIES                         #
# ************************************************************************ #
#Object Files and Dependency Files Definition path Main *** #
OBJECTS_MAIN 	=  $(patsubst %.c,objs/%.o,$(notdir $(SOURCE_MAIN)))
DEPS_MAIN 		= $(OBJECTS_MAIN:.o=.d)
DEPFLAGS 		= -MMD -MP#															# This will create the files(headers) as dependendcy and track them
-include $(DEPS_MAIN)

#Object Files and Dependency Files Definition path Lib *** #
OBJECTS_LIB 	=  $(patsubst %.c,objs/%.o,$(notdir $(SOURCE_FILES)))
DEPS_LIB 		= $(OBJECTS_LIB:.o=.d)
#DEPFLAGS 		= -MMD -MP#															# This will create the files(headers) as dependendcy and track them
-include $(DEPS_LIB)

OBJECTS = $(OBJECTS_MAIN) $(OBJECTS_LIB) 

# ************************************************************************ #
#                         HEADERS AND LIBS		                           #
# ************************************************************************ #
# *** Include or not a library (REMEBER TO MANAGE DEPENDECIES OF THE LIBRARIES, the root library comes after the child)
LDFLAGS			:=
CFLAGS_INCL 	= -I$(HEADER_DIR)
LIBS_PATH 		:=
ifneq ($(LIB_1_NAME), 0)
	LIBS_PATH 	+= $(LIB_1_FILE)
	LDFLAGS 	+= -L$(LIB_1_PATH) -l$(LIB_1_NAME)
	CFLAGS_INCL += -I$(LIB_1_PATH)/inc

endif
ifneq ($(LIB_2_NAME), 0)
	LIBS_PATH 	+= $(LIB_2_FILE)
	LDFLAGS 	+= -L$(LIB_2_PATH) -l$(LIB_2_NAME)
	CFLAGS_INCL += -I$(LIB_2_PATH)/inc
endif
ifneq ($(LIB_3_NAME), 0)
	LIBS_PATH 	+= $(LIB_3_FILE)
	LDFLAGS 	+= -L$(LIB_3_PATH) -l$(LIB_3_NAME)
	CFLAGS_INCL += -I$(LIB_3_PATH)/inc
endif
ifneq ($(LIB_4_NAME), 0)
	LIBS_PATH 	+= $(LIB_4_FILE)
	LDFLAGS 	+= -L$(LIB_4_PATH) -l$(LIB_4_NAME)
	CFLAGS_INCL += -I$(LIB_4_PATH)/inc
endif

LIB_PROGRAM 	= -Llibs -l$(NAME0)
LIB_OUTPUT_0=libs/lib$(NAME0)_0.a
LIB_OUTPUT_MERGED=libs/lib$(NAME0).a

# ************************************************************************ #
#                         VERBOSE AND DEBUG		                           #
# ************************************************************************ #
# *** VERBOSE MAKE? *** #
MAKEFLAGS		:= --no-print-directory --silent
ifeq ($(VERBOSE), 2)
MAKEFLAGS		:=
#MAKE 			+= --trace all --warn-undefined-variables
#MAKE			+= --debug=b -j1 --warn-undefined-variables
#MAKE			+= --debug=v -j1 --warn-undefined-variables
#MAKE			+= --debug=t -j1 --warn-undefined-variables
else
MAKEFLAGS 		+=
endif

# *** PROGRAM DBG MODE *** #
ifeq ($(DBG),1)
	DBG			= 1
	CFLAGS_DBG	+= -g3
	MACROS 		+= -DDBG=$(DBG)
endif

# *** PROGRAM OPTIONS *** #
ALGO = 0
ifneq ($(ALGO),0)
	M2			= ALGO
	MACROS 		+= -D$(M2)=\"$(ALGO)\"
endif



# ************************************************************************ #
#                         BONUS HELPERSº		                           #
# ************************************************************************ #
# *** Bonus Source Files .c Definition path *** #
CHECKER_BUILD 	= $(MAKE) -C $(CHECKER_BONUS_DIR) MAKEFLAGS=""

















###  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  ###
# ############################################################################ #
#            VAR, ENV, COMPILING AND LINKING PIPELINE                          #
# ############################################################################ #
#	
#	#### *** ENV, COMPILING AND LINKING PIPELINE *** #####
#	### * DEFINITIONS VARIABLES *
#	### * ENVIROMENT SET *
#	### * COMPILING PIPELINE *
#	### * LINKING PIPELINE * 
#	
#	
#	### * DEFINITIONS VARIABLES *
#	## MAKE_VERBOSE	= 0
#	## PRGM_DBG 		= 0
#	## PRGM_ALGO 		= 0
#	
#	
#	#### * ENVIROMENT SET *
#	### folders_build
#	### * Build Docker *
#	## Build the Dockerfile
#	## Run the Dockerfile
#	
#	### * GCL Repos *
#	## gcl program repo
#	## gcl libs depencies repo
#	
#	
#	#### * COMPILING PIPELINE *
#	### * External Dependencies *
#	## Build(run make -C) Deps Libs, 
#	##		if uptdated(): extrct its news objs
#	
#	### * Objs Program *
#	## Compile the program objs: $(OBJS)
#	
#	
#	#### * LINKING PIPELINE *
#	### * Library Linking *
#	## Link a program Lib0
#	## Link a program and external libs Lib1
#	## Link a program, external and shared libs Lib2
#	## Create the Lib_program
#	
#	### * Executable linking *
#	## Link the lib_program with main.file
#	
#	



# ************************************************************************ #
#                      BUILD SYSTEM PIPELINE                               #
# ************************************************************************ #

# ************************************************************************ #
.DEFAULT_GOAL:= build_system_pipeline

build_system_pipeline:
	$(MAKE) hello
	$(MAKE) build_enviroment_folders
	$(MAKE) build_dependencies_docker
	$(MAKE) build_enviroment_docker
	$(MAKE) build_deps
	$(MAKE) check_up_to_date
	$(MAKE) $(NAME)
	$(MAKE) dbg_rules
	$(MAKE) check_up_to_date_2
	$(MAKE) folders_ls_la
	if [ "$(IS_PROGRAM_AND_NOT_LIB)" -eq "1" ]; then \
		$(MAKE) run_program; \
	fi

# ************************************************************************ #
build_enviroment_folders:
	$(MAKE) folders_build
build_dependencies_docker:
#	$(MAKE) docker_install
build_enviroment_docker:
ifeq ($(DOCKER),1)
	$(MAKE) build_docker || true
endif
#	$(MAKE) run_docker

build_deps:
ifneq ($(LIB_1_NAME),0)
	cd libs && $(GCL) $(LIB_1_REPO) > /dev/null 2>&1 || true && cd .. && $(MAKE) mylibs_clean
	mv libs/mylibs/.git1 libs/mylibs/.git && git -C $(LIB_1_PATH) pull > /dev/null 2>&1 && mv libs/mylibs/.git libs/mylibs/.git1 || true
	$(LIB_1_CONFIG)
	$(MAKE) -C $(LIB_1_PATH) VERBOSE=$(VERBOSE) || true
endif
ifneq ($(LIB_2_NAME),0)
	cd libs && $(GCL) $(LIB_2_REPO) > /dev/null 2>&1 || true
	git -C $(LIB_2_PATH) pull > /dev/null 2>&1 || true
	$(LIB_2_CONFIG)
	$(MAKE) -C $(LIB_2_PATH) VERBOSE=$(VERBOSE) || true
endif
ifneq ($(LIB_3_NAME), 0)
	cd libs && $(GCL) $(LIB_3_REPO) > /dev/null 2>&1 || true
	git -C $(LIB_3_PATH) pull > /dev/null 2>&1 || true
	$(LIB_3_CONFIG)
	$(MAKE) -C $(LIB_3_PATH) MAKEFLAGS="" || true
endif

# ************************************************************************ #
# ************************************************************************ #
# ************************************************************************ #
NAME_PRGM = $(OUTPUT_PLACE)$(NAME0)
$(NAME_PRGM): $(LIB_OUTPUT_MERGED) $(OBJECTS_MAIN) 
	$(COMPILER) $(OBJECTS) $(LIBS_PATH) $(CFLAGS_DBG) $(CFLAGS_INCL) $(LDFLAGS) -o $(NAME)
	echo "  $(GREEN)(•̀ᴗ•́)و $(NAME) Bin Generated!$(RESET)"


NAME_LIB = lib$(NAME0).a
$(NAME_LIB): $(OBJECTS_LIB) $(LIBS_PATH) $(LIB_OUTPUT_0) $(LIB_OUTPUT_MERGED)
	cp $(LIB_OUTPUT_MERGED) $(NAME)
	echo "  $(GREEN)(•̀ᴗ•́)و $(NAME) Lib Generated!$(RESET)"



$(LIB_OUTPUT_MERGED): $(LIBS_PATH) $(LIB_OUTPUT_0) 
	echo "GROUP ( $(LIB_OUTPUT_0) $(LIBS_SO) $(LIBS_PATH) )" > $(LIB_OUTPUT_MERGED)
ifneq ($(VERBOSE), 0)
	echo "  $(GRAY)(•̀ᴗ•́)و lib$(NAME).a Library Merged Referenced done!$(RESET)"
endif



$(LIB_1_FILE):
	cd libs && $(GCL) $(LIB_1_REPO) > /dev/null 2>&1 || true && cd .. && $(MAKE) mylibs_clean
	mv libs/mylibs/.git1 libs/mylibs/.git && git -C $(LIB_1_PATH) pull > /dev/null 2>&1 && mv libs/mylibs/.git libs/mylibs/.git1 || true
	$(MAKE) -C $(LIB_1_PATH) VERBOSE=$(VERBOSE)
$(LIB_2_FILE):
	cd libs && $(GCL) $(LIB_2_REPO) > /dev/null 2>&1 || true
	git -C $(LIB_2_PATH) pull > /dev/null 2>&1 || true
	$(MAKE) -C $(LIB_2_PATH) VERBOSE=$(VERBOSE)
$(LIB_3_FILE):
	cd libs && $(GCL) $(LIB_3_REPO) > /dev/null 2>&1 || true
	git -C $(LIB_3_PATH) pull > /dev/null 2>&1 || true
	$(MAKE) -C $(LIB_3_PATH) MAKEFLAGS=""



$(LIB_OUTPUT_0): $(OBJECTS_LIB)
	$(LIB_LINK_STATIC) $(LIB_OUTPUT_0) $(OBJECTS_LIB)
ifneq ($(VERBOSE), 0)
	@echo "  $(GRAY)(•̀ᴗ•́)و lib$(NAME)_0.a Library done!$(RESET)"
endif



objs/%.o:	%.c
	$(COMPILER) $(PIC) $(CFLAGS_DBG) $(CFLAG_ASAN) $(CFLAGS_INCL) $(DEPFLAGS) $(MACROS) -c $< -o $@
ifneq ($(VERBOSE), 0)
	@echo "$(GRAY)()و $@ $(NAME) Compiling Objects done!$(RESET)"
endif



# ************************************************************************ #
dbg_rules:
ifeq ($(DBG),1)
	cp $(NAME0) log/4.Bins_folder/push_swap_g3
endif

#Name
all: $(NAME)


# ************************************************************************ #
# *** Bonus Rule *** #
bonus:		
			$(MAKE) clean
			$(MAKE) BONUS=1
mylibs_clean:
	mv libs/mylibs/.git libs/mylibs/.git1 > /dev/null 2>&1 || true
	$(RM) libs/mylibs/mylibcpp libs/mylibs/mytools libs/mylibs/mylibx libs/mylibs/myunittest
# ************************************************************************ #















# ############################################################################ #
#                                 RULES/RECLEAN                                #
# ############################################################################ #
# *** Clean Objects only *** #
clean:
	$(RM) objs
ifeq ($(BONUS),1)
	$(MAKE) clean -C $(CHECKER_BONUS_DIR) MAKEFLAGS=""
endif
	@echo	"$(RED)	¯\_(ツ)_/¯ OBJECTS REMOVED!$(RESET)"

# *** Clean+Bins+Libs *** #
fclean:	clean
	$(RM) $(NAME)
	$(RM) libs/*.a
ifeq ($(BONUS),1)
	$(MAKE) fclean -C $(CHECKER_BONUS_DIR) MAKEFLAGS=""
endif
	@echo	"$(RED)		(╯°□°）╯︵ ┻━┻ FILE, OBJ REMOVED!$(RESET)"

# *** FClean+Build *** #
re: fclean build_system_pipeline



# *** FClean+logs_folder *** #
fclean_all:	fclean
	$(RM) log
	$(RM) testers
	$(RM) Makedocker.sh
	if [ -f imgui.ini ]; then \
		rm imgui.ini; \
	fi
	@echo	"$(RED)			(╯°□°）╯︵ ┻━┻ FILE, OBJ AND LOG REMOVED!$(RESET)"

# *** Re_all *** #
re_all: fclean_all build_system_pipeline




# ############################################################################ #
#                                FOLDER BUILDER                                #
# ############################################################################ #
# *** Build folders *** #
folders_build:
	$(MAKE) folders_make_build
	$(MAKE) folders_doc
	$(MAKE) folders_log_build

# *** Build folders Make *** #
folders_make_build:
	mkdir -p inc
	mkdir -p libs
	mkdir -p objs

# *** Build folders Doc *** #
folders_doc:
	mkdir -p doc/doxygen
	mkdir -p doc/md

# *** Build folders Log *** #
folders_log_build:
	mkdir -p log/1.Warning_linting
	mkdir -p log/2.Memory_Check/logs
	mkdir -p log/2.Memory_Check/allocs
	mkdir -p log/3.Unit_Testing
	mkdir -p log/3.Unit_Testing/moves
	mkdir -p log/4.Bins_folder
	mkdir -p log/4.Bins_folder/log
	mkdir -p log/4.Bins_folder/log/2.Memory_Check/allocs
	mkdir -p log/5.Libs_nmart
	mkdir -p log/6.Make_dbg
	mkdir -p log/7.Doxygen
	mkdir -p log/8.Docker



# ############################################################################ #
#                                DEFS		                                   #
# ############################################################################ #
# **************************************************************************** #
#                                DEFS/PHONNY                               	   #
# **************************************************************************** #
# *** Phony *** #
.PHONY:		all build program_or_lib libs_build program 		\
			clean fclean fclean_all re 							\
			library_clean library_fclean library_re 			\
			folder_lns_builder folders_build check_up_to_date 	\
			hello debug 										\
			werror norm_1 norm_2 log_all werror_bonus			\
			testing_alles test_export 							\
			make_dbg create_bins								\
			leaks valgrind asan time_and_perfomance				\
			help bonus mylibs_clean								\
			bonus bonus_re										\
			run_visualizer										\

# **************************************************************************** #
#                                DEFS/COLORS                               	   #
# **************************************************************************** #
DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
RESET =			\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m



# **************************************************************************** #
#                         DOCKER AND DEPENDENCIES                          	   #
# **************************************************************************** #

build_docker: log/8.Docker/Makedocker.sh
log/8.Docker/Makedocker.sh:
	mkdir -p log/8.Docker
	wget \
	-O log/8.Docker/Makedocker.sh \
	https://raw.githubusercontent.com/diegonmarcos/system/refs/heads/main/S2_docker/src/Makedocker_.sh
	chmod +x log/8.Docker/Makedocker.sh
	ln -s log/8.Docker/Makedocker.sh Makedocker.sh
	./Makedocker.sh clear
	./Makedocker.sh build

run_docker:
	./log/8.Docker/Makedocker.sh run







































###  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  ###
# ############################################################################ #
#                                LOG ALLES                                     #
# ############################################################################ #
#
#	#### *** LOG ALLES *** ####
#	### * STATIC ANALYSIS *
#	### * LEAKS **
#	### * DYNAMIC ANALYSIS *
#	### * DEBUGGERS *
#	### * DOC *
#	### * TOOLS *
#	### * EXTRAS *
#
#
#	### * STATIC ANALYSIS *
#	## log_static_analysis
#	## bear
#	##-Wall -Wextra
#	##-Wformat -Warray-bounds -Wnull-dereference -Wvla
#	##-Weverything"
#	##clang-tidy
#	##--analyze -Xanalyzer -analyzer-checker=core
#	## norminette
#
#
#	### * LEAKS *
#	## create_bins_leaks
#	## log_leaks
#	## VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
#	##--tool=massif
#	##--tool=cachegrind 
#	##--tool=callgrind
#	## ASAN = -fsanitize=address
#
#
#	### * DYNAMIC ANALYSIS *
#	## test_egde_cases
#	## test_main_cases
#	## test_performance
#
#
#	### * DEBUGGERS *
#	## create_bins_dbg
#	## run_debug-gdb
#	## run_debug-lldb
#	## run_debug-vscode
#	## log_libs_nm_art
#	## log_dbg_info
#
#
#	### * DOC *
#	##doxygen
#
#
#	### * TOOLS *
#	##test_make_performance
#
#
#	### * EXTRAS *
#	##test_run_visualizer
#	##log_alles_bonus
#
#

log_alles:
	$(MAKE)
	$(MAKE) log_static_analysis || true
	$(MAKE) log_leaks || true
	$(MAKE) log_dynamic_analysis_tests || true
	$(MAKE) log_dbg_info || true
	$(MAKE) log_doxygen || true
	$(MAKE) log_make_performance || true
	$(MAKE) test_run_visualizer || true

log_alles_bonus:
	$(MAKE) bonus
	$(MAKE) log_static_analysis_bonus || true
	$(MAKE) log_leaks_bonus || true
	$(MAKE) log_dynamic_analysis_tests_bonus || true


































# ############################################################################ #
#                          STATIC ANALYZERS                                    #
# ############################################################################ #
# *** static analyzer *** #
log_static_analysis:
	$(MAKE) bear
	$(MAKE) bonus
	$(MAKE) werror
	$(MAKE) norm
	$(MAKE) norm_bonus
	$(MAKE) werror_bonus
#	$(MAKE) clang_tidy_fix

# *** Bear *** #
bear:
	bear --output log/6.Make_dbg/compile_commands.json -- make re

# *** Wall Wextra *** #
werror:
	
	@echo "$(GREEN)\n·Clang lintings$(RESET)"
	echo "\n##Clang Wall Wextra - fsyntaxOnly"
	echo "############################################\n"
	$(MAKE) CFLAGS_DBG=" -Wall -Wextra" 2>&1 | sed 's/\x1b\[//g'| sed 's/\0;93m//g'| sed 's/\0;90m//g'| sed 's/\0;92m//g'| sed 's/\0;39m//g' > log/1.Warning_linting/clang_www.txt

	@echo "\n##Clang Fron-End Semantic Wcore - fsyntaxOnly"
	echo "############################################\n"
	$(MAKE) CFLAGS_DBG="-Wformat -Warray-bounds -Wnull-dereference -Wvla -ftrapv" 2>&1 | sed 's/\x1b\[//g' | sed 's/\0;93m//g'| sed 's/\0;92m//g'| sed 's/\0;39m//g' > log/1.Warning_linting/clang_wcore.txt

	@echo "\n##Clang Fron-End Semantic wEverything - fsyntaxOnly"
	echo "############################################\n"
	$(MAKE) CFLAGS_DBG="-Weverything" 2>&1 | sed 's/\x1b\[//g' | sed 's/\0;93m//g'| sed 's/\0;92m//g'| sed 's/\0;39m//g' > log/1.Warning_linting/clang_wevery.txt

	@echo "\n##Clang Fron-End Semantic Clang-Tidy - fsyntaxOnly"
	echo "############################################\n"
	clang-tidy -p log/6.Make_dbg/compile_commands.json $(SOURCE_SRC_ALL) 2>&1 | sed 's/\x1b\[//g' | sed 's/\0;93m//g'| sed 's/\0;92m//g'| sed 's/\0;39m//g' > log/1.Warning_linting/clang_tidy.txt
	
	@echo "\n###Clang Static Analyzer Wcore"
	echo  "#########################\n"
	$(MAKE) CFLAGS_DBG="--analyze -Xanalyzer -analyzer-checker=core" 2>&1 | sed 's/\x1b\[//g' | sed 's/\0;93m//g'| sed 's/\0;92m//g'| sed 's/\0;39m//g' | tee log/1.Warning_linting/clang_analyzer.txt

# *** Norminette on Project*** #
norm:
	@echo "$(GREEN)\n····Running Norminette····$(RESET)"
	norminette src > log/1.Warning_linting/norminette.txt; \
	norminette inc >> log/1.Warning_linting/norminette.txt ; cat log/1.Warning_linting/norminette.txt

# *** Clang tidy fix*** #
clang_tidy_fix:
		clang-tidy $(SOURCE_MAIN) $(SOURCE_FILES) --fix

# *** Norminette on Bonus*** #
norm_bonus:
	@echo "$(GREEN)\n····Running Norminette····$(RESET)"
	norminette src/checker_bonus > log/1.Warning_linting/norminette_bonus.txt ; cat log/1.Warning_linting/norminette_bonus.txt \


werror_bonus:
	@echo "$(GREEN)\n·Clang lintings$(RESET)"
	echo "\n## BONUS Clang Wall Wextra - fsyntaxOnly"
	echo "############################################\n"
	$(CHECKER_BUILD) CFLAGS_DBG="-Wall -Wextra" || true > log/1.Warning_linting/bonus_clang_www.txt
	
	@echo "\n## BONUS Clang Fron-End Semantic - fsyntaxOnly"
	echo "############################################\n"
	$(CHECKER_BUILD) CFLAGS_DBG="-Wformat -Warray-bounds -Wnull-dereference -Wvla -ftrapv" 2>&1 | sed 's/\x1b\[//g' | sed 's/\0;93m//g'| sed 's/\0;92m//g'| sed 's/\0;39m//g' > log/1.Warning_linting/bonus_clang_wevery.txt
	
	@echo "\n### BONUS Clang Static Analyzer"
	echo  "#########################\n"
	$(CHECKER_BUILD) CFLAGS_DBG="--analyze -Xanalyzer -analyzer-checker=core " 2>&1 | sed 's/\x1b\[//g' | sed 's/\0;93m//g'| sed 's/\0;92m//g'| sed 's/\0;39m//g' | tee log/1.Warning_linting/bonus_clang_analyzer.txt






















# ############################################################################ #
#                                 LEAKS                                        #
# ############################################################################ #
# # *** Leaks analyzer *** #
# #log_leaks:
# #	mkdir -p log/4.Bins_folder
# 	$(MAKE)
# 	$(MAKE) create_bins_leaks
# 	$(MAKE) valgrind
# 	$(MAKE) asan || true

leaks_bonus:
		$(MAKE) create_bins_leaks_bonus

# *** Create bins for the leaks analyzer *** #

create_bins_leaks: log/4.Bins_folder/${NAME0}_g $(OBJECTS)
log/4.Bins_folder/$(NAME0)_g: $(OBJECTS)

# *** _g *** #
	$(MAKE) fclean
	$(MAKE) CFLAGS_DBG=" -g" OUTPUT_PLACE="log/4.Bins_folder/" NAME0=$(NAME0)_g
	gdb -batch -ex "info functions" log/4.Bins_folder/$(NAME0)_g > log/4.Bins_folder/log/gdb_functions_$(NAME0)_g.txt

# *** Asan *** #
	$(MAKE) fclean
	$(MAKE) CFLAG_ASAN=" -g -fsanitize=address -fno-omit-frame-pointer" OUTPUT_PLACE="log/4.Bins_folder/" NAME0=$(NAME0)_asan
	gdb -batch -ex "info functions" log/4.Bins_folder/$(NAME0)_asan > log/4.Bins_folder/log/gdb_functions_$(NAME0)_asan.txt
	$(MAKE) fclean

# *** BONUS _g *** #
create_bins_leaks_bonus:
	$(MAKE) fclean -C $(CHECKER_BONUS_DIR)
	$(MAKE) CFLAGS_DBG=" -g" OUTPUT_PLACE="../../log/4.Bins_folder/" NAME0="checker_g" -C $(CHECKER_BONUS_DIR)
	gdb -batch -ex "info functions" log/4.Bins_folder/checker_g > log/4.Bins_folder/log/gdb_functions_checker_g_asan.txt

# *** Runing Valgrind *** #
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
VALGRIND_EXPORT = --log-file=log/2.Memory_Check/logs/valgrind_report_.txt
#valgrind:
log_leaks:
	$(MAKE)
	$(MAKE) create_bins_leaks
	@echo "$(RED)\n# RUNNING VALGRIND: ERROR_HANDLING_INPUTS$(RESET)"
	@echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
	@echo "$(BOLD)\n# RUNNING VALGRIND ARG_EMPTY$(RESET)"
	
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_error_handling_empty.txt ./log/4.Bins_folder/push_swap_g $(ARG_EMPTY) 2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_error_handling_empty.txt && echo "1. Empty: ok" > log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_error_handling_empty.txt && echo "1. Empty: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true	
	
	@echo "$(BOLD)\n# RUNNING VALGRIND ARG_ONE$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_error_handling_one.txt ./log/4.Bins_folder/push_swap_g $(ARG_1) 2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_error_handling_one.txt && echo "2. One: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_error_handling_one.txt && echo "2. One: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true

	@echo "$(BOLD)\n# RUNNING VALGRIND INT_MAX$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_error_handling_intmax.txt ./log/4.Bins_folder/push_swap_g $(ARG_INT_MAX) 2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_error_handling_intmax.txt && echo "3. INT_MAX: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_error_handling_intmax.txt && echo "3. INT_MAX: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true

	@echo "$(BOLD)\n# RUNNING VALGRIND INT_MIN$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_error_handling_min.txt ./log/4.Bins_folder/push_swap_g $(ARG_INT_MIN) 2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_error_handling_min.txt && echo "4. INT_MIN: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_error_handling_min.txt && echo "4. INT_MIN: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true

	@echo "$(BOLD)\n# RUNNING VALGRIND ARG_SORTED$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_error_handling_sort.txt ./log/4.Bins_folder/push_swap_g $(ARG_SORTED) 2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_error_handling_sort.txt && echo "5: Sort: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_error_handling_sort.txt && echo "5: Sort: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true

	@echo "$(BOLD)\n# RUNNING VALGRIND ARG_DUPLICATED$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_error_handling_dupl.txt ./log/4.Bins_folder/push_swap_g $(ARG_DUPLICATED) 2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_error_handling_dupl.txt && echo "6. Dupl: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_error_handling_dupl.txt && echo "6. Dupl: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true

	@echo "$(BOLD)\n# RUNNING VALGRIND ARG_NON_NUMERIC$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_error_handling_nonnum.txt ./log/4.Bins_folder/push_swap_g $(ARG_NON_NUMERIC) 2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_error_handling_nonnum.txt && echo "7. Alpha: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_error_handling_nonnum.txt && echo "7. Alpha: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
	
	@echo "$(RED)\n# RUNNING VALGRIND: PERFORMANCE_CHECK$(RESET)"
	@echo "---------------------------------------------------------------------------------------------------------------------------"
	
	@echo "$(BOLD)\n# RUNNING VALGRIND 5 NUMBERS$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_5.txt ./log/4.Bins_folder/push_swap_g $(ARG_5)  2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_5.txt && echo "8. ARG_5: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_5.txt && echo "8. ARG_5: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	

	@echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
	
	@echo "$(BOLD)\n# RUNNING VALGRIND 6 NUMBERS$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_6.txt ./log/4.Bins_folder/push_swap_g $(ARG_6) 2>&1 || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_6.txt && echo "9. ARG_6: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_6.txt && echo "9. ARG_6: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true

	@echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
	
	@echo "$(BOLD)\n# RUNNING VALGRIND 6 NUMBERS_NO_SPLIT$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_push_6_not_split.txt ./log/4.Bins_folder/push_swap_g 0 9 1 8 2 6 2>&1 || true
	@if grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_push_6_not_split.txt; then \
		echo "10. ARG_6_Nsplit: Leaks: Ok" >> log/2.Memory_Check/Valgrind_Report.txt; \
	else \
		echo "10. ARG_6_Nsplit: Leaks: Nok" >> log/2.Memory_Check/Valgrind_Report.txt; \
	fi
	@if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_push_6_not_split.txt; then \
		echo "10. ARG_6_Nsplit: Errors: Ok" >> log/2.Memory_Check/Valgrind_Report.txt; \
	else \
		echo "10. ARG_6_Nsplit: Errors: Nok" >> log/2.Memory_Check/Valgrind_Report.txt; \
	fi

	@echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
	
	@echo "$(BOLD)\n# RUNNING VALGRIND ON CHECKER$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	$(VALGRIND) --log-file=log/2.Memory_Check/logs/valgrind_report_checker_6.txt ./log/4.Bins_folder/push_swap_g $(ARG_6) | ./log/4.Bins_folder/checker_g $(ARG_6) || true
	@echo "11. ARG_6 Checker:" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "All heap blocks were freed -- no leaks are possible" log/2.Memory_Check/logs/valgrind_report_checker_6.txt && echo "11. ARG_6 Checker: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true
	@grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log/2.Memory_Check/logs/valgrind_report_checker_6.txt && echo "11. ARG_6 Checker: ok" >> log/2.Memory_Check/Valgrind_Report.txt || true

	@echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
	
	@echo "$(BOLD)\n# RUNNING VALGRIND MASSIF && CACHEGRIND && CALLGRIND$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"

# *** Massif Target  *** #
	valgrind --tool=massif --massif-out-file=log/2.Memory_Check/logs/val_massif.out ./log/4.Bins_folder/push_swap_g $(ARG_6)
	ms_print log/2.Memory_Check/logs/val_massif.out > log/2.Memory_Check/logs/val_massif_report.txt
# *** Cachegrind Target *** #
	valgrind --tool=cachegrind --cachegrind-out-file=log/2.Memory_Check/logs/val_cachegrind.out ./log/4.Bins_folder/push_swap_g $(ARG_6)
# *** Callgrind Target *** #
	valgrind --tool=callgrind --callgrind-out-file=log/2.Memory_Check/logs/val_callgrind.out ./log/4.Bins_folder/push_swap_g $(ARG_6)

# *** runing Asan *** #
asan:
	@echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
	@echo "$(BOLD)\n# RUNNING ASAN$(RESET)"
	@for i in $(shell seq 1 100); do printf "$(GREEN)▓";sleep 0.0001; done; echo " ✓$(RESET)"
	export ASAN_OPTIONS="halt_on_error=0:log_path=log/2.Memory_Check/logs/Asan_report.txt";
	./log/4.Bins_folder/push_swap_asan $(ARG_6)
	@echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
	export ASAN_OPTIONS="halt_on_error=0:log_path=log/2.Memory_Check/logs/Asan_report_2.txt";
	./log/4.Bins_folder/push_swap_asan 5 4 3 2 1
	@echo "$(RESET)---------------------------------------------------------------------------------------------------------------------------"
















































# ############################################################################ #
#                             DYNAMIC ANALYSIS TESTERS                         #
# ############################################################################ #
# *** Command to run all tests *** #
log_dynamic_analysis_tests:
	$(MAKE) testers_folder_build
	$(MAKE) bonus
	$(MAKE) tests_run | tee log/3.Unit_Testing/Testing_Report.txt
	$(MAKE) test_performance
	$(MAKE) create_bins_dbg

#sed -r 's/\x1B\[[0-9;]*[mGKH]//g'
# ************************************************************************ #
#                               TESTERS_FOLDER                             #
# ************************************************************************ #
# *** Folder builder testers *** #
testers/testers.tar.gz:
	pipx install gdown
	mkdir -p testers
	gdown 'https://drive.google.com/uc?id=10rQ0zUPZZFOO4epDa62sx_2kUUrl1EFo' -O $@
#https://drive.google.com/file/d/10rQ0zUPZZFOO4epDa62sx_2kUUrl1EFo/view?usp=sharing

testers/checker_linux: testers/testers.tar.gz
	tar -xzf testers/testers.tar.gz -C .

testers_folder_build: testers/checker_linux


#testers: testers/testers.tar.gz 
#		tar -xzf $< -C .

# ************************************************************************ #
#                                   TESTS RUN                              #
# ************************************************************************ #
# *** Inputs for the tests *** #
ARG_EMPTY=""
ARG_1="2147483647"
ARG_INT_MAX="2147483648 3 2 1"
ARG_INT_MIN="-2147483649 3 2 1"
ARG_SORTED="1 2 3 4 2147483647"
ARG_DUPLICATED=	"5 4 3 2 1 1"
ARG_NON_NUMERIC="a 1 3 4 5"

ARG_2="9 -1"
ARG_3="0 9 2"
ARG_4="0 9 -2 8"
ARG_5="3 9 2 8 0"

ARG_6="0 9 2 8 3"
ARG_12="150 20 124 -80 100 123 -139 -27 59 91 186 212"
ARG_24="-8 -121 178 236 -131 -185 117 26 86 -156 -148 213 -216 102 -61 -126 93 -42 200 79 -116 78 -198 216"
ARG_50="-47 139 204 167 -95 76 203 67 -60 -12 -238 191 -105 -7 28 235 -54 239 189 -141 135 104 202 -226 -165 -9 101 -88 78 250 124 -157 163 40 -210 192 136 -99 137 157 72 -66 -33 -235 -118 -17 170 -49 -101 174"
ARG_75="-89 126 228 -14 -33 109 247 -242 -133 148 1 147 -201 -46 42 6 115 -52 249 -130 -215 67 12 202 17 -188 92 -47 -39 87 -44 -124 45 -158 11 -163 -129 38 36 -106 188 149 -235 171 -92 213 -195 -115 96 -81 4 -231 223 -216 25 229 244 208 -228 -179 -144 137 -116 91 59 -205 -237 95 -97 -229 -82 193 -113 -30 -40"
ARG_250="-35 -43 -206 -42 -37 137 -212 171 -19 -31 90 5 -201 87 158 -8 -198 226 141 222 -4 -165 103 76 33 188 61 175 62 -85 -54 -94 31 -121 4 -205 219 -66 102 -101 -32 46 -214 -108 -141 -86 127 -131 -166 8 -167 -2 78 -190 96 -74 -160 -172 -178 55 -73 218 238 -106 -238 -142 -105 -227 201 -230 -69 -118 -162 101 21 -17 -149 -114 7 -29 149 100 -120 126 117 209 -197 -152 233 235 27 189 -144 98 243 56 191 -221 71 -169 -6 30 12 -103 186 -91 134 -202 -48 -243 -41 216 -240 10 35 227 26 155 -193 195 -25 -67 -112 -236 180 142 -128 -139 123 97 -129 213 -231 3 174 166 236 -33 29 -250 194 95 228 43 -80 139 190 -217 168 144 210 -70 -123 239 13 -218 -87 -170 199 -195 208 207 -50 -163 -137 -81 -55 -220 -176 -99 -116 -30 47 -232 -204 -117 -188 19 -148 198 130 -9 22 -222 -210 0 -225 -26 -175 -20 -207 -1 -223 80 -159 -78 -111 -125 200 32 -219 -77 88 41 -53 72 122 160 -110 206 -249 132 -75 193 -96 44 111 151 66 203 -246 -44 1 -203 192 -171 40 6 -145 -211 -28 -88 185 110 154 -234 68 183 128 -62 217 -61 -104 45 -102 187 246 159 181 162"
ARG_375="210 -5 171 242 -140 -1 173 -64 -78 230 -249 175 -83 -25 -124 -106 -206 -193 -70 181 -89 -8 -234 -188 134 -76 194 43 -27 -242 -131 -137 183 -19 -204 -109 -34 -233 -148 -149 -133 -208 127 -52 71 203 88 -99 -47 -179 31 -50 -139 241 115 -192 153 8 -197 94 63 -42 -67 -102 110 -128 38 235 247 120 -153 -96 -176 -143 136 239 20 39 -101 -20 21 91 124 109 -26 -138 135 -207 -32 84 -232 19 37 57 -146 -223 -145 151 172 144 -90 143 221 54 145 -13 176 -155 48 204 -135 -161 166 1 49 -41 121 93 248 180 100 36 -141 -201 102 -53 -173 3 -172 245 238 162 -94 -11 244 -121 196 -228 -40 -190 -81 98 41 -49 -85 -127 -3 101 158 129 -241 -37 152 -62 26 -168 -45 206 -113 87 -29 -56 -15 -196 56 128 157 170 131 -244 190 -222 -105 -183 -158 104 35 -250 154 11 -210 51 122 189 -166 187 -123 218 59 -80 -134 -243 -46 96 -28 68 10 224 -247 -69 -152 77 -112 -248 249 -21 -227 -35 132 -212 -194 227 58 -97 -43 164 14 -55 -114 184 156 -163 105 -209 -239 250 220 -225 17 146 -73 199 -167 147 -39 216 228 139 29 82 -182 46 222 119 28 -211 60 -198 195 -154 32 69 74 -84 -18 -130 112 -82 178 -33 163 -180 130 89 214 -205 90 -200 -63 27 149 18 114 12 -51 229 -117 -61 -66 -65 -226 167 -129 15 -38 113 -12 -10 -22 106 -7 -71 -110 -74 -77 -177 225 117 -220 -237 142 -118 -57 44 236 86 -151 83 -75 179 -185 186 -98 -231 92 165 148 -72 207 231 45 234 -23 -174 -246 -92 -100 53 95 7 67 -171 13 -93 -147 141 -132 -111 226 -14 -86 -218 237 209 16 9 -162 65 198 -184 -17 197 33 182 223 -107 -48 116 34 200 -24 -178 79 -189 -68 111 47 212 107 205 -2 -216 -88 25 168"

ARG_100="-132 192 -136 -182 135 169 -194 -201 52 217 156 36 236 -55 -139 0 238 -227 221 -177 -87 -95 214 -34 -102 -154 191 83 -105 -144 244 -137 -186 -199 240 150 -113 -180 -36 175 -164 -110 -115 20 -235 237 87 -130 122 61 -239 -225 -206 14 -45 176 57 -121 10 -100 60 168 -86 -210 -134 -91 204 72 -205 53 -195 -40 -23 -141 243 209 212 142 -82 -187 -5 22 112 132 178 163 -250 222 -170 -248 216 126 234 218 194 76 170 224 67 -219"
ARG_500="-230 159 -202 -148 73 -210 28 -176 -134 143 -7 203 -99 -145 6 -239 97 -155 -215 117 -124 17 151 152 110 176 148 131 244 -235 207 -82 41 162 101 21 115 -138 -86 231 -122 -217 26 -43 192 -116 64 -29 -49 -200 4 -168 -53 19 -78 -234 -137 -63 0 -170 -172 -109 39 -192 -125 -95 -25 185 -160 11 220 -169 -249 98 -203 -102 -117 184 212 -83 -227 116 114 168 -245 156 142 126 -101 70 -178 113 -237 -91 -98 -64 193 -158 242 -15 -68 227 -24 108 88 -163 -119 -76 -244 -62 23 -151 58 210 -90 -129 -65 -193 89 197 -74 60 208 -16 57 124 169 111 -243 232 -162 -198 24 2 -58 141 -84 174 87 31 -180 122 -60 -85 -108 -126 -154 -139 33 129 132 -87 -32 -114 -52 27 -56 3 37 -128 99 -183 204 -132 -118 186 -105 -103 133 62 72 -174 137 -42 170 -34 199 -167 120 29 -27 196 -142 61 50 -50 74 130 -241 -40 -204 10 -199 233 243 -75 -21 -77 161 112 35 95 248 181 249 250 -106 84 157 167 194 -228 14 175 -222 -166 -236 107 -189 177 53 106 -112 245 -110 206 -18 155 -224 -72 102 -93 -17 -111 -209 -10 94 -153 18 -69 118 -94 123 160 -226 77 -104 -159 149 216 79 164 -36 90 -173 96 -141 -48 40 158 223 -35 -135 -184 -156 -196 -181 179 -123 -13 -71 -195 -44 -66 -150 -161 146 150 85 -38 38 171 144 153 54 16 236 136 205 134 125 -19 -6 -133 69 -225 86 219 119 32 -31 -131 -57 -61 83 172 -214 91 -20 -33 56 -186 154 -4 145 -238 25 209 36 -89 92 228 -140 -187 -231 138 200 -37 -143 225 -149 -45 214 34 -177 -1 13 -127 81 -107 -120 -46 182 -121 -146 43 75 -136 -54 239 -190 -247 229 -152 189 188 -97 -70 100 -113 -179 237 55 65 -73 211 -194 7 -144 230 -212 45 -51 201 238 22 -246 -191 20 -182 -9 109 127 -28 246 -147 183 198 -211 51 49 -8 67 63 147 46 -30 78 202 -5 -171 128 213 66 -220 76 -81 -175 247 135 -157 -223 42 -248 -67 -115 -88 166 -219 165 -208 71 52 8 -197 -79 -41 -250 -188 222 68 180 -26 226 -216 -232 -23 105 235 59 -22 103 173 224 -3 -207 -130 93 190 44 -11 191 221 9 104 -2 240 -59 241 139 178 5 215 -240 -201 217 30 -165 12 80 163 47 187 -92 -14 -242 -206 82 234 -39 140 195 121 15 -233 -100 -96 1 -164 -55 -47 48 -80 -185 -229 -218 -205 218 -12 -221"



tests_run_12:
	-echo -n "$(YELLOW)b1. ARG_12$(GREEN): | " ; ./push_swap $(ARG_12) 2>&1 | ./testers/checker_linux $(ARG_12) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_12) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
tests_run_12_valgrind:
		$(VALGRIND) $(VALGRIND_EXPORT) ./log/4.Bins_folder/push_swap_g3 $(ARG_12) 2>&1

tests_run_24:
	-echo -n "$(YELLOW)b1. ARG_24$(GREEN): | " ; ./push_swap $(ARG_24) 2>&1 | ./testers/checker_linux $(ARG_24) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_24) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
tests_run_24_valgrind:
		$(VALGRIND) $(VALGRIND_EXPORT) ./log/4.Bins_folder/push_swap_g3 $(ARG_24) 2>&1

tests_run_50:
	-echo -n "$(YELLOW)b1. ARG_50$(GREEN): | " ; ./push_swap $(ARG_50) 2>&1 | ./testers/checker_linux $(ARG_50) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_50) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
tests_run_50_valgrind:
		$(VALGRIND) $(VALGRIND_EXPORT) ./log/4.Bins_folder/push_swap_g3 $(ARG_50) 2>&1
		$(VALGRIND) ./log/4.Bins_folder/push_swap_g3 $(ARG_50) 2>&1
tests_run_75:
	-echo -n "$(YELLOW)b1. ARG_75$(GREEN): | " ; ./push_swap $(ARG_75) 2>&1 | ./testers/checker_linux $(ARG_75) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_75) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";

tests_run_250:
	-echo -n "$(YELLOW)b2. ARG_250$(BLUE): | " ; ./push_swap $(ARG_250) 2>&1 | ./testers/checker_linux $(ARG_250) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_250) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
tests_run_250_valgrind:
	-echo -n "$(YELLOW)b3. ARG_250$(BLUE): | " ; $(VALGRIND) $(VALGRIND_EXPORT) ./push_swap $(ARG_250)  2>&1 ;
tests_run_375:
	-echo -n "$(YELLOW)b2. ARG_375$(BLUE): | " ; ./push_swap $(ARG_375) 2>&1 | ./testers/checker_linux $(ARG_375) | tr '\n' ' ' ; echo -n " | " ; /push_swap $(ARG_375) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
tests_run_375_valgrind:
	-echo -n "$(YELLOW)b3. ARG_375$(BLUE): | " ; $(VALGRIND) $(VALGRIND_EXPORT) ./push_swap $(ARG_375)  2>&1 ;



tests_run_5:
	-echo -n "$(YELLOW)b1. ARG_5$(BLUE): | " ; ./push_swap $(ARG_5) 2>&1 | ./testers/checker_linux $(ARG_5) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_5) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_5) > log/3.Unit_Testing/moves/moves_5.txt; echo "";

tests_run_100:
	-echo -n "$(YELLOW)b2. ARG_100$(BLUE): | " ; ./push_swap $(ARG_100) 2>&1 | ./testers/checker_linux $(ARG_100) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_100) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
tests_run_100_valgrind:
	-echo -n "$(YELLOW)b3. ARG_100$(BLUE): | " ; $(VALGRIND) $(VALGRIND_EXPORT) ./push_swap $(ARG_100)  2>&1 ;

tests_run_500:
	-echo -n "$(YELLOW)b3. ARG_500$(BLUE): | " ; ./push_swap $(ARG_500) 2>&1 | ./testers/checker_linux $(ARG_500) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_500) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
tests_run_500_valgrind:
	-echo -n "$(YELLOW)b3. ARG_500$(BLUE): | " ; $(VALGRIND) $(VALGRIND_EXPORT) ./push_swap $(ARG_500)  2>&1 ;

# *** Run only the tests *** #
.PHONY: test_run
tests_run:
	@echo "$(RED)\n# RUNNING TESTS$(RESET)"
	@echo ""
	@echo "$(BOLD)### Milestones$(RESET)"
	@echo "Points for #5 numbers:"
	@echo "- less than 8: kudos"
	@echo "- less than 12: ok"
	@echo "- more than 12; FAIL!"
	@echo ""
	@echo "Points for #100 numbers:"
	@echo "- less than 700: 5"
	@echo "- less than 900: 4"
	@echo "- less than 1,100: 3"
	@echo "- less than 1,300: 2"
	@echo "- less than 1,500: 1"
	@echo ""
	@echo "Points for #500 numbers"
	@echo "- less than 5,500: 5"
	@echo "- less than 7,000: 4"
	@echo "- less than 8,500: 3"
	@echo "- less than 10,000: 2"
	@echo "- less than 11,500: 1"
	@echo ""
	@echo "Min Points: 8"
	@echo "---------------------------------------------------------------------------------------------------------------------------"
	echo"";
	-echo -n "$(GRAY)A ERROR_HANDLING_INPUTS $(RESET)"; echo"";
	-echo -n "$(YELLOW)a1. ARG_DUPLICATED$(GREEN): | " ; ./push_swap $(ARG_DUPLICATED) 2>&1  | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_DUPLICATED) 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)a2. ARG_NON_NUMERIC$(GREEN): | " ; ./push_swap $(ARG_NON_NUMERIC) 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_NON_NUMERIC) 2>&1  | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)a3. ARG_INT_MAX$(GREEN): | " ; ./push_swap $(ARG_INT_MAX) 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_INT_MAX) 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)a4. ARG_INT_MIN$(GREEN): | " ; ./push_swap $(ARG_INT_MIN) 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_INT_MIN) 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(GRAY)A ERROR_HANDLING_INPUTS2 $(RESET)"; echo"";
	-echo -n "$(YELLOW)a5. ARG_EMPTY $(GREEN): | " ; ./push_swap $(ARG_EMPTY) 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_EMPTY) 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_EMPTY) 2>&1; echo "";
	-echo -n "$(YELLOW)a6. ARG_1$(GREEN): | " ; ./push_swap $(ARG_1) 2>&1 |  tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_1) | wc -l 2>&1 | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)a7. ARG_SORTED$(GREEN): | " ; ./push_swap $(ARG_SORTED) 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_SORTED) | wc -l | tr '\n' ' ' ; echo -n " | " ;  echo "";echo "";
	-echo -n "$(GRAY)A ERROR_HANDLING_INPUTS3 $(RESET)"; echo"";
	-echo -n "$(YELLOW)b1. ARG_5_NOT_SPLIT$(GREEN): | " ; ./push_swap 0 9 2 8 -3 2>&1 | ./testers/checker_linux 0 9 2 8 -3 | tr '\n' ' ' ; echo -n " | " ; ./push_swap 0 9 2 8 3 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)b1. ARG_6_NOT_SPLIT$(GREEN): | " ; ./push_swap 0 9 2 8 3 -42 2>&1 | ./testers/checker_linux 0 9 2 8 3 -42 | tr '\n' ' ' ; echo -n " | " ; ./push_swap 0 9 2 8 3 -42 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	echo"";
	-echo -n "$(GRAY)B PERFORMANCE_CHECK $(RESET)"; echo""
	-echo -n "$(YELLOW)b1. ARG_2$(BLUE): | " ; ./push_swap $(ARG_2) 2>&1 | ./testers/checker_linux $(ARG_2) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_2) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_2) > log/3.Unit_Testing/moves/moves_2.txt; echo "";
	-echo -n "$(YELLOW)b1. ARG_3$(BLUE): | " ; ./push_swap $(ARG_3) 2>&1 | ./testers/checker_linux $(ARG_3) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_3) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_3) > log/3.Unit_Testing/moves/moves_3.txt; echo "";
	-echo -n "$(YELLOW)b1. ARG_4$(BLUE): | " ; ./push_swap $(ARG_4) 2>&1 | ./testers/checker_linux $(ARG_4) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_4) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_4) > log/3.Unit_Testing/moves/moves_4.txt; echo "";
	-echo -n "$(YELLOW)b1. ARG_5$(BLUE): | " ; ./push_swap $(ARG_5) 2>&1 | ./testers/checker_linux $(ARG_5) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_5) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_5) > log/3.Unit_Testing/moves/moves_5.txt; echo "";
	-echo -n "$(YELLOW)b2. ARG_100$(BLUE): | " ; ./push_swap $(ARG_100) 2>&1 | ./testers/checker_linux $(ARG_100) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_100) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_100) > log/3.Unit_Testing/moves/moves_100.txt; echo "";
	-echo -n "$(YELLOW)b3. ARG_500$(BLUE): | " ; ./push_swap $(ARG_500) 2>&1 | ./testers/checker_linux $(ARG_500) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_500) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_500) > log/3.Unit_Testing/moves/moves_500.txt; echo "";
	echo""
	-echo -n "$(GRAY)B PERFORMANCE_CHECK_BONUS $(RESET)"; echo""
	-echo -n "$(YELLOW)b3. ARG_500 && CHECKER_BONUS$(GREEN): | " ; ./push_swap $(ARG_5) | ./checker $(ARG_5) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_5) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)b3. ARG_500 && CHECKER_BONUS$(GREEN): | " ; ./push_swap $(ARG_100) | ./checker $(ARG_100) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_100) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)b3. ARG_500 && CHECKER_BONUS$(GREEN): | " ; ./push_swap $(ARG_500) | ./checker $(ARG_500) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_500) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	echo"";
	-echo -n "$(GRAY)C ERROR_HANDLING_INPUTS_BONUS $(RESET)"; echo"";
	-echo -n "$(YELLOW)a1. ARG_INT_MAX$(GREEN): | " ; ./checker $(ARG_INT_MAX) 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./checker $(ARG_INT_MAX) 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | "  ; echo "";
	-echo -n "$(YELLOW)a2. ARG_INT_MIN$(GREEN): | " ; ./checker $(ARG_INT_MIN) 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./checker $(ARG_INT_MIN) 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)a3. ARG_DUPLICATED$(GREEN): | " ; ./checker $(ARG_DUPLICATED) 2>&1  | tr '\n' ' ' ; echo -n " | " ; ./checker $(ARG_DUPLICATED) 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)a4. ARG_NON_NUMERIC$(GREEN): | " ; ./checker $(ARG_NON_NUMERIC) 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./checker $(ARG_NON_NUMERIC) 2>&1  | wc -l | tr '\n' ' ' ; echo -n " | "; echo "";
	-echo -n "$(GRAY)C ERROR_HANDLING_INPUTS_2_BONUS $(RESET)"; echo"";
	-echo -n "$(YELLOW)a5. ARG_EMPTY $(GREEN): | " ; ./checker $(ARG_EMPTY) <<EOF 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./checker $(ARG_EMPTY) <<EOF 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)a6. ARG_1$(GREEN): | " ; ./checker $(ARG_1) <<EOF 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./checker $(ARG_1) <<EOF 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)a7. ARG_SORTED$(GREEN): | " ; ./checker $(ARG_SORTED) <<EOF 2>&1 | tr '\n' ' ' ; echo -n " | " ; ./checker $(ARG_SORTED) <<EOF 2>&1 | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "---------------------------------------------------------------------------------------------------------------------------$(RESET)"; echo"";
	
test_performance:
	$(MAKE)
	/usr/bin/time -v ./push_swap $(ARG_500) 2> log/3.Unit_Testing/perfomance_time_push_ARG500.txt 1> /dev/null

perfomance:
	$(MAKE) fclean_all
	mkdir -p log/3.Unit_Testing
	/usr/bin/time -v $(MAKE) log_alles 2> log/3.Unit_Testing/perfomance_time_log_all.txt 1> /dev/null

tests_run_small:
	-echo -n "$(GRAY)B PERFORMANCE_CHECK $(RESET)"; echo""
	-echo -n "$(YELLOW)b1. ARG_2$(BLUE): | " ; ./push_swap $(ARG_2) 2>&1 | ./testers/checker_linux $(ARG_2) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_2) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_2) > log/3.Unit_Testing/moves/moves_2.txt; echo "";
	-echo -n "$(YELLOW)b1. ARG_3$(BLUE): | " ; ./push_swap $(ARG_3) 2>&1 | ./testers/checker_linux $(ARG_3) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_3) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_3) > log/3.Unit_Testing/moves/moves_3.txt; echo "";
	-echo -n "$(YELLOW)b1. ARG_4$(BLUE): | " ; ./push_swap $(ARG_4) 2>&1 | ./testers/checker_linux $(ARG_4) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_4) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_4) > log/3.Unit_Testing/moves/moves_4.txt; echo "";
	-echo -n "$(YELLOW)b1. ARG_5$(BLUE): | " ; ./push_swap $(ARG_5) 2>&1 | ./testers/checker_linux $(ARG_5) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_5) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_5) > log/3.Unit_Testing/moves/moves_5.txt; echo "";


test_bonus:
	$(MAKE) testers_folder_build
	$(MAKE) bonus
	-echo -n "$(GRAY)B PERFORMANCE_CHECK_LINUX $(RESET)"; echo""
	-echo -n "$(YELLOW)b2. ARG_100$(BLUE): | " ; ./push_swap $(ARG_100) 2>&1 | ./testers/checker_linux $(ARG_100) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_100) | wc -l | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_100) > log/3.Unit_Testing/moves/moves_100.txt; echo "";
	-echo -n "$(GRAY)B PERFORMANCE_CHECK_BONUS $(RESET)"; echo""
	-echo -n "$(YELLOW)b3. ARG_500 && CHECKER_BONUS$(GREEN): | " ; ./push_swap $(ARG_5) | ./checker $(ARG_5) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_5) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)b3. ARG_500 && CHECKER_BONUS$(GREEN): | " ; ./push_swap $(ARG_100) | ./checker $(ARG_100) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_100) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";
	-echo -n "$(YELLOW)b3. ARG_500 && CHECKER_BONUS$(GREEN): | " ; ./push_swap $(ARG_500) | ./checker $(ARG_500) | tr '\n' ' ' ; echo -n " | " ; ./push_swap $(ARG_500) | wc -l | tr '\n' ' ' ; echo -n " | " ; echo "";



























# ############################################################################ #
#                                DEBUGGERS                                     #
# ############################################################################ #

# ************************************************************************ #
#                                 RUN DEBUGGER                             #
# ************************************************************************ #
# *** Command to run especif debug *** #
debug-gdb: 
	$(MAKE) CFLAGS="$(CFLAGS) -g3"
	gdb ./$(NAME) -o "b main" -o run -o gui -o "run $(ARG_12)" 

debug-lldb: 
	$(MAKE) CFLAGS="$(CFLAGS) -g3"
	lldb ./$(NAME) -o "b main" -o run -o gui -o "run $(ARG_12)" 

debug-vscode:
ifeq ($(ALGO), 0)
	$(MAKE) create_bins_dbg
endif
	code -r -g log/4.Bins_folder/push_swap.c:1
	sleep 1
	xdotool key F5
#   code --open-url "vscode://ms-vscode.cpptools/debug/launch?name=PUSHSWAP_DBG"
#	code --open-url "vscode://ms-vscode.cpptools/debug?name=Debug%20Push%20Swap&program=$(CURDIR)/$(NAME)&args=$(ARG_12)"



# *** Debuggers *** #
debuggers:
	$(MAKE) create_bins_dbg
	$(MAKE) debuggers_info

# ************************************************************************ #
#                                                                          #
# ************************************************************************ #
# *** Create the bin for G3 debugging *** #
create_bins_dbg: log/4.Bins_folder/$(NAME0)_g3
log/4.Bins_folder/$(NAME0)_g3: $(OBJECTS)
# *** debugging _g3 *** #
	$(MAKE) fclean
	$(MAKE) CFLAGS_DBG=" -g3" OUTPUT_PLACE="log/4.Bins_folder/" NAME0=$(NAME0)_g3
	gdb -batch -ex "info functions" log/4.Bins_folder/$(NAME0)_g3 > log/4.Bins_folder/log/gdb_functions_$(NAME0)_g3.txt
	cd log/4.Bins_folder
	ln -s ../../src/push_swap/push_swap.c log/4.Bins_folder/push_swap.c || true
	ln -s ../../src/checker_bonus/src/checker_bonus.c log/4.Bins_folder/checker_bonus.c || true

.PHONY: create_bins_dbg

# *** Librarys info and make=debug *** #
debuggers_info:
	$(MAKE) libs_nm_art
#	$(MAKE) make_dbg


libs_nm_art:
	nm libs/lib$(LIB_1_NAME).a > log/5.Libs_nmart/lib$(LIB_1_NAME)_nm.txt
	ar t libs/lib$(LIB_1_NAME).a > log/5.Libs_nmart/lib$(LIB_1_NAME)_art.txt
	nm libs/lib$(NAME1).a > log/5.Libs_nmart/lib$(NAME1)_nm.txt
	ar t libs/lib$(NAME1).a > log/5.Libs_nmart/lib$(NAME1)_art.txt

make_dbg:
	$(MAKE) -d > log/6.Make_dbg/make_d.txt
	$(MAKE) CFLAGS_DBG="-v" > log/6.Make_dbg/clang_v.txt
	$(MAKE) --debug=b -j1 re > log/6.Make_dbg/make_debug_b.txt
	$(MAKE) --debug=v -j1 re > log/6.Make_dbg/make_debug_v.txt






























# **************************************************************************** #
#                                DOXYGEN         	                      	   #
# **************************************************************************** #
DOXYGEN_FILE	= log/7.Doxygen/Doxygen
DOXYGEN_PATH 	= log/7.Doxygen
DOXYGEN_OUTPUT	= doc/doxygen
doxygen:
	rm -rf $(DOXYGEN_PATH)
	$(MAKE) create_Doxyfile
	$(MAKE) doxfile_mod
	doxygen ./$(DOXYGEN_FILE)
	xdg-open doc/doxygen/html/index.html


create_Doxyfile:
	mkdir -p log/7.Doxygen
	doxygen -g $(DOXYGEN_FILE)

doxfile_mod:
	sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "$(NAME)"/g' ./$(DOXYGEN_FILE)
	sed -i 's/PROJECT_BRIEF          = "My Project Brief"/PROJECT_BRIEF          = "$(NAME)"/g' ./$(DOXYGEN_FILE)
	sed -i 's/OUTPUT_DIRECTORY       =/OUTPUT_DIRECTORY       = doc\/doxygen/g' ./$(DOXYGEN_FILE)
	sed -i 's/OPTIMIZE_OUTPUT_FOR_C  = NO/OPTIMIZE_OUTPUT_FOR_C  = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/HIDE_SCOPE_NAMES       = NO/HIDE_SCOPE_NAMES       = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/INPUT                  =/INPUT                  = src/g' ./$(DOXYGEN_FILE)
	sed -i 's/RECURSIVE              = NO/RECURSIVE              = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/EXCLUDE                =/EXCLUDE                = src\/src_all/g' ./$(DOXYGEN_FILE)
	sed -i 's/GENERATE_LATEX         = NO/GENERATE_LATEX         = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/GENERATE_TREEVIEW      = NO/GENERATE_TREEVIEW      = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/GENERATE_MAN           = NO/GENERATE_MAN           = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/GENERATE_DOCBOOK       = NO/GENERATE_DOCBOOK       = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/CALL_GRAPH             = NO/CALL_GRAPH             = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/CALLER_GRAPH           = NO/CALLER_GRAPH           = YES/g' ./$(DOXYGEN_FILE)
	sed -i 's/TIMESTAMP              = NO/TIMESTAMP              = YES/g' ./$(DOXYGEN_FILE)
#	sed -i 's/STRIP_FROM_PATH        =/STRIP_FROM_PATH        = ..\/..\/..\//g' ./$(DOXYGEN_FILE)



.PHONY: doxygen create_Doxyfile


























# ************************************************************************ #
#                          TESTERS VISUALIZER                              #
# ************************************************************************ #
test_visualizer_build: testers/push_swap_visualizer/build/bin/visualizer

testers/push_swap_visualizer.tar.gz:
	pipx install gdown
	mkdir -p testers
	gdown 'https://drive.google.com/uc?id=1xvaDfFKfIPTeiwLLu0K37YzJdesab_kx' -O $@
#	file $@ | grep gzip > /dev/null
#	if [ $$? -ne 0 ]; then echo "Error: Downloaded file is not a gzip archive!"; exit 1; fi

testers/push_swap_visualizer: testers/push_swap_visualizer.tar.gz
		tar -xzf $< -C testers/

testers/push_swap_visualizer/build/bin/visualizer: testers/push_swap_visualizer

test_visualizer_run: testers/push_swap_visualizer/build/bin/visualizer
	./testers/push_swap_visualizer/build/bin/visualizer

.PHONY: run_visualizer













###  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  ###
# ############################################################################ #
#                                HELPER                                        #
# ############################################################################ #
# *** Hello message *** #
hello:
ifneq ($(VERBOSE), 0)
	@echo "$(GRAY)\n################################################$(RESET)"
	@echo "$(GRAY)# Hello, $(USER)! $(shell date)$(RESET)"
	@echo "$(GRAY)# Welcome to Makefile for:$(BLUE) $(NAME)!$(RESET)"
	@echo "$(GRAY)################################################$(RESET)"
	echo ""
endif

# *** Build message of timestamps changes *** #
check_up_to_date:
	echo 1 > log/outdate.txt
ifneq ($(VERBOSE), 0)
	if [ ! -f "$(NAME)" ]; then \
		echo "$(GRAY)\n# ############################################################################ #$(RESET)"; \
		echo "$(BLUE)$(NAME)$(RESET)					$(shell date)\n$(YELLOW)STATUS: Bin does not exist. Building...$(RESET)"; \
		echo "$(GRAY)# ############################################################################ #\n$(RESET)"; \
		echo 1 > log/outdate.txt; \
	else \
		if find -L src/ inc/ $(LIBS_PATH) -newer "$(NAME)" -print | grep -q .; then \
			echo "$(GRAY)\n# ############################################################################ #$(RESET)"; \
			echo "$(BLUE)$(NAME)$(RESET)					$(shell date)\n$(RED)STATUS: Some files have changed. Rebuilding...$(RESET)"; \
			echo "$(GRAY)# ############################################################################ #\n$(RESET)"; \
			echo 1 > log/outdate.txt; \
			make folders_ls_la; \
		else \
			echo "$(GRAY)\n# ############################################################################ #$(RESET)"; \
			echo "$(BLUE)$(NAME)$(RESET)					$(shell date)\n$(GREEN)STATUS: is up-to-date.$(RESET)"; \
			echo "$(GRAY)# ############################################################################ #\n$(RESET)"; \
			echo 0 > log/outdate.txt; \
			exit 0; \
		fi; \
	fi;
endif

check_up_to_date_2:
	if [ "$(shell cat log/outdate.txt)" -eq "1" ]; then \
		make check_up_to_date_21; \
	fi;

check_up_to_date_21:
ifneq ($(VERBOSE), 0)
	if [ ! -f "$(NAME)" ]; then \
		echo "$(GRAY)\n# ############################################################################ #$(RESET)"; \
		echo "$(BLUE)$(NAME)$(RESET)					$(shell date)\n$(YELLOW)STATUS: Bin does not exist. Building...$(RESET)"; \
		echo "$(GRAY)# ############################################################################ #\n$(RESET)"; \
		echo 1 > log/outdate.txt; \
	else \
		if find -L src/ inc/ $(LIBS_PATH) -newer "$(NAME)" -print | grep -q .; then \
			echo "$(GRAY)\n# ############################################################################ #$(RESET)"; \
			echo "$(BLUE)$(NAME)$(RESET)					$(shell date)\n$(RED)STATUS: Some files have changed. Rebuilding...$(RESET)"; \
			echo "$(GRAY)# ############################################################################ #\n$(RESET)"; \
			echo 1 > log/outdate.txt; \
		else \
			echo "$(GRAY)\n# ############################################################################ #$(RESET)"; \
			echo "$(BLUE)$(NAME)$(RESET)					$(shell date)\n$(GREEN)STATUS: is up-to-date.$(RESET)"; \
			echo "$(GRAY)# ############################################################################ #\n$(RESET)"; \
			echo 0 > log/outdate.txt; \
			exit 0; \
		fi; \
	fi;
endif

folders_ls_la:
ifneq ($(VERBOSE), 0)
	echo "$(GRAY)\n# ############################################################################ #$(RESET)"
	echo "$(YELLOW)Folders and Files:$(RESET)"
	echo "$(GRAY)# ############################################################################ #"
	ls -l | awk '{print $$6, $$7, $$8, $$NF}' | sort
	ls -l libs/ | awk '{print $$6, $$7, $$8, $$NF}' | sort
	ls -l libs/mylibs/mylibc | awk '{print $$6, $$7, $$8, $$NF}' | sort
	echo "# ############################################################################ #$(RESET)"
endif

# *** Build folders *** #
folders_lns_build:
	@echo "Running folder_lns_builder..."
	@if [ -d "src/src_all" ]; then \
		echo "Deleting existing src/src_all directory..."; \
		rm -rf "src/src_all"; \
	fi
	@echo "Creating src/src_all directory..."
	@mkdir -p "src/src_all"
	@echo "Creating symbolic links for .c files..."
	@(find src/ -mindepth 1 -maxdepth 5 -type f -name "*.c" ! -path "*/.*" -print0 | \
		xargs -0 -I {} sh -c 'filename=$$(basename "{}"); \
			echo "Creating symbolic link for {} in src/src_all/$$filename"; \
			ln -s "$$(realpath --relative-to=src/src_all "{}")" "src/src_all/$$filename" || echo "Error creating symbolic link for {}";')
	@echo "Generating list_files_c.txt..."
	@(cd src/src_all; \
		find . -name "*.c" -print0 | xargs -0  printf "%s\t\t\\ \n"  > ../../log/list_files_c.txt)
	@echo "folder_lns_builder completed successfully."

# *** help message *** #
help:
	@echo "$(GRAY)\n### 1.DESCRIPTION:$(RESET)"
	@echo "$(GREEN)	This is make file for build either PROGRAM, LIBRARY, PROGRAM+LIBRARY with their dependencies connect.$(RESET)"
	@echo "$(GREEN)	- This Makefile is a template for a project with the following structure:$(RESET)"
	@echo "$(GREEN)	1. Headers.h, files all them must be placed inside the folder 'include'.$(RESET)"
	@echo "$(GREEN)	2. Library.a, files all them must be inside of the folder 'libs'.$(RESET)"
	@echo "$(GREEN)	3. The library makefile must be inside of the folder 'libs/mylib'.$(RESET)"
	@echo "$(GRAY)	structure:$(RESET)"
	@echo "$(GREEN)my_project/$(RESET)"
	@echo "$(GREEN)├── include/$(RESET)"
	@echo "$(GREEN)│   ├── main.h$(RESET)"
	@echo "$(GREEN)│   └── mylib.h$(RESET)"
	@echo "$(GREEN)├── libs/$(RESET)"
	@echo "$(GREEN)│   ├── mylib/$(RESET)"
	@echo "$(GREEN)│   │   ├── src/$(RESET)"
	@echo "$(GREEN)│   │   │   └── mylib.c$(RESET)"
	@echo "$(GREEN)│   │   │── objs/$(RESET)"
	@echo "$(GREEN)│   │   │   └── mylib.o$(RESET)"
	@echo "$(GREEN)│   │   └── Makefile <-- (1) Sub-Makefile for the library$(RESET)"
	@echo "$(GREEN)│   └── libmylib.a <-- (2) Library file outside mylib directory$(RESET)"
	@echo "$(GREEN)├── objs/$(RESET)"
	@echo "$(GREEN)│   ├── main.o$(RESET)"
	@echo "$(GREEN)│   ├── main_utils.o$(RESET)"
	@echo "$(GREEN)│   ├── main_utils1.o$(RESET)"
	@echo "$(GREEN)│   └── main_utils2.o$(RESET)"
	@echo "$(GREEN)├── src/$(RESET)"
	@echo "$(GREEN)│   └── main.c$(RESET)"
	@echo "$(GREEN)│       ├── UtilsA/$(RESET)"
	@echo "$(GREEN)│       │   ├── main_utils.c$(RESET)"
	@echo "$(GREEN)│       │   └── main_utils1.c$(RESET)"
	@echo "$(GREEN)│       └── UtilsB/$(RESET)"
	@echo "$(GREEN)│          └── main_utils2.c$(RESET)"
	@echo "$(GREEN)└── Makefile$(RESET)"
	@echo "$(GRAY)\n### 2. USAGE:$(RESET)"
	@echo "$(GREEN)	make [option]$(RESET)"
	@echo "$(GRAY)\n### 3. OPTIONS:$(RESET)"
	@echo "$(GRAY) DEFAULT RULES:$(RESET)"
	@echo "$(GREEN)	1. all, clean, fclean, fclean_all, re$(RESET)"
	@echo "$(GRAY) FUNCTIONS BUILD:$(RESET)"
	@echo "$(GREEN)	2. program_or_lib, program, lib, libs_build $(RESET)"
	@echo "$(GREEN)	3. library_clean, library_fclean, library_re $(RESET)"
	@echo "$(GREEN)	4. hello, check_up_to_date, code_cleaner, files_lns_creator $(RESET)"
	@echo "$(GRAY) linting(static/Wflags):$(RESET)"
	@echo "$(GREEN)	5. linting: werror, norm_1, norm_2$(RESET)"
	@echo "$(GRAY) SANITIZATION(static/Asan) & RUNTIME ERROR(dynamic/Valgrind):$(RESET)"
	@echo "$(GREEN)	6. leaks: create_bins, valgrind, asan$(RESET)"
	@echo "$(GRAY) UNIT TESTS:$(RESET)"
	@echo "$(GREEN)	7. testing_alles: run_visualizer, time_and_perfomance$(RESET)"
	@echo "$(GRAY) DEBUGGERS:$(RESET)"
	@echo "$(GREEN)	8. make_dbg, libs_nm_art, debug, compile_debug_files$(RESET)"
	@echo "$(GRAY) HELPERS:$(RESET)"
	@echo "$(GREEN)	9. log_all, check_up_to_date, code_cleaner, folders_build, folder_lns_builder$(RESET)"
	@echo "$(GRAY) EXTRAS:$(RESET)"
	@echo "$(GREEN)	10. bonus\n$(RESET)"
	








#####OLD TRASH


# # ************************************************************************ #
# # *** Default rule *** #
# #.DEFAULT_GOAL:= build_dependencies

# # *** Default rule *** #
# build_dependencies:
# 	$(MAKE) libs_build
# 	$(MAKE) check_up_to_date

# # *** Build the library included (MAKEFLAGS="" this not inherit env variables from father*** #
# libs_build:
# ifeq ($(BUILD_LIBRARY), 1)
# 	$(MAKE) -C $(LIB_1_PATH) MAKEFLAGS=""
# #	@echo "$(YELLOW)(•̀ᴗ•́)و $@ Done!$(RESET)"
# else
# #	@echo "$(GRAY)Skipping library build$(RESET)"
# endif


# # ************************************************************************ #
# #                               MAIN                                       #
# # ************************************************************************ #
# # *** Default rule *** #
# build_project:
# 	$(MAKE) hello
# 	$(MAKE) folders_build
# #	$(MAKE) folders_lns_build
# 	$(MAKE) program_or_lib
# 	$(MAKE) dbg_rules

# # *** Compiling the source files into object files *** #
# #objs/%.o:	%.c
# #	mkdir -p objs
# #	$(COMPILER) $(PIC) $(CFLAGS_DBG) $(CFLAG_ASAN) $(CFLAGS_INCL) $(DEPFLAGS) $(MACROS) -c $< -o $@
# #	@echo "$(GRAY)()و $@ $(NAME) Compiling Objects !$(RESET)"

# # *** Is program or a Lib? ***
# program_or_lib:
# ifeq ($(IS_PROGRAM_AND_NOT_LIB), 1)
# 	echo "  $(YELLOW)Linking a Program$(RESET)"
# 	$(MAKE) LIB_OUTPUT="libs/lib$(NAME0).a" lib
# 	$(MAKE) program
# else
# 	echo "  $(YELLOW)Linking a Lib$(RESET)"
# 	$(MAKE) LIB_OUTPUT=$(NAME) lib
# endif

# # *** Linking the object files into a library *** #
# lib:	$(OBJECTS_LIB)
# 	$(LIB_LINK_STATIC) $(LIB_OUTPUT) $(OBJECTS_LIB)
# 	@echo "  $(YELLOW)(•̀ᴗ•́)و lib$(NAME).a Library Generated!$(RESET)"

# # *** Linking the object files into the program *** #
# program: $(OBJECTS)
# 	$(COMPILER) $(OBJECTS_MAIN) -Llibs -l$(NAME0) $(LDFLAGS) $(CFLAG_ASAN) -o $(NAME)
# 	@echo "  $(YELLOW)(•̀ᴗ•́)و $(NAME) Bin Generated!$(RESET)"
# 	$(MAKE) check_up_to_date


























# ************************************************************************ #
# ************************************************************************ #
#1. DESCRIPTION:
#	This is make file for build either PROGRAM, LIBRARY, PROGRAM+LIBRARY 
#		with their dependecies connect.
#
# - This Makefile is a template for a project with the following structure:
#	1. Headers.h, files all them must be placed inside the folder "include".
#	2. Library.a, files all them must be inside of the folder "libs"
#	3. The library makefile must be inside of the folder "libs/mylib"

#	structure:
#		my_project/
#		├── include/
#		│   ├── main.h
#		│   └── mylib.h
#		│
#		├── libs/
#		│   ├── mylib/
#		│   │   ├── src/
#		│   │   │   └── mylib.c
#		│   │   │── objs/
#		│   │   │   └── mylib.o
#		│   │   └── Makefile		<-- (1) Sub-Makefile for the library
#		│   └── libmylib.a			<-- (2) Library file outside mylib directory
#		│
#		├── objs/
#		│   ├── main.o
#		│   ├── main_utils.o
#		│   ├── main_utils1.o
#		│   └── main_utils2.o
#		│
#		├── src/
#		│   └── main.c
#		│       ├── UtilsA/
#		│       │   ├── main_utils.c
#		│       │   └── main_utils1.c
#		│       └── UtilsB/
#		│          └── main_utils2.c
#		│
#		└── Makefile
#
#2. USAGE:
#	make [option]
#
#3. OPTIONS:
#	- DEFAULT:
#		1. help, all, clean, fclean, fclean_all, re
#
#	- FUNCTIONS BUILD:
#		2. program_or_lib, program, lib, libs_build, folders_build
#
#	- linting(static/Wflags) & SANITIZATION(static/Asan) & RUNTIME ERROR(dynamic/Valgrind) & UNIT_TESTING :
#		3. log_all: norm_1, norm_2, leaks: valgrind, asan
#		4. test, test5
#
#	- DEBUGGERS:
#		5. debug, compile_debug_files, make_dbg, create_bins
#
#	- HELPERS:
#		6. hello, check_up_to_date, code_cleaner, files_lns_creator
#		7. library_clean, library_fclean, library_re
#
#	- EXTRA:
#		8. bonus