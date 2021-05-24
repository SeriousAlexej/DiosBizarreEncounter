 
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
static FLOAT _fCustomScaling;
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
static CTextureObject _toUltFlare;
static CTextureObject _toWeaponBrace;
static CTextureObject _toInfAmmo;
static CTextureObject _toDIO;
static CTextureObject _toZaWarudo;
static CTextureObject _toBarBcg;
static CTextureObject _toBar;

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



// ----------------------- drawing functions

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

static void DIO_DrawIcon
(
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  CTextureObject &toIcon,
  ANGLE angle = 0.0f,
  COLOR color = C_WHITE
)
{
  CTextureData* ptd = (CTextureData*)toIcon.GetData();
  const FLOAT half_width = ptd->GetPixWidth()*0.5f * _dioHUDScaling;
  const FLOAT half_height = ptd->GetPixHeight()*0.5f * _dioHUDScaling;

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
    p0(1), p0(2), 0.0f, 0.0f, color|_ulAlphaHUD,
    p1(1), p1(2), 1.0f, 0.0f, color|_ulAlphaHUD,
    p2(1), p2(2), 1.0f, 1.0f, color|_ulAlphaHUD,
    p3(1), p3(2), 0.0f, 1.0f, color|_ulAlphaHUD
    );

  _pDP->FlushRenderingQueue();
}

static void DIO_DrawIconCircle
(
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  CTextureObject &toIcon,
  FLOAT percentage
)
{
  if (percentage < 0.1f) {
    return;
  }

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
    p0(1), p0(2), p0UV(1), p0UV(2), C_WHITE|_ulAlphaHUD,
    x_pos, y_pos, 0.5f, 0.5f, C_WHITE|_ulAlphaHUD ,
    p1(1), p1(2), p1UV(1), p1UV(2), C_WHITE|_ulAlphaHUD,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), C_WHITE|_ulAlphaHUD   
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
    x_pos, y_pos, 0.5f, 0.5f, C_WHITE|_ulAlphaHUD ,
    p0(1), p0(2), p0UV(1), p0UV(2), C_WHITE|_ulAlphaHUD,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), C_WHITE|_ulAlphaHUD,
    p1(1), p1(2), p1UV(1), p1UV(2), C_WHITE|_ulAlphaHUD
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
    x_pos, y_pos, 0.5f, 0.5f, C_WHITE|_ulAlphaHUD ,
    p0(1), p0(2), p0UV(1), p0UV(2), C_WHITE|_ulAlphaHUD,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), C_WHITE|_ulAlphaHUD,
    p1(1), p1(2), p1UV(1), p1UV(2), C_WHITE|_ulAlphaHUD
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
    x_pos, y_pos, 0.5f, 0.5f, C_WHITE|_ulAlphaHUD ,
    p0(1), p0(2), p0UV(1), p0UV(2), C_WHITE|_ulAlphaHUD,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), C_WHITE|_ulAlphaHUD,
    p1(1), p1(2), p1UV(1), p1UV(2), C_WHITE|_ulAlphaHUD
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
    x_pos, y_pos, 0.5f, 0.5f, C_WHITE|_ulAlphaHUD ,
    p0(1), p0(2), p0UV(1), p0UV(2), C_WHITE|_ulAlphaHUD,
    pinterp(1), pinterp(2), pinterpUV(1), pinterpUV(2), C_WHITE|_ulAlphaHUD,
    p1(1), p1(2), p1UV(1), p1UV(2), C_WHITE|_ulAlphaHUD
    );
}
}
}
}

  _pDP->FlushRenderingQueue();
}

static void DIO_DrawText
(
  EScreenPos x_anchor, INDEX x_offset,
  EScreenPos y_anchor, INDEX y_offset,
  const CTString &strText,
  FLOAT textScale,
  EScreenPos text_alignment,
  COLOR col
)
{
  _pDP->SetTextCharSpacing(textScale * _dioHUDScaling * _pDP->dp_FontData->fd_pixCharSpacing);
  _pDP->SetTextScaling(textScale * _dioHUDScaling);

  FLOAT text_width = _pDP->GetTextWidth(strText);
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

  _pDP->PutText(strText, x_pos, y_pos, col|_ulAlphaHUD);
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
static void HUD_DrawSniperMask( void )
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

  FLOAT fDistance = _penWeapons->m_fRayHitDistance;
  FLOAT aFOV = Lerp(_penWeapons->m_fSniperFOVlast, _penWeapons->m_fSniperFOV,
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
  if (_penWeapons->m_tmLastSniperFire+1.25f<fTM) { // blinking
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
static void FillWeaponAmmoTables(void)
{
  // ammo quantities
  _aaiAmmo[0].ai_iAmmoAmmount    = _penWeapons->m_iShells;
  _aaiAmmo[0].ai_iMaxAmmoAmmount = _penWeapons->m_iMaxShells;
  _aaiAmmo[1].ai_iAmmoAmmount    = _penWeapons->m_iBullets;
  _aaiAmmo[1].ai_iMaxAmmoAmmount = _penWeapons->m_iMaxBullets;
  _aaiAmmo[2].ai_iAmmoAmmount    = _penWeapons->m_iRockets;
  _aaiAmmo[2].ai_iMaxAmmoAmmount = _penWeapons->m_iMaxRockets;
  _aaiAmmo[3].ai_iAmmoAmmount    = _penWeapons->m_iGrenades;
  _aaiAmmo[3].ai_iMaxAmmoAmmount = _penWeapons->m_iMaxGrenades;
  _aaiAmmo[4].ai_iAmmoAmmount    = _penWeapons->m_iNapalm;
  _aaiAmmo[4].ai_iMaxAmmoAmmount = _penWeapons->m_iMaxNapalm;
  _aaiAmmo[5].ai_iAmmoAmmount    = _penWeapons->m_iElectricity;
  _aaiAmmo[5].ai_iMaxAmmoAmmount = _penWeapons->m_iMaxElectricity;
  _aaiAmmo[6].ai_iAmmoAmmount    = _penWeapons->m_iIronBalls;
  _aaiAmmo[6].ai_iMaxAmmoAmmount = _penWeapons->m_iMaxIronBalls;
  _aaiAmmo[7].ai_iAmmoAmmount    = _penWeapons->m_iSniperBullets;
  _aaiAmmo[7].ai_iMaxAmmoAmmount = _penWeapons->m_iMaxSniperBullets;

  // prepare ammo table for weapon possesion
  INDEX i, iAvailableWeapons = _penWeapons->m_iAvailableWeapons;
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
}

void HUD_SetEntityForStackDisplay(CRationalEntity *pren)
{
}

CTString GetButtonName(const CPlayer* player, const char* title)
{
  if (player && player->mp_buttonActionsListHead)
  {
    FOREACHINLIST(CButtonAction, ba_lnNode, *player->mp_buttonActionsListHead, itButtonAction)
    {
      if (itButtonAction->ba_strName == title)
      {
        if (itButtonAction->ba_iFirstKey != KID_NONE)
          return _pInput->GetButtonTransName(itButtonAction->ba_iFirstKey);
        else if (itButtonAction->ba_iSecondKey != KID_NONE)
          return _pInput->GetButtonTransName(itButtonAction->ba_iSecondKey);

        break;
      }
    }
  }
  return "";
}

// render interface (frontend) to drawport
// (units are in pixels for 640x480 resolution - for other res HUD will be scalled automatically)
extern void DrawHUD( const CPlayer *penPlayerCurrent, CDrawPort *pdpCurrent, BOOL bSnooping, const CPlayer *penPlayerOwner)
{
  // no player - no info, sorry
  if( penPlayerCurrent==NULL || (penPlayerCurrent->GetFlags()&ENF_DELETED)) return;
  
  // if snooping and owner player ins NULL, return
  if ( bSnooping && penPlayerOwner==NULL) return;

  // find last values in case of predictor
  CPlayer *penLast = (CPlayer*)penPlayerCurrent;
  if( penPlayerCurrent->IsPredictor()) penLast = (CPlayer*)(((CPlayer*)penPlayerCurrent)->GetPredicted());
  ASSERT( penLast!=NULL);
  if( penLast==NULL) return; // !!!! just in case

  // cache local variables
  hud_fOpacity = Clamp( hud_fOpacity, 0.1f, 1.0f);
  hud_fScaling = Clamp( hud_fScaling, 0.5f, 1.2f);
  _penPlayer  = penPlayerCurrent;
  _penWeapons = (CPlayerWeapons*)&*_penPlayer->m_penWeapons;
  _pDP        = pdpCurrent;
  _pixDPWidth   = _pDP->GetWidth();
  _pixDPHeight  = _pDP->GetHeight();
  _fCustomScaling     = hud_fScaling;
  _fResolutionScaling = (FLOAT)_pixDPWidth /640.0f;
  _colHUD     = 0x4C80BB00;
  _colHUDText = SE_COL_ORANGE_LIGHT;
  _ulAlphaHUD = NormFloatToByte(hud_fOpacity);
  _tmNow = _pTimer->CurrentTick();

  _dioHUDScaling = _pixDPHeight / 1080.0f;

  // determine hud colorization;
  COLOR colMax = SE_COL_BLUEGREEN_LT;
  COLOR colTop = SE_COL_ORANGE_LIGHT;
  COLOR colMid = LerpColor(colTop, C_RED, 0.5f);

  // adjust borders color in case of spying mode
  COLOR colBorder = _colHUD; 
  
  if( bSnooping) {
    colBorder = SE_COL_ORANGE_NEUTRAL;
    if( ((ULONG)(_tmNow*5))&1) {
      //colBorder = (colBorder>>1) & 0x7F7F7F00; // darken flash and scale
      colBorder = SE_COL_ORANGE_DARK;
      _fCustomScaling *= 0.933f;
    }
  }

  // draw sniper mask (original mask even if snooping)
  if (((CPlayerWeapons*)&*penPlayerOwner->m_penWeapons)->m_iCurrentWeapon==WEAPON_SNIPER
    &&((CPlayerWeapons*)&*penPlayerOwner->m_penWeapons)->m_bSniping) {
    HUD_DrawSniperMask();
  } 

  CTextureObject* p_portrait = &_toDIO;
  if (_penPlayer->m_mode == STAND_ENGAGED)
    p_portrait = &_toZaWarudo;
  DIO_DrawIcon(ESP_Start, 187, ESP_End, -135, *p_portrait);
   
  // prepare font and text dimensions
  CTString strValue;
  PIX pixCharWidth;
  FLOAT fValue, fNormValue, fCol, fRow;
  _pDP->SetFont( &_fdNumbersFont);
  pixCharWidth = _fdNumbersFont.GetWidth() + _fdNumbersFont.GetCharSpacing() +1;
  FLOAT fChrUnit = pixCharWidth * _fCustomScaling;

  const PIX pixTopBound    = 6;
  const PIX pixLeftBound   = 6;
  const PIX pixBottomBound = (480 * _pDP->dp_fWideAdjustment) -pixTopBound;
  const PIX pixRightBound  = 640-pixLeftBound;
  FLOAT fOneUnit  = (32+0) * _fCustomScaling;  // unit size
  FLOAT fAdvUnit  = (32+4) * _fCustomScaling;  // unit advancer
  FLOAT fNextUnit = (32+8) * _fCustomScaling;  // unit advancer
  FLOAT fHalfUnit = fOneUnit * 0.5f;
  
  // prepare and draw health info
  fValue = ClampDn( _penPlayer->GetHealth(), 0.0f);  // never show negative health

/*
HEALTH
*/
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

  //DIO_DrawIcon(ESP_Middle, 0, ESP_End, -120 - 32, _toFireTexture);
  //DIO_DrawIcon(ESP_Middle, 0, ESP_End, -90 - 32, _toUltFlare, _pTimer->CurrentTick()*45.0f*PI/180.0f);
  //DIO_DrawIcon(ESP_Middle, 0, ESP_End, -90 - 32, _toUlt);

  DIO_DrawIcon(ESP_Middle, 0, ESP_End, -90 - 32, _toUltBcg);
  DIO_DrawIconCircle(ESP_Middle, 0, ESP_End, -90 - 32, _toUltOverlay, int(_pTimer->CurrentTick()) % 100);
  strValue.PrintF("%d", int(_pTimer->CurrentTick()) % 100);
  DIO_DrawText(ESP_Middle, -4, ESP_End, -53 -32, strValue, 1.0f, ESP_Middle, C_WHITE);

  CTString ultimate_button = GetButtonName(_penPlayer, "Ultimate");
  if (ultimate_button != "")
  {
    _pDP->SetFont(_pfdDisplayFont);
    DIO_DrawText(ESP_Middle, 0, ESP_End, -20, ultimate_button, 1.0f, ESP_Middle, C_WHITE);
    _pDP->SetFont(&_fdNumbersFont);
  }




  /*
  CURRENT WEAPON DRAWING
  */



  // prepare and draw ammo and weapon info
  CTextureObject *ptoCurrentAmmo=NULL, *ptoCurrentWeapon=NULL, *ptoWantedWeapon=NULL;
  INDEX iCurrentWeapon = _penWeapons->m_iCurrentWeapon;
  INDEX iWantedWeapon  = _penWeapons->m_iWantedWeapon;
  // determine corresponding ammo and weapon texture component
  ptoCurrentWeapon = _awiWeapons[iCurrentWeapon].wi_ptoWeapon;
  ptoWantedWeapon  = _awiWeapons[iWantedWeapon].wi_ptoWeapon;


  if (ptoCurrentWeapon)
  {
    DIO_DrawIcon(ESP_End, -72, ESP_End, -121, _toWeaponBrace);

    AmmoInfo *paiCurrent = _awiWeapons[iCurrentWeapon].wi_paiAmmo;
    if (paiCurrent!=NULL)
      ptoCurrentAmmo = paiCurrent->ai_ptoAmmo;

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

  // display all ammo infos
  INDEX i;
  COLOR colIcon;
  // reduce the size of icon slightly
  _fCustomScaling = ClampDn( _fCustomScaling*0.8f, 0.5f);
  const FLOAT fOneUnitS  = fOneUnit  *0.8f;
  const FLOAT fAdvUnitS  = fAdvUnit  *0.8f;
  const FLOAT fNextUnitS = fNextUnit *0.8f;
  const FLOAT fHalfUnitS = fHalfUnit *0.8f;

  // prepare postition and ammo quantities
  fRow = pixBottomBound-fHalfUnitS;
  fCol = pixRightBound -fHalfUnitS;
  const FLOAT fBarPos = fHalfUnitS*0.7f;
  FillWeaponAmmoTables();

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
  _fCustomScaling = hud_fScaling;
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



  /*
  // reduce icon sizes a bit
  const FLOAT fUpperSize = ClampDn(_fCustomScaling*0.5f, 0.5f)/_fCustomScaling;
  _fCustomScaling*=fUpperSize;
  ASSERT( _fCustomScaling>=0.5f);
  fChrUnit  *= fUpperSize;
  fOneUnit  *= fUpperSize;
  fHalfUnit *= fUpperSize;
  fAdvUnit  *= fUpperSize;
  fNextUnit *= fUpperSize;
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

    FLOAT font_scale = 3.0f;
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

    // loop thru players 
    for( INDEX i=0; i<iPlayers; i++)
    { // get player name and mana
      CPlayer *penPlayer = _apenPlayers[i];
      const CTString strName = penPlayer->GetPlayerName();
      const INDEX iScore  = penPlayer->m_psGameStats.ps_iScore;
      const INDEX iMana   = penPlayer->m_iMana;
      const INDEX iFrags  = penPlayer->m_psGameStats.ps_iKills;
      const INDEX iDeaths = penPlayer->m_psGameStats.ps_iDeaths;
      const INDEX iHealth = ClampDn( (INDEX)ceil( penPlayer->GetHealth()), 0L);
      const INDEX iArmor  = ClampDn( (INDEX)ceil( penPlayer->m_fArmor),    0L);
      CTString strScore, strMana, strFrags, strDeaths, strHealth, strArmor;
      strScore.PrintF(  "%d", iScore);
      strMana.PrintF(   "%d", iMana);
      strFrags.PrintF(  "%d", iFrags);
      strDeaths.PrintF( "%d", iDeaths);
      strHealth.PrintF( "%d", iHealth);
      strArmor.PrintF(  "%d", iArmor);
      // detemine corresponding colors
      colHealth = C_mlRED;
      colMana = colScore = colFrags = colDeaths = colArmor = C_lGRAY;
      if( iMana   > _penPlayer->m_iMana)                      { bMaxMana   = FALSE; colMana   = C_WHITE; }
      if( iScore  > _penPlayer->m_psGameStats.ps_iScore)      { bMaxScore  = FALSE; colScore  = C_WHITE; }
      if( iFrags  > _penPlayer->m_psGameStats.ps_iKills)      { bMaxFrags  = FALSE; colFrags  = C_WHITE; }
      if( iDeaths > _penPlayer->m_psGameStats.ps_iDeaths)     { bMaxDeaths = FALSE; colDeaths = C_WHITE; }
      if( penPlayer==_penPlayer) colScore = colMana = colFrags = colDeaths = _colHUD; // current player
      if( iHealth>25) colHealth = _colHUD;
      if( iArmor >25) colArmor  = _colHUD;
      // eventually print it out
      if( hud_iShowPlayers==1 || hud_iShowPlayers==-1 && !bSinglePlay) {
        // printout location and info aren't the same for deathmatch and coop play
        const FLOAT fCharWidth = (PIX)((_pfdDisplayFont->GetWidth()-2) *fTextScale);
        if( bCooperative) {
          DIO_DrawText(ESP_End, -100, ESP_Start, 20 + (i+1) * line_height, strName + ":", font_scale, ESP_End, colScore);
          DIO_DrawText(ESP_End, -53, ESP_Start, 20 + (i+1) * line_height, strHealth,      font_scale, ESP_End, colHealth);
          DIO_DrawText(ESP_End, -50, ESP_Start, 20 + (i+1) * line_height, "/",            font_scale, ESP_Middle, _colHUD);
          DIO_DrawText(ESP_End, -47, ESP_Start, 20 + (i+1) * line_height, strArmor,       font_scale, ESP_Start, colArmor);
        } else if( bScoreMatch) { 
          _pDP->PutTextR( strName+":", _pixDPWidth-12*fCharWidth, line_height*i+fOneUnit*2, _colHUD |_ulAlphaHUD);
          _pDP->PutText(  "/",         _pixDPWidth- 5*fCharWidth, line_height*i+fOneUnit*2, _colHUD |_ulAlphaHUD);
          _pDP->PutTextC( strScore,    _pixDPWidth- 8*fCharWidth, line_height*i+fOneUnit*2, colScore|_ulAlphaHUD);
          _pDP->PutTextC( strMana,     _pixDPWidth- 2*fCharWidth, line_height*i+fOneUnit*2, colMana |_ulAlphaHUD);
        } else { // fragmatch!
          _pDP->PutTextR( strName+":", _pixDPWidth-8*fCharWidth, line_height*i+fOneUnit*2, _colHUD  |_ulAlphaHUD);
          _pDP->PutText(  "/",         _pixDPWidth-4*fCharWidth, line_height*i+fOneUnit*2, _colHUD  |_ulAlphaHUD);
          _pDP->PutTextC( strFrags,    _pixDPWidth-6*fCharWidth, line_height*i+fOneUnit*2, colFrags |_ulAlphaHUD);
          _pDP->PutTextC( strDeaths,   _pixDPWidth-2*fCharWidth, line_height*i+fOneUnit*2, colDeaths|_ulAlphaHUD);
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
      }
      if (GetSP()->sp_iScoreLimit>0) {
        INDEX iScoreLeft = ClampDn(GetSP()->sp_iScoreLimit-iMaxScore, INDEX(0));
        strLimitsInfo.PrintF("%s^cFFFFFF%s: %d\n", strLimitsInfo, TRANS("SCORE LEFT"), iScoreLeft);
      }
      _pfdDisplayFont->SetFixedWidth();
      _pDP->SetFont( _pfdDisplayFont);
      _pDP->SetTextScaling( fTextScale*0.8f );
      _pDP->SetTextCharSpacing( -2.0f*fTextScale);
      _pDP->PutText( strLimitsInfo, 5.0f*_pixDPWidth/640.0f, 48.0f*_pixDPWidth/640.0f, C_WHITE|CT_OPAQUE);
    }
        

    // prepare color for local player printouts
    bMaxScore  ? colScore  = C_WHITE : colScore  = C_lGRAY;
    bMaxMana   ? colMana   = C_WHITE : colMana   = C_lGRAY;
    bMaxFrags  ? colFrags  = C_WHITE : colFrags  = C_lGRAY;
    bMaxDeaths ? colDeaths = C_WHITE : colDeaths = C_lGRAY;
  }
  */

/*
  // printout player latency if needed
  if( hud_bShowLatency) {
    CTString strLatency;
    strLatency.PrintF( "%4.0fms", _penPlayer->m_tmLatency*1000.0f);
    PIX pixFontHeight = (PIX)(_pfdDisplayFont->GetHeight() *fTextScale +fTextScale+1);
    _pfdDisplayFont->SetFixedWidth();
    _pDP->SetFont( _pfdDisplayFont);
    _pDP->SetTextScaling( fTextScale);
    _pDP->SetTextCharSpacing( -2.0f*fTextScale);
    _pDP->PutTextR( strLatency, _pixDPWidth, _pixDPHeight-pixFontHeight, C_WHITE|CT_OPAQUE);
  }
  */

/*
  // restore font defaults
  _pfdDisplayFont->SetVariableWidth();
  _pDP->SetFont( &_fdNumbersFont);
  _pDP->SetTextCharSpacing(1);

  // prepare output strings and formats depending on game type
  FLOAT fWidthAdj = 8;
  INDEX iScore = _penPlayer->m_psGameStats.ps_iScore;
  INDEX iMana  = _penPlayer->m_iMana;
  if( bFragMatch) {
    if (!hud_bShowMatchInfo) { fWidthAdj = 4; }
    iScore = _penPlayer->m_psGameStats.ps_iKills;
    iMana  = _penPlayer->m_psGameStats.ps_iDeaths;
  } else if( bCooperative) {
    // in case of coop play, show squad (common) score
    iScore = iScoreSum;
  }

  // eventually draw mana info 
  if( bScoreMatch || bFragMatch) {
    // prepare and draw score or frags info 
    strValue.PrintF( "%d", iScore);
    fRow = pixTopBound  +fHalfUnit;
    fCol = pixLeftBound +fHalfUnit;
    fAdv = fAdvUnit+ fChrUnit*fWidthAdj/2 -fHalfUnit;
    HUD_DrawText(   fCol+fAdv, fRow, strValue, colScore, 1.0f);
    HUD_DrawIcon(   fCol,      fRow, _toFrags, C_WHITE, 1.0f, FALSE);

    strValue.PrintF( "%d", iMana);
    fRow = pixTopBound  + fNextUnit+fHalfUnit;
    fCol = pixLeftBound + fHalfUnit;
    fAdv = fAdvUnit+ fChrUnit*fWidthAdj/2 -fHalfUnit;
    HUD_DrawText(   fCol+fAdv, fRow, strValue,  colMana, 1.0f);
    HUD_DrawIcon(   fCol,      fRow, _toDeaths, C_WHITE, 1.0f, FALSE);
  }
  */
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

    _toUltBcg.SetData_t(CTFILENAME("Textures\\HUD\\ult_bcg.tex"));
    _toUltOverlay.SetData_t(CTFILENAME("Textures\\HUD\\ult_overlay.tex"));
    _toFireTexture.SetData_t(CTFILENAME("Textures\\UltimateFire\\UltimateFire.tex"));
    _toUlt.SetData_t(CTFILENAME("Textures\\HUD\\ult.tex"));
    _toUltFlare.SetData_t(CTFILENAME("Textures\\HUD\\ult_flare.tex"));
    _toWeaponBrace.SetData_t(CTFILENAME("Textures\\HUD\\weapon_brace.tex"));
    _toInfAmmo.SetData_t(CTFILENAME("Textures\\HUD\\no_ammo.tex"));
    _toDIO.SetData_t(CTFILENAME("Textures\\HUD\\DIO.tex"));
    _toZaWarudo.SetData_t(CTFILENAME("Textures\\HUD\\ZaWarudo.tex"));
    _toBarBcg.SetData_t(CTFILENAME("Textures\\HUD\\bar_bcg.tex"));
    _toBar.SetData_t(CTFILENAME("Textures\\HUD\\bar.tex"));

    // initialize status bar textures
    _toHealth.SetData_t(  CTFILENAME("TexturesMP\\Interface\\HSuper.tex"));
    _toOxygen.SetData_t(  CTFILENAME("Textures\\HUD\\Oxygen.tex"));
    _toFrags.SetData_t(   CTFILENAME("TexturesMP\\Interface\\IBead.tex"));
    _toDeaths.SetData_t(  CTFILENAME("TexturesMP\\Interface\\ISkull.tex"));
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

    ((CTextureData*)_toUltBcg.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toUltOverlay.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toFireTexture.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toUlt.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toUltFlare.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toWeaponBrace.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toInfAmmo.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toDIO.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toZaWarudo.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toBarBcg.GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toBar.GetData())->Force(TEX_CONSTANT);

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

  }
  catch( char *strError) {
    FatalError( strError);
  }

}


// clean up
extern void EndHUD(void)
{

}

