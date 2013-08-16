# OpenGL ES 2.0 Simulator # {#mainpage}

[TOC]

Intorduction {#introduction}
============
This project's main purpose is for simulating a real hardware on OpenGL ES 2.0.
This includes a full OpenGL environment letting *Custom Hardware* simulator can 
run on it. So, the OpenGL ES 2.0 environment's performance is not what I really
care about but hardware does. You can see the whole driver part is making no
sense and should be re written with better method. If I have time, I may do
that. But for now, I should focus on the hardware itself rather than other part
which is working fine.

* * *

Compile Requirement {#compile_required}
===================
- GCC: 4.6.4 or above with c++11(c++0x) support
  + [MinGW-builds](http://sourceforge.net/projects/mingwbuilds/) (Windows)
	
	Using mingw-gcc 4.8.1 should be no problem.
	
  + With Code::Blocks built-in mingw-gcc 4.6.4 (Windows)
  
    There is a bug caused by Mingw-gcc 4.6.4-4.7.2 on Windows. Please see the
    [issue section](#known_issue) for the solution by patching or updating 
    Mingw-gcc.
	
  + On most Linux distribution, Update to gcc 4.6.4 or above should be a piece 
    of cake :)

	If you are using RedHat or CentOS, please do what this [page]
	(http://people.centos.org/tru/devtools-1.1/readme) say to add the updated
	gcc into the independent environment.
  
  
- [Nvidia Cg Toolkits](https://developer.nvidia.com/cg-toolkit-download)
  (Both Windows and Linux)
  
  Current version uses cg compiler as its glsl compiler. Lack of this compiler
  will cause glCompilerShader malfunction, although you can use glShaderBinary
  to avoid it.
	
	
- [Code::Blocks](http://www.codeblocks.org/downloads) (Both Windows and 
  Linux)
	
  The whole project is managed by this IDE, but you can still use custom 
  Makefile or use cbp2make converting .cbp to Makefile
  
  
- Flex & bison
  + Use MSYS (Windows, recommend)
  + [win flex-bison](http://sourceforge.net/projects/winflexbison/) (Windows)
  + These tools on Linux are built-in. :)

  The assembly grammar and token is defined in .y and .l file and need Flex & 
  bison to generate C code for compiling. Although these generated C code
  already attached within the project and you can compiled them with no problem,
  you still need these tool if you want to adjust the grammar.

* * *
  
How to get this project {#how_to_get_this_project}
=======================

Use this git command if you dont have an account on my git server.

	git clone git://140.116.164.239/ogles1_1.git
	
Or this if you do have one
	
	git clone git@140.116.164.239:ogles1_1
	
You can use any git client to execute the above commands. If on Windows, go
checking [MsysGit](http://msysgit.github.io/), [TortoiseGit]
(https://code.google.com/p/tortoisegit/), or even Msys/Cygwin system with git
command.

You can also directly go to [my git server]
(http://140.116.164.239/~git/?p=ogles1_1.git;a=summary) 
and click the "snapshot" on the master branch to download whole project within
the tgz file. This page also allows anyone to trace the the project's current
progress.

* * *

How to Compile this project {#how_to_compile_this_project}
===========================

- Use Code::Blocks
  
  Direcly open ogles1_1.cbp(for Winddows) or ogles1_1_linux.cbp(for Linux) in 
  codeblocks and push F9 (compile). If you have right gcc version or pathced 
  mingw-gcc and correct toolchain setting in codeblocks compiler setting page,
  there shall be no problem.

- Makefile

  If you prefer to use unix build system, cbp2make will do you a favor but you
  need to compile this tool from source. You can get its source from [here]
  (http://sourceforge.net/projects/cbp2make/)
	
  Once you get cbp2make's binary, use this command to generate Makefile if you 
  are under Windows.
  
		cbp2make -in ogles1_1.cbp -out Makefile

  or this command if you are using linux.

		cbp2make -in ogles1_1_linux.cbp -out Makefile

  You still need to check you compiler's version if you encounter any standard
  library's problem.

Besides, there is a single, independent Makefile under 'src' directory which is
used to generated assembler's C code from .y and .l file. You can use it after
the .l and .y file are modified. ( However, this operation needs make tool and
flex/bison. If on windows, the most convenient way I know is to use msys/cygwin
system to make this Makefile )

* * *

Major File Association {#basic_file_association}
======================
The main.cpp and other file in the same level with main.cpp plus the file
in /external are used for OpenGL Application only, not the part of my 
simulation. If there are any licence issue in it, it shouldn't have business
with me. If I have time in the future, this project should be compiled into
library and has no relationship with these files.

\dot
digraph {
	node [ fontname=arial, fontsize=11, shape=record ];
	edge [ color=blue ];
	"main.cpp" [URL="\ref main.cpp"];
	"gl3.h" [URL="\ref gl3.h", 
			 shape=ellipse];
	"gl3.cpp" [URL="\ref gl3.cpp"]
	"context.h" [URL="\ref context.h",
				 shape=ellipse];
	"context.cpp" [URL="\ref context.cpp"]
	context_glapi [label="{context_glapi.cpp|{DrawArray()}}", 
				   URL="\ref Context::DrawArrays()"];
	"context_shader_glapi.cpp" [URL="\ref context_shader_glapi.cpp"]
	"context_link.cpp" [URL="\ref context_link.cpp"];
	driver [label="{driver.cpp|{ActiveGPU()}}", 
			URL="\ref ActiveGPU()"];
	"driver.h" [URL="\ref driver.h",
				shape=ellipse];
	"gpu_core.h" [URL="\ref gpu_core.h",
				  shape=ellipse];
	"gpu_core.cpp" [URL="\ref gpu_core.cpp"];
	"shader_core.h" [URL="\ref shader_core.h",
					 shape=ellipse];
	"shader_core.cpp" [URL="\ref shader_core.cpp"];
	"geometry.cpp" [URL="\ref geometry.cpp"];
	"rasterizer.cpp" [URL="\ref rasterizer.cpp"];
	"texture_unit.h" [URL="\ref texture_unit.h",
					  shape=ellipse];
	"texture_unit.cpp" [URL="\ref texture_unit.cpp"];
	
	"main.cpp" -> {"gl3.h" "gl3.cpp"};
	"gl3.cpp" -> {"context.h" "context.cpp" context_glapi
				 "context_shader_glapi.cpp" "context_link.cpp"};
	"context_link.cpp" -> {"nvgp4info.l" "nvgp4info.y" 
						   "nvgp4ASM.l" "nvgp4ASM.y"};
	context_glapi -> {driver "driver.h"};
	driver -> {"gpu_core.h" "gpu_core.cpp"};
	"gpu_core.cpp" -> {"shader_core.h" "shader_core.cpp" 
					   "geometry.cpp" "rasterizer.cpp"};
	"shader_core.cpp" -> {"texture_unit.h" "texture_unit.cpp"};
					
}
\enddot

* * *

Known Issue {#known_issue}
===========

- While compile the code on windows, the compile error **std::to_string is not
  a member of std** is jumped out.
	
  This is a known bug for mingw-gcc from 4.6.4 to 4.7.2. You can update your 
  Mingw-gcc by [MinGW-builds](http://sourceforge.net/projects/mingwbuilds/files/).
  After you installed newer Mingw-gcc, make sure you have alredy change the
  codeblocks compiler toolchain setting before compile the code.
  
  Their is another way to solve it by patching your Mingw-gcc from this [site]
  (http://tehsausage.com/mingw-to-string). You may find your Mingw-gcc under
  `C:\Program Files (x86)\CodeBlocks\MinGW` (If you use the codeblocks' bundled 
  gcc) or `C:\MinGW` . Follow the step on the web site with no additional work 
  should fix this problem.

* * *

Cause this project is still under development, any unexpected situation is 
possible. Please email or report to me if you find any compiler error or bug.

	
Liou Jhe-Yu <br>
lioujheyu@gmail.com <br>
National Cheng-kung University, EE Department, <br>
[Computer Architecture and System Laboratory]
(http://caslab.ee.ncku.edu.tw/index.html) <br>
Tainan, Taiwan <br>
2013/6/30 <br>
2013/8/16 1st update
