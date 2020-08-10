from conans import CMake, ConanFile, tools


class CppProjectConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch", "arch_build"
    generators = "cmake"

    options = {"with_tests": [True, False]}
    default_options = {"with_tests": False}

    _cmake = None

    @property
    def _build_subfolder(self):
        return "build_subfolder"

    def requirements(self):
        if self.options.with_tests:
            self.requires.add("catch2/2.11.0")

    def _configure_cmake(self):
        if self._cmake:
            return self._cmake

        self._cmake = CMake(self)
        self._cmake.verbose = True
        self._cmake.definitions["ENABLE_TESTING"] = self.options.with_tests
        self._cmake.configure(build_folder=self._build_subfolder)
        return self._cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
