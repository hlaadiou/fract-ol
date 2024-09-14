# Fractol - Dive into the World of Fractals

**Fractol** is an interactive fractal visualization program that allows you to explore the intricate patterns of the **Mandelbrot** and **Julia** sets. Written in C and using **MinilibX** for graphical rendering, Fractol lets you experience the beauty of fractals with simple commands.

## Features
- **Mandelbrot Set**: Render the iconic Mandelbrot fractal.
- **Julia Set**: Customize and render the Julia fractal with user-defined parameters.
- Real-time zoom and color manipulation for an enhanced exploration experience.

## How to Run

### 1. Render the Mandelbrot Set:
To generate and view the Mandelbrot fractal, run:
```
./fractol mandelbrot
```
### 2. Render the Julia Set:
To render the Julia fractal, you must provide the real and imaginary parts as arguments:
```
./fractol julia <real_part> <imaginary_part>
```
Example:
```
./fractol julia -0.7 0.27015
```

## Controls

Once the fractal is rendered, you can interact with it using the following controls:

**Arrow Keys**: Move around the fractal (navigate up, down, left, right).
**Enter**: Change the color scheme.
**Page Up / Page Down**: Increase or decrease the number of iterations to render more or less detail in real time.
**Scroll Wheel**: Zoom in and out of the fractal.

## Dependencies

**MinilibX**: A lightweight graphics library used for rendering.
**Make**: Required for compiling the project.
