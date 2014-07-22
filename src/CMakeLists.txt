find_package(OpenCV REQUIRED)
add_executable(robosub_rpi BaseVideoDevice.cpp Circle.cpp CliOptions.cpp Contour.cpp ContourDetector.cpp HSVImage.cpp Logger.cpp Mission.cpp Rectangle.cpp robosub_rpi.cpp Robot.cpp RXPacket.cpp Serial.cpp StartingGateMission.cpp TXPacket.cpp USBVideoDevice.cpp)
target_link_libraries(robosub_rpi ${OpenCV_LIBS})
add_subdirectory(experiments)
