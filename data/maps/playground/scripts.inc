playground_MapScripts::
	.byte 0


playground_EventScript_GetRowlet::
	lockall
	givemon SPECIES_ROWLET, 10, ITEM_ORAN_BERRY
	giveitem ITEM_ULTRA_BALL, 10
	call playground_EventScript_RowletFanfare
	releaseall
	end


playground_EventScript_RowletFanfare::
	bufferspeciesname 1, SPECIES_ROWLET
	removeobject 1
	setflag FLAG_SYS_POKEMON_GET
	message playground_Text_ObtainedRowlet
	waitmessage
	bufferspeciesname 0, SPECIES_ROWLET
	return


playground_EventScript_CheckFountain::
	lockall
	message playground_Text_CheckFountain_Dry
	waitmessage
	releaseall
	end


playground_Text_ObtainedRowlet::
	.string "{PLAYER} obtained Rowlet!$"

playground_Text_CheckFountain_Dry::
	.string "The fountain seems oddly dry...$"