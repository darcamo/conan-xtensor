from conans import ConanFile, CMake, tools
import shutil
import os


class XtensorConan(ConanFile):
    name = "xtensor"
    version = "0.16.4"
    license = "BSD-3"
    url = "https://github.com/darcamo/conan-xtensor"
    description = "C++ tensors with broadcasting and lazy computing"
    no_copy_source = True
    homepage = "https://github.com/QuantStack/xtensor"
    generators = "cmake"
    # No settings/options are necessary, this is header only

    def requirements(self):
        self.requires("xtl/0.4.12@darcamo/stable")

    def source(self):
        tools.get("https://github.com/QuantStack/xtensor/archive/{0}.zip".format(self.version))
        shutil.move("xtensor-{0}".format(self.version), "sources")

        tools.replace_in_file("sources/CMakeLists.txt", "project(xtensor)",
                              """project(xtensor)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()""")

    def build(self):
        cmake = CMake(self)
        os.mkdir("build")
        shutil.move("conanbuildinfo.cmake", "build/")
        cmake.configure(source_folder="sources", build_folder="build")
        cmake.install()
