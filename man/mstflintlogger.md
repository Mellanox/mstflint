
# NAME

mstflintlogger

# SYNPOSIS

> mstflintlogger \[OPTIONS\]
>
> \[-l|-\-set-level \<LEVEL\>\] \[-m|-\-set-module \<MODULE:LEVEL\>\]
> \[-M|-\-clear-module \<MODULE\>\] \[-o|-\-enable-output \<SINK\>\]
> \[-O|-\-disable-output \<SINK\>\] \[-n|-\-set-max-log-files \<COUNT\>\]
> \[-s|-\-show\] \[-r|-\-reset\] \[-h|-\-help\]

# DESCRIPTION

> mstflintlogger configures the NVIDIA Tools logger used by the mstflint tools. It
> reads and writes a single JSON file, /var/lib/mstflint/mstflintlogger.json, which
> every tool loads once at process start. Verbosity is therefore data, not
> code: no tool flag and no rebuild is involved, and one command changes what
> every tool logs.
>
> Logging is off until it is turned on. With no configuration file present,
> no output is produced at all, unless NVTOOLSLOGGER_LEVEL is set (see
> ENVIRONMENT).
>
> The configuration file records the mstflint build that wrote it. A file
> written by a different build, for example before an upgrade, is ignored and
> the defaults apply, so logging is off again until it is turned back on; the
> next mstflintlogger command rewrites the file.
>
> A configuration change affects processes started afterwards; a tool that is
> already running is unaffected.
>
> Severity levels are debug, info, warning, error, fatal and off. A level
> means "this level and above"; off silences the layer. Output sinks are
> stdout, stderr, file and syslog. The file sink writes
> /var/log/mstflint/\<executable\>_\<pid\>.log. When stdout is not a terminal,
> the stdout sink writes to stderr instead, so log records never end up in
> output that another program parses.
>
> Writing the configuration file requires root.

OPTIONS

> mstflintlogger \[OPTIONS\]

  - **-l**|-\-set-level \<LEVEL\>
    : Set the global severity threshold, used by every layer with no override.
    If the configuration has no output sink yet and the command names none,
    stdout is enabled as well

  - **-m**|-\-set-module \<MODULE:LEVEL\>
    : Set a per-layer severity override, e.g. mtcr:debug. May be repeated.
    Use all:\<LEVEL\> to set every layer

  - **-M**|-\-clear-module \<MODULE\>
    : Drop a per-layer override so the layer follows the global level. May be
    repeated. Use all to drop every override

  - **-o**|-\-enable-output \<SINK\>
    : Add an output sink. May be repeated

  - **-O**|-\-disable-output \<SINK\>
    : Remove an output sink. May be repeated

  - **-n**|-\-set-max-log-files \<COUNT\>
    : Cap the number of .log files kept in the log directory, 1 to 1000
    (default: 100). Older files beyond the cap are deleted when a new log file
    is opened

  - **-s**|-\-show
    : Print the configuration and the resolved severity of every layer,
    tagged (override) or (global)

  - **-r**|-\-reset
    : Reset the configuration to defaults, i.e. logging off

  - **-h**|-\-help
    : Show help message and exit

  - **-v**|-\-version
    : Show version and exit

# LAYERS

> A layer is the unit of on/off control: one name in the log record, one key in
> the configuration file, one argument to -\-set-module. The layers are:
>
> mtcr, reg_access, flint, mlxconfig, mlxlink, mlxreg, mft_core, mlxfwops,
> mst_tool, efuse, common, hca_caps
>
> all is not a layer, it is a keyword accepted by -\-set-module and
> -\-clear-module that expands to every layer.

# ENVIRONMENT

> NVTOOLSLOGGER_LEVEL, set to 1 (debug) through 5 (fatal), logs every layer at
> that level and above to stdout for a single run, e.g.
> NVTOOLSLOGGER_LEVEL=1 mstflint -d /dev/mst/mt4123_pciconf0 q. A valid value
> takes over the run entirely: the configuration file is not read. Any other
> value is ignored.

# NOTES

> Clears are applied before sets, so -\-clear-module all -\-set-module
> flint:debug in a single command means "drop every override, then enable
> just flint".
>
> -\-show combined with a modification flag does not print; run -\-show on its
> own to inspect.
>
> The configuration file is replaced atomically, so a tool starting while it
> is being written sees either the old contents or the new, never a partial
> file.

# EXAMPLES

> Log the low-level device access layer to a file, reproduce a failure, then
> put things back:
>
> \# mstflintlogger -\-enable-output file -\-set-module mtcr:debug
>
> \# mstflintlogger -\-show
>
> \# mstflint -d /dev/mst/mt4123_pciconf0 q
>
> \# less /var/log/mstflint/mstflint_\<pid\>.log
>
> \# mstflintlogger -\-clear-module mtcr -\-disable-output file

# SEE ALSO

The full documentation for **mstflintlogger,** is maintained as a Texinfo
manual. If the **info** and **mstflintlogger,** programs are properly
installed at your site, the command

> **info mstflintlogger,**

should give you access to the complete manual.
