sudo apt-get install libeigen3-dev libboost-serialization-dev libboost-filesystem-dev libboost-test-dev libboost-program-options-dev libboost-thread-dev libtbb-dev

sudo apt-get -qq update
sudo apt-get -qq --yes --force-yes install autoconf automake
wget http://members.loria.fr/JBMouret/mirrors/nlopt-2.4.2.tar.gz
tar -zxvf nlopt-2.4.2.tar.gz && cd nlopt-2.4.2
./configure -with-cxx --enable-shared --without-python --without-matlab --without-octave
sudo make install
sudo ldconfig
cd ..
