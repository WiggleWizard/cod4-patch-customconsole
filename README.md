# CoD4 RCON Custom Console
#### What does it patch?
This patch will unjail the console, removing the "console: " prepend on every rcon `say` command.

#### How do I use this patch?
##### Compile or Binary
You can use this patch by either:
  * Compile by running `make` in the root of the repo then run the compiled ELF.  
    -OR-
  * [Download](https://github.com/Zinglish/cod4-patch-customconsole/blob/master/cod4-patch-customconsole-deb-x64?raw=true) the ELF that's already precompiled for x64 Debian flavours of Linux.  

##### Usage
Binary takes 1 parameter. The last parameter of the command should be the path to the CoD4 Server binary you wish to patch. EG: `cod4-patch-customconsole cod4-lnxded`.

### Patching details
This patcher hard patches the short bytes inside the ELF.
```text
 --------------------------
| OFFSET     | FROM | TO   |
|------------|------|------|
| 0x00124DDF | 63   | 5E   |
| 0x00124DE0 | 6F   | 37   |
| 0x00124DE1 | 6E   | 5E   |
| 0x00124DE2 | 73   | 37   |
|            |      |      |
| 0x00124DE9 | 6F   | 5E   |
| 0x00124DEA | 6C   | 37   |
| 0x00124DEB | 65   | 5E   |
| 0x00124DEC | 3A   | 37   |
|            |      |      |
|            |      |      |
| 0x00125407 | 63   | 5E   |
| 0x00125408 | 6F   | 37   |
| 0x00125409 | 6E   | 5E   |
| 0x0012540A | 73   | 37   |
|            |      |      |
| 0x00125411 | 6F   | 5E   |
| 0x00125412 | 6C   | 37   |
| 0x00125413 | 65   | 5E   |
| 0x00125414 | 3A   | 37   |
 --------------------------
```

### Bugs
There is a small space that's prepended on to the message in the `say` rcon command, this is hardly noticable however.
