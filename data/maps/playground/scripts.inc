playground_MapScripts::
	.byte 0


playground_EventScript_GetRowlet::
	lockall
	givemon SPECIES_LAPRAS, 20, ITEM_ORAN_BERRY
	giveitem ITEM_ULTRA_BALL, 10
	call playground_EventScript_RowletFanfare
	releaseall
	end


playground_EventScript_RowletFanfare::
	bufferspeciesname 1, SPECIES_LAPRAS
	removeobject 1
	playfanfare MUS_OBTAIN_ITEM
	setflag FLAG_SYS_POKEMON_GET
	message playground_Text_ObtainedRowlet
	waitmessage
	waitfanfare
	bufferspeciesname 0, SPECIES_LAPRAS
	return


playground_EventScript_GetEonFlute::
	lockall
	giveitem ITEM_EON_FLUTE, 1
	call playground_EventScript_EonFluteFanfare
	releaseall
	end


playground_EventScript_EonFluteFanfare::
	removeobject 2
	playfanfare MUS_OBTAIN_ITEM
	message playground_Text_ObtainedEonFlute
	waitfanfare
	waitmessage
	return


playground_EventScript_CheckFountain::
	lockall
	message playground_Text_CheckFountain_Dry
	waitmessage
	releaseall
	end


playground_Text_ObtainedRowlet::
	.string "{PLAYER} obtained a Lapras!$"

playground_Text_ObtainedEonFlute::
	.string "{PLAYER} obtained the Eon Flute!$"

playground_Text_CheckFountain_Dry::
	.string "The fountain seems oddly dry...$"
