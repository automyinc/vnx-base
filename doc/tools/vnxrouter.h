
/** \page vnxrouter vnxrouter
 * 
 * vnxrouter is a process running a vnx::Router module.
 * 
 * \code
 * Usage: vnxrouter [-c | --config <directory>] [-p | --port <port>] [-u | --unix-path <unix path>]
 * \endcode
 * 
 * - \b -p or \b --port TCP server port, default = 4444.
 * - \b -u or \b --unix-path UNIX domain socket, default = ".vnxrouter.sock".
 * 
 * The router can be configured by a "Router.json" file, see vnx::Router for more information.
 * 
 * Example:
 * \code{.json}
$ cat config/Router.json
{
	"import_map": {
		"rpi_imu": [
			"vnx.time_sync",
			"vehicle.imu_info",
			"vehicle.gps_info",
			"vehicle.ubx_msgs",
			"vehicle.pps_signal",
			"vehicle.odometry",
			"vehicle.vehicle_info",
			"vehicle.wheel_speed",
			"vehicle.obd_msgs",
			"vehicle.control_status",
			"kia_soul_ev.control_state"
		]
	},
	"export_map": {
		"rpi_imu": [
			"vehicle.control_output"
		]
	}
}
 * \endcode
 * 
 * This "Router.json" config will have vnxrouter connect to rpi_imu:4444 and import the list of topics as well as sync time with rpi_imu.
 * In addition it will export "vehicle.control_output" to rpi_imu::4444 via anther connection.
 * 
 * Running vnxrouter in the background:
 * \code
 * $ screen -S vnxrouter -d -m vnxrouter -c config/
 * \endcode
 * 
 * 
 * 
 */
