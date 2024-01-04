# AUTOGIT

A command line app for automating `git add .` , `git commit -m` and `git push`.

## Building from Source

- **Install meson**

  For example:

  ```bash
  apt install meson # for ubuntu or debian based distro
  ```

  it can also be installed using pip by running `pip install meson`.

  Please refer to [Meson Build](https://github.com/mesonbuild/meson) repo for other installations.

- **Install Ninja**
  for example
  ```bash
  apt install ninja # for ubuntu or debian based distro
  ```
  ```bash
  yum install ninja # for redhat or fedora based distro
  ```
  Please refer to [Ninja Build](https://github.com/ninja-build/ninja) repo for other installations.
- **Clone This Repository**
  ```bash
  git clone https://github.com/dev5h/autogit.git && cd autogit
  ```
- **Run Build Commands**
  `bash
    meson build
    cd build
    ninja install
    `
  And that should complete the installation . You might need `sudo` to install it depends on your system.
