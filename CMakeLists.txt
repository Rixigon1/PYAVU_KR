# cmake_minimum_required(VERSION 3.19)
# project(PAYVU_KR LANGUAGES CXX)

# find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

# qt_standard_project_setup()

# qt_add_executable(PAYVU_KR
#     WIN32 MACOSX_BUNDLE
#     main.cpp


#     dataStructures.h
#     dataStructures.cpp
#     fileFunctions.h fileFunctions.cpp
#     menuFunctions.h menuFunctions.cpp
# )

# target_compile_features(PAYVU_KR PRIVATE cxx_std_20)

# qt_add_translations(
#     TARGETS PAYVU_KR
#     TS_FILES PAYVU_KR_ru_RU.ts
# )

# target_link_libraries(PAYVU_KR
#     PRIVATE
#         Qt::Core
#         Qt::Widgets
# )

# install(TARGETS PAYVU_KR
#     BUNDLE  DESTINATION .
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )

# qt_generate_deploy_app_script(
#     TARGET PAYVU_KR
#     OUTPUT_SCRIPT deploy_script
#     NO_UNSUPPORTED_PLATFORM_ERROR
# )
# install(SCRIPT ${deploy_script})


cmake_minimum_required(VERSION 3.19)

project(PAYVU_KR LANGUAGES CXX)

add_executable(PAYVU_KR
    main.cpp
    dataStructures.h
    dataStructures.cpp
    fileFunctions.h
    fileFunctions.cpp
    menuFunctions.h
    menuFunctions.cpp
    utils.h utils.cpp
)

target_compile_features(PAYVU_KR PRIVATE cxx_std_20)


