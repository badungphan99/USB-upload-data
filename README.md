# Smart USB

## Preinstall

### Hardware

- Raspberry pi zero w
- SD card

### Software

- ` $ sudo apt-get update `
- ` $ sudo apt-get install libcurl4-openssl-dev cmake git`

## Install

- ` $ git clone https://github.com/badungphan99/USB-upload-data `
- ` $ cd USB-upload-data && mkdir build && cd build && cmake .. && make `
- For first time run ` $ ./init ` it maybe take some time (about 1 hours)
- Run code ` $ ./usb `