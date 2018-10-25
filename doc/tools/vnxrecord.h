
/** \page vnxrecord vnxrecord
 * 
 * vnxrecord is a data recording tool, it connects to a target process and records the specified topics to a file.
 * 
 * \code
 * Usage: vnxrecord [-f | --file <file>] [-s | --source <url>] [-t | --topics <topic ...>]
 * \endcode
 * 
 * - \b -f or \b --file Optional file name, use "%" as a placeholder for a date string.
 * - \b -s or \b --source Target process to connect to, by default connects to localhost:4444.
 * - \b -t or \b --topics List of topics to record, needs at least one.
 * 
 * Topics have a tree structure (see \ref topic), so one can record a whole set of topics by recording a whole domain.
 * 
 * vnxrecord will sync its time to the target process, as such multiple vnxrecord processes can be running on different machines
 * without timestamp issues.
 * 
 * It is also possible to use the vnx::Recorder module directly inside a process.
 * 
 * See \ref vnxplay to play back recordings.
 * 
 * Example:
 * \code
$ vnxrecord -s localhost -t sensors.raw_data
[Proxy] INFO: Enabling remote time sync
[Recorder] INFO: Writing to 'record_20181025_173136.dat'
[Proxy] INFO: remote->enable_export('sensors.raw_data')
[Proxy] INFO: Connected to localhost:4444
[TimeServer] INFO: Initialized with offset=11
[Recorder] INFO: 356 MB, 356.418 MB/s, 773 s/s, 0 % lost
[Recorder] INFO: 765 MB, 409.705 MB/s, 855 s/s, 0 % lost
[Recorder] INFO: 1193 MB, 375.127 MB/s, 789 s/s, 0 % lost
[Recorder] INFO: 1440 MB, 247.318 MB/s, 533 s/s, 1.53045 % lost
[Recorder] INFO: 1856 MB, 415.697 MB/s, 849 s/s, 15.5473 % lost
[Recorder] INFO: Closing file, please wait ...
[Recorder] INFO: File closed
 * \endcode
 * 
 */
