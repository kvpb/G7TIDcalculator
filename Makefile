#!/usr/bin/make -f

SHELL = /bin/sh
# If we inherit the SHELL variable from the environment. https://www.gnu.org/software/make/manual/make.html#Makefile-Basics

.SUFFIXES:
.SUFFIXES: .c .h .o
# Clear out the suffix list, and introduce suffixes subject to implicit rules. https://www.gnu.org/software/make/manual/make.html#Makefile-Basics

#	V A R I A B L E S   F O R   S P E C I F Y I N G   C O M M A N D S 
#	                                    variables for specifying commands
#	https://www.gnu.org/software/make/manual/make.html#Command-Variables

#YACC = bison -y
# parser generator, thicc in '85 already.

#MKDIR = mkdir
# MKDIR

#RM = rm
# RM

#RMDIR = rmdir
# RMDIR

CC = gcc
# compiler
CLIBS = 
# compiler libraries
CINCLUDE = include
CFLAGS = -I$(CINCLUDE) -Wall -Wextra -Werror
# compiler options:
#	-Wall	'Enable all warnings about constructions that some users consider questionable and that are easy to avoid (or modify to prevent the warning) even in conjunction with macros. Also enable some language-specific warnings described in C++ Dialect Options and Objective-C and Objective-C++ Dialect Options.'
#	-Wextra	'Enable some extra warning flags that are not enabled by -Wall.'
#	-Werror	'Make all warnings into errors.'
LDFLAGS = #-Llib
LDLIBS = -lm
# linker options:
#	-lm		(As the standard C library does not include the math library, link with the math library.) 'Search the library named _m_ when linking. (The second alternative with the library as a separate argument is only for POSIX compliance and is not recommended.)'

INSTALL = /usr/bin/install -c#/usr/local/bin/install -c
INSTALL_PROGRAM = $(INSTALL)
# installer
INSTALL_DATA = ${INSTALL} -m 644

#	V A R I A B L E S   F O R   I N S T A L L A T I O N   D I R E C T O R I E S 
#	                                         variables for installation directories
#	https://www.gnu.org/prep/standards/html_node/Directory-Variables.html#Directory-Variables
#	https://www.gnu.org/software/make/manual/make.html#Prerequisite-Types

#DESTDIR = ./tmp/stage
# 'The DESTDIR variable is specified by the user on the make command line as an absolute file name.  For example: ```make DESTDIR=/tmp/stage install```  DESTDIR should be supported only in the install* and uninstall* targets, as those are the only targets where it is useful.  [...]  You should not set the value of DESTDIR in your Makefile at all; then the files are installed into their expected locations by default.' https://www.gnu.org/software/make/manual/make.html#DESTDIR

srcdir = src#@srcdir@ # source directory https://www.gnu.org/software/make/manual/make.html#Complex-Makefile https://doc.rust-lang.org/cargo/guide/project-layout.html # If I truly sticked to how the authors of the original BSD TAR from january 1979 and Cargo do it, I would forgo main.c and have src/bin/.
objdir := obj
prefix = /usr/local#$${HOME} # executable directory pathname prefix (parent directory)
datarootdir = $(prefix)/share
datadir = $(datarootdir)
exec_prefix = $(prefix)
bindir = bin#$(srcdir)/../bin#$(exec_prefix)/bin # executable directory path
libexecdir = $(exec_prefix)/libexec
infodir = $(datarootdir)/info

#	R U L E S   &   P H O N Y   T A R G E T S
#	                        rules & phony targets
#	https://www.gnu.org/software/make/manual/make.html#Standard-Targets
#	https://www.gnu.org/software/make/manual/make.html#Install-Command-Categories
#	https://www.gnu.org/software/make/manual/make.html#Automatic-Prerequisites

OBJ = $(SRC:$(srcdir)/%.c=$(objdir)/%.o)
SRC = $(wildcard $(srcdir)/*.c)
BIN = $(bindir)/cg7tid

.PHONY: all clean
all: $(BIN)

$(objdir) $(bindir):
	mkdir -pv -m 0755 $@

$(objdir)/%.o: $(srcdir)/%.c | $(objdir)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ) | $(bindir)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
#$(TARGET_EXECUTABLE): $(FILES_OBJECT)
#	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(FILES_OBJECT) $(CLIBS)
#$(TARGET) : $(OBJECTS)
#	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
#[ -e ./bin ] && rm bin; gcc -o bin src.c && ./bin; rm bin;

#.PHONY: install
#install: all
#	$(INSTALL_PROGRAM) $(BIN) $(DESTDIR)$(bindir)/$(BIN)

.PHONY: uninstall
uninstall:
	rm -v $(BIN)
#	rm -v $(DESTDIR)$(bindir)/$(BIN)

.PHONY: clean
clean:
	@rm -rv $(bindir) $(objdir)
#	@rm -v $(DESTDIR)$(bindir)/$(BIN) $(objdir)/$(OBJ)
#	@rm -f $(TARGET) $(OBJECTS) core

-include $(OBJ:.o=.d)

#	Makefile
#	CG7TID (G7TID Calculator)
#
#	Karl V. P. B. `kvpb`	AKA Karl Thomas George West `ktgw`
#	+33 A BB BB BB BB		+1 (DDD) DDD-DDDD
#	local-part@domain
#	https://x.com/ktgwkvpb
#	https://github.com/kvpb

#	Copyright 2022 Karl Vincent Pierre Bertin
#
#	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
#	1.	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#
#	2.	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#
#	3.	Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
#
#	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, BINMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
