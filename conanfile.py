from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy
from os.path import join


class Animation(ConanFile):
    name = "animation"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    exports_sources = "CMakeLists.txt", "src/*"

    def requirements(self):
        self.requires("glad/0.1.36")
        self.requires("glfw/3.3.8")
        self.requires("freeglut/3.4.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.so*", src="lib", dst="bin")
        self.copy("*.dll", dst="bin", src="bin")

    def package(self):
        #copy(self, "*", join(self.package_folder, "bin"), join(self.source_folder, "bin"))
        cmake = CMake(self)
        cmake.install()