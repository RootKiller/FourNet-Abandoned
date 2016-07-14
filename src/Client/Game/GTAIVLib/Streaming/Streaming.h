// Copyright (C) 2016 by Rage MP Team

#pragma once

/**
 * Implementation of the game CStreaming class.
 */
class CStreaming
{
public:
	/**
	 * Loads all requested models immediately.
	 *
	 * @param[in] modelHash The hash of the model to load.
	 * @param[in] unknown0 ?
	 * @param[in] unknown1 ?
	 * @return ?
	 */
	static bool			RequestSpecialModel(const unsigned modelHash, const unsigned unknown0, const unsigned unknown1);

	/**
	 * Loads all requested models immediately.
	 *
	 * @param[in] priorityModelsOnly Should we load priority models only or all of them?
	 * @return ?
	 */
	static int			LoadAllRequestedModels(const bool priorityModelsOnly);

	/**
	 * Request model by given hash.
	 *
	 * @param[in] modelHash The model hash.
	 * @param[in] unk ?
	 */
	static void			RequestModel(const unsigned modelHash, const unsigned unk);

	/**
	 * Check if given model has been loaded.
	 *
	 * @param[in] modelHash The hash of the model.
	 * @return @c true if model was loaded @c false otherwise.
	 */
	static bool			HasModelLoaded(const unsigned modelHash);
};

/**
 * Find index of the model by it's hash.
 *
 * @note We don't know yet the proper placement for this method but as it's related
 *       to models putting in Streaming code seems natural.
 *
 * It's maybe CModelInfo::GetIndexFromHash or something like that.
 *
 * @param[in] modelHash The hash of the model.
 * @param[out] modelIndex The model index.
 * @return ?
 */
int ModelIndexByModelHash(const unsigned modelHash, int *const modelIndex);

/* eof */
