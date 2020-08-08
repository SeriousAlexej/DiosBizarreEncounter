970
%{
#include "StdH.h"
#include "EntitiesMP/AnimationChanger.h"
%}

class CAttachmentAnimator : CRationalEntity
{
name      "AttachmentAnimator";
thumbnail "Thumbnails\\AnimationChanger.tbn";
features  "HasName", "HasTarget", "IsTargetable";

properties:
  1 CTString       m_strName     "Name" 'N' = "Attachment animator",
  2 CEntityPointer m_penTarget   "Target" 'T' COLOR(C_GREEN|0xFF),
  3 ANIMATION      m_iAttachment "Attachment" = 0,

  {
    CAnimData m_attachmentsList;
  }

components:
  1 model   MODEL_CHANGER     "Models\\Editor\\AnimationChanger.mdl",
  2 texture TEXTURE_CHANGER   "Models\\Editor\\Camera.tex"

functions:
  CAnimData* GetAnimData(SLONG slPropertyOffset)
  {
    if (!m_penTarget) {
      return CRationalEntity::GetAnimData(slPropertyOffset);
    }
    
    CModelObject* mo = (IsOfClass(m_penTarget, "AttachmentAnimator") ? ((CAttachmentAnimator*)&*m_penTarget)->GetTargetAttachmentModelObject() : m_penTarget->GetModelObject());
    if (!mo) {
      return CRationalEntity::GetAnimData(slPropertyOffset);
    }

    m_attachmentsList.Clear();
    INDEX numAnims = 0;
    { FOREACHINLIST(CAttachmentModelObject, amo_lnInMain, mo->mo_lhAttachments, itamo) {
      numAnims++;
    }}
    m_attachmentsList.CreateAnimations(numAnims);
    INDEX i = 0;
    FOREACHINLIST(CAttachmentModelObject, amo_lnInMain, mo->mo_lhAttachments, itamo) {
      CModelObject& amo_mo = (*itamo).amo_moModelObject;
      CTFileName modelName = amo_mo.GetName();
      m_attachmentsList.SetName(i++, modelName.FileName());
    }
    return &m_attachmentsList;    
  }

  CModelObject* GetTargetAttachmentModelObject()
  {
    if (!m_penTarget) {
      return NULL;
    }
    CModelObject* mo = (IsOfClass(m_penTarget, "AttachmentAnimator") ? ((CAttachmentAnimator*)&*m_penTarget)->GetTargetAttachmentModelObject() : m_penTarget->GetModelObject());
    if (!mo) {
      return NULL;
    }
    CAttachmentModelObject* amo = NULL;
    
    INDEX i = 0;
    { FOREACHINLIST(CAttachmentModelObject, amo_lnInMain, mo->mo_lhAttachments, itamo) {
      if (i++ == m_iAttachment) {
        amo = &(*itamo);
      }
    }}

    if (!amo) {
      return NULL;
    }
    return &amo->amo_moModelObject;
  }

procedures:
  Main()
  {
    InitAsEditorModel();
    SetPhysicsFlags(EPF_MODEL_IMMATERIAL);
    SetCollisionFlags(ECF_IMMATERIAL);

    SetModel(MODEL_CHANGER);
    SetModelMainTexture(TEXTURE_CHANGER);

    if (m_penTarget!=NULL && 
      !IsOfClass(m_penTarget, "ModelHolder2") && 
      !IsOfClass(m_penTarget, "AttachmentAnimator")) {
      WarningMessage("Target must be ModelHolder2 or AttachmentAnimator!");
      m_penTarget=NULL;
    }
    if (m_penTarget==NULL) {
      return;
    }
    
    wait() {
      on (EBegin) : { resume; }
      on(EChangeAnim eChange) : {
        CModelObject* mo = GetTargetAttachmentModelObject();
        if (mo)
        {
          if (mo->GetData()!=NULL) {
            mo->PlayAnim(eChange.iModelAnim, eChange.bModelLoop?AOF_LOOPING:0);
          }
          if (mo->mo_toTexture.GetData()!=NULL) {
            mo->mo_toTexture.PlayAnim(eChange.iTextureAnim, eChange.bTextureLoop?AOF_LOOPING:0);
          }
        }
        resume;
      }
    }
    return;
  }
};
