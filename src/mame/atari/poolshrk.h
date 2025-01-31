// license:BSD-3-Clause
// copyright-holders:Stefan Jokisch
/*************************************************************************

    Atari Pool Shark hardware

*************************************************************************/
#ifndef MAME_ATARI_POOLSHRK_H
#define MAME_ATARI_POOLSHRK_H

#pragma once

#include "machine/watchdog.h"
#include "sound/discrete.h"
#include "emupal.h"
#include "tilemap.h"

/* Discrete Sound Input Nodes */

class poolshrk_state : public driver_device
{
public:
	poolshrk_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_watchdog(*this, "watchdog"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_discrete(*this, "discrete"),
		m_playfield_ram(*this, "playfield_ram"),
		m_hpos_ram(*this, "hpos_ram"),
		m_vpos_ram(*this, "vpos_ram"),
		m_leds(*this, "led%u", 0U)
	{ }

	void poolshrk(machine_config &config);

	void init_poolshrk();

private:
	void da_latch_w(uint8_t data);
	void led_w(offs_t offset, uint8_t data);
	void watchdog_w(offs_t offset, uint8_t data);
	uint8_t input_r(offs_t offset);
	uint8_t irq_reset_r();
	void scratch_sound_w(offs_t offset, uint8_t data);
	void score_sound_w(uint8_t data);
	void click_sound_w(uint8_t data);
	void bump_sound_w(offs_t offset, uint8_t data);

	TILE_GET_INFO_MEMBER(get_tile_info);

	void poolshrk_palette(palette_device &palette) const;

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	virtual void video_start() override;
	void poolshrk_cpu_map(address_map &map);
	virtual void machine_start() override { m_leds.resolve(); }

	required_device<cpu_device> m_maincpu;
	required_device<watchdog_timer_device> m_watchdog;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	required_device<discrete_device> m_discrete;

	required_shared_ptr<uint8_t> m_playfield_ram;
	required_shared_ptr<uint8_t> m_hpos_ram;
	required_shared_ptr<uint8_t> m_vpos_ram;
	output_finder<2> m_leds;

	tilemap_t* m_bg_tilemap = nullptr;
	int m_da_latch = 0;
};


/*----------- defined in audio/poolshrk.c -----------*/
DISCRETE_SOUND_EXTERN( poolshrk_discrete );

#endif // MAME_ATARI_POOLSHRK_H
