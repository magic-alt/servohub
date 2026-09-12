# Optional Factory Service schema/code-generation targets.
find_package(Python3 3.10 COMPONENTS Interpreter REQUIRED)
set(SERVOHUB_FACTORY_SERVICE_CODEGEN "${PROJECT_SOURCE_DIR}/tools/factory_service_codegen/generate.py")
add_custom_target(factory_service_codegen
    COMMAND "${Python3_EXECUTABLE}" "${SERVOHUB_FACTORY_SERVICE_CODEGEN}" generate
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Regenerating ServoHub Factory Service identifiers and CANopen binding manifest"
    VERBATIM
)
add_custom_target(factory_service_codegen_check
    COMMAND "${Python3_EXECUTABLE}" "${SERVOHUB_FACTORY_SERVICE_CODEGEN}" check
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Checking ServoHub Factory Service generated artifacts"
    VERBATIM
)
