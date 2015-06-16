#Screenshot
###Description
这个项目是通过将图片显示，然后利用鼠标进行框图，并将选中框内的图片部分保存下来。
该项目用于在一张图片上选择手写数字检测的正负样本。

###Dependence
	
	cmake version = 3.0
	g++ version >= 4.1
	opencv version >= 2.4.9

###Run
首先将要处理的图片放到 `image` 文件夹，然后在 `run` 文件夹下运行如下命令：

	$bash run.sh

这是会显示一个图片窗口，通过鼠标按住左键选择图片框，然后松开左键，这样即得到一张选中图。可以持续选择。选中的图片保存在 `subImage` 文件夹下。

通过按向下(up)和向上(down)键来选择图片。

>
注意：在同一次运行的程序中选中的图片在保存时不会覆盖其他图片，但是后一次运行的程序会对前一次运行的结果进行覆盖。

###Author
	
	E-mail: xiezhw3@163.com
	Github: www.github.com/xiezhw3

 