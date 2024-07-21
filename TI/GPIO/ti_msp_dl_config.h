/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA0
#define PWM_0_INST_IRQHandler                                   TIMA0_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                               125000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOB
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_8
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM25)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM25_PF_TIMA0_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOB
#define GPIO_PWM_0_C1_PIN                                          DL_GPIO_PIN_9
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM26)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM26_PF_TIMA0_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA1)
#define TIMER_0_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (62499U)




/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C0
#define I2C_0_INST_IRQHandler                                    I2C0_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C0_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                        DL_GPIO_PIN_28
#define GPIO_I2C_0_IOMUX_SDA                                      (IOMUX_PINCM3)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                       IOMUX_PINCM3_PF_I2C0_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                        DL_GPIO_PIN_31
#define GPIO_I2C_0_IOMUX_SCL                                      (IOMUX_PINCM6)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                       IOMUX_PINCM6_PF_I2C0_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_0_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOB
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_5
#define GPIO_UART_1_TX_PIN                                        DL_GPIO_PIN_17
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM18)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM39)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM18_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM39_PF_UART1_TX
#define UART_1_BAUD_RATE                                                (115200)
#define UART_1_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_1_FBRD_32_MHZ_115200_BAUD                                      (24)





/* Port definition for Pin Group GPIO_LEDS */
#define GPIO_LEDS_PORT                                                   (GPIOB)

/* Defines for LED_1: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_LEDS_LED_1_PIN                                     (DL_GPIO_PIN_22)
#define GPIO_LEDS_LED_1_IOMUX                                    (IOMUX_PINCM50)
/* Defines for LED_2: GPIOB.26 with pinCMx 57 on package pin 28 */
#define GPIO_LEDS_LED_2_PIN                                     (DL_GPIO_PIN_26)
#define GPIO_LEDS_LED_2_IOMUX                                    (IOMUX_PINCM57)
/* Defines for LED_3: GPIOB.27 with pinCMx 58 on package pin 29 */
#define GPIO_LEDS_LED_3_PIN                                     (DL_GPIO_PIN_27)
#define GPIO_LEDS_LED_3_IOMUX                                    (IOMUX_PINCM58)
/* Defines for S1: GPIOA.18 with pinCMx 40 on package pin 11 */
#define GPIO_KEYS_S1_PORT                                                (GPIOA)
// pins affected by this interrupt request:["S1"]
#define GPIO_KEYS_GPIOA_INT_IRQN                                (GPIOA_INT_IRQn)
#define GPIO_KEYS_GPIOA_INT_IIDX                (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_KEYS_S1_IIDX                                   (DL_GPIO_IIDX_DIO18)
#define GPIO_KEYS_S1_PIN                                        (DL_GPIO_PIN_18)
#define GPIO_KEYS_S1_IOMUX                                       (IOMUX_PINCM40)
/* Defines for S2: GPIOB.21 with pinCMx 49 on package pin 20 */
#define GPIO_KEYS_S2_PORT                                                (GPIOB)
// groups represented: ["GPIO_Encoders","GPIO_KEYS"]
// pins affected: ["M2_B0_TI1","M1_B3_TI1","M1_B2_TI2","S2"]
#define GPIO_MULTIPLE_GPIOB_INT_IRQN                            (GPIOB_INT_IRQn)
#define GPIO_MULTIPLE_GPIOB_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define GPIO_KEYS_S2_IIDX                                   (DL_GPIO_IIDX_DIO21)
#define GPIO_KEYS_S2_PIN                                        (DL_GPIO_PIN_21)
#define GPIO_KEYS_S2_IOMUX                                       (IOMUX_PINCM49)
/* Port definition for Pin Group GPIO_Encoders */
#define GPIO_Encoders_PORT                                               (GPIOB)

/* Defines for M2_B0_TI1: GPIOB.0 with pinCMx 12 on package pin 47 */
#define GPIO_Encoders_M2_B0_TI1_IIDX                         (DL_GPIO_IIDX_DIO0)
#define GPIO_Encoders_M2_B0_TI1_PIN                              (DL_GPIO_PIN_0)
#define GPIO_Encoders_M2_B0_TI1_IOMUX                            (IOMUX_PINCM12)
/* Defines for M2_B1_TI2: GPIOB.1 with pinCMx 13 on package pin 48 */
#define GPIO_Encoders_M2_B1_TI2_PIN                              (DL_GPIO_PIN_1)
#define GPIO_Encoders_M2_B1_TI2_IOMUX                            (IOMUX_PINCM13)
/* Defines for M1_B3_TI1: GPIOB.3 with pinCMx 16 on package pin 51 */
#define GPIO_Encoders_M1_B3_TI1_IIDX                         (DL_GPIO_IIDX_DIO3)
#define GPIO_Encoders_M1_B3_TI1_PIN                              (DL_GPIO_PIN_3)
#define GPIO_Encoders_M1_B3_TI1_IOMUX                            (IOMUX_PINCM16)
/* Defines for M1_B2_TI2: GPIOB.2 with pinCMx 15 on package pin 50 */
#define GPIO_Encoders_M1_B2_TI2_IIDX                         (DL_GPIO_IIDX_DIO2)
#define GPIO_Encoders_M1_B2_TI2_PIN                              (DL_GPIO_PIN_2)
#define GPIO_Encoders_M1_B2_TI2_IOMUX                            (IOMUX_PINCM15)
/* Port definition for Pin Group MPU6050 */
#define MPU6050_PORT                                                     (GPIOA)

/* Defines for MPU6050_SDA: GPIOA.8 with pinCMx 19 on package pin 54 */
#define MPU6050_MPU6050_SDA_PIN                                  (DL_GPIO_PIN_8)
#define MPU6050_MPU6050_SDA_IOMUX                                (IOMUX_PINCM19)
/* Defines for MPU6050_SCL: GPIOA.9 with pinCMx 20 on package pin 55 */
#define MPU6050_MPU6050_SCL_PIN                                  (DL_GPIO_PIN_9)
#define MPU6050_MPU6050_SCL_IOMUX                                (IOMUX_PINCM20)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
