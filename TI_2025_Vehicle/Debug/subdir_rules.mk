################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-726104351: ../TI_2025_Vehicle.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/TI/CCS Theia/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle/TI_2025_Vehicle.syscfg" -o "." -s "C:/TI/mspm0_sdk_2_05_01_00/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-726104351 ../TI_2025_Vehicle.syscfg
device.opt: build-726104351
device.cmd.genlibs: build-726104351
ti_msp_dl_config.c: build-726104351
ti_msp_dl_config.h: build-726104351
Event.dot: build-726104351

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/CCS Theia/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle/Components/inc" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle/Debug" -I"C:/TI/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/TI/mspm0_sdk_2_05_01_00/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/CCS Theia/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle/Components/inc" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle/Debug" -I"C:/TI/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/CCS Theia/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle/Components/inc" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle/Debug" -I"C:/TI/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


