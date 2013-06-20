all:
	bison --name-prefix=nvgp4Info_ -d nvgp4Info.y
	flex -o nvgp4Info.cpp nvgp4Info.l
	bison --name-prefix=nvgp4ASM_ -d nvgp4ASM.y
	flex -o nvgp4ASM.cpp nvgp4ASM.l

clean:
	rm nvgp4ASM.cpp nvgp4ASM.tab.c nvgp4ASM.tab.h -f
	rm nvgp4Info.cpp nvgp4Info.tab.c nvgp4Info.tab.h -f
