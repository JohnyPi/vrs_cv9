/*
 * display.c
 *
 *  Created on: Dec 14, 2021
 *      Author: Marek Pohancenik
 */

#include "display.h"
#include "assignment.h"

uint64_t disp_time = 0, disp_time_saved = 0;

#define DISPLAY_SIZE 4

void display_update(char c, uint8_t dgt);
void display_show(char znk[50]);
uint8_t shift = 0;
uint8_t len = 0;
uint8_t prerusenie = 0;
uint8_t start = 1;
uint8_t d = 0;



/*Reset (turn-off) all the segments of display*/
void resetSegments(void) {
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_11);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_1);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_3);
}

/*Set (turn-on) all the segments of display*/
void setSegments(void) {
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_11);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_1);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3);
}

/* Reset (turn-off) all digits*/
void resetDigits(void) {
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_7);
}

/* Reset (turn-on) all digits*/
void setDigits(void) {
	DIGIT_1_ON;
	DIGIT_2_ON;
	DIGIT_3_ON;
	DIGIT_4_ON;
	DIGIT_TIME_ON;
}

void setDecimalPoint(void) {
	LL_GPIO_ResetOutputPin(SEGMENTDP_PORT, SEGMENTDP_PIN);
}

void character_podciar(void) {

	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);

}

void character_minus(void) {

	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);

}
/**
 * Pre-process number before it is displayed. Extract digits of the number
 */

/*
 * Turns required digit ON
 */
void setDigit(uint8_t pos) {
	switch (pos) {
	case 0:
		DIGIT_1_ON;
		break;
	case 1:
		DIGIT_2_ON;
		break;
	case 2:
		DIGIT_3_ON;
		break;
	case 3:
		DIGIT_4_ON;
		break;
	}
}

void display_update(char c, uint8_t dgt) {

	switch (c) {
	case 'A':
	case 'a':
		setDigit(dgt);
		character_A();
		break;
	case 'B':
	case 'b':
		setDigit(dgt);
		character_B();
		break;
	case 'C':
	case 'c':
		setDigit(dgt);
		character_C();
		break;
	case 'D':
	case 'd':
		setDigit(dgt);
		character_D();
		break;
	case 'E':
	case 'e':
		setDigit(dgt);
		character_E();
		break;
	case 'F':
	case 'f':
		setDigit(dgt);
		character_F();
		break;
	case 'G':
	case 'g':
		setDigit(dgt);
		character_G();
		break;
	case 'H':
	case 'h':
		setDigit(dgt);
		character_H();
		break;
	case 'I':
	case 'i':
		setDigit(dgt);
		character_I();
		break;
	case 'J':
	case 'j':
		setDigit(dgt);
		character_J();
		break;
	case 'K':
	case 'k':
		setDigit(dgt);
		character_K();
		break;
	case 'L':
	case 'l':
		setDigit(dgt);
		character_L();
		break;
	case 'M':
	case 'm':
		setDigit(dgt);
		character_M();
		break;
	case 'N':
	case 'n':
		setDigit(dgt);
		character_N();
		break;
	case 'O':
	case 'o':
		setDigit(dgt);
		character_O();
		break;
	case 'P':
	case 'p':
		setDigit(dgt);
		character_P();
		break;
	case 'Q':
	case 'q':
		setDigit(dgt);
		character_Q();
		break;
	case 'R':
	case 'r':
		setDigit(dgt);
		character_R();
		break;
	case 'S':
	case 's':
		setDigit(dgt);
		character_S();
		break;
	case 'T':
	case 't':
		setDigit(dgt);
		character_T();
		break;
	case 'U':
	case 'u':
		setDigit(dgt);
		character_U();
		break;
	case 'V':
	case 'v':
		setDigit(dgt);
		character_V();
		break;
	case 'W':
	case 'w':
		setDigit(dgt);
		character_W();
		break;
	case 'X':
	case 'x':
		setDigit(dgt);
		character_X();
		break;
	case 'Y':
	case 'y':
		setDigit(dgt);
		character_Y();
		break;
	case 'Z':
	case 'z':
		setDigit(dgt);
		character_Z();
		break;
	case '1':
		setDigit(dgt);
		character_1();
		break;
	case '2':
		setDigit(dgt);
		character_2();
		break;
	case '3':
		setDigit(dgt);
		character_3();
		break;
	case '4':
		setDigit(dgt);
		character_4();
		break;
	case '5':
		setDigit(dgt);
		character_5();
		break;
	case '6':
		setDigit(dgt);
		character_6();
		break;
	case '7':
		setDigit(dgt);
		character_7();
		break;
	case '8':
		setDigit(dgt);
		character_8();
		break;
	case '9':
		setDigit(dgt);
		character_9();
		break;
	case '0':
		setDigit(dgt);
		character_0();
		break;
	case '_':
		setDigit(dgt);
		character_podciar();
		break;
	case '-':
		setDigit(dgt);
		character_minus();
		break;

	}

	disp_time_saved = disp_time;
	while ((disp_time_saved + 2) > disp_time) {
	};

	resetDigits();
	resetSegments();
}

void display_show(char *znk) {
	len = strlen(znk) - 1;
	char *location = strchr(znk, '.');
	uint8_t position = 0;
	start = 0;
	if (location != NULL) {
		position = location - znk - 1;
		for (uint8_t i = 0; i < 4; i++) {
			if ((shift + i) == position) {
				setDecimalPoint();
				display_update(znk[(shift) + i], i);
			} else if ((shift + i) == (position + 1) && d == 0) {
				display_update(znk[(shift) + i + 1], i);
				d = 1;
				return;
			} else if ((shift + i) == (position + 1) && d == 1) {
				display_update(znk[(shift) + i + 2], i + 1);
				d = 0;
				return;
			} else
				display_update(znk[(shift) + i], i);
		}
	} else {
		len = len + 1;
		for (uint8_t j = 0; j < 4; j++) {
			display_update(znk[(shift) + j], j);
		}
	}

}


void TIM3_IRQHandler(void) {
	if (LL_TIM_IsActiveFlag_UPDATE(TIM3)) {
		if ((shift < len - 4) && prerusenie == 0) {
			shift++;
		} else if ((shift == len - 4) && prerusenie == 0 && start == 0) {
			prerusenie = 1;
		}

		else if (((shift + len) > len) && prerusenie == 1) {
			shift--;
		} else if (((shift + len) == len) && prerusenie == 1 && start == 0) {
			prerusenie = 0;
		}
	}

	LL_TIM_ClearFlag_UPDATE(TIM3);
}

