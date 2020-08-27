################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include gecko_sdk_3.0.0/util/third_party/segger/systemview/SEGGER/subdir.mk
-include gecko_sdk_3.0.0/util/third_party/printf/src/subdir.mk
-include gecko_sdk_3.0.0/util/third_party/printf/subdir.mk
-include gecko_sdk_3.0.0/platform/service/udelay/src/subdir.mk
-include gecko_sdk_3.0.0/platform/service/system/src/subdir.mk
-include gecko_sdk_3.0.0/platform/service/sleeptimer/src/subdir.mk
-include gecko_sdk_3.0.0/platform/service/mpu/src/subdir.mk
-include gecko_sdk_3.0.0/platform/service/iostream/src/subdir.mk
-include gecko_sdk_3.0.0/platform/service/device_init/src/subdir.mk
-include gecko_sdk_3.0.0/platform/service/cli/src/subdir.mk
-include gecko_sdk_3.0.0/platform/radio/rail_lib/plugin/rail_util_pti/subdir.mk
-include gecko_sdk_3.0.0/platform/radio/rail_lib/plugin/rail_util_init/subdir.mk
-include gecko_sdk_3.0.0/platform/radio/rail_lib/plugin/pa-conversions/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/ports/source/gnu/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/ports/source/generic/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/kernel/source/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/init/src/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/cpu/source/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/common/source/rtos/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/common/source/ring_buf/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/common/source/logging/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/common/source/lib/subdir.mk
-include gecko_sdk_3.0.0/platform/micrium_os/common/source/kal/subdir.mk
-include gecko_sdk_3.0.0/platform/emlib/src/subdir.mk
-include gecko_sdk_3.0.0/platform/emdrv/gpiointerrupt/src/subdir.mk
-include gecko_sdk_3.0.0/platform/emdrv/dmadrv/src/subdir.mk
-include gecko_sdk_3.0.0/platform/driver/leddrv/src/subdir.mk
-include gecko_sdk_3.0.0/platform/driver/button/src/subdir.mk
-include gecko_sdk_3.0.0/platform/common/toolchain/src/subdir.mk
-include gecko_sdk_3.0.0/platform/common/src/subdir.mk
-include gecko_sdk_3.0.0/platform/Device/SiliconLabs/EFR32FG14P/Source/GCC/subdir.mk
-include gecko_sdk_3.0.0/platform/Device/SiliconLabs/EFR32FG14P/Source/subdir.mk
-include gecko_sdk_3.0.0/hardware/driver/mx25_flash_shutdown/src/subdir.mk
-include gecko_sdk_3.0.0/hardware/board/src/subdir.mk
-include autogen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: te.axf

# Tool invocations
te.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:\work\te/autogen/linkerfile.ld" -Xlinker --gc-sections -Xlinker -Map="te.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o te.axf -Wl,--start-group "./app_cli.o" "./app_init.o" "./app_iostream_usart.o" "./app_process.o" "./main.o" "./autogen/rail_config.o" "./autogen/sl_board_default_init.o" "./autogen/sl_cli_command_table.o" "./autogen/sl_cli_instances.o" "./autogen/sl_device_init_clocks.o" "./autogen/sl_event_handler.o" "./autogen/sl_iostream_handles.o" "./autogen/sl_iostream_init_usart_instances.o" "./autogen/sl_rail_util_callbacks.o" "./autogen/sl_simple_button_instances.o" "./autogen/sl_simple_led_instances.o" "./gecko_sdk_3.0.0/hardware/board/src/sl_board_control_gpio.o" "./gecko_sdk_3.0.0/hardware/board/src/sl_board_init.o" "./gecko_sdk_3.0.0/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown.o" "./gecko_sdk_3.0.0/platform/Device/SiliconLabs/EFR32FG14P/Source/GCC/startup_efr32fg14p.o" "./gecko_sdk_3.0.0/platform/Device/SiliconLabs/EFR32FG14P/Source/system_efr32fg14p.o" "./gecko_sdk_3.0.0/platform/common/src/sl_slist.o" "./gecko_sdk_3.0.0/platform/common/src/sl_string.o" "./gecko_sdk_3.0.0/platform/common/toolchain/src/sl_memory.o" "./gecko_sdk_3.0.0/platform/driver/button/src/sl_button.o" "./gecko_sdk_3.0.0/platform/driver/button/src/sl_simple_button.o" "./gecko_sdk_3.0.0/platform/driver/leddrv/src/sl_led.o" "./gecko_sdk_3.0.0/platform/driver/leddrv/src/sl_simple_led.o" "./gecko_sdk_3.0.0/platform/emdrv/dmadrv/src/dmadrv.o" "./gecko_sdk_3.0.0/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_assert.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_cmu.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_core.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_emu.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_gpio.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_ldma.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_rtcc.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_system.o" "./gecko_sdk_3.0.0/platform/emlib/src/em_usart.o" "./gecko_sdk_3.0.0/platform/micrium_os/common/source/kal/kal_kernel.o" "./gecko_sdk_3.0.0/platform/micrium_os/common/source/lib/lib_ascii.o" "./gecko_sdk_3.0.0/platform/micrium_os/common/source/lib/lib_mem.o" "./gecko_sdk_3.0.0/platform/micrium_os/common/source/lib/lib_str.o" "./gecko_sdk_3.0.0/platform/micrium_os/common/source/logging/logging.o" "./gecko_sdk_3.0.0/platform/micrium_os/common/source/ring_buf/ring_buf.o" "./gecko_sdk_3.0.0/platform/micrium_os/common/source/rtos/rtos_err_str.o" "./gecko_sdk_3.0.0/platform/micrium_os/common/source/rtos/rtos_utils.o" "./gecko_sdk_3.0.0/platform/micrium_os/cpu/source/cpu_core.o" "./gecko_sdk_3.0.0/platform/micrium_os/init/src/sl_micrium_kernel.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_cfg_app.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_core.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_dbg.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_flag.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_mon.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_msg.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_mutex.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_prio.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_q.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_sem.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_stat.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_task.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_time.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_tmr.o" "./gecko_sdk_3.0.0/platform/micrium_os/kernel/source/os_var.o" "./gecko_sdk_3.0.0/platform/micrium_os/ports/source/generic/arm_cpu_dwt_ts.o" "./gecko_sdk_3.0.0/platform/micrium_os/ports/source/gnu/armv7m_cpu_a.o" "./gecko_sdk_3.0.0/platform/micrium_os/ports/source/gnu/armv7m_os_cpu_a.o" "./gecko_sdk_3.0.0/platform/micrium_os/ports/source/gnu/armv7m_os_cpu_c.o" "./gecko_sdk_3.0.0/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o" "./gecko_sdk_3.0.0/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.o" "./gecko_sdk_3.0.0/platform/radio/rail_lib/plugin/rail_util_init/sl_rail_util_init.o" "./gecko_sdk_3.0.0/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o" "./gecko_sdk_3.0.0/platform/service/cli/src/sl_cli.o" "./gecko_sdk_3.0.0/platform/service/cli/src/sl_cli_arguments.o" "./gecko_sdk_3.0.0/platform/service/cli/src/sl_cli_command.o" "./gecko_sdk_3.0.0/platform/service/cli/src/sl_cli_input.o" "./gecko_sdk_3.0.0/platform/service/cli/src/sl_cli_io.o" "./gecko_sdk_3.0.0/platform/service/cli/src/sl_cli_tokenize.o" "./gecko_sdk_3.0.0/platform/service/device_init/src/sl_device_init_dcdc_s1.o" "./gecko_sdk_3.0.0/platform/service/device_init/src/sl_device_init_emu_s1.o" "./gecko_sdk_3.0.0/platform/service/device_init/src/sl_device_init_hfxo_s1.o" "./gecko_sdk_3.0.0/platform/service/device_init/src/sl_device_init_lfxo_s1.o" "./gecko_sdk_3.0.0/platform/service/iostream/src/sl_iostream.o" "./gecko_sdk_3.0.0/platform/service/iostream/src/sl_iostream_retarget_stdio.o" "./gecko_sdk_3.0.0/platform/service/iostream/src/sl_iostream_swo_itm_8.o" "./gecko_sdk_3.0.0/platform/service/iostream/src/sl_iostream_uart.o" "./gecko_sdk_3.0.0/platform/service/iostream/src/sl_iostream_usart.o" "./gecko_sdk_3.0.0/platform/service/iostream/src/sl_iostream_vuart.o" "./gecko_sdk_3.0.0/platform/service/mpu/src/sl_mpu.o" "./gecko_sdk_3.0.0/platform/service/sleeptimer/src/sl_sleeptimer.o" "./gecko_sdk_3.0.0/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.o" "./gecko_sdk_3.0.0/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.o" "./gecko_sdk_3.0.0/platform/service/system/src/sl_system_init.o" "./gecko_sdk_3.0.0/platform/service/system/src/sl_system_kernel.o" "./gecko_sdk_3.0.0/platform/service/udelay/src/sl_udelay.o" "./gecko_sdk_3.0.0/platform/service/udelay/src/sl_udelay_armv6m_gcc.o" "./gecko_sdk_3.0.0/util/third_party/printf/printf.o" "./gecko_sdk_3.0.0/util/third_party/printf/src/iostream_printf.o" "./gecko_sdk_3.0.0/util/third_party/segger/systemview/SEGGER/SEGGER_RTT.o" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.0//platform/radio/rail_lib/autogen/librail_release/librail_efr32xg14_gcc_release.a" -lgcc -lc -lm -lnosys -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: te.hex'
	arm-none-eabi-objcopy -O ihex "te.axf" "te.hex"
	@echo ' '

	@echo 'Building bin file: te.bin'
	arm-none-eabi-objcopy -O binary "te.axf" "te.bin"
	@echo ' '

	@echo 'Building s37 file: te.s37'
	arm-none-eabi-objcopy -O srec "te.axf" "te.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "te.axf" -A
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) te.axf
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
