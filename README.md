# optical module

just a build framework


# How To

```
1. devtool add optical-module https://github.com/inspur-bmc/optical-module.git
2. modify optical-module_git.bb ,add 
        DEPENDS += "autoconf-archive-native"
3. bitbake optical-module
```
