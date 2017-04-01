[![Build Status](https://travis-ci.org/westernmagic/NumPDE.svg?branch=master)](https://travis-ci.org/westernmagic/NumPDE)
[![Build status](https://ci.appveyor.com/api/projects/status/1qr8140lmrcfdg9x/branch/master?svg=true)](https://ci.appveyor.com/project/westernmagic/numpde/branch/master)
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

