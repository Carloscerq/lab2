#include "ili9341.h"
#include "tft_gfx.h"
#include "glcdfont.h"

// Draw a circle outline
void ILI9341_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ILI9341_DrawPixel(x0  , y0 + r, color);
    ILI9341_DrawPixel(x0  , y0 - r, color);
    ILI9341_DrawPixel(x0 + r, y0  , color);
    ILI9341_DrawPixel(x0 - r, y0  , color);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ILI9341_DrawPixel(x0 + x, y0 + y, color);
        ILI9341_DrawPixel(x0 - x, y0 + y, color);
        ILI9341_DrawPixel(x0 + x, y0 - y, color);
        ILI9341_DrawPixel(x0 - x, y0 - y, color);
        ILI9341_DrawPixel(x0 + y, y0 + x, color);
        ILI9341_DrawPixel(x0 - y, y0 + x, color);
        ILI9341_DrawPixel(x0 + y, y0 - x, color);
        ILI9341_DrawPixel(x0 - y, y0 - x, color);
    }
}

void ili9341_drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
    
        if (cornername & 0x4)
        {
            ILI9341_DrawPixel(x0 + x, y0 + y, color);
            ILI9341_DrawPixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2)
        {
            ILI9341_DrawPixel(x0 + x, y0 - y, color);
            ILI9341_DrawPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8)
        {
            ILI9341_DrawPixel(x0 - y, y0 + x, color);
            ILI9341_DrawPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1)
        {
            ILI9341_DrawPixel(x0 - y, y0 - x, color);
            ILI9341_DrawPixel(x0 - x, y0 - y, color);
        }
    }
}

// Used to do circles and roundrects
void ili9341_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x1)
        {
            ILI9341_DrawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
            ILI9341_DrawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
        }
        if (cornername & 0x2)
        {
            ILI9341_DrawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
            ILI9341_DrawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
        }
    }
}

void ILI9341_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    ILI9341_DrawFastVLine(x0, y0 - r, 2 * r + 1, color);
    ili9341_fillCircleHelper(x0, y0, r, 3, 0, color);
}

// Bresenham's algorithm - thx wikpedia
void ILI9341_DrawLine(int16_t x0, int16_t y0,	int16_t x1, int16_t y1, uint16_t color)
{
	if (y0 == y1)
    {
		if (x1 > x0)
        {
			ILI9341_DrawFastHLine(x0, y0, x1 - x0 + 1, color);
		} else if (x1 < x0)
        {
			ILI9341_DrawFastHLine(x1, y0, x0 - x1 + 1, color);
		} else
        {
			ILI9341_DrawPixel(x0, y0, color);
		}
		return;
	} else if (x0 == x1)
    {
		if (y1 > y0)
        {
			ILI9341_DrawFastVLine(x0, y0, y1 - y0 + 1, color);
		} else
        {
			ILI9341_DrawFastVLine(x0, y1, y0 - y1 + 1, color);
		}
		return;
	}

	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep)
    {
		swap(x0, y0);
		swap(x1, y1);
	}
	if (x0 > x1)
    {
		swap(x0, x1);
		swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1)
    {
		ystep = 1;
	}
    else
    {
		ystep = -1;
	}

	int16_t xbegin = x0;

	if (steep)
    {
		for (; x0 <= x1; x0++)
        {
			err -= dy;
			if (err < 0)
            {
				int16_t len = x0 - xbegin;
				if (len)
                {
					ILI9341_DrawFastVLine(y0, xbegin, len + 1, color);
				}
                else
                {
					ILI9341_DrawPixel(y0, x0, color);
				}
				xbegin = x0 + 1;
				y0 += ystep;
				err += dx;
			}
		}
		if (x0 > xbegin + 1)
        {
			ILI9341_DrawFastVLine(y0, xbegin, x0 - xbegin, color);
		}
	}
    else
    {
		for (; x0 <= x1; x0++)
        {
			err -= dy;
			if (err < 0)
            {
				int16_t len = x0 - xbegin;
				if (len)
                {
					ILI9341_DrawFastHLine(xbegin, y0, len + 1, color);
				} else
                {
					ILI9341_DrawPixel(x0, y0, color);
				}
				xbegin = x0 + 1;
				y0 += ystep;
				err += dx;
			}
		}
		if (x0 > xbegin + 1)
        {
			ILI9341_DrawFastHLine(xbegin, y0, x0 - xbegin, color);
		}
	}
}

// Draw a rectangle
void ILI9341_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	ILI9341_DrawFastHLine(x, y, w, color);
	ILI9341_DrawFastHLine(x, y + h - 1, w, color);
	ILI9341_DrawFastVLine(x, y, h, color);
	ILI9341_DrawFastVLine(x + w - 1, y, h, color);
}

// Draw a rounded rectangle
void ILI9341_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
  // smarter version
  ILI9341_DrawFastHLine(x + r, y, w - 2 * r, color); // Top
  ILI9341_DrawFastHLine(x + r, y + h - 1, w - 2 * r, color); // Bottom
  ILI9341_DrawFastVLine(x, y + r, h - 2 * r, color); // Left
  ILI9341_DrawFastVLine(x + w - 1, y + r, h - 2 * r, color); // Right
  // draw four corners
  ili9341_drawCircleHelper(x + r, y + r, r, 1, color);
  ili9341_drawCircleHelper(x + w - r - 1, y + r, r, 2, color);
  ili9341_drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
  ili9341_drawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

// Fill a rounded rectangle
void ILI9341_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
  // smarter version
  ILI9341_FillRect(x + r, y, w - 2 * r, h, color);

  // draw four corners
  ili9341_fillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
  ili9341_fillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}

// Draw a triangle
void ILI9341_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
  ILI9341_DrawLine(x0, y0, x1, y1, color);
  ILI9341_DrawLine(x1, y1, x2, y2, color);
  ILI9341_DrawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void ILI9341_FillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
    int16_t a, b, y, last;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1)
    {
        swap(y0, y1);
        swap(x0, x1);
    }
    if (y1 > y2)
    {
        swap(y2, y1);
        swap(x2, x1);
    }
    if (y0 > y1)
    {
        swap(y0, y1);
        swap(x0, x1);
    }

    if (y0 == y2) // Handle awkward all-on-same-line case as its own thing
    {
        a = b = x0;
        if (x1 < a) a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a) a = x2;
        else if (x2 > b) b = x2;
        ILI9341_DrawFastHLine(a, y0, b-a+1, color);
        return;
    }

    int16_t dx01 = x1 - x0;
    int16_t dy01 = y1 - y0;
    int16_t dx02 = x2 - x0;
    int16_t dy02 = y2 - y0;
    int16_t dx12 = x2 - x1;
    int16_t dy12 = y2 - y1;
    int16_t sa   = 0;
    int16_t sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if (y1 == y2) last = y1;   // Include y1 scanline
    else last = y1 - 1; // Skip it

    for (y = y0; y <= last; y++)
    {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if (a > b) swap(a,b);
        ILI9341_DrawFastHLine(a, y, b - a + 1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++)
    {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if (a > b) swap(a,b);
        ILI9341_DrawFastHLine(a, y, b-a+1, color);
    }
}

void ILI9341_DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color)
{
    int16_t i, j, byteWidth = (w + 7) / 8;

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++ )
        {
            if (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)))
            {
                ILI9341_DrawPixel(x + i, y + j, color);
            }
        }
    }
}

// Draw a character
void ili9341_drawChar(int16_t x, int16_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size)
{
    char i, j;
    
    if ((x >= ili9341Info.width)    ||      // Clip right
        (y >= ili9341Info.height)   ||      // Clip bottom
        ((x + 6 * size - 1) < 0)    ||      // Clip left
        ((y + 8 * size - 1) < 0))           // Clip top
        return;

    for (i = 0; i < 6; i++ )
    {
        uint8_t line;
    
        if (i == 5)
            line = 0x0;
        else
            line = pgm_read_byte(font + (c * 5) + i);
    
        for (j = 0; j < 8; j++)
        {
            if (line & 0x1)
            {
                if (size == 1)      // default size
                {    
                    ILI9341_DrawPixel(x + i, y + j, color);
                }
                else                // big size
                    ILI9341_FillRect(x + (i * size), y + (j * size), size, size, color);
            } else if (bg != color)
            {
                if (size == 1)      // default size
                {
                    ILI9341_DrawPixel(x + i, y + j, bg);
                }
                else                // big size
                    ILI9341_FillRect(x + i * size, y + j * size, size, size, bg);
            }
                line >>= 1;
        }
    }
}

void ILI9341_Write(uint8_t c)
{
    if (c == '\n')
    {
        ili9341Info.cursorY += ili9341Info.textSize * 8;
        ili9341Info.cursorX  = 0;
    } else if (c == '\r')
    {
        // skip em
    } else if (c == '\t')
    {
        int new_x = ili9341Info.cursorX + tabspace;
        if (new_x < ili9341Info.width)
        {
            ili9341Info.cursorX = new_x;
        }
    }
    else
    {
        ili9341_drawChar(ili9341Info.cursorX, ili9341Info.cursorY, c, ili9341Info.textColor, ili9341Info.textBgColor, ili9341Info.textSize);
        ili9341Info.cursorX += ili9341Info.textSize * 6;
        if (ili9341Info.wrap && (ili9341Info.cursorX > (ili9341Info.width - ili9341Info.textSize * 6)))
        {
            ili9341Info.cursorY += ili9341Info.textSize * 8;
            ili9341Info.cursorX = 0;
        }
    }
}

inline void ILI9341_WriteString(char* str)
{
    while (*str)
    {
        ILI9341_Write(*str++);
    }
}


inline void ILI9341_SetCursor(int16_t x, int16_t y)
{
    ili9341Info.cursorX = x;
    ili9341Info.cursorY = y;
}

inline void ILI9341_SetTextSize(uint8_t s)
{
    ili9341Info.textSize = (s > 0) ? s : 1;
}

inline void ILI9341_SetTextColor(uint16_t c)
{
    ili9341Info.textColor = ili9341Info.textBgColor = c;
}

inline void ILI9341_SetTextColor2(uint16_t c, uint16_t b)
{
    ili9341Info.textColor = c;
    ili9341Info.textBgColor = b;
}

inline void ILI9341_SetTextWrap(bool w)
{
    ili9341Info.wrap = w;
}

inline uint8_t ILI9341_GetRotation(void)
{
    /* Returns current roation of screen
    *          0 = no rotation (0 degree rotation)
    *          1 = rotate 90 degree clockwise
    *          2 = rotate 180 degree
    *          3 = rotate 90 degree anticlockwise
    */
    return ili9341Info.rotation;
}
