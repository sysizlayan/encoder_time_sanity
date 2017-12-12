################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
qei_1.cpp: ../qei_1.ino
	@echo 'Building file: $<'
	@echo 'Invoking: Resource Custom Build Step'
	
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccsv7/tools/compiler/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-exceptions -Dprintf=iprintf -DF_CPU=80000000L -DENERGIA_EK_TM4C123GXL -DENERGIA_ARCH_TIVAC -DENERGIA=18 -DARDUINO=10610 -I"C:/Users/Yigit/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/variants/EK-TM4C123GXL" -I"C:/Users/Yigit/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/system/driverlib" -I"C:/Users/Yigit/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/system/inc" -I"C:/Users/Yigit/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/system" -I"C:/Users/Yigit/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/cores/tivac" -I"C:/Users/Yigit/Desktop/workspace_v7/qei_1" -I"C:/ti/ccsv7/tools/compiler/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include" -Os -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -w -Wall -fno-threadsafe-statics --param max-inline-insns-single=500 -mabi=aapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -fno-rtti -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


