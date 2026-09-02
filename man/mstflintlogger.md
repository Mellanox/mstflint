
# NAME

mstflintlogger

# SYNPOSIS

> mstflintlogger \[OPTIONS\]
>
> \[-l|-\-set-level \<LEVEL\>\] \[-m|-\-set-module \<MODULE:LEVEL\>\]
> \[-M|-\-clear-module \<MODULE\>\] \[-o|-\-enable-output \<SINK\>\]
> \[-O|-\-disable-output \<SINK\>\] \[-n|-\-set-max-log-files \<COUNT\>\]
> \[-s|-\-show\] \[-r|-\-reset\] \[-c|-\-config-file \<PATH\>\]
> \[-h|-\-help\]

# DESCRIPTION

> mstflintlogger configures the NVIDIA Tools logger used by the mstflint tools. It
> reads and writes a single JSON file, /var/lib/mstflint/mstflintlogger.json, which
> every tool loads once at process start. Verbosity is therefore data, not
> code: no tool flag, no environment variable and no rebuild is involved, and
> one command changes what every tool logs.
>
> Logging is off until it is turned on. With no configuration file present,
> no output is produced at all.
>
> A configuration change affects processes started afterwards; a tool that is
> already running is unaffected.
>
> Severity levels are debug, info, warning, error, fatal and off. A level
> means "this level and above"; off silences the layer. Output sinks are
> stdout, stderr, file and syslog. The file sink writes
> /var/log/mstflint/\<executable\>_\<pid\>.log.
>
> Writing the default configuration file requires root. Use -\-config-file to
> work on an unprivileged copy.

OPTIONS

> mstflintlogger \[OPTIONS\]

  - **-l**|-\-set-level \<LEVEL\>
    : Set the global severity threshold, used by every layer with no override

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
    : Cap the number of .log files kept in the log directory (default: 100).
    Older files beyond the cap are deleted when a new log file is opened

  - **-s**|-\-show
    : Print the configuration and the resolved severity of every layer,
    tagged (override) or (global)

  - **-r**|-\-reset
    : Reset the configuration to defaults, i.e. logging off

  - **-c**|-\-config-file \<PATH\>
    : Operate on a different configuration file
    (default: /var/lib/mstflint/mstflintlogger.json)

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
