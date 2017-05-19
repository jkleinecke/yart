from conans import ConanFile, CMake, tools
import os


class YartConan(ConanFile):
    name = "yart"
    version = "0.0.1"
    license = "<Put the package license here>"
    url = "<Package recipe repository url here, for issues about the package>"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake", "txt"
    exports_sources = "src/*", "CMakeLists.txt"
    dev_requires = "gtest/1.8.0@lasote/stable"

    def build(self):
        cmake = CMake(self)
        cmake.definitions["ENABLE_TESTING"] = self.scope.dev
        cmake.configure(source_dir=self.conanfile_directory, build_dir="./")
        cmake.build()
        if self.scope.dev:
            cmake.test()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")    
        
    def package(self):
        self.copy("*.h", dst="include/yart", src="src")
        self.copy("*yart.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["yart"]
