cmake_minimum_required(VERSION 2.8.3)
project(MISL1000BaseTXFirmware)

include(tm4c1294.cmake)

set(TIVAWARE_PATH $ENV{HOME}/projects/projects/TivaWare)

include_directories(${TIVAWARE_PATH})

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/FreeRTOS/portable/CCS/ARM_CM4F/)
include_directories(${CMAKE_SOURCE_DIR}/FreeRTOS/include/)



add_executable(${CMAKE_PROJECT_NAME}.axf    startup_gcc.c
                                            SystemInit.c
                                            ${TIVAWARE_PATH}/utils/uartstdio.c
                                            FreeRTOS/croutine.c
                                            FreeRTOS/event_groups.c
                                            FreeRTOS/list.c
                                            FreeRTOS/queue.c
                                            FreeRTOS/tasks.c
                                            FreeRTOS/timers.c
                                            FreeRTOS/portable/CCS/ARM_CM4F/port.c
                                            FreeRTOS/portable/MemMang/heap_2.c
                                            FreeRTOS/Tasks/BlinkLEDTask.cpp
                                            FreeRTOS/Tasks/CLIInterpreterTask.cpp
                                            FreeRTOS/Tasks/ITask.cpp
                                            CommandLine/Commands/ICommand.cpp
                                            CommandLine/Commands/SetPort.cpp
                                            HardwareControl/GPIOPin.cpp
                                            HardwareControl/HardwareRegister.cpp
                                            HardwareControl/SPI.cpp
                                            HardwareControl/UIOStream.cpp
                                            HardwareControl/W5500.cpp
                                            SystemObjects/ExceptionHandler.cpp
                                            SystemObjects/HelperFunctions.cpp
                                            SystemObjects/RTOSMutex.cpp
#                                           TCPIPObjects/HTTPHandler.cpp
                                            TCPIPObjects/Socket.cpp
                                            main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}.axf
        ${TIVAWARE_PATH}/usblib/gcc/libusb.a
        ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a
        )
target_compile_definitions(${CMAKE_PROJECT_NAME}.axf PRIVATE UART_BUFFERED=1)


