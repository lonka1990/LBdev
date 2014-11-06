/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>

void lcd_clk_init(void);
void pio_init(void);
static void tc0c2_capture_initialize(void);
//void TC0C2_Handler(void);

/** Capture status*/
static uint32_t gs_ul_captured_ra;
static uint32_t gs_ul_captured_rb;

void TC0C2_Handler(void)
{
	//! [tc_capture_irq_handler_start]
	//! [tc_capture_irq_handler_status]
	if ((tc_get_status(TC, TC0C2_CHANNEL_CAPTURE) & TC_SR_LDRBS) == TC_SR_LDRBS) {

		//! [tc_capture_irq_handler_read_ra]
		gs_ul_captured_ra = tc_read_ra(TC, TC0C2_CHANNEL_CAPTURE);
		//! [tc_capture_irq_handler_read_ra]
		//! [tc_capture_irq_handler_read_rb]
		gs_ul_captured_rb = tc_read_rb(TC, TC0C2_CHANNEL_CAPTURE);
		//! [tc_capture_irq_handler_read_rb]
		pio_set(PIOA, PIO_PA23);
	}
}

int main (void)
{
	/*system clock is set to 64MHz*/
	sysclk_init();
	lcd_clk_init();
	pio_init();
	tc0c2_capture_initialize();
	
	while (1)
	{
	}
}

void lcd_clk_init(void)
{
	pio_set_peripheral(PIOA, PIO_PERIPH_B, PIO_PA17);
	
	/*Switch the Programmable Clock module PCK1 source clock to the MAIN Clock, with a prescaler of 2:*/
	pmc_switch_pck_to_pllack(PMC_PCK_1, PMC_PCK_PRES_CLK_4);
	
	/*Enable Programmable Clock module PCK1:*/
	pmc_enable_pck(PMC_PCK_1);
}

void pio_init(void)
{
	/*Enable the module clock to the PIOA peripheral*/
	pmc_enable_periph_clk(ID_PIOA);
	
	pio_set_output(PIOA, PIO_PA23, LOW, DISABLE, ENABLE);			// Set pin 23 direction on PIOA as output, default low level
	//pio_set_input(PIOA, PIO_PA16, PIO_PULLUP);						// Set pin 16 direction on PIOA as input, with pullup
}

/**
 * \brief Configure TC TC_CHANNEL_CAPTURE in capture operating mode.
 */
//! [tc_capture_init]
static void tc0c2_capture_initialize(void)
{
	/* Configure the PMC to enable the TC module */
	sysclk_enable_peripheral_clock(ID_TC0C2_CAPTURE);

	/* Init TC to capture mode. */
	tc_init(TC, TC0C2_CHANNEL_CAPTURE,
			TC_CMR_TCCLKS_TIMER_CLOCK3 /* Clock Selection */
			| TC_CMR_LDRA_RISING /* RA Loading: rising edge of TIOA */
			| TC_CMR_LDRB_FALLING /* RB Loading: falling edge of TIOA */
			| TC_CMR_ABETRG /* External Trigger: TIOA */
			| TC_CMR_ETRGEDG_FALLING /* External Trigger Edge: Falling edge */
	);
	
	//! [tc_capture_gpio]
	/** Configure PIO Pins for TC */
	ioport_set_pin_mode(PIN_TC0C2_CAPTURE, PIN_TC0C2_CAPTURE_MUX);
	/** Disable I/O to enable peripheral mode) */
	ioport_disable_pin(PIN_TC0C2_CAPTURE);
	//! [tc_capture_gpio]

	//! [tc_capture_init_irq]
	/** Configure TC interrupts for TC TC_CHANNEL_CAPTURE only */
	NVIC_DisableIRQ(TC0C2_IRQn);
	NVIC_ClearPendingIRQ(TC0C2_IRQn);
	NVIC_SetPriority(TC0C2_IRQn, 0);
	NVIC_EnableIRQ(TC0C2_IRQn);
	//! [tc_capture_init_irq]
	
	//! [tc_capture_init_module_irq]
	tc_enable_interrupt(TC, TC0C2_CHANNEL_CAPTURE, TC_IER_LDRBS);
	/* Start the timer counter on TC TC_CHANNEL_CAPTURE */
	//! [tc_capture_start_now]
	tc_start(TC, TC0C2_CHANNEL_CAPTURE);
	
	//tc_disable_interrupt(TC, TC_CHANNEL_CAPTURE, TC_IDR_LDRBS);
}