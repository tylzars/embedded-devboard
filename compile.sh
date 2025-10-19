arm-none-eabi-gcc \
    -mcpu=cortex-m4 \
    -mthumb \
    -mfpu=fpv4-sp-d16 \
    -mfloat-abi=hard \
    -DPART_TM4C1294NCPDT \
    -O0 \
    -g \
    -Wall \
    -T linker.ld \
    -nostdlib \
    -nostartfiles \
    --specs=nano.specs \
    -Wl,--gc-sections \
    -o main.elf \
    learn.c hexdump.c lcd.c global.h startup.c mlib.c && arm-none-eabi-objcopy -O ihex main.elf main.hex
