SHELL := /bin/bash

.SECONDARY:
# prevents deletion of intermediate targets in chained rules

.DELETE_ON_ERROR:
# delete targets if a rule fails


C := $(wildcard *.c)
MD := $(patsubst %.c,%.md,$(C))

all:  $(MD)


%.md: %.c
	echo -e "---\ntitle: Program $<\n---\n" > $@
	echo -e "[Súbor na stiahnutie](./$<)\n" >> $@
	echo '```c' >> $@
	cat $< >> $@
	echo '```' >> $@
