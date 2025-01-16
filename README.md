# Bedrock Engine

Bedrock is a simple rendering engine built with C++ and OpenGL. This project was developed as a personal exploration to gain deeper insights into rendering techniques and graphics programming in general.

## Features

- Basic rendering capabilities using OpenGL.
- Cross-platform window creation and management.
- Mathematical utilities for graphics programming.

### Prerequisites

To build and run Bedrock Engine, ensure you have the following installed:
- A modern C++ compiler (supporting at least C++20).
- OpenGL (version 4.4 or later).

## Dependencies

Bedrock uses the following libraries:

- [GLFW](https://www.glfw.org): For window creation, input handling, and context management.
- [GLM](https://github.com/g-truc/glm): A header-only library for mathematics, including vector and matrix operations tailored for graphics programming.
- [GLAD](https://glad.dav1d.de): For loading OpenGL function pointers.

These dependencies are included.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

Special thanks to The Cherno for his contribution to C++ tutorials. The engine structure mainly mimics his Game Engine Series despite some shortcuts to make this project as simple as possible for me.

After implementing all the base stuff, the direction for this project is headed to add support for more graphics APIs like Vulkan and DirectX and create demo scenes to test features.

