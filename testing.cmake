#

enable_testing()

add_test(
    NAME INBUILT_TESTING
    COMMAND $<TARGET_FILE:embroider> --test
)

add_test(
    NAME installed
    COMMAND bash ${PROJECT_SOURCE_DIR}/test/exists.sh
)
