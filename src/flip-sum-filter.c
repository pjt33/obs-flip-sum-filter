/*
Copyright (c) 2020 Peter Taylor

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>

struct flip_sum_context
{
	size_t channels;
};

static const char *smfs_name(void *type_data)
{
	UNUSED_PARAMETER(type_data);

	// TODO l10n
	return "Flip and sum";
}

static void smfs_destroy(void *data)
{
	struct flip_sum_context* ctxt = data;
	bfree(ctxt);
}

static void smfs_update(void *data, obs_data_t *settings)
{
	UNUSED_PARAMETER(settings);

	struct flip_sum_context *ctxt = data;
	ctxt->channels = audio_output_get_channels(obs_get_audio());
}

static void *smfs_create(obs_data_t *settings, obs_source_t *filter)
{
	struct flip_sum_context *ctxt = bzalloc(sizeof(*ctxt));
	smfs_update(ctxt, settings);
	return ctxt;
}

static struct obs_audio_data *smfs_filter_audio(void *data, struct obs_audio_data *audio)
{
	struct flip_sum_context *ctxt = data;
	float **adata = (float**)audio->data;

	if (ctxt->channels >= 2) {
		for (size_t i = 0; i < audio->frames; i++) {
			const register float diff = adata[0][i] - adata[1][i];
			adata[0][i] = diff;
			adata[1][i] = diff;
		}
	}

	return audio;
}

struct obs_source_info flip_sum_filter = {
	.id = "flip_sum_filter",
	.type = OBS_SOURCE_TYPE_FILTER,
	.output_flags = OBS_SOURCE_AUDIO,
	.get_name = smfs_name,
	.create = smfs_create,
	.update = smfs_update,
	.destroy = smfs_destroy,
	.filter_audio = smfs_filter_audio,
};
