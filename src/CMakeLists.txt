find_package(OpenCV REQUIRED)
add_executable(robosub_rpi Circle.cpp Contour.cpp ContourDetector.cpp HSVImage.cpp Rectangle.cpp robosub_rpi.cpp Robot.cpp RXPacket.cpp Serial.cpp TXPacket.cpp VideoDevice.cpp)
target_link_libraries(robosub_rpi ${OpenCV_LIBS})
add_subdirectory(experiments)
