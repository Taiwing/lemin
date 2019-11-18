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

PARSERDIR		=	parser
SOLVERDIR		=	solver

SRCC			=	lemin_options.c\
					main.c\
					print_help.c\

PARSERC			=	lemin_parser.c\

SOLVERC			=	lemin_path.c\
					lemin_solver.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(PARSERC))\
					$(patsubst %.c,%.o,$(SOLVERC))\
					$(patsubst %.c,%.o,$(SRCC))\

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.h	$(SUB1D)/$(HDIR)
vpath			%.c	$(SRCDIR)/$(PARSERDIR)
vpath			%.c	$(SRCDIR)/$(SOLVERDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(SUB1D)/libft.a $(ODIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ)) $(LIBS)

$(SUB1D)/libft.a:
	make -C $(SUB1D)

lemin_options.o: lemin_options.h t_lemindata.h t_vertex.h t_leminpath.h\
	libft.h
main.o: lemin_options.h t_lemindata.h t_vertex.h t_leminpath.h libft.h\
	print_help.h lemin_parser.h lemin_solver.h
lemin_parser.o: t_lemindata.h t_vertex.h t_leminpath.h libft.h
print_help.o: lemin_options.h t_lemindata.h t_vertex.h t_leminpath.h libft.h
lemin_path.o: t_lemindata.h t_vertex.h t_leminpath.h libft.h
lemin_solver.o: lemin_path.h t_lemindata.h t_vertex.h t_leminpath.h libft.h
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
