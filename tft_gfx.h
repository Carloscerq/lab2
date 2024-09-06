#include "app.h"

void ILI9341_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void ILI9341_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void ILI9341_DrawLine(int16_t x0, int16_t y0,	int16_t x1, int16_t y1, uint16_t color);
void ILI9341_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void ILI9341_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void ILI9341_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void ILI9341_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void ILI9341_FillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void ILI9341_DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
void ILI9341_Write(uint8_t c);
void ILI9341_WriteString(char* str);
void ILI9341_SetCursor(int16_t x, int16_t y);
void ILI9341_SetTextSize(uint8_t s);
void ILI9341_SetTextColor(uint16_t c);
void ILI9341_SetTextColor2(uint16_t c, uint16_t b);
void ILI9341_SetTextWrap(bool w);
uint8_t ILI9341_GetRotation(void);
