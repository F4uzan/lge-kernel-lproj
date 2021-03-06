/*
 * LP5521 LED chip driver.
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contact: Samu Onkalo <samu.p.onkalo@nokia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef __LINUX_LP5521_H
#define __LINUX_LP5521_H

/* See Documentation/leds/leds-lp5521.txt */

struct lp5521_led_config {
	char		*name;
	u8		chan_nr;
	u8		led_current; /* mA x10, 0 if led is not connected */
	u8		max_current;
};

struct lp5521_led_pattern {
	u8 *r;
	u8 *g;
	u8 *b;
	u8 size_r;
	u8 size_g;
	u8 size_b;
};

#define LP5521_CLOCK_AUTO	0
#define LP5521_CLOCK_INT	1
#define LP5521_CLOCK_EXT	2

/* Bits in CONFIG register */
#define LP5521_PWM_HF			0x40	/* PWM: 0 = 256Hz, 1 = 558Hz */
#define LP5521_PWRSAVE_EN		0x20	/* 1 = Power save mode */
#define LP5521_CP_MODE_OFF		0	/* Charge pump (CP) off */
#define LP5521_CP_MODE_BYPASS		8	/* CP forced to bypass mode */
#define LP5521_CP_MODE_1X5		0x10	/* CP forced to 1.5x mode */
#define LP5521_CP_MODE_AUTO		0x18	/* Automatic mode selection */
#define LP5521_R_TO_BATT		4	/* R out: 0 = CP, 1 = Vbat */
#define LP5521_CLK_SRC_EXT		0	/* Ext-clk source (CLK_32K) */
#define LP5521_CLK_INT			1	/* Internal clock */
#define LP5521_CLK_AUTO			2	/* Automatic clock selection */

struct lp5521_platform_data {
	struct lp5521_led_config *led_config;
	u8	num_channels;
	u8	clock_mode;
	int	(*setup_resources)(void);
	void	(*release_resources)(void);
	void	(*enable)(bool state);
	const char *label;
	u8	update_config;
	struct lp5521_led_pattern *patterns;
	int num_patterns;
};

#if defined(CONFIG_MACH_MSM8X25_V7)    /*This Table is for V7*/
#if 1  /*V7 1st Tunning Current Table [Not Linear]*/
static const u8 current_index_mapped_value[256] = {
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 14, 14, 14, 14,
	14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
	14, 14, 14, 14, 14, 14, 14, 21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
	28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 35,
	35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
	35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 42, 42, 42, 42, 42,
	42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42,
	42, 42, 42, 42, 42, 42, 49, 49, 49, 49, 49, 49, 49, 49, 49,
	49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
	49, 49, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
	63, 63, 63, 63, 70, 70, 70, 77, 77, 77, 77, 84, 84, 84, 84,
	91, 91, 91, 91, 98, 98, 98, 98, 98, 98, 98, 105, 105, 105, 105,
	112, 112, 112, 112, 119, 119, 119, 140, 140, 140, 147, 147, 147, 154, 154,
	154, 161, 161, 168, 168, 175, 182, 189, 196, 203, 203, 210, 210, 224, 224,
	224
};
#else   /*V7 Original Tunning Current Table [Linear] */
static const u8 current_index_mapped_value[256] = {
	7, 7, 7, 7, 7, 7, 7, 7, 14, 14, 14, 14, 14, 14, 14,
	14, 21, 21, 21, 21, 21, 21, 21, 21, 28, 28, 28, 28, 28, 28,
	28, 28, 35, 35, 35, 35, 35, 35, 35, 35, 42, 42, 42, 42, 42,
	42, 42, 42, 49, 49, 49, 49, 49, 49, 49, 49, 56, 56, 56, 56,
	56, 56, 56, 56, 63, 63, 63, 63, 63, 63, 63, 63, 70, 70, 70,
	70, 70, 70, 70, 70, 77, 77, 77, 77, 77, 77, 77, 77, 84, 84,
	84, 84, 84, 84, 84, 84, 91, 91, 91, 91, 91, 91, 91, 91, 98,
	98, 98, 98, 98, 98, 98, 98, 105, 105, 105, 105, 105, 105, 105, 105,
	112, 112, 112, 112, 112, 112, 112, 112, 119, 119, 119, 119, 119, 119, 119,
	119, 126, 126, 126, 126, 126, 126, 126, 126, 133, 133, 133, 133, 133, 133,
	133, 133, 140, 140, 140, 140, 140, 140, 140, 140, 147, 147, 147, 147, 147,
	147, 147, 147, 154, 154, 154, 154, 154, 154, 154, 154, 161, 161, 161, 161,
	161, 161, 161, 161, 168, 168, 168, 168, 168, 168, 168, 168, 175, 175, 175,
	175, 175, 175, 175, 175, 182, 182, 182, 182, 182, 182, 182, 182, 189, 189,
	189, 189, 189, 189, 189, 189, 196, 196, 196, 196, 196, 196, 196, 196, 203,
	203, 203, 203, 203, 203, 203, 203, 210, 210, 210, 210, 210, 210, 210, 210,
	217, 217, 217, 217, 217, 217, 217, 217, 224, 224, 224, 224, 224, 224, 224,
	224
};
#endif
#elif defined(CONFIG_MACH_MSM7X25A_V3) /*This Table is for V3/GK*/
static const u8 current_index_mapped_value[256] = {
	7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,   // 14
	7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  8,  8,   // 29
	8,  8,  8,  9,  9,  9,  9,  9,  9, 10, 10, 10, 10, 10, 10,   // 44
	11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13,  // 59
	14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 17, 17, 17, 19,  // 74
	18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 22, 22, 23, 23, 24,  // 89
	24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31,  // 104
	31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38,  // 119
	39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 45, 46, 47, 48,  // 134
	49, 50, 51, 52, 52, 53, 54, 55, 56, 57, 58, 59, 60, 60, 61,  // 149
	61, 62, 62, 63, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,  // 164
	73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87,  // 179
	88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,  // 194
	103,104,105,106,107,108,109,111,112,113,114,115,116,117,118, // 209
	119,121,123,124,126,127,128,129,130,131,132,133,134,135,136, // 224
	138,140,142,143,144,146,148,150,151,152,154,155,157,158,159, // 239
	160,161,162,163,164,165,166,167,168,169,170,172,174,176,178, // 254
	180
};
#else  /*This Table is for linear tuning model*/
static const u8 current_index_mapped_value[256] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  // 14
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,  // 29
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,  // 44
	45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,    // 59
	60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,  // 74
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,  // 89
	90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,  // 104
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,  // 119
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,  // 134
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,  // 149
	150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,  // 164
	165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,  // 179
	180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,   // 194
	195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,   // 209
	210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,   // 224
	225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,   // 239
	240,241,242,243,244,245,246,247,248,249,220,251,252,253,254,   // 254
	255
};
#endif /*MACH_MSM8X25_V7 */
#endif /* __LINUX_LP5521_H */
