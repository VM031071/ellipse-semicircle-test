#include <iostream>
#include "BMP.h"
#include <cmath>

// Returns the corresponding position for a given value.
int getPos(int t, int r1, int r2)
{
  return sqrt(pow(r1, 2) - pow(t, 2)) * r2 / r1;
}

// Generates an ellipse with white pixels.
BMP generateEllipse(BMP canvas, int a, int b)
{
  int x = 0;
  int y = b;
  int d = 1 - b;

  canvas.set_pixel(x + a, y + b - 1, 255, 255, 255, 0);
  canvas.set_pixel(-x + a, y + b - 1, 255, 255, 255, 0);
  canvas.set_pixel(-x + a, -y + b, 255, 255, 255, 0);
  canvas.set_pixel(x + a, -y + b, 255, 255, 255, 0);
  
  while (pow(b, 2) * x < pow(a, 2) * y)
    {
      if (d < 0)
        {
          d += pow(b, 2) * (2 * x + 3);
        }
      else
        {
          d += pow(b, 2) * (2 * x + 3) + pow(a, 2) * (-2 * y + 2);
          y--;
        }

      x++;
      
      canvas.set_pixel(x + a, y + b - 1, 255, 255, 255, 0);
      canvas.set_pixel(-x + a, y + b - 1, 255, 255, 255, 0);
      canvas.set_pixel(-x + a, -y + b, 255, 255, 255, 0);
      canvas.set_pixel(x + a, -y + b, 255, 255, 255, 0);
    }

  x = a;
  y = 0;
  d = 1 - a;

  canvas.set_pixel(x + a - 1, y + b, 255, 255, 255, 0);
  canvas.set_pixel(-x + a, y + b, 255, 255, 255, 0);
  canvas.set_pixel(-x + a, -y + b, 255, 255, 255, 0);
  canvas.set_pixel(x + a - 1, -y + b, 255, 255, 255, 0);

  while (pow(b, 2) * x > pow(a, 2) * y)
    {
      if (d < 0)
        {
          d += pow(a, 2) * (2 * y + 3);
        }
      else
        {
          d += pow(a, 2) * (2 * y + 3) + pow(b, 2) * (-2 * x + 2);
          x--;
        }

      y++;
      
      canvas.set_pixel(x + a - 1, y + b, 255, 255, 255, 0);
      canvas.set_pixel(-x + a, y + b, 255, 255, 255, 0);
      canvas.set_pixel(-x + a, -y + b, 255, 255, 255, 0);
      canvas.set_pixel(x + a - 1, -y + b, 255, 255, 255, 0);
    }
  
  return canvas;
}

// Generates a semicircle with red pixels.
BMP generateSemiCircle(BMP canvas, int a, int b)
{
  int x = 0;
  int y = b;
  int d = 1 - b;

  canvas.set_pixel(x + 2 * a, y + b - 1, 0, 0, 255, 0);
  canvas.set_pixel(x + 2 * a, -y + b, 0, 0, 255, 0);

  while (pow(b, 2) * x < pow(a, 2) * y)
    {
      if (d < 0)
        {
          d += pow(b, 2) * (2 * x + 3);
        }
      else
        {
          d += pow(b, 2) * (2 * x + 3) + pow(a, 2) * (-2 * y + 2);
          y--;
        }

      x++;

      canvas.set_pixel(x + 2 * a, y + b - 1, 0, 0, 255, 0);
      canvas.set_pixel(x + 2 * a, -y + b, 0, 0, 255, 0);
    }

  x = a;
  y = 0;
  d = 1 - a;

  canvas.set_pixel(x + 2 * a - 1, y + b, 0, 0, 255, 0);
  canvas.set_pixel(x + 2 * a - 1, -y + b, 0, 0, 255, 0);

  while (pow(b, 2) * x > pow(a, 2) * y)
    {
      if (d < 0)
        {
          d += pow(a, 2) * (2 * y + 3);
        }
      else
        {
          d += pow(a, 2) * (2 * y + 3) + pow(b, 2) * (-2 * x + 2);
          x--;
        }

      y++;
      
      canvas.set_pixel(x + 2 * a - 1, y + b, 0, 0, 255, 0);
      canvas.set_pixel(x + 2 * a - 1, -y + b, 0, 0, 255, 0);
    }
  
  return canvas;
}

int main()
  {
    // Initialize canvas.
    BMP bmpNew(1440 , 720, false);

    // Set the canvas to black.
    bmpNew.fill_region(0, 0, 200, 200, 0, 0, 0, 0);

    // Generate the whole ellipse.
    bmpNew = generateEllipse(bmpNew, bmpNew.bmp_info_header.width / 2, bmpNew.bmp_info_header.height / 2);
    // Generate the semicircle.
    bmpNew = generateSemiCircle(bmpNew, bmpNew.bmp_info_header.height / 2, bmpNew.bmp_info_header.height / 2);

    // Save the canvas to a BMP file.
    bmpNew.write("output.bmp");

    return 0;
  }