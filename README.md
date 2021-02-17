# nopengl

```cpp
// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.
```

## What it is

*nopengl* (named by prepending a random letter to OpenGL and hoping it didn't sound dirty or like a slur), is an extremely lightweight header only C++ library to wrap simple OpenGL commands to simplify them or add error checking.

For the most part, in a release compile, the resulting binary should be as if this library wasn't used. It is simply to make life a little easier. Take, for example, compiling, linking, and verifying shader programs. It's a pain.

Not all bazillion OpenGL features are covered, this grows as it needs to.

## Third Party Code

The plan for nopengl is to use little to no third party code, and none is compulsory. Currently, this is the situation:

* [glad](https://glad.dav1d.de) is included (generated for OpenGL 4.6 Core with no extensions), though can be excluded with a CMake flag if you choose to use your own OpenGL loader or version of glad. They simply must be included before nopengl headers if you choose to not use the included glad.
* [fmt](https://fmt.dev/latest/index.html) is used and required for logging. If you have fmt included in your project another way there is a CMake flag to not download/build it just for nopengl. You can also completely disable logging with another CMake flag. Once compiler vendors have support for C++20 `std::format` this dependency will be removed.
* [GLFW](https://www.glfw.org) is fetched and used **only in the example code**, so is not compulsory.
* [GLM](https://github.com/g-truc/glm) is fetched and used **only in the example code**, so is not compulsory.
* [Catch2](https://github.com/catchorg/Catch2) is fetched and used only if tests are enabled, which is also not compulsory.
* [pwropt](https://github.com/BetaJester/pwropt) is fetched and used for CMake, it's my tool so you can damn well trust it.

## Example

An example is included in the example directory, it attempts to cover several uses of nopengl.

## License(s)

nopengl itself is under the MIT license.
