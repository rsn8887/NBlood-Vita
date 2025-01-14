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
#include "build.h"
#include "compat.h"
#include "common_game.h"
#include "qav.h"
#include "tile.h"

#define kMaxClients 64
static void (*clientCallback[kMaxClients])(int, void *);
static int nClients;


int qavRegisterClient(void(*pClient)(int, void *))
{
    dassert(nClients < kMaxClients);
    clientCallback[nClients] = pClient;

    return nClients++;
}

void DrawFrame(int x, int y, TILE_FRAME *pTile, int stat, int shade, int palnum)
{
    stat |= pTile->stat;
    int angle = pTile->angle;
    if (stat & 0x100)
    {
        angle = (angle+1024)&2047;
        stat &= ~0x100;
        stat ^= 0x4;
    }
    if (stat & kQavOrientationLeft)
    {
        stat &= ~kQavOrientationLeft;
        stat |= 256;
    }
    if (palnum <= 0)
        palnum = pTile->palnum;
    rotatesprite((x + pTile->x) << 16, (y + pTile->y) << 16, pTile->z, angle,
                 pTile->picnum, ClipRange(pTile->shade + shade, -128, 127), palnum, stat,
                 windowxy1.x, windowxy1.y, windowxy2.x, windowxy2.y);
}

void QAV::Draw(int ticks, int stat, int shade, int palnum)
{
    dassert(ticksPerFrame > 0);
    int nFrame = ticks / ticksPerFrame;
    dassert(nFrame >= 0 && nFrame < nFrames);
    FRAMEINFO *pFrame = &frames[nFrame];
    for (int i = 0; i < 8; i++)
    {
        if (pFrame->tiles[i].picnum > 0)
            DrawFrame(x, y, &pFrame->tiles[i], stat, shade, palnum);
    }
}

void QAV::Play(int start, int end, int nCallback, void *pData)
{
    dassert(ticksPerFrame > 0);
    int frame;
    int ticks;
    if (start < 0)
        frame = (start + 1) / ticksPerFrame;
    else
        frame = start / ticksPerFrame + 1;
    
    for (ticks = ticksPerFrame * frame; ticks <= end; frame++, ticks += ticksPerFrame)
    {
        if (frame >= 0 && frame < nFrames)
        {
            FRAMEINFO *pFrame = &frames[frame];
            SOUNDINFO *pSound = &pFrame->sound;
            if (pSound->sound > 0)
            {
                if (nSprite == -1)
                    PlaySound(pSound->sound);
                else
                    PlaySound3D(&sprite[nSprite], pSound->sound, 16+pSound->at4, 6);
            }
            if (pFrame->nCallbackId > 0 && nCallback != -1)
            {
                clientCallback[nCallback](pFrame->nCallbackId, pData);
            }
        }
    }
}

void QAV::Preload(void)
{
    for (int i = 0; i < nFrames; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (frames[i].tiles[j].picnum >= 0)
                tilePreloadTile(frames[i].tiles[j].picnum);
        }
    }
}