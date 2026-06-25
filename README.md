<p align="center">
  <img src="config/icons/CJ_v2.png" alt="ToonTown MultiTool" width="480">
</p>

A **ToonTown Rewritten** (partial CC support) MultiTool for **Linux and Windows**.

<!-- Hero screenshot goes here. Suggested: top-of-app multitoon tab with
     4 toons enabled, 1200x700 PNG. Drop the file into assets/ and add
     an img tag once available. -->

---

![standard-readme compliant](https://img.shields.io/badge/version-1.0.3-blue)
![standard-readme compliant](https://img.shields.io/badge/phacenet-8a2be2)

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Install](#install)
- [Usage](#usage)
- [Security](#security)
- [Background](#background)
- [License](#license)

---

## Install

- **Windows (exe)**

  - Navigate to the releases tab on the right side of the screen and click it
  - Find the latest release, labelled Vx.x.x
  - Within that release, find the asset labelled **TTR-MultiTool-x.x.x-win64.zip** and download it
  - Open the zipped archive, and extract the **TTR-MultiTool-x.x.x-win64** folder anywhere on your computer.
  - Locate the **TTR-MultiTool.exe** executable and run it. On first download, Windows SmartScreen may show "Windows protected your PC". This is expected for unsigned installers, click "More info" then "Run anyway".
  - Skim the usage section to ensure you understand how to use the tool (or dont't!)

- **Linux (AppImage)**
- Navigate to the releases tab on the right side of the screen and click it.
- Find the latest release, labelled Vx.x.x.
- Within that release, find the asset labelled **TTR-MultiTool-x.x.x-linux.tar.gz** and download it.
- Extract the tarball anywhere on your computer, and from within the directory, run: chmod +x TTR_MultiToolx86_64.AppImage
- Skim the usage section to ensure you understand how to use the tool (or dont't!)

- **Compile from Source**
- Instructions will be minimal, because if you are compiling from source, I assume you know what you are doing
- Linux: requires X11 development headers (libx11-dev)
- Windows: requires MSVC 2022 Build Tools and vcpkg for dependency management
- This repo was written and tested on Linux Mint, using Neovim and uses C++20
- Run "git clone https://github.com/phacenet/CJs-ToonTown-MultiTool.git" in a directory of your choosing
- Ensure you have all of the required dependencies from the Cmake before attempting to compile
- Requires Qt6, socket.io.client-cpp, libcurl, libsodium, openssl
- **Note** A patch to socket.io.client-cpp was made, as Cloudflare upgrades the connection to HTTP/2 when it sees HTTP/2 advertised in TLS, but socket.io-client-cpp only knows how to do WebSocket over HTTP/1.1, hence the patch forces HTTP/1.1.
- websocketpp is incompatible with C++20, so the CMake forces C++17 for the socket.io targets specifically

---


## Usage
- The MultiTool has 6 different "apps" built into it.
    - Launch TTR
    - ToonHQ Auto Group Accept
    - ToonHQ Web Page
    - Dual Toon
    - Doodle Training
    - Invasion Monitor
- **Launch TTR**
    - Launches ToonTown Rewritten from the app. Can store up to **3** different logins at once. All logins are encrypted and stored locally in the config/ToonHQLogin or config/ToontownLogin folders.
    - 


---

## Install



## Usage


```
```

## License

[MIT](LICENSE) © Richard Littauer

by **flossbud**
