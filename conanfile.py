from conans import ConanFile, CMake

class ArbitraryName(ConanFile):
    name = "rapidcheck"
    version = "2016.10.24"
    branch = "master"
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    license = "BSD"
    url = "https://github.com/TyRoXx/rapidcheck"
    exports = "CMakeLists.txt", "include*", "src*", "ext*", "extras*"

    def source(self):
        pass

    def build(self):
        cmake = CMake(self.settings)
        self.run("mkdir _build")
        self.run('cd _build && cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=../install %s' %
            cmake.command_line
        )
        if self.settings.os == "Windows":
            self.run("cd _build && cmake --build . %s --target install --config %s" % (cmake.build_config, self.settings.build_type))
        else:
            self.run("cd _build && cmake --build . %s -- -j2 install" % cmake.build_config)

    def package(self):
        self.copy(pattern="*.h*", dst="include", src="include", keep_path=True)
        self.copy(pattern="*.a", dst="lib", src="install/lib", keep_path=False)
        self.copy(pattern="*.lib", dst="lib", src="install/lib", keep_path=False)
        self.copy(pattern="*.pdb", dst="bin", src="install/lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["rapidcheck"]
