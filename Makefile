############################## COMPILE VAR #####################################

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		=	-g
HDIR		=	includes
SRCDIR		=	src
SUB1D		=	libft
HFLAGS		=	-I $(HDIR) -I $(SUB1D)/$(HDIR)
LIBS		=	$(SUB1D)/libft.a
NAME		=	lem-in

############################## SOURCES #########################################

OPTIONSDIR		=	options
PARSERDIR		=	parser
PRINTDIR		=	print
SOLVERDIR		=	solver

SRCC			=	main.c\

OPTIONSC		=	explain.c\
					help.c\
					lemin_options.c\

PARSERC			=	lemin_parser.c\

PRINTC			=	print_lemin.c\

SOLVERC			=	bfs.c\
					fix_overlap.c\
					lemin_path.c\
					lemin_solver.c\
					solution.c\
					test_solution.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(OPTIONSC))\
					$(patsubst %.c,%.o,$(PARSERC))\
					$(patsubst %.c,%.o,$(PRINTC))\
					$(patsubst %.c,%.o,$(SOLVERC))\
					$(patsubst %.c,%.o,$(SRCC))\

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.h	$(SUB1D)/$(HDIR)
vpath			%.c	$(SRCDIR)/$(OPTIONSDIR)
vpath			%.c	$(SRCDIR)/$(PARSERDIR)
vpath			%.c	$(SRCDIR)/$(PRINTDIR)
vpath			%.c	$(SRCDIR)/$(SOLVERDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(SUB1D)/libft.a $(ODIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ)) $(LIBS)

$(SUB1D)/libft.a:
	make -C $(SUB1D)

main.o: lemin_options.h t_lemindata.h t_vertex.h t_leminpath.h libft.h\
	lemin_parser.h lemin_solver.h print_lemin.h
explain.o: lemin_options.h t_lemindata.h t_vertex.h t_leminpath.h libft.h
help.o: lemin_options.h t_lemindata.h t_vertex.h t_leminpath.h libft.h
lemin_options.o: lemin_options.h t_lemindata.h t_vertex.h t_leminpath.h\
	libft.h
lemin_parser.o: t_lemindata.h t_vertex.h t_leminpath.h libft.h
print_lemin.o: lemin_options.h t_lemindata.h t_vertex.h t_leminpath.h libft.h\
	print_lemin.h
bfs.o: bfs.h t_lemindata.h t_vertex.h t_leminpath.h libft.h lemin_path.h
fix_overlap.o: bfs.h t_lemindata.h t_vertex.h t_leminpath.h libft.h solution.h\
	lemin_path.h lemin_options.h
lemin_path.o: t_lemindata.h t_vertex.h t_leminpath.h libft.h
lemin_solver.o: lemin_path.h t_lemindata.h t_vertex.h t_leminpath.h libft.h\
	solution.h bfs.h fix_overlap.h lemin_options.h
solution.o: lemin_path.h t_lemindata.h t_vertex.h t_leminpath.h libft.h
test_solution.o: lemin_path.h t_lemindata.h t_vertex.h t_leminpath.h libft.h
%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -c $(CFLAGS) $< $(HFLAGS) -o $(ODIR)/$@

$(ODIR):
	mkdir -p $@

############################## CLEANUP #########################################

clean:
	rm -rf $(ODIR)
	make -C $(SUB1D) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
