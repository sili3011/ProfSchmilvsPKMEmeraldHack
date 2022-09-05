EventScript_UseRide::
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_EndUseRide
	bufferpartymonnick 0, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox gText_WantToUseRide, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_ReleaseUseRide
	msgbox gText_PlayerUsedRide, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_RIDE
EventScript_ReleaseUseRide::
	releaseall
EventScript_EndUseRide::
	end
