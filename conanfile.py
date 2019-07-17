from conans import ConanFile, CMake, tools
import shutil
import os


class XtensorConan(ConanFile):
    name = "xtensor"
    version = "0.20.8"
    license = "BSD-3"
    url = "https://github.com/darcamo/conan-xtensor"
    description = "C++ tensors with broadcasting and lazy computing"
    no_copy_source = True
    homepage = "https://github.com/QuantStack/xtensor"
    generators = "cmake"
    # No settings/options are necessary, this is header only

    # TODO: Add option for openmp that sets USE_OPENMP in CMake

    def requirements(self):
        self.requires("xtl/0.6.4@darcamo/stable")
        self.requires("xsimd/7.2.3@darcamo/stable")

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
        cmake.definitions["XTENSOR_USE_XSIMD"] = "ON"
        cmake.configure(source_folder="sources", build_folder="build")
        cmake.install()

    def package_info(self):
        try:
            shutil.move("lib64", "lib")
        except Exception:
            pass
