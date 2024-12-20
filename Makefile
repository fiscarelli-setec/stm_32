CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

# Opzioni di compilazione
CFLAGS = -mcpu=cortex-m7 -mthumb -O2 -g -DSTM32H745xx -DCORE_CM7 -I./CMSIS/Core/Include -I./CMSIS/Device/STM32H7xx/Include -I./HAL_Driver/Inc
CFLAGS_CPU2 = -mcpu=cortex-m4 -mthumb -O2 -g -DSTM32H745xx -DCORE_CM4 -I./CMSIS/Core/Include -I./CMSIS/Device/STM32H7xx/Include -I./HAL_Driver/Inc

# Opzioni di linking
LDFLAGS = -L./CMSIS/Device/STM32H7xx/Include -L./HAL_Driver/Inc

# File sorgenti per CPU1
CPU1_SRCS = cpu1_main.c adc.c dma.c hsem.c system_stm32h7xx.c syscalls.c \
            ./HAL_Driver/Src/stm32h7xx_hal.c \
            ./HAL_Driver/Src/stm32h7xx_hal_adc.c \
            ./HAL_Driver/Src/stm32h7xx_hal_dma.c \
            ./HAL_Driver/Src/stm32h7xx_hal_hsem.c \
            ./HAL_Driver/Src/stm32h7xx_hal_rcc.c \
            ./HAL_Driver/Src/stm32h7xx_hal_gpio.c \
            ./HAL_Driver/Src/stm32h7xx_hal_cortex.c \
            ./HAL_Driver/Src/stm32h7xx_hal_pwr.c \
			./HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c

# File sorgenti per CPU2
CPU2_SRCS = cpu2_main.c adc.c dma.c hsem.c system_stm32h7xx.c \
            ./HAL_Driver/Src/stm32h7xx_hal.c \
            ./HAL_Driver/Src/stm32h7xx_hal_adc.c \
            ./HAL_Driver/Src/stm32h7xx_hal_dma.c \
            ./HAL_Driver/Src/stm32h7xx_hal_hsem.c \
            ./HAL_Driver/Src/stm32h7xx_hal_rcc.c \
            ./HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
            ./HAL_Driver/Src/stm32h7xx_hal_gpio.c \
            ./HAL_Driver/Src/stm32h7xx_hal_cortex.c \
            ./HAL_Driver/Src/stm32h7xx_hal_pwr.c

CPU2_SRCS += syscalls.c
# File oggetto
CPU1_OBJS = $(CPU1_SRCS:.c=.o)
CPU2_OBJS = $(CPU2_SRCS:.c=.o)

# Regole principali
all: cpu1.elf cpu2.elf

cpu1.elf: $(CPU1_OBJS)
	$(CC) $(CFLAGS) -Tlinker_script_cpu1.ld -o $@ $^
cpu2.elf: $(CPU2_OBJS)
	$(CC) -mcpu=cortex-m4 -mthumb -O2 -g -DSTM32H745xx -DCORE_CM4 -Tlinker_script_cpu2.ld -o $@ $^



# Regola per compilare i file oggetto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o_CPU2: %.c
	$(CC) $(CFLAGS_CPU2) -c $< -o $@

# Pulizia
clean:
	rm -f *.o *.elf




FLASHER = STM32_Programmer_CLI
SERIAL_PORT = COM1
BAUD_RATE = 115200

cpu1.bin: cpu1.elf
	arm-none-eabi-objcopy -O binary $< $@

cpu2.bin: cpu2.elf
	arm-none-eabi-objcopy -O binary $< $@

flash: cpu1.bin cpu2.bin
	$(FLASHER) -c port=$(SERIAL_PORT) -br $(BAUD_RATE) -w cpu1.bin 0x08000000
	$(FLASHER) -c port=$(SERIAL_PORT) -br $(BAUD_RATE) -w cpu2.bin 0x08100000

