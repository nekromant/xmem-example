cmake_minimum_required(VERSION 3.0)
set(CROSS_COMPILE avr)
set(CMAKE_TOOLCHAIN_FILE cmake/toolchain.cmake)

set(CONFIG_MCU atmega1280)
set(CONFIG_F_CPU 16000000)


project(XMemTest
  VERSION 0.5
  LANGUAGES C ASM
      )

#add_compile_options(-Os -Wall -ffunction-sections -std=gnu99)

include_directories(include)

set(target ${PROJECT_NAME})

add_executable(${target}
  src/stdio.c
  src/main.c
  src/xmem.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=${CONFIG_MCU} -DF_CPU=${CONFIG_F_CPU} -Os")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,vfprintf -lprintf_flt -Wl,-u,vfscanf -lscanf_flt")
#add_definitions(-DF_CPU=${CONFIG_F_CPU})
#add_definitions(-D__DELAY_BACKWARD_COMPATIBLE__)

target_link_libraries(${target} -Wl,--gc-sections -Wl,--relax)
target_link_libraries(${target} -mmcu=${CONFIG_MCU})


add_custom_command(
  TARGET ${target}
  COMMAND ${CROSS_OBJCOPY} -j .text -j .data -O ihex ${target} ${target}.hex
  COMMAND ${CROSS_SIZE_TOOL} ${CROSS_SIZE_FLAGS} ${target}
  DEPENDS ${target}
  COMMENT "Creatinng ${target}.hex"
)

add_custom_command(
TARGET ${target}
COMMAND
  ${CROSS_OBJCOPY} -j .eeprom --set-section-flags=.eeprom=alloc,load
  --change-section-lma .eeprom=0 --no-change-warnings
  -O binary ${target} ${target}.eep
DEPENDS uisp-loader
)

add_custom_target(
  deploy
  COMMAND avrdude -c arduino -p ${CONFIG_MCU} -P /dev/ttyUSB0 -b 57600 -U flash:w:${target}.hex
)
