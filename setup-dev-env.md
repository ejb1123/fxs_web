1. Install windows 10
2. Install [python2.7-x86_64](https://www.python.org/ftp/python/2.7.13/python-2.7.13.amd64.msi)
    * Install to `C:\FiveM-dev\python27`
3. Install [7-zip](http://7-zip.org/download.html)
4. Install [premake5](https://premake.github.io/download.html#v5)
    * Install to `C:\FiveM-dev\premake5`
5. Install [git](https://git-scm.com/download/win)
6. Install [Visual Studio Installer](https://aka.ms/vsdownload)
7. Install Visual Studio Community 2017
    - components
        * Desktop Development with C++
        * .NET desktop development

8. Download [Boost files](https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.7z/download)
    * Location C:\FiveM-dev\boost

9. Create dev.env.ps1
    * Location `C:\FiveM-dev\dev.env.ps1`
    ```POWERSHELL
    $env:PYTHON="C:\FiveM-dev\Python27"
    $env:PATH="C:\FiveM-dev\Premake5\;C:\FiveM-dev\Python27;$env:PATH"
    $env:BOOST_ROOT="C:\FiveM-dev\boost"
    ```

10. Clone the repo
    * `git clone https://github.com/citizenfx/fivem.git`

11. get submodules
    * `git update --init --recursive`
12. Run premake5
    * `premake5 --game=server vs2017`