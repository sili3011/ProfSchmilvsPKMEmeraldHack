playground_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, playground_OnLoad
	.byte 0


playground_OnLoad::
	setflag FLAG_SYS_B_DASH
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_POKEDEX_GET
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_SYS_DEXNAV_GET
	return


playground_EventScript_GetRowlet::
	lockall
	givemon SPECIES_LAPRAS, 10, ITEM_ORAN_BERRY
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
	.string "{PLAYER} obtained Rowlet!$"

playground_Text_ObtainedEonFlute::
	.string "{PLAYER} obtained the Eon Flute!$"

playground_Text_CheckFountain_Dry::
	.string "The fountain seems oddly dry...$"
