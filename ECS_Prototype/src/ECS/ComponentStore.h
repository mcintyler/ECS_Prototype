#pragma once

struct ComponentStore {
	static int type_count;		// Amount of different component types
	static size_t* offsets;		// Array of offsets (in bytes) for each component in the data array
	static size_t* sizes;		// Array of sizes (in bytes) of each component
	static size_t total_size;	// Size (in bytes) of all components combined
	void* data;					// Array of all the components' data
};