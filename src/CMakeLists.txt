set(INTERNAL_HEADERS

)
set(IMPL_SOURCES
    main.cpp
)
set(INTERNAL_FILES ${IMPL_SOURCES} ${INTERNAL_HEADERS})

add_executable(Emulator6502
  ${INTERNAL_FILES}
)

add_executable(Emulator6502::Emulator6502 ALIAS Emulator6502)

target_include_directories(Emulator6502
  PUBLIC
    $<BUILD_INTERFACE:${SOURCES_DIR}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(Emulator6502
  PROPERTIES
    OUTPUT_NAME "Emulator6502"
)