#include "StdH.h"
#include "graphics_exports.h"

extern CStaticStackArray<GFXVertex>*   p_avtxCommon = NULL;
extern CStaticStackArray<GFXTexCoord>* p_atexCommon = NULL;
extern CStaticStackArray<GFXColor>*    p_acolCommon = NULL;
extern CStaticStackArray<INDEX>*       p_aiCommonElements = NULL;
extern void (*graphicsFlushQuads)(void) = NULL;
extern TBlendFuncType          glBlendEquation = NULL;
extern TGetIntegerFuncType     glGetIntegerv = NULL;
extern TReadPixelsFuncType     glReadPixels = NULL;
extern TEnableFuncType         glEnable = NULL;
extern TActiveTextureFuncType  glActiveTexture = NULL;
extern TGenTexturesFuncType    glGenTextures = NULL;
extern TBindTextureFuncType    glBindTexture = NULL;
extern TTexImage2DFuncType     glTexImage2D = NULL;
extern TDeleteTexturesFuncType glDeleteTextures = NULL;
extern TTexParameteriFuncType  glTexParameteri = NULL;

extern void graphicsResetArrays(void)
{
  p_avtxCommon->PopAll();
  p_atexCommon->PopAll();
  p_acolCommon->PopAll();
  p_aiCommonElements->PopAll();
}

extern INDEX PixelFormatSize(D3DFORMAT d3dFormat)
{
  switch(d3dFormat)
  {
  case D3DFMT_X8R8G8B8:
  case D3DFMT_A8R8G8B8:
    return 4;
  case D3DFMT_R8G8B8:
    return 3;
  case D3DFMT_R5G6B5:
  case D3DFMT_X1R5G5B5:
  case D3DFMT_A1R5G5B5:
  case D3DFMT_X4R4G4B4:
  case D3DFMT_A4R4G4B4:
    return 2;
  default:
    return 1; // unknown
  }
}
