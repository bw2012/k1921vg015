//-- Includes ------------------------------------------------------------------
#include <K1921VG015.h>
#include <stdint.h>
#include <stdio.h>
#include <system_k1921vg015.h>

#include "retarget.h"

//-- Defines -------------------------------------------------------------------
void TMR32_IRQHandler();

volatile uint32_t test = 0;

void Send_buff(char *a) {
    uint8_t i = 0;
    while ((i < 120) && (a[i] != 0)) {
        retarget_put_char(a[i]);
        i++;
    }
}

void BSP_led_init() {
    // Разрешаем тактирование GPIOC
    RCU->CGCFGAHB_bit.GPIOCEN = 1;
    // Включаем  GPIOC
    RCU->RSTDISAHB_bit.GPIOCEN = 1;
    GPIOC->OUTENSET = 1;
    GPIOC->DATAOUTSET = 1;
}

void TMR32_init(uint32_t period) {
    RCU->CGCFGAPB_bit.TMR32EN = 1;
    RCU->RSTDISAPB_bit.TMR32EN = 1;

    // Записываем значение периода в CAPCOM[0]
    TMR32->CAPCOM[0].VAL = period - 1;
    // Выбираем режим счета от 0 до значения CAPCOM[0]
    TMR32->CTRL_bit.MODE = 1;

    // Разрешаем прерывание по совпадению значения счетчика и CAPCOM[0]
    TMR32->IM = 2;

    // Настраиваем обработчик прерывания для TMR32
    PLIC_SetIrqHandler(Plic_Mach_Target, IsrVect_IRQ_TMR32, TMR32_IRQHandler);
    PLIC_SetPriority(IsrVect_IRQ_TMR32, 0x1);
    PLIC_IntEnable(Plic_Mach_Target, IsrVect_IRQ_TMR32);
}

//-- Peripheral init functions -------------------------------------------------
void periph_init() {
    BSP_led_init();
    SystemInit();
    SystemCoreClockUpdate();
    BSP_led_init();

    retarget_init();
    printf("K1921VG015 SYSCLK = %d MHz\n", (int)(SystemCoreClock / 1E6));
    printf("  UID[0] = 0x%X  UID[1] = 0x%X  UID[2] = 0x%X  UID[3] = 0x%X\n", (unsigned int)PMUSYS->UID[0], (unsigned int)PMUSYS->UID[1], (unsigned int)PMUSYS->UID[2], (unsigned int)PMUSYS->UID[3]);
    printf("  Start RunLeds\n");
}

//-- Main ----------------------------------------------------------------------
int main(void) {
    periph_init();
    TMR32_init(SystemCoreClock >> 2);

    test = 0;

    InterruptEnable();

    while (1) {

    }

    return 0;
}

//-- IRQ INTERRUPT HANDLERS ---------------------------------------------------------------
void TMR32_IRQHandler() {
    printf("TEST %d\n", test);

    test++;

    GPIOC->DATAOUTTGL = 1;
    // Сбрасываем флаг прерывания таймера
    TMR32->IC = 3;
}
