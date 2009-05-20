/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define MP4_BLOCK_SIZE 4096

#define FOURCC_EQ(a, b) ((a)[0] == (b)[0] && (a)[1] == (b)[1] && (a)[2] && (b)[2] && (a)[3] == (b)[3])

typedef struct mp4info {
  PerlIO *infile;
  char *file;
  Buffer *buf;
  uint64_t size;  // total size
  uint8_t  hsize; // header size
  uint64_t rsize; // remaining size
  HV *info;
  HV *tags;
  uint32_t current_track;
} mp4info;

static int get_mp4tags(PerlIO *infile, char *file, HV *info, HV *tags);

int _mp4_read_box(mp4info *mp4);
uint8_t _mp4_parse_ftyp(mp4info *mp4);
uint8_t _mp4_parse_mvhd(mp4info *mp4);
uint8_t _mp4_parse_tkhd(mp4info *mp4);
uint8_t _mp4_parse_hdlr(mp4info *mp4);
uint8_t _mp4_parse_stsd(mp4info *mp4);
uint8_t _mp4_parse_mp4a(mp4info *mp4);
uint8_t _mp4_parse_esds(mp4info *mp4);
uint8_t _mp4_parse_stts(mp4info *mp4);
uint8_t _mp4_parse_stsc(mp4info *mp4);
uint8_t _mp4_parse_stsz(mp4info *mp4);
uint8_t _mp4_parse_stco(mp4info *mp4);
uint8_t _mp4_parse_meta(mp4info *mp4);
uint8_t _mp4_parse_ilst(mp4info *mp4);
uint8_t _mp4_parse_ilst_data(mp4info *mp4, uint32_t size, SV *key);
uint8_t _mp4_parse_ilst_custom(mp4info *mp4, uint32_t size);
HV * _mp4_get_current_trackinfo(mp4info *mp4);
uint32_t _mp4_descr_length(Buffer *buf);
