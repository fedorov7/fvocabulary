# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

include(conan)

conan_add_remote(NAME
                 bincrafters
                 URL
                 https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(REQUIRES
                ${CONAN_EXTRA_REQUIRES}
                OPTIONS
                ${CONAN_EXTRA_OPTIONS}
                BASIC_SETUP
                CMAKE_TARGETS # individual targets to link to
                BUILD
                missing)
