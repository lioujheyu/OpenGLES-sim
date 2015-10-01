# OpenGL ES 2.0 Simulator # 

![POM with self shadow](/gallery/FourShape1_POM_w_self_shadow.jpg)

Intorduction 
============
This project's main purpose is for simulating a GPU hardware on OpenGL ES 2.0.
It's also my personal OpenGL ES playing and learning ground :).

The project includes a full OpenGL environment letting *Custom Hardware* simulator can run on it. Cause it's a hardware simultor, the OpenGL API environment's performance is not what I really care about but hardware does. You can see the whole driver part is making no sense and should be rewritten with better method if I have time. But for now, I should focus on the hardware itself rather than other part which is working fine. 

The GPU simulator includes a kind of unified shader based on the [NVGP4 instruction set](http://developer.download.nvidia.com/opengl/specs/GL_NV_gpu_program4.txt) along with a texture unit whihc has 2D-map, cubemapping, and isometric, anisotrpic filter surppoted. It also has a serious fixed hardware like primitive assembly, Z-Near only clipping, culling, rasterier using tile-hierarachy-recursive structure, interpolation using barycentric method, depth test, and etc....

* * *

The detail document can be found [here](http://caslab.ee.ncku.edu.tw/~elvis/ogles-sim/)

Cause this project is still under development, any unexpected situation is possible. Please email or report to me if you find any compiler error or bug.

	
Liou Jhe-Yu <br>
lioujheyu@gmail.com <br>
National Cheng-kung University, EE Department, <br>
[Computer Architecture and System Laboratory](http://caslab.ee.ncku.edu.tw/index.html) <br>
Tainan, Taiwan <br>
2013/9/25
