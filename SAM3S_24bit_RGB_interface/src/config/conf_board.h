/**
 * \file
 *
 * \brief Board configuration.
 *
 * Copyright (c) 2012-2014 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/** Enable Com Port. */
#define CONF_BOARD_UART_CONSOLE


#  define BOARD_FREQ_SLCK_XTAL      (32768UL)
#  define BOARD_FREQ_SLCK_BYPASS    (32768UL)
#  define BOARD_FREQ_MAINCK_BYPASS  (12000000UL)
#  define BOARD_OSC_STARTUP_US      (15625UL)
#  define BOARD_FREQ_MAINCK_XTAL    (12000000UL)


/** PWM LED0 pin definitions. */
#define PIN_PWM_LED0_GPIO    PIO_PA19_IDX
#define PIN_PWM_LED0_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_LED0_CHANNEL PWM_CHANNEL_0

/** PWM LED1 pin definitions. */
#define PIN_PWM_LED1_GPIO    PIO_PA20_IDX
#define PIN_PWM_LED1_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_LED1_CHANNEL PWM_CHANNEL_1



/*************************///// Timer Counter 0 \\\\\*******************************/
//! [tc_define_peripheral]
/* Use TC Peripheral 0. */
#define TC             TC0
#define TC_PERIPHERAL  0
//! [tc_define_peripheral]

/*************************  Timer Counter 0 Channel 0 *******************************/
/* Use TC2_Handler for TC capture interrupt. */
#define TC0C0_Handler  TC0_Handler
#define TC0C0_IRQn     TC0_IRQn
//! [tc_define_irq_handler]
//! [tc_define_ch0]
/* Configure TC0 channel 2 as capture input. */
#define TC0C0_CHANNEL_CAPTURE		0
#define ID_TC0C0_CAPTURE			ID_TC0
#define CLOCK_MCK_div_2			TC_CMR_TCCLKS_TIMER_CLOCK1		//Master Clock divided by 2
#define CLOCK_MCK_div_8			TC_CMR_TCCLKS_TIMER_CLOCK2		//Master Clock divided by 8
#define CLOCK_MCK_div_32		TC_CMR_TCCLKS_TIMER_CLOCK3		//Master Clock divided by 32
#define CLOCK_MCK_div_128		TC_CMR_TCCLKS_TIMER_CLOCK4		//Master Clock divided by 128
#define CLOCK_MCK_SLCK			TC_CMR_TCCLKS_TIMER_CLOCK5		//Slow Clock
//! [tc_define_ch0]

/*************************  Timer Counter 0 Channel 1 *******************************/
//! [tc_define_ch1]
/* Configure TC0 channel 1 as waveform output. */
#define TC_CHANNEL_WAVEFORM 1
#define ID_TC_WAVEFORM      ID_TC1
#define PIN_TC_WAVEFORM     PIN_TC0_TIOA1
#define PIN_TC_WAVEFORM_MUX PIN_TC0_TIOA1_MUX

#define TC_WAVEFORM_TIMER_SELECTION TC_CMR_TCCLKS_TIMER_CLOCK4
#define TC_WAVEFORM_DIVISOR     128
#define TC_WAVEFORM_FREQUENCY   178
#define TC_WAVEFORM_DUTY_CYCLE  30
//! [tc_define_ch1]

/*************************  Timer Counter 0 Channel 2 *******************************/

/** Configure TC0 channel 2 as capture input. **/
#define PIN_TC0C2_TIOA2       (PIO_PA26_IDX)
#define PIN_TC0C2_TIOA2_MUX   (IOPORT_MODE_MUX_B)
#define TC0C2_CHANNEL_CAPTURE 2
#define ID_TC0C2_CAPTURE      ID_TC2
#define PIN_TC0C2_CAPTURE     PIN_TC0C2_TIOA2
#define PIN_TC0C2_CAPTURE_MUX PIN_TC0C2_TIOA2_MUX

/** Use TC2_Handler for TC capture interrupt**/
#define TC0C2_Handler  TC2_Handler
#define TC0C2_IRQn     TC2_IRQn


#endif /* CONF_BOARD_H_INCLUDED */
