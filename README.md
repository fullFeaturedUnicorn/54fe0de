Very basic 3D renderer written in C99 for educational purposes.

![](/visualization.png)

This picture existed in 3D space and was rendered using presented engine. You can grab appropriate model [here](/models/visualization.pepe).

### Dependencies

Any POSIX-compatible system, glibc (AFAIK, strsep is glibc-specific function, besides that, it's portable (or at least it's relatively easy to make it so)).

### Compiling

```
git clone /thisrepo/
make
```

To run tests:

```
make tests
```

To clear temporary files, rendered images and compiled binaries:

```
make clean
```

### Usage

```
bin/main -f model -o out.pgm
```

### Model

Model is a plain text file with configuration fields and then, in a last section, one per line, bunch of polygons to render manually specified in order. Here is a typical model file:

```
CAMERA
[[100,50,75]]
CANVAS
[[0,0,0][0,100,0][0,100,150][0,150,100]]
BACKGROUND
15
COLOR
8
EDGES
2
SCALING
5
MODEL
[[200,50,75]]
[[200,30,20][300,90,50]]
// this is comment
[[200,60,75][300,85,90][400,92,50]]
…
```

**CAMERA** -- Position of camera "lens".

**CANVAS** -- 4-vertex polygon (rectangle), basically a "screen" for projection.

**BACKGROUND** -- default background for output image. Pretty straighforward.

**COLOR** -- default color to fill rendered polygons with. It can be either specified manually via polygon declaration, or calculated automatically based on light source position, but in case of lack of information from both possible sources, this value vill be picked up.

**EDGES** -- specify how to render "skeleton" of the model, basically to draw edges of said polygons, or not. 0 -- do not draw any edges, 1 -- draw edges and fill polygons with their corresponding color, 2 -- draw only edges, ignore "body". Edges are always have color 0 (black).

**SCALING** -- surely, it is possible to manually set canvas size to a size of display it will be viewed on. But we all have different display resolutions, and there's more to come with 4K/8K/whatever, so it's dumb to tie anything to a fixed canvas size. Moreover, it's easier to operate with smaller numbers when it comes to coordinates of something in 3D space. The solution is to render everything on a small canvas with size, like, 150x100, and then scale result to appropriate size afterwards. 

The problem is, rendering accuracy will not be invreased with such dumb image upscaling. That's why I calculate position of some point projected to a smaller canvas as a floating point number, then multiply canvas size, as well as 2D coordinates of projection to a scaling factor, and then pick closest integer representation of said 2D coordinate. This way accuracy will be increased with scaling factor growth almost infinitely. Very cool.

### Thought process

It took reasonable amount of headache to come up with this. For historic purposes, I saved whatever was helpful to my brain. 

[Link](/assets/kdscmlacmlsd.png).

### Known wtf's

1. It is unbelievably hard to implement all possible kinds of intersections between all possible polygons as well as to find out whether particlular polygon is visible to a camera, so I use a dirty trick. Polygons are sorted in advance, and rendered in order from the farthest to closest from viewer's prospective. There's some exceptional cases when this approach is not applicable, but in most cases, the output should look just fine.

2. If projection of one point in line exceeds canvas size, the line will not be rendered at all. It's ridiculously easy to fix if we just assume we will not move the camera, and some other conditions, but making "overflowing" lines work reliably in every possible case, including negative position values and stuff, required some more pondering with pencil and a piece of paper, so I just left it this way intentionally atm. Maybe will return to it later (not really likely, because world aren't short on full-fledged 3D endines where all this problems are already solved).

### Code style

Tried to follow [Linux kernel's internal guidelines](https://www.kernel.org/doc/html/v4.10/process/coding-style.html) as much as I can. But failed, obviously.

### License

GPLv3+
