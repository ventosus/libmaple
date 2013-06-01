MEMORY
{
  ccm (rwx) : ORIGIN = 0x10000000, LENGTH = 0K
  ram (rwx) : ORIGIN = 0x20000C00, LENGTH = 17K
  rom (rx)  : ORIGIN = 0x08005000, LENGTH = 0K
}
