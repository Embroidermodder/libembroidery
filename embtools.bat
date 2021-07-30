@ECHO OFF
SETLOCAL

:main
:: Start point for script.

CALL :main_tests
CALL :embphoto

EXIT /b 0

:embphoto
ECHO "Function to filter photos for producing embroideries."
EXIT /b 0

:main_tests
DEL build
MKDIR build
CD build
cmake ..
cmake --build .

./embroider --test
cd ..
EXIT /b 0

:full_test_suite

EXIT /b 0
