## At a glance
A step-by-step tutorial for building an out-of-source LLVM pass based on Adrian Sampson's "LLVM for Grad Students"

## Setup

LLVM is an umbrella project for building compilers
and code transformation tools. We consider in this tutorial:
- Building LLVM from source
- Building a trivial out-of-source LLVM pass.

We will be using LLVM version `3.8`. We assume that you have a working compiler toolchain (GCC or LLVM) and that CMake is installed (minimum version 3.4.3). Additionally, we assume that you have the corresponding `Clang` already installed. You can easily obtain `Clang` using:

```bash
$ sudo apt-get install clang-3.8
```
Clang is the compiler front-end, the tool that takes C/C++ code as input and
transforms it to LLVM IR. This command will also install LLVM itself.



### Compiling LLVM
Compiling LLVM is mandatory if you are building an in-source pass (within LLVM source tree). It can also be convenient to give you full control over LLVM compilation options.

1.  Download LLVM [source](http://llvm.org/releases/)
and unpack it in a directory of your choice which will refer to as `$LLVM_SRC`

2. Create a separate build directory
    ```bash
    $ mkdir llvm-build
    $ cd llvm-build
    ```
3. Instruct CMake to detect and configure your build environment:

    ```bash
    $ cmake $LLVM_SRC
    ```
4. Now start the actual compilation within your build directory

    ```bash
    $ cmake --build .
    ```
    The --build option is a portable why to tell cmake to invoke the underlying
    build tool (make, ninja, xcodebuild, msbuild, etc.)

5. Building will take a while, after that you can install LLVM in its default directory
    which is `/usr/local`
    ```bash
    $ cmake --build . --target install
    ```
    It's possible to set a different install directory ($LLVM_HOME) at installation
    time using
    ```bash
    $ cmake -DCMAKE_INSTALL_PREFIX=$LLVM_HOME -P cmake_install.cmake
    ```
    Note that $LLVM_HOME must `not` contain `~`(tilde) to refer to your home directory as
    it won't be expanded. Use an absolute path instead.

# LLVM-Testing
$ cc -c rtlib.c
$ clang -Xclang -load -Xclang build/skeleton/libSkeletonPass.so -c example.c
$ cc example.o rtlib.o
$ ./a.out