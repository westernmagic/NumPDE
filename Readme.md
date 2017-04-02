[![Travis branch](https://img.shields.io/travis/westernmagic/NumPDE/master.svg)](https://travis-ci.org/westernmagic/NumPDE)
[![AppVeyor branch](https://img.shields.io/appveyor/ci/westernmagic/NumPDE/master.svg)](https://ci.appveyor.com/project/westernmagic/numpde/branch/master)
[![Coverity Scan](https://img.shields.io/coverity/scan/12234.svg)](https://scan.coverity.com/projects/westernmagic-numpde)
# NumPDE FS 2017

## Cloning
```
git clone --recursive https://github.com/westernmagic/NumPDE.git
```

Then edit [Settings.cmake](Settings.cmake) appropiately.


## `master` branch
Contains my solutions

### Building
```
cd seriesX
mkdir -p build
cd build
cmake ..
cmake --build .
```

### Testing
```
ctest
```

### Generating submissions
```
cmake --build . --target package_source
```

## `handouts` branch
Contains official handouts

## `solutions` branch
Contains official solutions

