# Bugs and Glitches

These are known bugs and glitches in the original Pokémon Crystal game: code that clearly does not work as intended, or that only works in limited circumstances but has the possibility to fail or crash.

Fixes are written in the `diff` format. If you've used Git before, this should look familiar:

```diff
 this is some code
-delete red - lines
+add green + lines
```

Fixes in the [multi-player battle engine](#multi-player-battle-engine) category will break compatibility with standard Pokémon Gold/Silver/Crystal for link battles. This can be avoided by writing more complicated fixes that only apply if the value at `[wLinkMode]` is not `LINK_COLOSSEUM`. That's how Crystal itself fixed two bugs in Gold and Silver regarding the moves [Reflect and Light Screen](#reflect-and-light-screen-can-make-special-defense-wrap-around-above-1024) and [Present](#present-damage-is-incorrect-in-link-battles).


## Contents

- [Multi-player battle engine](#multi-player-battle-engine)
  - [Perish Song and Spikes can leave a Pokémon with 0 HP and not faint](#perish-song-and-spikes-can-leave-a-pok%C3%A9mon-with-0-hp-and-not-faint)
  - [Thick Club and Light Ball can make (Special) Attack wrap around above 1024](#thick-club-and-light-ball-can-make-special-attack-wrap-around-above-1024)
  - [Metal Powder can increase damage taken with boosted (Special) Defense](#metal-powder-can-increase-damage-taken-with-boosted-special-defense)
  - [Reflect and Light Screen can make (Special) Defense wrap around above 1024](#reflect-and-light-screen-can-make-special-defense-wrap-around-above-1024)
  - [Moves with a 100% secondary effect chance will not trigger it in 1/256 uses](#moves-with-a-100-secondary-effect-chance-will-not-trigger-it-in-1256-uses)
  - [Belly Drum sharply boosts Attack even with under 50% HP](#belly-drum-sharply-boosts-attack-even-with-under-50-hp)
  - [Berserk Gene's confusion lasts for 256 turns or the previous Pokémon's confusion count](#berserk-genes-confusion-lasts-for-256-turns-or-the-previous-pok%C3%A9mons-confusion-count)
  - [Confusion damage is affected by type-boosting items and Explosion/Self-Destruct doubling](#confusion-damage-is-affected-by-type-boosting-items-and-explosionself-destruct-doubling)
  - [Moves that lower Defense can do so after breaking a Substitute](#moves-that-lower-defense-can-do-so-after-breaking-a-substitute)
  - [Counter and Mirror Coat still work if the opponent uses an item](#counter-and-mirror-coat-still-work-if-the-opponent-uses-an-item)
  - [A Disabled but PP Up–enhanced move may not trigger Struggle](#a-disabled-but-pp-upenhanced-move-may-not-trigger-struggle)
  - [A Pokémon that fainted from Pursuit will have its old status condition when revived](#a-pok%C3%A9mon-that-fainted-from-pursuit-will-have-its-old-status-condition-when-revived)
  - [Lock-On and Mind Reader don't always bypass Fly and Dig](#lock-on-and-mind-reader-dont-always-bypass-fly-and-dig)
  - [Beat Up can desynchronize link battles](#beat-up-can-desynchronize-link-battles)
  - [Beat Up works incorrectly with only one Pokémon in the party](#beat-up-works-incorrectly-with-only-one-pok%C3%A9mon-in-the-party)
  - [Beat Up may trigger King's Rock even if it failed](#beat-up-may-trigger-kings-rock-even-if-it-failed)
  - [Present damage is incorrect in link battles](#present-damage-is-incorrect-in-link-battles)
  - [Return and Frustration deal no damage when the user's happiness is low or high, respectively](#return-and-frustration-deal-no-damage-when-the-users-happiness-is-low-or-high-respectively)
  - [Dragon Scale, not Dragon Fang, boosts Dragon-type moves](#dragon-scale-not-dragon-fang-boosts-dragon-type-moves)
  - [Switching out or switching against a Pokémon with max HP below 4 freezes the game](#switching-out-or-switching-against-a-pok%C3%A9mon-with-max-HP-below-4-freezes-the-game)
  - [Moves that do damage and increase your stats do not increase stats after a KO](#moves-that-do-damage-and-increase-your-stats-do-not-increase-stats-after-a-ko)
- [Single-player battle engine](#single-player-battle-engine)
  - [A Transformed Pokémon can use Sketch and learn otherwise unobtainable moves](#a-transformed-pok%C3%A9mon-can-use-sketch-and-learn-otherwise-unobtainable-moves)
  - [Catching a Transformed Pokémon always catches a Ditto](#catching-a-transformed-pok%C3%A9mon-always-catches-a-ditto)
  - [Experience underflow for level 1 Pokémon with Medium-Slow growth rate](#experience-underflow-for-level-1-pok%C3%A9mon-with-medium-slow-growth-rate)
  - [The Dude's catching tutorial may crash if his Poké Ball can't be used](#the-dudes-catching-tutorial-may-crash-if-his-pok%C3%A9-ball-cant-be-used)
  - [BRN/PSN/PAR do not affect catch rate](#brnpsnpar-do-not-affect-catch-rate)
  - [Moon Ball does not boost catch rate](#moon-ball-does-not-boost-catch-rate)
  - [Love Ball boosts catch rate for the wrong gender](#love-ball-boosts-catch-rate-for-the-wrong-gender)
  - [Fast Ball only boosts catch rate for three Pokémon](#fast-ball-only-boosts-catch-rate-for-three-pok%C3%A9mon)
  - [Heavy Ball uses wrong weight value for three Pokémon](#heavy-ball-uses-wrong-weight-value-for-three-pok%C3%A9mon)
  - [PRZ and BRN stat reductions don't apply to switched Pokémon](#prz-and-brn-stat-reductions-dont-apply-to-switched-pok%C3%A9mon)
  - [Glacier Badge may not boost Special Defense depending on the value of Special Attack](#glacier-badge-may-not-boost-special-defense-depending-on-the-value-of-special-attack)
  - ["Smart" AI encourages Mean Look if its own Pokémon is badly poisoned](#smart-ai-encourages-mean-look-if-its-own-pok%C3%A9mon-is-badly-poisoned)
  - ["Smart" AI discourages Conversion2 after the first turn](#smart-ai-discourages-conversion2-after-the-first-turn)
  - ["Smart" AI does not encourage Solar Beam, Flame Wheel, or Moonlight during Sunny Day](#smart-ai-does-not-encourage-solar-beam-flame-wheel-or-moonlight-during-sunny-day)
  - [AI does not discourage Future Sight when it's already been used](#ai-does-not-discourage-future-sight-when-its-already-been-used)
  - [AI makes a false assumption about `CheckTypeMatchup`](#ai-makes-a-false-assumption-about-checktypematchup)
  - [AI use of Full Heal or Full Restore does not cure Nightmare status](#ai-use-of-full-heal-or-full-restore-does-not-cure-nightmare-status)
  - [AI use of Full Heal does not cure confusion status](#ai-use-of-full-heal-does-not-cure-confusion-status)
  - [AI might use its base reward value as an item](#ai-might-use-its-base-reward-value-as-an-item)
  - [Wild Pokémon can always Teleport regardless of level difference](#wild-pok%C3%A9mon-can-always-teleport-regardless-of-level-difference)
  - [`RIVAL2` has lower DVs than `RIVAL1`](#rival2-has-lower-dvs-than-rival1)
  - [`HELD_CATCH_CHANCE` has no effect](#held_catch_chance-has-no-effect)
  - [Credits sequence changes move selection menu behavior](#credits-sequence-changes-move-selection-menu-behavior)
- [Overworld engine](#overworld-engine)
  - [`LoadMetatiles` wraps around past 128 blocks](#loadmetatiles-wraps-around-past-128-blocks)
  - [Surfing directly across a map connection does not load the new map](#surfing-directly-across-a-map-connection-does-not-load-the-new-map)
  - [Swimming NPCs aren't limited by their movement radius](#swimming-npcs-arent-limited-by-their-movement-radius)
  - [You can fish on top of NPCs](#you-can-fish-on-top-of-npcs)
  - [Pokémon deposited in the Day-Care might lose experience](#pok%C3%A9mon-deposited-in-the-day-care-might-lose-experience)
- [Graphics](#graphics)
  - [In-battle “`…`” ellipsis is too high](#in-battle--ellipsis-is-too-high)
  - [Two tiles in the `port` tileset are drawn incorrectly](#two-tiles-in-the-port-tileset-are-drawn-incorrectly)
  - [The Ruins of Alph research center's roof color at night looks wrong](#the-ruins-of-alph-research-centers-roof-color-at-night-looks-wrong)
  - [Slowpoke Well's stones use the wrong corner tile](#slowpoke-wells-stones-use-the-wrong-corner-tile)
  - [A hatching Unown egg would not show the right letter](#a-hatching-unown-egg-would-not-show-the-right-letter)
  - [Beat Up may fail to raise Substitute](#beat-up-may-fail-to-raise-substitute)
  - [HP bar animation is slow for high HP](#hp-bar-animation-is-slow-for-high-hp)
  - [HP bar animation off-by-one error for low HP](#hp-bar-animation-off-by-one-error-for-low-hp)
  - [Using a Park Ball in non-Contest battles has a corrupt animation](#using-a-park-ball-in-non-contest-battles-has-a-corrupt-animation)
  - [Battle transitions fail to account for the enemy's level](#battle-transitions-fail-to-account-for-the-enemys-level)
  - [Some trainer NPCs have inconsistent overworld sprites](#some-trainer-npcs-have-inconsistent-overworld-sprites)
  - [Tackle is missing part of its hit animation](#tackle-is-missing-part-of-its-hit-animation)
- [Audio](#audio)
  - [Slot machine payout sound effects cut each other off](#slot-machine-payout-sound-effects-cut-each-other-off)
  - [Team Rocket battle music is not used for Executives or Scientists](#team-rocket-battle-music-is-not-used-for-executives-or-scientists)
  - [No bump noise if standing on tile `$3E`](#no-bump-noise-if-standing-on-tile-3e)
  - [Playing Entei's Pokédex cry can distort Raikou's and Suicune's](#playing-enteis-pok%C3%A9dex-cry-can-distort-raikous-and-suicunes)
  - [`SFX_RUN` does not play correctly when a wild Pokémon flees from battle](#sfx_run-does-not-play-correctly-when-a-wild-pok%C3%A9mon-flees-from-battle)
- [Text](#text)
  - [Five-digit experience gain is printed incorrectly](#five-digit-experience-gain-is-printed-incorrectly)
  - [Only the first three evolution entries can have Stone compatibility reported correctly](#only-the-first-three-evolution-entries-can-have-stone-compatibility-reported-correctly)
  - [`EVOLVE_STAT` can break Stone compatibility reporting](#evolve_stat-can-break-stone-compatibility-reporting)
  - [A "HOF Master!" title for 200-Time Famers is defined but inaccessible](#a-hof-master-title-for-200-time-famers-is-defined-but-inaccessible)
- [Scripted events](#scripted-events)
  - [Clair can give TM24 Dragonbreath twice](#clair-can-give-tm24-dragonbreath-twice)
  - [Daisy's grooming doesn't always increase happiness](#daisys-grooming-doesnt-always-increase-happiness)
  - [Magikarp in Lake of Rage are shorter, not longer](#magikarp-in-lake-of-rage-are-shorter-not-longer)
  - [Magikarp length limits have a unit conversion error](#magikarp-length-limits-have-a-unit-conversion-error)
  - [Magikarp lengths can be miscalculated](#magikarp-lengths-can-be-miscalculated)
  - [`CheckOwnMon` only checks the first five letters of OT names](#checkownmon-only-checks-the-first-five-letters-of-ot-names)
  - [`CheckOwnMonAnywhere` does not check the Day-Care](#checkownmonanywhere-does-not-check-the-day-care)
  - [The unused `phonecall` script command may crash](#the-unused-phonecall-script-command-may-crash)
- [Internal engine routines](#internal-engine-routines)
  - [Saves corrupted by mid-save shutoff are not handled](#saves-corrupted-by-mid-save-shutoff-are-not-handled)
  - [`ScriptCall` can overflow `wScriptStack` and crash](#scriptcall-can-overflow-wscriptstack-and-crash)
  - [`LoadSpriteGFX` does not limit the capacity of `UsedSprites`](#loadspritegfx-does-not-limit-the-capacity-of-usedsprites)
  - [`ChooseWildEncounter` doesn't really validate the wild Pokémon species](#choosewildencounter-doesnt-really-validate-the-wild-pok%C3%A9mon-species)
  - [`TryObjectEvent` arbitrary code execution](#tryobjectevent-arbitrary-code-execution)
  - [`ReadObjectEvents` overflows into `wObjectMasks`](#readobjectevents-overflows-into-wobjectmasks)
  - [`ClearWRAM` only clears WRAM bank 1](#clearwram-only-clears-wram-bank-1)
  - [`BattleAnimCmd_ClearObjs` only clears the first 6⅔ objects](#battleanimcmd_clearobjs-only-clears-the-first-6-objects)
  - [Options menu fails to clear joypad state on initialization](#options-menu-fails-to-clear-joypad-state-on-initialization)


## Multi-player battle engine


### Perish Song and Spikes can leave a Pokémon with 0 HP and not faint

([Video](https://www.youtube.com/watch?v=1IiPWw5fMf8&t=85))

**Fix:** Edit `CheckFaint_PlayerThenEnemy` and `CheckFaint_EnemyThenPlayer` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
 	jp HandleEncore

+HasAnyoneFainted:
+	call HasPlayerFainted
+	jp nz, HasEnemyFainted
+	ret
+
 CheckFaint_PlayerThenEnemy:
-; BUG: Perish Song and Spikes can leave a Pokemon with 0 HP and not faint (see docs/bugs_and_glitches.md)
+.faint_loop
+	call .Function
+	ret c
+	call HasAnyoneFainted
+	ret nz
+	jr .faint_loop
+
+.Function:
 	call HasPlayerFainted
 	jr nz, .PlayerNotFainted
 	call HandlePlayerMonFaint
 	...
```

```diff
 CheckFaint_EnemyThenPlayer:
-; BUG: Perish Song and Spikes can leave a Pokemon with 0 HP and not faint (see docs/bugs_and_glitches.md)
+.faint_loop
+	call .Function
+	ret c
+	call HasAnyoneFainted
+	ret nz
+	jr .faint_loop
+
+.Function:
 	call HasEnemyFainted
 	jr nz, .EnemyNotFainted
 	call HandleEnemyMonFaint
 	...
```


### Thick Club and Light Ball can make (Special) Attack wrap around above 1024

([Video](https://www.youtube.com/watch?v=rGqu3d3pdok&t=450))

**Fix:** Edit `SpeciesItemBoost` in [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm):

```diff
 ; Double the stat
-; BUG: Thick Club and Light Ball can make (Special) Attack wrap around above 1024 (see docs/bugs_and_glitches.md)
 	sla l
 	rl h
+
+	ld a, HIGH(MAX_STAT_VALUE)
+	cp h
+	jr c, .cap
+	ret nz
+	ld a, LOW(MAX_STAT_VALUE)
+	cp l
+	ret nc
+
+.cap
+	ld hl, MAX_STAT_VALUE
 	ret
```


### Metal Powder can increase damage taken with boosted (Special) Defense

([Video](https://www.youtube.com/watch?v=rGqu3d3pdok&t=450))

**Fix:** Edit [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm):

```diff
 DittoMetalPowder:
 	...

-; BUG: Metal Powder can increase damage taken with boosted (Special) Defense (see docs/bugs_and_glitches.md)
-	ld a, c
-	srl a
-	add c
-	ld c, a
-	ret nc
-
-	srl b
-	ld a, b
-	and a
-	jr nz, .done
-	inc b
-.done
-	scf
-	rr c
+	ld h, b
+	ld l, c
+	srl b
+	rr c
+	add hl, bc
+	ld b, h
+	ld c, l
+
+	ld a, HIGH(MAX_STAT_VALUE)
+	cp b
+	jr c, .cap
+	ret nz
+	ld a, LOW(MAX_STAT_VALUE)
+	cp c
+	ret nc
+
+.cap
+	ld bc, MAX_STAT_VALUE
 	ret
```

```diff
 PlayerAttackDamage:
 	...

 .done
+	push hl
+	call DittoMetalPowder
+	pop hl

 	call TruncateHL_BC

 	ld a, [wBattleMonLevel]
 	ld e, a
-	call DittoMetalPowder

 	ld a, 1
 	and a
 	ret
```

```diff
 EnemyAttackDamage:
 	...

 .done
+	push hl
+	call DittoMetalPowder
+	pop hl

 	call TruncateHL_BC

 	ld a, [wBattleMonLevel]
 	ld e, a
-	call DittoMetalPowder

 	ld a, 1
 	and a
 	ret
```


### Reflect and Light Screen can make (Special) Defense wrap around above 1024

This bug existed for all battles in Gold and Silver, and was only fixed for single-player battles in Crystal to preserve link compatibility.

**Fix:** Edit `TruncateHL_BC` in [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm):

```diff
 .finish
-; BUG: Reflect and Light Screen can make (Special) Defense wrap around above 1024 (see docs/bugs_and_glitches.md)
-	ld a, [wLinkMode]
-	cp LINK_COLOSSEUM
-	jr z, .done
 ; If we go back to the loop point,
 ; it's the same as doing this exact
 ; same check twice.
 	ld a, h
 	or b
 	jr nz, .loop

-.done
 	ld b, l
 	ret
```

(This fix also affects Thick Club, Light Ball, and Metal Powder, as described above, but their specific fixes in the above bugs allow more accurate damage calculations.)


### Moves with a 100% secondary effect chance will not trigger it in 1/256 uses

([Video](https://www.youtube.com/watch?v=mHkyO5T5wZU&t=206))

**Fix:** Edit `BattleCommand_EffectChance` in [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm):

```diff
 .got_move_chance
-; BUG: Moves with a 100% secondary effect chance will not trigger it in 1/256 uses (see docs/bugs_and_glitches.md)
-	call BattleRandom
+	ld a, [hl]
+	sub 100 percent
+	; If chance was 100%, RNG won't be called (carry not set)
+	; Thus chance will be subtracted from 0, guaranteeing a carry
+	call c, BattleRandom
 	cp [hl]
 	pop hl
 	ret c

 .failed
 	ld a, 1
 	ld [wEffectFailed], a
 	and a
 	ret
```

**Compatibility preservation:** If you wish to keep compatibility with standard Pokémon Crystal, you can disable the fix during link battles by also applying the following edit in the same place:

```diff
+	ld a, [wLinkMode]
+	cp LINK_COLOSSEUM
+	scf ; Force RNG to be called
+	jr z, .nofix ; Don't apply fix in link battles, for compatibility
 	ld a, [hl]
 	sub 100 percent
 	; If chance was 100%, RNG won't be called (carry not set)
 	; Thus chance will be subtracted from 0, guaranteeing a carry
+.nofix
 	call c, BattleRandom
```

### Belly Drum sharply boosts Attack even with under 50% HP

([Video](https://www.youtube.com/watch?v=zuCLMikWo4Y))

**Fix:** Edit `BattleCommand_BellyDrum` in [engine/battle/move_effects/belly_drum.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/belly_drum.asm):

```diff
 BattleCommand_BellyDrum:
-; BUG: Belly Drum sharply boosts Attack even with under 50% HP (see docs/bugs_and_glitches.md)
-	call BattleCommand_AttackUp2
-	ld a, [wAttackMissed]
-	and a
-	jr nz, .failed
-
 	callfar GetHalfMaxHP
 	callfar CheckUserHasEnoughHP
 	jr nc, .failed
+
+	push bc
+	call BattleCommand_AttackUp2
+	pop bc
+	ld a, [wAttackMissed]
+	and a
+	jr nz, .failed
```


### Berserk Gene's confusion lasts for 256 turns or the previous Pokémon's confusion count

([Video](https://youtube.com/watch?v=Pru3mohq20A))

**Fix:** Edit `HandleBerserkGene` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
 HandleBerserkGene:
 	...
-; BUG: Berserk Gene's confusion lasts for 256 turns or the previous Pokémon's confusion count (see docs/bugs_and_glitches.md)
 	ld a, BATTLE_VARS_SUBSTATUS3
 	call GetBattleVarAddr
 	push af
 	set SUBSTATUS_CONFUSED, [hl]
+	ldh a, [hBattleTurn]
+	and a
+	ld hl, wPlayerConfuseCount
+	jr z, .set_confuse_count
+	ld hl, wEnemyConfuseCount
+.set_confuse_count
+	call BattleRandom
+	and %11
+	add 2
+	ld [hl], a
 	ld a, BATTLE_VARS_MOVE_ANIM
 	call GetBattleVarAddr
 	...
```

This makes the Berserk Gene use the regular confusion duration (2–5 turns).


### Confusion damage is affected by type-boosting items and Explosion/Self-Destruct doubling

([Video](https://twitter.com/crystal_rby/status/874626362287562752))

**Fix:**

First, edit [wram.asm](https://github.com/pret/pokecrystal/blob/master/ram/wram.asm):

```diff
 wTurnEnded:: db

-	ds 1
+wIsConfusionDamage:: db

 wPlayerStats::
```

Then edit four routines in [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm):

```diff
 HitSelfInConfusion:
 	...
 	call TruncateHL_BC
 	ld d, 40
 	pop af
 	ld e, a
+	ld a, TRUE
+	ld [wIsConfusionDamage], a
 	ret
```

```diff
 BattleCommand_DamageCalc:
 ; Return a damage value for move power d, player level e, enemy defense c and player attack b.
-; BUG: Confusion damage is affected by type-boosting items and Explosion/Self-Destruct doubling (see docs/bugs_and_glitches.md)
 	...
 .skip_zero_damage_check
+	xor a ; Not confusion damage
+	ld [wIsConfusionDamage], a
+	; fallthrough
+
+ConfusionDamageCalc:
 ; Minimum defense value is 1.
 	ld a, c
 	and a
 	jr nz, .not_dividing_by_zero
 	ld c, 1
 .not_dividing_by_zero

 	...

 ; Item boosts
+
+; Item boosts don't apply to confusion damage
+	ld a, [wIsConfusionDamage]
+	and a
+	jr nz, .DoneItem
+
 	call GetUserItem

 	...
```

```diff
 CheckEnemyTurn:
 	...

 	ld hl, HurtItselfText
 	call StdBattleTextbox

 	call HitSelfInConfusion
-	call BattleCommand_DamageCalc
+	call ConfusionDamageCalc
 	call BattleCommand_LowerSub

 	...
```

```diff
 HitConfusion:
 	ld hl, HurtItselfText
 	call StdBattleTextbox

 	xor a
 	ld [wCriticalHit], a

 	call HitSelfInConfusion
-	call BattleCommand_DamageCalc
+	call ConfusionDamageCalc
 	call BattleCommand_LowerSub
```


### Moves that lower Defense can do so after breaking a Substitute

([Video](https://www.youtube.com/watch?v=OGwKPRJLaaI))

This bug affects Acid, Iron Tail, and Rock Smash.

**Fix:** Edit `DefenseDownHit` in [data/moves/effects.asm](https://github.com/pret/pokecrystal/blob/master/data/moves/effects.asm):

```diff
 DefenseDownHit:
 	checkobedience
 	usedmovetext
 	doturn
 	critical
 	damagestats
 	damagecalc
 	stab
 	damagevariation
 	checkhit
 	effectchance
 	hittarget
 	failuretext
 	checkfaint
 	criticaltext
 	supereffectivetext
 	checkfaint
 	buildopponentrage
-; BUG: Moves that lower Defense can do so after breaking a Substitute (see docs/bugs_and_glitches.md)
-	effectchance
 	defensedown
 	statdownmessage
 	endmove
```


### Counter and Mirror Coat still work if the opponent uses an item

([Video](https://www.youtube.com/watch?v=uRYyzKRatFk))

**Fix:** Edit `BattleCommand_Counter` in [engine/battle/move_effects/counter.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/counter.asm) and `BattleCommand_MirrorCoat` in [engine/battle/move_effects/mirror_coat.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/mirror_coat.asm):

```diff
-; BUG: Counter and Mirror Coat still work if the opponent uses an item (see docs/bugs_and_glitches.md)
 	ld hl, wCurDamage
 	ld a, [hli]
 	or [hl]
-	ret z
+	jr z, .failed
```

Add this to the end of each file:

```diff
+.failed
+	ld a, 1
+	ld [wEffectFailed], a
+	and a
+	ret
```


### A Disabled but PP Up–enhanced move may not trigger Struggle

([Video](https://www.youtube.com/watch?v=1v9x4SgMggs))

**Fix:** Edit `CheckPlayerHasUsableMoves` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
 .done
-; BUG: A Disabled but PP Up–enhanced move may not trigger Struggle (see docs/bugs_and_glitches.md)
-	and a
+	and PP_MASK
 	ret nz

 .force_struggle
 	ld hl, BattleText_MonHasNoMovesLeft
 	call StdBattleTextbox
 	ld c, 60
 	call DelayFrames
 	xor a
 	ret
```


### A Pokémon that fainted from Pursuit will have its old status condition when revived

([Video](https://www.youtube.com/watch?v=tiRvw-Nb2ME))

**Fix:** Edit `PursuitSwitch` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
-; BUG: A Pokémon that fainted from Pursuit will have its old status condition when revived (see docs/bugs_and_glitches.md)
 	ld a, $f0
 	ld [wCryTracks], a
 	ld a, [wBattleMonSpecies]
 	call PlayStereoCry
+	ld a, [wCurBattleMon]
+	push af
 	ld a, [wLastPlayerMon]
+	ld [wCurBattleMon], a
+	call UpdateFaintedPlayerMon
+	pop af
+	ld [wCurBattleMon], a
-	ld c, a
-	ld hl, wBattleParticipantsNotFainted
-	ld b, RESET_FLAG
-	predef SmallFarFlagAction
 	call PlayerMonFaintedAnimation
 	ld hl, BattleText_MonFainted
 	jr .done_fainted
```


### Lock-On and Mind Reader don't always bypass Fly and Dig

This bug affects Attract, Curse, Foresight, Mean Look, Mimic, Nightmare, Spider Web, Transform, and stat-lowering effects of moves like String Shot or Bubble during the semi-invulnerable turn of Fly or Dig.

**Fix:** Edit `CheckHiddenOpponent` in [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm):

```diff
 CheckHiddenOpponent:
-; BUG: Lock-On and Mind Reader don't always bypass Fly and Dig (see docs/bugs_and_glitches.md)
+	ld a, BATTLE_VARS_SUBSTATUS5_OPP
+	call GetBattleVar
+	cpl
+	and 1 << SUBSTATUS_LOCK_ON
+	ret z
+
 	ld a, BATTLE_VARS_SUBSTATUS3_OPP
 	call GetBattleVar
 	and 1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND
 	ret
```


### Beat Up can desynchronize link battles

([Video](https://www.youtube.com/watch?v=202-iAsrIa8))

**Fix:** Edit `BattleCommand_BeatUp` in [engine/battle/move_effects/beat_up.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/beat_up.asm):

```diff
 .got_mon
-; BUG: Beat Up can desynchronize link battles (see docs/bugs_and_glitches.md)
 	ld a, [wCurBeatUpPartyMon]
 	ld hl, wPartyMonNicknames
 	call GetNickname
 	ld a, MON_HP
 	call GetBeatupMonLocation
 	ld a, [hli]
 	or [hl]
 	jp z, .beatup_fail ; fainted
 	ld a, [wCurBeatUpPartyMon]
 	ld c, a
 	ld a, [wCurBattleMon]
-	cp [hl]
+	cp c
 	ld hl, wBattleMonStatus
 	jr z, .active_mon
 	ld a, MON_STATUS
 	call GetBeatupMonLocation
 .active_mon
 	ld a, [hl]
 	and a
 	jp nz, .beatup_fail
```


### Beat Up works incorrectly with only one Pokémon in the party

This bug prevents the rest of Beat Up's effect from being executed if the player or enemy only has one Pokémon in their party while using it. It prevents Substitute from being raised and King's Rock from working.

**Fix:** Edit `BattleCommand_EndLoop` in [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm):

```diff
 .only_one_beatup
-; BUG: Beat Up works incorrectly with only one Pokémon in the party (see docs/bugs_and_glitches.md)
 	ld a, BATTLE_VARS_SUBSTATUS3
 	call GetBattleVarAddr
 	res SUBSTATUS_IN_LOOP, [hl]
-	call BattleCommand_BeatUpFailText
-	jp EndMoveEffect
+	ret
```

**Cosmetic fix:** This fix does not break compatibility, but it only affects what's shown on the screen for the patched game.

```diff
 .only_one_beatup
 ; BUG: Beat Up works incorrectly with only one Pokemon in the party (see docs/bugs_and_glitches.md)
 	ld a, BATTLE_VARS_SUBSTATUS3
 	call GetBattleVarAddr
 	res SUBSTATUS_IN_LOOP, [hl]
 	call BattleCommand_BeatUpFailText
+	call BattleCommand_RaiseSub
 	jp EndMoveEffect
```


### Beat Up may trigger King's Rock even if it failed

**Fix:** Edit `BattleCommand_BeatUpFailText` in [engine/battle/move_effects/beat_up.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/beat_up.asm):

```diff
 BattleCommand_BeatUpFailText:
-; BUG: Beat Up may trigger King's Rock even if it failed (see docs/bugs_and_glitches.md)
 	ld a, [wBeatUpHitAtLeastOnce]
 	and a
 	ret nz
+
+	inc a
+	ld [wAttackMissed], a

 	jp PrintButItFailed
```


### Present damage is incorrect in link battles

([Video](https://www.youtube.com/watch?v=XJaQoKtrEuw))

This bug existed for all battles in Gold and Silver, and was only fixed for single-player battles in Crystal to preserve link compatibility.

**Fix:** Edit `BattleCommand_Present` in [engine/battle/move_effects/present.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/present.asm):

```diff
 BattleCommand_Present:
-; BUG: Present damage is incorrect in link battles (see docs/bugs_and_glitches.md)
-	ld a, [wLinkMode]
-	cp LINK_COLOSSEUM
-	jr z, .colosseum_skippush
 	push bc
 	push de
-.colosseum_skippush
-
 	call BattleCommand_Stab
-
-	ld a, [wLinkMode]
-	cp LINK_COLOSSEUM
-	jr z, .colosseum_skippop
 	pop de
 	pop bc
-.colosseum_skippop
```


### Return and Frustration deal no damage when the user's happiness is low or high, respectively

This happens because the user's happiness (or 255 − happiness for Frustration) is multiplied by 10 and divided by 25, which rounds down to zero when the happiness is 0–2 (or 253–255 for Frustration).

**Fix:**

Edit [engine/battle/move_effects/return.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/return.asm):

```diff
 BattleCommand_HappinessPower:
-; BUG: Return and Frustration deal no damage when the user's happiness is low or high, respectively (see docs/bugs_and_glitches.md)
 	...
 	call Multiply
 	ld a, 25
 	ldh [hDivisor], a
 	ld b, 4
 	call Divide
 	ldh a, [hQuotient + 3]
+	and a
+	jr nz, .done
+	inc a
+.done
 	ld d, a
 	pop bc
 	ret
```

And edit [engine/battle/move_effects/frustration.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/frustration.asm):

```diff
 BattleCommand_FrustrationPower:
-; BUG: Return and Frustration deal no damage when the user's happiness is low or high, respectively (see docs/bugs_and_glitches.md)
 	...
 	call Multiply
 	ld a, 25
 	ldh [hDivisor], a
 	ld b, 4
 	call Divide
 	ldh a, [hQuotient + 3]
+	and a
+	jr nz, .done
+	inc a
+.done
 	ld d, a
 	pop bc
 	ret
```


### Dragon Scale, not Dragon Fang, boosts Dragon-type moves

**Fix:** Edit `ItemAttributes` in [data/items/attributes.asm](https://github.com/pret/pokecrystal/blob/master/data/items/attributes.asm):

```diff
-; BUG: Dragon Scale, not Dragon Fang, boosts Dragon-type moves (see docs/bugs_and_glitches.md)
 ; DRAGON_FANG
-	item_attribute 100, HELD_NONE, 0, CANT_SELECT, ITEM, ITEMMENU_NOUSE, ITEMMENU_NOUSE
+	item_attribute 100, HELD_DRAGON_BOOST, 10, CANT_SELECT, ITEM, ITEMMENU_NOUSE, ITEMMENU_NOUSE
 ...
 ; DRAGON_SCALE
-	item_attribute 2100, HELD_DRAGON_BOOST, 10, CANT_SELECT, ITEM, ITEMMENU_NOUSE, ITEMMENU_NOUSE
+	item_attribute 2100, HELD_NONE, 0, CANT_SELECT, ITEM, ITEMMENU_NOUSE, ITEMMENU_NOUSE
```


### Switching out or switching against a Pokémon with max HP below 4 freezes the game

This happens because switching involves calculating a percentage of maximum enemy HP. Directly calculating *HP* × 100 / *max HP* would require a two-byte denominator, so instead the game calculates *HP* × 25 / (*max HP* / 4), since even a maximum HP of 999 divided by 4 is 249, which fits in one byte. However, if the maximum HP is below 4 this will divide by 0, which enters an infinite loop in `_Divide`.

**Fix:** First, edit `SendOutMonText` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
-; BUG: Switching out or switching against a Pokémon with max HP below 4 freezes the game (see docs/bugs_and_glitches.md)
 	; compute enemy health remaining as a percentage
 	xor a
 	ldh [hMultiplicand + 0], a
 	ld hl, wEnemyMonHP
 	ld a, [hli]
 	ld [wEnemyHPAtTimeOfPlayerSwitch], a
 	ldh [hMultiplicand + 1], a
 	ld a, [hl]
 	ld [wEnemyHPAtTimeOfPlayerSwitch + 1], a
 	ldh [hMultiplicand + 2], a
-	ld a, 25
-	ldh [hMultiplier], a
-	call Multiply
 	ld hl, wEnemyMonMaxHP
 	ld a, [hli]
 	ld b, [hl]
-	srl a
-	rr b
-	srl a
-	rr b
+	ld c, 100
+	and a
+	jr z, .shift_done
+.shift
+	rra
+	rr b
+	srl c
+	and a
+	jr nz, .shift
+.shift_done
+	ld a, c
+	ldh [hMultiplier], a
+	call Multiply
 	ld a, b
 	ld b, 4
 	ldh [hDivisor], a
 	call Divide
```

Then edit `WithdrawMonText` in the same file:

```diff
 	; compute enemy health lost as a percentage
 	ld hl, wEnemyMonHP + 1
 	ld de, wEnemyHPAtTimeOfPlayerSwitch + 1
 	ld b, [hl]
 	dec hl
 	ld a, [de]
 	sub b
 	ldh [hMultiplicand + 2], a
 	dec de
 	ld b, [hl]
 	ld a, [de]
 	sbc b
 	ldh [hMultiplicand + 1], a
-	ld a, 25
-	ldh [hMultiplier], a
-	call Multiply
 	ld hl, wEnemyMonMaxHP
 	ld a, [hli]
 	ld b, [hl]
-	srl a
-	rr b
-	srl a
-	rr b
+	ld c, 100
+	and a
+	jr z, .shift_done
+.shift
+	rra
+	rr b
+	srl c
+	and a
+	jr nz, .shift
+.shift_done
+	ld a, c
+	ldh [hMultiplier], a
+	call Multiply
 	ld a, b
 	ld b, 4
 	ldh [hDivisor], a
 	call Divide
```

This changes both calculations to *HP* × (100 / *N*) / (*max HP* / *N*) for the smallest necessary *N*, which will be at least 1, so it avoids dividing by zero and is also more accurate.


### Moves that do damage and increase your stats do not increase stats after a KO

`BattleCommand_CheckFaint` "ends the move effect if the opponent faints", and these moves attempt to raise the user's stats *after* `checkfaint`. Note that fixing this can lead to stats being increased at the end of battle, but will not have any negative effects.

**Fix:** Edit [data/moves/effects.asm](https://github.com/pret/pokecrystal/blob/master/data/moves/effects.asm):

```diff
 DefenseUpHit:
 	...
 	criticaltext
 	supereffectivetext
-; BUG: Moves that do damage and increase your stats do not increase stats after a KO (see docs/bugs_and_glitches.md)
+	defenseup
+	statupmessage
 	checkfaint
 	buildopponentrage
-	defenseup
-	statupmessage
 	endmove

 AttackUpHit:
 	...
 	criticaltext
 	supereffectivetext
+	attackup
+	statupmessage
 	checkfaint
 	buildopponentrage
-	attackup
-	statupmessage
 	endmove

 AllUpHit:
 	...
 	criticaltext
 	supereffectivetext
+	allstatsup
 	checkfaint
 	buildopponentrage
-	allstatsup
 	endmove
```


## Single-player battle engine


### A Transformed Pokémon can use Sketch and learn otherwise unobtainable moves

([Video](https://www.youtube.com/watch?v=AFiBxAOkCGI))

**Fix:** Edit `BattleCommand_Sketch` in [engine/battle/move_effects/sketch.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/sketch.asm):

```diff
-; If the opponent is transformed, fail.
-; BUG: A Transformed Pokémon can use Sketch and learn otherwise unobtainable moves (see docs/bugs_and_glitches.md)
+; If the user is transformed, fail.
-	ld a, BATTLE_VARS_SUBSTATUS5_OPP
+	ld a, BATTLE_VARS_SUBSTATUS5
 	call GetBattleVarAddr
 	bit SUBSTATUS_TRANSFORMED, [hl]
 	jp nz, .fail
```


### Catching a Transformed Pokémon always catches a Ditto

**Fix:** Edit `PokeBallEffect` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
 	ld hl, wEnemySubStatus5
 	ld a, [hl]
 	push af
 	set SUBSTATUS_TRANSFORMED, [hl]

-; BUG: Catching a Transformed Pokémon always catches a Ditto (see docs/bugs_and_glitches.md)
 	bit SUBSTATUS_TRANSFORMED, a
-	jr nz, .ditto
-	jr .not_ditto
+	jr nz, .load_data

-.ditto
-	ld a, DITTO
-	ld [wTempEnemyMonSpecies], a
-	jr .load_data
-
-.not_ditto
-	set SUBSTATUS_TRANSFORMED, [hl]
 	ld hl, wEnemyBackupDVs
 	ld a, [wEnemyMonDVs]
 	ld [hli], a
 	ld a, [wEnemyMonDVs + 1]
 	ld [hl], a

 .load_data
 	ld a, [wTempEnemyMonSpecies]
 	ld [wCurPartySpecies], a
 	ld a, [wEnemyMonLevel]
 	ld [wCurPartyLevel], a
 	farcall LoadEnemyMon

 	pop af
 	ld [wEnemySubStatus5], a
```


### Experience underflow for level 1 Pokémon with Medium-Slow growth rate

([Video](https://www.youtube.com/watch?v=SXH8u0plHrE))

**Fix:** Edit `CalcExpAtLevel` in [engine/pokemon/experience.asm](https://github.com/pret/pokecrystal/blob/master/engine/pokemon/experience.asm):

```diff
 CalcExpAtLevel:
 ; (a/b)*n**3 + c*n**2 + d*n - e
-; BUG: Experience underflow for level 1 Pokémon with Medium-Slow growth rate (see docs/bugs_and_glitches.md)
+	ld a, d
+	dec a
+	jr nz, .UseExpFormula
+; Pokémon have 0 experience at level 1
+	ld hl, hProduct
+	ld [hli], a
+	ld [hli], a
+	ld [hli], a
+	ld [hl], a
+	ret
+
+.UseExpFormula
 	ld a, [wBaseGrowthRate]
 	add a
 	add a
 	ld c, a
 	ld b, 0
 	ld hl, GrowthRates
 	add hl, bc
```


### The Dude's catching tutorial may crash if his Poké Ball can't be used

([Video](https://www.youtube.com/watch?v=A8zaTOkjKS4&t=407))

This can occur if your party and current PC box are both full when you start the tutorial.

**Fix:** Edit `PokeBallEffect` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
 PokeBallEffect:
-; BUG: The Dude's catching tutorial may crash if his Poké Ball can't be used (see docs/bugs_and_glitches.md)
 	ld a, [wBattleMode]
 	dec a
 	jp nz, UseBallInTrainerBattle

+	ld a, [wBattleType]
+	cp BATTLETYPE_TUTORIAL
+	jr z, .room_in_party
+
 	ld a, [wPartyCount]
 	cp PARTY_LENGTH
 	jr nz, .room_in_party

 	ld a, BANK(sBoxCount)
 	call OpenSRAM
 	ld a, [sBoxCount]
 	cp MONS_PER_BOX
 	call CloseSRAM
 	jp z, Ball_BoxIsFullMessage
```


### BRN/PSN/PAR do not affect catch rate

**Fix:** Edit `PokeBallEffect` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
 .statuscheck
-; BUG: BRN/PSN/PAR do not affect catch rate (see docs/bugs_and_glitches.md)
 	ld b, a
 	ld a, [wEnemyMonStatus]
 	and 1 << FRZ | SLP_MASK
 	ld c, 10
 	jr nz, .addstatus
+	ld a, [wEnemyMonStatus]
 	and a
 	ld c, 5
 	jr nz, .addstatus
 	ld c, 0
 .addstatus
 	ld a, b
 	add c
 	jr nc, .max_1
 	ld a, $ff
 .max_1
```


### Moon Ball does not boost catch rate

The Moon Ball checks the wrong memory address for the wrong item ID, so no Pokémon can receive the boost.

**Fix:** Edit `MoonBallMultiplier` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
-; BUG: Moon Ball does not boost catch rate (see docs/bugs_and_glitches.md)
 	inc hl
-	inc hl
-	inc hl

 	push bc
 	ld a, BANK("Evolutions and Attacks")
 	call GetFarByte
-	cp MOON_STONE_RED ; BURN_HEAL
+	cp MOON_STONE
 	pop bc
 	ret nz
```

Note that this fix only accounts for Pokémon that evolve via Moon Stone as their first evolution method. However, that is sufficient to cover all Pokémon in the game that can evolve by Moon Stone.


### Love Ball boosts catch rate for the wrong gender

**Fix:** Edit `LoveBallMultiplier` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
 .got_wild_gender

-; BUG: Love Ball boosts catch rate for the wrong gender (see docs/bugs_and_glitches.md)
 	ld a, d
 	pop de
 	cp d
 	pop bc
-	ret nz
+	ret z
```


### Fast Ball only boosts catch rate for three Pokémon

**Fix:** Edit `FastBallMultiplier` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
 .loop
-; BUG: Fast Ball only boosts catch rate for three Pokémon (see docs/bugs_and_glitches.md)
 	ld a, BANK(FleeMons)
 	call GetFarByte

 	inc hl
 	cp -1
 	jr z, .next
 	cp c
-	jr nz, .next
+	jr nz, .loop
 	sla b
 	jr c, .max
```


### Heavy Ball uses wrong weight value for three Pokémon

`HeavyBall_GetDexEntryBank` gets the wrong bank for Kadabra (64), Tauros (128), and Sunflora (192).

**Fix:** Edit `HeavyBall_GetDexEntryBank` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
 HeavyBall_GetDexEntryBank:
-; BUG: Heavy Ball uses wrong weight value for three Pokemon (see docs/bugs_and_glitches.md)
 	push hl
 	push de
 	ld a, [wEnemyMonSpecies]
+	dec a
 	rlca
 	rlca
 	maskbits NUM_DEX_ENTRY_BANKS
 	ld hl, .PokedexEntryBanks
 	ld d, 0
 	ld e, a
 	add hl, de
 	ld a, [hl]
 	pop de
 	pop hl
 	ret

 .PokedexEntryBanks:
 	db BANK("Pokedex Entries 001-064")
 	db BANK("Pokedex Entries 065-128")
 	db BANK("Pokedex Entries 129-192")
 	db BANK("Pokedex Entries 193-251")
```


### PRZ and BRN stat reductions don't apply to switched Pokémon

This does not affect link battles or Battle Tower battles because those jump from `LoadEnemyMon` to `InitEnemyMon`, which already calls `ApplyStatusEffectOnEnemyStats`.

**Fix:** Edit `LoadEnemyMon` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
 	ld hl, wEnemyMonStats
 	ld de, wEnemyStats
 	ld bc, NUM_EXP_STATS * 2
 	call CopyBytes

-; BUG: PRZ and BRN stat reductions don't apply to switched Pokémon (see docs/bugs_and_glitches.md)
+	call ApplyStatusEffectOnEnemyStats
 	ret
```


### Glacier Badge may not boost Special Defense depending on the value of Special Attack

Pryce's dialog ("That BADGE will raise the SPECIAL stats of POKéMON.") implies that Glacier Badge is intended to boost both Special Attack and Special Defense, but the Special Defense boost will not happen unless the unboosted Special Attack stat is 206–432, or 661 or above.

**Fix:** Edit `BadgeStatBoosts.CheckBadge` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
 .CheckBadge:
-; BUG: Glacier Badge may not boost Special Defense depending on the value of Special Attack (see docs/bugs_and_glitches.md)
 	ld a, b
 	srl b
+	push af
 	call c, BoostStat
+	pop af
 	inc hl
 	inc hl
 ; Check every other badge.
 	srl b
 	dec c
 	jr nz, .CheckBadge
 	srl a
 	call c, BoostStat
 	ret
```


### "Smart" AI encourages Mean Look if its own Pokémon is badly poisoned

([Video](https://www.youtube.com/watch?v=cygMO-zHTls))

**Fix:** Edit `AI_Smart_MeanLook` in [engine/battle/ai/scoring.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/ai/scoring.asm):

```diff
 ; 80% chance to greatly encourage this move if the enemy is badly poisoned.
-; BUG: "Smart" AI encourages Mean Look if its own Pokémon is badly poisoned (see docs/bugs_and_glitches.md)
-	ld a, [wEnemySubStatus5]
+	ld a, [wPlayerSubStatus5]
 	bit SUBSTATUS_TOXIC, a
 	jr nz, .asm_38e26
```


### "Smart" AI discourages Conversion2 after the first turn

**Fix:** Edit `AI_Smart_Conversion2` in [engine/battle/ai/scoring.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/ai/scoring.asm):

```diff
 AI_Smart_Conversion2:
-; BUG: "Smart" AI discourages Conversion2 after the first turn (see docs/bugs_and_glitches.md)
 	ld a, [wLastPlayerMove]
 	and a
-	jr nz, .discourage
+	jr z, .discourage
```


### "Smart" AI does not encourage Sunny Day when it knows Solar Beam, Flame Wheel, or Moonlight

**Fix:** Edit `SunnyDayMoves` in [data/battle/ai/sunny_day_moves.asm](https://github.com/pret/pokecrystal/blob/master/data/battle/ai/sunny_day_moves.asm):

```diff
 SunnyDayMoves:
-; BUG: "Smart" AI does not encourage Sunny Day when it knows Solar Beam, Flame Wheel, or Moonlight (see docs/bugs_and_glitches.md)
 	db FIRE_PUNCH
 	db EMBER
 	db FLAMETHROWER
+	db SOLARBEAM
 	db FIRE_SPIN
 	db FIRE_BLAST
+	db FLAME_WHEEL
 	db SACRED_FIRE
 	db MORNING_SUN
 	db SYNTHESIS
+	db MOONLIGHT
 	db -1 ; end
```


### AI does not discourage Future Sight when it's already been used

**Fix:** Edit `AI_Redundant` in [engine/battle/ai/redundant.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/ai/redundant.asm):

```diff
 .FutureSight:
-; BUG: AI does not discourage Future Sight when it's already been used (see docs/bugs_and_glitches.md)
-	ld a, [wEnemyScreens]
-	bit SCREENS_UNUSED, a
+	ld a, [wEnemyFutureSightCount]
+	and a
 	ret
```


### AI makes a false assumption about `CheckTypeMatchup`

**Fix:** Edit `BattleCheckTypeMatchup` in [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm):

```diff
 BattleCheckTypeMatchup:
 	ld hl, wEnemyMonType1
 	ldh a, [hBattleTurn]
 	and a
-	jr z, CheckTypeMatchup
+	jr z, .get_type
 	ld hl, wBattleMonType1
+.get_type
+	ld a, BATTLE_VARS_MOVE_TYPE
+	call GetBattleVar ; preserves hl, de, and bc
 	; fallthrough
 CheckTypeMatchup:
-; BUG: AI makes a false assumption about CheckTypeMatchup (see docs/bugs_and_glitches.md)
 	push hl
 	push de
 	push bc
-	ld a, BATTLE_VARS_MOVE_TYPE
-	call GetBattleVar
 	ld d, a
 	...
```


### AI use of Full Heal or Full Restore does not cure Nightmare status

([Video](https://www.youtube.com/watch?v=rGqu3d3pdok&t=322))

**Fix:** Edit `AI_HealStatus` in [engine/battle/ai/items.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/ai/items.asm):

```diff
 AI_HealStatus:
-; BUG: AI use of Full Heal or Full Restore does not cure Nightmare status (see docs/bugs_and_glitches.md)
 	ld a, [wCurOTMon]
 	ld hl, wOTPartyMon1Status
 	ld bc, PARTYMON_STRUCT_LENGTH
 	call AddNTimes
 	xor a
 	ld [hl], a
 	ld [wEnemyMonStatus], a
+	ld hl, wEnemySubStatus1
+	res SUBSTATUS_NIGHTMARE, [hl]
 	ld hl, wEnemySubStatus5
 	res SUBSTATUS_TOXIC, [hl]
 	ret
```


### AI use of Full Heal does not cure confusion status

**Fix:** Edit `EnemyUsedFullRestore`, and `AI_HealStatus` in [engine/battle/ai/items.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/ai/items.asm):

```diff
 EnemyUsedFullRestore:
-; BUG: AI use of Full Heal does not cure confusion status (see docs/bugs_and_glitches.md)
 	call AI_HealStatus
 	ld a, FULL_RESTORE
 	ld [wCurEnemyItem], a
-	ld hl, wEnemySubStatus3
-	res SUBSTATUS_CONFUSED, [hl]
- 	xor a
- 	ld [wEnemyConfuseCount], a
 	; fallthrough
```

```diff
 AI_HealStatus:
 ; BUG: AI use of Full Heal or Full Restore does not cure Nightmare status (see docs/bugs_and_glitches.md)
 	ld a, [wCurOTMon]
 	ld hl, wOTPartyMon1Status
 	ld bc, PARTYMON_STRUCT_LENGTH
 	call AddNTimes
 	xor a
 	ld [hl], a
 	ld [wEnemyMonStatus], a
+	ld [wEnemyConfuseCount], a
+	ld hl, wEnemySubStatus3
+	res SUBSTATUS_CONFUSED, [hl]
 	ld hl, wEnemySubStatus5
 	res SUBSTATUS_TOXIC, [hl]
 	ret
```

### AI might use its base reward value as an item

In the `AI_TryItem` routine, an item pointer is set to `wEnemyTrainerItem1` and then increments to `wEnemyTrainerItem2` to see if either of the AI's items are in the `AI_Items` list. However, if the AI has used its first item (or its first one is `ITEM_NONE`) and hasn't used its second item, the item pointer can increment from `wEnemyTrainerItem2` to `wEnemyTrainerBaseReward`. If the value at this address then matches an item in the `AI_Items` list, the AI could mistakenly use it.

**Fix:** Edit `AI_TryItem` in [engine/battle/ai/items.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/ai/items.asm):

```diff
 AI_TryItem:
  	...
 	ld a, [wTrainerClass]
 	dec a
 	ld hl, TrainerClassAttributes + TRNATTR_AI_ITEM_SWITCH
 	ld bc, NUM_TRAINER_ATTRIBUTES
 	call AddNTimes
 	ld b, h
 	ld c, l
 	ld hl, AI_Items
-; BUG: AI might use its base reward value as an item (see docs/bugs_and_glitches.md)
-	ld de, wEnemyTrainerItem1
 .loop
+	ld de, wEnemyTrainerItem1
 	ld a, [hl]
 	and a
 	inc a
 	ret z
```


### Wild Pokémon can always Teleport regardless of level difference

**Fix:** Edit `BattleCommand_Teleport` in [engine/battle/move_effects/teleport.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/move_effects/teleport.asm):

```diff
 .loop_enemy
-; BUG: Wild Pokémon can always Teleport regardless of level difference (see docs/bugs_and_glitches.md)
+; If a random number >= player level / 4, Teleport will succeed
 	call BattleRandom
 	cp c
 	jr nc, .loop_enemy
 	; b = player level / 4
 	srl b
 	srl b
 	cp b
-	jr nc, .run_away
+	jr c, .failed
```


### `RIVAL2` has lower DVs than `RIVAL1`

`RIVAL1` is battled throughout the game. `RIVAL2` is battled at Indigo Plateau, and would not be expected to have worse DVs.

**Fix:** Edit `TrainerClassDVs` in [data/trainers/dvs.asm](https://github.com/pret/pokecrystal/blob/master/data/trainers/dvs.asm):

```diff
 	dn 13, 13, 13, 13 ; RIVAL1
 	...
-; BUG: RIVAL2 has lower DVs than RIVAL1 (see docs/bugs_and_glitches.md)
-	dn  9,  8,  8,  8 ; RIVAL2
+	dn 13, 13, 13, 13 ; RIVAL2
```


### `HELD_CATCH_CHANCE` has no effect

**Fix:** Edit `PokeBallEffect` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
-; BUG: HELD_CATCH_CHANCE has no effect (see docs/bugs_and_glitches.md)
 	ld d, a
 	push de
 	ld a, [wBattleMonItem]
+	ld b, a
 	farcall GetItemHeldEffect
 	ld a, b
 	cp HELD_CATCH_CHANCE
 	pop de
 	ld a, d
 	jr nz, .max_2
 	add c
 	jr nc, .max_2
 	ld a, $ff
 .max_2
```


### Credits sequence changes move selection menu behavior

([Video](https://www.youtube.com/watch?v=vjFUo6Jr4po&t=438))

To select a move in battle, you have to press and release the Up or Down buttons. However, after playing the credits sequence, holding down either button will continuously scroll through the moves.

**Fix:** Edit `Credits` in [engine/movie/credits.asm](https://github.com/pret/pokecrystal/blob/master/engine/movie/credits.asm):

```diff
-; BUG: Credits sequence changes move selection menu behavior (see docs/bugs_and_glitches.md)
 	ldh a, [hVBlank]
 	push af
 	ld a, VBLANK_CREDITS
 	ldh [hVBlank], a
+	ldh a, [hInMenu]
+	push af
 	ld a, TRUE
 	ldh [hInMenu], a

 	...

 	ldh [hLCDCPointer], a
 	ldh [hBGMapAddress], a
+	pop af
+	ldh [hInMenu], a
 	pop af
 	ldh [hVBlank], a
 	pop af
 	ldh [rSVBK], a
```

The `[hInMenu]` value determines this button behavior. However, the battle moves menu doesn't actually set `[hInMenu]` to anything, so either behavior *may* have been intentional. The default 0 prevents continuous scrolling; a value of 1 allows it. (The Japanese release sets it to 0.)

**Optional fix:** To explicitly set a `[hInMenu]` for the moves menu, edit `BattleTurn` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
 BattleTurn:
+	ldh a, [hInMenu]
+	push af
+	ld a, 1 ; or "xor a" for the value 0
+	ldh [hInMenu], a
+
 .loop

 	...

 	jp .loop

 .quit
+	pop af
+	ldh [hInMenu], a
 	ret
```


## Overworld engine


### `LoadMetatiles` wraps around past 128 blocks

This bug prevents you from using blocksets with more than 128 blocks.

**Fix:** Edit `LoadMetatiles` in [home/map.asm](https://github.com/pret/pokecrystal/blob/master/home/map.asm):

```diff
 	; Set hl to the address of the current metatile data ([wTilesetBlocksAddress] + (a) tiles).
-; BUG: LoadMetatiles wraps around past 128 blocks (see docs/bugs_and_glitches.md)
-	add a
 	ld l, a
 	ld h, 0
+	add hl, hl
 	add hl, hl
 	add hl, hl
 	add hl, hl
 	ld a, [wTilesetBlocksAddress]
 	add l
 	ld l, a
 	ld a, [wTilesetBlocksAddress + 1]
 	adc h
 	ld h, a
```


### Surfing directly across a map connection does not load the new map

([Video](https://www.youtube.com/watch?v=XFOWvMNG-zw))

**Fix:**

First, edit `UsedSurfScript` in [engine/events/overworld.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/overworld.asm):

```diff
 UsedSurfScript:
-; BUG: Surfing directly across a map connection does not load the new map (see docs/bugs_and_glitches.md)
 	writetext UsedSurfText ; "used SURF!"
 	waitbutton
 	closetext

 	callasm .empty_fn ; empty function

 	readmem wSurfingPlayerState
 	writevar VAR_MOVEMENT

 	special UpdatePlayerSprite
 	special PlayMapMusic
-; step into the water (slow_step DIR, step_end)
 	special SurfStartStep
-	applymovement PLAYER, wMovementBuffer
 	end
```

Then edit `SurfStartStep` in [engine/overworld/player_object.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/player_object.asm):

```diff
 SurfStartStep:
-	call InitMovementBuffer
-	call .GetMovementData
-	call AppendToMovementBuffer
-	ld a, movement_step_end
-	call AppendToMovementBuffer
-	ret
-
-.GetMovementData:
 	ld a, [wPlayerDirection]
 	srl a
 	srl a
 	maskbits NUM_DIRECTIONS
 	ld e, a
 	ld d, 0
 	ld hl, .movement_data
 	add hl, de
-	ld a, [hl]
-	ret
+	add hl, de
+	add hl, de
+	ld a, BANK(.movement_data)
+	jp StartAutoInput

 .movement_data
-	slow_step DOWN
-	slow_step UP
-	slow_step LEFT
-	slow_step RIGHT
+	db D_DOWN,  0, -1
+	db D_UP,    0, -1
+	db D_LEFT,  0, -1
+	db D_RIGHT, 0, -1
```

This fix will make the player enter the water at a normal walking speed, not with a slow step.


### Swimming NPCs aren't limited by their movement radius

This bug is why the Lapras in [maps/UnionCaveB2F.asm](https://github.com/pret/pokecrystal/blob/master/maps/UnionCaveB2F.asm), which uses `SPRITEMOVEDATA_SWIM_WANDER`, is not restricted by its `1, 1` movement radius.

**Fix:** Edit `CanObjectMoveInDirection` in [engine/overworld/npc_movement.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/npc_movement.asm):

```diff
-; BUG: Swimming NPCs aren't limited by their movement radius (see docs/bugs_and_glitches.md)
 	ld hl, OBJECT_FLAGS1
 	add hl, bc
 	bit NOCLIP_TILES_F, [hl]
+	jr nz, .noclip_tiles
```


### You can fish on top of NPCs

**Fix**: Edit [engine/events/overworld.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/overworld.asm):

```diff
 FishFunction:
 ...

 .TryFish:
-; BUG: You can fish on top of NPCs (see docs/bugs_and_glitches.md)
 	ld a, [wPlayerState]
 	cp PLAYER_SURF
 	jr z, .fail
 	cp PLAYER_SURF_PIKA
 	jr z, .fail
 	call GetFacingTileCoord
 	call GetTilePermission
 	cp WATER_TILE
-	jr z, .facingwater
+	jr nz, .fail
+	farcall CheckFacingObject
+	jr nc, .facingwater
 .fail
 	ld a, $3
 	ret
```


### Pokémon deposited in the Day-Care might lose experience

When a Pokémon is withdrawn from the Day-Care, its Exp. Points are reset to the minimum required for its level. This means that if it hadn't gained any levels while in the Day-Care, it may lose experience.

**Fix:** Edit `RetrieveBreedmon` in [engine/pokemon/move_mon.asm](https://github.com/pret/pokecrystal/blob/master/engine/pokemon/move_mon.asm):

```diff
 RetrieveBreedmon:

 	...
-; BUG: Pokémon deposited in the Day-Care might lose experience (see docs/bugs_and_glitches.md)
 	ld a, [wPartyCount]
 	dec a
 	ld [wCurPartyMon], a
 	farcall HealPartyMon
-	ld a, [wCurPartyLevel]
-	ld d, a
+	ld d, MAX_LEVEL
 	callfar CalcExpAtLevel
 	pop bc
-	ld hl, MON_EXP
+	ld hl, MON_EXP + 2
 	add hl, bc
 	ldh a, [hMultiplicand]
-	ld [hli], a
+	ld b, a
 	ldh a, [hMultiplicand + 1]
-	ld [hli], a
+	ld c, a
 	ldh a, [hMultiplicand + 2]
+	ld d, a
+	ld a, [hld]
+	sub d
+	ld a, [hld]
+	sbc c
+	ld a, [hl]
+	sbc b
+	jr c, .not_max_exp
+	ld a, b
+	ld [hli], a
+	ld a, c
+	ld [hli], a
+	ld a, d
 	ld [hl], a
+.not_max_exp
 	and a
 	ret
```


## Graphics


### In-battle “`…`” ellipsis is too high

This is a mistake with the “`…`” tile in [gfx/battle/hp_exp_bar_border.png](https://github.com/pret/pokecrystal/blob/master/gfx/battle/hp_exp_bar_border.png):

![image](https://raw.githubusercontent.com/pret/pokecrystal/master/gfx/battle/hp_exp_bar_border.png)

**Fix:** Lower the ellipsis by two pixels:

![image](https://raw.githubusercontent.com/pret/pokecrystal/master/docs/images/hp_exp_bar_border.png)


### Two tiles in the `port` tileset are drawn incorrectly

This is a mistake with the left-hand warp carpet corner tiles in [gfx/tilesets/port.png](https://github.com/pret/pokecrystal/blob/master/gfx/tilesets/port.png):

![image](https://raw.githubusercontent.com/pret/pokecrystal/master/gfx/tilesets/port.png)

**Fix:** Adjust them to match the right-hand corner tiles:

![image](https://raw.githubusercontent.com/pret/pokecrystal/master/docs/images/port.png)


### The Ruins of Alph research center's roof color at night looks wrong

The dungeons' map group mostly has indoor maps that don't need roof colors, but [maps/RuinsOfAlphOutside.blk](https://github.com/pret/pokecrystal/blob/master/maps/RuinsOfAlphOutside.blk) is an exception. It appears to have poorly-chosen roof colors: the morning/day colors are the same default gray as the unused group 0, and the night colors combine the light default gray and the dark red of Cinnabar's night roofs.

![image](https://raw.githubusercontent.com/pret/pokecrystal/master/docs/images/ruins_of_alph_outside.png)

**Fix:** Edit [gfx/tilesets/roofs.pal](https://github.com/pret/pokecrystal/blob/master/gfx/tilesets/roofs.pal) to use the same red colors as Cinnabar (which are not actually seen in-game):

```diff
 ; group 3 (dungeons)
-	RGB 21,21,21, 11,11,11 ; morn/day
-	RGB 21,21,21, 17,08,07 ; nite
+	RGB 31,10,00, 18,06,00 ; morn/day
+	RGB 18,05,09, 17,08,07 ; nite
```

![image](https://raw.githubusercontent.com/pret/pokecrystal/master/docs/images/ruins_of_alph_outside_cinnabar.png)


### Slowpoke Well's stones use the wrong corner tile

This is a mistake with block $5B in the `johto_modern` tileset. The bottom-left corners of the three stones around Slowpoke Well use tile $4B, but should use tile $47.

![image](https://raw.githubusercontent.com/pret/pokecrystal/master/docs/images/slowpoke_well.png)

**Fix:** Edit block $5B with [Polished Map](https://github.com/Rangi42/polished-map) to use the same tiles as block $5C:

![image](https://raw.githubusercontent.com/pret/pokecrystal/master/docs/images/slowpoke_well_fixed.png)


### A hatching Unown egg would not show the right letter

**Fix:** Edit both functions in [engine/pokemon/breeding.asm](https://github.com/pret/pokecrystal/blob/master/engine/pokemon/breeding.asm):

```diff
 GetEggFrontpic:
-; BUG: A hatching Unown egg would not show the right letter (see docs/bugs_and_glitches.md)
 	push de
 	ld [wCurPartySpecies], a
 	ld [wCurSpecies], a
 	call GetBaseData
-	ld hl, wBattleMonDVs
+	ld a, MON_DVS
+	call GetPartyParamLocation
 	predef GetUnownLetter
 	pop de
 	predef_jump GetMonFrontpic

 GetHatchlingFrontpic:
 	push de
 	ld [wCurPartySpecies], a
 	ld [wCurSpecies], a
 	call GetBaseData
-	ld hl, wBattleMonDVs
+	ld a, MON_DVS
+	call GetPartyParamLocation
 	predef GetUnownLetter
 	pop de
 	predef_jump GetAnimatedFrontpic
```


### Beat Up may fail to raise Substitute

This bug prevents Substitute from being raised if Beat Up was blocked by Protect or Detect.

**Fix:** Edit `BattleCommand_FailureText` in [engine/battle/effect_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/effect_commands.asm).

```diff
-; BUG: Beat Up may fail to raise Substitute (see docs/bugs_and_glitches.md)
 	cp EFFECT_MULTI_HIT
 	jr z, .multihit
 	cp EFFECT_DOUBLE_HIT
 	jr z, .multihit
 	cp EFFECT_POISON_MULTI_HIT
 	jr z, .multihit
+	cp EFFECT_BEAT_UP
+	jr z, .multihit
 	jp EndMoveEffect

 .multihit
 	call BattleCommand_RaiseSub
 	jp EndMoveEffect
```


### HP bar animation is slow for high HP

([Video](https://www.youtube.com/watch?v=SE-BfsFgZVM))

**Fix:** Edit `LongAnim_UpdateVariables` in [engine/battle/anim_hp_bar.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/anim_hp_bar.asm):

```diff
-; BUG: HP bar animation is slow for high HP (see docs/bugs_and_glitches.md)
 	call ComputeHPBarPixels
+	ld a, e
 	pop bc
 	pop de
 	pop hl
-	ld a, e
 	ld hl, wCurHPBarPixels
 	cp [hl]
 	jr z, .loop
 	ld [hl], a
 	and a
 	ret
```


### HP bar animation off-by-one error for low HP

([Video](https://www.youtube.com/watch?v=9KyNVIZxJvI))

**Fix:** Edit `ShortHPBar_CalcPixelFrame` in [engine/battle/anim_hp_bar.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/anim_hp_bar.asm):

```diff
 	ld b, 0
 .loop
-; BUG: HP bar animation off-by-one error for low HP (see docs/bugs_and_glitches.md)
 	ld a, l
 	sub HP_BAR_LENGTH_PX
 	ld l, a
 	ld a, h
 	sbc $0
 	ld h, a
+	jr z, .done
 	jr c, .done
 	inc b
 	jr .loop
```


### Using a Park Ball in non-Contest battles has a corrupt animation

([Video](https://www.youtube.com/watch?v=v1ErZdLCIyU))

**Fix:** Edit `PokeBallEffect` in [engine/items/item_effects.asm](https://github.com/pret/pokecrystal/blob/master/engine/items/item_effects.asm):

```diff
 .room_in_party
-; BUG: Using a Park Ball in non-Contest battles has a corrupt animation (see docs/bugs_and_glitches.md)
 	xor a
 	ld [wWildMon], a
-	ld a, [wCurItem]
-	cp PARK_BALL
+	ld a, [wBattleType]
+	cp BATTLETYPE_CONTEST
 	call nz, ReturnToBattle_UseBall
```


### Battle transitions fail to account for the enemy's level

([Video](https://www.youtube.com/watch?v=eij_1060SMc))

There are three things wrong here:

- `wEnemyMonLevel` isn't initialized yet
- `wBattleMonLevel` gets overwritten after it's initialized by `FindFirstAliveMonAndStartBattle`
- `wBattleMonLevel` isn't initialized until much later when the battle is with a trainer

**Fix:**

First, edit [engine/battle/battle_transition.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/battle_transition.asm):

```diff
 StartTrainerBattle_DetermineWhichAnimation:
 ; The screen flashes a different number of times depending on the level of
 ; your lead Pokemon relative to the opponent's.
-; BUG: Battle transitions fail to account for enemy's level (see docs/bugs_and_glitches.md)
+	ld a, [wOtherTrainerClass]
+	and a
+	jr z, .wild
+	farcall SetTrainerBattleLevel
+
+.wild
+	ld b, PARTY_LENGTH
+	ld hl, wPartyMon1HP
+	ld de, PARTYMON_STRUCT_LENGTH - 1
+
+.loop
+	ld a, [hli]
+	or [hl]
+	jr nz, .okay
+	add hl, de
+	dec b
+	jr nz, .loop
+
+.okay
+	ld de, MON_LEVEL - MON_HP - 1
+	add hl, de
 	ld de, 0
-	ld a, [wBattleMonLevel]
+	ld a, [hl]
 	add 3
-	ld hl, wEnemyMonLevel
+	ld hl, wCurPartyLevel
 	cp [hl]
 	jr nc, .not_stronger
 	set TRANS_STRONGER_F, e
 .not_stronger
 	ld a, [wEnvironment]
 	cp CAVE
 	jr z, .cave
 	cp ENVIRONMENT_5
 	jr z, .cave
 	cp DUNGEON
 	jr z, .cave
 	set TRANS_NO_CAVE_F, e
 .cave
 	ld hl, .StartingPoints
 	add hl, de
 	ld a, [hl]
 	ld [wJumptableIndex], a
 	ret

 .StartingPoints:
 ; entries correspond to TRANS_* constants
 	db BATTLETRANSITION_CAVE
 	db BATTLETRANSITION_CAVE_STRONGER
 	db BATTLETRANSITION_NO_CAVE
 	db BATTLETRANSITION_NO_CAVE_STRONGER
```

Then edit [engine/battle/start_battle.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/start_battle.asm):

```diff
 FindFirstAliveMonAndStartBattle:
 	xor a
 	ldh [hMapAnims], a
 	call DelayFrame
-	ld b, PARTY_LENGTH
-	ld hl, wPartyMon1HP
-	ld de, PARTYMON_STRUCT_LENGTH - 1
-
-.loop
-	ld a, [hli]
-	or [hl]
-	jr nz, .okay
-	add hl, de
-	dec b
-	jr nz, .loop
-
-.okay
-	ld de, MON_LEVEL - MON_HP
-	add hl, de
-	ld a, [hl]
-	ld [wBattleMonLevel], a
 	predef DoBattleTransition
```

Finally, edit [engine/battle/read_trainer_party.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/read_trainer_party.asm):

```diff
 INCLUDE "data/trainers/parties.asm"
+
+SetTrainerBattleLevel:
+	ld a, 255
+	ld [wCurPartyLevel], a
+
+	ld a, [wInBattleTowerBattle]
+	bit IN_BATTLE_TOWER_BATTLE_F, a
+	ret nz
+
+	ld a, [wLinkMode]
+	and a
+	ret nz
+
+	ld a, [wOtherTrainerClass]
+	dec a
+	ld c, a
+	ld b, 0
+	ld hl, TrainerGroups
+	add hl, bc
+	add hl, bc
+	ld a, [hli]
+	ld h, [hl]
+	ld l, a
+
+	ld a, [wOtherTrainerID]
+	ld b, a
+.skip_trainer
+	dec b
+	jr z, .got_trainer
+.skip_party
+	ld a, [hli]
+	cp $ff
+	jr nz, .skip_party
+	jr .skip_trainer
+.got_trainer
+
+.skip_name
+	ld a, [hli]
+	cp "@"
+	jr nz, .skip_name
+
+	inc hl
+	ld a, [hl]
+	ld [wCurPartyLevel], a
+	ret
```


### Some trainer NPCs have inconsistent overworld sprites

*Some of these may have been intentional behavior; use your own judgment for whether to fix them.*

Most trainer classes always use the same sprite and color for their overworld NPCs. There are some exceptions:

- [maps/FastShipCabins_SE_SSE_CaptainsCabin.asm](https://github.com/pret/pokecrystal/blob/master/maps/FastShipCabins_SE_SSE_CaptainsCabin.asm): `TrainerPsychicRodney` should use `SPRITE_YOUNGSTER`, not `SPRITE_SUPER_NERD`
- [maps/LakeOfRage.asm](https://github.com/pret/pokecrystal/blob/master/maps/LakeOfRage.asm): `TrainerFisherAndre` and `TrainerFisherRaymond` should use `PAL_NPC_GREEN`, not `PAL_NPC_BLUE`
- [maps/Route13.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route13.asm): `TrainerHikerKenny` should use `PAL_NPC_BROWN`, not `PAL_NPC_RED`
- [maps/Route44.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route44.asm): `TrainerBirdKeeperVance1` should use `PAL_NPC_BLUE`, not `PAL_NPC_GREEN`
- [maps/Route44.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route44.asm): `TrainerPokemaniacZach` should use `PAL_NPC_BLUE`, not `PAL_NPC_GREEN`
- [maps/UnionCaveB2F.asm](https://github.com/pret/pokecrystal/blob/master/maps/UnionCaveB2F.asm): `TrainerCooltrainermNick` should use `SPRITE_COOLTRAINER_M`, not `SPRITE_ROCKER`
- [maps/FuchsiaPokecenter1F.asm](https://github.com/pret/pokecrystal/blob/master/maps/FuchsiaPokecenter1F.asm): `FuchsiaPokecenter1FNurseScript` should use `PAL_NPC_RED`, not `PAL_NPC_GREEN`
- [maps/IlexForest.asm](https://github.com/pret/pokecrystal/blob/master/maps/IlexForest.asm): `TrainerBugCatcherWayne` should use `SPRITE_BUG_CATCHER` and `PAL_NPC_BROWN`, not `SPRITE_YOUNGSTER` and `PAL_NPC_GREEN`

Most of the NPCs in [maps/NationalParkBugContest.asm](https://github.com/pret/pokecrystal/blob/master/maps/NationalParkBugContest.asm) and [maps/Route36NationalParkGate.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route36NationalParkGate.asm) are also inconsistent with their trainers from other maps:

- `BugCatchingContestant1AScript` and `BugCatchingContestant1BScript`: `BUG_CATCHER DON` from [maps/Route30.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route30.asm) should use `SPRITE_BUG_CATCHER` and `PAL_NPC_BROWN`, not `SPRITE_YOUNGSTER` and `PAL_NPC_RED`
- `BugCatchingContestant2AScript` and `BugCatchingContestant2BScript`: `BUG_CATCHER ED` from [maps/Route2.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route2.asm) should use `SPRITE_BUG_CATCHER` and `PAL_NPC_BROWN`, not `SPRITE_YOUNGSTER` and `PAL_NPC_GREEN`
- `BugCatchingContestant3AScript` and `BugCatchingContestant3BScript`: `COOLTRAINERM NICK` from [maps/UnionCaveB2F.asm](https://github.com/pret/pokecrystal/blob/master/maps/UnionCaveB2F.asm) should use `SPRITE_COOLTRAINER_M` and `PAL_NPC_RED`, not `SPRITE_ROCKER` and `PAL_NPC_BLUE`
- `BugCatchingContestant4AScript` and `BugCatchingContestant4BScript`: `POKEFANM WILLIAM` from [maps/NationalPark.asm](https://github.com/pret/pokecrystal/blob/master/maps/NationalPark.asm) should use `PAL_NPC_RED`, not `PAL_NPC_BROWN`
- `BugCatchingContestant5AScript` and `BugCatchingContestant5BScript`: `BUG_CATCHER BENNY` from [maps/AzaleaGym.asm](https://github.com/pret/pokecrystal/blob/master/maps/AzaleaGym.asm) should use `SPRITE_BUG_CATCHER` and `PAL_NPC_BROWN`, not `SPRITE_YOUNGSTER` and `PAL_NPC_RED`
- `BugCatchingContestant7AScript` and `BugCatchingContestant7BScript`: `PICNICKER CINDY` from [maps/FuchsiaGym.asm](https://github.com/pret/pokecrystal/blob/master/maps/FuchsiaGym.asm) should use `PAL_NPC_GREEN`, not `PAL_NPC_BLUE`
- `BugCatchingContestant8AScript` and `BugCatchingContestant8BScript`: `BUG_CATCHER JOSH` from [maps/AzaleaGym.asm](https://github.com/pret/pokecrystal/blob/master/maps/AzaleaGym.asm) should use `SPRITE_BUG_CATCHER` and `PAL_NPC_BROWN`, not `SPRITE_YOUNGSTER` and `PAL_NPC_RED`
- `BugCatchingContestant9AScript` and `BugCatchingContestant9BScript`: `YOUNGSTER SAMUEL` from [maps/Route34.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route34.asm) should use `PAL_NPC_BLUE`, not `PAL_NPC_GREEN`

(Note that [maps/Route8.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route8.asm) has three `BIKER`s, `DWAYNE`, `HARRIS`, and `ZEKE`, that use `PAL_NPC_RED`, `PAL_NPC_GREEN`, and `PAL_NPC_BLUE` instead of `PAL_NPC_BROWN`; this is intentional since they're the "Kanto Pokémon Federation".)

(The use of `SPRITE_ROCKER` instead of `SPRITE_COOLTRAINER_M` for `COOLTRAINERM NICK` may also be an intentional reference to the player's brother from the [Space World '97 beta](https://github.com/pret/pokegold-spaceworld).)


### Tackle is missing part of its hit animation

Copying two rows causes `BATTLE_BG_EFFECT_TACKLE` to hit the horizontal sprite limit. This fix restores the animation to copy only one row like in Pokémon Gold and Silver.

**Fix:** Edit `BattleAnim_Tackle` in [data/moves/animations.asm](https://github.com/pret/pokecrystal/blob/master/data/moves/animations.asm):

```diff
 BattleAnim_Tackle:
-; BUG: Tackle is missing part of its hit animation (see docs/bugs_and_glitches.md)
 	anim_1gfx BATTLE_ANIM_GFX_HIT
-	anim_call BattleAnim_TargetObj_2Row
+	anim_call BattleAnim_TargetObj_1Row
 	anim_bgeffect BATTLE_BG_EFFECT_TACKLE, $0, BG_EFFECT_USER, $0
```


## Audio


### Slot machine payout sound effects cut each other off

([Video](https://www.youtube.com/watch?v=ojq3xqfRF6I))

**Fix:** Edit `SlotsAction_PayoutAnim` in [engine/games/slot_machine.asm](https://github.com/pret/pokecrystal/blob/master/engine/games/slot_machine.asm):

```diff
 .okay
-; BUG: Slot machine payout sound effects cut each other off (see docs/bugs_and_glitches.md)
 	ld [hl], e
 	dec hl
 	ld [hl], d
 	ld a, [wSlotsDelay]
 	and $7
-	ret z
+	ret nz
 	ld de, SFX_GET_COIN_FROM_SLOTS
 	call PlaySFX
 	ret
```


### Team Rocket battle music is not used for Executives or Scientists

**Fix:** Edit `PlayBattleMusic` in [engine/battle/start_battle.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/start_battle.asm):

```diff
-; BUG: Team Rocket battle music is not used for Executives or Scientists (see docs/bugs_and_glitches.md)
 	ld de, MUSIC_ROCKET_BATTLE
 	cp GRUNTM
 	jr z, .done
 	cp GRUNTF
 	jr z, .done
+	cp EXECUTIVEM
+	jr z, .done
+	cp EXECUTIVEF
+	jr z, .done
+	cp SCIENTIST
+	jr z, .done
```


### No bump noise if standing on tile `$3E`

If `[wWalkingDirection]` is `STANDING` (`$FF`), this will check `[.EdgeWarps + $ff]`, which happens to be `$3E`.

**Fix:** Edit `DoPlayerMovement.CheckWarp` in [engine/overworld/player_movement.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/player_movement.asm):

```diff
 .CheckWarp:
-; BUG: No bump noise if standing on tile $3E (see docs/bugs_and_glitches.md)

 	ld a, [wWalkingDirection]
+	cp STANDING
+	jr z, .not_warp
 	ld e, a
 	ld d, 0
 	ld hl, .EdgeWarps
 	add hl, de
 	ld a, [wPlayerTileCollision]
 	cp [hl]
 	jr nz, .not_warp

 	ld a, TRUE
 	ld [wWalkingIntoEdgeWarp], a
 	ld a, [wWalkingDirection]
-	cp STANDING
-	jr z, .not_warp
```


### Playing Entei's Pokédex cry can distort Raikou's and Suicune's

([Video](https://www.youtube.com/watch?v=z305e4sIO24))

The exact cause of this bug is unknown.

**Workaround:** Edit `DexEntryScreen_MenuActionJumptable.Cry` in [engine/pokedex/pokedex.asm](https://github.com/pret/pokecrystal/blob/master/engine/pokedex/pokedex.asm):

```diff
 .Cry:
-; BUG: Playing Entei's Pokédex cry can distort Raikou's and Suicune's (see docs/bugs_and_glitches.md)
-	call Pokedex_GetSelectedMon
-	ld a, [wTempSpecies]
-	call GetCryIndex
-	ld e, c
-	ld d, b
-	call PlayCry
+	ld a, [wCurPartySpecies]
+	call PlayMonCry
 	ret
```


## Text


### Five-digit experience gain is printed incorrectly

([Video](https://www.youtube.com/watch?v=o54VjpAEoO8))

**Fix:** Edit `_BoostedExpPointsText` and `_ExpPointsText` in [data/text/common_2.asm](https://github.com/pret/pokecrystal/blob/master/data/text/common_2.asm):

```diff
 _BoostedExpPointsText::
-; BUG: Five-digit experience gain is printed incorrectly (see docs/bugs_and_glitches.md)
 	text_start
 	line "a boosted"
 	cont "@"
-	text_decimal wStringBuffer2, 2, 4
+	text_decimal wStringBuffer2, 2, 5
 	text " EXP. Points!"
 	prompt

 _ExpPointsText::
-; BUG: Five-digit experience gain is printed incorrectly (see docs/bugs_and_glitches.md)
 	text_start
 	line "@"
-	text_decimal wStringBuffer2, 2, 4
+	text_decimal wStringBuffer2, 2, 5
 	text " EXP. Points!"
 	prompt
```


### Only the first three evolution entries can have Stone compatibility reported correctly

**Workaround:** Edit `PlacePartyMonEvoStoneCompatibility.DetermineCompatibility` in [engine/pokemon/party_menu.asm](https://github.com/pret/pokecrystal/blob/master/engine/pokemon/party_menu.asm):

```diff
 .DetermineCompatibility:
-; BUG: Only the first three evolution entries can have Stone compatibility reported correctly (see docs/bugs_and_glitches.md)
 	ld de, wStringBuffer1
 	ld a, BANK(EvosAttacksPointers)
 	ld bc, 2
 	call FarCopyBytes
 	ld hl, wStringBuffer1
 	ld a, [hli]
 	ld h, [hl]
 	ld l, a
 	ld de, wStringBuffer1
 	ld a, BANK("Evolutions and Attacks")
-	ld bc, 10
+	ld bc, STRING_BUFFER_LENGTH
 	call FarCopyBytes
```

This supports up to six entries.


### `EVOLVE_STAT` can break Stone compatibility reporting

**Fix:** Edit `PlacePartyMonEvoStoneCompatibility.DetermineCompatibility` in [engine/pokemon/party_menu.asm](https://github.com/pret/pokecrystal/blob/master/engine/pokemon/party_menu.asm):

```diff
 .loop2
-; BUG: EVOLVE_STAT can break Stone compatibility reporting (see docs/bugs_and_glitches.md)
 	ld a, [hli]
 	and a
 	jr z, .nope
+	cp EVOLVE_STAT
+	jr nz, .not_four_bytes
+	inc hl
+.not_four_bytes
 	inc hl
 	inc hl
 	cp EVOLVE_ITEM
 	jr nz, .loop2
```


### A "HOF Master!" title for 200-Time Famers is defined but inaccessible

([Video](https://www.youtube.com/watch?v=iHkWubvxmSg))

**Fix:** Edit `_HallOfFamePC.DisplayMonAndStrings` in [engine/events/halloffame.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/halloffame.asm):

```diff
-; BUG: A "HOF Master!" title for 200-Time Famers is defined but inaccessible (see docs/bugs_and_glitches.md)
 	ld a, [wHallOfFameTempWinCount]
-	cp HOF_MASTER_COUNT + 1
+	cp HOF_MASTER_COUNT
 	jr c, .print_num_hof
 	ld de, .HOFMaster
 	hlcoord 1, 2
 	call PlaceString
 	hlcoord 13, 2
 	jr .finish
```


## Scripted events


### Clair can give TM24 Dragonbreath twice

([Video](https://www.youtube.com/watch?v=8BvBjqxmyOk))

**Fix:**

Edit `DragonsDen1F_MapScripts` in [maps/DragonsDen1F.asm](https://github.com/pret/pokecrystal/blob/master/maps/DragonsDen1F.asm):

```diff
 	def_callbacks
+	callback MAPCALLBACK_NEWMAP, .UnsetClairScene
+
+.UnsetClairScene:
+	setmapscene DRAGONS_DEN_B1F, SCENE_DRAGONSDENB1F_NOOP
+	endcallback
```

And edit [maps/DragonsDenB1F.asm](https://github.com/pret/pokecrystal/blob/master/maps/DragonsDenB1F.asm):

```diff
 DragonsDenB1F_ClairScene:
-; BUG: Clair can give TM24 Dragonbreath twice (see docs/bugs_and_glitches.md)
```


### Daisy's grooming doesn't always increase happiness

Subtracting `$FF` from `$FF` fails to set the carry flag, which results in a 0.4% chance that Daisy's grooming will not affect your Pokémon's happiness.

This is a bug with `HaircutOrGrooming` in [engine/events/haircut.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/haircut.asm):

```asm
.loop
	sub [hl]
	jr c, .ok
	inc hl
	inc hl
	inc hl
	jr .loop

.ok
	inc hl
	ld a, [hli]
	ld [wScriptVar], a
	ld c, [hl]
	call ChangeHappiness
	ret

...

INCLUDE "data/events/happiness_probabilities.asm"

CopyPokemonName_Buffer1_Buffer3:
	ld hl, wStringBuffer1
	ld de, wStringBuffer3
	ld bc, MON_NAME_LENGTH
	jp CopyBytes
```

**Fix:** Edit  [data/events/happiness_probabilities.asm](https://github.com/pret/pokecrystal/blob/master/data/events/happiness_probabilities.asm):

```diff
 HappinessData_DaisysGrooming:
-; BUG: Daisy's grooming doesn't always increase happiness (see docs/bugs_and_glitches.md)
-	db -1,             2, HAPPINESS_GROOMING ; 99.6% chance
+	db 50 percent,     2, HAPPINESS_GROOMING ; 50% chance
+	db -1,             2, HAPPINESS_GROOMING ; 50% chance
```


### Magikarp in Lake of Rage are shorter, not longer

`cp HIGH(1024)` should be `cp 3`, since 1024 mm = 3'4", but `HIGH(1024)` = 4.

**Fix:** Edit `LoadEnemyMon.CheckMagikarpArea` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
 .CheckMagikarpArea:
-; BUG: Magikarp in Lake of Rage are shorter, not longer (see docs/bugs_and_glitches.md)
 	ld a, [wMapGroup]
 	cp GROUP_LAKE_OF_RAGE
-	jr z, .Happiness
+	jr nz, .Happiness
 	ld a, [wMapNumber]
 	cp MAP_LAKE_OF_RAGE
-	jr z, .Happiness
+	jr nz, .Happiness
 ; 40% chance of not flooring
 	call Random
 	cp 39 percent + 1
 	jr c, .Happiness
 ; Try again if length < 1024 mm (i.e. if HIGH(length) < 3 feet)
 	ld a, [wMagikarpLength]
-	cp HIGH(1024)
+	cp 3
 	jr c, .GenerateDVs ; try again
```


### Magikarp length limits have a unit conversion error

- `cp HIGH(1536)` should be `cp 5`, since 1536 mm = 5'0", but `HIGH(1536)` = 6.
- `cp LOW(1616)` should be `cp 4`, since 1616 mm = 5'4", but `LOW(1616)` = 80.
- `cp LOW(1600)` should be `cp 3`, since 1600 mm = 5'3", but `LOW(1600)` = 64.

**Fix:** Edit `LoadEnemyMon.CheckMagikarpArea` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
 ; Get Magikarp's length
-; BUG: Magikarp length limits have a unit conversion error (see docs/bugs_and_glitches.md)
 	ld de, wEnemyMonDVs
 	ld bc, wPlayerID
 	callfar CalcMagikarpLength

 ; No reason to keep going if length > 1536 mm (i.e. if HIGH(length) > 6 feet)
 	ld a, [wMagikarpLength]
-	cp HIGH(1536)
+	cp 5
 	jr nz, .CheckMagikarpArea

 ; 5% chance of skipping both size checks
 	call Random
 	cp 5 percent
 	jr c, .CheckMagikarpArea
 ; Try again if length >= 1616 mm (i.e. if LOW(length) >= 4 inches)
 	ld a, [wMagikarpLength + 1]
-	cp LOW(1616)
+	cp 4
 	jr nc, .GenerateDVs

 ; 20% chance of skipping this check
 	call Random
 	cp 20 percent - 1
 	jr c, .CheckMagikarpArea
 ; Try again if length >= 1600 mm (i.e. if LOW(length) >= 3 inches)
 	ld a, [wMagikarpLength + 1]
-	cp LOW(1600)
+	cp 3
 	jr nc, .GenerateDVs
```

**Better fix:** Rewrite the whole system to use millimeters instead of feet and inches, since they have better precision (1 in = 25.4 mm); and only convert from metric to imperial units for display purposes (or don't, of course).


### Magikarp lengths can be miscalculated

`CalcMagikarpLength.BCLessThanDE` only compares the high bytes of `bc` and `de`. This causes the first entry of the `MagikarpLengths` table to go unused, and `bc` values between 65,280 and 65,509 to use the wrong formula. As a side effect, the highest possible length is capped at 1,625mm (before being converted to feet and inches).

**Fix:** Edit `CalcMagikarpLength.BCLessThanDE` in [engine/events/magikarp.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/magikarp.asm):

```diff
 .BCLessThanDE:
-; BUG: Magikarp lengths can be miscalculated (see docs/bugs_and_glitches.md)
 	ld a, b
 	cp d
-	ret c
-	ret nc
+	ret nz
 	ld a, c
 	cp e
 	ret
```


### `CheckOwnMon` only checks the first five letters of OT names

([Video](https://www.youtube.com/watch?v=GVTTmReM4nQ))

This bug can allow you to talk to Eusine in Celadon City and encounter Ho-Oh with only traded legendary beasts.

**Fix:** Edit `CheckOwnMon` in [engine/pokemon/search_owned.asm](https://github.com/pret/pokecrystal/blob/master/engine/pokemon/search_owned.asm):

```diff
 	; check OT

 	ld hl, wPlayerName

-; BUG: CheckOwnMon only checks the first five letters of OT names (see docs/bugs_and_glitches.md)
-rept NAME_LENGTH_JAPANESE - 2
+rept PLAYER_NAME_LENGTH - 2
 	ld a, [de]
 	cp [hl]
 	jr nz, .notfound
 	cp "@"
 	jr z, .found ; reached end of string
 	inc hl
 	inc de
 endr

 	ld a, [de]
 	cp [hl]
 	jr z, .found
```


### `CheckOwnMonAnywhere` does not check the Day-Care

*This may have been intentional behavior; use your own judgment for whether to fix it.*

This bug can prevent you from talking to Eusine in Celadon City or encountering Ho-Oh when a caught legendary beast is in the Day-Care.

**Fix:** Edit `CheckOwnMonAnywhere` in [engine/pokemon/search_owned.asm](https://github.com/pret/pokecrystal/blob/master/engine/pokemon/search_owned.asm):

```diff
-; BUG: CheckOwnMon does not check the Day-Care (see docs/bugs_and_glitches.md)
+	ld hl, wBreedMon1Species
+	ld bc, wBreedMon1OT
+	call CheckOwnMon
+	ret c ; found!
+
+	ld hl, wBreedMon2Species
+	ld bc, wBreedMon2OT
+	call CheckOwnMon
+	ret c ; found!
+
 	ld d, a
 	ld e, 0
 	ld hl, wPartyMon1Species
 	ld bc, wPartyMonOTs
```


### The unused `phonecall` script command may crash

The `phonecall` script command calls the `PhoneCall` routine, which calls the `BrokenPlaceFarString` routine; this switches banks without being in bank 0, so it would start running arbitrary data as code.

**Fix:** Edit `PhoneCall.CallerTextboxWithName` in [engine/phone/phone.asm](https://github.com/pret/pokecrystal/blob/master/engine/phone/phone.asm):

```diff
-; BUG: The unused phonecall script command may crash (see docs/bugs_and_glitches.md)
-	ld a, [wPhoneScriptBank]
-	ld b, a
 	ld a, [wPhoneCaller]
 	ld e, a
 	ld a, [wPhoneCaller + 1]
 	ld d, a
-	call BrokenPlaceFarString
+	ld a, [wPhoneScriptBank]
+	call PlaceFarString
 	ret
```

You can also delete the now-unused `BrokenPlaceFarString` routine in the same file.


## Internal engine routines


### Saves corrupted by mid-save shutoff are not handled

([Video 1](https://www.youtube.com/watch?v=ukqtK0l6bu0), [Video 2](https://www.youtube.com/watch?v=c2zHd1BPtvc))

This allows Pokémon to be duplicated, among other effects. It does not have a simple and accurate fix. A fix would involve redesigning parts of the save system for Pokémon boxes.


### `ScriptCall` can overflow `wScriptStack` and crash

**Fix:** Edit `ScriptCall` in [engine/overworld/scripting.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/scripting.asm):

```diff
 ScriptCall:
-; BUG: ScriptCall can overflow wScriptStack and crash (see docs/bugs_and_glitches.md)
-
+	ld hl, wScriptStackSize
+	ld a, [hl]
+	cp 5
+	ret nc
 	push de
-	ld hl, wScriptStackSize
-	ld e, [hl]
 	inc [hl]
+	ld e, a
 	ld d, 0
 	ld hl, wScriptStack
 	add hl, de
 	add hl, de
 	add hl, de
 	pop de
 	ld a, [wScriptBank]
 	ld [hli], a
 	ld a, [wScriptPos]
 	ld [hli], a
 	ld a, [wScriptPos + 1]
 	ld [hl], a
 	ld a, b
 	ld [wScriptBank], a
 	ld a, e
 	ld [wScriptPos], a
 	ld a, d
 	ld [wScriptPos + 1], a
 	ret
```


### `LoadSpriteGFX` does not limit the capacity of `UsedSprites`

**Fix:** Edit `LoadSpriteGFX` in [engine/overworld/overworld.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/overworld.asm):

```diff
 LoadSpriteGFX:
-; BUG: LoadSpriteGFX does not limit the capacity of UsedSprites (see docs/bugs_and_glitches.md)
-
 	ld hl, wUsedSprites
 	ld b, SPRITE_GFX_LIST_CAPACITY
 .loop
 	ld a, [hli]
 	and a
 	jr z, .done
 	push hl
 	call .LoadSprite
 	pop hl
 	ld [hli], a
 	dec b
 	jr nz, .loop

 .done
 	ret

 .LoadSprite:
+	push bc
 	call GetSprite
+	pop bc
 	ld a, l
 	ret
```


### `ChooseWildEncounter` doesn't really validate the wild Pokémon species

**Fix:** Edit `ChooseWildEncounter` in [engine/overworld/wildmons.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/wildmons.asm):

```diff
 .ok
-; BUG: ChooseWildEncounter doesn't really validate the wild Pokemon species (see docs/bugs_and_glitches.md)
 	ld a, b
 	ld [wCurPartyLevel], a
 	ld b, [hl]
+	ld a, b
 	call ValidateTempWildMonSpecies
 	jr c, .nowildbattle

-	ld a, b
 	cp UNOWN
 	jr nz, .done
```


### `TryObjectEvent` arbitrary code execution

If `IsInArray` returns `nc`, data at `bc` will be executed as code.

**Fix:** Edit `TryObjectEvent` in [engine/overworld/events.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/events.asm):

```diff
-; BUG: TryObjectEvent arbitrary code execution (see docs/bugs_and_glitches.md)
 	push bc
 	ld de, 3
 	ld hl, ObjectEventTypeArray
 	call IsInArray
-	jr nc, .nope
 	pop bc
+	jr nc, .nope

 	inc hl
 	ld a, [hli]
 	ld h, [hl]
 	ld l, a
 	jp hl

 .nope
 	xor a
 	ret
```


### `ReadObjectEvents` overflows into `wObjectMasks`

**Fix:** Edit `ReadObjectEvents` in [home/map.asm](https://github.com/pret/pokecrystal/blob/master/home/map.asm):

```diff
-; get NUM_OBJECTS - [wCurMapObjectEventCount]
+; get NUM_OBJECTS - [wCurMapObjectEventCount] - 1
-; BUG: ReadObjectEvents overflows into wObjectMasks (see docs/bugs_and_glitches.md)
 	ld a, [wCurMapObjectEventCount]
 	ld c, a
-	ld a, NUM_OBJECTS
+	ld a, NUM_OBJECTS - 1
 	sub c
 	jr z, .skip
+	jr c, .skip

 	; could have done "inc hl" instead
 	ld bc, 1
 	add hl, bc
 	ld bc, MAPOBJECT_LENGTH
 .loop
 	ld [hl],  0
 	inc hl
 	ld [hl], -1
 	dec hl
 	add hl, bc
 	dec a
 	jr nz, .loop
```


### `ClearWRAM` only clears WRAM bank 1

**Fix:** Edit `ClearWRAM` in [home/init.asm](https://github.com/pret/pokecrystal/blob/master/home/init.asm):

```diff
 ClearWRAM::
 ; Wipe swappable WRAM banks (1-7)
 ; Assumes CGB or AGB
-; BUG: ClearWRAM only clears WRAM bank 1 (see docs/bugs_and_glitches.md)

 	ld a, 1
 .bank_loop
 	push af
 	ldh [rSVBK], a
 	xor a
 	ld hl, STARTOF(WRAMX)
 	ld bc, SIZEOF(WRAMX)
 	call ByteFill
 	pop af
 	inc a
 	cp 8
-	jr nc, .bank_loop
+	jr c, .bank_loop
 	ret
```


### `BattleAnimCmd_ClearObjs` only clears the first 6⅔ objects

**Fix:** Edit `BattleAnimCmd_ClearObjs` in [engine/battle_anims/anim_commands.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle_anims/anim_commands.asm):

```diff
 BattleAnimCmd_ClearObjs:
-; BUG: BattleAnimCmd only clears the first 6⅔ objects (see docs/bugs_and_glitches.md)
 	ld hl, wActiveAnimObjects
-	ld a, $a0
+	ld a, NUM_BATTLE_ANIM_STRUCTS * BATTLEANIMSTRUCT_LENGTH
 .loop
 	ld [hl], 0
 	inc hl
 	dec a
 	jr nz, .loop
 	ret
```


### Options menu fails to clear joypad state on initialization

([Video](https://www.youtube.com/watch?v=uhDSIkXkl3g))

This bug allows all the options to be updated at once if the left or right buttons are pressed on the same frame that the options menu is opened.

**Fix:** Edit `_Option` in [engine/menus/options_menu.asm](https://github.com/pret/pokecrystal/blob/master/engine/menus/options_menu.asm):

```diff
 _Option:
-; BUG: Options menu fails to clear joypad state on initialization (see docs/bugs_and_glitches.md)
+	call ClearJoypad
 	ld hl, hInMenu
 	ld a, [hl]
 	push af
```


### `SFX_RUN` does not play correctly when a wild Pokémon flees from battle

**Fix:** Edit `WildFled_EnemyFled_LinkBattleCanceled` in [engine/battle/core.asm](https://github.com/pret/pokecrystal/blob/master/engine/battle/core.asm):

```diff
-; BUG: SFX_RUN does not play correctly when a wild Pokemon flees from battle (see docs/bugs_and_glitches.md)
 	ld de, SFX_RUN
-	call PlaySFX
+	call WaitPlaySFX
```
