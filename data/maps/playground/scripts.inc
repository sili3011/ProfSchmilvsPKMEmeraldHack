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
	givemon SPECIES_LAPRAS, 20, ITEM_ORAN_BERRY
	givemon SPECIES_MACHOP, 20, ITEM_ORAN_BERRY
	givemon SPECIES_TAUROS, 20, ITEM_ORAN_BERRY
	call playground_EventScript_RowletFanfare
	giveitem ITEM_ULTRA_BALL, 10
	releaseall
	end


playground_EventScript_RowletFanfare::
	bufferspeciesname 1, SPECIES_LAPRAS
	bufferspeciesname 1, SPECIES_MACHOP
	bufferspeciesname 1, SPECIES_TAUROS
	removeobject 1
	playfanfare MUS_OBTAIN_ITEM
	setflag FLAG_SYS_POKEMON_GET
	message playground_Text_ObtainedRowlet
	waitmessage
	waitfanfare
	bufferspeciesname 0, SPECIES_LAPRAS
	bufferspeciesname 0, SPECIES_MACHOP
	bufferspeciesname 0, SPECIES_TAUROS
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


playground_EventScript_Maveri::
	trainerbattle_single TRAINER_MAVERI, playground_EventScript_Maveri_Text_0, playground_EventScript_Maveri_Text_1
	end


playground_EventScript_Maveri_Text_0:
	.string "Surf is my favorite move!$"

playground_EventScript_Maveri_Text_1:
	.string "Guess I ll sleep with the fishes today...$"

playground_Text_ObtainedRowlet::
	.string "{PLAYER} obtained a Lapras!$"

playground_Text_ObtainedEonFlute::
	.string "{PLAYER} obtained the Eon Flute!$"

playground_Text_CheckFountain_Dry::
	.string "The fountain seems oddly dry...$"
