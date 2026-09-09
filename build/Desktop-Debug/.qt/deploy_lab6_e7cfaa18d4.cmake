include("C:/qtprojects/lab6/build/Desktop-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/lab6-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "C:/qtprojects/lab6/build/Desktop-Debug/lab6.exe"
    GENERATE_QT_CONF
)
