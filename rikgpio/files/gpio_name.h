#ifndef GPIO_NAME_H
#define GPIO_NAME_H

/*Объявления портов ввода/вывода системной платы Рикор*/

//Names
#define FM_SLPS4 					"GPIOG3"
#define FM_SLPS3 					"GPIOG2"

#define FM_MEM_THERM_EVENT 			"GPIOP7"
#define FM_PCH_BMC_THERMTRIP		"GPIOP6"
#define FM_CPU_CATERR				"GPIOP5"
#define FM_CPU_ERR2					"GPIOP4"
#define IRQ_SERIAL					"GPIOP3"
#define FM_BMC_MIC_MUX_RST			"GPIOP2"
#define FM_BMC_PCH_SMI_LPC			"GPIOP1"

#define SPEAKER_BMC					"GPIOD7"
#define FP_ID_LED					"GPIOD6"
#define FP_ID_BTN					"GPIOD5"
#define FP_NMI_BTN					"GPIOD4"
#define FM_BMC_PWRBTN_OUT			"GPIOD3"
#define FM_BMC_PWR_BTN				"GPIOD2"
#define FM_NMI_EVENT				"GPIOD0"

#define FM_CPU1_MEMGH_MEMHOT		"GPIOC5"
#define FM_CPU1_MEMEF_MEMHOT		"GPIOC4"
#define FM_CPU0_MEMCD_MEMHOT		"GPIOC3"
#define FM_CPU0_MEMAB_MEMHOT		"GPIOC2"

#define FM_BMC_ONCTL				"GPIOY3"

#define FP_LED_STATUS_AMBER			"GPIOQ7"
#define FM_INTRUDER_HDR				"GPIOQ6"
#define FM_BMC_PCH_SCI_LPC			"GPIOQ5"
#define FP_LED_STATUS_GREEN			"GPIOQ4"

#define FM_PS_PWROK					"GPIOE6"
#define FM_BMC_FLASH_WP				"GPIOE5"
#define FM_BIOS_POST_CMPL			"GPIOE4"
#define IRQ_SML0_ALERT_N			"GPIOE3"
#define FM_SMI_ACTIVE				"GPIOE2"
#define FM_FORCE_BMC_UPDATE			"GPIOE1"
#define FM_CPU1_DISABLE				"GPIOE0"

#define FP_PWR_BTN_MUX_N			"GPIOR7"
#define FM_BMC_PWR_BTN_N			"GPIOR6"
#define RST_BMC_RSTBTN_OUT_N		"GPIOR5"
#define FP_RST_BTN_N				"GPIOR4"

//Directions
//0 - input
//1 - output
#define FM_SLPS4_DIR 				0
#define FM_SLPS3_DIR 				0

#define FM_MEM_THERM_EVENT_DIR 		0
#define FM_PCH_BMC_THERMTRIP_DIR	0
#define FM_CPU_CATERR_DIR			0
#define FM_CPU_ERR2_DIR				0
#define IRQ_SERIAL_DIR				0
#define FM_BMC_MIC_MUX_RST_DIR		1
#define FM_BMC_PCH_SMI_LPC_DIR		0		//1 -по идее должен быть output - TODO

#define SPEAKER_BMC_DIR				1
#define FP_ID_LED_DIR				1
#define FP_ID_BTN_DIR				0
#define FP_NMI_BTN_DIR				0
#define FM_BMC_PWRBTN_OUT_DIR		0		//1 -по идее должен быть output - TODO
#define FM_BMC_PWR_BTN_DIR			0
#define FM_NMI_EVENT_DIR			0

#define FM_CPU1_MEMGH_MEMHOT_DIR	0
#define FM_CPU1_MEMEF_MEMHOT_DIR	0
#define FM_CPU0_MEMCD_MEMHOT_DIR	0
#define FM_CPU0_MEMAB_MEMHOT_DIR	0

#define FM_BMC_ONCTL_DIR			1		//1 -по идее должен быть output - TODO

#define FP_LED_STATUS_AMBER_DIR		1
#define FM_INTRUDER_HDR_DIR			0
#define FM_BMC_PCH_SCI_LPC_DIR		0
#define FP_LED_STATUS_GREEN_DIR		1

#define FM_PS_PWROK_DIR				0
#define FM_BMC_FLASH_WP_DIR			1
#define FM_BIOS_POST_CMPL_DIR		0
#define IRQ_SML0_ALERT_N_DIR		0
#define FM_SMI_ACTIVE_DIR			0
#define FM_FORCE_BMC_UPDATE_DIR		0
#define FM_CPU1_DISABLE_DIR			0		//1 -по идее должен быть output - TODO

#define FP_PWR_BTN_MUX_N_DIR		0
#define FM_BMC_PWR_BTN_N_DIR		1	
#define RST_BMC_RSTBTN_OUT_N_DIR	1	
#define FP_RST_BTN_N_DIR			1	


#endif	//GPIO_NAME_H
