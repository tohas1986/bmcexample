/********************************************************************************
* File Name     : linux/arch/arm/plat-aspeed/dev-i2c.c
* Author        : Ryan chen
* Description   : ASPEED I2C Device
*
* Copyright (C) ASPEED Technology Inc.
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by the Free Software Foundation;
* either version 2 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,  but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

* History      :
*    1. 2012/07/30 ryan chen create this file
*
********************************************************************************/

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <asm/io.h>
#include <linux/gpio.h>

#ifdef CONFIG_COLDFIRE
#include "../../arm/plat-aspeed/include/plat/devs.h"
#include "../../arm/mach-aspeed/include/mach/irqs.h"
#include "../../arm/mach-aspeed/include/mach/ast1010_platform.h"
#else
#include <mach/irqs.h>
#include <mach/platform.h>
#include <plat/ast_i2c.h>
#include <plat/devs.h>
#include <plat/regs-iic.h>
#include <plat/ast-scu.h>
#endif
/* --------------------------------------------------------------------
 *  I2C
 * -------------------------------------------------------------------- */
#ifdef AST_I2C_DEBUG
#define I2CDBUG(fmt, args...) printk("%s() " fmt, __FUNCTION__, ## args)
#else
#define I2CDBUG(fmt, args...)
#endif

#if defined(CONFIG_I2C_AST) || defined(CONFIG_I2C_AST_MODULE)

static struct ast_i2c_driver_data ast_i2c_data = {
	.bus_clk = 100000,		//bus clock 100KHz
	.master_dma = MASTER_XFER_MODE,
	.slave_dma = SLAVE_XFER_MODE,
	.request_pool_buff_page = request_pool_buff_page,
	.free_pool_buff_page = free_pool_buff_page,
#ifdef CONFIG_AST_I2C_SLAVE_EEPROM
	.slave_xfer = i2c_slave_xfer,
	.slave_init = i2c_slave_init,
#endif
	.get_i2c_clock = ast_get_pclk,
};

static struct ast_i2c_driver_data ast_i2c_data_1M = {
	.bus_clk = 1000000,		//bus clock 1M
	.master_dma = MASTER_XFER_MODE,
	.slave_dma = SLAVE_XFER_MODE,
	.request_pool_buff_page = request_pool_buff_page,
	.free_pool_buff_page = free_pool_buff_page,
#ifdef CONFIG_AST_I2C_SLAVE_EEPROM
	.slave_xfer = i2c_slave_xfer,
	.slave_init = i2c_slave_init,
#endif
	.get_i2c_clock = ast_get_pclk,
};

static struct ast_i2c_driver_data ast_i2c_data_400K = {
	.bus_clk = 400000,		//bus clock 400KHz
	.master_dma = MASTER_XFER_MODE,
	.slave_dma = SLAVE_XFER_MODE,
	.request_pool_buff_page = request_pool_buff_page,
	.free_pool_buff_page = free_pool_buff_page,
#ifdef CONFIG_AST_I2C_SLAVE_EEPROM
	.slave_xfer = i2c_slave_xfer,
	.slave_init = i2c_slave_init,
#endif
	.get_i2c_clock = ast_get_pclk,
};

static u64 ast_i2c_dma_mask = 0xffffffffUL;
static struct resource ast_i2c_dev0_resources[] = {
	[0] = {
		.start = AST_I2C_DEV0_BASE,
		.end = AST_I2C_DEV0_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV0,
		.end = IRQ_I2C_DEV0,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev0_device = {
	.name = "ast-i2c",
	.id = 0,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev0_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev0_resources),
};

static struct resource ast_i2c_dev1_resources[] = {
	[0] = {
		.start = AST_I2C_DEV1_BASE,
		.end = AST_I2C_DEV1_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV1,
		.end = IRQ_I2C_DEV1,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev1_device = {
	.name = "ast-i2c",
	.id = 1,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev1_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev1_resources),
};

struct platform_device ast_i2c_dev1_device_1M = {
	.name = "ast-i2c",
	.id = 1,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data_1M,
	},
	.resource = ast_i2c_dev1_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev1_resources),
};

static struct resource ast_i2c_dev2_resources[] = {
	[0] = {
		.start = AST_I2C_DEV2_BASE,
		.end = AST_I2C_DEV2_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV2,
		.end = IRQ_I2C_DEV2,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev2_device = {
	.name = "ast-i2c",
	.id = 2,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev2_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev2_resources),
};

static struct resource ast_i2c_dev3_resources[] = {
	[0] = {
		.start = AST_I2C_DEV3_BASE,
		.end = AST_I2C_DEV3_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV3,
		.end = IRQ_I2C_DEV3,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev3_device = {
	.name = "ast-i2c",
	.id = 3,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev3_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev3_resources),
};

struct platform_device ast_i2c_dev3_device_1M = {
	.name = "ast-i2c",
	.id = 3,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data_1M,
	},
	.resource = ast_i2c_dev3_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev3_resources),
};

#if defined(AST_I2C_DEV4_BASE)
static struct resource ast_i2c_dev4_resources[] = {
	[0] = {
		.start = AST_I2C_DEV4_BASE,
		.end = AST_I2C_DEV4_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV4,
		.end = IRQ_I2C_DEV4,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev4_device = {
	.name = "ast-i2c",
	.id = 4,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev4_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev4_resources),
};

struct platform_device ast_i2c_dev4_device_400K = {
	.name = "ast-i2c",
	.id = 4,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data_400K,
	},
	.resource = ast_i2c_dev4_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev4_resources),
};
#endif

#if defined(AST_I2C_DEV5_BASE)
static struct resource ast_i2c_dev5_resources[] = {
	[0] = {
		.start = AST_I2C_DEV5_BASE,
		.end = AST_I2C_DEV5_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV5,
		.end = IRQ_I2C_DEV5,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev5_device = {
	.name = "ast-i2c",
	.id = 5,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev5_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev5_resources),
};

struct platform_device ast_i2c_dev5_device_1M = {
	.name = "ast-i2c",
	.id = 5,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data_1M,
	},
	.resource = ast_i2c_dev5_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev5_resources),
};
#endif

#if defined(AST_I2C_DEV6_BASE)
static struct resource ast_i2c_dev6_resources[] = {
	[0] = {
		.start = AST_I2C_DEV6_BASE,
		.end = AST_I2C_DEV6_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV6,
		.end = IRQ_I2C_DEV6,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev6_device = {
	.name = "ast-i2c",
	.id = 6,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev6_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev6_resources),
};
#endif

#if defined(AST_I2C_DEV7_BASE)
static struct resource ast_i2c_dev7_resources[] = {
	[0] = {
		.start = AST_I2C_DEV7_BASE,
		.end = AST_I2C_DEV7_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV7,
		.end = IRQ_I2C_DEV7,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev7_device = {
	.name = "ast-i2c",
	.id = 7,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev7_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev7_resources),
};

struct platform_device ast_i2c_dev7_device_1M = {
	.name = "ast-i2c",
	.id = 7,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data_1M,
	},
	.resource = ast_i2c_dev7_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev7_resources),
};
#endif

#if defined(AST_I2C_DEV8_BASE)
static struct resource ast_i2c_dev8_resources[] = {
	[0] = {
		.start = AST_I2C_DEV8_BASE,
		.end = AST_I2C_DEV8_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV8,
		.end = IRQ_I2C_DEV8,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev8_device = {
	.name = "ast-i2c",
	.id = 8,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev8_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev8_resources),
};
#endif

#if defined(AST_I2C_DEV9_BASE)
static struct resource ast_i2c_dev9_resources[] = {
	[0] = {
		.start = AST_I2C_DEV9_BASE,
		.end = AST_I2C_DEV9_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV9,
		.end = IRQ_I2C_DEV9,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev9_device = {
	.name = "ast-i2c",
	.id = 9,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev9_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev9_resources),
};
#endif

#if defined(AST_I2C_DEV10_BASE)
static struct resource ast_i2c_dev10_resources[] = {
	[0] = {
		.start = AST_I2C_DEV10_BASE,
		.end = AST_I2C_DEV10_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV10,
		.end = IRQ_I2C_DEV10,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev10_device = {
	.name = "ast-i2c",
	.id = 10,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev10_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev10_resources),
};
#endif

#if defined(AST_I2C_DEV11_BASE)
static struct resource ast_i2c_dev11_resources[] = {
	[0] = {
		.start = AST_I2C_DEV11_BASE,
		.end = AST_I2C_DEV11_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV11,
		.end = IRQ_I2C_DEV11,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev11_device = {
	.name = "ast-i2c",
	.id = 11,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev11_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev11_resources),
};
#endif

#if defined(AST_I2C_DEV12_BASE)
static struct resource ast_i2c_dev12_resources[] = {
	[0] = {
		.start = AST_I2C_DEV12_BASE,
		.end = AST_I2C_DEV12_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV12,
		.end = IRQ_I2C_DEV12,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev12_device = {
	.name = "ast-i2c",
	.id = 12,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev12_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev12_resources),
};
#endif

#if defined(AST_I2C_DEV13_BASE)
static struct resource ast_i2c_dev13_resources[] = {
	[0] = {
		.start = AST_I2C_DEV13_BASE,
		.end = AST_I2C_DEV13_BASE + SZ_64 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C_DEV13,
		.end = IRQ_I2C_DEV13,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ast_i2c_dev13_device = {
	.name = "ast-i2c",
	.id = 13,
	.dev = {
		.dma_mask = &ast_i2c_dma_mask,
		.coherent_dma_mask = 0xffffffff,
		.platform_data = &ast_i2c_data,
	},
	.resource = ast_i2c_dev13_resources,
	.num_resources = ARRAY_SIZE(ast_i2c_dev13_resources),
};
#endif

/*--------- I2C Board devices ------------*/
#if defined(CONFIG_FBTP) || defined(CONFIG_PWNEPTUNE)
static struct i2c_board_info ast_i2c_board_info_0[] __initdata = {
	// SMBus for LAN

	// U5D1, CPU0, PIROM, 0xA0

	// U2D1, CPU1, PIROM, 0xA2

	// J1C1, Airmax ConnB, FRU 0xA8, Temp 0x98

	// Can probe: 0xA0, 0xA2
	// TODO: the PIROM supports only smbus-read/write a single byte
	//  might need to write a driver or library function
};

static struct i2c_board_info ast_i2c_board_info_1[] __initdata = {
	// SMBus for SlotX24 devices

	// J9F1, HSCE8 200, NA

	// J1T1, HSEC8 60, NA

	// EU9E4, P17C9X1172, 0x6A

	// U8D7, CPLD, UART, 0x8C

	//TODO: probed 0x40 and 0xE2 only
};

static struct i2c_board_info ast_i2c_board_info_2[] __initdata = {
#if 0
	// SMBus for OCP LAN

	// J9B3, Mezz A connector
	// NIC: 0xE0, 0xC8
	// Temp: 0x3E
	// FRU: None

	//TODO: probed 0x2C only
#endif
};

/*
 * Under I2C Dev 3
 */
static struct i2c_board_info ast_i2c_board_info_3[] __initdata = {
	// SMBus for Host interface

	// EU8E1, CKMNG+, 0xD0

	// EU4C4, DB1200ZL, 0xD8

	// J8B1, ME Debug, NA

	// U2M3, Board ID EEPROM, 0xA8(ONLY for BIOS?)

	// JPA3, XDP, N/A

	// PCH, SMT1 0x90, Slave 0x88

	// TODO: Probed 0x10, 0x88, 0x90, 0xA8, 0xD0, 0xD8
};
/*
 * Under I2C Dev 4
 */
static struct i2c_board_info ast_i2c_board_info_4[] __initdata = {
	// SMBus for SML0

	// EU9E1, I210, 0xC6

	// PCH, SML0, SMT2, 0x2C

	// TODO: probed 0x2C
};
/*
 * Under I2C Dev 5
 */
static struct i2c_board_info ast_i2c_board_info_5[] __initdata = {
	// SMBus for VR Devices

	// EU1F3, PXM1310B, 0x0C(found:cpu1/vddqGHJ)

	// EU1B1, PXM1310B, 0x04(cpu1/vddqKLM)

	// EU7A5, PXM1310B, 0x14(found: cpu0/vddqDEF)

	// EU8A1, PXE1110J, 0xD0(found: PCH/pvnn)

	// J4B2, MCP CPU1, N/A

	// EU4D2, PXE1610B, 0x90(found: cpu0/vccIn)

	// EU4D3, PXE1110J, 0xB4(cpu1/vccIO)

	// EU1C2, PXE1610B, 0xB0(cpu1/vccIn)

	// EU7F1, PXM1310B, 0x1C(found: CPU0/vddqABC)

	// EU3N1, PXE1110J, 0x94(found: cpu0/vccIO)

	//TODO: Probed 0xC, 0x14, 0x1C, 0x90, 0x94, 0xD0
};

/*
 * Under I2C Dev 6
 */
static struct i2c_board_info ast_i2c_board_info_6[] __initdata = {
	// SMBus for Sensors

	// U8D7, CPLD:
	// 0x80: Programming, 0x82: I2C dev1, 0x84: I2C dev2, 0x86: I2C master rst#
  {
    I2C_BOARD_INFO("slb9645tt", 0x20),
  },

	// J8E1, TPM, 0xDC

	// U8D1, AT24C64, 0xA8
	      {
		I2C_BOARD_INFO("24c64", 0x54),
	      },

	// J9F1, HSCE8 200, N/A

	// U9B1, TMP421, 0x9C
	      {
		I2C_BOARD_INFO("tmp421", 0x4e),
	      },

	// U1D1, TMP421, 0x9E
	      {
		I2C_BOARD_INFO("tmp421", 0x4f),
	      },

	// EU9F1, ADC128D818, 0x1D

	//TODO: Probed 0x3A, 0x40, 0x80, 0x82, 0x86, 0x9C, 0x9e, 0xA8
};
/*
 * Under I2C Dev 7
 */
static struct i2c_board_info ast_i2c_board_info_7[] __initdata = {
	// SMBus for PMBUS

	// J1F1, AirMax conn A, FRU 0xA8, Temp 0x98


	// J1E3, 1X8 conn, NA

	// EU1D1, ADM1278, 0x22

/* ADM1278 is being accessed via ME, so remove this node for now
	{
		I2C_BOARD_INFO("adm1278", 0x11),
	},
*/

	// U2M2, PCA9517, EN

	// PCH, SML1, SMT3, 0x2E

	// TODO: probed 0x22
};
/*
 * Under I2C Dev 8
 */
static struct i2c_board_info ast_i2c_board_info_8[] __initdata = {
	// SMBus for OCP FRU devices

	// J8E4, Mezz C connector
	// FRU: 0xAE, Temp: 0x3E(0x98 rsvd)
	{
		I2C_BOARD_INFO("tmp421", 0x1f),
	},

	// J9B3, Mezz A connector
	// FRU: 0xA2, Temp: 0x3E(0x92 rsvd)

	// J8A4, MCP Sideband HFI
	// FRU: 0xA2, Temp: 0x3E(0x92 rsvd)

	//TODO: probed 0x3e, 0xc2
};

/*
 * Under I2C Dev 9
 */
static struct i2c_board_info ast_i2c_board_info_9[] __initdata = {
	// SMBus for Debug

	// U9A3, PCA9555, 0x4E

	// J9A5, USB3.0, NA
};

/*
 * Under I2C Dev 10
 */

static struct i2c_board_info ast_i2c_board_info_10[] __initdata = {
	// SMbus for PEHPCPU0
	// 0x42, 0x44

	// U5D1, CPU0, 0x22
};

/*
 * Under I2C Dev 11
 */
static struct i2c_board_info ast_i2c_board_info_11[] __initdata = {
	// SMbus for PEHPCPU1

	// J1C1, Airmax Conn B
	// 0xB6, 0xC6

	// U1B1, PCA9517, EN

	// U2D1, CPU1, 0x22
};

/*
 * Under I2C Dev 12
 */
static struct i2c_board_info ast_i2c_board_info_12[] __initdata = {
	// SMbus for PEHPCPU0

	// 0x46, 0x48

	// U1R1, PCA9517, EN

	// U5D1, CPU0, 0x22
};
#elif  CONFIG_FBTTN
//FBTTN start
static struct i2c_board_info ast_i2c_board_info_0_t5[] __initdata = {
  //HSC    , ADM1278   0x20
  //EEPROM , 24LC64    0xa0
  //Temp Sensor, TMP75 0x94
  {
		I2C_BOARD_INFO("adm1278", 0x10),
	},
  {
		I2C_BOARD_INFO("24c64", 0x50),
	},
  {
		I2C_BOARD_INFO("tmp75", 0x4a),
	},
  {
		I2C_BOARD_INFO("tmp75", 0x48),
	},
  {
		I2C_BOARD_INFO("tmp75", 0x4c),
  },

};

static struct i2c_board_info ast_i2c_board_info_0_t7[] __initdata = {
  //HSC    , ADM1278   0x20
  //EEPROM , 24LC64    0xa0
  //Temp Sensor, TMP75 0x94
  {
		I2C_BOARD_INFO("adm1278", 0x10),
	},
  {
		I2C_BOARD_INFO("24c64", 0x50),
	},
  {
		I2C_BOARD_INFO("tmp75", 0x4a),
	},
};

static struct i2c_board_info ast_i2c_board_info_1[] __initdata = {
  // IOC, Type7 (t7) 0x0a
};

static struct i2c_board_info ast_i2c_board_info_2[] __initdata = {
  //to Local SCC
};

static struct i2c_board_info ast_i2c_board_info_3[] __initdata = {
  // To BIC Mono Lake 0x40
};

static struct i2c_board_info ast_i2c_board_info_4[] __initdata = {
  // Mezz C connector -> OCP MEZZ
  {
		I2C_BOARD_INFO("24c64", 0x51),
  },
};

static struct i2c_board_info ast_i2c_board_info_5[] __initdata = {
  // DPB MISC TCA9555 0x48
  // ADM1278, 0x20 (8BIT) -> ML HSC
  {
		I2C_BOARD_INFO("adm1278", 0x10),
	},
  {
    I2C_BOARD_INFO("pca9555", 0x24),
  },
};

static struct i2c_board_info ast_i2c_board_info_6[] __initdata = {

	//Fan TACT, MXA31790
	//DPB HSC , ADM1278

    // DPB
	// ADM1278, 0x20 (8BIT)
	// max31790, 0x40 (8bit)
        //{
		//I2C_BOARD_INFO("adm1278", 0x10),
		// },
		// {
		//I2C_BOARD_INFO("max31790", 0x20),
		// },

};

static struct i2c_board_info ast_i2c_board_info_7[] __initdata = {
//M2
};

static struct i2c_board_info ast_i2c_board_info_8[] __initdata = {
//M2
};

static struct i2c_board_info ast_i2c_board_info_9[] __initdata = {
//IPMB SCC Local
};

static struct i2c_board_info ast_i2c_board_info_10[] __initdata = {
//REMOTE SCC IPMB
};

static struct i2c_board_info ast_i2c_board_info_11[] __initdata = {
//DEBUG Card i2c
//         {
//		I2C_BOARD_INFO("pca9555", 0x27),
//		 },
};

static struct i2c_board_info ast_i2c_board_info_12[] __initdata = {
  //MEZZ OOB
  //Get MEZZ TMP421
  {
		I2C_BOARD_INFO("tmp421", 0x1f),
  },
};

static struct i2c_board_info ast_i2c_board_info_13[] __initdata = {
  // TPM
  {
    I2C_BOARD_INFO("slb9645tt", 0x20),
  },
};

//end for FBTTN
#elif defined(CONFIG_YOSEMITE)

//Under I2C Dev 0
static struct i2c_board_info ast_i2c_board_info_0[] __initdata = {
  // Slot#0 NIC sideband
};

//Under I2C Dev 1
static struct i2c_board_info ast_i2c_board_info_1[] __initdata = {
  // Slot#0 IPMB interface
};

//Under I2C Dev 2
static struct i2c_board_info ast_i2c_board_info_2[] __initdata = {
  // Slot#1 NIC sideband
};


//Under I2C Dev 3
static struct i2c_board_info ast_i2c_board_info_3[] __initdata = {
  // Slot#1 IPMB interface
};

//Under I2C Dev 4
static struct i2c_board_info ast_i2c_board_info_4[] __initdata = {
  // Slot#2 NIC sideband
};

//Under I2C Dev 5
static struct i2c_board_info ast_i2c_board_info_5[] __initdata = {
  // Slot#2 IPMB interface
};

//Under I2C Dev 6
static struct i2c_board_info ast_i2c_board_info_6[] __initdata = {
  // Slot#3 NIC sideband
};

//Under I2C Dev 7
static struct i2c_board_info ast_i2c_board_info_7[] __initdata = {
  // Slot#3 IPMB interface
};

//Under I2C Dev 8
static struct i2c_board_info ast_i2c_board_info_8[] __initdata = {
  // FRUID
  // {
  //   I2C_BOARD_INFO("24c64", 0x51),
  // },
};

//Under I2C Dev 9
static struct i2c_board_info ast_i2c_board_info_9[] __initdata = {
  // Inlet and Outlet temp. sensors
  // {
  //   I2C_BOARD_INFO("tmp421", 0x4e),
  // },
  // {
  //   I2C_BOARD_INFO("tmp421", 0x4f),
  // },
};

//Under I2C Dev 10
static struct i2c_board_info ast_i2c_board_info_10[] __initdata = {
  // Hotswap Sensor
  // {
  //   I2C_BOARD_INFO("adm1278", 0x40),
  // },
};

//Under I2C Dev 11
static struct i2c_board_info ast_i2c_board_info_11[] __initdata = {
  // Mezz Card LAN_SMB bus (PHY, Temp. Sensor)
  //{
    //I2C_BOARD_INFO("tmp75", 0x1f),
  //},
};

//Under I2C Dev 12
static struct i2c_board_info ast_i2c_board_info_12[] __initdata = {
  // Mezz Card Mezz_SMB bus (FRUID, GPIO expander, QSFP+)
  // {
  //   I2C_BOARD_INFO("24c64", 0x51),
  // },
};

/* end of CONFIG_YOSEMITE */
#elif defined(CONFIG_LIGHTNING)
//FBLTN start
static struct i2c_board_info __initdata ast_i2c_board_info_0[] = {
};
//Under I2C Dev 1
static struct i2c_board_info __initdata ast_i2c_board_info_1[] = {
};

//Under I2C Dev 2
static struct i2c_board_info __initdata ast_i2c_board_info_2[] = {
};

//Under I2C Dev 3
static struct i2c_board_info __initdata ast_i2c_board_info_3[] = {
};

//Under I2C Dev 4
static struct i2c_board_info __initdata ast_i2c_board_info_4[] = {
	// PEB FRUID (0xA0)
	{
		I2C_BOARD_INFO("24c64", 0x50),
	},
	// PEB RTC PCF8563 (0xA2)
	{
		I2C_BOARD_INFO("pcf8563", 0x51),
	},

};

//Under I2C Dev 5
static struct i2c_board_info __initdata ast_i2c_board_info_5[] = {
	{
		I2C_BOARD_INFO("24c64", 0x51),
	},
	// FCB LED Driver (0xC0)
	{
		I2C_BOARD_INFO("pca9551", 0x60),
	},
};

//Under I2C Dev 6
static struct i2c_board_info __initdata ast_i2c_board_info_6[] = {
	// PDPB Temp Sensor (0x92)
	  {
	    I2C_BOARD_INFO("tmp75", 0x49),
	  },
	  // PDPB Temp Sensor (0x94)
	  {
	    I2C_BOARD_INFO("tmp75", 0x4a),
	  },
	  // PDPB Temp Sensor (0x96)
	  {
	    I2C_BOARD_INFO("tmp75", 0x4b),
	  },
	  // PDPB Temp Sensor (0x98)
	  {
	    I2C_BOARD_INFO("tmp75", 0x4c),
	  },
	  // PDPB FRUID (0xA2)
	  {
	    I2C_BOARD_INFO("24c64", 0x51),
	  },
};

//Under I2C Dev 7
static struct i2c_board_info __initdata ast_i2c_board_info_7[] = {
};

//Under I2C Dev 8
static struct i2c_board_info __initdata ast_i2c_board_info_8[] = {
};

//Under I2C Dev 9
static struct i2c_board_info __initdata ast_i2c_board_info_9[] = {
};

//Under I2C Dev 10
static struct i2c_board_info __initdata ast_i2c_board_info_10[] = {
};

//Under I2C Dev 11
static struct i2c_board_info __initdata ast_i2c_board_info_11[] = {
};

//Under I2C Dev 12
static struct i2c_board_info __initdata ast_i2c_board_info_12[] = {
};

//Under I2C Dev 13
static struct i2c_board_info __initdata ast_i2c_board_info_13[] = {
};

/* end of defined(CONFIG_LIGHTNING) */


#else
//AST EVB I2C Device
static struct i2c_board_info __initdata ast_i2c_board_info_0[] = {
	{
		I2C_BOARD_INFO("ddc", 0x50),
	},
#if defined(CONFIG_ARCH_AST3200)
	{
		.type	= "cat66121_hdmi",
		.addr	= 0x4C,
		.flags	= 0,
		.irq		= IRQ_GPIOB0,
//		.platform_data	= &it66121_hdmi0_pdata,
	},
	{
		.type	= "cat66121_hdmi",
		.addr	= 0x4D,
		.flags	= 1,
		.irq		= IRQ_GPIOB1,
//		.platform_data	= &it66121_hdmi1_pdata,
	},
#endif
};

static struct i2c_board_info __initdata ast_i2c_board_info_1[] = {
#if defined(CONFIG_ARCH_AST3200)
	{
		.type	= "cat66121_hdmi",
		.addr	= 0x4C,
		.flags	= 0,
		.irq		= IRQ_GPIOB2,
//		.platform_data 	= &it66121_hdmi2_pdata,
	},
	{
		.type	= "cat66121_hdmi",
		.addr	= 0x4D,
		.flags	= 1,
		.irq		= IRQ_GPIOB3,
//		.platform_data 	= &it66121_hdmi3_pdata,
	},
#endif
};

static struct i2c_board_info __initdata ast_i2c_board_info_2[] = {
};

//Under I2C Dev 3
static struct i2c_board_info __initdata ast_i2c_board_info_3[] = {
	{
		I2C_BOARD_INFO("24c08", 0x50),
	},
};
//Under I2C Dev 8
static struct i2c_board_info __initdata ast_i2c_board_info_7[] = {
	{
		I2C_BOARD_INFO("lm75", 0x4d),
	}
};

#endif
/*-------------------------------------*/
#if defined(CONFIG_FBTP) || defined(CONFIG_PWNEPTUNE)
void __init ast_add_device_i2c(void)
{
	/* I2C Multi-Pin */
	ast_scu_multi_func_i2c();

	ast_i2c_data.reg_gr = ioremap(AST_I2C_BASE, 4*SZ_16);
	if (!ast_i2c_data.reg_gr) {
		printk(KERN_ERR "ast_add_device_i2c ERROR \n");
		return;
	}

        ast_i2c_data_400K.reg_gr = ast_i2c_data.reg_gr;// 400KHz reg_gr setting

	platform_device_register(&ast_i2c_dev0_device);
	platform_device_register(&ast_i2c_dev1_device);
	platform_device_register(&ast_i2c_dev2_device);
	platform_device_register(&ast_i2c_dev3_device);
	platform_device_register(&ast_i2c_dev4_device_400K);
	platform_device_register(&ast_i2c_dev5_device);
	platform_device_register(&ast_i2c_dev6_device);
	platform_device_register(&ast_i2c_dev7_device);
	platform_device_register(&ast_i2c_dev8_device);
	platform_device_register(&ast_i2c_dev9_device);
	platform_device_register(&ast_i2c_dev10_device);
	platform_device_register(&ast_i2c_dev11_device);
	platform_device_register(&ast_i2c_dev12_device);
	platform_device_register(&ast_i2c_dev13_device);

	i2c_register_board_info(0, ast_i2c_board_info_0,
			ARRAY_SIZE(ast_i2c_board_info_0));
	i2c_register_board_info(1, ast_i2c_board_info_1,
			ARRAY_SIZE(ast_i2c_board_info_1));
	i2c_register_board_info(2, ast_i2c_board_info_2,
			ARRAY_SIZE(ast_i2c_board_info_2));
	i2c_register_board_info(3, ast_i2c_board_info_3,
			ARRAY_SIZE(ast_i2c_board_info_3));
	i2c_register_board_info(4, ast_i2c_board_info_4,
			ARRAY_SIZE(ast_i2c_board_info_4));
	i2c_register_board_info(5, ast_i2c_board_info_5,
			ARRAY_SIZE(ast_i2c_board_info_5));
	i2c_register_board_info(6, ast_i2c_board_info_6,
			ARRAY_SIZE(ast_i2c_board_info_6));
	i2c_register_board_info(7, ast_i2c_board_info_7,
			ARRAY_SIZE(ast_i2c_board_info_7));
	i2c_register_board_info(8, ast_i2c_board_info_8,
			ARRAY_SIZE(ast_i2c_board_info_8));
	i2c_register_board_info(9, ast_i2c_board_info_9,
			ARRAY_SIZE(ast_i2c_board_info_9));
	i2c_register_board_info(10, ast_i2c_board_info_10,
			ARRAY_SIZE(ast_i2c_board_info_10));
	i2c_register_board_info(11, ast_i2c_board_info_11,
			ARRAY_SIZE(ast_i2c_board_info_11));
	i2c_register_board_info(12, ast_i2c_board_info_12,
			ARRAY_SIZE(ast_i2c_board_info_12));
}

#elif CONFIG_FBTTN
void __init ast_add_device_i2c(void)
{
	int sys_type = 0;

	/* I2C Multi-Pin */
	ast_scu_multi_func_i2c();

	ast_i2c_data.reg_gr = ioremap(AST_I2C_BASE, 4*SZ_16);
	if (!ast_i2c_data.reg_gr) {
		printk(KERN_ERR "ast_add_device_i2c ERROR \n");
		return;
	}

    ast_i2c_data_1M.reg_gr = ast_i2c_data.reg_gr;// 1MHz reg_gr setting

	platform_device_register(&ast_i2c_dev0_device);
	platform_device_register(&ast_i2c_dev1_device);
	platform_device_register(&ast_i2c_dev2_device);
	platform_device_register(&ast_i2c_dev3_device_1M);
	platform_device_register(&ast_i2c_dev4_device);
	platform_device_register(&ast_i2c_dev5_device);
	platform_device_register(&ast_i2c_dev6_device);
	platform_device_register(&ast_i2c_dev7_device);
	platform_device_register(&ast_i2c_dev8_device);
	platform_device_register(&ast_i2c_dev9_device);
	platform_device_register(&ast_i2c_dev10_device);
	platform_device_register(&ast_i2c_dev11_device);
	platform_device_register(&ast_i2c_dev12_device);
	platform_device_register(&ast_i2c_dev13_device);

	//System Type GPIOJ4~GPIOJ7, 0001 = M.2-based IOM (Type 5), 0010 = IOC-based IOM (Type 7)
	sys_type = (gpio_get_value(76) << 3) + (gpio_get_value(77) << 2)
			   + (gpio_get_value(78) << 1) + gpio_get_value(79);

	if(sys_type == 2) {
	//If sys_type(79) is 2, means System is Type 7
		i2c_register_board_info(0, ast_i2c_board_info_0_t7,
			ARRAY_SIZE(ast_i2c_board_info_0_t7));
	}
	else {
		i2c_register_board_info(0, ast_i2c_board_info_0_t5,
			ARRAY_SIZE(ast_i2c_board_info_0_t5));
	}

	i2c_register_board_info(1, ast_i2c_board_info_1,
			ARRAY_SIZE(ast_i2c_board_info_1));
	i2c_register_board_info(2, ast_i2c_board_info_2,
			ARRAY_SIZE(ast_i2c_board_info_2));
	i2c_register_board_info(3, ast_i2c_board_info_3,
			ARRAY_SIZE(ast_i2c_board_info_3));
	i2c_register_board_info(4, ast_i2c_board_info_4,
			ARRAY_SIZE(ast_i2c_board_info_4));
	i2c_register_board_info(5, ast_i2c_board_info_5,
			ARRAY_SIZE(ast_i2c_board_info_5));
	i2c_register_board_info(6, ast_i2c_board_info_6,
			ARRAY_SIZE(ast_i2c_board_info_6));
	i2c_register_board_info(7, ast_i2c_board_info_7,
			ARRAY_SIZE(ast_i2c_board_info_7));
	i2c_register_board_info(8, ast_i2c_board_info_8,
			ARRAY_SIZE(ast_i2c_board_info_8));
	i2c_register_board_info(9, ast_i2c_board_info_9,
			ARRAY_SIZE(ast_i2c_board_info_9));
	i2c_register_board_info(10, ast_i2c_board_info_10,
			ARRAY_SIZE(ast_i2c_board_info_10));
	i2c_register_board_info(11, ast_i2c_board_info_11,
			ARRAY_SIZE(ast_i2c_board_info_11));
	i2c_register_board_info(12, ast_i2c_board_info_12,
			ARRAY_SIZE(ast_i2c_board_info_12));
	i2c_register_board_info(13, ast_i2c_board_info_13,
			ARRAY_SIZE(ast_i2c_board_info_13));
}
#elif defined(CONFIG_YOSEMITE)
void __init ast_add_device_i2c(void)
{
	/* I2C Multi-Pin */
	ast_scu_multi_func_i2c();

	ast_i2c_data.reg_gr = ioremap(AST_I2C_BASE, 4*SZ_16);
	if (!ast_i2c_data.reg_gr) {
		printk(KERN_ERR "ast_add_device_i2c ERROR \n");
		return;
	}

  ast_i2c_data_1M.reg_gr = ast_i2c_data.reg_gr;// 1MHz reg_gr setting

	platform_device_register(&ast_i2c_dev0_device);
	platform_device_register(&ast_i2c_dev1_device_1M);
	platform_device_register(&ast_i2c_dev2_device);
	platform_device_register(&ast_i2c_dev3_device_1M);
	platform_device_register(&ast_i2c_dev4_device);
	platform_device_register(&ast_i2c_dev5_device_1M);
	platform_device_register(&ast_i2c_dev6_device);
	platform_device_register(&ast_i2c_dev7_device_1M);
	platform_device_register(&ast_i2c_dev8_device);
	// platform_device_register(&ast_i2c_dev9_device);
	// platform_device_register(&ast_i2c_dev10_device);
	// platform_device_register(&ast_i2c_dev11_device);
	// platform_device_register(&ast_i2c_dev12_device);
	// platform_device_register(&ast_i2c_dev13_device);

	i2c_register_board_info(0, ast_i2c_board_info_0,
		              ARRAY_SIZE(ast_i2c_board_info_0));
	i2c_register_board_info(1, ast_i2c_board_info_1,
                  ARRAY_SIZE(ast_i2c_board_info_1));
	i2c_register_board_info(2, ast_i2c_board_info_2,
                  ARRAY_SIZE(ast_i2c_board_info_2));
	i2c_register_board_info(3, ast_i2c_board_info_3,
                  ARRAY_SIZE(ast_i2c_board_info_3));
	i2c_register_board_info(4, ast_i2c_board_info_4,
                  ARRAY_SIZE(ast_i2c_board_info_4));
	i2c_register_board_info(5, ast_i2c_board_info_5,
                  ARRAY_SIZE(ast_i2c_board_info_5));
	i2c_register_board_info(6, ast_i2c_board_info_6,
                  ARRAY_SIZE(ast_i2c_board_info_6));
	i2c_register_board_info(7, ast_i2c_board_info_7,
                  ARRAY_SIZE(ast_i2c_board_info_7));
	i2c_register_board_info(8, ast_i2c_board_info_8,
		              ARRAY_SIZE(ast_i2c_board_info_8));
	// i2c_register_board_info(9, ast_i2c_board_info_9,
 //                  ARRAY_SIZE(ast_i2c_board_info_9));
	// i2c_register_board_info(10, ast_i2c_board_info_10,
 //                  ARRAY_SIZE(ast_i2c_board_info_10));
	// i2c_register_board_info(11, ast_i2c_board_info_11,
 //                  ARRAY_SIZE(ast_i2c_board_info_11));
	// i2c_register_board_info(12, ast_i2c_board_info_12,
 //                  ARRAY_SIZE(ast_i2c_board_info_12));
}

#elif defined(CONFIG_LIGHTNING)
void __init ast_add_device_i2c(void)
{
	/* I2C Multi-Pin */
	ast_scu_multi_func_i2c();

	ast_i2c_data.reg_gr = ioremap(AST_I2C_BASE, 4*SZ_16);
	if (!ast_i2c_data.reg_gr) {
		printk(KERN_ERR "ast_add_device_i2c ERROR \n");
		return;
	}

	platform_device_register(&ast_i2c_dev0_device);
	platform_device_register(&ast_i2c_dev1_device);
	platform_device_register(&ast_i2c_dev2_device);
	platform_device_register(&ast_i2c_dev3_device);
	platform_device_register(&ast_i2c_dev4_device);
	platform_device_register(&ast_i2c_dev5_device);
	platform_device_register(&ast_i2c_dev6_device);
	platform_device_register(&ast_i2c_dev7_device);
	platform_device_register(&ast_i2c_dev8_device);
	platform_device_register(&ast_i2c_dev9_device);
	platform_device_register(&ast_i2c_dev10_device);
	platform_device_register(&ast_i2c_dev11_device);
	platform_device_register(&ast_i2c_dev12_device);
	platform_device_register(&ast_i2c_dev13_device);

	i2c_register_board_info(0, ast_i2c_board_info_0,
			ARRAY_SIZE(ast_i2c_board_info_0));
	i2c_register_board_info(1, ast_i2c_board_info_1,
			ARRAY_SIZE(ast_i2c_board_info_1));
	i2c_register_board_info(2, ast_i2c_board_info_2,
			ARRAY_SIZE(ast_i2c_board_info_2));
	i2c_register_board_info(3, ast_i2c_board_info_3,
			ARRAY_SIZE(ast_i2c_board_info_3));
	i2c_register_board_info(4, ast_i2c_board_info_4,
			ARRAY_SIZE(ast_i2c_board_info_4));
	i2c_register_board_info(5, ast_i2c_board_info_5,
			ARRAY_SIZE(ast_i2c_board_info_5));
	i2c_register_board_info(6, ast_i2c_board_info_6,
			ARRAY_SIZE(ast_i2c_board_info_6));
	i2c_register_board_info(7, ast_i2c_board_info_7,
			ARRAY_SIZE(ast_i2c_board_info_7));
	i2c_register_board_info(8, ast_i2c_board_info_8,
			ARRAY_SIZE(ast_i2c_board_info_8));
	i2c_register_board_info(9, ast_i2c_board_info_9,
			ARRAY_SIZE(ast_i2c_board_info_9));
	i2c_register_board_info(10, ast_i2c_board_info_10,
			ARRAY_SIZE(ast_i2c_board_info_10));
	i2c_register_board_info(11, ast_i2c_board_info_11,
			ARRAY_SIZE(ast_i2c_board_info_11));
	i2c_register_board_info(12, ast_i2c_board_info_12,
			ARRAY_SIZE(ast_i2c_board_info_12));
}

#else

void __init ast_add_device_i2c(void)
{
	//I2C Multi-Pin
	ast_scu_multi_func_i2c();

	ast_i2c_data.reg_gr = ioremap(AST_I2C_BASE, 4*SZ_16);
	if (!ast_i2c_data.reg_gr) {
		printk("ast_add_device_i2c ERROR \n");
		return;
	}

	platform_device_register(&ast_i2c_dev0_device);
	platform_device_register(&ast_i2c_dev1_device);
	platform_device_register(&ast_i2c_dev2_device);
	platform_device_register(&ast_i2c_dev3_device);
	platform_device_register(&ast_i2c_dev4_device);
	platform_device_register(&ast_i2c_dev5_device);
	platform_device_register(&ast_i2c_dev6_device);
	platform_device_register(&ast_i2c_dev7_device);
	platform_device_register(&ast_i2c_dev8_device);

#if defined(AST_I2C_DEV9_BASE)
	platform_device_register(&ast_i2c_dev9_device);
#endif

#if defined(CONFIG_MMC_AST)
	//Due to share pin with SD
#else
#if defined(AST_I2C_DEV10_BASE)
	platform_device_register(&ast_i2c_dev10_device);
#endif

#if defined(AST_I2C_DEV11_BASE)
	platform_device_register(&ast_i2c_dev11_device);
#endif
#if defined(AST_I2C_DEV12_BASE)
	platform_device_register(&ast_i2c_dev12_device);
#endif
#if defined(AST_I2C_DEV13_BASE)
	platform_device_register(&ast_i2c_dev13_device);
#endif
#endif

	i2c_register_board_info(0, ast_i2c_board_info_0, ARRAY_SIZE(ast_i2c_board_info_0));
	i2c_register_board_info(1, ast_i2c_board_info_1, ARRAY_SIZE(ast_i2c_board_info_1));
	i2c_register_board_info(2, ast_i2c_board_info_2, ARRAY_SIZE(ast_i2c_board_info_2));
	i2c_register_board_info(3, ast_i2c_board_info_3, ARRAY_SIZE(ast_i2c_board_info_3));
	i2c_register_board_info(7, ast_i2c_board_info_7, ARRAY_SIZE(ast_i2c_board_info_7));
}

#endif

#else

void __init ast_add_device_i2c(void) {}

#endif
