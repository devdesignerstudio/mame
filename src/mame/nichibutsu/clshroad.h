// license:BSD-3-Clause
// copyright-holders:Luca Elia
#ifndef MAME_NICHIBUTSU_CLSHROAD_H
#define MAME_NICHIBUTSU_CLSHROAD_H

#pragma once

#include "emupal.h"
#include "screen.h"
#include "tilemap.h"

class clshroad_state : public driver_device
{
public:
	clshroad_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_audiocpu(*this, "audiocpu")
		, m_screen(*this, "screen")
		, m_gfxdecode(*this, "gfxdecode")
		, m_palette(*this, "palette")
		, m_spriteram(*this, "spriteram")
		, m_vram_0(*this, "vram_0")
		, m_vram_1(*this, "vram_1")
		, m_vregs(*this, "vregs")
	{ }

	void firebatl(machine_config &config);
	void clshroad(machine_config &config);
	void init_firebatl();

private:
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<screen_device> m_screen;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_vram_0;
	required_shared_ptr<uint8_t> m_vram_1;
	required_shared_ptr<uint8_t> m_vregs;

	u8 m_main_irq_mask = 0U;
	u8 m_sound_irq_mask = 0U;
	u8 m_color_bank = 0U;
	u8 m_video_unk = 0U;

	tilemap_t *m_tilemap_0a = nullptr;
	tilemap_t *m_tilemap_0b = nullptr;
	tilemap_t *m_tilemap_1 = nullptr;

	uint8_t input_r(offs_t offset);
	DECLARE_WRITE_LINE_MEMBER(main_irq_mask_w);
	DECLARE_WRITE_LINE_MEMBER(sound_irq_mask_w);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_w);
	void vram_0_w(offs_t offset, uint8_t data);
	void vram_1_w(offs_t offset, uint8_t data);

	TILE_GET_INFO_MEMBER(get_tile_info_0a);
	TILE_GET_INFO_MEMBER(get_tile_info_0b);
	TILEMAP_MAPPER_MEMBER(tilemap_scan_rows_extra);
	TILE_GET_INFO_MEMBER(get_tile_info_fb1);
	TILE_GET_INFO_MEMBER(get_tile_info_1);

	virtual void machine_start() override;
	virtual void machine_reset() override;
	DECLARE_VIDEO_START(firebatl);
	void firebatl_palette(palette_device &palette) const;
	DECLARE_VIDEO_START(clshroad);
	void clshroad_palette(palette_device &palette) const;
	void color_bank_w(offs_t offset, u8 data);
	void video_unk_w(offs_t offset, u8 data);
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);

	INTERRUPT_GEN_MEMBER(vblank_irq);
	INTERRUPT_GEN_MEMBER(half_vblank_irq);
	INTERRUPT_GEN_MEMBER(sound_timer_irq);
	void clshroad_map(address_map &map);
	void clshroad_sound_map(address_map &map);
};

#endif // MAME_NICHIBUTSU_CLSHROAD_H
