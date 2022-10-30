# HWC-Cache
This is *LFU (least frequently used)* cache emulation written in *C++*. This type of cache stores memory pages with high hit rate and replaces pages with low frequency with the new ones in case there is not enough free space to fit them both. Cached pages have low access time and others are loaded with slow lookup method provided by user.

## Usage
This section isn't done yet.

## Building from source
#### Downloading
Download this repository with

```bash
git clone https://github.com/nerett/hwc-cache.git
```

#### Installing dependencies
Install required packages automatically with

```bash
make install-dependencies-pkg PACKAGEMANAGER=<your-package-manager-name> #apt is used if PACKAGEMANAGER is not defined
```

...or install them manually with your distro package manager (check list [here](https://github.com/nerett/hwc-cache#Dependencies)).

#### Building
Build `hwc-cache` as a standalone program with

```bash
make MODE=DEBUG #or MODE=RELEASE; MODE=RELEASE if not defined
```

#### Running
You can run builded release/debug version of standalone `hwc-cache` with

```bash
make run MODE=DEBUG #MODE=RELEASE if MODE is not defined
```

Use `rund` instead of `run` to run with `valgrind`

...or run this binary with manually from project directory.

#### Rebuilding
To totally rebuild the project run

```bash
make clean
make MODE=<modename>
```

## Dependencies
This project actually depends on `libc` and building requires `make`, `g++` and `git` (it can also require `valgrind` installed to use `rund` target).

## Documentation
This section isn't done yet.

## About project
This programm was written during MIPT **Vladimirov's** cource.
