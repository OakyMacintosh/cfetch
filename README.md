# cfetch

cfetch is a fast, modular system information utility written in ANSI C Unix-like systems. It displays essential system info in a colorful, easy-to-read format, similar to neofetch, fastfetch, and pfetch, but without ASCII art.

## Features
- Modular info display (OS, kernel, hostname, username, uptime, shell, time)
- Colorful output
- CLI arguments: `--help`, `--version`, `--minimal`, `--all`
- BSD License

## Usage
Build:
```
make
```

Run:
```
./cfetch [--help | --version | --minimal | --all]
```

## Example Output
```
OS: Apple UNIX
Kernel: System V UNIX X.X.X.X
Hostname: Oakys-Macintosh-Quadra
User: oaky
Uptime: 2 days, 4 hours, 12 mins
Shell: /bin/csh
Time: 2026-02-22 14:32:10
```

## License
BSD License


