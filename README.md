#INSTALL
copy fs-web.dll to the fxserver.exe directory and then add `fs:web` to the `components.json`

#HACKING

*After setting up dev enviroment run

```
mklink /J ./components/fs-web path_to_fivem/fivem/code/components/fs-web
```

to link the folder to the FiveM code.

* Add `fs-web` to `path_to_fivem/fivem/code/components/config.lua`
* Run premake