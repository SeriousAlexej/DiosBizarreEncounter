#include "StdH.h"
#include <windows.h>
#include "jojo_events.h"
#include "graphics_exports.h"

static void* orig_addr = NULL;
static char jump_instruction[sizeof(int) + 1] = { char(0xE9), 0, 0, 0, 0 };
static char original_bytes[sizeof(jump_instruction)] = { 0, 0, 0, 0, 0 };

BOOLEAN Attach()
{
  orig_addr = &CEntity::HandleSentEvents;
  int offset = reinterpret_cast<int>(&JoJoHandleSentEvents) - (reinterpret_cast<int>(orig_addr) + sizeof(jump_instruction));
  memcpy(jump_instruction + 1, &offset, sizeof(int));
  memcpy(original_bytes, orig_addr, sizeof(original_bytes));

  int enginedll_base_address = reinterpret_cast<int>(orig_addr) - 0xFEC80;
  _paseSentEvents = reinterpret_cast<CStaticStackArray<CSentEvent>*>(enginedll_base_address + 0x20FCC0);

  p_avtxCommon = reinterpret_cast<CStaticStackArray<GFXVertex>*>  (enginedll_base_address + 0x1F9DC0);
  p_atexCommon = reinterpret_cast<CStaticStackArray<GFXTexCoord>*>(enginedll_base_address + 0x1F9DB0);
  p_acolCommon = reinterpret_cast<CStaticStackArray<GFXColor>*>   (enginedll_base_address + 0x1F9DA0);
  p_aiCommonElements = reinterpret_cast<CStaticStackArray<INDEX>*>(enginedll_base_address + 0x1F9D90);
  graphicsFlushQuads = reinterpret_cast<void(*)(void)>            (enginedll_base_address + 0x5BD90);

  DWORD old_page_mode, dummy;
  if (::VirtualProtect(orig_addr, sizeof(jump_instruction), PAGE_EXECUTE_READWRITE, &old_page_mode) == 0)
    return FALSE;
  memcpy(orig_addr, jump_instruction, sizeof(jump_instruction));
  if (::VirtualProtect(orig_addr, sizeof(jump_instruction), old_page_mode, &dummy) == 0)
    return FALSE;

  return TRUE;
}

BOOLEAN Detach()
{
  ClearEventFactory();

  DWORD old_page_mode, dummy;
  if (::VirtualProtect(orig_addr, sizeof(original_bytes), PAGE_EXECUTE_READWRITE, &old_page_mode) == 0)
    return FALSE;
  memcpy(orig_addr, original_bytes, sizeof(original_bytes));
  if (::VirtualProtect(orig_addr, sizeof(original_bytes), old_page_mode, &dummy) == 0)
    return FALSE;

  return TRUE;
}

BOOLEAN WINAPI DllMain(IN HINSTANCE, IN DWORD reason, IN LPVOID)
{
  switch (reason)
  {
  case DLL_PROCESS_ATTACH:
    return Attach();

  case DLL_PROCESS_DETACH:
    return Detach();

  default:
    return TRUE;
  }
}
