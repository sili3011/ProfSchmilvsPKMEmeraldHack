#include "global.h"
#include "battle_pyramid.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "menu.h"
#include "map_name_popup.h"
#include "palette.h"
#include "region_map.h"
#include "start_menu.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "constants/layouts.h"
#include "constants/region_map_sections.h"
#include "constants/weather.h"

// enums
enum MapPopUp_Themes
{
    MAPPOPUP_THEME_WOOD,
    MAPPOPUP_THEME_MARBLE,
    MAPPOPUP_THEME_STONE,
    MAPPOPUP_THEME_BRICK,
    MAPPOPUP_THEME_UNDERWATER,
    MAPPOPUP_THEME_STONE2,
};

// static functions
static void Task_MapNamePopUpWindow(u8 taskId);
static void ShowMapNamePopUpWindow(void);
static void LoadMapNamePopUpWindowBg(void);

// EWRAM
static EWRAM_DATA u8 sPopupTaskId = 0;

// .rodata
static const u8 gMapPopUp_Table[][960] =
    {
        INCBIN_U8("graphics/interface/map_popup/wood.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/marble.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/stone.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/brick.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/underwater.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/stone2.4bpp"),
};

static const u8 gMapPopUp_Outline_Table[][960] =
    {
        INCBIN_U8("graphics/interface/map_popup/wood_outline.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/marble_outline.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/stone_outline.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/brick_outline.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/underwater_outline.4bpp"),
        INCBIN_U8("graphics/interface/map_popup/stone2_outline.4bpp"),
};

static const u16 gMapPopUp_Palette_Table[][16] =
    {
        INCBIN_U16("graphics/interface/map_popup/wood.gbapal"),
        INCBIN_U16("graphics/interface/map_popup/marble_outline.gbapal"),
        INCBIN_U16("graphics/interface/map_popup/stone_outline.gbapal"),
        INCBIN_U16("graphics/interface/map_popup/brick_outline.gbapal"),
        INCBIN_U16("graphics/interface/map_popup/underwater_outline.gbapal"),
        INCBIN_U16("graphics/interface/map_popup/stone2_outline.gbapal"),
};

static const u16 gUnknown_0857F444[16] = INCBIN_U16("graphics/interface/map_popup/857F444.gbapal");

static const u8 gRegionMapSectionId_To_PopUpThemeIdMapping[] =
    {
        [MAPSEC_PLAYGROUND] = MAPPOPUP_THEME_STONE2,
        [MAPSEC_PETRIFACTHEIM_CITY] = MAPPOPUP_THEME_MARBLE,
        [MAPSEC_GRANITE_CAVE] = MAPPOPUP_THEME_STONE,
        [MAPSEC_MT_CHIMNEY] = MAPPOPUP_THEME_STONE,
        [MAPSEC_SAFARI_ZONE] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_BATTLE_FRONTIER] = MAPPOPUP_THEME_MARBLE,
        [MAPSEC_PETALBURG_WOODS] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_RUSTURF_TUNNEL] = MAPPOPUP_THEME_STONE,
        [MAPSEC_ABANDONED_SHIP] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_NEW_MAUVILLE] = MAPPOPUP_THEME_MARBLE,
        [MAPSEC_METEOR_FALLS] = MAPPOPUP_THEME_STONE,
        [MAPSEC_METEOR_FALLS2] = MAPPOPUP_THEME_STONE,
        [MAPSEC_MT_PYRE] = MAPPOPUP_THEME_STONE,
        [MAPSEC_AQUA_HIDEOUT_OLD] = MAPPOPUP_THEME_STONE,
        [MAPSEC_SHOAL_CAVE] = MAPPOPUP_THEME_STONE,
        [MAPSEC_SEAFLOOR_CAVERN] = MAPPOPUP_THEME_STONE,
        [MAPSEC_UNDERWATER_SEAFLOOR_CAVERN] = MAPPOPUP_THEME_STONE2,
        [MAPSEC_VICTORY_ROAD] = MAPPOPUP_THEME_STONE,
        [MAPSEC_MIRAGE_ISLAND] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_CAVE_OF_ORIGIN] = MAPPOPUP_THEME_STONE,
        [MAPSEC_SOUTHERN_ISLAND] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_FIERY_PATH] = MAPPOPUP_THEME_STONE,
        [MAPSEC_FIERY_PATH2] = MAPPOPUP_THEME_STONE,
        [MAPSEC_JAGGED_PASS] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_JAGGED_PASS2] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_SEALED_CHAMBER] = MAPPOPUP_THEME_STONE,
        [MAPSEC_UNDERWATER_SEALED_CHAMBER] = MAPPOPUP_THEME_STONE2,
        [MAPSEC_SCORCHED_SLAB] = MAPPOPUP_THEME_STONE,
        [MAPSEC_ISLAND_CAVE] = MAPPOPUP_THEME_STONE,
        [MAPSEC_DESERT_RUINS] = MAPPOPUP_THEME_STONE,
        [MAPSEC_ANCIENT_TOMB] = MAPPOPUP_THEME_STONE,
        [MAPSEC_INSIDE_OF_TRUCK] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_SKY_PILLAR] = MAPPOPUP_THEME_STONE,
        [MAPSEC_SECRET_BASE] = MAPPOPUP_THEME_STONE,
        [MAPSEC_DYNAMIC] = MAPPOPUP_THEME_MARBLE,
        [MAPSEC_AQUA_HIDEOUT -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_MAGMA_HIDEOUT -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_MIRAGE_TOWER -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_BIRTH_ISLAND -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_FARAWAY_ISLAND -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_WOOD,
        [MAPSEC_ARTISAN_CAVE -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_MARINE_CAVE -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_UNDERWATER_MARINE_CAVE -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE2,
        [MAPSEC_TERRA_CAVE -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_UNDERWATER_105 -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE2,
        [MAPSEC_UNDERWATER_125 -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE2,
        [MAPSEC_UNDERWATER_129 -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE2,
        [MAPSEC_DESERT_UNDERPASS -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_ALTERING_CAVE -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_NAVEL_ROCK -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_STONE,
        [MAPSEC_TRAINER_HILL -
            KANTO_MAPSEC_COUNT] = MAPPOPUP_THEME_MARBLE};

static const u8 gText_PyramidFloor1[] = _("PYRAMID FLOOR 1");
static const u8 gText_PyramidFloor2[] = _("PYRAMID FLOOR 2");
static const u8 gText_PyramidFloor3[] = _("PYRAMID FLOOR 3");
static const u8 gText_PyramidFloor4[] = _("PYRAMID FLOOR 4");
static const u8 gText_PyramidFloor5[] = _("PYRAMID FLOOR 5");
static const u8 gText_PyramidFloor6[] = _("PYRAMID FLOOR 6");
static const u8 gText_PyramidFloor7[] = _("PYRAMID FLOOR 7");
static const u8 gText_Pyramid[] = _("PYRAMID");

static const u8 *const gBattlePyramid_MapHeaderStrings[] =
    {
        gText_PyramidFloor1,
        gText_PyramidFloor2,
        gText_PyramidFloor3,
        gText_PyramidFloor4,
        gText_PyramidFloor5,
        gText_PyramidFloor6,
        gText_PyramidFloor7,
        gText_Pyramid,
};

static const u8 sText_PyramidFloor1[] = _("PYRAMID FLOOR 1");
static const u8 sText_PyramidFloor2[] = _("PYRAMID FLOOR 2");
static const u8 sText_PyramidFloor3[] = _("PYRAMID FLOOR 3");
static const u8 sText_PyramidFloor4[] = _("PYRAMID FLOOR 4");
static const u8 sText_PyramidFloor5[] = _("PYRAMID FLOOR 5");
static const u8 sText_PyramidFloor6[] = _("PYRAMID FLOOR 6");
static const u8 sText_PyramidFloor7[] = _("PYRAMID FLOOR 7");
static const u8 sText_Pyramid[] = _("PYRAMID");

static const u8 *const sBattlePyramid_MapHeaderStrings[FRONTIER_STAGES_PER_CHALLENGE + 1] =
    {
        sText_PyramidFloor1,
        sText_PyramidFloor2,
        sText_PyramidFloor3,
        sText_PyramidFloor4,
        sText_PyramidFloor5,
        sText_PyramidFloor6,
        sText_PyramidFloor7,
        sText_Pyramid,
};

static bool8 UNUSED StartMenu_ShowMapNamePopup(void)
{
    HideStartMenu();
    ShowMapNamePopup();
    return TRUE;
}

// States and data defines for Task_MapNamePopUpWindow
enum
{
    STATE_SLIDE_IN,
    STATE_WAIT,
    STATE_SLIDE_OUT,
    STATE_UNUSED,
    STATE_ERASE,
    STATE_END,
    STATE_PRINT, // For some reason the first state is numerically last.
};

#define POPUP_OFFSCREEN_Y 40
#define POPUP_SLIDE_SPEED 2

#define tState data[0]
#define tOnscreenTimer data[1]
#define tYOffset data[2]
#define tIncomingPopUp data[3]
#define tPrintTimer data[4]

void ShowMapNamePopup(void)
{
    if (FlagGet(FLAG_HIDE_MAP_NAME_POPUP) != TRUE)
    {
        if (!FuncIsActiveTask(Task_MapNamePopUpWindow))
        {
            // New pop up window
            sPopupTaskId = CreateTask(Task_MapNamePopUpWindow, 90);
            SetGpuReg(REG_OFFSET_BG0VOFS, POPUP_OFFSCREEN_Y);
            gTasks[sPopupTaskId].tState = STATE_PRINT;
            gTasks[sPopupTaskId].tYOffset = POPUP_OFFSCREEN_Y;
        }
        else
        {
            // There's already a pop up window running.
            // Hurry the old pop up offscreen so the new one can appear.
            if (gTasks[sPopupTaskId].tState != STATE_SLIDE_OUT)
                gTasks[sPopupTaskId].tState = STATE_SLIDE_OUT;
            gTasks[sPopupTaskId].tIncomingPopUp = TRUE;
        }
    }
}

static void Task_MapNamePopUpWindow(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->tState)
    {
    case STATE_PRINT:
        // Wait, then create and print the pop up window
        if (++task->tPrintTimer > 30)
        {
            task->tState = STATE_SLIDE_IN;
            task->tPrintTimer = 0;
            ShowMapNamePopUpWindow();
        }
        break;
    case STATE_SLIDE_IN:
        // Slide the window onscreen.
        task->tYOffset -= POPUP_SLIDE_SPEED;
        if (task->tYOffset <= 0)
        {
            task->tYOffset = 0;
            task->tState = STATE_WAIT;
            gTasks[sPopupTaskId].data[1] = 0;
        }
        break;
    case STATE_WAIT:
        // Wait while the window is fully onscreen.
        if (++task->tOnscreenTimer > 120)
        {
            task->tOnscreenTimer = 0;
            task->tState = STATE_SLIDE_OUT;
        }
        break;
    case STATE_SLIDE_OUT:
        // Slide the window offscreen.
        task->tYOffset += POPUP_SLIDE_SPEED;
        if (task->tYOffset >= POPUP_OFFSCREEN_Y)
        {
            task->tYOffset = POPUP_OFFSCREEN_Y;
            if (task->tIncomingPopUp)
            {
                // A new pop up window is incoming,
                // return to the first state to show it.
                task->tState = STATE_PRINT;
                task->tPrintTimer = 0;
                task->tIncomingPopUp = FALSE;
            }
            else
            {
                task->tState = STATE_ERASE;
                return;
            }
        }
        break;
    case STATE_ERASE:
        ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
        task->tState = STATE_END;
        break;
    case STATE_END:
        HideMapNamePopUpWindow();
        return;
    }
    SetGpuReg(REG_OFFSET_BG0VOFS, task->tYOffset);
}

void HideMapNamePopUpWindow(void)
{
    if (FuncIsActiveTask(Task_MapNamePopUpWindow))
    {
        ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
        RemoveMapNamePopUpWindow();
        SetGpuReg_ForcedBlank(REG_OFFSET_BG0VOFS, 0);
        DestroyTask(sPopupTaskId);
    }
}

static void ShowMapNamePopUpWindow(void)
{
    u8 mapDisplayHeader[24];
    u8 *withoutPrefixPtr;
    u8 x;
    const u8 *mapDisplayHeaderSource;

    if (InBattlePyramid())
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP)
        {
            withoutPrefixPtr = &(mapDisplayHeader[3]);
            mapDisplayHeaderSource = gBattlePyramid_MapHeaderStrings[7];
        }
        else
        {
            withoutPrefixPtr = &(mapDisplayHeader[3]);
            mapDisplayHeaderSource = gBattlePyramid_MapHeaderStrings[gSaveBlock2Ptr->frontier.curChallengeBattleNum];
        }
        StringCopy(withoutPrefixPtr, mapDisplayHeaderSource);
    }
    else
    {
        withoutPrefixPtr = &(mapDisplayHeader[3]);
        GetMapName(withoutPrefixPtr, gMapHeader.regionMapSectionId, 0);
    }
    AddMapNamePopUpWindow();
    LoadMapNamePopUpWindowBg();
    x = GetStringCenterAlignXOffset(7, withoutPrefixPtr, 80);
    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;
    AddTextPrinterParameterized(GetMapNamePopUpWindowId(), 7, mapDisplayHeader, x, 3, 0xFF, NULL);
    CopyWindowToVram(GetMapNamePopUpWindowId(), 3);
}

static void sub_80D4A78(u8 bg, u8 x, u8 y, u8 deltaX, u8 deltaY, u8 unused)
{
    s32 i;

    for (i = 0; i < 12; i++)
    {
        FillBgTilemapBufferRect(bg, 0x21D + i, i - 1 + x, y - 1, 1, 1, 0xE);
    }
    FillBgTilemapBufferRect(bg, 0x229, x - 1, y, 1, 1, 0xE);
    FillBgTilemapBufferRect(bg, 0x22A, deltaX + x, y, 1, 1, 0xE);
    FillBgTilemapBufferRect(bg, 0x22B, x - 1, y + 1, 1, 1, 0xE);
    FillBgTilemapBufferRect(bg, 0x22C, deltaX + x, y + 1, 1, 1, 0xE);
    FillBgTilemapBufferRect(bg, 0x22D, x - 1, y + 2, 1, 1, 0xE);
    FillBgTilemapBufferRect(bg, 0x22E, deltaX + x, y + 2, 1, 1, 0xE);
    for (i = 0; i < 12; i++)
    {
        FillBgTilemapBufferRect(bg, 0x22F + i, i - 1 + x, y + deltaY, 1, 1, 0xE);
    }
}

static void LoadMapNamePopUpWindowBg(void)
{
    u8 popUpThemeId;
    u8 popupWindowId = GetMapNamePopUpWindowId();
    u16 regionMapSectionId = gMapHeader.regionMapSectionId;

    if (regionMapSectionId >= KANTO_MAPSEC_START)
    {
        if (regionMapSectionId > KANTO_MAPSEC_END)
            regionMapSectionId -= KANTO_MAPSEC_COUNT;
        else
            regionMapSectionId = 0; // Discard kanto region sections;
    }
    popUpThemeId = gRegionMapSectionId_To_PopUpThemeIdMapping[regionMapSectionId];

    LoadBgTiles(GetWindowAttribute(popupWindowId, WINDOW_BG), gMapPopUp_Outline_Table[popUpThemeId], 0x400, 0x21D);
    CallWindowFunction(popupWindowId, sub_80D4A78);
    PutWindowTilemap(popupWindowId);
    if (gMapHeader.weather == WEATHER_UNDERWATER_BUBBLES)
        LoadPalette(&gUnknown_0857F444, 0xE0, 0x20);
    else
        LoadPalette(gMapPopUp_Palette_Table[popUpThemeId], 0xE0, 0x20);
    BlitBitmapToWindow(popupWindowId, gMapPopUp_Table[popUpThemeId], 0, 0, 80, 24);
}
