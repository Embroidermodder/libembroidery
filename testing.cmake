#

add_executable(emb_test1 test/test1.c)
target_link_libraries(emb_test1 PRIVATE embroidery)

enable_testing()

add_test(
    NAME emb_test1
    COMMAND $<TARGET_FILE:emb_test1>
)

add_test(
    NAME installed
    COMMAND bash ${PROJECT_SOURCE_DIR}/test/exists.sh
)
