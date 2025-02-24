CheckMagikarpLength:
	; Returns 3 if you select a Magikarp that beats the previous record.
	; Returns 2 if you select a Magikarp, but the current record is longer.
	; Returns 1 if you press B in the Pokemon selection menu.
	; Returns 0 if the Pokemon you select is not a Magikarp.

	; Let's start by selecting a Magikarp.
	farcall SelectMonFromParty
	jr c, .declined
	ld a, [wCurPartySpecies]
	cp MAGIKARP
	jr nz, .not_magikarp

	; Now let's compute its length based on its DVs and Trainer ID.
	ld a, [wCurPartyMon]
	ld hl, wPartyMon1Species
	ld bc, PARTYMON_STRUCT_LENGTH
	call AddNTimes
	push hl
	ld bc, MON_DVS
	add hl, bc
	ld d, h
	ld e, l
	pop hl
	ld bc, MON_OT_ID
	add hl, bc
	ld b, h
	ld c, l
	call CalcMagikarpLength
	call PrintMagikarpLength
	farcall StubbedTrainerRankings_MagikarpLength
	ld hl, .MagikarpGuruMeasureText
	call PrintText

	; Did we beat the record?
	ld hl, wMagikarpLength
	ld de, wBestMagikarpLengthFeet
	ld c, 2
	call CompareBytes
	jr nc, .not_long_enough

	; NEW RECORD!!! Let's save that.
	ld hl, wMagikarpLength
	ld de, wBestMagikarpLengthFeet
	ld a, [hli]
	ld [de], a
	inc de
	ld a, [hl]
	ld [de], a
	inc de
	ld a, [wCurPartyMon]
	ld hl, wPartyMonOTs
	call SkipNames
	call CopyBytes
	ld a, MAGIKARPLENGTH_BEAT_RECORD
	ld [wScriptVar], a
	ret

.not_long_enough
	ld a, MAGIKARPLENGTH_TOO_SHORT
	ld [wScriptVar], a
	ret

.declined
	ld a, MAGIKARPLENGTH_REFUSED
	ld [wScriptVar], a
	ret

.not_magikarp
	xor a ; MAGIKARPLENGTH_NOT_MAGIKARP
	ld [wScriptVar], a
	ret

.MagikarpGuruMeasureText:
	text_far _MagikarpGuruMeasureText
	text_end

Magikarp_LoadFeetInchesChars:
	ld hl, vTiles2 tile "′" ; $6e
	ld de, .feetinchchars
	lb bc, BANK(.feetinchchars), 2
	call Request2bpp
	ret

.feetinchchars
INCBIN "gfx/font/feet_inches.2bpp"

PrintMagikarpLength:
	call Magikarp_LoadFeetInchesChars
	ld hl, wStringBuffer1
	ld de, wMagikarpLength
	lb bc, PRINTNUM_LEFTALIGN | 1, 2
	call PrintNum
	ld [hl], "′"
	inc hl
	ld de, wMagikarpLength + 1
	lb bc, PRINTNUM_LEFTALIGN | 1, 2
	call PrintNum
	ld [hl], "″"
	inc hl
	ld [hl], "@"
	ret

CalcMagikarpLength:
; Return Magikarp's length (in feet and inches) at wMagikarpLength (big endian).
;
; input:
;   de: wEnemyMonDVs
;   bc: wPlayerID

; It generates a value between 190 and 1755 using a Magikarp's DVs
; and its trainer ID. This value is further filtered in LoadEnemyMon
; to make longer Magikarp even rarer.

; The value is generated from a lookup table.
; The index is determined by the DV xored with the player's trainer ID
; and then stored in bc.

; if bc < 10:    [wMagikarpLength] = bc + 190
; if bc ≥ 65510: [wMagikarpLength] = bc - 65510 + 1600
; else:          [wMagikarpLength] = z * 100 + (bc - x) / y

	; bc = rrc(dv[0]) ++ rrc(dv[1]) ^ rrc(id)

	; id
	ld h, b
	ld l, c
	ld a, [hli]
	ld b, a
	ld c, [hl]
	rrc b
	rrc c

	; dv
	ld a, [de]
	inc de
	rrca
	rrca
	xor b
	ld b, a

	ld a, [de]
	rrca
	rrca
	xor c
	ld c, a

	; if bc < 10:
	;     de = bc + 190
	;     break

	ld a, b
	and a
	jr nz, .no
	ld a, c
	cp 10
	jr nc, .no

	ld hl, 190
	add hl, bc
	ld d, h
	ld e, l
	jr .done

.no

	ld hl, MagikarpLengths
	ld a, 2
	ld [wTempByteValue], a

.read
	ld a, [hli]
	ld e, a
	ld a, [hli]
	ld d, a
	call .BCLessThanDE
	jr nc, .next

	; c = (bc - de) / [hl]
	call .BCMinusDE
	ld a, b
	ldh [hDividend + 0], a
	ld a, c
	ldh [hDividend + 1], a
	ld a, [hl]
	ldh [hDivisor], a
	ld b, 2
	call Divide
	ldh a, [hQuotient + 3]
	ld c, a

	; de = c + 100 × (2 + i)
	xor a
	ldh [hMultiplicand + 0], a
	ldh [hMultiplicand + 1], a
	ld a, 100
	ldh [hMultiplicand + 2], a
	ld a, [wTempByteValue]
	ldh [hMultiplier], a
	call Multiply
	ld b, 0
	ldh a, [hProduct + 3]
	add c
	ld e, a
	ldh a, [hProduct + 2]
	adc b
	ld d, a
	jr .done

.next
	inc hl ; align to next triplet
	ld a, [wTempByteValue]
	inc a
	ld [wTempByteValue], a
	cp 16
	jr c, .read

	call .BCMinusDE
	ld hl, 1600
	add hl, bc
	ld d, h
	ld e, l

.done
	; convert from mm to feet and inches
	; in = mm / 25.4
	; ft = in / 12

	; hl = de × 10
	ld h, d
	ld l, e
	add hl, hl
	add hl, hl
	add hl, de
	add hl, hl

	; hl = hl / 254
	ld de, -254
	ld a, -1
.div_254
	inc a
	add hl, de
	jr c, .div_254

	; d, e = hl / 12, hl % 12
	ld d, 0
.mod_12
	cp 12
	jr c, .ok
	sub 12
	inc d
	jr .mod_12
.ok
	ld e, a

	ld hl, wMagikarpLength
	ld [hl], d ; ft
	inc hl
	ld [hl], e ; in
	ret

.BCLessThanDE:
; BUG: Magikarp lengths can be miscalculated (see docs/bugs_and_glitches.md)
	ld a, b
	cp d
	ret c
	ret nc
	ld a, c
	cp e
	ret

.BCMinusDE:
; bc -= de
	ld a, c
	sub e
	ld c, a
	ld a, b
	sbc d
	ld b, a
	ret

INCLUDE "data/events/magikarp_lengths.asm"

MagikarpHouseSign:
	ld a, [wBestMagikarpLengthFeet]
	ld [wMagikarpLength], a
	ld a, [wBestMagikarpLengthInches]
	ld [wMagikarpLength + 1], a
	call PrintMagikarpLength
	ld hl, .KarpGuruRecordText
	call PrintText
	ret

.KarpGuruRecordText:
	text_far _KarpGuruRecordText
	text_end
