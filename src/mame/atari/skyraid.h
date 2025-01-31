// license:BSD-3-Clause
// copyright-holders:Stefan Jokisch
#ifndef MAME_ATARI_SKYRAID_H
#define MAME_ATARI_SKYRAID_H

#pragma once

#include "sound/discrete.h"
#include "emupal.h"

class skyraid_state : public driver_device
{
public:
	skyraid_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_pos_ram(*this, "pos_ram"),
		m_alpha_num_ram(*this, "alpha_num_ram"),
		m_obj_ram(*this, "obj_ram"),
		m_discrete(*this, "discrete"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_led(*this, "led")
	{ }

	void skyraid(machine_config &config);

private:
	uint8_t skyraid_port_0_r();
	void skyraid_range_w(uint8_t data);
	void skyraid_offset_w(uint8_t data);
	void skyraid_scroll_w(uint8_t data);
	virtual void machine_start() override;
	virtual void video_start() override;
	void skyraid_palette(palette_device &palette) const;
	uint32_t screen_update_skyraid(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void skyraid_sound_w(uint8_t data);
	void draw_text(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_terrain(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_missiles(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_trapezoid(bitmap_ind16& dst, bitmap_ind16& src);

	void skyraid_map(address_map &map);

	int m_analog_range = 0;
	int m_analog_offset = 0;

	int m_scroll = 0;

	required_shared_ptr<uint8_t> m_pos_ram;
	required_shared_ptr<uint8_t> m_alpha_num_ram;
	required_shared_ptr<uint8_t> m_obj_ram;
	required_device<discrete_device> m_discrete;
	bitmap_ind16 m_helper;

	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	output_finder<> m_led;
};

/*----------- defined in audio/skyraid.c -----------*/
DISCRETE_SOUND_EXTERN( skyraid_discrete );

#endif // MAME_ATARI_SKYRAID_H
