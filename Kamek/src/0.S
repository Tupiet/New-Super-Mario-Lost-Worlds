.text
#include <asm_setup.S>
.extern OSReport

.align 4

.global reportCrashAdress
reportCrashAdress:
  .int 0
  lis r3, output@h
  ori r3, r3, output@l
  mtsprg 0, r4
  mfsrr0 r4
  addi r4, r4, 0x4
  mtsrr0 r4
  mfsprg r4, 0
  bl OSReport
  rfi



output: .string "Game crashed at address: 0x%08x\n"