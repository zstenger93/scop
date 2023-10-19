<h1 align="center">📖 42 SCOP</h1>

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/nutshell.jpeg">

<h2 align="center">Rendering engine with OpenGL for object files</h2>

## Menu

[How it Looks](#how-it-looks)

[Setup](#setup)

[Object Files](#object-files)

[.mtl Files](#.mtl-files)

[Input Handling](#input-handling)

[Creating Triangle](#creating-triangles)

[Color](#color)

[UV Coordinates](#uv-coordinates)

[UV Normalizing](#uv-normalizing)

[Normals](#normals)

[Keys](#keys)

[Resources](#resources)

## How it Looks

Teapot with uv map texture

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/teapot.png">

Object which for I created the .obj file manually (yes I like the pain)

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/hb.png">

With wireframe

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/hb_w.png">

An alien animal with colorful texture

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/alienanimal.png">

With basic light on

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/alien_light_on.png">

Polygon mode POINTS

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/alien.png">

Skull with it's texture on

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/skull.png">

Polygon mode WIREFRAME

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/skull_wire.png">

A cool result with messed up uv mapping

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/skull1.png">

Just because it looks cool

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/skull_color.png">

Camel with it's texture

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/camel.png">

Polygon mode WIREFRAME

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/camel_wire.png">

42 logo with wireframe

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/42.png">

For Star Wars fans

<img align=center src="https://github.com/zstenger93/scop/blob/master/readme_src/sw.png">

## Setup

Have at least OpenGL 3 or above or leave the page now and run for the sake of your sanity.

You will also need:
```
	- stb_image.h
	- GLFW
	- Specific GLAD headers based on OpenGL version
	- GLM
```

## Object Files

It's possible to have different layouts, not all the values are necessary.

Faces can be stored different ways like

```
f 4 9 7 1
```

or

```
f 23/123/123 321/3213/213 43/45/12 423/3423/432
```

## .mtl Files

Values for material and lighting calculations

## Input Handling

Make yourself a favor, plan and save all the values in a structured way, then start playing with them

## Creating Triangles

One face contains 3 or 4 indexes and each of them marks the index of an x, y and z coordinate for one point of a triangle or square. Combining these coordinates from a face will result one triangle or square.

## Color

you can use normal colors, or the uv coordinates

## UV Coordinates

Usually provided in the .obj file as well

## UV Normalizing

In case you don't have them, you need to calculate it yourself

## Normals

Normals are used for lighting calculations

## Keys

```
Handling keypress events as:
		Camera movement:
			W:		move camera forward
			A:		move camera left
			S:		move camera backwards
			D:		move camera right
			X:		move camera down
			SPACE:		move camera up
			8:		incrase camera movement speed
			9:		decrase camera movement speed
		Object Rotation:
			I:		rotates the object left on X axis
			K:		rotates the object right on X axis
			J:		rotates the object left on Y axis
			L:		rotates the object right on Y axis
			U:		rotates the object left on Z axis
			O:		rotates the object right on Z axis
			M:		incrases the speed
			N:		reduces the speed
		Polygon Mode:
			1: 		wireframe
			2:		points
			3:		filled
		Switching beteewen texture and color:
			Z:		basic lighting on
			C:		color mode
				4:	changing the value of R
				5:	changing the value of G
				6:	changing the value of B
			V:		texture mode
			B:		texture versions
						-texture
						-color
						-mixture between texture and color
```

## Resources

Can't get any better than the videos and explanations from this site

https://learnopengl.com/Introduction