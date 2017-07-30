# fs_fxs-web
**fs_fxs-web** is a  **FXServer** component that adds custom http endpoints.

# Installation
1. Copy `fs-web.dll` to your **fxserver** directory 
2. Add `fs:web` to the `components.json` file

# Developing

* After setting up dev enviroment run

```
git submodule update --init --recursive
.\Build-Scripts\scripts\fxs-components\componentLinker.ps1 -SrcDir $pwd -WorkDir "Path to the fivem repo"
```

to link the folder to the **FiveM** code.

* Run premake5 in the five/code folder