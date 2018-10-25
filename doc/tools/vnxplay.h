
/** \page vnxplay vnxplay
 * 
 * vnxplay is a data playback tool, it can play back one or more recordings at various speeds.
 * 
 * \code
 * Usage: vnxplay [-b | --blocking] [-f | --files <file ...>] [-p | --port <port>] [-r | --repeat] [-u | --unix-path <unix path>] [-x | --speed] [--seek <0-1>]
 * \endcode
 * 
 * - \b -b or \b --blocking Flag if to publish samples in blocking mode.
 * - \b -f or \b --files List of recording files.
 * - \b -p or \b --port TCP server port, default = 4444.
 * - \b -r or \b --repeat Flag if to play in a loop.
 * - \b -u or \b --unix-path UNIX domain path, default = "/tmp/vnxplayer.sock".
 * - \b -x or \b --speed Playback speed, default = 1.
 * 
 * Multiple recording files can be specified, they can overlap and/or form a sequence.
 * If there is a gap between files of more than 5 seconds it will be skipped.
 * 
 * See \ref vnxrecord to create recordings.
 * 
 * The player can be controlled by the following keys:
 * - \b space = toggle play/pause
 * - \b s = stop and seek to beginning
 * - \b x = seek -10 min
 * - \b c = seek -1 min
 * - \b v = seek -10 s
 * - \b b = seek +10 s
 * - \b n = seek +1 min
 * - \b m = seek +10 min
 * - \b 1 = set speed 1 x
 * - \b 2 = set speed 2 x
 * - \b 3 = set speed 3 x
 * - \b 4 = set speed 5 x
 * - \b 5 = set speed 10 x
 * - \b 6 = set speed 20 x
 * - \b 7 = set speed 30 x
 * - \b 8 = set speed 50 x
 * - \b 9 = set speed 100 x
 * - \b 0 = set speed 1000 x
 * - \b q = set speed 0.5 x
 * - \b w = set speed 0.3 x
 * - \b e = set speed 0.2 x
 * - \b r = set speed 0.1 x
 * - \b t = set speed 0.05 x
 * - \b y = set speed 0.03 x
 * - \b u = set speed 0.02 x
 * - \b i = set speed 0.01 x
 * - \b o = set speed 0.001 x
 * - \b p = set speed 0.0001 x
 * 
 * Example:
 * \code
$ vnxplay -f record_20180623_180915.dat
Controls: space=play/pause, s=stop, x=-10min, c=-1min, v=-10s, b=+10s, n=+1min, m=+10min, [1234567890]=faster, [qwertyuiop]=slower
[UnixServer] INFO: Running on /tmp/vnxplayer.sock
[TcpServer] INFO: Running on 0.0.0.0:4444
[Player] INFO: open('record_20180623_180915.dat')
[Player] INFO: Start    : 2018-06-24 03:09:15 CEST (1529802555 UTC)
[Player] INFO: End      : 2018-06-24 03:16:49 CEST (1529803009 UTC)
[Player] INFO: Duration : 00:07:34 (HH:MM:SS)
[Player] INFO: Total    : 2201289 samples, 0 lost, 179770 MB
[Player] INFO: 'lidar.info.default.Velodyne_FC': 455 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'lidar.info.online.Velodyne_FC': 455 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'sensors.raw_data.Basler_L': 5647 samples, 0 lost (0 %), 33882 MB
[Player] INFO: 'sensors.raw_data.Basler_R': 5628 samples, 0 lost (0 %), 33768 MB
[Player] INFO: 'sensors.raw_data.FLIR_FL': 5579 samples, 0 lost (0 %), 53001 MB
[Player] INFO: 'sensors.raw_data.FLIR_FR': 5582 samples, 0 lost (0 %), 53029 MB
[Player] INFO: 'sensors.raw_data.OCAM_LF': 2098 samples, 0 lost (0 %), 2458 MB
[Player] INFO: 'sensors.raw_data.OCAM_RF': 2127 samples, 0 lost (0 %), 2492 MB
[Player] INFO: 'sensors.raw_data.Velodyne_FC': 342763 samples, 0 lost (0 %), 434 MB
[Player] INFO: 'vehicle.control_input': 9003 samples, 0 lost (0 %), 1 MB
[Player] INFO: 'vehicle.gps_info': 455 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vehicle.imu_info': 362562 samples, 0 lost (0 %), 46 MB
[Player] INFO: 'vehicle.obd_msgs': 958765 samples, 0 lost (0 %), 119 MB
[Player] INFO: 'vehicle.odometry': 362561 samples, 0 lost (0 %), 504 MB
[Player] INFO: 'vehicle.pps_signal': 455 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vehicle.ubx_msgs': 2730 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vehicle.vehicle_info': 45489 samples, 0 lost (0 %), 7 MB
[Player] INFO: 'vehicle.wheel_speed': 22740 samples, 0 lost (0 %), 2 MB
[Player] INFO: 'vision.info.default.Basler_L': 4549 samples, 0 lost (0 %), 1 MB
[Player] INFO: 'vision.info.default.Basler_R': 4548 samples, 0 lost (0 %), 1 MB
[Player] INFO: 'vision.info.default.FLIR_FL': 4541 samples, 0 lost (0 %), 1 MB
[Player] INFO: 'vision.info.default.FLIR_FR': 4549 samples, 0 lost (0 %), 1 MB
[Player] INFO: 'vision.info.default.OCAM_LF': 2098 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vision.info.default.OCAM_RF': 2127 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vision.info.default.Stereo_FN': 9528 samples, 0 lost (0 %), 2 MB
[Player] INFO: 'vision.info.default.Stereo_FW': 455 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vision.info.intensity.Basler_L': 5647 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vision.info.intensity.Basler_R': 5628 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vision.info.intensity.FLIR_FL': 5579 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vision.info.intensity.FLIR_FR': 5582 samples, 0 lost (0 %), 0 MB
[Player] INFO: 'vision.info.online.Basler_L': 4548 samples, 0 lost (0 %), 1 MB
[Player] INFO: 'vision.info.online.FLIR_FL': 4541 samples, 0 lost (0 %), 1 MB
[Player] INFO: 'vnx.time_sync': 2275 samples, 0 lost (0 %), 0 MB
[Player] INFO: [>                                                 ] 0%, 1.14713/454.852 s, 446.697 MB/s, 5532 s/s, 1 x (0.965209 x)
...
 * \endcode
 * 
 * Every second of playback an info line is printed:
 * \code
[Player] INFO: {progess bar} {progress}%, {current time}/{total time} s, {read bandwidth} MB/s, {samples per second} s/s, {target speed} x ({actual speed} x)
 * \endcode
 * 
 */
