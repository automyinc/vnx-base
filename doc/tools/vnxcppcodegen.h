
/** \page vnxcppcodegen vnxcppcodegen
 * 
 * \code
Usage: vnxcppcodegen [--overwrite] [--cleanup] <output-directory>/ <package> <interface-directory>/ [interface-directory-2/] ...
 * \endcode
 * 
 * `vnxcppcodegen` is a command line tool to generate C++ code from VNI type definitions.
 * 
 * It is included in the commercial and enterprise package of VNX. 
 * 
 * - \b --cleanup will remove obsolete files in the output directory
 * - \b --overwrite will re-write all files, even if the content is the same
 * 
 * For example: (see vnx-examples repository)
 * 
 * \code
$ vnxcppcodegen --cleanup generated/ example interface/ modules/ /usr/interface/vnx/ /usr/interface/basic/ /usr/interface/math/
UPDATE generated/include/example/CameraSensorBase.hxx
UPDATE generated/src/CameraSensorBase.cpp
UPDATE generated/include/example/CameraSensorClient.hxx
UPDATE generated/src/CameraSensorClient.cpp
UPDATE generated/include/example/DatabaseBase.hxx
UPDATE generated/src/DatabaseBase.cpp
UPDATE generated/include/example/DatabaseClient.hxx
UPDATE generated/src/DatabaseClient.cpp
UPDATE generated/include/example/ImageProcessorBase.hxx
UPDATE generated/src/ImageProcessorBase.cpp
UPDATE generated/include/example/ImageProcessorClient.hxx
UPDATE generated/src/ImageProcessorClient.cpp
UPDATE generated/include/example/LidarInfo.hxx
UPDATE generated/src/LidarInfo.cpp
UPDATE generated/include/example/LidarPointCloud.hxx
UPDATE generated/src/LidarPointCloud.cpp
UPDATE generated/include/example/LidarProcessorBase.hxx
UPDATE generated/src/LidarProcessorBase.cpp
UPDATE generated/include/example/LidarProcessorClient.hxx
UPDATE generated/src/LidarProcessorClient.cpp
UPDATE generated/include/example/LidarSensorBase.hxx
UPDATE generated/src/LidarSensorBase.cpp
UPDATE generated/include/example/LidarSensorClient.hxx
UPDATE generated/src/LidarSensorClient.cpp
UPDATE generated/include/example/Transaction.hxx
UPDATE generated/src/Transaction.cpp
UPDATE generated/include/example/User.hxx
UPDATE generated/src/User.cpp
UPDATE generated/include/example/lidar_point_t.hxx
UPDATE generated/src/lidar_point_t.cpp
UPDATE generated/include/example/transaction_type_e.hxx
UPDATE generated/src/transaction_type_e.cpp
UPDATE generated/include/example/package.hxx
UPDATE generated/src/package.cpp
 * \endcode
 * 
 * 
 * 
 */
