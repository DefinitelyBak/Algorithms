from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("benchmark/1.9.4")
        self.requires("gtest/1.17.0")

    def layout(self):
        cmake_layout(self)