# Computer-Graphics
# Menu-Driven Computer Graphics Project in Turbo C++

## Project Description

This is a **menu-driven computer graphics project** developed in **Turbo C++** using the `graphics.h` library.  
The project allows the user to draw basic 2D shapes such as **lines, circles, ellipses, rectangles, and triangles** using **classic graphics algorithms**.

The program demonstrates:
- **DDA Line Drawing Algorithm**
- **Bresenham Line Drawing Algorithm**
- **Midpoint Circle Algorithm**
- **Bresenham Circle Algorithm**
- **Midpoint Ellipse Algorithm**
- Simple drawing for **Rectangle** and **Triangle**

It is **interactive**, menu-driven, and designed for **educational purposes**, suitable for **learning computer graphics concepts**.

---

## Features

1. **Console-based menu** with options to choose different shapes.  
2. **Submenus for line and circle algorithms**:  
   - Line: DDA or Bresenham  
   - Circle: Midpoint or Bresenham  
3. **Graphics window** displays the shapes clearly.  
4. **Message “Press any key to continue”** is displayed at the **bottom of the graphics window**, so it does not cover the drawing.  
5. **Clean console menu** that does **not scroll downward** after each operation.  
6. Works perfectly with **Turbo C++ 3.2 DOS environment**.  

---

## Requirements

- Turbo C++ (DOS version 3.0 or 3.2)  
- Windows PC or DOSBox emulator for running Turbo C++  
- Basic knowledge of console navigation and graphics algorithms  

---

## Installation / Setup

1. Download and install **Turbo C++** on your system or use **DOSBox**.  
2. Copy the source file `graphics_menu.cpp` into your **Turbo C++ project folder**.  
3. Make sure your **BGI folder** path is correctly set in `initgraph()`:
   ```cpp
   initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

4. Replace `C:\\TURBOC3\\BGI` in your code with the path where the **BGI folder** is located on your system.
5. Open the `.cpp` file in **Turbo C++**.
6. Compile the program using **Alt + F9**.
7. Run the program using **Ctrl + F9**.

---

## Usage

Run the program. A menu will appear in the console:

==== COMPUTER GRAPHICS MENU ====
1. Line Drawing
2. Circle Drawing
3. Ellipse Drawing
4. Rectangle Drawing
5. Triangle Drawing
6. Exit
Enter your choice:

## Sample Inputs for Testing
## Line Drawing

Submenu choice: 1 → DDA, 2 → Bresenham

Input coordinates:

x1 y1: 100 100
x2 y2: 300 200

## Circle Drawing

Submenu choice: 1 → Midpoint, 2 → Bresenham

Input center and radius:

x y: 320 240
radius: 100

## Ellipse Drawing

Input center and radii:

x y: 320 240
x-radius y-radius: 150 80

## Rectangle Drawing

Input top-left and bottom-right coordinates:

x1 y1 x2 y2: 150 100 450 300

## Triangle Drawing

Input three vertices:

x1 y1 x2 y2 x3 y3: 200 300 400 300 300 100


After each drawing, press any key to return to the menu.

Repeat until you choose 6 → Exit.

Line Drawing (DDA / Bresenham)

Circle Drawing (Midpoint / Bresenham)

Ellipse Drawing

Rectangle and Triangle

## License

This project is open-source and free to use for educational purposes.

## Author

Preksha Jain


---


