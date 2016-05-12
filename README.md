# sparkan
How to build:
git clone git@github.com:nhirsl/sparkan.git
mkdir sparkan-build
mkdir sparkan-install
cd sparkan-build
cmake -DCMAKE_INSTALL_PREFIX=../sparkan-install -DCMAKE_BUILD_TYPE=debugfull ../sparkan/src/sparkan
make && make install

Alternatively, open CMakeLists.txt file in QtCreator and run cmake from IDE.
