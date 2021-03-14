set(EMULATOR6502_PATH "Emulator6502")

set(INTERNAL_HEADERS
  ${EMULATOR6502_PATH}/common.h
  ${EMULATOR6502_PATH}/opcode.h
  ${EMULATOR6502_PATH}/cpu.h
  ${EMULATOR6502_PATH}/emulator.h
)
set(IMPL_SOURCES
  ${EMULATOR6502_PATH}/cpu.cpp
  ${EMULATOR6502_PATH}/emulator.cpp
)
set(INTERNAL_FILES ${IMPL_SOURCES} ${INTERNAL_HEADERS})

add_executable(Emulator6502
  main.cpp
  ${INTERNAL_FILES}
)

add_executable(Emulator6502::Emulator6502 ALIAS Emulator6502)

target_include_directories(Emulator6502
  PUBLIC
    ${EMULATOR6502_PATH}
)

set_target_properties(Emulator6502
  PROPERTIES
    OUTPUT_NAME "Emulator6502"
)

target_compile_options(Emulator6502 PRIVATE -Werror -Wall -Wextra -Wshadow -Wpedantic)