#include <math.h>
#include "ili9341.h"

ILI9341_INFO ili9341Info;

void ili9341_writeCommand(uint8_t cmd);
void ili9341_writeData(uint8_t dat);
void ili9341_writeData16(uint16_t dat);
void ili9341_mode16(void);
void ili9341_mode8(void);

void ILI9341_Init(void)
{
    ili9341Info.width = ILI9341_DEF_WIDTH;
    ili9341Info.height = ILI9341_DEF_HEIGHT;
    ili9341Info.cursorX = 0;
    ili9341Info.cursorY = 0;
    ili9341Info.rotation = 0;
    ili9341Info.textSize = 1;
    ili9341Info.textColor = ILI9341_WHITE;
    ili9341Info.textBgColor = ILI9341_BLACK;
    ili9341Info.wrap = false;

//    LCD_RST_TRIS;
//    LCD_DC_TRIS;
//    LCD_CS_TRIS;
//    LCD_SDO_TRIS;

    LCD_DC_CLR;
    LCD_CS_CLR;
    LCD_CS_SET;

    // Reset
    LCD_RST_CLR;
    CORETIMER_DelayMs(10);    
    LCD_RST_SET;
    CORETIMER_DelayMs(10);

    ili9341_writeCommand(0xEF);
    CORETIMER_DelayMs(100);
    ili9341_writeData(0x03);
    CORETIMER_DelayMs(100);

    ili9341_writeData(0x80);
    ili9341_writeData(0x02);

    ili9341_writeCommand(0xCF);
    ili9341_writeData(0x00);
    ili9341_writeData(0xC1);
    ili9341_writeData(0x30);

    ili9341_writeCommand(0xED);
    ili9341_writeData(0x64);
    ili9341_writeData(0x03);
    ili9341_writeData(0x12);
    ili9341_writeData(0x81);

    ili9341_writeCommand(0xE8);
    ili9341_writeData(0x85);
    ili9341_writeData(0x00);
    ili9341_writeData(0x78);

    ili9341_writeCommand(0xCB);
    ili9341_writeData(0x39);
    ili9341_writeData(0x2C);
    ili9341_writeData(0x00);
    ili9341_writeData(0x34);
    ili9341_writeData(0x02);

    ili9341_writeCommand(0xF7);
    ili9341_writeData(0x20);

    ili9341_writeCommand(0xEA);
    ili9341_writeData(0x00);
    ili9341_writeData(0x00);

    ili9341_writeCommand(ILI9341_PWCTR1);    //Power control
    ili9341_writeData(0x23);                 //VRH[5:0]

    ili9341_writeCommand(ILI9341_PWCTR2);    //Power control
    ili9341_writeData(0x10);                 //SAP[2:0];BT[3:0]

    ili9341_writeCommand(ILI9341_VMCTR1);    //VCM control
    ili9341_writeData(0x3e);
    ili9341_writeData(0x28);

    ili9341_writeCommand(ILI9341_VMCTR2);    //VCM control2
    ili9341_writeData(0x86);

    ili9341_writeCommand(ILI9341_MADCTL);    // Memory Access Control
    ili9341_writeData(ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR);

    ili9341_writeCommand(ILI9341_PIXFMT);
    ili9341_writeData(0x55);

    ili9341_writeCommand(ILI9341_FRMCTR1);
    ili9341_writeData(0x00);
    ili9341_writeData(0x18);

    ili9341_writeCommand(ILI9341_DFUNCTR);    // Display Function Control
    ili9341_writeData(0x08);
    ili9341_writeData(0x82);
    ili9341_writeData(0x27);

    ili9341_writeCommand(0xF2);              // 3Gamma Function Disable
    ili9341_writeData(0x00);

    ili9341_writeCommand(ILI9341_GAMMASET);   //Gamma curve selected
    ili9341_writeData(0x01);

    ili9341_writeCommand(ILI9341_GMCTRP1);    //Set Gamma
    ili9341_writeData(0x0F);
    ili9341_writeData(0x31);
    ili9341_writeData(0x2B);
    ili9341_writeData(0x0C);
    ili9341_writeData(0x0E);
    ili9341_writeData(0x08);
    ili9341_writeData(0x4E);
    ili9341_writeData(0xF1);
    ili9341_writeData(0x37);
    ili9341_writeData(0x07);
    ili9341_writeData(0x10);
    ili9341_writeData(0x03);
    ili9341_writeData(0x0E);
    ili9341_writeData(0x09);
    ili9341_writeData(0x00);

    ili9341_writeCommand(ILI9341_GMCTRN1);    //Set Gamma
    ili9341_writeData(0x00);
    ili9341_writeData(0x0E);
    ili9341_writeData(0x14);
    ili9341_writeData(0x03);
    ili9341_writeData(0x11);
    ili9341_writeData(0x07);
    ili9341_writeData(0x31);
    ili9341_writeData(0xC1);
    ili9341_writeData(0x48);
    ili9341_writeData(0x08);
    ili9341_writeData(0x0F);
    ili9341_writeData(0x0C);
    ili9341_writeData(0x31);
    ili9341_writeData(0x36);
    ili9341_writeData(0x0F);

    ili9341_writeCommand(ILI9341_SLPOUT);    //Exit Sleep
    CORETIMER_DelayMs(150);
    ili9341_writeCommand(ILI9341_DISPON);    //Display on
    CORETIMER_DelayMs(150);

}

void ili9341_spiWrite8(uint8_t c)
{
    // Envia um único byte via SPI
    SPI2_Write(&c, 1);
    CORETIMER_DelayMs(5);
}


void ili9341_spiWrite16(uint16_t c)
{
    uint8_t data[2];
    data[0] = c >> 8;    // Byte mais significativo (MSB)
    data[1] = c & 0xFF;  // Byte menos significativo (LSB)

    // Envia os dois bytes via SPI, um byte de cada vez
    SPI2_Write(data, 2);
    CORETIMER_DelayMs(5);

}
  
void ili9341_writeCommand(uint8_t cmd)
{
    LCD_DC_CLR;
    LCD_CS_CLR;
    
    ili9341_spiWrite8(cmd);
    
    LCD_CS_SET;
}

void ili9341_writeData(uint8_t dat)
{
    LCD_DC_SET;
    LCD_CS_CLR;

    ili9341_spiWrite8(dat);

    LCD_CS_SET;
}

void ili9341_writeData16(uint16_t dat)
{
    LCD_DC_SET;
    LCD_CS_CLR;

    ili9341_spiWrite16(dat);
    
    LCD_CS_SET;
}

void ili9341_setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    ili9341_writeCommand(ILI9341_CASET);    // Column addr set
    ili9341_writeData16(x0);
    ili9341_writeData16(x1);

    ili9341_writeCommand(ILI9341_PASET);    // Row addr set
    ili9341_writeData16(y0);
    ili9341_writeData16(y1);

    ili9341_writeCommand(ILI9341_RAMWR);    // write to RAM
}

void ili9341_pushColor(uint16_t color)
{
    LCD_DC_SET;
    LCD_CS_CLR;

    ili9341_spiWrite16(color);

    LCD_CS_SET;
}

inline uint16_t ILI9341_Color565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

//color565toRGB14		- converts 16 bit 565 format color to 14 bit RGB (2 bits clear for math and sign)
//returns 00rrrrr000000000,00gggggg00000000,00bbbbb000000000
//thus not overloading sign, and allowing up to double for additions for fixed point delta
void ili9341_color565toRGB14(uint16_t color, int16_t *r, int16_t *g, int16_t *b)
{
	*r = (color >> 2) & 0x3E00;
	*g = (color << 3) & 0x3F00;
	*b = (color << 9) & 0x3E00;
}

//RGB14tocolor565		- converts 14 bit RGB back to 16 bit 565 format color
uint16_t ili9341_RGB14tocolor565(int16_t r, int16_t g, int16_t b)
{
	return (((r & 0x3E00) << 2) | ((g & 0x3F00) >>3) | ((b & 0x3E00) >> 9));
}

void ILI9341_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
/* Draw a vertical line at location from (x,y) to (x,y+h-1) with color
 * Parameters:
 *      x:  x-coordinate line to draw; top left of screen is x=0
 *              and x increases to the right
 *      y:  y-coordinate of starting point of line; top left of screen is y=0
 *              and y increases to the bottom
 *      h:  height of line to draw
 *      color:  16-bit color value
 * Returns:     Nothing
 */

	if ((x >= ili9341Info.width) || (x < 0) || (y >= ili9341Info.height)) return;
	if(y < 0)
    {
        h += y;
        y = 0;
 	}
	if (( y + h - 1) >= ili9341Info.height) h = ili9341Info.height - y;
    
    ili9341_setAddrWindow(x, y, x, y + h - 1);

    LCD_DC_SET;
    LCD_CS_CLR;

    while (h--)
    {
        ili9341_spiWrite16(color);
    }

    LCD_CS_SET;
}

void ILI9341_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
/* Draw a horizontal line at location from (x,y) to (x+w-1,y) with color
 * Parameters:
 *      x:  x-coordinate starting point of line; top left of screen is x=0
 *              and x increases to the right
 *      y:  y-coordinate of starting point of line; top left of screen is y=0
 *              and y increases to the bottom
 *      w:  width of line to draw
 *      color:  16-bit color value
 * Returns:     Nothing
 */

	if ((x >= ili9341Info.width) || (y >= ili9341Info.height) || (y < 0)) return;
	if (x < 0)
    {
        w += x;
        x = 0;
 	}
	if ((x + w - 1) >= ili9341Info.width)  w = ili9341Info.width - x;

    ili9341_setAddrWindow(x, y, x + w - 1, y);

    LCD_DC_SET;
    LCD_CS_CLR;

    while (w--)
    {
        ili9341_spiWrite16(color);
    }

    LCD_CS_SET;
}

void ILI9341_DrawPixel(int16_t x, int16_t y, uint16_t color)
{
/* Draw a pixel at location (x,y) with given color
 * Parameters:
 *      x:  x-coordinate of pixel to draw; top left of screen is x=0
 *              and x increases to the right
 *      y:  y-coordinate of pixel to draw; top left of screen is y=0
 *              and y increases to the bottom
 *      color:  16-bit color value
 * Returns:     Nothing
 */

    if((x < 0) ||(x >= ili9341Info.width) || (y < 0) || (y >= ili9341Info.height)) return;

    ili9341_setAddrWindow(x, y, x + 1, y + 1);

    LCD_DC_SET;
    LCD_CS_CLR;
    
    ili9341_spiWrite16(color);
    
    LCD_CS_SET;
}

// fill a rectangle
void ILI9341_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
/* Draw a filled rectangle with starting top-left vertex (x,y),
 *  width w and height h with given color
 * Parameters:
 *      x:  x-coordinate of top-left vertex; top left of screen is x=0
 *              and x increases to the right
 *      y:  y-coordinate of top-left vertex; top left of screen is y=0
 *              and y increases to the bottom
 *      w:  width of rectangle
 *      h:  height of rectangle
 *      color:  16-bit color value
 * Returns:     Nothing
 */

	if ((x >= ili9341Info.width) || (y >= ili9341Info.height)) return;
	if (x < 0)
    {
        w += x;
        x = 0;
 	}
	if (y < 0)
    {
        h += y;
        y = 0;
 	}
	if ((x + w - 1) >= ili9341Info.width)  w = ili9341Info.width  - x;
	if ((y + h - 1) >= ili9341Info.height) h = ili9341Info.height - y;
    
    ili9341_setAddrWindow(x, y, x + w - 1, y + h - 1);

    LCD_DC_SET;
    LCD_CS_CLR;

    for (y = h; y > 0; y--)
    {
        for (x = w; x > 0; x--)
        {
            ili9341_spiWrite16(color);
        }
    }

    LCD_CS_SET;
}

void ILI9341_FillScreen(uint16_t color)
{
/* Fill entire screen with given color
 * Parameters:
 *      color: 16-bit color value
 * Returs:  Nothing
 */
    ILI9341_FillRect(0, 0, ili9341Info.width, ili9341Info.height, color);
}

void ILI9341_FillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2)
{
	// rudimentary clipping (drawChar w/big text requires this)
	if ((x >= ili9341Info.width) || (y >= ili9341Info.height)) return;
	if ((x + w - 1) >= ili9341Info.width)  w = ili9341Info.width  - x;
	if ((y + h - 1) >= ili9341Info.height) h = ili9341Info.height - y;
	
	int16_t r1, g1, b1, r2, g2, b2, dr, dg, db, r, g, b;
	ili9341_color565toRGB14(color1, &r1, &g1, &b1);
	ili9341_color565toRGB14(color2, &r2, &g2, &b2);
	dr = (r2 - r1) / h;
    dg = (g2 - g1) / h;
    db = (b2 - b1) / h;
	r = r1;
    g = g1;
    b = b1;	

	// TODO: this can result in a very long transaction time
	// should break this into multiple transactions, even though
	// it'll cost more overhead, so we don't stall other SPI libs
	ili9341_setAddrWindow(x, y, x + w - 1, y + h - 1);

    LCD_DC_SET;
    LCD_CS_CLR;

	for (y = h; y > 0; y--)
    {
		uint16_t color = ili9341_RGB14tocolor565(r, g, b);

		for (x = w; x > 1; x--)
        {
			ili9341_spiWrite16(color);
		}

		r += dr;
        g += dg;
        b += db;
	}

    LCD_CS_SET;
}

// fillRectHGradient	- fills area with horizontal gradient
void ILI9341_FillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2)
{
	// rudimentary clipping (drawChar w/big text requires this)
	if ((x >= ili9341Info.width) || (y >= ili9341Info.height)) return;
	if ((x + w - 1) >= ili9341Info.width)  w = ili9341Info.width  - x;
	if ((y + h - 1) >= ili9341Info.height) h = ili9341Info.height - y;
	
	int16_t r1, g1, b1, r2, g2, b2, dr, dg, db, r, g, b;
	
    ili9341_color565toRGB14(color1, &r1, &g1, &b1);
	ili9341_color565toRGB14(color2, &r2, &g2, &b2);
	
    dr = (r2 - r1) / h;
    dg = (g2 - g1) / h;
    db = (b2 - b1) / h;
	r = r1;
    g = g1;
    b = b1;	

	// TODO: this can result in a very long transaction time
	// should break this into multiple transactions, even though
	// it'll cost more overhead, so we don't stall other SPI libs
	ili9341_setAddrWindow(x, y, x+w-1, y+h-1);

    LCD_DC_SET;
    LCD_CS_CLR;

	for (y = h; y > 0; y--)
    {
		uint16_t color;
		
        for (x = w; x > 1; x--)
        {
			color = ili9341_RGB14tocolor565(r, g, b);
			ili9341_spiWrite16(color);
			r += dr;
            g += dg;
            b += db;
		}
		
        color = ili9341_RGB14tocolor565(r, g, b);
		r = r1;
        g = g1;
        b = b1;
	}

    LCD_CS_SET;
}

// fillScreenVGradient - fills screen with vertical gradient
void ILI9341_FillScreenVGradient(uint16_t color1, uint16_t color2)
{
	ILI9341_FillRectVGradient(0, 0, ili9341Info.width, ili9341Info.height, color1, color2);
}

// fillScreenHGradient - fills screen with horizontal gradient
void ILI9341_FillScreenHGradient(uint16_t color1, uint16_t color2)
{
	ILI9341_FillRectHGradient(0, 0, ili9341Info.width, ili9341Info.height, color1, color2);
}

// Now lets see if we can writemultiple pixels
void ILI9341_WriteRect(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *pcolors)
{
	ili9341_setAddrWindow(x, y, x + w - 1, y + h - 1);

    LCD_DC_SET;
    LCD_CS_CLR;

	for (y = h; y > 0; y--)
    {
		for(x = w; x > 1; x--)
        {
			ili9341_spiWrite16(*pcolors++);
		}
	}

    LCD_CS_SET;
}

void ILI9341_SetRotation(uint8_t m)
{
	ili9341Info.rotation = m % 4; // can't be higher than 3

	ili9341_writeCommand(ILI9341_MADCTL);
	
    switch (ili9341Info.rotation)
    {
        case 0:
            ili9341_writeData(ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR);
            ili9341Info.width  = ILI9341_DEF_WIDTH;
            ili9341Info.height = ILI9341_DEF_HEIGHT;
            break;
        case 1:
            ili9341_writeData(ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR);
            ili9341Info.width  = ILI9341_DEF_HEIGHT;
            ili9341Info.height = ILI9341_DEF_WIDTH;
            break;
        case 2:
            ili9341_writeData(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
            ili9341Info.width  = ILI9341_DEF_WIDTH;
            ili9341Info.height = ILI9341_DEF_HEIGHT;
            break;
        case 3:
            ili9341_writeData(ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR);
            ili9341Info.width  = ILI9341_DEF_HEIGHT;
            ili9341Info.height = ILI9341_DEF_WIDTH;
            break;
	}

	ili9341Info.cursorX = 0;
	ili9341Info.cursorY = 0;
}

void ILI9341_SetScroll(uint16_t offset)
{
	ili9341_writeCommand(ILI9341_VSCRSADD);
	ili9341_writeData16(offset);
}

void ILI9341_InvertDisplay(bool b)
{
	ili9341_writeCommand(b ? ILI9341_INVON : ILI9341_INVOFF);
}

uint16_t ILI9341_GetWidth(void)
{
    return ili9341Info.width;
}        

uint16_t ILI9341_GetHeight(void)
{
    return ili9341Info.height;
}        

// writeRect8BPP - 	write 8 bit per pixel paletted bitmap
//					bitmap data in array at pixels, one byte per pixel
//					color palette data in array at palette
void ili9341_writeRect8BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette )
{
	ili9341_setAddrWindow(x, y, x + w - 1, y + h - 1);

    LCD_DC_SET;
    LCD_CS_CLR;

	for (y = h; y > 0; y--)
    {
		for (x = w; x > 1; x--)
        {
			ili9341_spiWrite16(palette[*pixels++]);
		}
	}

    LCD_CS_SET;
}

// writeRect4BPP - 	write 4 bit per pixel paletted bitmap
//					bitmap data in array at pixels, 4 bits per pixel
//					color palette data in array at palette
//					width must be at least 2 pixels
void ili9341_writeRect4BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette )
{
	ili9341_setAddrWindow(x, y, x + w - 1, y + h - 1);

    LCD_DC_SET;
    LCD_CS_CLR;

	for (y = h; y > 0; y--)
    {
		for (x = w; x > 2; x -= 2)
        {
			ili9341_spiWrite16(palette[((*pixels)>>4)&0xF]);
			ili9341_spiWrite16(palette[(*pixels++)&0xF]);
		}
	}

    LCD_CS_SET;
}

// writeRect2BPP - 	write 2 bit per pixel paletted bitmap
//					bitmap data in array at pixels, 4 bits per pixel
//					color palette data in array at palette
//					width must be at least 4 pixels
void ili9341_writeRect2BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette )
{
	ili9341_setAddrWindow(x, y, x + w - 1, y + h - 1);

    LCD_DC_SET;
    LCD_CS_CLR;

	for (y = h; y > 0; y--)
    {
		for (x = w; x > 4; x -= 4)
        {
			//unrolled loop might be faster?
			ili9341_spiWrite16(palette[((*pixels)>>6)&0x3]);
			ili9341_spiWrite16(palette[((*pixels)>>4)&0x3]);
			ili9341_spiWrite16(palette[((*pixels)>>2)&0x3]);
			ili9341_spiWrite16(palette[(*pixels++)&0x3]);
		}
	}

    LCD_CS_SET;
}

// writeRect1BPP - 	write 1 bit per pixel paletted bitmap
//					bitmap data in array at pixels, 4 bits per pixel
//					color palette data in array at palette
//					width must be at least 8 pixels
void ili9341_writeRect1BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette )
{
	ili9341_setAddrWindow(x, y, x + w - 1, y + h - 1);

    LCD_DC_SET;
    LCD_CS_CLR;

	for (y = h; y > 0; y--)
    {
		for (x = w; x > 8; x -= 8)
        {
			//unrolled loop might be faster?
			ili9341_spiWrite16(palette[((*pixels)>>7)&0x1]);
			ili9341_spiWrite16(palette[((*pixels)>>6)&0x1]);
			ili9341_spiWrite16(palette[((*pixels)>>5)&0x1]);
			ili9341_spiWrite16(palette[((*pixels)>>4)&0x1]);
			ili9341_spiWrite16(palette[((*pixels)>>3)&0x1]);
			ili9341_spiWrite16(palette[((*pixels)>>2)&0x1]);
			ili9341_spiWrite16(palette[((*pixels)>>1)&0x1]);
			ili9341_spiWrite16(palette[(*pixels++)&0x1]);
		}
	}
    
    LCD_CS_SET;
}
