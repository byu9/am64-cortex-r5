# Compile options

```
-mcpu=cortex-r5 
-mfloat-abi=hard 
-mlong-calls 
-fno-exceptions 
-fno-rtti

-Og 

-ffunction-sections 
-fdata-sections 
-g -gdwarf-4 
-Wall -Wextra -Wno-main
 -specs="nosys.specs" 
 ```
 
 # Link Options
 
 ```
-mcpu=cortex-r5
 
-fno-exceptions
-mlong-calls 
-Og 

-ffunction-sections 
-fdata-sections 
-g -gdwarf-4 
-Wall -Wextra -Wno-main
-specs="nosys.specs"  
-Wl,-Map,"out.map" 

-nostartfiles 
-nodefaultlibs 
-nostdlib 
-static 

-Wl,--gc-sections 
-Wl,--no-warn-rwx-segments
```