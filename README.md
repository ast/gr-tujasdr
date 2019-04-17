# gr-tujasdr

GNURadio blocks for TujaSDR trx

## Building

```bash
# Host

cmake -DENABLE_DOXYGEN=OFF -DENABLE_PYTHON=OFF ..

# Cross
# See https://github.com/TujaSDR/gnuradio-rbpi3

cmake -DPYTHON_EXECUTABLE=/usr/bin/python3.5 -DENABLE_DOXYGEN=OFF -DCMAKE_TOOLCHAIN_FILE=$SDKPATH/rbpi3.cmake ..
```
