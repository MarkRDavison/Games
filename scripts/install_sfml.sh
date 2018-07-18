pushd .
git clone https://github.com/SFML/SFML.git
echo $PWD
cd SFML
mkdir install
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install -DSFML_BUILD_FRAMEWORKS=FALSE -DBUILD_SHARED_LIBS=FALSE ..
make all install
popd