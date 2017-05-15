#ifndef _NUC144__H__

#include <stdbool.h>
#include "gpio.h"

void nuc144_ioInit(void);
void setRed(bool state);
void setBlue(bool state);
void setGreen(bool state);
bool readButton(void);

/*****************************************************************************/
/*                           Board Specifics                                 */
/*****************************************************************************/
/* 11 GPIO ports (A -> K)
 *
 * Defaults:
 *
 * A15: pulled up						JTDI
 * A14: pulled down						JTCK-SWCLK
 * A13: pulled up		very high speed	JTMS-SWDIO
 *  B4: pulled up						NJTRST
 *  B3: 				very high speed	JTDO/T RACES WO
 */
#define USER_SW	PC13	/* can be configured for PA0 */
#define LED1	PB0		/* can be configured for PA5 */
#define LED2	PB7		/* */
#define LED3	PB14	/* */

#define RED_PIN		0
#define BLUE_PIN	7
#define GREEN_PIN	14
#define BUTTON_PIN	13
/*****************************************************************************/
/*****************************************************************************/

#endif
