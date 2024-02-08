rm -r Examples build.sh LICENSE README.md 
g++ Siddhi.cpp -o Siddhi &&
g++ mSiddhi.cpp -o mSiddhi &&
cd base &&
g++ * &&
cd .. &&
cd Modules/headers &&
g++ * &&
cd ..
