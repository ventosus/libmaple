MEMORY
{
  ccm (rwx) : ORIGIN = 0x10000000, LENGTH = 4K
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 12K
  rom (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
}
