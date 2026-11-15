SHELL := /bin/bash

.SECONDARY:
# prevents deletion of intermediate targets in chained rules

.DELETE_ON_ERROR:
# delete targets if a rule fails


C := $(wildcard *.c)
CPP := $(wildcard *.cpp)
MD := $(patsubst %.cpp,%.md,$(CPP)) $(patsubst %.c,%.md,$(C))

all:  $(MD)


%.md: %.c
	echo -e "---\ntitle: Program $<\n---\n" > $@
	echo -e "[Súbor na stiahnutie](./$<)\n" >> $@
	echo '```c' >> $@
	cat $< >> $@
	echo '```' >> $@


%.md: %.cpp
	echo -e "---\ntitle: Program $<\n---\n" > $@
	echo -e "[Súbor na stiahnutie](./$<)\n" >> $@
	echo '```cpp' >> $@
	cat $< >> $@
	echo '```' >> $@
