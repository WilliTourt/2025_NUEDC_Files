################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-154440161: ../TI_2025_Vehicle_PureC.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/TI/CCS Theia/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/TI_2025_Vehicle_PureC.syscfg" -o "." -s "C:/TI/mspm0_sdk_2_05_01_00/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-154440161 ../TI_2025_Vehicle_PureC.syscfg
device.opt: build-154440161
device.cmd.genlibs: build-154440161
ti_msp_dl_config.c: build-154440161
ti_msp_dl_config.h: build-154440161
Event.dot: build-154440161

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/CCS Theia/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Components/inc" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Debug" -I"C:/TI/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_05_01_00/source" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Components/mpu6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/TI/mspm0_sdk_2_05_01_00/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/CCS Theia/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Components/inc" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Debug" -I"C:/TI/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_05_01_00/source" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Components/mpu6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/CCS Theia/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Components/inc" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Debug" -I"C:/TI/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_05_01_00/source" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Components/mpu6050" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


