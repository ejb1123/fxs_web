# fs_fxs-web
s_fxs-web is a  FSServer component that adds custom http endpoints.

# Installation
1. Copy `fs-web.dll` to your **fxserver** directory 
2. Add `fs:web` to the `components.json` file

# Developing

*After setting up dev enviroment run

```
mklink /J ./components/fs-web path_to_fivem/fivem/code/components/fs-web
```

to link the folder to the FiveM code.

* Add `fs-web` to `path_to_fivem/fivem/code/components/config.lua`
* Run premake