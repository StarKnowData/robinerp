@echo off
echo Delete VC Proj temp file  waiting ......
del /f /s /q /a *.scc *.suo *.log *.embed.manifest BuildLog.htm *.intermediate.manifest *.dep *.user *.obj *.idb *.aps *.res *.plg *.opt *.ncb *.bak *.tmp *.idb *.exp *.ilk *.pdb *.tli *.tlh disasm.asm *.trg *.pch *.~* *.ddp readme.txt thumbs.db
echo Delete finish
echo & pause