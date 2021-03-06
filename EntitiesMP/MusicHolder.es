222
%{
#include "StdH.h"
#include "EntitiesMP/EnemyBase.h"
#include "EntitiesMP/EnemySpawner.h"
#include "EntitiesMP/Trigger.h"
#include "EntitiesMP/Woman.h"
#include "EntitiesMP/PlayerWeapons.h"
#include "EntitiesMP/MovingBrush.h"
#include "EntitiesMP/MovingBrushMarker.h"
#include "EntitiesMP/Camera.h"
#include "EntitiesMP/CameraMarker.h"
#include "EntitiesMP/Reminder.h"
#include "EntitiesJoJo/TheWorld.h"
#include "EntitiesJoJo/DioPosing.h"
#include "EntitiesJoJo/jojo_events.h"
#include "EntitiesJoJo/entitycast.h"
#include "EntitiesJoJo/RodaRollaDa.h"
#include "EntitiesJoJo/EventStorage.h"
#include "EntitiesJoJo/EventEntity.h"
#include "EntitiesJoJo/EventProperty.h"
#include "EntitiesJoJo/EntityHashTable.h"
#include <Engine/Templates/Stock_CTextureData.h>
#include <vector>
#include <utility>

typedef std::pair<CBrushPolygonTexture*, UBYTE> TTextureScrollPair;
typedef std::vector<TTextureScrollPair> TTexturesVector;
static TTexturesVector all_textures;
extern TIME g_dioTime;
%}

uses "EntitiesJoJo/jojo_events";

enum MusicType {
  0 MT_LIGHT  "light",
  1 MT_MEDIUM "medium",
  2 MT_HEAVY  "heavy",
  3 MT_EVENT  "event",
  4 MT_CONTINUOUS  "continuous",
};

event EChangeMusic {
  enum MusicType mtType,
  CTFileName fnMusic,
  FLOAT fVolume,
  BOOL bForceStart,
};

%{
#define MUSIC_VOLUMEMIN   0.02f     // minimum volume (considered off)
#define MUSIC_VOLUMEMAX   0.98f     // maximum volume (considered full)

float FadeInFactor(TIME fFadeTime)
{
  return (float) pow(MUSIC_VOLUMEMAX/MUSIC_VOLUMEMIN, 1/(fFadeTime/_pTimer->TickQuantum));
}
float FadeOutFactor(TIME fFadeTime)
{
  return (float) pow(MUSIC_VOLUMEMIN/MUSIC_VOLUMEMAX, 1/(fFadeTime/_pTimer->TickQuantum));
}
%}

class CMusicHolder : CRationalEntity {
name      "MusicHolder";
thumbnail "Thumbnails\\MusicHolder.tbn";
features "HasName", "IsTargetable", "IsImportant";

properties:
  1 CTString m_strName     "" = "MusicHolder",
  2 FLOAT m_fScoreMedium "Score Medium" = 100.0f,
  3 FLOAT m_fScoreHeavy  "Score Heavy"  = 1000.0f,

 10 CTFileName m_fnMusic0 "Music Light" 'M' = CTFILENAME(""),
 11 CTFileName m_fnMusic1 "Music Medium"    = CTFILENAME(""),
 12 CTFileName m_fnMusic2 "Music Heavy"     = CTFILENAME(""),
 13 CTFileName m_fnMusic3                   = CTFILENAME(""),  // event music
 14 CTFileName m_fnMusic4                   = CTFILENAME(""),  // continuous music

 20 FLOAT m_fVolume0  "Volume Light" 'V' = 1.0f,
 21 FLOAT m_fVolume1  "Volume Medium"    = 1.0f,
 22 FLOAT m_fVolume2  "Volume Heavy"     = 1.0f,
 23 FLOAT m_fVolume3                     = 1.0f,  // event volume
 24 FLOAT m_fVolume4                     = 1.0f,  // continuous volume

// internals

100 CEntityPointer m_penBoss,    // current boss if any
102 CEntityPointer m_penCounter,   // enemy counter for wave-fight progress display
104 INDEX m_ctEnemiesInWorld = 0,   // count of total enemies in world
105 CEntityPointer m_penRespawnMarker,    // respawn marker for coop
106 INDEX m_ctSecretsInWorld = 0,   // count of total secrets in world
101 FLOAT m_tmFade = 1.0f,    // music cross-fade speed
103 enum MusicType m_mtCurrentMusic = MT_LIGHT, // current active channel

// for cross-fade purposes
110 FLOAT m_fCurrentVolume0a  = 1.0f,
210 FLOAT m_fCurrentVolume0b  = 1.0f,
111 FLOAT m_fCurrentVolume1a  = 1.0f,
211 FLOAT m_fCurrentVolume1b  = 1.0f,
112 FLOAT m_fCurrentVolume2a  = 1.0f,
212 FLOAT m_fCurrentVolume2b  = 1.0f,
113 FLOAT m_fCurrentVolume3a  = 1.0f,
213 FLOAT m_fCurrentVolume3b  = 1.0f,
114 FLOAT m_fCurrentVolume4a  = 1.0f,
214 FLOAT m_fCurrentVolume4b  = 1.0f,

// the music channels
120 CSoundObject m_soMusic0a,
220 CSoundObject m_soMusic0b,
121 CSoundObject m_soMusic1a,
221 CSoundObject m_soMusic1b,
122 CSoundObject m_soMusic2a,
222 CSoundObject m_soMusic2b,
123 CSoundObject m_soMusic3a,
223 CSoundObject m_soMusic3b,
124 CSoundObject m_soMusic4a,
224 CSoundObject m_soMusic4b,

// next free subchannel markers (all starts at subchannel 1(b), first switch goes to subchannel 0(a))
130 INDEX m_iSubChannel0 = 1,
131 INDEX m_iSubChannel1 = 1,
132 INDEX m_iSubChannel2 = 1,
133 INDEX m_iSubChannel3 = 1,
134 INDEX m_iSubChannel4 = 1,

230 CEntityPointer m_penDioPlayer,
231 FLOAT m_timeZaWarudoStart = 0.0f,
232 CEntityPointer m_penEventStorage,
233 CEntityPointer m_penEntityHashTable,

  {
    // array of enemies that make fuss
    CDynamicContainer<CEntity> m_cenFussMakers;
    BOOL m_visualsChanged;
  }

components:
  1 model   MODEL_MARKER     "Models\\Editor\\MusicHolder.mdl",
  2 texture TEXTURE_MARKER   "Models\\Editor\\MusicHolder.tex",
  3 class   CLASS_EVENT_STORAGE    "Classes\\EventStorage.ecl",
  4 class   CLASS_EVENT_HASH_TABLE "Classes\\EntityHashTable.ecl",


functions:

  CEntity* HashTable()
  {
    if (!m_penEntityHashTable) {
      m_penEntityHashTable = CreateEntity(GetPlacement(), CLASS_EVENT_HASH_TABLE);
      m_penEntityHashTable->Initialize();
    }
    return m_penEntityHashTable.ep_pen;
  }

  BOOL IsEntityFrozen(CEntity* pen)
  {
    return ((EntityHashTable*)HashTable())->Contains(pen);
  }

  void FreezeEntity(const CEntityPointer& pen)
  {
    ((EntityHashTable*)HashTable())->Add(pen);
  }

  void ClearFrozenEntities()
  {
    ((EntityHashTable*)HashTable())->Clear();
  }

  void StoreEvent(CSentEvent& se)
  {
    if (!m_penEventStorage) {
      m_penEventStorage = CreateEntity(GetPlacement(), CLASS_EVENT_STORAGE);
      m_penEventStorage->Initialize();
    }
    ((EventStorage*)m_penEventStorage.ep_pen)->StoreEvent(se);
  }

  void PopStoredEvents()
  {
    if (m_penEventStorage) {
      ((EventStorage*)m_penEventStorage.ep_pen)->PopEvents();
    }
  }

  void CMusicHolder()
  {
    all_textures.clear();
    m_visualsChanged = FALSE;
  }

  void ~CMusicHolder()
  {
    all_textures.clear();
    if (m_visualsChanged == TRUE)
    {
      EnableDioVisuals(FALSE);
    }
  }

  void Read_t(CTStream* istr)
  {
    CRationalEntity::Read_t(istr);

    if (m_penDioPlayer != NULL)
    {
      m_visualsChanged = TRUE;
    } else {
      m_visualsChanged = FALSE;
    }

    if (m_visualsChanged)
    {
      EnableDioVisuals(m_visualsChanged);
    }
  }

  // count enemies in current world
  void CountEnemies(void)
  {
    m_ctEnemiesInWorld = 0;
    m_ctSecretsInWorld = 0;
    // for each entity in the world
    {FOREACHINDYNAMICCONTAINER(GetWorld()->wo_cenEntities, CEntity, iten) {
      CEntity *pen = iten;
      // if enemybase
      if (IsDerivedFromClass(pen, "Enemy Base")) {
        CEnemyBase *penEnemy = (CEnemyBase *)pen;
        // if not template
        if (!penEnemy->m_bTemplate) {
          // count one
          m_ctEnemiesInWorld++;
		      // if this is a woman kamikaze carrier, add another one to count
		      if (IsOfClass(pen, "Woman")) {
			      if (((CWoman *)&*pen)->m_bKamikazeCarrier) { m_ctEnemiesInWorld++; }
		      }
        }
      // if spawner
      } else if (IsDerivedFromClass(pen, "Enemy Spawner")) {
        CEnemySpawner *penSpawner = (CEnemySpawner *)pen;
        // if not teleporting
        if (penSpawner->m_estType!=EST_TELEPORTER) {
          // add total count
          m_ctEnemiesInWorld+=penSpawner->m_ctTotal;
          // if this spawner points to a woman kamikaze carrier template, increase count once more
          if (penSpawner->m_penTarget) {
            if (IsOfClass(penSpawner->m_penTarget, "Woman")) {
              if (((CWoman *)&*penSpawner->m_penTarget)->m_bKamikazeCarrier) { m_ctEnemiesInWorld+=penSpawner->m_ctTotal; }
            }
          }
        }
      // if trigger
      } else if (IsDerivedFromClass(pen, "Trigger")) {
        CTrigger *penTrigger = (CTrigger *)pen;
        // if has score
        if (penTrigger->m_fScore>0) {
          // it counts as a secret
          m_ctSecretsInWorld++;
        }
      }
    }}
  }

  // check for stale fuss-makers
  void CheckOldFussMakers(void)
  {
    TIME tmNow = _pTimer->CurrentTick();
    TIME tmTooOld = tmNow-10.0f;
    CDynamicContainer<CEntity> cenOldFussMakers;
    // for each fussmaker
    {FOREACHINDYNAMICCONTAINER(m_cenFussMakers, CEntity, itenFussMaker) {
      CEnemyBase & enFussMaker = (CEnemyBase&)*itenFussMaker;
      // if haven't done fuss for too long
      if (enFussMaker.m_tmLastFussTime<tmTooOld) {
        // add to old fuss makers
        cenOldFussMakers.Add(&enFussMaker);
      }
    }}
    // for each old fussmaker
    {FOREACHINDYNAMICCONTAINER(cenOldFussMakers, CEntity, itenOldFussMaker) {
      CEnemyBase &enOldFussMaker = (CEnemyBase&)*itenOldFussMaker;
      // remove from fuss
      enOldFussMaker.RemoveFromFuss();
    }}
  }
  
  // get total score of all active fuss makers
  INDEX GetFussMakersScore(void) {
    INDEX iScore = 0;
    {FOREACHINDYNAMICCONTAINER(m_cenFussMakers, CEntity, itenFussMaker) {
      CEnemyBase &enFussMaker = (CEnemyBase&)*itenFussMaker;
      iScore += enFussMaker.m_iScore;
    }}
    return iScore;
  }

  // change given music channel
  void ChangeMusicChannel(enum MusicType mtType, const CTFileName &fnNewMusic, FLOAT fNewVolume)
  {
    INDEX &iSubChannel = (&m_iSubChannel0)[mtType];
    // take next sub-channel if needed
    if (fnNewMusic!="") {
      iSubChannel = (iSubChannel+1)%2;
    }
    // find channel's variables
    FLOAT &fVolume = (&m_fVolume0)[mtType];
    CSoundObject &soMusic = (&m_soMusic0a)[mtType*2+iSubChannel];
    FLOAT &fCurrentVolume = (&m_fCurrentVolume0a)[mtType*2+iSubChannel];

    // setup looping/non looping flags
    ULONG ulFlags;
    if (mtType==MT_EVENT) {
      ulFlags = SOF_MUSIC;
    } else {
      ulFlags = SOF_MUSIC|SOF_LOOP|SOF_NONGAME;
    }

    // remember volumes
    fVolume = fNewVolume;
    // start new music file if needed
    if (fnNewMusic!="") {
      PlaySound( soMusic, fnNewMusic, ulFlags);
      // initially, not playing
      fCurrentVolume = MUSIC_VOLUMEMIN;
      soMusic.Pause();
      soMusic.SetVolume(fCurrentVolume, fCurrentVolume);
    }
  }

  // fade out one channel
  void FadeOutChannel(INDEX iChannel, INDEX iSubChannel)
  {
    // find channel's variables
    FLOAT &fVolume = (&m_fVolume0)[iChannel];
    CSoundObject &soMusic = (&m_soMusic0a)[iChannel*2+iSubChannel];
    FLOAT &fCurrentVolume = (&m_fCurrentVolume0a)[iChannel*2+iSubChannel];

    // do nothing, if music is not playing
    if( !soMusic.IsPlaying()) { return; }

    // do nothing, if music is already paused
    if( soMusic.IsPaused()) { return; }

    // if minimum volume reached 
    if( fCurrentVolume<MUSIC_VOLUMEMIN) {
      // pause music
      soMusic.Pause();
    } else {
      // music isn't even faded yet, so continue on fading it out
      fCurrentVolume *= FadeOutFactor( m_tmFade);
      soMusic.SetVolume( fCurrentVolume*fVolume, fCurrentVolume*fVolume);
    }
  }

  // fade in one channel
  void FadeInChannel(INDEX iChannel, INDEX iSubChannel)
  {
    // find channel's variables
    FLOAT &fVolume = (&m_fVolume0)[iChannel];
    CSoundObject &soMusic = (&m_soMusic0a)[iChannel*2+iSubChannel];
    FLOAT &fCurrentVolume = (&m_fCurrentVolume0a)[iChannel*2+iSubChannel];

    // do nothing, if music is not playing
    if( !soMusic.IsPlaying()) { return; }

    // resume music if needed
    if( soMusic.IsPaused()) {
      soMusic.Resume();
    }
    // fade in music if needed
    if( fCurrentVolume<MUSIC_VOLUMEMAX) {
      fCurrentVolume *= FadeInFactor( m_tmFade);
      fCurrentVolume = ClampUp( fCurrentVolume, 1.0f);
    }
    soMusic.SetVolume( fCurrentVolume*fVolume, fCurrentVolume*fVolume);
  }

  // fade one channel in or out
  void CrossFadeOneChannel(enum MusicType mtType)
  {
    INDEX iSubChannelActive = (&m_iSubChannel0)[mtType];
    INDEX iSubChannelInactive = (iSubChannelActive+1)%2;
    // if it is current channel
    if (mtType==m_mtCurrentMusic) {
      // fade in active subchannel
      FadeInChannel(mtType, iSubChannelActive);
      // fade out inactive subchannel
      FadeOutChannel(mtType, iSubChannelInactive);
    // if it is not current channel
    } else {
      // fade it out
      FadeOutChannel(mtType, 0);
      FadeOutChannel(mtType, 1);
    }
  }

  void EnableDioVisuals(BOOL enable)
  {
    INDEX &iSubChannel = (&m_iSubChannel0)[m_mtCurrentMusic];
    CSoundObject &soMusic = (&m_soMusic0a)[m_mtCurrentMusic*2+iSubChannel];
    if (enable == TRUE)
    {
      g_dioTime = _pTimer->GetLerpedCurrentTick();
      soMusic.Pause();
    } else {
      g_dioTime = 0.0f;
      soMusic.Resume();
    }
  }

  void SetBrushTexturesAnimated(BOOL animated)
  {
    if (all_textures.empty())
    { 
      {FOREACHINDYNAMICARRAY(GetWorld()->wo_baBrushes.ba_abrBrushes, CBrush3D, itbr)
      {
        {FOREACHINLIST(CBrushMip, bm_lnInBrush, itbr->br_lhBrushMips, itbm)
        {
          {FOREACHINDYNAMICARRAY(itbm->bm_abscSectors, CBrushSector, itbs)
          {
            { for (INDEX i = 0; i < itbs->bsc_abpoPolygons.Count(); i++)
            {
              CBrushPolygon& polygon = itbs->bsc_abpoPolygons[i];
              { for (INDEX j = 0; j < 3; j++)
              {
                CBrushPolygonTexture& polygon_texture = polygon.bpo_abptTextures[j];
                all_textures.push_back(TTextureScrollPair(&polygon_texture, polygon_texture.s.bpt_ubScroll));
              }}
            }}
          }}
        }}
      }}
    }

    for (INDEX i = 0; i < all_textures.size(); i++)
    {
      if (animated == TRUE)
      {
        all_textures[i].first->s.bpt_ubScroll = all_textures[i].second;
      } else {
        all_textures[i].first->s.bpt_ubScroll = 0;
      }
    }
  }
  
  void TokiWoTomare(CEntityPointer penDio)
  {
    m_timeZaWarudoStart = _pTimer->CurrentTick();
    SetDio(penDio);

    SetBrushTexturesAnimated(FALSE);

    SendEvent(EHandleStopTime());
  }
  
  void TokiWaUgokiDasu()
  {
    SetBrushTexturesAnimated(TRUE);
    SendEvent(EHandleStartTime());
  }

  void SetDio(CEntityPointer penDioPlayer)
  {
    if (m_penDioPlayer == penDioPlayer)
    {
      return;
    }

    BOOL prevVisuals = m_visualsChanged;
    m_penDioPlayer = penDioPlayer;

    if (m_penDioPlayer != NULL)
    {
      m_visualsChanged = TRUE;
    } else {
      m_visualsChanged = FALSE;
    }

    if (prevVisuals != m_visualsChanged)
    {
      EnableDioVisuals(m_visualsChanged);
    }
  }

  BOOL IsDioOrRelated(CEntity* penSomething)
  {
    if (!m_penDioPlayer || !penSomething)
    {
      return FALSE;
    }
    penSomething = penSomething->GetPredictionTail();
    if (penSomething->en_ulFlags & ENF_DELETED) {
      return FALSE;
    }

    CPlayer* pDio = (CPlayer*)&*m_penDioPlayer;
    pDio = (CPlayer*)pDio->GetPredictionTail();
    if (penSomething == GetPredictionTail() ||
        penSomething == pDio ||
        penSomething == pDio->m_penWeapons.ep_pen ||
        penSomething == pDio->m_penAnimator.ep_pen ||
        penSomething == pDio->m_penView.ep_pen ||
        penSomething == pDio->m_pen3rdPersonView.ep_pen ||
        entity_cast(penSomething, EntityHashTable) != NULL ||
        entity_cast(penSomething, EventStorage) != NULL ||
        entity_cast(penSomething, EventEntity) != NULL ||
        entity_cast(penSomething, EventProperty) != NULL ||
        entity_cast(penSomething, CMovingBrush) != NULL ||
        entity_cast(penSomething, CMovingBrushMarker) != NULL ||
        entity_cast(penSomething, CCamera) != NULL ||
        entity_cast(penSomething, CCameraMarker) != NULL ||
        entity_cast(penSomething, CDioPosing) != NULL ||
        (entity_cast(penSomething, CReminder) != NULL && IsDioOrRelated(((CReminder*)penSomething)->m_penOwner.ep_pen)) ||
        (entity_cast(penSomething, CTheWorld) != NULL && IsDioOrRelated(((CTheWorld*)penSomething)->m_penOwner.ep_pen)) ||
        (entity_cast(penSomething, CRodaRollaDa) != NULL && IsDioOrRelated(((CRodaRollaDa*)penSomething)->m_penOwner.ep_pen)) ||
        (entity_cast(penSomething, CBasicEffect) != NULL && IsDioOrRelated(penSomething->GetParent())))
    {
      return TRUE;
    }

    return FALSE;
  }

  BOOL IsZaWarudo() const
  {
    return m_penDioPlayer != NULL ? TRUE : FALSE;
  }

procedures:
  // initialize music
  Main(EVoid) {

    // init as model
    InitAsEditorModel();
    SetPhysicsFlags(EPF_MODEL_IMMATERIAL);
    SetCollisionFlags(ECF_IMMATERIAL);

    // set appearance
    SetModel(MODEL_MARKER);
    SetModelMainTexture(TEXTURE_MARKER);

    // reset Dio, just in case
    SetDio(NULL);
    // wait for game to start
    autowait(_pTimer->TickQuantum);

    // prepare initial music channel values
    ChangeMusicChannel(MT_LIGHT,        m_fnMusic0, m_fVolume0);
    ChangeMusicChannel(MT_MEDIUM,       m_fnMusic1, m_fVolume1);
    ChangeMusicChannel(MT_HEAVY,        m_fnMusic2, m_fVolume2);
    ChangeMusicChannel(MT_EVENT,        m_fnMusic3, m_fVolume3);
    ChangeMusicChannel(MT_CONTINUOUS,   m_fnMusic4, m_fVolume4);

    // start with light music
    m_mtCurrentMusic = MT_LIGHT;
    m_fCurrentVolume0a = MUSIC_VOLUMEMAX*0.98f;
    m_tmFade = 0.01f;
    CrossFadeOneChannel(MT_LIGHT);
    // reset Dio, just in case
    SetDio(NULL);

    // must react after enemyspawner and all enemies, but before player for proper enemy counting
    // (total wait is two ticks so far)
    autowait(_pTimer->TickQuantum);
    // reset Dio, just in case
    SetDio(NULL);

    // count enemies in current world
    CountEnemies();

    // main loop
    while(TRUE) {
      // wait a bit
      wait(0.1f) {
        on (ETimer) : {
          stop;
        };
        // if music is to be changed
        on (EChangeMusic ecm) : { 
          // change parameters
          ChangeMusicChannel(ecm.mtType, ecm.fnMusic, ecm.fVolume);
          // if force started
          if (ecm.bForceStart) {
            // set as current music
            m_mtCurrentMusic = ecm.mtType;
          }
          // stop waiting
          stop;
        }
        on (EZaWarudo za_warudo) :
        {
          TokiWoTomare(za_warudo.penDio->GetPredictionTail());
          call StandoPowah();
        }
        on (EZaWarudoEnd) :
        {
          if (m_penDioPlayer) {
            m_penDioPlayer->SendEvent(EZaWarudoEnd());
          }
          TokiWaUgokiDasu();
          stop;
        }
      }
      // check fuss
      CheckOldFussMakers();
      // get total score of all active fuss makers
      FLOAT fFussScore = GetFussMakersScore();
      // if event is on
      if (m_mtCurrentMusic==MT_EVENT) {
        // if event has ceased playing
        if (!m_soMusic3a.IsPlaying() && !m_soMusic3b.IsPlaying()) {
          // switch to light music
          m_mtCurrentMusic=MT_LIGHT;
        }
      }
      // if heavy fight is on
      if (m_mtCurrentMusic==MT_HEAVY) {
        // if no more fuss
        if (fFussScore<=0.0f) {
          // switch to no fight
          m_mtCurrentMusic=MT_LIGHT;
        }
      // if medium fight is on
      } else if (m_mtCurrentMusic==MT_MEDIUM) {
        // if no more fuss
        if (fFussScore<=0.0f) {
          // switch to no fight
          m_mtCurrentMusic=MT_LIGHT;
        // if larger fuss
        } else if (fFussScore>=m_fScoreHeavy) {
          // switch to heavy fight
          m_mtCurrentMusic=MT_HEAVY;
        }
      // if no fight is on
      } else if (m_mtCurrentMusic==MT_LIGHT) {
        // if heavy fuss
        if (fFussScore>=m_fScoreHeavy) {
          // switch to heavy fight
          m_mtCurrentMusic=MT_HEAVY;
        // if medium fuss
        } else if (fFussScore>=m_fScoreMedium) {
          // switch to medium fight
          m_mtCurrentMusic=MT_MEDIUM;
        }
      }

      // setup fade speed depending on music type
      if (m_mtCurrentMusic==MT_LIGHT) {
        m_tmFade = 2.0f;
      } else if (m_mtCurrentMusic==MT_MEDIUM) {
        m_tmFade = 1.0f;
      } else if (m_mtCurrentMusic==MT_HEAVY) {
        m_tmFade = 1.0f;
      } else if (m_mtCurrentMusic==MT_EVENT || m_mtCurrentMusic==MT_CONTINUOUS) {
        m_tmFade = 0.5f;
      }

      // fade all channels
      CrossFadeOneChannel(MT_LIGHT);
      CrossFadeOneChannel(MT_MEDIUM);
      CrossFadeOneChannel(MT_HEAVY);
      CrossFadeOneChannel(MT_EVENT);
      CrossFadeOneChannel(MT_CONTINUOUS);
    }
    return;
  }
  
  StandoPowah()
  {
    wait (ZA_WARUDO_DURATION)
    {
      on (EBegin) : { resume; }
      on (ETimer) : { stop; }
      on (EZaWarudo) : { resume; }
      on (EZaWarudoEnd) : { resume; }
    }
    return EZaWarudoEnd();
  }
};
