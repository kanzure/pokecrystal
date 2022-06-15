OpenSRAM::
; if invalid bank, sram is disabled
	cp CART_SRAM_32KB
	jr c, .valid
if DEF(_DEBUG)
	push af
	push bc
	ld b, 1
.loop
	sla b
	dec a
	jr nz, .loop
	ld a, BANK(sOpenedInvalidSRAM)
	call OpenSRAM
	ld a, [sOpenedInvalidSRAM]
	or b
	ld [sOpenedInvalidSRAM], a
	pop bc
	pop af
endc
	jr CloseSRAM

.valid:
; switch to sram bank a
	push af
; latch clock data
	ld a, 1
	ld [MBC3LatchClock], a
; enable sram/clock write
	ld a, CART_SRAM_ENABLE
	ld [rRAMG], a
; select sram bank
	pop af
	ld [rRAMB], a
	ret

CloseSRAM::
	push af
	ld a, CART_SRAM_DISABLE
; reset clock latch for next time
	ld [MBC3LatchClock], a
; disable sram/clock write
	ld [rRAMG], a
	pop af
	ret
