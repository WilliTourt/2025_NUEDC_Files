################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Examples/%.o: ../Examples/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/CCS Theia/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Components/inc" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC" -I"E:/Folders/Documents/Embedded_Dev/Texas Instruments/CCS Theia/TI_2025_Vehicle_PureC/Debug" -I"C:/TI/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"Examples/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


