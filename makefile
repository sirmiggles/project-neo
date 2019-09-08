#	Makefile for CITS3402 - High Performance Computing's Project I		\
	Project:		Matrix Operations									\
	Author:			Miguel Aries Sambat Tabadero (22240204)				\
	Version:		0.0.1												\
	Last Edited:	08/9/2019

#	*IMPORTANT*                                                         \
	DO NOT REMOVE, MOVE, OR ALTER THIS MAKEFILE FROM THE ROOT FOLDER

#	Changelog:															\
	08/9/2019	-	Added dynamic variable makefile

#	Compiler information and compile flags (cc for MacOS, gcc for Linux)
CC    = gcc
FLAGS = -fopenmp -Wall -Werror -pedantic

#	Target for compilation
TARG     = matrix

OBJDIR   = obj
SRCDIR   = src
SRCFILES = $(wildcard $(SRCDIR)/*.c)
HEADERS  = $(wildcard $(SRCDIR)/*.h)

#	Target object files (.o)
OBJS     = $(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(TARG): $(OBJS)
	$(CC) $(FLAGS) -o $(TARG) $(OBJS)
	@echo "Successfully compiled " $<

$(OBJS) : $(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
