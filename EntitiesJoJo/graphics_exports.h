#ifndef JOJO_GRAPHICS_EXPORTS_H
#define JOJO_GRAPHICS_EXPORTS_H

#define GL_TEXTURE0           0x84C0
#define GL_ACTIVE_TEXTURE     0x84E0
#define GL_FUNC_SUBTRACT      0x800A
#define GL_BLEND_EQUATION_RGB 0x8009

typedef void (__stdcall* TBlendFuncType)         (GLenum);
typedef void (__stdcall* TGetIntegerFuncType)    (GLenum, GLint*);
typedef void (__stdcall* TReadPixelsFuncType)    (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*);
typedef void (__stdcall* TEnableFuncType)        (GLuint);
typedef void (__stdcall* TActiveTextureFuncType) (GLenum);
typedef void (__stdcall* TGenTexturesFuncType)   (GLsizei, GLuint*);
typedef void (__stdcall* TBindTextureFuncType)   (GLenum, GLuint);
typedef void (__stdcall* TTexImage2DFuncType)    (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*);
typedef void (__stdcall* TDeleteTexturesFuncType)(GLsizei, const GLuint*);
typedef void (__stdcall* TTexParameteriFuncType) (GLenum, GLenum, GLint);

extern TBlendFuncType          glBlendEquation;
extern TGetIntegerFuncType     glGetIntegerv;
extern TReadPixelsFuncType     glReadPixels;
extern TEnableFuncType         glEnable;
extern TActiveTextureFuncType  glActiveTexture;
extern TGenTexturesFuncType    glGenTextures;
extern TBindTextureFuncType    glBindTexture;
extern TTexImage2DFuncType     glTexImage2D;
extern TDeleteTexturesFuncType glDeleteTextures;
extern TTexParameteriFuncType  glTexParameteri;

extern CStaticStackArray<GFXVertex>*   p_avtxCommon;
extern CStaticStackArray<GFXTexCoord>* p_atexCommon;
extern CStaticStackArray<GFXColor>*    p_acolCommon;
extern CStaticStackArray<INDEX>*       p_aiCommonElements;
extern void graphicsResetArrays(void);
extern void (*graphicsFlushQuads)(void);

extern INDEX PixelFormatSize(D3DFORMAT d3dFormat);

#endif