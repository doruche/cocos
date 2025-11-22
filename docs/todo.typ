这里记录一些不明且尚未解决的问题.

- 启动的时候pm有小概率直接crash, 暂时原因不明
- uart16550启动时小概率(就遇到过一次)可能发生以下异常:
  ```bash
  [NOTIFY|kernel/arch/trap/utrap.c:134]   task page fault: tid=2 name=uart16550 addr=0x80207938 pc=0x80207938 exccode=Instruction page fault
  ```
  这里的pc在console_putc的ret处, 不是很清楚为什么......
  如果我把kernel的log级别开到trace, 应该能发现具体原因, 但是我没开......现在也很难复现, 等有机会再说吧.