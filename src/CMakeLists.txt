set(EMULATOR6502_PATH "Emulator6502")

set(INTERNAL_HEADERS
  ${EMULATOR6502_PATH}/Types.h
  ${EMULATOR6502_PATH}/Instruction.h
  ${EMULATOR6502_PATH}/Interpreter.h
  ${EMULATOR6502_PATH}/DescriptorTable.h
  ${EMULATOR6502_PATH}/FileLoader/FileLoader.h
  ${EMULATOR6502_PATH}/Cpu.h
)
set(IMPL_SOURCES
  ${EMULATOR6502_PATH}/Instruction.cpp
  ${EMULATOR6502_PATH}/DescriptorTable.cpp
  ${EMULATOR6502_PATH}/FileLoader/FileLoader.cpp
  ${EMULATOR6502_PATH}/Cpu.cpp
)
set(INTERNAL_FILES ${IMPL_SOURCES} ${INTERNAL_HEADERS})

add_executable(Emulator6502
  ${INTERNAL_FILES}
  main.cpp
)

target_include_directories(Emulator6502
  PUBLIC
    ${EMULATOR6502_PATH}
)

set_target_properties(Emulator6502
  PROPERTIES
    OUTPUT_NAME "Emulator6502"
)

target_compile_options(Emulator6502 PRIVATE -Werror -Wall -Wextra -Wshadow -Wpedantic)

add_executable(Emulator6502::Emulator6502 ALIAS Emulator6502)