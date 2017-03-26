[![Build Status](https://travis-ci.com/westernmagic/NumPDE.svg?token=oXBJR2fnFJyyeSMnYqqk&branch=travis)](https://travis-ci.com/westernmagic/NumPDE)
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

