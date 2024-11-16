# AVR I2C Driver Example

This project is to have a simple example of an primary I2C communication on an ATtiny85 with documentation.

Supports writing and reading from secondary devices.

## Project Structure

- `src` The main source code folder
- `src/main.c` The main file for using the I2C driver.
- `src/driver/i2c.[h|c]` The I2C driver implementation files.
- `install_deps.sh` Run this to install all the tools needed to build and flash AVR projects.
- `Makefile` Contains commands to build and burn the AVR project.
- `compile_flags.txt` Contains setup flags to work with the C LSP (clangd)

## Demo

The demo has an ATtiny85 loaded with the code in this project hooked up to an arduino uno using the Wire library to
act as a secondary device to talk to.

Actions performed:
- The primary (ATtiny85) sends "Hello, World!" to the secondary (Arduino Uno) device.
- The primary requests a read from the secondary to toggle the LED.

https://github.com/user-attachments/assets/6c168a57-7b3c-4304-adfc-d2d9f486735c

## USBTiny

If using USBTiny programmer on linux you may have to run the upload command with sudo because
of permission issues.

## Setup in WSL

If you are trying to develop in WSL you need to forward the USB device onto the WSL environment.

1. Start by downloading this utility program `winget install --interactive --exact dorssel.usbipd-win`

2. Look for the USB port the arduino is using.

```bash
$ usbipd list
```

3. Bind the USB port

```bash
$ usbipd bind --busid <port> # example would be 1-2
```

4. Attach to WSL environment

```bash
$ usbipd attach --wsl --busid <port>
```

5. Verify the USB port on WSL.

If you do not have lsusb find whatever your system uses.

This will list the USB ports you have access to and the arduino port should be in the list.

```bash
$ lsusb
```

Once done you can just detach the USB port.

