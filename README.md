# ReView
! In the early stages, not yet functional.
`ReView` is a command line interface for daily journaling.

# For development
Main Requirements to build the project without building the docker image:
1. cmake version >= 3.25.1
2. g++ version >= 12

Setup project:
```bash
$ git clone https://github.com/dwclake/review.git
$ cd review
$ git submodule init
$ git submodule update
$ ./vcpkg/bootstrap-vcpkg.sh
```
Build and run project:
```bash
$ cmake -B build -S .
$ cmake --build build
$ ./build/review
```
# License
`ReView` is distributed under the terms of both the MIT license and the Apache License (Version 2.0)
