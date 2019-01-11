# optical module

just a build framework


# How To

```
1. devtool add sfp-manager https://github.com/inspur-bmc/sfp-manager.git
2. modify sfp-manager_git.bb ,add 
        DEPENDS += "autoconf-archive-native"
3. bitbake sfp-manager
```
