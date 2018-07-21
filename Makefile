#
# pseultra/Makefile
# Project makefile
# 
# (C) pseudophpt 2018
#

MAKE = make

# Make all tools
all: 
	$(MAKE) -C boot
	$(MAKE) -C bootcsum
