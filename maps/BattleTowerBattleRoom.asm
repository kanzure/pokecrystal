	object_const_def ; object_event constants
	const BATTLETOWERBATTLEROOM_YOUNGSTER
	const BATTLETOWERBATTLEROOM_RECEPTIONIST

BattleTowerBattleRoom_MapScripts:
	db 2 ; scene scripts
	scene_script .EnterBattleRoom ; SCENE_DEFAULT
	scene_script .DummyScene ; SCENE_FINISHED

	db 0 ; callbacks

.EnterBattleRoom:
	disappear BATTLETOWERBATTLEROOM_YOUNGSTER
	prioritysjump Script_BattleRoom
	setscene SCENE_FINISHED
.DummyScene:
	; setval BATTLETOWERACTION_GET_CHALLENGE_STATE
	; special BattleTowerAction
	; ifequal $1, Script_ShutGameOff
	; ifequal $2, Script_ShutGameOffEarly
	end

Script_BattleRoom:
	applymovement PLAYER, MovementData_BattleTowerBattleRoomPlayerWalksIn
; beat all 7 opponents in a row
Script_BattleRoomLoop:
	setval BATTLETOWERBATTLEROOM_YOUNGSTER
	special LoadOpponentTrainerAndPokemonWithOTSprite
	appear BATTLETOWERBATTLEROOM_YOUNGSTER
	warpsound
	waitsfx
	applymovement BATTLETOWERBATTLEROOM_YOUNGSTER, MovementData_BattleTowerBattleRoomOpponentWalksIn
	opentext
	battletowertext BATTLETOWERTEXT_INTRO
	promptbutton
	closetext
	special BattleTowerBattle ; calls predef startbattle
	special FadeOutPalettes
	reloadmap
	ifnotequal $0, Script_FailedBattleTowerChallenge
	; readmem wNrOfBeatenBattleTowerTrainers
	; ifequal BATTLETOWER_STREAK_LENGTH, Script_BeatenAllTrainers
	applymovement BATTLETOWERBATTLEROOM_YOUNGSTER, MovementData_BattleTowerBattleRoomOpponentWalksOut
	warpsound
	disappear BATTLETOWERBATTLEROOM_YOUNGSTER
	applymovement BATTLETOWERBATTLEROOM_RECEPTIONIST, MovementData_BattleTowerBattleRoomReceptionistWalksToPlayer
	applymovement PLAYER, MovementData_BattleTowerBattleRoomPlayerTurnsToFaceReceptionist
	opentext
	getBTcoins
	updateBTcoinsStringBuffer
	givecoins USE_SCRIPT_VAR
	writetext Text_BTCoins
	waitbutton
	refreshscreen
	special DisplayCoinCaseBalance
	playsound SFX_TRANSACTION
	waitbutton
	refreshscreen
	opentext
	writetext Text_YourMonWillBeHealedToFullHealth
	waitbutton
	closetext
	playmusic MUSIC_HEAL
	special FadeOutPalettes
	special LoadMapPalettes
	pause 60
	special FadeInPalettes
	special RestartMapMusic
	opentext
Script_AskToContinue:
	writetext Text_NextUpOpponentNo
	yesorno
	iffalse Script_DontBattleNextOpponent
	; writetext Text_AskSaveBeforeContinue
	; yesorno
	; iffalse Script_ContinueAndBattleNextOpponent
	; special TryQuickSave
	; iffalse Script_ContinueAndBattleNextOpponent
	; setval BATTLETOWERACTION_SAVELEVELGROUP ; save level group
	; special BattleTowerAction
	; setval BATTLETOWERACTION_SAVEOPTIONS ; choose reward
	; special BattleTowerAction
	; setval BATTLETOWERACTION_SAVE_AND_QUIT ; set challenge state to saved and left
	; special BattleTowerAction
	
Script_ContinueAndBattleNextOpponent:
	closetext
	applymovement PLAYER, MovementData_BattleTowerBattleRoomPlayerTurnsToFaceNextOpponent
	applymovement BATTLETOWERBATTLEROOM_RECEPTIONIST, MovementData_BattleTowerBattleRoomReceptionistWalksAway
	sjump Script_BattleRoomLoop

Script_DontBattleNextOpponent:
	writetext Text_SaveAndEndTheSession
	yesorno
	; iffalse Script_DontSaveAndEndTheSession
	iffalse Script_AskToContinue
	; playsound SFX_SAVE
	; waitsfx
	; special Reset
; Script_DontSaveAndEndTheSession:
	; writetext Text_CancelYourBattleRoomChallenge
	; yesorno
	; iffalse Script_ContinueAndBattleNextOpponent
	; setval BATTLETOWERACTION_CHALLENGECANCELED
	; special BattleTowerAction
	; setval BATTLETOWERACTION_06
	; special BattleTowerAction
	; closetext
	; special FadeOutPalettes
	closetext
	setval BATTLETOWERACTION_SAVELEVELGROUP ; save level group
	special BattleTowerAction
	setval BATTLETOWERACTION_SAVEOPTIONS ; choose reward
	special BattleTowerAction
	setval BATTLETOWERACTION_SAVE_AND_QUIT ; set challenge state to saved and left
	special BattleTowerAction
	special FadeOutPalettes
	warpfacing UP, BATTLE_TOWER_1F, 11, 7
	opentext
	writetext Text_WeHopeToServeYouAgain
	realquicksave
	waitbutton
	closetext
	end
	
; Script_ShutGameOff:
	; warpfacing DOWN, BATTLE_TOWER_1F, 11, 9
	; end

; Script_ShutGameOffEarly:
	; setscene SCENE_DEFAULT
	; warpfacing UP, BATTLE_TOWER_1F, 11, 7
	; end

Script_FailedBattleTowerChallenge:
	pause 60
	special BattleTowerFade
	warpfacing UP, BATTLE_TOWER_1F, 11, 7
	setval BATTLETOWERACTION_CHALLENGECANCELED
	special BattleTowerAction
	opentext
	writetext Text_ThanksForVisiting
	waitbutton
	closetext
	end

; Script_BeatenAllTrainers:
	; pause 60
	; special BattleTowerFade
	; warpfacing UP, BATTLE_TOWER_1F, 11, 7
; Script_BeatenAllTrainers2:
	; opentext
	; writetext Text_CongratulationsYouveBeatenAllTheTrainers
	; sjump Script_GivePlayerHisPrize

UnreferencedScript_0x9f4eb:
	setval BATTLETOWERACTION_CHALLENGECANCELED
	special BattleTowerAction
	opentext
	writetext Text_TooMuchTimeElapsedNoRegister
	waitbutton
	closetext
	end

UnreferencedScript_0x9f4f7:
	setval BATTLETOWERACTION_CHALLENGECANCELED
	special BattleTowerAction
	setval BATTLETOWERACTION_06
	special BattleTowerAction
	opentext
	writetext Text_ThanksForVisiting
	writetext Text_WeHopeToServeYouAgain
	waitbutton
	closetext
	end

Text_ReturnedAfterSave_Mobile:
	text "You'll be returned"
	line "after you SAVE."
	done

BattleTowerBattleRoom_MapEvents:
	db 0, 0 ; filler

	db 2 ; warp events
	warp_event  5,  7, BATTLE_TOWER_HALLWAY, 4
	warp_event  6,  7, BATTLE_TOWER_HALLWAY, 4

	db 0 ; coord events

	db 0 ; bg events

	db 2 ; object events
	object_event  6,  0, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_BATTLE_TOWER_BATTLE_ROOM_YOUNGSTER
	object_event  3,  6, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, -1
