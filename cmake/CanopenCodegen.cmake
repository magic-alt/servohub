# Optional developer-only CANopen/CiA402 code-generation targets.
#
# This module deliberately does not make normal SIL builds depend on Python or
# objdictgen. Enable it explicitly with SERVOHUB_ENABLE_CANOPEN_CODEGEN=ON.

find_package(Python3 3.10 COMPONENTS Interpreter REQUIRED)

set(SERVOHUB_CANOPEN_CODEGEN_SCRIPT
    "${PROJECT_SOURCE_DIR}/tools/canopen_codegen/generate.py"
)

add_custom_target(canopen_codegen
    COMMAND "${Python3_EXECUTABLE}" "${SERVOHUB_CANOPEN_CODEGEN_SCRIPT}" generate
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Regenerating CanFestival SlaveOD C/H and ServoHub CiA402 contract"
    VERBATIM
)

add_custom_target(canopen_codegen_check
    COMMAND "${Python3_EXECUTABLE}" "${SERVOHUB_CANOPEN_CODEGEN_SCRIPT}" check
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Validating ServoHub CANopen object dictionary and generated CiA402 contract"
    VERBATIM
)

add_custom_target(canopen_codegen_list
    COMMAND "${Python3_EXECUTABLE}" "${SERVOHUB_CANOPEN_CODEGEN_SCRIPT}" list
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Listing ServoHub CANopen object dictionary"
    VERBATIM
)

add_custom_target(canopen_codegen_migrate_jsonc
    COMMAND "${Python3_EXECUTABLE}" "${SERVOHUB_CANOPEN_CODEGEN_SCRIPT}" migrate-jsonc
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Creating reviewable JSONC object dictionary from current EDS"
    VERBATIM
)
