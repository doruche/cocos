# Cocos

_No longer maintained. I made some wrong design choices and it's now
almost impossible to fix them without rewriting a lot of code.
Feel free to fork and experiment on your own._

Cocos is an experimental microkernel operating system written in C, targeting the RISC-V 64-bit architecture. It is designed for educational purposes and to explore microkernel concepts such as IPC, user-space servers, and capability-based resource management.

## Features

*   **Microkernel Architecture**: Minimal kernel handling IPC, scheduling, and basic memory management (a bit hybrid).
*   **No Permission Mechanism**: The kernel does not enforce permission checks. Cocos is just an experimental OS for learning, and we trust all user-space components.
*   **IPC**: Synchronous message passing and asynchronous notifications.
*   **User-space Servers**:
    *   `pm`: Process Manager.
    *   `vsfs`: Very Simple File System.
    *   `ramdisk`: RAM disk driver.
    *   `uart16550`: Serial driver.
    *   `idle`: Idle task.
    *   `random`: Random number generator.
    *   `echo`: Simple echo server.
*   **User-space Applications**: Shell, standard utilities (`ls`, `mount`, `mkdir`, etc.).
*   **Platform**: We implement an HAL, but now only target QEMU RISC-V  Virt.

## Directory Structure

*   `kernel/`: The core microkernel source code.
    *   `arch/`: Architecture-specific code.
    *   `ipc/`: Inter-Process Communication implementation.
    *   `mm/`: Memory management.
    *   `syscall/`: System call handlers.
    *   `task/`: Task scheduling and management.
*   `uspace/`: User-space components.
    *   `apps/`: User applications (shell, utils).
    *   `libc/`: C library implementation.
    *   `servers/`: System servers (pm, fs, drivers).
*   `libs/`: libcocos - Shared kernel/user libraries.
*   `include/`: Header files.
*   `docs/`: Design documentation.
*   `scripts/`: Build and utility scripts.

## Prerequisites

To build and run Cocos, you need the following tools:

*   **RISC-V Toolchain**: `riscv64-unknown-elf-gcc`, `ld`, etc.
*   **QEMU**: `qemu-system-riscv64` for emulation.
*   **Make**: Build system.
*   **Python 3**: For utility scripts.

## Build & Run

1.  **Build the project**:
    ```bash
    make -j$(nproc)
    ```
    This will build the kernel, user-space libraries, servers, and applications.

    You could specify some kernel configurations in `Config.mk` before building, or pass them as arguments to `make`, e.g. `make KLOG=1 ULOG=1 LLOG=1`.

2.  **Run in QEMU**:
    ```bash
    make run
    ```
    This will start the OS in QEMU. You should see the shell prompt.
    
    `make run-log` is also available to enable serial logging to a file `build/qemu.log`, which is useful for debugging.

3.  **Debug**:
    *   Start GDB server:
        ```bash
        make gdb-server
        ```
    *   Connect with GDB client (in another terminal):
        ```bash
        make gdb-client
        ```

## Build System

For convenience and scalability, we introduce a custom build system based on Makefiles - CBuild (just like Linux's KBuild), whose name stands for _Cocos Build System_. You can find its core implementation in `scripts/build.mk`.

The usage of CBuild is similar to KBuild, but with tons of simplifications. Let's take adding a new server as an example:
- Create a new folder under `uspace/servers/`, e.g. `myserver/`.
- You write some source files in it, e.g. `myserver.c` and `libmyserver.c`.
- Create a `CBuild` file right under `myserver/` with the following content:
    ```makefile
    obj-y := myserver.o libmyserver.o
    ```
- Finally, add the new server to the list of servers in top-level Makefile thus the server will be built and linked into the final image:
    ```makefile
    export SERVERS := \
        ...
        myserver \
        ...
    ```
    And that's it! You have successfully added a new server to Cocos.

Some configuration can also be done easily. For example, we can add a new optional server `fat32` to cocos. To do this, just replace the `obj-y := ...` line in `uspace/servers/fat32/CBuild` with:
```makefile
obj-$(FAT32_SUPPORT) := ...
```
Then, in `Config.mk`, we can enable or disable this server by setting:
```makefile
FAT32_SUPPORT := y # or n
```
Or you can directly pass the configuration when invoking `make`:
```bash
make FAT32_SUPPORT=y ...
```

Sometime your server or application may depend on some custom dependencies. such as for ramfs server, it may depend on a `initrd.img` file to be included in the final image. You can achieve this by fake a custom target in the CBuild file:
```makefile
obj-y := ramfs.o libramfs.o initrd.o
initrd.o: $(TOPDIR)/path/to/initrd.img
    @cp $< $@
```

## Architecture

Cocos follows a microkernel design where the kernel provides minimal mechanisms, and policies are implemented in user-space servers.

*   **Direct IPC**: The primary mechanism for communication between tasks and servers.
*   **Process Management**: The `pm` server manages process creation and lifecycle.
*  **Drivers**: Drivers like `uart16550` and `ramdisk` run in user space.
*  **Name Space**: Each process can have its own namespace managed by the `pm` server, thus allowing isolation and different views of the whole system. `pm` server provides a basic service to publish/unpublish and lookup services by name. And processes can mount/umount services they need to their namespace.(e.g. mounting service `disk0` to `/dev/disk0`, mounting service `fs0` to `/`).
*   **File System**: The `vsfs` server implements the file system, communicating with drivers like `ramdisk`.

## Documentation

More detailed design documents can be found in the `docs/` directory (Note: some documents might be work-in-progress or reflect earlier designs).
