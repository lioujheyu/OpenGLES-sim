all:
	bison --name-prefix=context_link_ -d context_link.y
	flex -o context_link.cpp context_link.l

clean:
	rm context_link.cpp context_link.tab.c -f
