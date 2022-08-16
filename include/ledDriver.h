#ifndef __LEDDRIVER_H
#define __LEDDRIVER_H


#define WS2812_0			7			// WS2812's zero high time is long about one third of the period
#define WS2812_1			14
#define WS2812_RESET		0

#define LED_NUMBER			10					// how many LEDs the MCU should control?
#define LED_DATA_SIZE		LED_NUMBER * 24
#define RESET_SLOTS_BEGIN	1
#define RESET_SLOTS_END		50
#define WS2812_LAST_SLOT	1
#define LED_BUFFER_SIZE		RESET_SLOTS_BEGIN + LED_DATA_SIZE + WS2812_LAST_SLOT + RESET_SLOTS_END


void ws2812Init(void);
void fillBufferWhite(void);
void fillBufferBlack(void);
void setWHOLEcolor(uint8_t RED, uint8_t GREEN, uint8_t BLUE);
void setLEDcolor(uint32_t LEDnumber, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
void stripEffect_AllColors(uint32_t delay);






#endif
