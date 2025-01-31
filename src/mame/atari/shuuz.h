// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*************************************************************************

    Atari Shuuz hardware

*************************************************************************/
#ifndef MAME_ATARI_SHUUZ_H
#define MAME_ATARI_SHUUZ_H

#pragma once

#include "atarimo.h"
#include "atarivad.h"
#include "screen.h"
#include "tilemap.h"

class shuuz_state : public driver_device
{
public:
	shuuz_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_gfxdecode(*this, "gfxdecode")
		, m_screen(*this, "screen")
		, m_vad(*this, "vad")
	{ }

	void shuuz(machine_config &config);

private:
	void latch_w(uint16_t data);
	uint16_t leta_r(offs_t offset);
	uint16_t special_port0_r();

	virtual void machine_start() override;

	int get_hblank(screen_device &screen) const { return (screen.hpos() > (screen.width() * 9 / 10)); }

	TILE_GET_INFO_MEMBER(get_playfield_tile_info);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

	void main_map(address_map &map);

	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<atari_vad_device> m_vad;

	int m_cur[2]{};

	static const atari_motion_objects_config s_mob_config;
};

#endif // MAME_ATARI_SHUUZ_H
