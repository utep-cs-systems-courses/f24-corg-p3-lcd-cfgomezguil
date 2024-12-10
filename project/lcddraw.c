/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include <math.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

void fillTriangle(u_char colMin, u_char rowMin, u_char width, u_char height, u_int colorBGR)
{
  u_char colMid = colMin + (width / 2); // Middle of the rectangle's width
  u_char rowMax = rowMin + height;     // Bottom row of the rectangle

  
  for (u_char row = rowMin; row < rowMax; row++) {
    // Determine the horizontal range for the current row
    u_char rowHeight = row - rowMin; // Distance from the top row
    u_char colStart = colMid - rowHeight; // Left boundary of the triangle for the row
    u_char colEnd = colMid + rowHeight;   // Right boundary of the triangle for the row

    if (colStart < colMin) colStart = colMin; // Clamp to the rectangle bounds
    if (colEnd >= colMin + width) colEnd = colMin + width - 1; // Clamp to the rectangle bounds
    // Set the area and fill it for the current row
    lcd_setArea(colStart, row, colEnd, row);
    for (u_char col = colStart; col <= colEnd; col++) {
      lcd_writeColor(colorBGR);
    }
  }
}

void drawUDTriangle(u_char colMin, u_char rowMin, u_char width, u_char height,u_int colorBGR){
  for(u_char row = 0; row < height; row++) {
    // Calculate width reduction for row
    u_char rowWidth = width - ((width * row) / height);

    u_char colStart = colMin + ((width - rowWidth) / 2);
    u_char colEnd = colStart + rowWidth - 1;

    // Draw pixels in the row
    for (u_char col = colStart; col <= colEnd; col++) {
      drawPixel(col, rowMin + row, colorBGR);
    }
  }
}
    
// Circle formula (x-h)^2 + (y-k)^2 = r^2
void drawSemiCircle(u_char colMin, u_char rowMin, u_char width, u_char height, u_int colorBGR) {
  // Calculate the radius of the semi-circle
  u_char radius = width / 2;

  // Center of the circle
  u_char centerX = colMin + radius;
  u_char centerY = rowMin + height - 1;

  // Draw the semi-circle
  for (u_char row = 0; row < height; row++) {
    // Calculate the vertical distance from the center
    u_char dy = centerY - (rowMin + row);
    // Determine the horizontal range (width of the semi-circle at this row)
    u_char dx = (u_char) sqrt((radius * radius) - (dy * dy));
    // Calculate the starting and ending columns for this row
    u_char colStart = centerX - dx;
    u_char colEnd = centerX + dx;
    // Draw pixels for the row
    for (u_char col = colStart; col <= colEnd; col++) {
      drawPixel(col, rowMin + row, colorBGR);
    }
  }
}

void drawHeart(u_char colMin, u_char rowMin, u_char sizeRow, u_char sizeCol, u_int colorBGR){
  // sizeRow = semi-circle size
  // sizeCol = height of Triangle
  // triRow = total length of triangle
  u_char triRow = sizeRow * 2;
  u_char triCol = sizeCol * 2;
  drawUDTriangle(colMin, rowMin, triRow, triCol, colorBGR);
  drawSemiCircle(colMin, rowMin - sizeCol, sizeRow, sizeCol, colorBGR);
  drawSemiCircle(colMin + sizeRow, rowMin - sizeCol, sizeRow - 1 , sizeCol, colorBGR);
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}

void drawChar8x12(u_char rcol, u_char rrow, char c,u_int fgColorBGR, u_int bgColorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_char oc = c - 0x20; // Offset character to align with font_8x12 array

  lcd_setArea(rcol, rrow, rcol + 7, rrow + 11); /* Set area for 8x12 font */
  while (row < 12) {
    while (col < 8) {
      // Use the specific row for the current character in the font_8x12 array
      u_int colorBGR = (font_8x12[oc][row] & (0x80 >> col)) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    row++;
  }
}


void drawString8x12(u_char col, u_char row, char *string, u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar8x12(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 9; // Adjust spacing for 8x12 font (8 pixels width + 1 pixel gap)
  }
}




/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

