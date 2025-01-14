//-------------------------------------------------------------------------
/*
Copyright (C) 2010-2019 EDuke32 developers and contributors
Copyright (C) 2019 Nuke.YKT

This file is part of NBlood.

NBlood is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------
#pragma once

#include "palette.h"
#include "common_game.h"
#include "controls.h"
#include "messages.h"
#include "player.h"

enum VIEW_EFFECT {
    VIEW_EFFECT_0 = 0,
    VIEW_EFFECT_1,
    VIEW_EFFECT_2,
    VIEW_EFFECT_3,
    VIEW_EFFECT_4,
    VIEW_EFFECT_5,
    VIEW_EFFECT_6,
    VIEW_EFFECT_7,
    VIEW_EFFECT_8,
    VIEW_EFFECT_9,
    VIEW_EFFECT_10,
    VIEW_EFFECT_11,
    VIEW_EFFECT_12,
    VIEW_EFFECT_13,
    VIEW_EFFECT_14,
    VIEW_EFFECT_15,
    VIEW_EFFECT_16,
    VIEW_EFFECT_17,
    VIEW_EFFECT_18,
};

enum VIEWPOS {
    VIEWPOS_0 = 0,
    VIEWPOS_1
};

enum INTERPOLATE_TYPE {
    INTERPOLATE_TYPE_INT = 0,
    INTERPOLATE_TYPE_SHORT,
};

#define CROSSHAIR_PAL (MAXPALOOKUPS-RESERVEDPALS-1)
#define kCrosshairTile 2319
#define kLoadScreen 2049
#define kLoadScreenCRC -2051908571
#define kLoadScreenWideBackWidth 256
#define kLoadScreenWideSideWidth 128
#define kLoadScreenWideBack 9216
#define kLoadScreenWideLeft 9217
#define kLoadScreenWideRight 9218
#define kLoadScreenWideMiddle 9219

struct FONT {
    int tile, xSize, ySize, space;
};

extern int gZoom;
extern FONT gFont[5];
extern int gViewMode;
extern VIEWPOS gViewPos;
extern int gViewIndex;
extern int gScreenTilt;
extern int deliriumTilt, deliriumTurn, deliriumPitch;
extern int gScreenTiltO, deliriumTurnO, deliriumPitchO;
extern int gShowFrameRate;
extern char gInterpolateSprite[512];
extern char gInterpolateWall[1024];
extern char gInterpolateSector[128];
extern LOCATION gPrevSpriteLoc[kMaxSprites];
extern int gViewSize;
extern CGameMessageMgr gGameMessageMgr;
extern int gViewXCenter, gViewYCenter;
extern int gViewX0, gViewY0, gViewX1, gViewY1;
extern int gViewX0S, gViewY0S, gViewX1S, gViewY1S;
extern palette_t CrosshairColors;
extern palette_t DefaultCrosshairColors;
extern int32_t g_crosshairSum;
extern int32_t r_maxfps;
extern int32_t r_maxfpsoffset;
extern double g_frameDelay;
extern float r_ambientlight, r_ambientlightrecip;
extern int gLastPal;
extern int32_t gShowFps, gFramePeriod;


static inline double calcFrameDelay(int maxFPS) { return maxFPS ? ((double)timerGetFreqU64() / (double)(maxFPS)) : 0.0; }

void viewGetFontInfo(int id, const char *unk1, int *pXSize, int *pYSize);
void viewUpdatePages(void);
void viewToggle(int viewMode);
void viewInitializePrediction(void);
void viewUpdatePrediction(GINPUT *pInput);
void sub_158B4(PLAYER *pPlayer);
void fakeProcessInput(PLAYER *pPlayer, GINPUT *pInput);
void fakePlayerProcess(PLAYER *pPlayer, GINPUT *pInput);
void fakeMoveDude(spritetype *pSprite);
void fakeActAirDrag(spritetype *pSprite, int num);
void fakeActProcessSprites(void);
void viewCorrectPrediction(void);
void viewBackupView(int nPlayer);
void viewClearInterpolations(void);
void viewAddInterpolation(void *data, INTERPOLATE_TYPE type);
void CalcInterpolations(void);
void RestoreInterpolations(void);
void viewDrawText(int nFont, const char *pString, int x, int y, int nShade, int nPalette, int position, char shadow, unsigned int nStat = 0);
void viewTileSprite(int nTile, int nShade, int nPalette, int x1, int y1, int x2, int y2);
void InitStatusBar(void);
void DrawStatSprite(int nTile, int x, int y, int nShade = 0, int nPalette = 0, unsigned int nStat = 0, int nScale = 65536);
void DrawStatMaskedSprite(int nTile, int x, int y, int nShade = 0, int nPalette = 0, unsigned int nStat = 0, int nScale = 65536);
void DrawStatNumber(const char *pFormat, int nNumber, int nTile, int x, int y, int nShade, int nPalette, unsigned int nStat = 0, int nScale = 65536);
void TileHGauge(int nTile, int x, int y, int nMult, int nDiv, int nStat = 0, int nScale = 65536);
void viewDrawPack(PLAYER *pPlayer, int x, int y);
void DrawPackItemInStatusBar(PLAYER *pPlayer, int x, int y, int x2, int y2, int nStat = 0);
void UpdateStatusBar(int arg);
void viewInit(void);
void viewResizeView(int size);
void UpdateFrame(void);
void viewDrawInterface(int arg);
uspritetype *viewInsertTSprite(int nSector, int nStatnum, uspritetype *pSprite);
uspritetype *viewAddEffect(int nTSprite, VIEW_EFFECT nViewEffect);
void viewProcessSprites(int cX, int cY, int cZ);
void CalcOtherPosition(spritetype *pSprite, int *pX, int *pY, int *pZ, int *vsectnum, int nAng, int zm);
void CalcPosition(spritetype *pSprite, int *pX, int *pY, int *pZ, int *vsectnum, int nAng, int zm);
void viewSetMessage(const char *pMessage);
void viewDisplayMessage(void);
void viewSetErrorMessage(const char *pMessage);
void DoLensEffect(void);
void UpdateDacs(int nPalette, bool bNoTint = false);
int viewFPSLimit(void);
void viewDrawScreen(void);
void viewLoadingScreenWide(void);
void viewLoadingScreenUpdate(const char *pzText4 = NULL, int nPercent = -1);
void viewLoadingScreen(int nTile, const char *pText, const char *pText2, const char *pText3);
void viewUpdateDelirium(void);
void viewUpdateShake(void);
void viewGetCrosshairColor(void);
void viewSetCrosshairColor(int32_t r, int32_t g, int32_t b);
void viewPrintFPS(void);


inline void viewInterpolateSector(int nSector, sectortype *pSector)
{
    if (!TestBitString(gInterpolateSector, nSector))
    {
        viewAddInterpolation(&pSector->floorz, INTERPOLATE_TYPE_INT);
        viewAddInterpolation(&pSector->ceilingz, INTERPOLATE_TYPE_INT);
        viewAddInterpolation(&pSector->floorheinum, INTERPOLATE_TYPE_SHORT);
        SetBitString(gInterpolateSector, nSector);
    }
}

inline void viewInterpolateWall(int nWall, walltype *pWall)
{
    if (!TestBitString(gInterpolateWall, nWall))
    {
        viewAddInterpolation(&pWall->x, INTERPOLATE_TYPE_INT);
        viewAddInterpolation(&pWall->y, INTERPOLATE_TYPE_INT);
        SetBitString(gInterpolateWall, nWall);
    }
}

inline void viewBackupSpriteLoc(int nSprite, spritetype *pSprite)
{
    if (!TestBitString(gInterpolateSprite, nSprite))
    {
        LOCATION *pPrevLoc = &gPrevSpriteLoc[nSprite];
        pPrevLoc->x = pSprite->x;
        pPrevLoc->y = pSprite->y;
        pPrevLoc->z = pSprite->z;
        pPrevLoc->ang = pSprite->ang;
        SetBitString(gInterpolateSprite, nSprite);
    }
}
