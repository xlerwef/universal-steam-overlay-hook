# Overview

Universal steam overlay hook. Injector GUI is relatively useless at the moment.

# Why
Steam is worse than big brother and hooks all supported game's D3D Present, VTable swap, etc. dependent on the DX api version utilized by the game. They also support Vulkan from what I can tell digging around in the renderer module. The weirdest thing about this is they do this regardless of whether or not the steam overlay is enabled in the user's Steam settings. 

For D3D11 - Given that they're hooking present, the first 5 bytes of the game's present function are replaced with a jump to steam's callback present, where they render the overlay, like friends list, recording, fps, etc. You'd think the simplest path would be to place our jump a few bytes after theirs, so their callback remains in tact. But, to my dismay this results in some sort of stack corruption down the line and resutls in a crash. Rather than figuring out where this is going wrong, it's much simpler to place our own jump inside their callback present function. Now, thanks to their oddities, we have a universal hook that works on 90% of steam games! (Only for D3D11 at the moment, though I plan to add support for 9, 11, 12 and Vulkan.)

# Build
Download and install vcpkg

Install polyhook:x64-windows-static, spdlog:x64-windows-static

vcpkg integrate install

vcpkg integrate project
test

# Usage

Right now with the lackluster GUI, process name is hardcoded. In order to inject to a specific process, needs be set in Injector/Injector.cpp and it's the process var.

F5 to inject with GUI selected, Hack.dll in the same directory as the Injector.exe.