967
%{
#include "StdH.h"
%}

class EventProperty : CEntity {
  name "EventProperty";
  thumbnail "Thumbnails\\Marker.tbn";
  features "IsImportant";

properties:
  1 FLOAT m_fVal = 0.0f,
  2 INDEX m_iVal = 0,
  3 BOOL  m_bVal = FALSE,
  4 CEntityPointer m_pVal,
  5 CTString m_sVal = "",
  6 CTFileName m_fnmVal = "",
  7 FLOATplane3D m_p3dVal = FLOATplane3D(FLOAT3D(1,0,0),0),
  8 FLOAT3D m_f3dVal = FLOAT3D(0, 0, 0),
  9 COLOR m_cVal = C_WHITE,
 10 FLOATmatrix3D m_m3dVal = FLOATmatrix3D(0),

components:
  1 model   MODEL_MARKER     "Models\\Editor\\Axis.mdl",
  2 texture TEXTURE_MARKER   "Models\\Editor\\Vector.tex"

functions:

  void FromProperty(void* prop, INDEX type)
  {
    switch (type)
    {
    case EVENTPROP_FLOAT:
      m_fVal = *((FLOAT*)prop);
      break;
    case EVENTPROP_INDEX:
      m_iVal = *((INDEX*)prop);
      break;
    case EVENTPROP_BOOL:
      m_bVal = *((BOOL*)prop);
      break;
    case EVENTPROP_CEntity_PTR:
      m_pVal = *((CEntity**)prop);
      break;
    case EVENTPROP_CEntityPointer:
      m_pVal = *((CEntityPointer*)prop);
      break;
    case EVENTPROP_CTString:
      m_sVal = *((CTString*)prop);
      break;
    case EVENTPROP_CTFileName:
      m_fnmVal = *((CTFileName*)prop);
      break;
    case EVENTPROP_FLOATplane3D:
      m_p3dVal = *((FLOATplane3D*)prop);
      break;
    case EVENTPROP_FLOAT3D:
      m_f3dVal = *((FLOAT3D*)prop);
      break;
    case EVENTPROP_COLOR:
      m_cVal = *((COLOR*)prop);
      break;
    case EVENTPROP_FLOATmatrix3D:
      m_m3dVal = *((FLOATmatrix3D*)prop);
      break;
    case EVENTPROP_CModelData_PTR:
      GetModelObject()->SetData(*(CModelData**)prop);
      break;
    case EVENTPROP_CTextureData_PTR:
      GetModelObject()->mo_toTexture.SetData(*(CTextureData**)prop);
      break;

    default:
      CPrintF("^cff0000ERROR: EventProperty::FromProperty - Unknown property type %d!^C\n", type);
      break;
    }
  }

  void ToProperty(void* prop, INDEX type)
  {
    switch (type)
    {
    case EVENTPROP_FLOAT:
      *((FLOAT*)prop) = m_fVal;
      break;
    case EVENTPROP_INDEX:
      *((INDEX*)prop) = m_iVal;
      break;
    case EVENTPROP_BOOL:
      *((BOOL*)prop) = m_bVal;
      break;
    case EVENTPROP_CEntity_PTR:
      *((CEntity**)prop) = m_pVal.ep_pen;
      break;
    case EVENTPROP_CEntityPointer:
      *((CEntityPointer*)prop) = m_pVal;
      break;
    case EVENTPROP_CTString:
      *((CTString*)prop) = m_sVal;
      break;
    case EVENTPROP_CTFileName:
      *((CTFileName*)prop) = m_fnmVal;
      break;
    case EVENTPROP_FLOATplane3D:
      *((FLOATplane3D*)prop) = m_p3dVal;
      break;
    case EVENTPROP_FLOAT3D:
      *((FLOAT3D*)prop) = m_f3dVal;
      break;
    case EVENTPROP_COLOR:
      *((COLOR*)prop) = m_cVal;
      break;
    case EVENTPROP_FLOATmatrix3D:
      *((FLOATmatrix3D*)prop) = m_m3dVal;
      break;
    case EVENTPROP_CModelData_PTR:
      *((CModelData**)prop) = GetModelObject()->GetData();
      break;
    case EVENTPROP_CTextureData_PTR:
      *((CTextureData**)prop) = (CTextureData*)GetModelObject()->mo_toTexture.GetData();
      break;

    default:
      CPrintF("^cff0000ERROR: EventProperty::ToProperty - Unknown property type %d!^C\n", type);
      break;
    }
  }

procedures:
  Main()
  {
    InitAsEditorModel();
    SetPhysicsFlags(EPF_MODEL_IMMATERIAL);
    SetCollisionFlags(ECF_IMMATERIAL);
    SetModel(MODEL_MARKER);
    SetModelMainTexture(TEXTURE_MARKER);

    return;
  }
};
