# Linux К1921ВГ015 examples

Адаптированная для сборки под Linux версия примера работы с российским микроконтроллером К1921ВГ015


## RISCV GCC toolkit 

Скачать RISCV GCC toolkit версии 13.2.0 

> [!NOTE]
> Именно этой версии, в версии 14.2.0 почему-то нет rv32imfc_zicsr. Я не знаю с чем это связано, может быть я где-то не разобрался, а может это бага.

`xpack-riscv-none-elf-gcc-13.2.0-2-linux-x64.tar.gz`

https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/



## OpenOCD

Скачать сборку OpenOCD

`xpack-openocd-k1921vk-0.12.0-k1921vk-linux-x64.tar.gz`

> [!NOTE]
> Необходима именно эта версия OpenOCD. В ней добавлена возможность прошивки микроконтроллера К1921ВГ015

https://github.com/DCVostok/openocd-k1921vk/releases


## Environment setup

Распаковать архивы куда-нибудь в удобное-место.

Подправить Makefile 

COMPILER_PATH должен указывать на bin каталог RISCV GCC toolkit, OPENOCD_PATH на исполняемый файл openocd


## Make

`make`

Собирает прошивку

> [!NOTE]
> Исходники прошивок адаптированы для работы с отладочной платой BlueBird-VG015, а не с оригинальной платой от АО «НИИЭТ». Встроенный светодиод не на том пине и т.д.


## Firmware upload

`make upload-jlink`

Заливает прошивку через JLink

`make upload-bp`

Заливает прошивку через программатор BlueProg


## Links

Сайт производителя отладочной платы BlueBird-VG015

https://www.xn-----6kccalfmhwcdcrbm1aajnghfrqjce3b0z.xn--p1ai/VG015/1-VG015_devboard.html


Офф. сайт производителя микроконтроллеров К1921ВГ015 АО «НИИЭТ»

https://niiet.ru/product/%D0%BA1921%D0%B2%D0%B3015/
