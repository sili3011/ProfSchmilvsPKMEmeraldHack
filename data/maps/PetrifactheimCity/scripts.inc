PetrifactheimCity_MapScripts::
	.byte 0


PetrifactheimCity_EventScript_SurfTrainer1::
	trainerbattle_single TRAINER_SURF_GYM_1, PetrifactheimCity_EventScript_SurfTrainer1_Text_0, PetrifactheimCity_EventScript_SurfTrainer1_Text_1
	end


PetrifactheimCity_EventScript_Maveri::
	trainerbattle_single TRAINER_MAVERI, PetrifactheimCity_EventScript_SurfTrainer1_Text_0, PetrifactheimCity_EventScript_SurfTrainer1_Text_1
	end


PetrifactheimCity_EventScript_SurfTrainer1_Text_0:
	.string "Surf is my favorite move!$"

PetrifactheimCity_EventScript_SurfTrainer1_Text_1:
	.string "Guess I ll sleep with the fishes today...$"
