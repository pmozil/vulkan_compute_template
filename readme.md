# Lab work 6.5: Integrals on vulkan
Authors (team): Petro Mozil (https://github.com/pmozil), Kostya Savarona (https://github.com/KostyaCS)
Variant: Vulkan?

## Prerequisites

Install vulkan and glsl. Here's the rundown:

### Library Installation

#### Vulkan
You will need vulkan tools and libvulkan. Here are the commands:

- `sudo apt install vulkan-tools` or `sudo dnf install vulkan-tools`: Command-line utilities
- `sudo apt install libvulkan-dev` or `sudo dnf install vulkan-loader-devel` : Installs Vulkan loader
- `sudo apt install vulkan-validationlayers-dev spirv-tools` or `sudo dnf install mesa-vulkan-devel vulkan-validation-layers-devel`

!!! On Arch Linux, you can run `sudo pacman -S vulkan-devel` to install all the required tools above. !!!

#### Shaders
Two popular shader compilers are Khronos Group's glslangValidator and Google's glslc. 
The latter has a familiar GCC- and Clang-like usage, so we'll go with that: 
- On Ubuntu, download Google's [unofficial binaries](https://github.com/google/shaderc/blob/main/downloads.md)
    and copy glslc to your `/usr/local/bin`. Note you may need to sudo depending on your permissions. 
- On Fedora use `sudo dnf install glslc`, while on 
- On Arch Linux run sudo `pacman -S shaderc`. 

To test, run `glslc` and it should rightfully complain we didn't pass any shaders to compile:
```
glslc: error: no input files
```


### Compilation

I mean, just a `./compile.sh` will suffice, lol. You may want to do release,
  debug has validation layers enabled, and that's kinda just a wall of text for
  ppl new to vulkan ( /// ^~^ /// )


### Usage

It's just like lab 3: do
```bash
./build/integrate_parallel_vulkan 1 ./config_files/func1.cfg
```
```bash
./build/integrate_parallel_vulkan 2 ./config_files/func2.cfg
```
```bash
./build/integrate_parallel_vulkan 3 ./config_files/func3.cfg
```
And enjoy!

### Important!

Not much, just make sure to install vulkan pls.
If needed, I can also do a crash course on vulkan, lol

### Results

The results are described in detail in [report.md](./report.md)

In short, 10x speedup on the first 2 functions and 2x speedup on the third one.
And that's compared to our fastest CPU implementation
