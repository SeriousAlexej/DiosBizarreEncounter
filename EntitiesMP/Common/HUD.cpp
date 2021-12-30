 
#include "StdH.h"
#include "GameMP/SEColors.h"
#include <math.h>

#include <Engine/Graphics/DrawPort.h>

#include <EntitiesMP/Player.h>
#include <EntitiesMP/PlayerWeapons.h>
#include <EntitiesMP/MusicHolder.h>
#include <EntitiesMP/EnemyBase.h>
#include <EntitiesMP/EnemyCounter.h>
#include <EntitiesJoJo/TheWorld.h>
#include <EntitiesJoJo/jojo_events.h>
#include <GameJoJo/ButtonAction.h>

// cheats
extern INDEX cht_bEnable;
extern INDEX cht_bGod;
extern INDEX cht_bFly;
extern INDEX cht_bGhost;
extern INDEX cht_bInvisible;
extern FLOAT cht_fTranslationMultiplier;

// interface control
extern INDEX hud_bShowInfo;
extern INDEX hud_bShowLatency;
extern INDEX hud_bShowMessages;
extern INDEX hud_iShowPlayers;
extern INDEX hud_iShowPlayersList;
extern INDEX hud_iSortPlayers;
extern FLOAT hud_fOpacity;
extern FLOAT hud_fScaling;
extern FLOAT hud_tmWeaponsOnScreen;
extern INDEX hud_bShowMatchInfo;

// player statistics sorting keys
enum SortKeys {
  PSK_NAME    = 1,
  PSK_HEALTH  = 2,
  PSK_SCORE   = 3,
  PSK_MANA    = 4, 
  PSK_FRAGS   = 5,
  PSK_DEATHS  = 6,
};

extern const INDEX aiWeaponsRemap[19];

// drawing variables
static const CPlayer *_penPlayer;
static CPlayerWeapons *_penWeapons;
static CDrawPort *_pDP;
static PIX   _pixDPWidth, _pixDPHeight;
static FLOAT _fResolutionScaling;
static ULONG _ulAlphaHUD;
static COLOR _colHUD;
static COLOR _colHUDText;
static TIME  _tmNow = -1.0f;
static TIME  _tmLast = -1.0f;
static CFontData _fdNumbersFont;

static FLOAT _dioHUDScaling;

// array for pointers of all players
extern CPlayer *_apenPlayers[NET_MAXGAMEPLAYERS] = {0};

// DIO textures
static CTextureObject _toUltBcg;
static CTextureObject _toUltOverlay;
static CTextureObject _toFireTexture;
static CTextureObject _toUlt;
static CTextureObject _toUltRodarollada;
static CTextureObject _toUltFlare;
static CTextureObject _toWeaponBrace;
static CTextureObject _toInfAmmo;
static CTextureObject _toDIO;
static CTextureObject _toZaWarudo;
static CTextureObject _toBarBcg;
static CTextureObject _toBar;
static CTextureObject _toWarudoTimer;
static CTextureObject _toWarudoArrow;
static CTextureObject _toWarudoBcg;

static CTextureObject _toMBLeft;
static CTextureObject _toMBRight;
static CTextureObject _toMB3;
static CTextureObject _toMB4;
static CTextureObject _toMB5;
static CTextureObject _toMWUp;
static CTextureObject _toMWDown;
static CTextureObject _toPointer;

static CTextureObject _toAbilityFrame;
static CTextureObject _toAbilityCancel;
static CTextureObject _toAbilityOverlay;
static CTextureObject _toAbility_Stand;
static CTextureObject _toAbility_Leg;
static CTextureObject _toAbility_Zoom;
static CTextureObject _toAbility_Knives;
static CTextureObject _toAbility_Menacing;

static CFontData* _owFont = NULL;

// status bar textures
static CTextureObject _toHealth;
static CTextureObject _toOxygen;
static CTextureObject _toFrags;
static CTextureObject _toDeaths;
static CTextureObject _toArmorSmall;
static CTextureObject _toArmorMedium;
static CTextureObject _toArmorLarge;

// ammo textures                    
static CTextureObject _toAShells;
static CTextureObject _toABullets;
static CTextureObject _toARockets;
static CTextureObject _toAGrenades;
static CTextureObject _toANapalm;
static CTextureObject _toAElectricity;
static CTextureObject _toAIronBall;
static CTextureObject _toASniperBullets;
static CTextureObject _toASeriousBomb;
// weapon textures
static CTextureObject _toWKnife;
static CTextureObject _toWColt;
static CTextureObject _toWDoubleColt;
static CTextureObject _toWSingleShotgun;
static CTextureObject _toWDoubleShotgun;
static CTextureObject _toWTommygun;
static CTextureObject _toWSniper;
static CTextureObject _toWChainsaw;
static CTextureObject _toWMinigun;
static CTextureObject _toWRocketLauncher;
static CTextureObject _toWGrenadeLauncher;
static CTextureObject _toWFlamer;
static CTextureObject _toWLaser;
static CTextureObject _toWIronCannon;
static CTextureObject _toWHands;
static CTextureObject _toWSBomb;

// powerup textures (ORDER IS THE SAME AS IN PLAYER.ES!)
#define MAX_POWERUPS 4
static CTextureObject _atoPowerups[MAX_POWERUPS];
// tile texture (one has corners, edges and center)
static CTextureObject _toTile;
// sniper mask texture
static CTextureObject _toSniperMask;
static CTextureObject _toSniperWheel;
static CTextureObject _toSniperArrow;
static CTextureObject _toSniperEye;
static CTextureObject _toSniperLed;

// ammo's info structure
struct AmmoInfo {
  CTextureObject    *ai_ptoAmmo;
  struct WeaponInfo *ai_pwiWeapon1;
  struct WeaponInfo *ai_pwiWeapon2;
  INDEX ai_iAmmoAmmount;
  INDEX ai_iMaxAmmoAmmount;
  INDEX ai_iLastAmmoAmmount;
  TIME  ai_tmAmmoChanged;
  BOOL  ai_bHasWeapon;
};

// weapons' info structure
struct WeaponInfo {
  enum WeaponType  wi_wtWeapon;
  CTextureObject  *wi_ptoWeapon;
  struct AmmoInfo *wi_paiAmmo;
  BOOL wi_bHasWeapon;
};

extern struct WeaponInfo _awiWeapons[18];
static struct AmmoInfo _aaiAmmo[8] = {
  { &_toAShells,        &_awiWeapons[4],  &_awiWeapons[5],  0, 0, 0, -9, FALSE }, //  0
  { &_toABullets,       &_awiWeapons[6],  &_awiWeapons[7],  0, 0, 0, -9, FALSE }, //  1
  { &_toARockets,       &_awiWeapons[8],  NULL,             0, 0, 0, -9, FALSE }, //  2
  { &_toAGrenades,      &_awiWeapons[9],  NULL,             0, 0, 0, -9, FALSE }, //  3
  { &_toANapalm,        &_awiWeapons[11], NULL,             0, 0, 0, -9, FALSE }, //  4
  { &_toAElectricity,   &_awiWeapons[12], NULL,             0, 0, 0, -9, FALSE }, //  5
  { &_toAIronBall,      &_awiWeapons[14], NULL,             0, 0, 0, -9, FALSE }, //  6
  { &_toASniperBullets, &_awiWeapons[13], NULL,             0, 0, 0, -9, FALSE }, //  7
};

static const INDEX aiAmmoRemap[8] = { 0, 1, 2, 3, 4, 7, 5, 6 };
struct WeaponInfo _awiWeapons[18] = {
  { WEAPON_NONE,            NULL,                 NULL,         FALSE },   //  0
  { WEAPON_KNIFE,           &_toWKnife,           NULL,         FALSE },   //  1
  { WEAPON_COLT,            &_toWColt,            NULL,         FALSE },   //  2
  { WEAPON_DOUBLECOLT,      &_toWDoubleColt,      NULL,         FALSE },   //  3
  { WEAPON_SINGLESHOTGUN,   &_toWSingleShotgun,   &_aaiAmmo[0], FALSE },   //  4
  { WEAPON_DOUBLESHOTGUN,   &_toWDoubleShotgun,   &_aaiAmmo[0], FALSE },   //  5
  { WEAPON_TOMMYGUN,        &_toWTommygun,        &_aaiAmmo[1], FALSE },   //  6
  { WEAPON_MINIGUN,         &_toWMinigun,         &_aaiAmmo[1], FALSE },   //  7
  { WEAPON_ROCKETLAUNCHER,  &_toWRocketLauncher,  &_aaiAmmo[2], FALSE },   //  8
  { WEAPON_GRENADELAUNCHER, &_toWGrenadeLauncher, &_aaiAmmo[3], FALSE },   //  9
  { WEAPON_CHAINSAW,        &_toWChainsaw,        NULL,         FALSE },   // 10
  { WEAPON_FLAMER,          &_toWFlamer,          &_aaiAmmo[4], FALSE },   // 11
  { WEAPON_LASER,           &_toWLaser,           &_aaiAmmo[5], FALSE },   // 12
  { WEAPON_SNIPER,          &_toWSniper,          &_aaiAmmo[7], FALSE },   // 13
  { WEAPON_IRONCANNON,      &_toWIronCannon,      &_aaiAmmo[6], FALSE },   // 14
  { WEAPON_HANDS,           &_toWHands,           NULL,         FALSE },   // 15
  { WEAPON_NONE,            NULL,                 NULL,         FALSE },   // 16
  { WEAPON_NONE,            NULL,                 NULL,         FALSE },   // 17
};


// compare functions for qsort()
static int qsort_CompareNames( const void *ppPEN0, const void *ppPEN1) {
  CPlayer &en0 = **(CPlayer**)ppPEN0;
  CPlayer &en1 = **(CPlayer**)ppPEN1;
  CTString strName0 = en0.GetPlayerName();
  CTString strName1 = en1.GetPlayerName();
  return strnicmp( strName0, strName1, 8);
}

static int qsort_CompareScores( const void *ppPEN0, const void *ppPEN1) {
  CPlayer &en0 = **(CPlayer**)ppPEN0;
  CPlayer &en1 = **(CPlayer**)ppPEN1;
  SLONG sl0 = en0.m_psGameStats.ps_iScore;
  SLONG sl1 = en1.m_psGameStats.ps_iScore;
  if(      sl0<sl1) return +1;
  else if( sl0>sl1) return -1;
  else              return  0;
}

static int qsort_CompareHealth( const void *ppPEN0, const void *ppPEN1) {
  CPlayer &en0 = **(CPlayer**)ppPEN0;
  CPlayer &en1 = **(CPlayer**)ppPEN1;
  SLONG sl0 = (SLONG)ceil(en0.GetHealth());
  SLONG sl1 = (SLONG)ceil(en1.GetHealth());
  if(      sl0<sl1) return +1;
  else if( sl0>sl1) return -1;
  else              return  0;
}

static int qsort_CompareManas( const void *ppPEN0, const void *ppPEN1) {
  CPlayer &en0 = **(CPlayer**)ppPEN0;
  CPlayer &en1 = **(CPlayer**)ppPEN1;
  SLONG sl0 = en0.m_iMana;
  SLONG sl1 = en1.m_iMana;
  if(      sl0<sl1) return +1;
  else if( sl0>sl1) return -1;
  else              return  0;
}

static int qsort_CompareDeaths( const void *ppPEN0, const void *ppPEN1) {
  CPlayer &en0 = **(CPlayer**)ppPEN0;
  CPlayer &en1 = **(CPlayer**)ppPEN1;
  SLONG sl0 = en0.m_psGameStats.ps_iDeaths;
  SLONG sl1 = en1.m_psGameStats.ps_iDeaths;
  if(      sl0<sl1) return +1;
  else if( sl0>sl1) return -1;
  else              return  0;
}

static int qsort_CompareFrags( const void *ppPEN0, const void *ppPEN1) {
  CPlayer &en0 = **(CPlayer**)ppPEN0;
  CPlayer &en1 = **(CPlayer**)ppPEN1;
  SLONG sl0 = en0.m_psGameStats.ps_iKills;
  SLONG sl1 = en1.m_psGameStats.ps_iKills;
  if(      sl0<sl1) return +1;
  else if( sl0>sl1) return -1;
  else              return -qsort_CompareDeaths(ppPEN0, ppPEN1);
}
// all info about color transitions
struct ColorTransitionTable {
  COLOR ctt_colFine;      // color for values over 1.0
  COLOR ctt_colHigh;      // color for values from 1.0 to 'fMedium'
  COLOR ctt_colMedium;    // color for values from 'fMedium' to 'fLow'
  COLOR ctt_colLow;       // color for values under fLow
  FLOAT ctt_fMediumHigh;  // when to switch to high color   (normalized float!)
  FLOAT ctt_fLowMedium;   // when to switch to medium color (normalized float!)
  BOOL  ctt_bSmooth;      // should colors have smooth transition
};
static struct ColorTransitionTable _cttHUD;
// prepare color transitions
static void PrepareColorTransitions( COLOR colFine, COLOR colHigh, COLOR colMedium, COLOR colLow,
                                     FLOAT fMediumHigh, FLOAT fLowMedium, BOOL bSmooth)
{
  _cttHUD.ctt_colFine     = colFine;
  _cttHUD.ctt_colHigh     = colHigh;   
  _cttHUD.ctt_colMedium   = colMedium;
  _cttHUD.ctt_colLow      = colLow;
  _cttHUD.ctt_fMediumHigh = fMediumHigh;
  _cttHUD.ctt_fLowMedium  = fLowMedium;
  _cttHUD.ctt_bSmooth     = bSmooth;
}

INDEX GetPlayerIndex(const CPlayer* penPlayer)
{
  if (penPlayer)
    for (INDEX i = 0; i < NET_MAXGAMEPLAYERS; ++i)
      if (static_cast<const CPlayer*>(penPlayer->GetPlayerEntity(i)) == penPlayer)
        return i;

  return 0;
}

// fill array with players' statistics (returns current number of players in game)
extern INDEX SetAllPlayersStats( INDEX iSortKey)
{
  // determine maximum number of players for this session
  INDEX iPlayers    = 0;
  INDEX iMaxPlayers = _penPlayer->GetMaxPlayers();
  CPlayer *penCurrent;
  // loop thru potentional players 
  for( INDEX i=0; i<iMaxPlayers; i++)
  { // ignore non-existent players
    penCurrent = (CPlayer*)&*_penPlayer->GetPlayerEntity(i);
    if( penCurrent==NULL) continue;
    // fill in player parameters
    _apenPlayers[iPlayers] = penCurrent;
    // advance to next real player
    iPlayers++;
  }
  // sort statistics by some key if needed
  switch( iSortKey) {
  case PSK_NAME:    qsort( _apenPlayers, iPlayers, sizeof(CPlayer*), qsort_CompareNames);   break;
  case PSK_SCORE:   qsort( _apenPlayers, iPlayers, sizeof(CPlayer*), qsort_CompareScores);  break;
  case PSK_HEALTH:  qsort( _apenPlayers, iPlayers, sizeof(CPlayer*), qsort_CompareHealth);  break;
  case PSK_MANA:    qsort( _apenPlayers, iPlayers, sizeof(CPlayer*), qsort_CompareManas);   break;
  case PSK_FRAGS:   qsort( _apenPlayers, iPlayers, sizeof(CPlayer*), qsort_CompareFrags);   break;
  case PSK_DEATHS:  qsort( _apenPlayers, iPlayers, sizeof(CPlayer*), qsort_CompareDeaths);  break;
  default:  break;  // invalid or NONE key specified so do nothing
  }
  // all done
  return iPlayers;
}
// get current color from local color transitions table
static COLOR GetCurrentColor( FLOAT fNormalizedValue)
{
  // if value is in 'low' zone just return plain 'low' alert color
  if( fNormalizedValue < _cttHUD.ctt_fLowMedium) return( _cttHUD.ctt_colLow & 0xFFFFFF00);
  // if value is in out of 'extreme' zone just return 'extreme' color
  if( fNormalizedValue > 1.0f) return( _cttHUD.ctt_colFine & 0xFFFFFF00);
 
  COLOR col;
  // should blend colors?
  if( _cttHUD.ctt_bSmooth)
  { // lets do some interpolations
    FLOAT fd, f1, f2;
    COLOR col1, col2;
    UBYTE ubH,ubS,ubV, ubH2,ubS2,ubV2;
    // determine two colors for interpolation
    if( fNormalizedValue > _cttHUD.ctt_fMediumHigh) {
      f1   = 1.0f;
      f2   = _cttHUD.ctt_fMediumHigh;
      col1 = _cttHUD.ctt_colHigh;
      col2 = _cttHUD.ctt_colMedium;
    } else { // fNormalizedValue > _cttHUD.ctt_fLowMedium == TRUE !
      f1   = _cttHUD.ctt_fMediumHigh;
      f2   = _cttHUD.ctt_fLowMedium;
      col1 = _cttHUD.ctt_colMedium;
      col2 = _cttHUD.ctt_colLow;
    }
    // determine interpolation strength
    fd = (fNormalizedValue-f2) / (f1-f2);
    // convert colors to HSV
    ColorToHSV( col1, ubH,  ubS,  ubV);
    ColorToHSV( col2, ubH2, ubS2, ubV2);
    // interpolate H, S and V components
    ubH = (UBYTE)(ubH*fd + ubH2*(1.0f-fd));
    ubS = (UBYTE)(ubS*fd + ubS2*(1.0f-fd));
    ubV = (UBYTE)(ubV*fd + ubV2*(1.0f-fd));
    // convert HSV back to COLOR
    col = HSVToColor( ubH, ubS, ubV);
  }
  else
  { // simple color picker
    col = _cttHUD.ctt_colMedium;
    if( fNormalizedValue > _cttHUD.ctt_fMediumHigh) col = _cttHUD.ctt_colHigh;
  }
  // all done
  return( col & 0xFFFFFF00);
}




// ----------------------- drawing functions

FLOAT GetAngleFromTo(const CPlayer* from, const CPlayer* to)
{
  if (from == to)
    return 0.0f;
  CPlacement3D pl_from(FLOAT3D(0,0,0), ANGLE3D(from->en_plViewpoint.pl_OrientationAngle(1),0,0));
  pl_from.RelativeToAbsolute(from->GetPlacement());
  CPlacement3D pl_to = to->GetPlacement();
  pl_to.AbsoluteToRelative(pl_from);
  FLOAT2D v1(0.0f, 1.0f);
  FLOAT2D v2(pl_to.pl_PositionVector(1), -pl_to.pl_PositionVector(3));
  FLOAT v2_length = v2.Length();
  if (v2_length < 0.01f)
    return 0.0f;
  FLOAT angle = (v1 % v2) / v2_length;
  angle = acos(Clamp(angle, -1.0f, 1.0f));
  if (v2(1) < 0.0f)
    angle *= -1.0f;
  return angle;
}

enum EScreenPos
{
  ESP_Start,
  ESP_Middle,
  ESP_End
};

FLOAT ctg(FLOAT angle)
{
  return cos(angle) / sin(angle);
}

static void DIO_DrawBcg
(
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  EScreenPos x_growth, FLOAT width,
  EScreenPos y_growth, FLOAT height,
  COLOR color
)
{
  const FLOAT half_width = width*0.5f * _dioHUDScaling;
  const FLOAT half_height = height*0.5f * _dioHUDScaling;
  
  FLOAT x_pos = 0.0f;
  if (x_anchor == ESP_Middle) {
    x_pos = _pixDPWidth / 2;
  } else if (x_anchor == ESP_End) {
    x_pos = _pixDPWidth;
  }
  FLOAT x_growth_offset = -half_width;
  if (x_growth == ESP_Start) {
    x_growth_offset = 0.0f;
  } else if (x_growth == ESP_End) {
    x_growth_offset *= 2.0f;
  }
  x_pos += static_cast<FLOAT>(x_offset) * _dioHUDScaling + x_growth_offset;
  FLOAT x_pos_end = x_pos + half_width + half_width;
  
  FLOAT y_pos = 0.0f;
  if (y_anchor == ESP_Middle) {
    y_pos = _pixDPHeight / 2;
  } else if (y_anchor == ESP_End) {
    y_pos = _pixDPHeight;
  }
  FLOAT y_growth_offset = -half_height;
  if (y_growth == ESP_Start) {
    y_growth_offset = 0.0f;
  } else if (x_growth == ESP_End) {
    y_growth_offset *= 2.0f;
  }
  y_pos += static_cast<FLOAT>(y_offset) * _dioHUDScaling + y_growth_offset;
  FLOAT y_pos_end = y_pos + half_height + half_height;

  
  FLOAT colAlpha = (color & 0xFF) / static_cast<FLOAT>(0xFF);
  color &= 0xFFFFFF00;
  color |= NormFloatToByte(colAlpha * (_ulAlphaHUD / static_cast<FLOAT>(0xFF)));

  FLOAT tmp;
  if (width < 0.0f)
  {
    tmp = x_pos;
    x_pos = x_pos_end;
    x_pos_end = tmp;
  }
  if (height < 0.0f)
  {
    tmp = y_pos;
    y_pos = y_pos_end;
    y_pos_end = tmp;
  }

  _pDP->Fill(x_pos, y_pos, x_pos_end - x_pos, y_pos_end - y_pos, color);
}

static void DIO_DrawIconADD
(
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  CTextureObject &toIcon,
  ANGLE angle = 0.0f,
  FLOAT2D scale = FLOAT2D(1.0f, 1.0f)
)
{
  CTextureData* ptd = (CTextureData*)toIcon.GetData();
  const FLOAT half_width = ptd->GetPixWidth()*0.5f * _dioHUDScaling * scale(1);
  const FLOAT half_height = ptd->GetPixHeight()*0.5f * _dioHUDScaling * scale(2);

  FLOAT x_pos = 0.0f;
  if (x_anchor == ESP_Middle) {
    x_pos = _pixDPWidth / 2;
  } else if (x_anchor == ESP_End) {
    x_pos = _pixDPWidth;
  }
  x_pos += static_cast<FLOAT>(x_offset) * _dioHUDScaling - half_width;
  const FLOAT x_pos_end = x_pos + half_width + half_width;
  
  FLOAT y_pos = 0.0f;
  if (y_anchor == ESP_Middle) {
    y_pos = _pixDPHeight / 2;
  } else if (y_anchor == ESP_End) {
    y_pos = _pixDPHeight;
  }
  y_pos += static_cast<FLOAT>(y_offset) * _dioHUDScaling - half_height;
  const FLOAT y_pos_end = y_pos + half_height + half_height;

  _pDP->InitTexture(&toIcon);
  // ADD blending mode
  shaDisableDepthWrite();
  shaDisableAlphaTest();
  shaEnableBlend();
  shaBlendFunc(GFX_ONE, GFX_ONE);

  FLOAT3D p0(x_pos, y_pos, 1.0f);
  FLOAT3D p1(x_pos_end, y_pos, 1.0f);
  FLOAT3D p2(x_pos_end, y_pos_end, 1.0f);
  FLOAT3D p3(x_pos, y_pos_end, 1.0f);

  if (angle != 0.0f)
  {
    FLOAT2D vtoCenter(x_pos + half_width, y_pos + half_height);
    FLOATmatrix3D toCenter(0.0f);
    toCenter(1, 3) = vtoCenter(1);
    toCenter(2, 3) = vtoCenter(2);
    toCenter(1, 1) = 1.0f;
    toCenter(2, 2) = 1.0f;
    toCenter(3, 3) = 1.0f;
    FLOATmatrix3D fromCenter(0.0f);
    fromCenter(1, 3) = -vtoCenter(1);
    fromCenter(2, 3) = -vtoCenter(2);
    fromCenter(1, 1) = 1.0f;
    fromCenter(2, 2) = 1.0f;
    fromCenter(3, 3) = 1.0f;
    FLOATmatrix3D rotate(0.0f);
    rotate(1, 1) = cos(angle);
    rotate(1, 2) = -sin(angle);
    rotate(2, 1) = -rotate(1, 2);
    rotate(2, 2) = rotate(1, 1);
    rotate(3, 3) = 1.0f;
    FLOATmatrix3D transformMatrix = toCenter * rotate * fromCenter;

    p0 = p0 * transformMatrix;
    p1 = p1 * transformMatrix;
    p2 = p2 * transformMatrix;
    p3 = p3 * transformMatrix;
  }

  _pDP->AddTexture(
    p0(1), p0(2), 0.0f, 0.0f, C_WHITE | 255,
    p1(1), p1(2), 1.0f, 0.0f, C_WHITE | 255,
    p2(1), p2(2), 1.0f, 1.0f, C_WHITE | 255,
    p3(1), p3(2), 0.0f, 1.0f, C_WHITE | 255
    );

  _pDP->FlushRenderingQueue();
}

static void DIO_DrawIcon
(
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  CTextureObject &toIcon,
  ANGLE angle = 0.0f,
  COLOR color = C_WHITE,
  FLOAT opacity = 1.0f,
  FLOAT scale = 1.0f,
  FLOAT vertical_slice = 1.0f // wow thats hardcode :D
)
{
  CTextureData* ptd = (CTextureData*)toIcon.GetData();
  const FLOAT half_width = ptd->GetPixWidth()*0.5f * _dioHUDScaling * scale;
  const FLOAT half_height = ptd->GetPixHeight()*0.5f * _dioHUDScaling * scale;

  FLOAT x_pos = 0.0f;
  if (x_anchor == ESP_Middle) {
    x_pos = _pixDPWidth / 2;
  } else if (x_anchor == ESP_End) {
    x_pos = _pixDPWidth;
  }
  x_pos += static_cast<FLOAT>(x_offset) * _dioHUDScaling - half_width;
  const FLOAT x_pos_end = x_pos + half_width + half_width;
  
  FLOAT y_pos = 0.0f;
  if (y_anchor == ESP_Middle) {
    y_pos = _pixDPHeight / 2;
  } else if (y_anchor == ESP_End) {
    y_pos = _pixDPHeight;
  }
  y_pos += static_cast<FLOAT>(y_offset) * _dioHUDScaling - half_height;
  const FLOAT y_pos_end = y_pos + half_height + half_height;

  _pDP->InitTexture(&toIcon);
  
  FLOAT3D p0(x_pos, y_pos + (1.0f - vertical_slice)*half_height*2.0f, 1.0f);
  FLOAT3D p1(x_pos_end, y_pos + (1.0f - vertical_slice)*half_height*2.0f, 1.0f);
  FLOAT3D p2(x_pos_end, y_pos_end, 1.0f);
  FLOAT3D p3(x_pos, y_pos_end, 1.0f);

  if (angle != 0.0f)
  {
    FLOAT2D vtoCenter(x_pos + half_width, y_pos + half_height);
    FLOATmatrix3D toCenter(0.0f);
    toCenter(1, 3) = vtoCenter(1);
    toCenter(2, 3) = vtoCenter(2);
    toCenter(1, 1) = 1.0f;
    toCenter(2, 2) = 1.0f;
    toCenter(3, 3) = 1.0f;
    FLOATmatrix3D fromCenter(0.0f);
    fromCenter(1, 3) = -vtoCenter(1);
    fromCenter(2, 3) = -vtoCenter(2);
    fromCenter(1, 1) = 1.0f;
    fromCenter(2, 2) = 1.0f;
    fromCenter(3, 3) = 1.0f;
    FLOATmatrix3D rotate(0.0f);
    rotate(1, 1) = cos(angle);
    rotate(1, 2) = -sin(angle);
    rotate(2, 1) = -rotate(1, 2);
    rotate(2, 2) = rotate(1, 1);
    rotate(3, 3) = 1.0f;
    FLOATmatrix3D transformMatrix = toCenter * rotate * fromCenter;

    p0 = p0 * transformMatrix;
    p1 = p1 * transformMatrix;
    p2 = p2 * transformMatrix;
    p3 = p3 * transformMatrix;
  }
  
  const UBYTE alpha = Clamp(INDEX(opacity * _ulAlphaHUD), INDEX(0), INDEX(255));
  const INDEX final_color = (color & 0xFFFFFF00) | alpha;
  _pDP->AddTexture(
    p0(1), p0(2), 0.0f, 1.0f - vertical_slice, final_color,
    p1(1), p1(2), 1.0f, 1.0f - vertical_slice, final_color,
    p2(1), p2(2), 1.0f, 1.0f, final_color,
    p3(1), p3(2), 0.0f, 1.0f, final_color
    );

  _pDP->FlushRenderingQueue();
}

static void DIO_DrawIconCircle
(
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  CTextureObject &toIcon,
  FLOAT percentage,
  COLOR color = C_WHITE,
  FLOAT opacity = 1.0f
)
{
  if (percentage < 0.1f) {
    return;
  }
  const UBYTE alpha = Clamp(INDEX(opacity * _ulAlphaHUD), INDEX(0), INDEX(255));
  const INDEX final_color = (color & 0xFFFFFF00) | alpha;

  CTextureData* ptd = (CTextureData*)toIcon.GetData();
  const FLOAT width = ptd->GetPixWidth() * _dioHUDScaling;
  const FLOAT height = ptd->GetPixHeight() * _dioHUDScaling;
  const FLOAT half_width = width*0.5f;
  const FLOAT half_height = height*0.5f;

  FLOAT x_pos = 0.0f;
  if (x_anchor == ESP_Middle) {
    x_pos = _pixDPWidth / 2;
  } else if (x_anchor == ESP_End) {
    x_pos = _pixDPWidth;
  }
  x_pos += static_cast<FLOAT>(x_offset) * _dioHUDScaling;
  
  FLOAT y_pos = 0.0f;
  if (y_anchor == ESP_Middle) {
    y_pos = _pixDPHeight / 2;
  } else if (y_anchor == ESP_End) {
    y_pos = _pixDPHeight;
  }
  y_pos += static_cast<FLOAT>(y_offset) * _dioHUDScaling;

  _pDP->InitTexture(&toIcon);
  FLOAT u = min(percentage, 12.5f) * 0.01f;
  FLOAT angle = 0.5f*PI - 2.0f*PI*u;
  FLOAT uv_pos = 0.5f*(1.0f + ctg(angle));

  FLOAT2D p0(x_pos, y_pos - half_height);
  FLOAT2D p0UV(0.5f, 0.0f);
  FLOAT2D p1(x_pos - half_width + width * uv_pos, y_pos - half_height);
  FLOAT2D p1UV(uv_pos, 0.0f);
  FLOAT2D pinterp = (p0 + p1)*0.5f;
  FLOAT2D pinterpUV = (p0UV + p1UV)*0.5f;
  _pDP->AddTexture(
    p0(1), p0(2), p0UV(1), p0UV(2), final_color,
    x_pos, y_pos, 0.5f, 0.5f, final_color,
    p1(1), p1(2), p1UV(1), p1UV(2), final_color,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), final_color   
    );

if (percentage > 12.5f)
{
  u = min(percentage - 12.5f, 25.0f) * 0.01f;
  angle = 0.25f*PI - 2.0f*PI*u;
  uv_pos = 1.0f-0.5f*(1.0f + tan(angle));

  p0 = FLOAT2D(x_pos + half_width, y_pos - half_height);
  p0UV = FLOAT2D(1.0f, 0.0f);
  p1 = FLOAT2D(x_pos + half_width, y_pos - half_height + height * uv_pos);
  p1UV = FLOAT2D(1.0f, uv_pos);
  FLOAT2D pinterp = (p0 + p1)*0.5f;
  FLOAT2D pinterpUV = (p0UV + p1UV)*0.5f;
  _pDP->AddTexture(
    x_pos, y_pos, 0.5f, 0.5f, final_color,
    p0(1), p0(2), p0UV(1), p0UV(2), final_color,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), final_color,
    p1(1), p1(2), p1UV(1), p1UV(2), final_color
    );
if (percentage > 37.5f)
{
  u = min(percentage - 37.5f, 25.0f) * 0.01f;
  angle = 0.25f*PI - 2.0f*PI*u;
  uv_pos = 0.5f*(1.0f + tan(angle));

  p0 = FLOAT2D(x_pos + half_width, y_pos + half_height);
  p0UV = FLOAT2D(1.0f, 1.0f);
  p1 = FLOAT2D(x_pos - half_width + width * uv_pos, y_pos + half_height);
  p1UV = FLOAT2D(uv_pos, 1.0f);
  FLOAT2D pinterp = (p0 + p1)*0.5f;
  FLOAT2D pinterpUV = (p0UV + p1UV)*0.5f;
  _pDP->AddTexture(
    x_pos, y_pos, 0.5f, 0.5f, final_color,
    p0(1), p0(2), p0UV(1), p0UV(2), final_color,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), final_color,
    p1(1), p1(2), p1UV(1), p1UV(2), final_color
    );
if (percentage > 62.5f)
{
  u = (min(percentage, 87.5f)-25.0f) * (-0.01f);
  angle = 2.0f*PI*u;
  uv_pos = 0.5f*(1.0f + tan(angle));

  p0 = FLOAT2D(x_pos - half_width, y_pos + half_height);
  p0UV = FLOAT2D(0.0f, 1.0f);
  p1 = FLOAT2D(x_pos - half_width, y_pos - half_height + height * uv_pos);
  p1UV = FLOAT2D(0.0f, uv_pos);
  FLOAT2D pinterp = (p0 + p1)*0.5f;
  FLOAT2D pinterpUV = (p0UV + p1UV)*0.5f;
  _pDP->AddTexture(
    x_pos, y_pos, 0.5f, 0.5f, final_color,
    p0(1), p0(2), p0UV(1), p0UV(2), final_color,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), final_color,
    p1(1), p1(2), p1UV(1), p1UV(2), final_color
    );
if (percentage > 87.5f)
{
  u = (percentage - 87.5f) * 0.01f;
  angle = 3.0f*PI*0.25f - 2.0f*PI*u;
  uv_pos = 0.5f*(1.0f + ctg(angle));

  p0 = FLOAT2D(x_pos - half_width, y_pos - half_height);
  p0UV = FLOAT2D(0.0f, 0.0f);
  p1 = FLOAT2D(x_pos - half_width + width * uv_pos, y_pos - half_height);
  p1UV = FLOAT2D(uv_pos, 0.0f);
  FLOAT2D pinterp = (p0 + p1)*0.5f;
  FLOAT2D pinterpUV = (p0UV + p1UV)*0.5f;
  _pDP->AddTexture(
    x_pos, y_pos, 0.5f, 0.5f, final_color,
    p0(1), p0(2), p0UV(1), p0UV(2), final_color,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), final_color,
    p1(1), p1(2), p1UV(1), p1UV(2), final_color
    );
}
}
}
}

  _pDP->FlushRenderingQueue();
}

static FLOAT DIO_GetTextWidth(const CTString& strText, FLOAT textScale)
{
  _pDP->SetTextCharSpacing(textScale * _dioHUDScaling * _pDP->dp_FontData->fd_pixCharSpacing);
  _pDP->SetTextScaling(textScale * _dioHUDScaling);

  return _pDP->GetTextWidth(strText) / _dioHUDScaling;
}

static void DIO_DrawText
(
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  const CTString &strText,
  FLOAT textScale,
  EScreenPos text_alignment,
  COLOR col,
  FLOAT opacity = 1.0f
)
{
  _pDP->SetTextCharSpacing(textScale * _dioHUDScaling * _pDP->dp_FontData->fd_pixCharSpacing);
  _pDP->SetTextScaling(textScale * _dioHUDScaling);

  const FLOAT text_width_orig = _pDP->GetTextWidth(strText);
  FLOAT text_width = text_width_orig;
  const FLOAT text_height = _pDP->dp_FontData->fd_pixCharHeight * _pDP->dp_fTextScaling;

  FLOAT x_pos = 0.0f;
  if (x_anchor == ESP_Middle) {
    x_pos = _pixDPWidth / 2;
  } else if (x_anchor == ESP_End) {
    x_pos = _pixDPWidth;
  }
  if (text_alignment == ESP_Start) {
    text_width = 0.0f;
  } else if (text_alignment == ESP_Middle) {
    text_width *= 0.5f;
  }
  x_pos += static_cast<FLOAT>(x_offset) * _dioHUDScaling - text_width;
  
  FLOAT y_pos = 0.0f;
  if (y_anchor == ESP_Middle) {
    y_pos = _pixDPHeight / 2;
  } else if (y_anchor == ESP_End) {
    y_pos = _pixDPHeight;
  }
  y_pos += static_cast<FLOAT>(y_offset) * _dioHUDScaling - text_height;

  const UBYTE alpha = Clamp(INDEX(opacity * _ulAlphaHUD), INDEX(0), INDEX(255));
  const INDEX final_color = (col & 0xFFFFFF00) | alpha;
/*
  if (framed) {
    _pDP->Fill(x_pos, y_pos, text_width_orig, text_height, 0x19191980);
  }
*/
  _pDP->PutText(strText, x_pos, y_pos, final_color);
}

static void DrawRotatedQuad( class CTextureObject *_pTO, FLOAT fX, FLOAT fY, FLOAT fSize, ANGLE aAngle, COLOR col)
{
  FLOAT fSinA = Sin(aAngle);
  FLOAT fCosA = Cos(aAngle);
  FLOAT fSinPCos = fCosA*fSize+fSinA*fSize;
  FLOAT fSinMCos = fSinA*fSize-fCosA*fSize;
  FLOAT fI0, fJ0, fI1, fJ1, fI2, fJ2, fI3, fJ3;

  fI0 = fX-fSinPCos;  fJ0 = fY-fSinMCos;
  fI1 = fX+fSinMCos;  fJ1 = fY-fSinPCos;
  fI2 = fX+fSinPCos;  fJ2 = fY+fSinMCos;
  fI3 = fX-fSinMCos;  fJ3 = fY+fSinPCos;
  
  _pDP->InitTexture( _pTO);
  _pDP->AddTexture( fI0, fJ0, 0, 0, col,   fI1, fJ1, 0, 1, col,
                    fI2, fJ2, 1, 1, col,   fI3, fJ3, 1, 0, col);
  _pDP->FlushRenderingQueue();  

}

static void DrawAspectCorrectTextureCentered( class CTextureObject *_pTO, FLOAT fX, FLOAT fY, FLOAT fWidth, COLOR col)
{
  CTextureData *ptd = (CTextureData*)_pTO->GetData();
  FLOAT fTexSizeI = ptd->GetPixWidth();
  FLOAT fTexSizeJ = ptd->GetPixHeight();
  FLOAT fHeight = fWidth*fTexSizeJ/fTexSizeJ;
  
  _pDP->InitTexture( _pTO);
  _pDP->AddTexture( fX-fWidth*0.5f, fY-fHeight*0.5f, fX+fWidth*0.5f, fY+fHeight*0.5f, 0, 0, 1, 1, col);
  _pDP->FlushRenderingQueue();
}

// draw sniper mask
static void HUD_DrawSniperMask(CPlayerWeapons* pWeaponsForSniper)
{
  // determine location
  const FLOAT fSizeI = _pixDPWidth;
  const FLOAT fSizeJ = _pixDPHeight;
  const FLOAT fCenterI = fSizeI/2;  
  const FLOAT fCenterJ = fSizeJ/2;  
  const FLOAT fBlackStrip = (fSizeI-fSizeJ)/2;

  COLOR colMask = C_WHITE|CT_OPAQUE;
  
  CTextureData *ptd = (CTextureData*)_toSniperMask.GetData();
  const FLOAT fTexSizeI = ptd->GetPixWidth();
  const FLOAT fTexSizeJ = ptd->GetPixHeight();

  // main sniper mask
  _pDP->InitTexture( &_toSniperMask);
  _pDP->AddTexture( fBlackStrip, 0, fCenterI, fCenterJ, 0.98f, 0.02f, 0, 1.0f, colMask);
  _pDP->AddTexture( fCenterI, 0, fSizeI-fBlackStrip, fCenterJ, 0, 0.02f, 0.98f, 1.0f, colMask);
  _pDP->AddTexture( fBlackStrip, fCenterJ, fCenterI, fSizeJ, 0.98f, 1.0f, 0, 0.02f, colMask);
  _pDP->AddTexture( fCenterI, fCenterJ, fSizeI-fBlackStrip, fSizeJ, 0, 1, 0.98f, 0.02f, colMask);
  _pDP->FlushRenderingQueue();
  _pDP->Fill( 0, 0, fBlackStrip+1, fSizeJ, C_BLACK|CT_OPAQUE);
  _pDP->Fill( fSizeI-fBlackStrip-1, 0, fBlackStrip+1, fSizeJ, C_BLACK|CT_OPAQUE);

  colMask = LerpColor(SE_COL_BLUE_LIGHT, C_WHITE, 0.25f);

  FLOAT _fYResolutionScaling = (FLOAT)_pixDPHeight/480.0f;

  FLOAT fDistance = pWeaponsForSniper->m_fRayHitDistance;
  FLOAT aFOV = Lerp(pWeaponsForSniper->m_fSniperFOVlast, pWeaponsForSniper->m_fSniperFOV,
                    _pTimer->GetLerpFactor());
  CTString strTmp;
  
  // wheel
  FLOAT fZoom = 1.0f/tan(RadAngle(aFOV)*0.5f);  // 2.0 - 8.0
  
  FLOAT fAFact = (Clamp(aFOV, 14.2f, 53.1f)-14.2f)/(53.1f-14.2f); // only for zooms 2x-4x !!!!!!
  ANGLE aAngle = 314.0f+fAFact*292.0f;

  DrawRotatedQuad(&_toSniperWheel, fCenterI, fCenterJ, 40.0f*_fYResolutionScaling,
                  aAngle, colMask|0x44);
  
  FLOAT fTM = _pTimer->GetLerpedCurrentTick();
  
  COLOR colLED;
  if (pWeaponsForSniper->m_tmLastSniperFire+1.25f<fTM) { // blinking
    colLED = 0x44FF22BB;
  } else {
    colLED = 0xFF4422DD;
  }

  // reload indicator
  DrawAspectCorrectTextureCentered(&_toSniperLed, fCenterI-37.0f*_fYResolutionScaling,
    fCenterJ+36.0f*_fYResolutionScaling, 15.0f*_fYResolutionScaling, colLED);
    
  if (_fResolutionScaling>=1.0f)
  {
    FLOAT _fIconSize;
    FLOAT _fLeftX,  _fLeftYU,  _fLeftYD;
    FLOAT _fRightX, _fRightYU, _fRightYD;

    if (_fResolutionScaling<=1.3f) {
      _pDP->SetFont( _pfdConsoleFont);
      _pDP->SetTextAspect( 1.0f);
      _pDP->SetTextScaling(1.0f);
      _fIconSize = 22.8f;
      _fLeftX = 159.0f;
      _fLeftYU = 8.0f;
      _fLeftYD = 6.0f;
      _fRightX = 159.0f;
      _fRightYU = 11.0f;
      _fRightYD = 6.0f;
    } else {
      _pDP->SetFont( _pfdDisplayFont);
      _pDP->SetTextAspect( 1.0f);
      _pDP->SetTextScaling(0.7f*_fYResolutionScaling);
      _fIconSize = 19.0f;
      _fLeftX = 162.0f;
      _fLeftYU = 8.0f;
      _fLeftYD = 6.0f;
      _fRightX = 162.0f;
      _fRightYU = 11.0f;
      _fRightYD = 6.0f;
    }
     
    // arrow + distance
    DrawAspectCorrectTextureCentered(&_toSniperArrow, fCenterI-_fLeftX*_fYResolutionScaling,
      fCenterJ-_fLeftYU*_fYResolutionScaling, _fIconSize*_fYResolutionScaling, 0xFFCC3399 );
    if (fDistance>9999.9f) { strTmp.PrintF("---.-");           }
    else if (TRUE)         { strTmp.PrintF("%.1f", fDistance); }
    _pDP->PutTextC( strTmp, fCenterI-_fLeftX*_fYResolutionScaling,
      fCenterJ+_fLeftYD*_fYResolutionScaling, colMask|0xaa);
    
    // eye + zoom level
    DrawAspectCorrectTextureCentered(&_toSniperEye,   fCenterI+_fRightX*_fYResolutionScaling,
      fCenterJ-_fRightYU*_fYResolutionScaling, _fIconSize*_fYResolutionScaling, 0xFFCC3399 ); //SE_COL_ORANGE_L
    strTmp.PrintF("%.1fx", fZoom);
    _pDP->PutTextC( strTmp, fCenterI+_fRightX*_fYResolutionScaling,
      fCenterJ+_fRightYD*_fYResolutionScaling, colMask|0xaa);
  }
}


// helper functions

// fill weapon and ammo table with current state
static void FillWeaponAmmoTables(const CPlayer* player)
{
  const CPlayerWeapons* pWeapons = ((CPlayer*)player)->GetPlayerWeapons();
  // ammo quantities
  _aaiAmmo[0].ai_iAmmoAmmount    = pWeapons->m_iShells;
  _aaiAmmo[0].ai_iMaxAmmoAmmount = pWeapons->m_iMaxShells;
  _aaiAmmo[1].ai_iAmmoAmmount    = pWeapons->m_iBullets;
  _aaiAmmo[1].ai_iMaxAmmoAmmount = pWeapons->m_iMaxBullets;
  _aaiAmmo[2].ai_iAmmoAmmount    = pWeapons->m_iRockets;
  _aaiAmmo[2].ai_iMaxAmmoAmmount = pWeapons->m_iMaxRockets;
  _aaiAmmo[3].ai_iAmmoAmmount    = pWeapons->m_iGrenades;
  _aaiAmmo[3].ai_iMaxAmmoAmmount = pWeapons->m_iMaxGrenades;
  _aaiAmmo[4].ai_iAmmoAmmount    = pWeapons->m_iNapalm;
  _aaiAmmo[4].ai_iMaxAmmoAmmount = pWeapons->m_iMaxNapalm;
  _aaiAmmo[5].ai_iAmmoAmmount    = pWeapons->m_iElectricity;
  _aaiAmmo[5].ai_iMaxAmmoAmmount = pWeapons->m_iMaxElectricity;
  _aaiAmmo[6].ai_iAmmoAmmount    = pWeapons->m_iIronBalls;
  _aaiAmmo[6].ai_iMaxAmmoAmmount = pWeapons->m_iMaxIronBalls;
  _aaiAmmo[7].ai_iAmmoAmmount    = pWeapons->m_iSniperBullets;
  _aaiAmmo[7].ai_iMaxAmmoAmmount = pWeapons->m_iMaxSniperBullets;
  
  // prepare ammo table for weapon possesion
  INDEX i, iAvailableWeapons = pWeapons->m_iAvailableWeapons;
  for( i=0; i<8; i++) _aaiAmmo[i].ai_bHasWeapon = FALSE;
  // weapon possesion
  for( i=WEAPON_NONE+1; i<WEAPON_LAST; i++)
  {
    if( _awiWeapons[i].wi_wtWeapon!=WEAPON_NONE)
    {
      // regular weapons
      _awiWeapons[i].wi_bHasWeapon = (iAvailableWeapons&(1<<(_awiWeapons[i].wi_wtWeapon-1)));
      if( _awiWeapons[i].wi_paiAmmo!=NULL) _awiWeapons[i].wi_paiAmmo->ai_bHasWeapon |= _awiWeapons[i].wi_bHasWeapon;
    }
  }
  
  const BOOL usingStand = player->m_mode == STAND_ENGAGED;
  if (usingStand)
    for (i = WEAPON_NONE + 1; i < WEAPON_LAST; ++i)
      if (_awiWeapons[i].wi_wtWeapon != WEAPON_NONE)
        _awiWeapons[i].wi_bHasWeapon = (_awiWeapons[i].wi_wtWeapon == WEAPON_KNIFE) || (_awiWeapons[i].wi_wtWeapon == WEAPON_HANDS);
}

void HUD_SetEntityForStackDisplay(CRationalEntity *pren)
{
}

CTextureObject* GetButtonTexture(INDEX button_index)
{
  switch (button_index)
  {
  case KID_MOUSE1:
    return &_toMBLeft;
  case KID_MOUSE2:
    return &_toMBRight;
  case KID_MOUSE3:
    return &_toMB3;
  case KID_MOUSE4:
    return &_toMB4;
  case KID_MOUSE5:
    return &_toMB5;
  case KID_MOUSEWHEELUP:
    return &_toMWUp;
  case KID_MOUSEWHEELDOWN:
    return &_toMWDown;
  default:
    return NULL;
  }
}

void DIO_DrawButton
(
  const CPlayer* player,
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  const char* title,
  COLOR color = C_WHITE,
  FLOAT opacity = 1.0f
)
{
  if (!player || !player->mp_buttonActionsListHead)
    return;

  INDEX button_index = KID_NONE; 
  FOREACHINLIST(CButtonAction, ba_lnNode, *player->mp_buttonActionsListHead, itButtonAction)
  {
    if (itButtonAction->ba_strName == title)
    {
      if (itButtonAction->ba_iFirstKey != KID_NONE)
        button_index = itButtonAction->ba_iFirstKey;
      else if (itButtonAction->ba_iSecondKey != KID_NONE)
        button_index = itButtonAction->ba_iSecondKey;
      break;
    }
  }
  if (button_index == KID_NONE)
    return;

  CTextureObject* button_texture = GetButtonTexture(button_index);
  if (button_texture)
  {
    DIO_DrawIcon(x_anchor, x_offset, y_anchor, y_offset, *button_texture, 0.0f, color, opacity);
  } else {
    CFontData* prev_font = _pDP->dp_FontData;
    _pDP->SetFont(_owFont);
    const FLOAT text_scale = 0.8f;
    const FLOAT text_height = _pDP->dp_FontData->fd_pixCharHeight * text_scale;
    DIO_DrawText(x_anchor, x_offset - 5, y_anchor, y_offset + text_height * 0.5f, _pInput->GetButtonTransName(button_index), text_scale, ESP_Middle, color, opacity);
    _pDP->SetFont(prev_font);
  }
}

/***************************************
PEW PEW ABILITIES
****************************************/
class AbilityButton
{
public:
  virtual ~AbilityButton()
  {
  }

  void Reinit()
  {
    m_stateChanged = 0;
  }

  BOOL Render
  (
  const CPlayer* player,
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset
  )
  {
    if (!IsVisible(player))
      return FALSE;

    UpdateState(player);
    const FLOAT factor = LerpFactor();
    const FLOAT2D shift = Lerp(m_src_offset, m_desired_offset, factor);
    const FLOAT opacity = Lerp(m_src_opacity, m_desired_opacity, factor);
    const COLOR col = LerpColor(m_src_col, m_desired_col, factor);

    const INDEX x_pos = x_offset + shift(1);
    const INDEX y_pos = y_offset + shift(2);

    DIO_DrawIcon(x_anchor, x_pos, y_anchor, y_pos, m_logo, 0, col, opacity);

    COLOR text_color = C_WHITE;
    switch (m_state)
    {
    case AB_Active:
      if (m_prevstate != AB_Cooldown)
        break;
      if (factor < 1.0f)
        DIO_DrawIcon(x_anchor, x_pos, y_anchor, y_pos, m_logo, 0.0f, col, Lerp(0.2f, 1.0f, factor), Lerp(10.0f, 1.0f, factor));
      break;

    case AB_Using:
      if (factor < 1.0f)
        DIO_DrawIcon(x_anchor, x_offset, y_anchor, y_offset, m_logo, 0, m_desired_col, Lerp(1.0f, 0.0f, factor), Lerp(1.0f, 3.0f, factor));
      break;

    case AB_Inactive:
      DIO_DrawIcon(x_anchor, x_pos, y_anchor, y_pos, _toAbilityFrame, 0, 0x77000000, factor * opacity);
      DIO_DrawIcon(x_anchor, x_pos + 19, y_anchor, y_pos + 30, _toAbilityCancel, 0, C_WHITE, factor * opacity);
      text_color = col;
      break;

    case AB_Cooldown:
      {
        const FLOAT2D cooldown_start_time_and_duration = GetCooldownTimeAndDuration(player);
        const FLOAT cooldown_factor = (_pTimer->GetLerpedCurrentTick() - cooldown_start_time_and_duration(1)) / cooldown_start_time_and_duration(2);
        DIO_DrawIcon(x_anchor, x_pos, y_anchor, y_pos, _toAbilityOverlay, 0, C_WHITE, factor*0.5f, 1.0f, Lerp(0.2421875f, 0.7421875f, cooldown_factor));
        DIO_DrawIcon(x_anchor, x_pos, y_anchor, y_pos, _toAbilityFrame, 0, C_WHITE, factor);


        CTString seconds_left;
        seconds_left.PrintF("%d", (INDEX)ceil((1.0f - cooldown_factor) * cooldown_start_time_and_duration(2)));
        CFontData* prev_font = _pDP->dp_FontData;
        _pDP->SetFont(_owFont);
        const FLOAT text_scale = 1.0f;
        const FLOAT text_height = _pDP->dp_FontData->fd_pixCharHeight * text_scale;
        DIO_DrawText(x_anchor, x_pos - 2, y_anchor, y_pos + text_height * 0.5f + 3, seconds_left, text_scale, ESP_Middle, C_WHITE);
        _pDP->SetFont(prev_font);

        text_color = col;
        break;
      }

    default:
      break;
    }
    DIO_DrawButton(player, x_anchor, x_offset - 15, y_anchor, y_offset + 58, m_button_name, text_color, opacity);

    if (m_prevstate == AB_Cooldown && !m_toAbilityFlame.IsAnimFinished())
    {
      FLOAT flame_angle = RadAngle(22.0f);
      FLOAT2D flame_shift(150.0f * sin(flame_angle), 150.0f * (-cos(flame_angle)));
      DIO_DrawIconADD(x_anchor, x_pos + flame_shift(1), y_anchor, y_pos + flame_shift(2), m_toAbilityFlame, flame_angle, FLOAT2D(1.0f, 2.0f));
    }

    return TRUE;
  }

protected:
  enum ABState
  {
    AB_Active,
    AB_Inactive,
    AB_Using,
    AB_Cooldown
  };

  AbilityButton(CTextureObject& logo, const CTString& button_name)
    : m_logo(logo)
    , m_button_name(button_name)
    , m_src_offset(0,0)
    , m_desired_offset(0,0)
    , m_src_opacity(1.0f)
    , m_desired_opacity(1.0f)
    , m_src_col(C_WHITE)
    , m_desired_col(C_WHITE)
    , m_state(AB_Active)
    , m_prevstate(AB_Active)
    , m_stateChanged(0)
  {
    m_toAbilityFlame.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\Flame.tex"));
    ((CTextureData*)m_toAbilityFlame.GetData())->Force(TEX_CONSTANT);
  }

  void UpdateState(const CPlayer* player)
  {
    ABState new_state = DetermineState(player);
    if (new_state != m_state)
    {
      m_prevstate = m_state;
      const FLOAT factor = LerpFactor();
      m_src_offset = Lerp(m_src_offset, m_desired_offset, factor);
      m_src_opacity = Lerp(m_src_opacity, m_desired_opacity, factor);
      m_src_col = LerpColor(m_src_col, m_desired_col, factor);

      m_stateChanged = _pTimer->GetLerpedCurrentTick();

      if (m_prevstate == AB_Cooldown)
        m_toAbilityFlame.PlayAnim(0, 0);

      switch (new_state)
      {
      case AB_Active:
        m_desired_offset = FLOAT2D(0, 0);
        m_desired_opacity = 1.0f;
        m_desired_col = C_WHITE;
        break;

      case AB_Cooldown: // [[fallthrough]];
      case AB_Inactive:
        m_desired_offset = FLOAT2D(0, 0);
        m_desired_opacity = 0.8f;
        m_desired_col = 0x77777700;
        break;

      case AB_Using:
        m_desired_offset = FLOAT2D(4, 4);
        m_desired_opacity = 1.0f;
        m_desired_col = 0xF48F2700;
        break;

      default:
        FatalError("Unknown ability state!\n");
      }
    } else {
      if (LerpFactor() >= 1.0f)
      {
        m_src_offset = m_desired_offset;
        m_src_opacity = m_desired_opacity;
        m_src_col = m_desired_col;
      }
    }
    m_state = new_state;
  }

  FLOAT LerpFactor() const
  {
    return Clamp((_pTimer->GetLerpedCurrentTick() - m_stateChanged) / 0.1f, 0.0f, 1.0f);
  }

  virtual FLOAT2D GetCooldownTimeAndDuration(const CPlayer* player)
  {
    (void)player;
    return FLOAT2D(INDEX(_pTimer->CurrentTick() / 10.0f) * 10.0f, 10.0f);
  }

  virtual ABState DetermineState(const CPlayer* player) = 0;

  virtual BOOL IsVisible(const CPlayer* player) = 0;

protected:
  CTextureObject& m_logo;
  CTString m_button_name;
  FLOAT2D m_src_offset;
  FLOAT2D m_desired_offset;
  FLOAT m_src_opacity;
  FLOAT m_desired_opacity;
  COLOR m_src_col;
  COLOR m_desired_col;
  ABState m_state;
  ABState m_prevstate;
  TIME m_stateChanged;
  CTextureObject m_toAbilityFlame;
};

/************************************************************/
/************************************************************/
class Ability_Stand : public AbilityButton
{
public:
  Ability_Stand()
    : AbilityButton(_toAbility_Stand, "Toggle stand")
  {
  }

protected:
  FLOAT2D GetCooldownTimeAndDuration(const CPlayer* player)
  {
    if (!player)
      return FLOAT2D(1.0f, 1.0f);

    return FLOAT2D(player->m_tmWhenStandTurnedPassive, player->GetStandAbilityCooldown());
  }

  ABState DetermineState(const CPlayer* player)
  {
    if (!player)
      return AB_Inactive;

    if (!player->m_penTheWorld)
      return AB_Inactive;

    if (player->m_mode == STAND_ENGAGED)
      return AB_Using;

    FLOAT2D cd_time_and_duration = GetCooldownTimeAndDuration(player);
    if (_pTimer->CurrentTick() - cd_time_and_duration(1) <= cd_time_and_duration(2))
      return AB_Cooldown;

    return AB_Active;
  }

  BOOL IsVisible(const CPlayer*)
  {
    return TRUE;
  }
};

/************************************************************/
/************************************************************/
class Ability_Leg : public AbilityButton
{
public:
  Ability_Leg()
    : AbilityButton(_toAbility_Leg, "Secondary Fire/Sniper Zoom")
  {
  }

protected:
  ABState DetermineState(const CPlayer* player)
  {
    if (player && player->m_penWeapons)
    {
      const CPlayerWeapons* weapons = (const CPlayerWeapons*)&*(player->m_penWeapons);
      if (weapons->IsPlayerSwimming())
        return AB_Inactive;
      if (weapons->m_iCurrentWeapon != WEAPON_HANDS && weapons->m_bLegKickInProgress)
        return AB_Using;
      if (weapons->HoldingFire() && weapons->m_bSecondaryFire)
        return AB_Using;
    }

    return AB_Active;
  }

  BOOL IsVisible(const CPlayer* player)
  {
    if (player && player->m_penWeapons)
    {
      const CPlayerWeapons* weapons = (const CPlayerWeapons*)&*(player->m_penWeapons);
      return weapons->m_iCurrentWeapon != WEAPON_SNIPER && weapons->m_iCurrentWeapon != WEAPON_KNIFE;
    }
    return FALSE;
  }
};

/************************************************************/
/************************************************************/
class Ability_Zoom : public AbilityButton
{
public:
  Ability_Zoom()
    : AbilityButton(_toAbility_Zoom, "Secondary Fire/Sniper Zoom")
  {
  }

protected:
  ABState DetermineState(const CPlayer* player)
  {
    if (player && player->m_penWeapons)
    {
      const CPlayerWeapons* weapons = (const CPlayerWeapons*)&*(player->m_penWeapons);
      if (weapons->m_bSniping)
        return AB_Using;
    }

    return AB_Active;
  }

  BOOL IsVisible(const CPlayer* player)
  {
    if (player && player->m_penWeapons)
    {
      const CPlayerWeapons* weapons = (const CPlayerWeapons*)&*(player->m_penWeapons);
      return weapons->m_iCurrentWeapon == WEAPON_SNIPER;
    }
    return FALSE;
  }
};

/************************************************************/
/************************************************************/
class Ability_Knives : public AbilityButton
{
public:
  Ability_Knives()
    : AbilityButton(_toAbility_Knives, "Secondary Fire/Sniper Zoom")
  {
  }

protected:
  ABState DetermineState(const CPlayer* player)
  {
    if (player && player->m_penWeapons)
    {
      const CPlayerWeapons* weapons = (const CPlayerWeapons*)&*(player->m_penWeapons);
      if (weapons->HoldingFire() && weapons->m_bSecondaryFire)
        return AB_Using;
    }

    return AB_Active;
  }

  BOOL IsVisible(const CPlayer* player)
  {
    if (player && player->m_penWeapons)
    {
      const CPlayerWeapons* weapons = (const CPlayerWeapons*)&*(player->m_penWeapons);
      return weapons->m_iCurrentWeapon == WEAPON_KNIFE;
    }
    return FALSE;
  }
};

/************************************************************/
/************************************************************/
class Ability_Menacing : public AbilityButton
{
public:
  Ability_Menacing()
    : AbilityButton(_toAbility_Menacing, "Emote")
  {
  }

protected:
  ABState DetermineState(const CPlayer* player)
  {
    if (player)
    {
      if (player->m_bInEmote)
        return AB_Using;
    }

    return AB_Active;
  }

  BOOL IsVisible(const CPlayer* player)
  {
    if (player)
      return TRUE;
    return FALSE;
  }
};

typedef AbilityButton* AbilityPtr;
static AbilityPtr abilities[NET_MAXGAMEPLAYERS][5] = { NULL };

// render interface (frontend) to drawport
// (units are in pixels for 1920x1080 resolution - for other res HUD will be scalled automatically)
extern void DrawHUD(CPlayer* penPlayerMaybePredicted, CDrawPort *pdpCurrent)
{
  // no player - no info, sorry
  if( penPlayerMaybePredicted==NULL || (penPlayerMaybePredicted->GetFlags()&ENF_DELETED)) return;
  const CPlayer* penPlayerCurrent = (CPlayer*)penPlayerMaybePredicted->GetPredictionTail();

  FixupHiresFonts();

  // cache local variables
  hud_fOpacity = Clamp( hud_fOpacity, 0.1f, 1.0f);
  hud_fScaling = Clamp( hud_fScaling, 0.5f, 1.2f);
  _penPlayer  = penPlayerCurrent;
  _penWeapons = (CPlayerWeapons*)&*_penPlayer->m_penWeapons;
  _pDP        = pdpCurrent;
  _pixDPWidth   = _pDP->GetWidth();
  _pixDPHeight  = _pDP->GetHeight();
  _fResolutionScaling = (FLOAT)_pixDPWidth /640.0f;
  _colHUD     = 0x4C80BB00;
  _colHUDText = SE_COL_ORANGE_LIGHT;
  _ulAlphaHUD = NormFloatToByte(hud_fOpacity);
  _tmNow = _pTimer->CurrentTick();

  _dioHUDScaling = _pixDPHeight / 1080.0f;

  // draw sniper mask (original mask even if snooping)
  CPlayerWeapons* pWeaponsForSniper = (CPlayerWeapons*)&*penPlayerMaybePredicted->m_penWeapons;
  if (pWeaponsForSniper->m_iCurrentWeapon==WEAPON_SNIPER && pWeaponsForSniper->m_bSniping)
    HUD_DrawSniperMask(pWeaponsForSniper);

  CTextureObject* p_portrait = &_toDIO;
  if (_penPlayer->m_mode == STAND_ENGAGED)
    p_portrait = &_toZaWarudo;
  DIO_DrawIcon(ESP_Start, 187, ESP_End, -135, *p_portrait);
   
  // prepare font and text dimensions
  CTString strValue;
  FLOAT fValue, fNormValue;
  _pDP->SetFont( &_fdNumbersFont);
  
  // prepare and draw health info
  fValue = ClampDn( _penPlayer->GetHealth(), 0.0f);  // never show negative health

/*
HEALTH
*/
  COLOR colIcon;
  CTextureObject *ptoCurrentAmmo=NULL, *ptoCurrentWeapon=NULL, *ptoWantedWeapon=NULL;
  INDEX iCurrentWeapon = _penWeapons->m_iCurrentWeapon;
  INDEX iWantedWeapon  = _penWeapons->m_iWantedWeapon;
  // determine corresponding ammo and weapon texture component
  ptoCurrentWeapon = _awiWeapons[iCurrentWeapon].wi_ptoWeapon;
  ptoWantedWeapon  = _awiWeapons[iWantedWeapon].wi_ptoWeapon;

  if (ptoCurrentWeapon)
  {
    AmmoInfo *paiCurrent = _awiWeapons[iCurrentWeapon].wi_paiAmmo;
    if (paiCurrent!=NULL)
      ptoCurrentAmmo = paiCurrent->ai_ptoAmmo;
  }
  if (hud_iShowPlayersList != 1) {
  const FLOAT bar_sections_per_100hp = 8.0f;
  const FLOAT bar_length = 217.0f;
  const COLOR additional_color = 0x59D5FF00;

  FLOAT2D p_top_left(277.0f * _dioHUDScaling, _pixDPHeight - 157.0f * _dioHUDScaling);
  FLOAT2D p_bottom_left = p_top_left + FLOAT2D(11.0f * _dioHUDScaling, 30.0f * _dioHUDScaling);
  FLOAT2D p_top_right = p_top_left + FLOAT2D(bar_length * _dioHUDScaling, 0.0f);
  FLOAT2D p_bottom_right = p_bottom_left + FLOAT2D(bar_length * _dioHUDScaling, 0.0f);

  if (fValue > TopHealth())
  {
    FLOAT hp_ratio = fValue / 100.0f;
    FLOAT bar_sections = bar_sections_per_100hp * hp_ratio;

    _pDP->InitTexture(&_toBarBcg);
    _pDP->AddTexture(
      p_top_left(1),     p_top_left(2),     0.0f,         0.0f, C_WHITE|_ulAlphaHUD,
      p_top_right(1),    p_top_right(2),    bar_sections, 0.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_right(1), p_bottom_right(2), bar_sections, 1.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_left(1),  p_bottom_left(2),  0.0f,         1.0f, C_WHITE|_ulAlphaHUD
      );
    _pDP->FlushRenderingQueue();

    FLOAT base_ratio = TopHealth() / fValue;

    FLOAT p_bottom_middle = p_bottom_left(1) + (p_bottom_right(1) - p_bottom_left(1))*base_ratio;
    FLOAT p_top_middle = p_top_left(1) + (p_top_right(1) - p_top_left(1))*base_ratio;
    
    _pDP->InitTexture(&_toBar);
    _pDP->AddTexture(
      p_top_left(1),    p_top_left(2),     0.0f,                    0.0f, C_WHITE|_ulAlphaHUD,
      p_top_middle,     p_top_right(2),    bar_sections*base_ratio, 0.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_middle,  p_bottom_right(2), bar_sections*base_ratio, 1.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_left(1), p_bottom_left(2),  0.0f,                    1.0f, C_WHITE|_ulAlphaHUD
      );

    _pDP->AddTexture(
      p_top_middle,      p_top_right(2),    0.0f,                             0.0f, additional_color|_ulAlphaHUD,
      p_top_right(1),    p_top_right(2),    bar_sections*(1.0f - base_ratio), 0.0f, additional_color|_ulAlphaHUD,
      p_bottom_right(1), p_bottom_right(2), bar_sections*(1.0f - base_ratio), 1.0f, additional_color|_ulAlphaHUD,
      p_bottom_middle,   p_bottom_right(2), 0.0f,                             1.0f, additional_color|_ulAlphaHUD
      );

    _pDP->FlushRenderingQueue();
  } else {
    FLOAT hp_ratio = TopHealth() / 100.0f;
    FLOAT bar_sections = bar_sections_per_100hp * hp_ratio;

    _pDP->InitTexture(&_toBarBcg);
    _pDP->AddTexture(
      p_top_left(1),     p_top_left(2),     0.0f,         0.0f, C_WHITE|_ulAlphaHUD,
      p_top_right(1),    p_top_right(2),    bar_sections, 0.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_right(1), p_bottom_right(2), bar_sections, 1.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_left(1),  p_bottom_left(2),  0.0f,         1.0f, C_WHITE|_ulAlphaHUD
      );
    _pDP->FlushRenderingQueue();

    FLOAT current_hp_ratio = fValue / TopHealth();
    p_top_right = p_top_left + FLOAT2D(bar_length * _dioHUDScaling * current_hp_ratio, 0.0f);
    p_bottom_right = p_bottom_left + FLOAT2D(bar_length * _dioHUDScaling * current_hp_ratio, 0.0f);

    _pDP->InitTexture(&_toBar);
    _pDP->AddTexture(
      p_top_left(1),     p_top_left(2),     0.0f,                            0.0f, C_WHITE|_ulAlphaHUD,
      p_top_right(1),    p_top_right(2),    bar_sections * current_hp_ratio, 0.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_right(1), p_bottom_right(2), bar_sections * current_hp_ratio, 1.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_left(1),  p_bottom_left(2),  0.0f,                            1.0f, C_WHITE|_ulAlphaHUD
      );
    _pDP->FlushRenderingQueue();
  }

  strValue.PrintF("%d", (SLONG)ceil(fValue));
  DIO_DrawText(ESP_Start, 320, ESP_End, -146, strValue, 0.75f, ESP_End, C_WHITE);
  DIO_DrawText(ESP_Start, 320+7, ESP_End, -146-7, "/", 0.5f, ESP_Middle, additional_color);
  strValue.PrintF("%d", (SLONG)ceil(max(TopHealth(), fValue)));
  DIO_DrawText(ESP_Start, 320+13, ESP_End, -146-7, strValue, 0.5f, ESP_Start, C_WHITE);


  /*
  ARMOR
  */

  // prepare and draw armor info (eventually)
  fValue = _penPlayer->m_fArmor;
  if (fValue > 0.0f)
  {
    const COLOR armor_color = 0xFBD01900;

    FLOAT2D p_top_left(288.0f * _dioHUDScaling, _pixDPHeight - 127.0f * _dioHUDScaling);
    FLOAT2D p_bottom_left = p_top_left + FLOAT2D(-11.0f * _dioHUDScaling, 30.0f * _dioHUDScaling);
    FLOAT2D p_top_right = p_top_left + FLOAT2D(bar_length * _dioHUDScaling, 0.0f);
    FLOAT2D p_bottom_right = p_bottom_left + FLOAT2D(bar_length * _dioHUDScaling, 0.0f);

    if (fValue > TopArmor())
    {
      FLOAT armor_ratio = fValue / 100.0f;
      FLOAT bar_sections = bar_sections_per_100hp * armor_ratio;

      _pDP->InitTexture(&_toBarBcg);
      _pDP->AddTexture(
        p_top_left(1),     p_top_left(2),     0.0f,         0.0f, C_WHITE|_ulAlphaHUD,
        p_top_right(1),    p_top_right(2),    bar_sections, 0.0f, C_WHITE|_ulAlphaHUD,
        p_bottom_right(1), p_bottom_right(2), bar_sections, 1.0f, C_WHITE|_ulAlphaHUD,
        p_bottom_left(1),  p_bottom_left(2),  0.0f,         1.0f, C_WHITE|_ulAlphaHUD
        );
      _pDP->FlushRenderingQueue();

      FLOAT base_ratio = TopArmor() / fValue;

      FLOAT p_bottom_middle = p_bottom_left(1) + (p_bottom_right(1) - p_bottom_left(1))*base_ratio;
      FLOAT p_top_middle = p_top_left(1) + (p_top_right(1) - p_top_left(1))*base_ratio;
    
      _pDP->InitTexture(&_toBar);
      _pDP->AddTexture(
        p_top_left(1),    p_top_left(2),     0.0f,                    0.0f, armor_color|_ulAlphaHUD,
        p_top_middle,     p_top_right(2),    bar_sections*base_ratio, 0.0f, armor_color|_ulAlphaHUD,
        p_bottom_middle,  p_bottom_right(2), bar_sections*base_ratio, 1.0f, armor_color|_ulAlphaHUD,
        p_bottom_left(1), p_bottom_left(2),  0.0f,                    1.0f, armor_color|_ulAlphaHUD
        );

      _pDP->AddTexture(
        p_top_middle,      p_top_right(2),    0.0f,                             0.0f, additional_color|_ulAlphaHUD,
        p_top_right(1),    p_top_right(2),    bar_sections*(1.0f - base_ratio), 0.0f, additional_color|_ulAlphaHUD,
        p_bottom_right(1), p_bottom_right(2), bar_sections*(1.0f - base_ratio), 1.0f, additional_color|_ulAlphaHUD,
        p_bottom_middle,   p_bottom_right(2), 0.0f,                             1.0f, additional_color|_ulAlphaHUD
        );

      _pDP->FlushRenderingQueue();
    } else {
      FLOAT armor_ratio = TopArmor() / 100.0f;
      FLOAT bar_sections = bar_sections_per_100hp * armor_ratio;

      _pDP->InitTexture(&_toBarBcg);
      _pDP->AddTexture(
        p_top_left(1),     p_top_left(2),     0.0f,         0.0f, C_WHITE|_ulAlphaHUD,
        p_top_right(1),    p_top_right(2),    bar_sections, 0.0f, C_WHITE|_ulAlphaHUD,
        p_bottom_right(1), p_bottom_right(2), bar_sections, 1.0f, C_WHITE|_ulAlphaHUD,
        p_bottom_left(1),  p_bottom_left(2),  0.0f,         1.0f, C_WHITE|_ulAlphaHUD
        );
      _pDP->FlushRenderingQueue();

      FLOAT current_hp_ratio = fValue / TopArmor();
      p_top_right = p_top_left + FLOAT2D(bar_length * _dioHUDScaling * current_hp_ratio, 0.0f);
      p_bottom_right = p_bottom_left + FLOAT2D(bar_length * _dioHUDScaling * current_hp_ratio, 0.0f);

      _pDP->InitTexture(&_toBar);
      _pDP->AddTexture(
        p_top_left(1),     p_top_left(2),     0.0f,                            0.0f, armor_color|_ulAlphaHUD,
        p_top_right(1),    p_top_right(2),    bar_sections * current_hp_ratio, 0.0f, armor_color|_ulAlphaHUD,
        p_bottom_right(1), p_bottom_right(2), bar_sections * current_hp_ratio, 1.0f, armor_color|_ulAlphaHUD,
        p_bottom_left(1),  p_bottom_left(2),  0.0f,                            1.0f, armor_color|_ulAlphaHUD
        );
      _pDP->FlushRenderingQueue();
    }

    strValue.PrintF("%d", (SLONG)ceil(fValue));
    DIO_DrawText(ESP_Start, 310, ESP_End, -50, strValue, 0.75f, ESP_End, C_WHITE);
    DIO_DrawText(ESP_Start, 310+7, ESP_End, -50-13, "/", 0.5f, ESP_Middle, additional_color);
    strValue.PrintF("%d", (SLONG)ceil(max(TopArmor(), fValue)));
    DIO_DrawText(ESP_Start, 310+13, ESP_End, -50-13, strValue, 0.5f, ESP_Start, C_WHITE);
  }

/*
ULTIMATE
*/
  if (_penPlayer->m_penMainMusicHolder!=NULL) {
    CMusicHolder &mh = (CMusicHolder&)*_penPlayer->m_penMainMusicHolder;
    const BOOL is_zawarudo = mh.IsZaWarudo();
    if (is_zawarudo) {
      FLOAT warudo_percentage = Clamp(1.0f - (_pTimer->GetLerpedCurrentTick() - mh.m_timeZaWarudoStart) / ZA_WARUDO_DURATION, 0.0f, 1.0f);
      DIO_DrawIconCircle(ESP_Middle, 0, ESP_Start, 110, _toWarudoBcg, warudo_percentage*100.0f);
      DIO_DrawIcon(ESP_Middle, 0, ESP_Start, 110, _toWarudoTimer);
      DIO_DrawIcon(ESP_Middle, 0, ESP_Start, 110, _toWarudoArrow, RadAngle(warudo_percentage*360));
    }

    FLOAT ultimate_opacity = 0.0f;
    if (_penPlayer->m_ultimateCharge >= MAX_ULTIMATE_CHARGE) {
      ultimate_opacity = Clamp(2.0f * (_pTimer->CurrentTick() - _penPlayer->m_tmGainedUltimate), 0.0f, 1.0f);
    }
    if (ultimate_opacity > 0.0f) {
      BOOL can_throw_rodarollada = const_cast<CPlayer*>(_penPlayer)->CanThrowRodaRollaDa();

      COLOR ult_icon_color = C_WHITE;
      if (is_zawarudo && !can_throw_rodarollada) {
        ult_icon_color = C_GRAY;
      }

      DIO_DrawIcon(ESP_Middle, 0, ESP_End, -120 - 32, _toFireTexture, 0.0f, C_WHITE, ultimate_opacity);
      DIO_DrawIcon(ESP_Middle, 0, ESP_End, -90 - 32, _toUltFlare, _pTimer->CurrentTick()*45.0f*PI/180.0f, C_WHITE, ultimate_opacity);
      DIO_DrawIcon(ESP_Middle, 0, ESP_End, -90 - 32, (is_zawarudo ? _toUltRodarollada : _toUlt), 0.0f, ult_icon_color, ultimate_opacity);
    }
    if (ultimate_opacity < 1.0f) {
      const FLOAT ult_percentage = (_penPlayer->m_ultimateCharge / static_cast<FLOAT>(MAX_ULTIMATE_CHARGE)) * 100.0f;
      DIO_DrawIcon(ESP_Middle, 0, ESP_End, -90 - 32, _toUltBcg, 0.0f, C_WHITE, 1.0f - ultimate_opacity);
      DIO_DrawIconCircle(ESP_Middle, 0, ESP_End, -90 - 32, _toUltOverlay, ult_percentage, C_WHITE, 1.0f - ultimate_opacity);
      strValue.PrintF("%d", int(ult_percentage));
      DIO_DrawText(ESP_Middle, -4, ESP_End, -53 -32, strValue, 1.0f, ESP_Middle, C_WHITE, 1.0f - ultimate_opacity);
    }


    DIO_DrawButton(_penPlayer, ESP_Middle, 0, ESP_End, -44, "Ultimate");
  }
  /*
  CURRENT WEAPON DRAWING
  */



  if (ptoCurrentWeapon)
  {
    DIO_DrawIcon(ESP_End, -72, ESP_End, -121, _toWeaponBrace);
    DIO_DrawIcon(ESP_End, -168, ESP_End, -124, *ptoCurrentWeapon);

    if (ptoCurrentAmmo!=NULL && !GetSP()->sp_bInfiniteAmmo)
    {
      fValue = _penWeapons->GetAmmo();
      strValue.PrintF("%d", (SLONG)ceil(fValue));
      DIO_DrawText(ESP_End, -122, ESP_End, -136, strValue, 0.75f, ESP_End, C_WHITE);
      DIO_DrawText(ESP_End, -122+7, ESP_End, -136-7, "/", 0.5f, ESP_Middle, additional_color);
      strValue.PrintF("%d", (SLONG)ceil(_penWeapons->GetMaxAmmo()));
      DIO_DrawText(ESP_End, -122+13, ESP_End, -136-7, strValue, 0.5f, ESP_Start, C_WHITE);
    } else {
      DIO_DrawIcon(ESP_End, -117, ESP_End, -162, _toInfAmmo);
    }
  }

  if (penPlayerCurrent->m_iSeriousBombCount > 0)
  {
    DIO_DrawIcon(ESP_End, -32, ESP_End, -237, _toWeaponBrace);
    DIO_DrawIcon(ESP_End, -128, ESP_End, -240, _toWSBomb);
    strValue.PrintF("%d", penPlayerCurrent->m_iSeriousBombCount);
    DIO_DrawText(ESP_End, -82, ESP_End, -252, strValue, 0.75f, ESP_End, C_WHITE);
    DIO_DrawText(ESP_End, -82+7, ESP_End, -252-7, "/", 0.5f, ESP_Middle, additional_color);
    DIO_DrawText(ESP_End, -82+13, ESP_End, -252-7, "3", 0.5f, ESP_Start, C_WHITE);
  }

  /*
  ABILITY DRAWING
  */
  if (TRUE)
  {
    INDEX player_index = GetPlayerIndex(penPlayerCurrent);
    INDEX shift = 0;
    for (INDEX i = 0; i < 5; ++i)
    {
      shift += abilities[player_index][i]->Render(penPlayerCurrent, ESP_End, -300 - (77*shift), ESP_End, -121) ? 1 : 0;
    }
  }

  // display all ammo infos
  INDEX i;
  FillWeaponAmmoTables(penPlayerCurrent);

  // draw powerup(s) if needed
  TIME *ptmPowerups = (TIME*)&_penPlayer->m_tmInvisibility;
  TIME *ptmPowerupsMax = (TIME*)&_penPlayer->m_tmInvisibilityMax;
  INDEX numPowerUps = 0;
  for (i=0; i<MAX_POWERUPS; i++)
  {
    const TIME tmDelta = ptmPowerups[i] - _tmNow;
    if( tmDelta>0)
      numPowerUps++;
  }

  if (numPowerUps > 0)
  {
    const FLOAT powerup_w = ((CTextureData*)_atoPowerups[0].GetData())->GetPixWidth();
    const FLOAT powerup_h = ((CTextureData*)_atoPowerups[0].GetData())->GetPixHeight();
    const FLOAT powerups_height_total = numPowerUps*powerup_h + (numPowerUps-1)*16.0f;
    const float powerups_width_total = powerup_w + 8.0f;
    const FLOAT x_pos = 32.0f + powerup_w*0.5f;
    FLOAT y_pos = 0.5f*powerups_height_total - powerup_h*0.5f;
    FLOAT y_advance = -(powerup_h + 16.0f);

    DIO_DrawBcg(
      ESP_Start, 32.0f + powerups_width_total * 0.5f,
      ESP_Middle, 0,
      ESP_Middle, powerups_width_total,
      ESP_Middle, powerups_height_total,
      0x19191980);

    for (i=0; i<MAX_POWERUPS; i++)
    {
      const TIME tmDelta = ptmPowerups[i] - _tmNow;
      if( tmDelta<=0) continue;
      fNormValue = tmDelta / ptmPowerupsMax[i];

      DIO_DrawBcg(
        ESP_Start, 32.0f + powerup_w + 4.0f,
        ESP_Middle, y_pos + powerup_h*0.5f,
        ESP_Middle, 8.0f,
        ESP_Start, -powerup_h*fNormValue,
        additional_color | 0xFF);

      DIO_DrawIcon(ESP_Start, x_pos, ESP_Middle, y_pos, _atoPowerups[i]);
      // play sound if icon is flashing
      if (fNormValue <= 0.125f) {
        // activate blinking only if value is <= half the low edge
        INDEX iLastTime = (INDEX)(_tmLast*4);
        INDEX iCurrentTime = (INDEX)(_tmNow*4);
        if(iCurrentTime&1 & !(iLastTime&1)) {
          ((CPlayer *)penPlayerCurrent)->PlayPowerUpSound();
        }
      }
      y_pos += y_advance;
    }
  }


  // if weapon change is in progress
  hud_tmWeaponsOnScreen = Clamp( hud_tmWeaponsOnScreen, 0.0f, 10.0f);   
  if( (_tmNow - _penWeapons->m_tmWeaponChangeRequired) < hud_tmWeaponsOnScreen) {
    // determine number of weapons that player has
    INDEX ctWeapons = 0;
    for( i=WEAPON_NONE+1; i<WEAPON_LAST; i++) {
      if( _awiWeapons[i].wi_wtWeapon!=WEAPON_NONE && _awiWeapons[i].wi_wtWeapon!=WEAPON_DOUBLECOLT &&
          _awiWeapons[i].wi_bHasWeapon)
          ctWeapons++;
    }
    const INDEX numWeaponsInColumn = 7;
    // display all available weapons
    FLOAT y_offset = -(min(ctWeapons, numWeaponsInColumn)*0.5f - 0.5f) * ((CTextureData*)_toWKnife.GetData())->GetPixHeight();
    FLOAT y_original = y_offset;
    FLOAT x_offset = -(32.0f + 0.5f*((CTextureData*)_toWKnife.GetData())->GetPixWidth());
    
    FLOAT border_width = ((CTextureData*)_toWKnife.GetData())->GetPixWidth();
    FLOAT border_height = min(ctWeapons, numWeaponsInColumn)*((CTextureData*)_toWKnife.GetData())->GetPixHeight();

    if (ctWeapons > numWeaponsInColumn)
    {
      x_offset -= ((CTextureData*)_toWKnife.GetData())->GetPixWidth();
      border_width *= 2.0f;
    }

    DIO_DrawBcg(
      ESP_End, -(32.0f + border_width*0.5f),
      ESP_Middle, 0,
      ESP_Middle, border_width,
      ESP_Middle, border_height,
      0x19191980);

    // display all available weapons
    for( INDEX ii=WEAPON_NONE+1, iCounter = 0; ii<WEAPON_LAST; ii++, iCounter++)
    {
      i = aiWeaponsRemap[ii];
      // skip if hasn't got this weapon
      if (_awiWeapons[i].wi_wtWeapon==WEAPON_NONE ||
          _awiWeapons[i].wi_wtWeapon==WEAPON_DOUBLECOLT ||
          !_awiWeapons[i].wi_bHasWeapon)
      {
          iCounter--;
          continue;
      }
      // weapon that is currently selected has different colors
      if (ptoWantedWeapon == _awiWeapons[i].wi_ptoWeapon ||
          (_awiWeapons[iWantedWeapon].wi_wtWeapon == WEAPON_COLT && _awiWeapons[i].wi_wtWeapon == WEAPON_DOUBLECOLT) ||
          (_awiWeapons[iWantedWeapon].wi_wtWeapon == WEAPON_DOUBLECOLT && _awiWeapons[i].wi_wtWeapon == WEAPON_COLT))
        colIcon = additional_color;
      else
        colIcon = C_WHITE;

      // no ammo
      if (_awiWeapons[i].wi_paiAmmo!=NULL && _awiWeapons[i].wi_paiAmmo->ai_iAmmoAmmount==0)
        colIcon = 0x42424200;

      DIO_DrawIcon(ESP_End, x_offset, ESP_Middle, y_offset, *_awiWeapons[i].wi_ptoWeapon, 0.0f, colIcon);

      // advance to next position
      y_offset += ((CTextureData*)_toWKnife.GetData())->GetPixHeight();
      if (iCounter == numWeaponsInColumn - 1)
      {
        y_offset = y_original;
        x_offset += ((CTextureData*)_toWKnife.GetData())->GetPixWidth();
      }
    }
  }

  // draw oxygen info if needed
  FLOAT top_oxygen = 30.0f;
  fValue = _penPlayer->en_tmMaxHoldBreath - (_pTimer->CurrentTick() - _penPlayer->en_tmLastBreathed);
  if (_penPlayer->IsConnected() && (_penPlayer->GetFlags()&ENF_ALIVE) && fValue < top_oxygen)
  {
    FLOAT oxygen_w = ((CTextureData*)_toOxygen.GetData())->GetPixWidth();
    FLOAT oxygen_h = ((CTextureData*)_toOxygen.GetData())->GetPixHeight();
    FLOAT ogyxen_x = -0.5f*(bar_length + oxygen_w);
    FLOAT oxygen_y = 70.0f;

    DIO_DrawIcon(
      ESP_Middle, ogyxen_x,
      ESP_Start,  oxygen_y + oxygen_h*0.5f,
      _toOxygen);

    FLOAT2D p_top_left(_pixDPWidth*0.5f - bar_length*0.5f * _dioHUDScaling, (oxygen_y + oxygen_h*0.5f - 15.0f) * _dioHUDScaling);
    FLOAT2D p_bottom_left = p_top_left + FLOAT2D(0.0f, 30.0f * _dioHUDScaling);
    FLOAT2D p_top_right = p_top_left + FLOAT2D(bar_length * _dioHUDScaling, 0.0f);
    FLOAT2D p_bottom_right = p_bottom_left + FLOAT2D(bar_length * _dioHUDScaling, 0.0f);

    FLOAT bar_sections = 8.0f;

    _pDP->InitTexture(&_toBarBcg);
    _pDP->AddTexture(
      p_top_left(1),     p_top_left(2),     0.0f,         0.0f, C_WHITE|_ulAlphaHUD,
      p_top_right(1),    p_top_right(2),    bar_sections, 0.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_right(1), p_bottom_right(2), bar_sections, 1.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_left(1),  p_bottom_left(2),  0.0f,         1.0f, C_WHITE|_ulAlphaHUD
      );
    _pDP->FlushRenderingQueue();
    
    FLOAT current_ratio = fValue / top_oxygen;
    p_top_right    = p_top_left    + FLOAT2D(bar_length * _dioHUDScaling * current_ratio, 0.0f);
    p_bottom_right = p_bottom_left + FLOAT2D(bar_length * _dioHUDScaling * current_ratio, 0.0f);

    _pDP->InitTexture(&_toBar);
    _pDP->AddTexture(
      p_top_left(1),     p_top_left(2),     0.0f,                         0.0f, C_WHITE|_ulAlphaHUD,
      p_top_right(1),    p_top_right(2),    bar_sections * current_ratio, 0.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_right(1), p_bottom_right(2), bar_sections * current_ratio, 1.0f, C_WHITE|_ulAlphaHUD,
      p_bottom_left(1),  p_bottom_left(2),  0.0f,                         1.0f, C_WHITE|_ulAlphaHUD
      );
    _pDP->FlushRenderingQueue();
  }

  // draw boss energy if needed
  if (_penPlayer->m_penMainMusicHolder!=NULL)
  {
    CMusicHolder &mh = (CMusicHolder&)*_penPlayer->m_penMainMusicHolder;
    FLOAT fNormValue = 0.0f;
    FLOAT fValue = 0.0f;

    if (mh.m_penBoss != NULL && (mh.m_penBoss->en_ulFlags&ENF_ALIVE))
    {
      CEnemyBase &eb = (CEnemyBase&)*mh.m_penBoss;
      ASSERT( eb.m_fMaxHealth>0);
      fValue = eb.GetHealth();
      fNormValue = fValue/eb.m_fMaxHealth;
    }
    if (mh.m_penCounter != NULL)
    {
      CEnemyCounter &ec = (CEnemyCounter&)*mh.m_penCounter;
      if (ec.m_iCount>0)
      {
        fValue = ec.m_iCount;
        fNormValue = fValue/ec.m_iCountFrom;
      }
    }
    
    if (fNormValue>0)
    {
      FLOAT bar_sections = 32.0f;

      FLOAT2D p_top_left(_pixDPWidth*0.5f - bar_length * _dioHUDScaling, 143.0f * _dioHUDScaling);
      FLOAT2D p_bottom_left = p_top_left + FLOAT2D(0.0f, 30.0f * _dioHUDScaling);
      FLOAT2D p_top_right = p_top_left + FLOAT2D(bar_length*2.0f * _dioHUDScaling, 0.0f);
      FLOAT2D p_bottom_right = p_bottom_left + FLOAT2D(bar_length*2.0f * _dioHUDScaling, 0.0f);

      _pDP->InitTexture(&_toBarBcg);
      _pDP->AddTexture(
        p_top_left(1),     p_top_left(2),     0.0f,         0.0f, C_WHITE|_ulAlphaHUD,
        p_top_right(1),    p_top_right(2),    bar_sections, 0.0f, C_WHITE|_ulAlphaHUD,
        p_bottom_right(1), p_bottom_right(2), bar_sections, 1.0f, C_WHITE|_ulAlphaHUD,
        p_bottom_left(1),  p_bottom_left(2),  0.0f,         1.0f, C_WHITE|_ulAlphaHUD
        );
      _pDP->FlushRenderingQueue();

      p_top_right    = p_top_left    + FLOAT2D(bar_length*2.0f * _dioHUDScaling * fNormValue, 0.0f);
      p_bottom_right = p_bottom_left + FLOAT2D(bar_length*2.0f * _dioHUDScaling * fNormValue, 0.0f);

      COLOR boss_color = 0xFE001300;
      _pDP->InitTexture(&_toBar);
      _pDP->AddTexture(
        p_top_left(1),     p_top_left(2),     0.0f,                      0.0f, boss_color|_ulAlphaHUD,
        p_top_right(1),    p_top_right(2),    bar_sections * fNormValue, 0.0f, boss_color|_ulAlphaHUD,
        p_bottom_right(1), p_bottom_right(2), bar_sections * fNormValue, 1.0f, boss_color|_ulAlphaHUD,
        p_bottom_left(1),  p_bottom_left(2),  0.0f,                      1.0f, boss_color|_ulAlphaHUD
        );
      _pDP->FlushRenderingQueue();
    }
  }
}
  // determine scaling of normal text and play mode
  const FLOAT fTextScale  = (_fResolutionScaling+1) *0.5f;
  const BOOL bSinglePlay  =  GetSP()->sp_bSinglePlayer;
  const BOOL bCooperative =  GetSP()->sp_bCooperative && !bSinglePlay;
  const BOOL bScoreMatch  = !GetSP()->sp_bCooperative && !GetSP()->sp_bUseFrags;
  const BOOL bFragMatch   = !GetSP()->sp_bCooperative &&  GetSP()->sp_bUseFrags;
  COLOR colMana, colFrags, colDeaths, colHealth, colArmor;
  COLOR colScore  = _colHUD;
  INDEX iScoreSum = 0;

  // if not in single player mode, we'll have to calc (and maybe printout) other players' info
  if( !bSinglePlay)
  {
    // set font and prepare font parameters
    _pfdDisplayFont->SetVariableWidth();
    _pDP->SetFont(_pfdDisplayFont);

    COLOR colMax = _colHUD;
    COLOR colTop = SE_COL_ORANGE_LIGHT;
    COLOR colMid = LerpColor(colTop, C_RED, 0.5f);
    FLOAT font_scale = 2.0f;
    FLOAT line_height = _pDP->dp_FontData->fd_pixCharHeight * font_scale * 0.7f;
    // generate and sort by mana list of active players
    BOOL bMaxScore=TRUE, bMaxMana=TRUE, bMaxFrags=TRUE, bMaxDeaths=TRUE;
    hud_iSortPlayers = Clamp( hud_iSortPlayers, -1L, 6L);
    SortKeys eKey = (SortKeys)hud_iSortPlayers;
    if (hud_iSortPlayers==-1) {
           if (bCooperative) eKey = PSK_HEALTH;
      else if (bScoreMatch)  eKey = PSK_SCORE;
      else if (bFragMatch)   eKey = PSK_FRAGS;
      else { ASSERT(FALSE);  eKey = PSK_NAME; }
    }
    if( bCooperative) eKey = (SortKeys)Clamp( (INDEX)eKey, 0L, 3L);
    if( eKey==PSK_HEALTH && (bScoreMatch || bFragMatch)) { eKey = PSK_NAME; }; // prevent health snooping in deathmatch
    INDEX iPlayers = SetAllPlayersStats(eKey);
  
    const INDEX iAmmoXPosition = 350;
    INDEX iTimeXPosition = -150;
    if (hud_iShowPlayersList == 1) {

      PlayerStats psSquadLevel;
      {for( INDEX iPlayer=0; iPlayer<iPlayers; iPlayer++) {
        CPlayer *penPlayer = _apenPlayers[iPlayer];
        // add values to squad stats
        ASSERT( penPlayer!=NULL);
        PlayerStats psLevel = penPlayer->m_psLevelStats;
        PlayerStats psGame  = penPlayer->m_psGameStats ;
        psSquadLevel.ps_iScore   += psLevel.ps_iScore   ;
        psSquadLevel.ps_iKills   += psLevel.ps_iKills   ;
        psSquadLevel.ps_iDeaths  += psLevel.ps_iDeaths  ;
        psSquadLevel.ps_iSecrets += psLevel.ps_iSecrets ;
      }}
    
      CTString strGameMode, strGameDifficulty;

      switch (GetSP()->sp_gmGameMode) {
	    case  0: strGameMode = TRANS("Cooperative"); break;
	    case  1: strGameMode = TRANS("Scorematch");  break;
	    case  2: strGameMode = TRANS("Fragmatch");   break;
      }

      switch (GetSP()->sp_gdGameDifficulty) {
	    case -1: strGameDifficulty = TRANS("Tourist"); break;
	    case  0: strGameDifficulty = TRANS("Easy")   ; break;
	    case  1: strGameDifficulty = TRANS("Normal") ; break;
	    case  2: strGameDifficulty = TRANS("Hard")   ; break;
	    case  3: strGameDifficulty = TRANS("Serious"); break;
      }

      const INDEX      iDeaths  = _penPlayer->m_psGameStats.ps_iDeaths;
      CTString strSecrets, strKills, strSessionTime, strDeaths, strCredits, strMaxCredits, strEnemyStrength;
      strKills.PrintF(  "%i / %i", psSquadLevel.ps_iKills,   _penPlayer->m_psLevelTotal.ps_iKills);
      strSecrets.PrintF("%i / %i", psSquadLevel.ps_iSecrets, _penPlayer->m_psLevelTotal.ps_iSecrets);
      strDeaths.PrintF( "%d",  iDeaths);
      strCredits.PrintF("%d / %d", GetSP()->sp_ctCreditsLeft, GetSP()->sp_ctCredits);
      strSessionTime.PrintF("%s", TimeToString(_pNetwork->GetGameTime()));
      strGameMode.PrintF("%s - %s", strGameMode, strGameDifficulty);
      INDEX iEnemyStrengthPercent = 100 + (GetSP()->sp_fExtraEnemyStrength + GetSP()->sp_fExtraEnemyStrengthPerPlayer * _pNetwork->ga_sesSessionState.GetPlayersCount()) * 100;
      strEnemyStrength.PrintF("%i%s", iEnemyStrengthPercent, "%");
    
      // printout location and info aren't the same for deathmatch and coop play
      const FLOAT fCharWidth = (PIX)((_pfdDisplayFont->GetWidth()-2) *fTextScale);
      DIO_DrawBcg( ESP_Middle,    0,                ESP_Middle,    0, ESP_Middle, 1280, ESP_Middle, 900, 0x00000080); // table background
      DIO_DrawBcg( ESP_Middle,    0,                ESP_Middle, -355, ESP_Middle, 1240, ESP_Middle,   4, 0xFFFFFF80); // caption line
      DIO_DrawBcg( ESP_Middle,    0,                ESP_Middle,  360, ESP_Middle, 1240, ESP_Middle,   4, 0xFFFFFF80); // stats line
      DIO_DrawText(ESP_Middle,    0,                ESP_Middle, -400, TranslateConst(_penPlayer->en_pwoWorld->GetName(), 0),    2, ESP_Middle,  C_WHITE); //map name
      if( bFragMatch || bScoreMatch) {
        iTimeXPosition = -350;
      } else { iTimeXPosition = -150;}
      DIO_DrawText(ESP_Middle, iTimeXPosition,      ESP_Middle,  405, TRANS("Time"),  2, ESP_Middle,  C_WHITE); //elapsed time
      DIO_DrawText(ESP_Middle, iTimeXPosition,      ESP_Middle,  440, strSessionTime, 2, ESP_Middle,  C_WHITE);
      DIO_DrawText(ESP_Middle,    0,                ESP_Middle, -365, strGameMode,    2, ESP_Middle, _colHUD);

      DIO_DrawText(ESP_Middle, -570,                ESP_Middle, -315, TRANS("Ping"),        2, ESP_Middle, _colHUD);

      if (bCooperative) {
        DIO_DrawText(ESP_Middle, -310,            ESP_Middle, -315, TRANS("Player"),      2, ESP_Middle, _colHUD); // captions
        DIO_DrawText(ESP_Middle,  -50,            ESP_Middle, -315, TRANS("Health"),      2, ESP_Middle, _colHUD);
        DIO_DrawText(ESP_Middle,   50,            ESP_Middle, -315, TRANS("Armor"),       2, ESP_Middle, _colHUD);

        DIO_DrawText(ESP_Middle,  150,        ESP_Middle, -315, TRANS("Deaths"),      2, ESP_Middle, _colHUD);

        DIO_DrawText(ESP_Middle,  iAmmoXPosition, ESP_Middle, -315, TRANS("Ammo"),        2, ESP_Middle, _colHUD);
        DIO_DrawText(ESP_Middle,  555,            ESP_Middle, -315, TRANS("Distance"),    2, ESP_Middle, _colHUD);
      
        if (GetSP()->sp_bFriendlyFire && GetSP()->sp_bCooperative) {
          DIO_DrawText(ESP_Middle, -500,        ESP_Middle,  405, TRANS("^cff9900Friendly"),   2, ESP_Middle, C_WHITE);
          DIO_DrawText(ESP_Middle, -500,        ESP_Middle,  440, TRANS("^cff9000fire^C"),       2, ESP_Middle, C_WHITE);
        }

        if (iEnemyStrengthPercent > 100) {
          DIO_DrawText(ESP_Middle, -300,        ESP_Middle,  405, TRANS("Enemy strength"),       2, ESP_Middle, C_WHITE);
          DIO_DrawText(ESP_Middle, -300,        ESP_Middle,  440, strEnemyStrength,     2, ESP_Middle, C_WHITE);
        }
        DIO_DrawText(ESP_Middle,    0,            ESP_Middle,  405, TRANS("Kills"),       2, ESP_Middle, C_WHITE); //kills
        DIO_DrawText(ESP_Middle,    0,            ESP_Middle,  440, strKills,             2, ESP_Middle, C_WHITE);
        DIO_DrawText(ESP_Middle,  150,            ESP_Middle,  405, TRANS("Secrets"),     2, ESP_Middle, C_WHITE); //secrets
        DIO_DrawText(ESP_Middle,  150,            ESP_Middle,  440, strSecrets,           2, ESP_Middle, C_WHITE);
        if (bCooperative) {
          DIO_DrawText(ESP_Middle,  300,        ESP_Middle,  405, TRANS("Deaths"),      2, ESP_Middle, C_WHITE); //deaths
          DIO_DrawText(ESP_Middle,  300,        ESP_Middle,  440, strDeaths,            2, ESP_Middle, C_WHITE);}
        if (GetSP()->sp_ctCredits!=-1 && bCooperative) {
          DIO_DrawText(ESP_Middle,  450,        ESP_Middle,  405, TRANS("Credits"),      2, ESP_Middle, C_WHITE); //credits
          if (GetSP()->sp_ctCredits==0) {
          DIO_DrawText(ESP_Middle,  450,        ESP_Middle,  440, TRANS("^cff9900None^C"),      2, ESP_Middle, C_WHITE); //credits
          } else {
          DIO_DrawText(ESP_Middle,  450,        ESP_Middle,  440, strCredits, 2, ESP_Middle, C_WHITE);
          }
        }

      } else if( bScoreMatch) {
        DIO_DrawText(ESP_Middle, -150,            ESP_Middle, -315, TRANS("Player"),      2, ESP_Middle, _colHUD); // captions
        DIO_DrawText(ESP_Middle,  400,            ESP_Middle, -315, TRANS("Score"),       2, ESP_Middle, _colHUD);
        DIO_DrawText(ESP_Middle,  550,            ESP_Middle, -315, TRANS("Value"),       2, ESP_Middle, _colHUD);
      } else { // fragmatch!
        DIO_DrawText(ESP_Middle, -150,            ESP_Middle, -315, TRANS("Player"),      2, ESP_Middle, _colHUD);
        DIO_DrawText(ESP_Middle,  400,            ESP_Middle, -315, TRANS("Frags"),       2, ESP_Middle, _colHUD);
        DIO_DrawText(ESP_Middle,  550,            ESP_Middle, -315, TRANS("Deaths"),      2, ESP_Middle, _colHUD);     
      }
    }

    // loop thru players 
    for( INDEX i=0; i<iPlayers; i++)
    { // get player name and mana
      CPlayer *penPlayer = _apenPlayers[i];
	    if (penPlayer->m_penWeapons == NULL) {continue;}
      FillWeaponAmmoTables(penPlayer);
      const BOOL bCurrentPlayer = (const CPlayer*)(penPlayer->GetPredictionTail()) == _penPlayer;
      const CTString strName = penPlayer->GetPlayerName();
      const INDEX iScore  = penPlayer->m_psGameStats.ps_iScore;
      const INDEX iMana   = penPlayer->m_iMana;
      const INDEX iFrags  = penPlayer->m_psGameStats.ps_iKills;
      const INDEX iDeaths = penPlayer->m_psGameStats.ps_iDeaths;
      const INDEX iHealth = ClampDn( (INDEX)ceil( penPlayer->GetHealth()), 0L);
      const INDEX iArmor  = ClampDn( (INDEX)ceil( penPlayer->m_fArmor),    0L);
      const INDEX iLatency = ceil(penPlayer->en_tmPing*1000.0f);
      CTString strScore, strMana, strFrags, strDeaths, strHealth, strArmor, strLatency, strDistance;
      strScore.PrintF(  "%d", iScore);
      strMana.PrintF(   "%d", iMana);
      strFrags.PrintF(  "%d", iFrags);
      strDeaths.PrintF( "%d", iDeaths);
      strHealth.PrintF( "%d", iHealth);
      strArmor.PrintF(  "%d", iArmor);
	    strLatency.PrintF("%d", iLatency);
      strDistance.PrintF("%d", (INDEX)(_penPlayer->GetPlacement().pl_PositionVector - penPlayer->GetPlacement().pl_PositionVector).Length());
      // detemine corresponding colors
      colHealth = C_mlRED;
      colMana = colScore = colFrags = colDeaths = colArmor = C_lGRAY;
      COLOR colLatency = C_mlRED;
      if( iLatency  <150) {colLatency = _colHUD;} else if (iLatency <300) {colLatency = C_WHITE;}
      if( iMana   > _penPlayer->m_iMana)                      { bMaxMana   = FALSE; colMana   = C_WHITE; }
      if( iScore  > _penPlayer->m_psGameStats.ps_iScore)      { bMaxScore  = FALSE; colScore  = C_WHITE; }
      if( iFrags  > _penPlayer->m_psGameStats.ps_iKills)      { bMaxFrags  = FALSE; colFrags  = C_WHITE; }
      if( iDeaths > _penPlayer->m_psGameStats.ps_iDeaths)     { bMaxDeaths = FALSE; colDeaths = C_WHITE; }
      if( penPlayer==_penPlayer) colScore = colMana = colFrags = colDeaths = _colHUD; // current player
      if( iHealth>25) colHealth = _colHUD;
      if( iArmor >25) colArmor  = _colHUD;
      // eventually print it out
      if( (hud_iShowPlayers==1 || hud_iShowPlayers==-1) && hud_iShowPlayersList != 1) {
        // printout location and info aren't the same for deathmatch and coop play
        if( bCooperative) {
          FLOAT armor_width = DIO_GetTextWidth(strArmor, font_scale);
          FLOAT slash_width = DIO_GetTextWidth("/", font_scale);
          FLOAT health_width = DIO_GetTextWidth(strHealth, font_scale);

          FLOAT slash_offset = -armor_width;
          FLOAT health_offset = -slash_width + slash_offset;
          FLOAT name_offset = - health_width + health_offset;

          DIO_DrawText(ESP_End, -10 + name_offset,   ESP_Start, 20 + (i+1) * line_height, strName + ":", font_scale, ESP_End, _colHUD);
          DIO_DrawText(ESP_End, -10 + health_offset, ESP_Start, 20 + (i+1) * line_height, strHealth,     font_scale, ESP_End, colHealth);
          DIO_DrawText(ESP_End, -10 + slash_offset,  ESP_Start, 20 + (i+1) * line_height, "/",           font_scale, ESP_End, _colHUD);
          DIO_DrawText(ESP_End, -10,                 ESP_Start, 20 + (i+1) * line_height, strArmor,      font_scale, ESP_End, colArmor);
        } else if( bScoreMatch) {
          FLOAT armor_width = DIO_GetTextWidth(strMana, font_scale);
          FLOAT slash_width = DIO_GetTextWidth("/", font_scale);
          FLOAT health_width = DIO_GetTextWidth(strScore, font_scale);

          FLOAT slash_offset = -armor_width;
          FLOAT health_offset = -slash_width + slash_offset;
          FLOAT name_offset = - health_width + health_offset;

          DIO_DrawText(ESP_End, -10 + name_offset,   ESP_Start, 20 + (i+1) * line_height, strName + ":", font_scale, ESP_End, _colHUD);
          DIO_DrawText(ESP_End, -10 + health_offset, ESP_Start, 20 + (i+1) * line_height, strScore,      font_scale, ESP_End, colScore);
          DIO_DrawText(ESP_End, -10 + slash_offset,  ESP_Start, 20 + (i+1) * line_height, "/",           font_scale, ESP_End, _colHUD);
          DIO_DrawText(ESP_End, -10,                 ESP_Start, 20 + (i+1) * line_height, strMana,       font_scale, ESP_End, colMana);
        } else { // fragmatch!
          FLOAT armor_width = DIO_GetTextWidth(strDeaths, font_scale);
          FLOAT slash_width = DIO_GetTextWidth("/", font_scale);
          FLOAT health_width = DIO_GetTextWidth(strFrags, font_scale);

          FLOAT slash_offset = -armor_width;
          FLOAT health_offset = -slash_width + slash_offset;
          FLOAT name_offset = - health_width + health_offset;

          DIO_DrawText(ESP_End, -10 + name_offset,   ESP_Start, 20 + (i+1) * line_height, strName + ":", font_scale, ESP_End, _colHUD);
          DIO_DrawText(ESP_End, -10 + health_offset, ESP_Start, 20 + (i+1) * line_height, strFrags,      font_scale, ESP_End, colFrags);
          DIO_DrawText(ESP_End, -10 + slash_offset,  ESP_Start, 20 + (i+1) * line_height, "/",           font_scale, ESP_End, _colHUD);
          DIO_DrawText(ESP_End, -10,                 ESP_Start, 20 + (i+1) * line_height, strDeaths,     font_scale, ESP_End, colDeaths);
        }
      }
      
      if (hud_iShowPlayersList == 1) {
        const INDEX iListValuePosY    = -275+(40*i);
        const FLOAT fCharWidth = (PIX)((_pfdDisplayFont->GetWidth()-2) *fTextScale);

        INDEX iLineHeight = 40;
        if (bCurrentPlayer)
          DIO_DrawBcg( ESP_Middle, 0, ESP_Middle, -295+(40*i), ESP_Middle, 1240, ESP_Middle, iLineHeight, 0xFFFFFF40);

        if (bCooperative) {
          if (!GetSP()->sp_bInfiniteAmmo) {
            const INDEX iAmmoTypesTotal = 7;
            INDEX iCurrentAmmoTypesCount = 0;

            // count available ammo types for center align
            for( INDEX bb=0; bb<=iAmmoTypesTotal; bb++) {
              // if no ammo and hasn't got that weapon - just skip this ammo
              AmmoInfo &ai = _aaiAmmo[bb];
              if( ai.ai_iAmmoAmmount==0 && !ai.ai_bHasWeapon) continue;

              iCurrentAmmoTypesCount++;
            }
     
            INDEX iAmmoIndex = 0;
            for( INDEX ii=iAmmoTypesTotal; ii>=0; ii--) {
              INDEX iAmmoType = aiAmmoRemap[ii];
              // if no ammo and hasn't got that weapon - just skip this ammo
              AmmoInfo &ai = _aaiAmmo[iAmmoType];
              ASSERT( ai.ai_iAmmoAmmount>=0);
              if( ai.ai_iAmmoAmmount==0 && !ai.ai_bHasWeapon) continue;
              // display ammo info
              colIcon = C_WHITE;
              if( ai.ai_iAmmoAmmount==0) colIcon = C_mdGRAY; else
              if( ptoCurrentAmmo == ai.ai_ptoAmmo) colIcon = C_WHITE; 
              fNormValue = (FLOAT)ai.ai_iAmmoAmmount / ai.ai_iMaxAmmoAmmount;

              CTextureData* ctoAmmo = (CTextureData*)_aaiAmmo[iAmmoType].ai_ptoAmmo->GetData();
              
              const FLOAT fAmmoWidth  = ctoAmmo->GetPixWidth();
              const FLOAT fAmmoHeight = ctoAmmo->GetPixHeight();

              FLOAT fAmmoBarWidth =  fAmmoWidth - (fAmmoWidth/1.25f);
              FLOAT fAmmoBarHeight = fAmmoHeight*fNormValue;

              const float fIndent = 1.15f;

              INDEX iAmmoIconX = iAmmoXPosition - fAmmoWidth/2 + ((iCurrentAmmoTypesCount * fIndent * fAmmoWidth) / 2) - (iAmmoIndex*fAmmoWidth*fIndent);
              INDEX iAmmoIconY = iListValuePosY-(iLineHeight/2);

              PrepareColorTransitions( colMax, colTop, colMid, C_RED, 0.5f, 0.25f, FALSE);
              DIO_DrawIcon(ESP_Middle,  iAmmoIconX, ESP_Middle, iAmmoIconY, *_aaiAmmo[iAmmoType].ai_ptoAmmo, 0, colIcon);
              DIO_DrawBcg( ESP_Middle,  iAmmoIconX + fAmmoWidth/2, ESP_Middle, iAmmoIconY + fAmmoHeight/2.0f, 
              ESP_Middle, fAmmoBarWidth, ESP_Start, -fAmmoBarHeight, GetCurrentColor(fNormValue)|_ulAlphaHUD);  
              
              iAmmoIndex++;
            }
          }
             
          DIO_DrawText(ESP_Middle, -570, ESP_Middle, iListValuePosY, strLatency, 2, ESP_Middle, colLatency |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle, -310, ESP_Middle, iListValuePosY, strName,    2, ESP_Middle, colScore   |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,  -50, ESP_Middle, iListValuePosY, strHealth,  2, ESP_Middle, colHealth  |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,    0, ESP_Middle, iListValuePosY, "/",        2, ESP_Middle, colScore   |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,   50, ESP_Middle, iListValuePosY, strArmor,   2, ESP_Middle, colArmor   |_ulAlphaHUD);
        
          DIO_DrawText(ESP_Middle,  150, ESP_Middle, iListValuePosY, strDeaths,  2, ESP_Middle, colScore   |_ulAlphaHUD);

          if (!bCurrentPlayer) {
            DIO_DrawText(ESP_Middle,  555, ESP_Middle, iListValuePosY, strDistance, 2, ESP_Middle, colScore   |_ulAlphaHUD);
            DIO_DrawIcon(ESP_Middle,  605, ESP_Middle, iListValuePosY-22, _toPointer, GetAngleFromTo(_penPlayer, penPlayer), C_WHITE);
          }
        } else if( bScoreMatch) { 
          DIO_DrawText(ESP_Middle, -570, ESP_Middle, iListValuePosY, strLatency, 2, ESP_Middle, colLatency |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle, -150, ESP_Middle, iListValuePosY, strName,    2, ESP_Middle, _colHUD    |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,  400, ESP_Middle, iListValuePosY, strScore,   2, ESP_Middle, colScore   |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,  475, ESP_Middle, iListValuePosY, "/",        2, ESP_Middle, _colHUD    |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,  550, ESP_Middle, iListValuePosY, strMana,    2, ESP_Middle, colMana    |_ulAlphaHUD);
        } else { // fragmatch!
          DIO_DrawText(ESP_Middle, -570, ESP_Middle, iListValuePosY, strLatency, 2, ESP_Middle, colLatency |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle, -150, ESP_Middle, iListValuePosY, strName,    2, ESP_Middle, _colHUD    |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,  400, ESP_Middle, iListValuePosY, strFrags,   2, ESP_Middle, colFrags   |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,  475, ESP_Middle, iListValuePosY, "/",        2, ESP_Middle, _colHUD    |_ulAlphaHUD);
          DIO_DrawText(ESP_Middle,  550, ESP_Middle, iListValuePosY, strDeaths,  2, ESP_Middle, colDeaths  |_ulAlphaHUD);		 
        }
      }
	
      // calculate summ of scores (for coop mode)
      iScoreSum += iScore;  
    }
    // draw remaining time if time based death- or scorematch
    if ((bScoreMatch || bFragMatch) && hud_bShowMatchInfo){
      CTString strLimitsInfo="";  
      if (GetSP()->sp_iTimeLimit>0) {
        FLOAT fTimeLeft = ClampDn(GetSP()->sp_iTimeLimit*60.0f - _pNetwork->GetGameTime(), 0.0f);
        strLimitsInfo.PrintF("%s^cFFFFFF%s: %s\n", strLimitsInfo, TRANS("TIME LEFT"), TimeToString(fTimeLeft));
        if (hud_iShowPlayersList == 1) {
		      DIO_DrawText(ESP_Middle, 350, ESP_Middle, 405, TRANS("TIME LEFT"),      2, ESP_Middle, C_WHITE);
		      DIO_DrawText(ESP_Middle, 350, ESP_Middle, 440, TimeToString(fTimeLeft), 2, ESP_Middle, C_WHITE);
        }
      }
      extern INDEX SetAllPlayersStats( INDEX iSortKey);
      // fill players table
      const INDEX ctPlayers = SetAllPlayersStats(bFragMatch?5:3); // sort by frags or by score
      // find maximum frags/score that one player has
      INDEX iMaxFrags = LowerLimit(INDEX(0));
      INDEX iMaxScore = LowerLimit(INDEX(0));
      {for(INDEX iPlayer=0; iPlayer<ctPlayers; iPlayer++) {
        CPlayer *penPlayer = _apenPlayers[iPlayer];
        iMaxFrags = Max(iMaxFrags, penPlayer->m_psLevelStats.ps_iKills);
        iMaxScore = Max(iMaxScore, penPlayer->m_psLevelStats.ps_iScore);
      }}
      if (GetSP()->sp_iFragLimit>0) {
        INDEX iFragsLeft = ClampDn(GetSP()->sp_iFragLimit-iMaxFrags, INDEX(0));
        strLimitsInfo.PrintF("%s^cFFFFFF%s: %d\n", strLimitsInfo, TRANS("FRAGS LEFT"), iFragsLeft);
        if (hud_iShowPlayersList == 1) {
          CTString strFragsLeft(0, "%d", ClampDn(GetSP()->sp_iFragLimit-iMaxFrags, INDEX(0)));
			    DIO_DrawText(ESP_Middle, 0, ESP_Middle, 405, TRANS("FRAGS LEFT"),    2, ESP_Middle, C_WHITE);
			    DIO_DrawText(ESP_Middle, 0, ESP_Middle, 440, strFragsLeft,    2, ESP_Middle, C_WHITE);
        }
      }
      if (GetSP()->sp_iScoreLimit>0) {
        INDEX iScoreLeft = ClampDn(GetSP()->sp_iScoreLimit-iMaxScore, INDEX(0));
        strLimitsInfo.PrintF("%s^cFFFFFF%s: %d\n", strLimitsInfo, TRANS("SCORE LEFT"), iScoreLeft);
        if (hud_iShowPlayersList == 1) {
          CTString strScoreLeft(0, "%d", ClampDn(GetSP()->sp_iScoreLimit-iMaxScore, INDEX(0)));
			    DIO_DrawText(ESP_Middle, 0, ESP_Middle, 405, TRANS("SCORE LEFT"),     2, ESP_Middle, C_WHITE);
			    DIO_DrawText(ESP_Middle, 0, ESP_Middle, 440, strScoreLeft, 2, ESP_Middle, C_WHITE);
        }
      }
      _pDP->SetFont( _pfdDisplayFont);
      CTextureData* deaths_data = (CTextureData*)_toDeaths.GetData();
      CTextureData* frags_data = (CTextureData*)_toFrags.GetData();
      DIO_DrawText(ESP_Start, 8, ESP_Start, 16 + deaths_data->GetPixHeight() + frags_data->GetPixHeight() + 40, strLimitsInfo, 2.0f, ESP_Start, C_WHITE | CT_OPAQUE);
    }

    // prepare color for local player printouts
    bMaxScore  ? colScore  = C_WHITE : colScore  = C_lGRAY;
    bMaxMana   ? colMana   = C_WHITE : colMana   = C_lGRAY;
    bMaxFrags  ? colFrags  = C_WHITE : colFrags  = C_lGRAY;
    bMaxDeaths ? colDeaths = C_WHITE : colDeaths = C_lGRAY;
  
  }

  // printout player latency if needed
  if( hud_bShowLatency) {
    CTString strLatency;
    strLatency.PrintF( "%4.0fms", _penPlayer->m_tmLatency*1000.0f);
    FLOAT fTextScale = ((FLOAT)_pixDPWidth /640.0f + 1) * 0.5f;
    PIX pixFontHeight = (PIX)(_pfdDisplayFont->GetHeight() *fTextScale +fTextScale+1);
    _pfdDisplayFont->SetFixedWidth();
    _pDP->SetFont( _pfdDisplayFont);
    _pDP->SetTextScaling( fTextScale);
    _pDP->SetTextCharSpacing( -2.0f*fTextScale);
    _pDP->PutTextR( strLatency, _pixDPWidth, _pixDPHeight-pixFontHeight, C_WHITE|CT_OPAQUE);
    _pfdDisplayFont->SetVariableWidth();
  }


  // restore font defaults
  _pDP->SetFont( &_fdNumbersFont);
  _pDP->SetTextCharSpacing(1);

  // prepare output strings and formats depending on game type
  INDEX iScore = _penPlayer->m_psGameStats.ps_iScore;
  INDEX iMana  = _penPlayer->m_iMana;
  if( bFragMatch) {
    iScore = _penPlayer->m_psGameStats.ps_iKills;
    iMana  = _penPlayer->m_psGameStats.ps_iDeaths;
  } else if( bCooperative) {
    // in case of coop play, show squad (common) score
    iScore = iScoreSum;
  }

  // eventually draw mana info 
  if( bScoreMatch || bFragMatch) {
    // prepare and draw score or frags info 
    CTextureData* frags_data = (CTextureData*)_toFrags.GetData();
    DIO_DrawIcon(ESP_Start, 8 + frags_data->GetPixWidth()*0.5f, ESP_Start, 8 + frags_data->GetPixHeight()*0.5f, _toFrags);
    
    strValue.PrintF( "%d", iScore);
    DIO_DrawText(ESP_Start, 16 + frags_data->GetPixWidth(), ESP_Start, 8 + frags_data->GetPixHeight()*0.5 + 40, strValue, 1.0f, ESP_Start, C_WHITE);

    CTextureData* deaths_data = (CTextureData*)_toDeaths.GetData();
    FLOAT deaths_Y = 8 + deaths_data->GetPixHeight()*0.5f + 8 + frags_data->GetPixHeight();
    DIO_DrawIcon(ESP_Start, 8 + deaths_data->GetPixWidth()*0.5f, ESP_Start, deaths_Y, _toDeaths);

    strValue.PrintF( "%d", iMana);
    DIO_DrawText(ESP_Start, 16 + deaths_data->GetPixWidth(), ESP_Start, deaths_Y + 40, strValue, 1.0f, ESP_Start, C_WHITE);
  }

  // draw cheat modes
  if( GetSP()->sp_ctMaxPlayers==1) {
    INDEX iLine=1;
    ULONG ulAlpha = sin(_tmNow*16)*96 +128;
    PIX pixFontHeight = _pfdConsoleFont->fd_pixCharHeight;
    const COLOR colCheat = _colHUDText;
    _pDP->SetFont( _pfdConsoleFont);
    _pDP->SetTextScaling( 1.0f);
    const FLOAT fchtTM = cht_fTranslationMultiplier; // for text formatting sake :)
    if( fchtTM > 1.0f)  { _pDP->PutTextR( "turbo",     _pixDPWidth-1, _pixDPHeight-pixFontHeight*iLine, colCheat|ulAlpha); iLine++; }
    if( cht_bInvisible) { _pDP->PutTextR( "invisible", _pixDPWidth-1, _pixDPHeight-pixFontHeight*iLine, colCheat|ulAlpha); iLine++; }
    if( cht_bGhost)     { _pDP->PutTextR( "ghost",     _pixDPWidth-1, _pixDPHeight-pixFontHeight*iLine, colCheat|ulAlpha); iLine++; }
    if( cht_bFly)       { _pDP->PutTextR( "fly",       _pixDPWidth-1, _pixDPHeight-pixFontHeight*iLine, colCheat|ulAlpha); iLine++; }
    if( cht_bGod)       { _pDP->PutTextR( "god",       _pixDPWidth-1, _pixDPHeight-pixFontHeight*iLine, colCheat|ulAlpha); iLine++; }
  }

  // in the end, remember the current time so it can be used in the next frame
  _tmLast = _tmNow;
}



// initialize all that's needed for drawing the HUD
extern void InitHUD(void)
{
  // try to
  try {
    // initialize and load HUD numbers font
    DECLARE_CTFILENAME(fnFont, "Fonts\\NumbersDio.fnt");
    _fdNumbersFont.Load_t(fnFont);
    _fdNumbersFont.fd_pixCharSpacing = -6.0f;

    _toWarudoArrow.SetData_t(CTFILENAME("Textures\\HUD\\Warudo_Arrow.tex"));
    _toWarudoBcg.SetData_t(CTFILENAME("Textures\\HUD\\Warudo_Bcg.tex"));
    _toWarudoTimer.SetData_t(CTFILENAME("Textures\\HUD\\Warudo_Timer.tex"));
    _toUltBcg.SetData_t(CTFILENAME("Textures\\HUD\\ult_bcg.tex"));
    _toUltOverlay.SetData_t(CTFILENAME("Textures\\HUD\\ult_overlay.tex"));
    _toFireTexture.SetData_t(CTFILENAME("Textures\\UltimateFire\\UltimateFire.tex"));
    _toUlt.SetData_t(CTFILENAME("Textures\\HUD\\ult.tex"));
    _toUltRodarollada.SetData_t(CTFILENAME("Textures\\HUD\\ult_rodarollada.tex"));
    _toUltFlare.SetData_t(CTFILENAME("Textures\\HUD\\ult_flare.tex"));
    _toWeaponBrace.SetData_t(CTFILENAME("Textures\\HUD\\weapon_brace.tex"));
    _toInfAmmo.SetData_t(CTFILENAME("Textures\\HUD\\no_ammo.tex"));
    _toDIO.SetData_t(CTFILENAME("Textures\\HUD\\DIO.tex"));
    _toZaWarudo.SetData_t(CTFILENAME("Textures\\HUD\\ZaWarudo.tex"));
    _toBarBcg.SetData_t(CTFILENAME("Textures\\HUD\\bar_bcg.tex"));
    _toBar.SetData_t(CTFILENAME("Textures\\HUD\\bar.tex"));
    
    _toMBLeft.SetData_t(CTFILENAME("Textures\\HUD\\Mouse\\lmb.tex"));
    _toMBRight.SetData_t(CTFILENAME("Textures\\HUD\\Mouse\\rmb.tex"));
    _toMB3.SetData_t(CTFILENAME("Textures\\HUD\\Mouse\\mb3.tex"));
    _toMB4.SetData_t(CTFILENAME("Textures\\HUD\\Mouse\\mb4.tex"));
    _toMB5.SetData_t(CTFILENAME("Textures\\HUD\\Mouse\\mb5.tex"));
    _toMWUp.SetData_t(CTFILENAME("Textures\\HUD\\Mouse\\whup.tex"));
    _toMWDown.SetData_t(CTFILENAME("Textures\\HUD\\Mouse\\whdn.tex"));

    _toPointer.SetData_t(CTFILENAME("Textures\\HUD\\Pointer.tex"));
    
    _toAbilityFrame.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\frame.tex"));
    _toAbilityCancel.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\cancel.tex"));
    _toAbilityOverlay.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\overlay.tex"));
    _toAbility_Stand.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\stand.tex"));
    _toAbility_Leg.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\leg.tex"));
    _toAbility_Zoom.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\zoom.tex"));
    _toAbility_Knives.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\knives.tex"));
    _toAbility_Menacing.SetData_t(CTFILENAME("Textures\\HUD\\Abilities\\menacing.tex"));

    // initialize status bar textures
    _toHealth.SetData_t(  CTFILENAME("TexturesMP\\Interface\\HSuper.tex"));
    _toOxygen.SetData_t(  CTFILENAME("Textures\\HUD\\Oxygen.tex"));
    _toFrags.SetData_t(   CTFILENAME("Textures\\HUD\\Score.tex"));
    _toDeaths.SetData_t(  CTFILENAME("Textures\\HUD\\Skull.tex"));
    _toArmorSmall.SetData_t(  CTFILENAME("TexturesMP\\Interface\\ArSmall.tex"));
    _toArmorMedium.SetData_t(   CTFILENAME("TexturesMP\\Interface\\ArMedium.tex"));
    _toArmorLarge.SetData_t(   CTFILENAME("TexturesMP\\Interface\\ArStrong.tex"));

    // initialize ammo textures                    
    _toAShells.SetData_t(        CTFILENAME("TexturesMP\\Interface\\AmShells.tex"));
    _toABullets.SetData_t(       CTFILENAME("TexturesMP\\Interface\\AmBullets.tex"));
    _toARockets.SetData_t(       CTFILENAME("TexturesMP\\Interface\\AmRockets.tex"));
    _toAGrenades.SetData_t(      CTFILENAME("TexturesMP\\Interface\\AmGrenades.tex"));
    _toANapalm.SetData_t(        CTFILENAME("TexturesMP\\Interface\\AmFuelReservoir.tex"));
    _toAElectricity.SetData_t(   CTFILENAME("TexturesMP\\Interface\\AmElectricity.tex"));
    _toAIronBall.SetData_t(      CTFILENAME("TexturesMP\\Interface\\AmCannonBall.tex"));
    _toASniperBullets.SetData_t( CTFILENAME("TexturesMP\\Interface\\AmSniperBullets.tex"));
    _toASeriousBomb.SetData_t(   CTFILENAME("TexturesMP\\Interface\\AmSeriousBomb.tex"));

    // initialize weapon textures
    _toWKnife.SetData_t(           CTFILENAME("Textures\\HUD\\Weapons\\Knife.tex"));
    _toWColt.SetData_t(            CTFILENAME("Textures\\HUD\\Weapons\\Colt.tex"));
    _toWDoubleColt.SetData_t(      CTFILENAME("Textures\\HUD\\Weapons\\DoubleColt.tex"));
    _toWSingleShotgun.SetData_t(   CTFILENAME("Textures\\HUD\\Weapons\\SingleShotgun.tex"));
    _toWDoubleShotgun.SetData_t(   CTFILENAME("Textures\\HUD\\Weapons\\DoubleShotgun.tex"));
    _toWTommygun.SetData_t(        CTFILENAME("Textures\\HUD\\Weapons\\TommyGun.tex"));
    _toWMinigun.SetData_t(         CTFILENAME("Textures\\HUD\\Weapons\\MiniGun.tex"));
    _toWRocketLauncher.SetData_t(  CTFILENAME("Textures\\HUD\\Weapons\\RocketLauncher.tex"));
    _toWGrenadeLauncher.SetData_t( CTFILENAME("Textures\\HUD\\Weapons\\GrenadeLauncher.tex"));
    _toWLaser.SetData_t(           CTFILENAME("Textures\\HUD\\Weapons\\Laser.tex"));
    _toWIronCannon.SetData_t(      CTFILENAME("Textures\\HUD\\Weapons\\Cannon.tex"));
    _toWChainsaw.SetData_t(        CTFILENAME("Textures\\HUD\\Weapons\\Chainsaw.tex"));
    _toWSniper.SetData_t(          CTFILENAME("Textures\\HUD\\Weapons\\Sniper.tex"));
    _toWFlamer.SetData_t(          CTFILENAME("Textures\\HUD\\Weapons\\Flamer.tex"));
    _toWHands.SetData_t(           CTFILENAME("Textures\\HUD\\Weapons\\Hand.tex"));
    _toWSBomb.SetData_t(           CTFILENAME("Textures\\HUD\\Weapons\\SeriousBomb.tex"));
        
    // initialize powerup textures (DO NOT CHANGE ORDER!)
    _atoPowerups[0].SetData_t( CTFILENAME("Textures\\HUD\\Invisibility.tex"));
    _atoPowerups[1].SetData_t( CTFILENAME("Textures\\HUD\\Invulnerability.tex"));
    _atoPowerups[2].SetData_t( CTFILENAME("Textures\\HUD\\SeriousDamage.tex"));
    _atoPowerups[3].SetData_t( CTFILENAME("Textures\\HUD\\SeriousSpeed.tex"));
    // initialize sniper mask texture
    _toSniperMask.SetData_t(       CTFILENAME("TexturesMP\\Interface\\SniperMask.tex"));
    _toSniperWheel.SetData_t(       CTFILENAME("TexturesMP\\Interface\\SniperWheel.tex"));
    _toSniperArrow.SetData_t(       CTFILENAME("TexturesMP\\Interface\\SniperArrow.tex"));
    _toSniperEye.SetData_t(       CTFILENAME("TexturesMP\\Interface\\SniperEye.tex"));
    _toSniperLed.SetData_t(       CTFILENAME("TexturesMP\\Interface\\SniperLed.tex"));

    // initialize tile texture
    _toTile.SetData_t( CTFILENAME("Textures\\Interface\\Tile.tex"));

    ((CTextureData*)_toWarudoTimer.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWarudoArrow.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWarudoBcg.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toUltBcg.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toUltOverlay.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toFireTexture.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toUlt.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toUltFlare.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toUltRodarollada.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWeaponBrace.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toInfAmmo.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toDIO.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toZaWarudo.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toBarBcg.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toBar.GetData())->Force(TEX_CONSTANT);

    ((CTextureData*)_toMBLeft.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMBRight.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMB3.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMB4.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMB5.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMWUp.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMWDown.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toPointer.GetData())->Force(TEX_CONSTANT);

    ((CTextureData*)_toAbilityFrame.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAbilityCancel.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAbilityOverlay.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAbility_Stand.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAbility_Leg.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAbility_Zoom.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAbility_Knives.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAbility_Menacing.GetData())->Force(TEX_CONSTANT);

    // set all textures as constant
    ((CTextureData*)_toHealth .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toOxygen .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toFrags  .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toDeaths .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toArmorSmall.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toArmorMedium.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toArmorLarge.GetData())->Force(TEX_CONSTANT);

    ((CTextureData*)_toAShells       .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toABullets      .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toARockets      .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAGrenades     .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toANapalm       .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAElectricity  .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toAIronBall     .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toASniperBullets.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toASeriousBomb  .GetData())->Force(TEX_CONSTANT);

    ((CTextureData*)_toWKnife          .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWColt           .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWDoubleColt     .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWSingleShotgun  .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWDoubleShotgun  .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWTommygun       .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWRocketLauncher .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWGrenadeLauncher.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWChainsaw       .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWLaser          .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWIronCannon     .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWSniper         .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWMinigun        .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWFlamer         .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWHands          .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWSBomb          .GetData())->Force(TEX_CONSTANT);
    
    ((CTextureData*)_atoPowerups[0].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_atoPowerups[1].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_atoPowerups[2].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_atoPowerups[3].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toTile      .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toSniperMask.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toSniperWheel.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toSniperArrow.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toSniperEye.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toSniperLed.GetData())->Force(TEX_CONSTANT);

    if (!_owFont)
    {
      _owFont = new CFontData();
      _owFont->Load_t(CTFILENAME("Fonts\\ow.fnt"));
      _owFont->SetCharSpacing(-5);
      _owFont->SetLineSpacing(+1);
    }
    
    static Ability_Stand ab_stand[NET_MAXGAMEPLAYERS];
    static Ability_Leg ab_leg[NET_MAXGAMEPLAYERS];
    static Ability_Knives ab_knives[NET_MAXGAMEPLAYERS];
    static Ability_Zoom ab_zoom[NET_MAXGAMEPLAYERS];
    static Ability_Menacing ab_menacing[NET_MAXGAMEPLAYERS];
    for (INDEX i = 0; i < NET_MAXGAMEPLAYERS; ++i)
    {
      abilities[i][0] = &ab_stand[i];
      abilities[i][1] = &ab_menacing[i];
      abilities[i][2] = &ab_leg[i];
      abilities[i][3] = &ab_zoom[i];
      abilities[i][4] = &ab_knives[i];
    }
  }
  catch( char *strError) {
    FatalError( strError);
  }

}

extern void ReinitAbilities(const CPlayer* penPlayer)
{
  INDEX player_index = GetPlayerIndex(penPlayer);
  for (INDEX i = 0; i < 5; ++i)
    if (abilities[player_index][i])
      abilities[player_index][i]->Reinit();
}


// clean up
extern void EndHUD(void)
{
  if (_owFont)
  {
    delete _owFont;
    _owFont = NULL;
  }
}

