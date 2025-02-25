# Event Commands

Defined in [macros/scripts/events.asm](https://github.com/pret/pokecrystal/blob/master/macros/scripts/events.asm) and [engine/overworld/scripting.asm:ScriptCommandTable](https://github.com/pret/pokecrystal/blob/master/engine/overworld/scripting.asm).


## `$00`: <code>scall <i>script</i></code>
Used to call a script inside a different one. Once the former reaches its `end`, the game will return to the rest of the script that first called it.


## `$01`: <code>farscall <i>script</i></code>
A version of `scall` used to call scripts that are in different banks.


## `$02`: <code>memcall <i>script</i></code>
Used in engine scripts to call a function via a 2byte pointer pointing to a 3byte pointer. Seldom used in [engine/phone/phone.asm](https://github.com/pret/pokecrystal/blob/master/engine/phone/phone.asm#L384).


## `$03`: <code>sjump <i>script</i></code>
Used to jump to a script inside a different one. Once the former reaches its `end`, the game will return to the rest of the script that first called it.


## `$04`: <code>farsjump <i>script</i></code>
A version of `sjump` used to jump to scripts that are in different banks.


## `$05`: <code>memjump <i>script</i></code>
Used in engine scripts to jump to a function via a 2byte pointer pointing to a 3byte pointer. Seldom used in [engine/overworld/events.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/events.asm#L852).


## `$06`: <code>ifequal <i>byte</i>, <i>script</i></code>
Used in to compare if a value is identical to another defined value.


## `$07`: <code>ifnotequal <i>byte</i>, <i>script</i></code>
Used to compare if a value is not identical to another defined value.


## `$08`: <code>iffalse <i>script</i></code>
Used to see if an event/flag hasn't been set, or if the player told "no" to a yes or no question.


## `$09`: <code>iftrue <i>script</i></code>
Used to see if an event/flag has been set.


## `$0A`: <code>ifgreater <i>byte</i>, <i>script</i></code>
Used to compare if a value is greater than another defined value.


## `$0B`: <code>ifless <i>byte</i>, <i>script</i></code>
Used to compare if a value is lesser than another defined value.


## `$0C`: <code>jumpstd <i>std_script</i></code>
Used in map scripts to jump to an `std_script`, like Pokémon Center/Mart signs, or Gym statues. Refers to [engine/events/std_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/std_scripts.asm).


## `$0D`: <code>callstd <i>std_script</i></code>
Unused in regular gameplay. Identical to `jumpstd`, only as a `call` instead of a `jump`.


## `$0E`: <code>callasm <i>asm</i></code>
Used in engine scripts to call an asm function.


## `$0F`: <code>special <i>special_pointer</i></code>
Used to call a `special` function. Refers to [data/events/special_pointers.asm](https://github.com/pret/pokecrystal/blob/master/data/events/special_pointers.asm).


## `$10`: <code>memcallasm <i>asm</i></code>
Used in engine scripts to call an asm function via a 2byte pointer pointing to a 3byte pointer. Seldom used in [engine/overworld/events.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/events.asm#L852).


## `$11`: <code>checkmapscene <i>map</i></code>
Unused in regular gameplay. Used to check whether or not a given scene has been triggered, in a map other than the current one.


## `$12`: <code>setmapscene <i>map</i>, <i>scene_id</i></code>
Used to set a given scene as having been triggered, in a map other than the current one.


## `$13`: `checkscene`
Used to check whether or not a given scene from the current map has been triggered. See [maps/PlayersHouse1F.asm](https://github.com/pret/pokecrystal/blob/master/maps/PlayersHouse1F.asm#L113) and [maps/RuinsOfAlphResearchCenter.asm](https://github.com/pret/pokecrystal/blob/master/maps/RuinsOfAlphResearchCenter.asm#L21) as examples.


## `$14`: <code>setscene <i>scene_id</i></code>
Used to set a given scene from the current map as having been triggered.


## `$15`: <code>setval <i>value</i></code>

<code>[wScriptVar] = <i>value</i></code>

Used to load a given variable into RAM. Used in a variety of situations, like calling the right Unown puzzle, the right Move Tutor option, or the right Pokémon for `MonCheck`.


## `$16`: <code>addval <i>value</i></code>

<code>[wScriptVar] += <i>value</i></code>

Used to add a certain number to a given variable into RAM.


## `$17`: <code>random <i>value</i></code>
Used to call a random number, in conjunction with a value check command like `ifequal `. See [maps/OlivineCity.asm](https://github.com/pret/pokecrystal/blob/master/maps/OlivineCity.asm#L76) and [engine/phone/scripts/jack_gossip.asm](https://github.com/pret/pokecrystal/blob/master/engine/phone/scripts/jack_gossip.asm#L4) as examples.


## `$18`: `checkver`
Leftover from *Gold and Silver*, where it was used in map scripts to check the version ID of the game, either *Gold* (0) or *Silver* (1). By default, using `iftrue` would assume the version played is *Silver*.


## `$19`: <code>readmem <i>address</i></code>

<code>[wScriptVar] = [<i>address</i>]</code>

Used to write a given variable from a ram address to RAM.


## `$1A`: <code>writemem <i>address</i></code>

<code>[<i>address</i>] = [wScriptVar]</code>

Used to write a given variable from RAM to a ram address.


## `$1B`: <code>loadmem <i>address</i>, <i>value</i></code>

<code>[<i>address</i>] = <i>value</i></code>

Used to write a given value to a ram address.


## `$1C`: <code>readvar <i>variable</i></code>

<code>[wScriptVar] = GetVarAction(<i>variable</i>)</code>

Used to check `wScriptVar` values and write them into RAM.


## `$1D`: <code>writevar <i>variable</i></code>

<code>GetVarAction(<i>variable</i>) = [wScriptVar]</code>

Used to write a given variable from RAM to `wScriptVar` offsets.


## `$1E`: <code>loadvar <i>variable</i>, <i>value</i></code>

<code>GetVarAction(<i>variable</i>) = <i>value</i></code>

Used to write given variable to `GetVarAction` offsets.


## `$1F`: <code>giveitem <i>item_id</i>[, <i>quantity</i>=1]</code>
Used to give the player a specific item in a defined quantity.


## `$20`: <code>takeitem <i>item_id</i>[, <i>quantity</i>=1]</code>
Used to take away a specific item in a defined quantity from the player's inventory.


## `$21`: <code>checkitem <i>item_id</i></code>
Used to check if the player does or doesn't have a specific item in their inventory.


## `$22`: <code>givemoney <i>account</i>, <i>value</i></code>
Used to give a certain sum of money to the player.


## `$23`: <code>takemoney <i>account</i>, <i>value</i></code>
Used to take a given sum of money from the player. See [maps/Route39Farmhouse.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route39Farmhouse.asm#L23) as an example.


## `$24`: <code>checkmoney <i>account</i>, <i>value</i></code>
Used to check whether or not the player has a given sum of money. See [maps/Route39Farmhouse.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route39Farmhouse.asm#L23) as an example.


## `$25`: <code>givecoins <i>value</i></code>
Used to gift the player a specific amount of Game Corner coins.


## `$26`: <code>takecoins <i>value</i></code>
Used to take away a specific amount of Game Corner coins from the player.


## `$27`: <code>checkcoins <i>value</i></code>
Used to check if the player does or doesn't have a specific amount of Game Corner coins.


## `$28`: <code>addcellnum <i>contact_id</i></code>
Used to save a non-trainer character's phone number to the player's PokéGear.


## `$29`: <code>delcellnum <i>contact_id</i></code>
Used to delete a non-trainer character's phone number from the player's PokéGear.


## `$2A`: <code>checkcellnum <i>contact_id</i></code>
Used in conjunction with an `iftrue` or an `iffalse` check to see if the player has or hasn't registered a given character's phone number.


## `$2B`: <code>checktime <i>time</i></code>
Used to check what time of day it is, either `MORN`, `DAY`, or `NITE`.


## `$2C`: <code>checkpoke <i>mon_id</i></code>
Used to check if a given Pokémon is in the player's party.


## `$2D`: <code>givepoke <i>mon_id</i>, <i>level</i>[, <i>item</i>=0[, <i>nickname</i>, <i>ot_name</i>]]</code>
Used to gift the player a given Pokémon at a given level. Two extra parameters can also be set, namely the Pokémon's nickname, and its Original Trainer's name and gender (the latter is male/0 by default, but can be set to female/1). See [maps/Route35GoldenrodGate.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route35GoldenrodGate.asm#L31) as an example.


## `$2E`: <code>giveegg <i>mon_id</i>, <i>level</i></code>
Used to gift the player an egg of a specific Pokémon species. The level at which it hatches can be set manually, but using `EGG_LEVEL` will default to a level 5 hatchling.


## `$2F`: <code>givepokemail <i>pointer</i></code>
Used to give pokemail to an in-game gift Pokémon, specifying which type of mail and what message it will have. See [maps/Route35GoldenrodGate.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route35GoldenrodGate.asm#L32) as an example.


## `$30`: <code>checkpokemail <i>pointer</i></code>
Used as part of the Kenya side-quest, to check if the mail matches the one that was given to the player on Route 35. See [maps/Route31.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route31.asm#L198) as an example.


## `$31`: <code>checkevent <i>event_flag</i></code>
Used to check whether or not an event flag has been set. An event that has been set may be used in conjunction with an `iftrue` or `iffalse` check.


## `$32`: <code>clearevent <i>event_flag</i></code>
Used to clear an event flag. A map object that is assigned a set event will be neither visible nor interactable. and so clearing said flag will make the object appear.


## `$33`: <code>setevent <i>event_flag</i></code>
Used to set an event flag. An event that has been set may be used in conjunction with an `iftrue` or `iffalse` check. Moreover, a map object that is assigned a set event will no longer be visible nor interactable.

Events may be set upon starting a new save by being defined as such in [engine/events/std_scripts.asm](https://github.com/pret/pokecrystal/blob/master/maps/engine/events/std_scripts.asm#L480).


## `$34`: <code>checkflag <i>engine_flag</i></code>
Used to check whether or not an engine flag has been set.


## `$35`: <code>clearflag <i>engine_flag</i></code>
Used to clear an engine flag.


## `$36`: <code>setflag <i>engine_flag</i></code>
Used to set an engine flag.


## `$37`: `wildon`
Unused in regular gameplay. If one has used `wildoff` earlier, then using `wildon` will, appropriately, re-enable wild encounters.


## `$38`: `wildoff`
Unused in regular gameplay. Using this command will disable wild encounters for all maps.


## `$39`: <code>xycompare <i>pointer</i></code>
Unused in regular gameplay. This command compares the player's current X and Y coordinates with the ones in a table. To be useful, this code can only be used in a command queue, because with every step the player takes the bits are reset.


## `$3A`: <code>warpmod <i>warp_id</i>, <i>map</i></code>
Unused in regular gameplay. Used in map callbacks to change the destination of a warp set to `-1`. Here's an example of `warpmod` from [Polished Crystal](https://github.com/Rangi42/polishedcrystal/blob/master/maps/LavRadioTower1F.asm#L25).


## `$3B`: <code>blackoutmod <i>map</i></code>
Used to change the destination the player will be warped to after blacking out. Refers to [data/maps/spawn_points.asm](https://github.com/pret/pokecrystal/blob/master/data/maps/spawn_points.asm).

The point of this command is to avoid some story "desyncs". For example, a `blackoutmod` command set to Cherrygrove City is defined when meeting Prof. Oak at [Mr Pokémon's house](https://github.com/pret/pokecrystal/blob/master/maps/MrPokemonsHouse.asm#L37). If it weren't there, and the player hadn't visited Cherrygrove's Pokémon Center, then blacking out on Route 30 would warp them back to New Bark Town, thus skipping the first rival battle.


## `$3C`: <code>warp <i>map</i>, <i>x</i>, <i>y</i></code>
Used to warp the player to a given location, at specified coordinates. Note that this is done silently, though a separate `playsound` command may be added to it, either before or after.

Also note that the player will always be warped facing down. If one wishes to warp the player in another direction, see `warpfacing`.


## `$3D`: <code>getmoney <i>string_buffer</i>, <i>account</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = PrintNum(GetMoneyAccount(<i>account</i>))</code>

Used by [engine/phone/scripts/mom.asm](https://github.com/pret/pokecrystal/blob/master/engine/phone/scripts/mom.asm) to display the correct amount of money when calling mom, to know how much money has been saved.


## `$3E`: <code>getcoins <i>string_buffer</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = PrintNum([wCoins])</code>

Unused in regular gameplay. Identical to `getmoney`, only with the Game Corner coins in the player's Coin Case, as opposed to money.


## `$3F`: <code>getnum <i>string_buffer</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = PrintNum([wScriptVar])</code>

Used to display a given value in a dialogue box. See [maps/Route35NationalParkGate.asm](https://github.com/pret/pokecrystal/blob/master/maps/Route35NationalParkGate.asm#L54) as an example.

## `$40`: <code>getmonname <i>string_buffer</i>, <i>mon_id</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = GetPokemonName(<i>mon_id</i>)</code>

If <code><i>mon_id</i></code> = `USE_SCRIPT_VAR`, then it uses `[wScriptVar]` instead.

Used to display a given Pokémon name in a dialogue box. See [maps/ElmsLab.asm](https://github.com/pret/pokecrystal/blob/master/maps/ElmsLab.asm#L177) as an example.


## `$41`: <code>getitemname <i>string_buffer</i>, <i>item_id</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = GetItemName(<i>item_id</i>)</code>

If <code><i>item_id</i></code> = `USE_SCRIPT_VAR`, then it uses `[wScriptVar]` instead.

Used to display a given item name in a dialogue box. See [maps/CeladonCafe.asm](https://github.com/pret/pokecrystal/blob/master/maps/CeladonCafe.asm#L91) as an example.


## `$42`: <code>getcurlandmarkname <i>string_buffer</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = GetLandmarkName(GetWorldMapLocation())</code>

Used to display the current location name in a dialogue box. Used by both [engine/phone/scripts/mom.asm](https://github.com/pret/pokecrystal/blob/master/engine/phone/scripts/mom.asm#L12) and [engine/events/std_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/std_scripts.asm#L1757).


## `$43`: <code>gettrainername <i>string_buffer</i>, <i>trainer_group</i>, <i>trainer_id</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = GetTrainerName(<i>trainer_group</i>, <i>trainer_id</i>)</code>

Used to display a given trainer name in a dialogue box. See [maps/VioletGym.asm](https://github.com/pret/pokecrystal/blob/master/maps/VioletGym.asm#L105) as an example.


## `$44`: <code>getstring <i>string_buffer</i>, <i>text_pointer</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = CopyName1([wScriptBank], <i>text_pointer</i>)</code>

Used to display a given string in a dialogue box. See [maps/LavRadioTower1F.asm](https://github.com/pret/pokecrystal/blob/master/maps/LavRadioTower1F.asm#L34) as an example.


## `$45`: `itemnotify`
Used alongside a `giveitem` command. Prints the "<PLAYER> put the <ITEM> in the <BAG POCKET>." message. See [maps/DragonsDenB1F.asm](https://github.com/pret/pokecrystal/blob/master/maps/DragonsDenB1F.asm#L57) as an example.


## `$46`: `pocketisfull`
Seldom called by `GiveItemScript`, in [engine/overworld/scripting.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/scripting.asm#L467).


## `$47`: `opentext`
Used before a `writetext` command, to open a dialogue box.


## `$48`: <code>reanchormap [<i>dummy</i>=0]</code>
Used to trigger a complete screen refresh.


## `$49`: `closetext`
Used after either a `waitbutton` or `promptbutton` command, to close a dialogue box.


## `$4A`: <code>writeunusedbyte <i>byte</i></code>

<code>[<i>wUnusedScriptByte</i>] = <i>byte</i></code>

Unused in regular gameplay. All this command does is load a byte into `wUnusedScriptByte`.


## `$4B`: <code>farwritetext <i>text_pointer</i></code>
Used in engine scripts, combines both `farcall` and `writetext`.


## `$4C`: <code>writetext <i>text_pointer</i></code>
Used after an `opentext` command, to load a given text pointer.


## `$4D`: <code>repeattext <i>byte1</i>, <i>byte2</i></code>
Seldom called by `JumpTextFacePlayerScript`, in [engine/overworld/scripting.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/scripting.asm#L309).


## `$4E`: `yesorno`
Used to load a "yes or no" prompt. To be used in conjunction with an `iftrue` or `iffalse` check, for either "yes" or "no" respectively.


## `$4F`: <code>loadmenu <i>menu_header</i></code>
Used to load menu data. See [maps/DragonShrine.asm](https://github.com/pret/pokecrystal/blob/master/maps/DragonShrine.asm#L21) as an example.


## `$50`: `closewindow`
Used to close a menu window.


## `$51`: <code>jumptextfaceplayer <i>text_pointer</i></code>
Used to load the text of an `object_event`. Essentially combines `faceplayer`, `opentext`, `writetext`, `waitbutton`, and `closetext` in a single command.


## `$52`: <code>farjumptext <i>text_pointer</i></code>
Seldom used in [engine/events/std_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/std_scripts.asm) to draw text from [data/text/std_text.asm](https://github.com/pret/pokecrystal/blob/master/data/text/std_text.asm).


## `$53`: <code>jumptext <i>text_pointer</i></code>
Identical to `jumptextfaceplayer`, aside from lacking the `faceplayer` aspect. May be used for NPCs, though this command is usually reserved to load the text of a `bg_event`, namely signs.


## `$54`: `waitbutton`
Used after a `writetext` command. This will leave the dialogue box on-screen after its message is displayed, with the player needing to press either **A** or **B** to close it.


## `$55`: `promptbutton`
Used after a `writetext` command. Behaves identically to `waitbutton`, only differing in that here a down-facing arrow will flicker in the bottom-right corner of the dialogue box. This command is meant to be used in case one needs to load two or more sets of dialogue one after another, since using `waitbutton` would not play the "next dialogue box" sound.


## `$56`: <code>pokepic <i>mon_id</i></code>
Makes a given Pokémon's front sprite pop-up in a small window in the center of the screen. The sprite will be static, and in grayscale. Only used in Elm's Lab when interacting with the starters' poké balls.


## `$57`: `closepokepic`
Used to close a `pokepic`.


## `$58`: `_2dmenu`
A 2-dimensional menu, where the player can move their cursor in all four directions. Used for the battle menus, as well as the blackboard in Earl's academy. A writeup on menu types can be found [here](https://github.com/pret/pokecrystal/blob/master/docs/menus.md).


## `$59`: `verticalmenu`
A generic menu display. A writeup on menu types can be found [here](https://github.com/pret/pokecrystal/blob/master/docs/menus.md).


## `$5A`: `loadpikachudata`
Unused in regular gameplay. All this command does is load the data for a level 5 Pikachu.


## `$5B`: `randomwildmon`
Used as part of the Sweet Scent, But Catching Contest, and wild encounter engine scripts.


## `$5C`: `loadtemptrainer`

`[wOtherTrainer] = [wTempTrainer]`

Seldom used in [engine/events/trainer_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/trainer_scripts.asm), where it loads temporary trainer data.


## `$5D`: <code>loadwildmon <i>mon_id</i>, <i>level</i></code>
Used to load a battle against a specific Pokémon species at a given level. See [maps/UnionCaveB2F.asm](https://github.com/pret/pokecrystal/blob/master/maps/UnionCaveB2F.asm#L28) as an example.


## `$5E`: <code>loadtrainer <i>trainer_group</i>, <i>trainer_id</i></code>
Used to load a battle against a specific trainer class and a given party id.


## `$5F`: `startbattle`
Used directly following either a `loadwildmon` or a `loadtrainer`.


## `$60`: `reloadmapafterbattle`
Used following a `startbattle`. Reloads the map after the battle is over.


## `$61`: <code>catchtutorial <i>byte</i></code>
Used to initiate the Pokémon catching tutorial on Route 29. Needs to be preceded with a `loadwildmon` command.


## `$62`: <code>trainertext <i>text_id</i></code>
Seldom used in [engine/events/trainer_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/trainer_scripts.asm), where it loads temporary trainer dialogue data.


## `$63`: <code>trainerflagaction <i>action</i></code>
Seldom used in [engine/events/trainer_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/trainer_scripts.asm), where it handles the "trainer defeated" flag data.


## `$64`: <code>winlosstext <i>win_text_pointer</i>, <i>loss_text_pointer</i></code>
Used in trainer battle scripts to print a given string when the player either wins or loses. Note that this command needs to be used in conjunction with `BATTLETYPE_CANLOSE`, otherwise the game will skip straight to the blackout message. See [CherrygroveCity.asm](https://github.com/pret/pokecrystal/blob/master/maps/CherrygroveCity.asm#L122) as an example.


## `$65`: `scripttalkafter`
Seldom used in [engine/events/trainer_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/trainer_scripts.asm), where it handles what happens when talking to a defeated trainer.


## `$66`: `endifjustbattled`
Used as part of the trainer encounter setup. This command will make it so the "after battle" dialogue doesn't automatically play once the battle ends and the player is returned to the overworld.


## `$67`: `checkjustbattled`
Unused in regular gameplay. Used to check if a given trainer has just been battled or not.


## `$68`: <code>setlasttalked <i>object_id</i></code>
Used to set a character as the one last talked to.


## `$69`: <code>applymovement <i>object_id</i>, <i>data_pointer</i></code>
Used to assign either the player or a given object a movement script.


## `$6A`: <code>applymovementlasttalked <i>data_pointer</i></code>
Used to assign a movement script to the last talked character.


## `$6B`: `faceplayer`
Used to make a given character face the player.


## `$6C`: <code>faceobject <i>object1</i>, <i>object2</i></code>
Used to make a character face another given character.


## `$6D`: <code>variablesprite <i>variable_sprite_id</i>, <i>sprite_id</i></code>
Used to change the appearance of a variable sprite. A writeup on variable sprites can be found [here](https://github.com/pret/pokecrystal/wiki/Add-a-new-overworld-sprite).


## `$6E`: <code>disappear <i>object_id</i></code>
Used to hide an object.


## `$6F`: <code>appear <i>object_id</i></code>
Used to make a hidden object visible.


## `$70`: <code>follow <i>object2</i>, <i>object1</i></code>
Used to make the player follow an NPC, or vice versa. Do note that NPCs can't follow the player across map connections, nor through warps. NPCs followers are coded to jump off ledges like the player, though this won't play any sound.


## `$71`: `stopfollow`
Used to terminates a `follow` command.


## `$72`: <code>moveobject <i>object_id</i>, <i>x</i>, <i>y</i></code>
Used to move an object to a new location on the same map. Note that this only works if said object is not visible (see `disappear`).


## `$73`: <code>writeobjectxy <i>object_id</i></code>
Writes the current x/y values of a trainer into RAM, and they will stand at their current location even when outside of the player's sight. They will not return to their old location until a new map loads. Seldom used in [engine/events/trainer_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/trainer_scripts.asm).


## `$74`: <code>loademote <i>emote_id</i></code>
Used to load an emote in an engine script.


## `$75`: <code>showemote <i>emote_id</i>, <i>object_id</i>, <i>length</i></code>
Used to display an emote in map scripts, alongside which object it will appear above, and for how long.


## `$76`: <code>turnobject <i>object_id</i>, <i>facing</i></code>
Used to turn an object in a given cardinal direction.


## `$77`: <code>follownotexact <i>object2</i>, <i>object1</i></code>
Unused in regular gameplay. Used to make an NPC follow the player (doing it the other way around may cause the game to lock up). Compared to `follow`, this command doesn't account for ledges on the follower's side. Moreover, while `stopfollow` has no effect here, warping to a new map simply resumes the game as usual, whereas doing the same with `follow` causes the game to softlock after the player walks around for a bit.


## `$78`: <code>earthquake <i>param</i></code>
Will make the screen shake for a given amount of time.


## `$79`: <code>changemapblocks <i>blockdata_pointer</i></code>

<code>ChangeMap(<i>blockdata_pointer</i>)</code>

Unused in regular gameplay. Used in map callbacks to draw a new map over a given map, as long as they share the same tileset and dimensions. Here's an example of `changemapblocks` from [Polished Crystal](https://github.com/Rangi42/polishedcrystal/tree/master/maps/LakeOfRage.asm#L69).


## `$7A`: <code>changeblock <i>x</i>, <i>y</i>, <i>block</i></code>
Used to change one or more blocks in a given part of the current map. If the change happens for an area happens to be on-screen, a `refreshmap` command will have to be used afterwards.


## `$7B`: `reloadmap`
Reloads the current map completely.


## `$7C`: `refreshmap`
Refreshed the part of the map that's currently on-screen.


## `$7D`: <code>writecmdqueue <i>queue_pointer</i></code>
Writes to a command queue, namely used by maps which use Strength boulders that can fall through holes in the ground. See [maps/IcePathB1F.asm](https://github.com/pret/pokecrystal/blob/master/maps/IcePathB1F.asm#L14) as an example.


## `$7E`: <code>delcmdqueue <i>byte</i></code>
Unused in regular gameplay. Deletes a given command queue from ram.


## `$7F`: <code>playmusic <i>music_id</i></code>
Used to call a given music track.


## `$80`: `encountermusic`
Seldom used in [engine/events/trainer_scripts.asm](https://github.com/pret/pokecrystal/blob/master/engine/events/trainer_scripts.asm), where it loads the right encounter music.


## `$81`: <code>musicfadeout <i>music_id</i>, <i>length</i></code>
Fades out the current music track, so another one can be played instead.


## `$82`: `playmapmusic`
Makes the current map's music track play again.


## `$83`: `dontrestartmapmusic`
Makes it so no music is played after the current map reloads.


## `$84`: <code>cry <i>mon_id</i></code>
Used to play a given Pokémon's cry.


## `$85`: <code>playsound <i>sfx_id</i></code>
Used to play a given sound effect.


## `$86`: `waitsfx`
Wait until the chosen sound effect finishes playing until the next instruction is read.


## `$87`: `warpsound`
Plays the door warp sound effect. Seldom used in the Battle Tower scripts.


## `$88`: `specialsound`
Plays the "get item"sound effect. Seldom used in the "give item" engine scripts.


## `$89`: <code>autoinput <i>input_pointer</i></code>
Unused in regular gameplay. Calls `StartAutoInput`, which lets the game play a series of defined actions, like in the Pokémon catching tutorial.


## `$8A`: <code>newloadmap <i>which_method</i></code>
Used to call a new `MAPSETUP` type. Refers to [constants/map_setup_constants.asm](https://github.com/pret/pokecrystal/blob/master/constants/map_setup_constants.asm).


## `$8B`: <code>pause <i>length</i></code>
Used to pause the game a given number of frames until the next instruction is read.


## `$8C`: <code>deactivatefacing <i>length</i></code>
Seldom used in `ChangeDirectionScript`.


## `$8D`: <code>sdefer <i>script</i></code>
Used in a map scene to run a script.


## `$8E`: `warpcheck`
If the player is under a movement script, and enters a warp (like a door), this command will trigger it and warp the player to the new map.


## `$8F`: <code>stopandsjump <i>script</i></code>
Unused in regular gameplay. Calls `StopScript`, and then `Script_sjump`.


## `$90`: `endcallback`
Used to `terminate` a callback script.


## `$91`: `end`
Used to terminate map scripts.


## `$92`: <code>reloadend <i>which_method</i></code>
Seldom used in `EdgeWarpScript` to load a new map, and then end the script.


## `$93`: `endall`
Seldom used to terminate `Script_Whiteout`.


## `$94`: <code>pokemart <i>mart_type</i>, <i>mart_id</i></code>
Used to call the data of a sale clerk, as in what items they will propose, and what dialogue set they will use. Refers to [data/items/marts.asm](https://github.com/pret/pokecrystal/blob/master/data/items/marts.asm).


## `$95`: <code>elevator <i>floor_list</i></code>
Used to read what floors will appear as options in the elevator interface, and what maps the player will be warped to. Used in conjunction with a given data table, see [maps/GoldenrodDeptStoreElevator.asm](https://github.com/pret/pokecrystal/blob/master/maps/GoldenrodDeptStoreElevator.asm#L8) as an example.


## `$96`: <code>trade <i>trade_id</i></code>
Used to call the data for an in-game trade NPC, as in what Pokémon they're looking for, which one they offer in return, as well as what dialogue set they will use. Refers to [data/events/npc_trades.asm](https://github.com/pret/pokecrystal/blob/master/data/events/npc_trades.asm).


## `$97`: <code>askforphonenumber <i>contact_id</i></code>
Used to save a given character's phone number to the player's PokéGear.


## `$98`: <code>phonecall <i>call_id</i></code>
Unused in regular gameplay. Used in map scripts to play the phonecall animation, with a defined caller name. This command needs to be preceded by an `opentext` to display properly, which in turn prints an empty dialogue box during the ringing, unlike actual phonecalls.

Also note that this command is improperly implemented, and may crash the game when used. The latter issue can be corrected with the [following fix](https://github.com/pret/pokecrystal/blob/master/docs/bugs_and_glitches.md#the-Unused-phonecall-script-command-may-crash).

Here is an example of a script using this command:
```
WrongPhoneNumberScript:
	opentext
	phonecall UnknownCallName
	writetext UnknownCallerText
	waitbutton
	hangup
	closetext
	end

UnknownCallName:
	db "UNKNOWN CALL:@"

UnknownCallerText:
	text "Hey grandma, could"
	line "you go pick up--"

	para "Oh, sorry. I got"
	line "the wrong number."
	done
```

## `$99`: `hangup`
Unused in regular gameplay. Used in map scripts to play the phonecall hangup animation (the "Click…" string and the three beeps that follow).


## `$9A`: <code>describedecoration <i>byte</i></code>
Used by the room decorations to call a flavor text string based on what type of decor it is (poster, doll/console, or giant doll). Refers to [engine/overworld/decorations.asm](https://github.com/pret/pokecrystal/blob/master/engine/overworld/decorations.asm#L971).


## `$9B`: <code>fruittree <i>tree_id</i></code>
Used by fruit trees to call what kind of berry or apricorn the player will receive from them. Refers to [data/items/fruit_trees.asm](https://github.com/pret/pokecrystal/blob/master/data/items/fruit_trees.asm).


## `$9C`: <code>specialphonecall <i>call_id</i></code>
Used to trigger dedicated phonecalls upon warping to a new map. See [maps/VioletGym.asm](https://github.com/pret/pokecrystal/blob/master/maps/VioletGym.asm) and [maps/Route31 .asm](https://github.com/pret/pokecrystal/blob/master/maps/Route31.asm) as examples.


## `$9D`: `checkphonecall`
Used in engine scripts to check if a given phonecall has or hasn't happened.


## `$9E`: <code>verbosegiveitem <i>item_id</i>[, <i>quantity</i>=1]</code>
Used to gift the player an item, with a corresponding message ("<PLAYER> received <ITEM>. <PLAYER> put the <ITEM> in the <BAG POCKET>.") This command combines `itemnotify` and `giveitem` together (only with a more verbose "get item" string).


## `$9F`: <code>verbosegiveitemvar <i>item_id</i>, <i>variable</i></code>
A variant of the `verbosegiveitem` command used for Kurt's "get Apricorn Ball" scripts.


## `$A0`: <code>swarm <i>swarm_id</i>, <i>map</i></code>
Used in conjunction with a `setflag` command to instantly trigger a Pokémon swarm in a given map. See [engine/phone/scripts/anthony.asm](https://github.com/pret/pokecrystal/blob/master/engine/phone/scripts/anthony.asm#L51) as an example.


## `$A1`: `halloffame`
Triggers the "entering the Hall of Fame" sequence, and then plays the credits.


## `$A2`: `credits`
Plays the end credits, and then returns the player to the title screen.


## `$A3`: <code>warpfacing <i>facing</i>, <i>map</i>, <i>x</i>, <i>y</i></code>
Used to warp the player to a given location, at specified coordinates. Unlike the regular `warp` command, here one may also specify if the player will appear on the new map facing `UP`, `LEFT`, or `RIGHT`.


## `$A4`: <code>battletowertext <i>bttext_id</i></code>
Seldom used in [maps/BattleTowerBattleRoom.asm](https://github.com/pret/pokecrystal/blob/master/maps/BattleTowerBattleRoom.asm) to load the enemy trainer's dialogue.


## `$A5`: <code>getlandmarkname <i>string_buffer</i>, <i>landmark_id</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = GetLandmarkName(<i>landmark_id</i>)</code>

Used in engine scripts to save a given location name in a string buffer, for it to then be displayed in a dialogue box.


## `$A6`: <code>gettrainerclassname <i>string_buffer</i>, <i>trainer_group</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = GetName(TRAINER_NAME, <i>trainer_group</i>)</code>

Used in engine scripts to save a trainer class name in a string buffer, for it to then be displayed in a dialogue box.


## `$A7`: <code>getname <i>string_buffer</i>, <i>type</i>, <i>id</i></code>

<code>GetStringBuffer(<i>string_buffer</i>) = GetName(<i>type</i>, <i>id</i>)</code>

Used in the Pokémon stats and trainer attributes engine scripts, to draw a given name. Refers to [constants/text_constants.asm](https://github.com/pret/pokecrystal/blob/master/constants/text_constants.asm).


## `$A8`: <code>wait <i>duration</i></code>
Seldom used in Goldenrod and Saffron's train station scripts. This command is used to make the player wait until the landmark sign disappears before they perform the "leave the train" animation.


## `$A9`: `checksave`
Unused in regular gameplay. May be used in conjunction with an `iftrue` or an `iffalse` check to see if the player has saved their game or not.
